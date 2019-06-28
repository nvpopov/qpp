#ifndef QPP_VASP_IO_NATIVE
#define QPP_VASP_IO_NATIVE

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>
#include <geom/geom.hpp>
#include <geom/ngbr.hpp>
#include <geom/geom_anim.hpp>
#include <io/parsing_exceptions.hpp>

#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>
#include <array>

namespace qpp {

  template<class REAL, class CELL>
  void read_vasp_poscar(
      std::basic_istream<CHAR_EX,TRAITS> & inp,
      geometry<REAL,CELL> & geom) {

    STRING_EX poscar_header,
        poscar_header_scale,
        poscar_a,
        poscar_b,
        poscar_c,
        poscar_atypes,
        poscar_acount,
        poscar_coord_type,
        poscar_arecord;

    uint64_t cur_line;

    bool selective_dynamics{false};

    sgetline(inp, poscar_header, cur_line);
    sgetline(inp, poscar_header_scale, cur_line);

    sgetline(inp, poscar_a, cur_line);
    vector3<REAL> va = vec_from_str_ex<REAL>(poscar_a, cur_line);

    sgetline(inp, poscar_b, cur_line);
    vector3<REAL> vb = vec_from_str_ex<REAL>(poscar_b, cur_line);

    sgetline(inp, poscar_c, cur_line);
    vector3<REAL> vc = vec_from_str_ex<REAL>(poscar_c, cur_line);

    sgetline(inp, poscar_atypes, cur_line);
    std::vector<std::string_view> atypes_l = split_sv(poscar_atypes, " ");
    int atypes_c = atypes_l.size();
    check_min_split_size(atypes_l, 1, cur_line, poscar_atypes);

    sgetline(inp, poscar_acount, cur_line);
    std::vector<std::string_view> acount_l = split_sv(poscar_acount, " ");
    check_min_split_size(acount_l, 1, cur_line, poscar_acount);
    std::vector<int> acount_v;
    acount_v.resize(acount_l.size());

    for (int i = 0; i < acount_l.size(); i++)
      acount_v[i] = str2int(acount_l, i, cur_line, poscar_acount);

    sgetline(inp, poscar_coord_type, cur_line);
    STRING_EX poscar_coord_type_t = tolower(poscar_coord_type);
    if (poscar_coord_type_t.find("selective") != std::string::npos) {
        selective_dynamics = true;
        sgetline(inp, poscar_coord_type, cur_line);
        poscar_coord_type_t = tolower(poscar_coord_type);
      }

    //Construct cell
    geom.cell.v[0] = va;
    geom.cell.v[1] = vb;
    geom.cell.v[2] = vc;

    for (int i = 0; i < atypes_c; i++) {

        //get current atom type`s count
        int cur_atom_count = acount_v[i];

        for (int q = 0; q < cur_atom_count; q++) {
            sgetline(inp, poscar_arecord, cur_line);

            if (poscar_coord_type_t.find("cart") != std::string::npos) {
                vector3<REAL> pos_cart = vec_from_str_ex<REAL>(poscar_arecord,
                                                               cur_line);
                geom.add(std::string(atypes_l[i]), pos_cart);
              }

            if ((poscar_coord_type_t.find("frac") != std::string::npos) ||
                (poscar_coord_type_t.find("direct") != std::string::npos)) {
                vector3<REAL> pos_frac = vec_from_str_ex<REAL>(poscar_arecord,
                                                               cur_line);
                qpp::vector3<REAL> vpos =
                    va * pos_frac[0] + vb * pos_frac[1] + vc * pos_frac[2];
                geom.add(std::string(atypes_l[i]), vpos);
              }

          }

      }

    if (geom.nat() == 0)
      throw parsing_error_t(cur_line, poscar_arecord, "Invalid POSCAR file");

  }

  ///
  template<class REAL, class CELL>
  void read_vasp_outcar_md_with_frames(
      std::basic_istream<CHAR_EX,TRAITS> & inp,
      geometry<REAL, CELL> &geom,
      std::vector<geom_anim_record_t<REAL> > &anim
      /*std::vector<std::vector<qpp::vector3<REAL> > > &vel_list,
                      std::vector<REAL> &toten,
                      std::vector<REAL> &temperature*/) {

    STRING_EX inps;

    bool state_atom_types_filled{false};
    bool state_atom_num_filled{false};
    bool state_first_cell_parsed{false};
    bool state_parse_geom_data{false};
    bool state_ibrion_parsed{false};
    bool state_parse_init_geom{false};
    bool init_geom_parsed{false};

    std::vector<STRING_EX> atom_types;
    std::vector<size_t> atom_count;
    std::vector<std::array<qpp::vector3<REAL>, 3 > > cells;

    geom_anim_record_t<REAL> anim_static;
    anim_static.m_anim_type = geom_anim_t::anim_static;
    anim_static.m_anim_name = "static";
    anim_static.frames.resize(1);

    geom_anim_record_t<REAL> anim_md;

    int total_frames = 0;
    int local_atom_count = 0;
    int local_atom_count_init_geom = 0;

    std::vector<int> atom_lookup_v;

    while(std::getline(inp, inps)) {

        bool state_line_checked = false;

        if (!state_ibrion_parsed &&
            !state_line_checked &&
            inps.find("IBRION") != std::string::npos) {

            std::string_view ibrion_line(inps);
            std::vector<std::string_view> ibrion_splt = split_sv(inps, " ");
            uint8_t ibrion = std::atoi(ibrion_splt[2].data());

            if (ibrion == 0) {
                anim_md.m_anim_name = "vasp_md";
                anim_md.m_anim_type = geom_anim_t::anim_md;
              } else {
                anim_md.m_anim_name = "vasp_relax";
                anim_md.m_anim_type = geom_anim_t::anim_geo_opt;
              }

            state_ibrion_parsed = true;
            state_line_checked = true;

          }

        if (!state_atom_types_filled &&
            !state_line_checked &&
            inps.find("VRHFIN") != std::string::npos) {

            std::string_view atypes_l(inps);
            auto start_name = atypes_l.find("=") + 1;
            auto end_name = atypes_l.find(":");
            std::string_view at_name_sv = atypes_l.substr(start_name , end_name - start_name );
            std::string at_name(at_name_sv);
            at_name.erase(std::remove(at_name.begin(), at_name.end(), ' '), at_name.end());
            atom_types.push_back(at_name);
            state_line_checked = true;

          }

        if (!state_atom_num_filled &&
            !state_line_checked &&
            inps.find("ions per type") != std::string::npos) {

            state_atom_types_filled = true;
            std::vector<std::string_view> acount_l = split_sv(inps, " ");

            for (size_t i = 4; i < acount_l.size(); i++){
                size_t _atc = std::stoul(acount_l[i].data());
                atom_count.push_back(_atc);
              }

            state_atom_num_filled = true;
            state_line_checked = true;

            //build atom lookup table
            for(size_t at_c = 0; at_c < atom_types.size(); at_c++)
              for(size_t ac_c = 0; ac_c < atom_count[at_c]; ac_c++)
                atom_lookup_v.push_back(at_c);

          }

        if (!state_line_checked && inps.find("direct lattice vectors") != std::string::npos) {

            std::array<qpp::vector3<REAL>, 3 > _cell;

            for(int i = 0; i < 3; i++){

                std::getline(inp, inps);
                std::vector<std::string_view> splt = split_sv(inps, " ");
                _cell[i][0] = std::stof(splt[0].data());
                _cell[i][1] = std::stof(splt[1].data());
                _cell[i][2] = std::stof(splt[2].data());

              }

            if (state_first_cell_parsed) cells.push_back(_cell);
            else state_first_cell_parsed = true;
            state_line_checked = true;

          }

        if (!state_parse_init_geom &&
            !state_line_checked &&
            inps.find("position of ions in cartesian coordinates  (Angs") != std::string::npos) {
              state_parse_init_geom = true;
              state_line_checked = true;
              init_geom_parsed = true;
            }

        if (!state_parse_geom_data &&
            !state_line_checked &&
            inps.find("POSITION") != std::string::npos) {

            std::getline(inp, inps);
            local_atom_count = 0;

            //              qpp::periodic_cell<REAL> cell(cells[total_frames-1][0],
            //                  cells[total_frames-1][1],
            //                  cells[total_frames-1][2]);

            anim_md.frames.resize(anim_md.frames.size()+1);
            anim_md.frames[anim_md.frames.size()-1].atom_pos.reserve(atom_lookup_v.size());
            total_frames += 1;

            state_parse_geom_data = true;
            state_line_checked = true;

          }

        //parse step data
        if (state_parse_geom_data && !state_line_checked) {

            std::vector<std::string_view> splt = split_sv(inps, " ");

            if (inps.find("------------------------") == std::string::npos
                && (splt.size() == 3 || splt.size() == 6)) {

                qpp::vector3<REAL> pos{std::stof(splt[0].data()),
                      std::stof(splt[1].data()),
                      std::stof(splt[2].data())};
                anim_md.frames[anim_md.frames.size()-1].atom_pos.push_back(std::move(pos));
                local_atom_count += 1;

              } else {

                state_parse_geom_data = false;

              }

            state_line_checked = true;

          }

        //parse init geom data
        if (state_parse_init_geom && !state_line_checked) {

            std::vector<std::string_view> splt = split_sv(inps, " ");

            if (splt.size() == 3) {

                qpp::vector3<REAL> pos{std::stof(splt[0].data()),
                      std::stof(splt[1].data()),
                      std::stof(splt[2].data())};
                anim_static.frames[anim_static.frames.size()-1].atom_pos.push_back(std::move(pos));
                local_atom_count_init_geom += 1;

              } else {

                state_parse_init_geom = false;

              }

            state_line_checked = true;

          }

        //        if (inps.find("total energy   ETOTAL =") != std::string::npos && !state_line_checked){
        //            std::vector<STRING> etotal = split(inps);
        //            REAL etotal_val = 0.0;
        //            state_line_checked = true;
        //          }

        //        if (inps.find("kin. lattice  EKIN_LAT=") != std::string::npos && !state_line_checked){
        //            std::vector<STRING> temp_l = split(inps);
        //            REAL temp_val = 0.0;
        //            state_line_checked = true;
        //          }

      } //end while

    //loadout first frame into geometry
    geom.DIM = 3;

    for (size_t i = 0; i < atom_lookup_v.size(); i++) {

        if (init_geom_parsed) {
            geom.add(atom_types[atom_lookup_v[i]], anim_static.frames[0].atom_pos[i]);
          } else {
            geom.add(atom_types[atom_lookup_v[i]], anim_md.frames[0].atom_pos[i]);
            anim_static.frames[0].atom_pos.push_back(anim_md.frames[0].atom_pos[i]);
          }

      }

    geom.cell.v[0] = cells[0][0];
    geom.cell.v[1] = cells[0][1];
    geom.cell.v[2] = cells[0][2];

    //postproces animation to fight with riot atoms
    for (size_t i = 1; i < anim_md.frames.size(); i++) {
        for (size_t ac = 0; ac < geom.nat(); ac++) {

            //index min_dist_index = index::D(geom.DIM).all(0);
            float min_dist = 100.0f;
            vector3<REAL> goal_vector = anim_md.frames[i].atom_pos[ac];
            for (iterator idx(index::D(geom.DIM).all(-1),
                              index::D(geom.DIM).all(1)); !idx.end(); idx++ ) {
                vector3<REAL> t_pos_cf = geom.cell.transform(
                                           anim_md.frames[i].atom_pos[ac], idx);
                REAL dist = (anim_md.frames[i-1].atom_pos[ac] - t_pos_cf).norm();
                if (dist < min_dist) {
                    min_dist = dist;
                    //min_dist_index = i;
                    goal_vector = t_pos_cf;
                  }
              }
            anim_md.frames[i].atom_pos[ac] = std::move(goal_vector);
          }

      }

    anim.push_back(std::move(anim_static));
    anim.push_back(std::move(anim_md));

  }

  template< class REAL, class CELL >
  void write_vasp_poscar(std::basic_ostream<CHAR_EX,TRAITS>  & out,
                         qpp::geometry<REAL,CELL> & geom) {

    STRING_EX poscar_comment = "";

    for (int i = 0; i < geom.n_types(); i++)
      poscar_comment += geom.atom_of_type(i) + (i == geom.n_types() - 1 ? "" : " ");
    fmt::print(out, "{}\n", poscar_comment);
    fmt::print(out, "1.00000000\n");

    for (int i = 0; i < 3; i++)
      fmt::print(out,
                 "{:15.8f} {:15.8f} {:15.8f}\n",
                 geom.cell.v[i][0],
                 geom.cell.v[i][1],
                 geom.cell.v[i][2]);

    fmt::print(out, "{}\n", poscar_comment);

    for (int i = 0; i < geom.n_types(); i++)
      fmt::print(out, i == geom.n_types() - 1 ? "{}" : "{} ", geom.get_atom_count_by_type(i));

    fmt::print(out, "\n");
    fmt::print(out, "cartesian\n");

    for (int i = 0; i < geom.n_types(); i++)
      for (int q = 0; q < geom.nat(); q++)
        if (geom.type_table(q) == i)
          fmt::print(out,
                     "{:15.8f} {:15.8f} {:15.8f}\n",
                     geom.pos(q)[0],
                     geom.pos(q)[1],
                     geom.pos(q)[2]);

  }

}

#endif
