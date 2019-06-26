#ifndef QPP_VASP_CHGCAR
#define QPP_VASP_CHGCAR

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>
#include <geom/geom.hpp>
#include <geom/ngbr.hpp>
#include <geom/geom_anim.hpp>
#include <io/cube.hpp>
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
  void read_vasp_chgcar(std::basic_istream<CHAR_EX,TRAITS> & inp,
                        geometry<REAL, CELL> &geom,
                        std::vector<scalar_volume_t<REAL>> &volumes) {

    STRING_EX poscar_header,
              poscar_header_scale,
              poscar_a,
              poscar_b,
              poscar_c,
              poscar_atypes,
              poscar_acount,
              poscar_coord_type,
              poscar_arecord,
              _str;

    uint64_t cur_line;

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
      throw parsing_error_t(cur_line, poscar_arecord, "Invalid CHGCAR file");

    // read volume data
    REAL cell_volume = ((geom.cell.v[0]).cross(geom.cell.v[1])).dot(geom.cell.v[2]);

    //read empty line
    sgetline(inp, _str, cur_line);

    //read nx ny nz
    sgetline(inp, _str, cur_line);
    std::vector<std::string_view> splt = split_sv(_str, " ");
    check_min_split_size(splt, 3, cur_line, _str);
    size_t nx = str2int(splt, 0, cur_line, _str);
    size_t ny = str2int(splt, 1, cur_line, _str);
    size_t nz = str2int(splt, 2, cur_line, _str);

    volumes.resize(1);
    volumes[0].m_field.resize(nx*ny*nz, 0);
    volumes[0].m_offset = vector3<REAL>{0, 0, 0};
    volumes[0].m_axis[0] = geom.cell.v[0] / nx;
    volumes[0].m_axis[1] = geom.cell.v[1] / ny;
    volumes[0].m_axis[2] = geom.cell.v[2] / nz;
    volumes[0].m_steps[0] = nx;
    volumes[0].m_steps[1] = ny;
    volumes[0].m_steps[2] = nz;
    volumes[0].m_has_negative_values = false;
    volumes[0].m_addr_mode = 0;
    volumes[0].m_name = "chgcar";

    size_t ix = 0;
    size_t iy = 0;
    size_t iz = 0;

    bool exit_fl{false};
    while (!inp.eof() && !exit_fl) {

        sgetline(inp, _str, cur_line);
        splt = split_sv(_str, " ");
        for (size_t i = 0; i < splt.size(); i++) {


            REAL val = str2real<REAL>(splt, i, cur_line, _str) / cell_volume;
            volumes[0].m_field[ix*nz*ny + iy*nz + iz] = val;

            ix++;
//            std::cout << "NXYZ " << ix << " " << iy << " " << iz << " " <<
//                      (ix == nx - 1 && iy == ny - 1 && iz == nz - 1) << std::endl;
            if (ix == nx - 1 && iy == ny - 1 && iz == nz - 1) exit_fl = true;

            if (ix == nx) {
                ix = 0;
                iy++;
              }

            if (iy == ny) {
                iy = 0;
                iz++;
              }

          }

    } // while (!inp.eof())

  } // read_cube

} // namespace qpp

#endif
