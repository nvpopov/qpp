#ifndef QPP_VASP_IO_NATIVE
#define QPP_VASP_IO_NATIVE
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>

#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>

namespace qpp{

  template<class REAL, class CELL>
  void read_vasp_poscar(
      std::basic_istream<CHAR,TRAITS> & inp,
      geometry<REAL,CELL> & geom){

    STRING poscar_header,
        poscar_header_scale,
        poscar_a,
        poscar_b,
        poscar_c,
        poscar_atypes,
        poscar_acount,
        poscar_coord_type,
        poscar_arecord;

    std::getline(inp, poscar_header);
    std::getline(inp, poscar_header_scale);
    std::getline(inp, poscar_a);
    std::getline(inp, poscar_b);
    std::getline(inp, poscar_c);
    std::getline(inp, poscar_atypes);
    std::getline(inp, poscar_acount);
    std::getline(inp, poscar_coord_type);
    STRING poscar_coord_type_t = tolower(poscar_coord_type);

    //Construct cell
    qpp::vector3<REAL> va = vec_from_string<REAL>(poscar_a);
    qpp::vector3<REAL> vb = vec_from_string<REAL>(poscar_b);
    qpp::vector3<REAL> vc = vec_from_string<REAL>(poscar_c);
    geom.cell.v[0] = va;
    geom.cell.v[1] = vb;
    geom.cell.v[2] = vc;

    //Construct atom types
    std::vector<STRING> atypes_l = split(poscar_atypes);
    int atypes_c = atypes_l.size();
    std::vector<STRING> acount_l = split(poscar_acount);

    for (int i = 0; i < atypes_c; i++){
        //get current atom type`s count
        int cur_atom_count ;
        s2t(acount_l[i], cur_atom_count);
        for (int q = 0; q < cur_atom_count; q++){
            std::getline(inp, poscar_arecord);

            if (poscar_coord_type_t.find("cart") != std::string::npos)
              geom.add(atypes_l[i], vec_from_string<REAL>(poscar_arecord));

            if ((poscar_coord_type_t.find("frac") != std::string::npos) ||
                (poscar_coord_type_t.find("direct") != std::string::npos)){
                qpp::vector3<REAL> cv =
                    vec_from_string<REAL>(poscar_arecord);
                qpp::vector3<REAL> vpos =
                    va * cv[0] + vb * cv[1] + vc * cv[2];
                geom.add(atypes_l[i], vpos);
              }
          }
      }
  }

  //md means vector of geometries and velocities
  template<class REAL, class CELL>
  void read_vasp_outcar_md(
      std::basic_istream<CHAR,TRAITS> & inp,
      std::vector<geometry<REAL,CELL>* > &geom_list,
      std::vector<std::vector<qpp::vector3<REAL> > > &vel_list,
      std::vector<REAL> &toten,
      std::vector<REAL> &temperature){

    STRING inps;

    bool bAtomTypesFilled = false;
    bool bAtomNumFilled = false;
    bool bFirstCellParsed = false;
    bool bParseGeomData = false;

    std::vector<STRING> atom_types;
    std::vector<int> atom_count;
    std::vector<std::array<qpp::vector3<REAL>, 3 > > cells;

    int total_frames = 0;
    int local_atom_count = 0;
    std::vector<int> atom_lookup_v;

    while(std::getline(inp, inps)){
        bool bLineChecked = false;

        if (!bAtomTypesFilled && !bLineChecked)
          if (inps.find("POSCAR") != std::string::npos){
              std::vector<STRING> atypes_l = split(inps);
              bAtomTypesFilled = true;
              bLineChecked = true;
              for (int i = 1; i < atypes_l.size(); i++)
                atom_types.push_back(atypes_l[i]);
            }

        if (!bAtomNumFilled  && !bLineChecked)
          if (inps.find("ions per type") != std::string::npos){
              std::vector<STRING> acount_l = split(inps);
              for (int i = 4; i < acount_l.size(); i++){
                  int _atc = 0;
                  s2t(acount_l[i], _atc);
                  atom_count.push_back(_atc);
                }
              bAtomNumFilled = true;
              bLineChecked = true;

              //build atom lookup table
              for(int at_c = 0; at_c < atom_types.size(); at_c++)
                for(int ac_c = 0; ac_c< atom_count[at_c]; ac_c++)
                  atom_lookup_v.push_back(at_c);
            }

        if (!bLineChecked &&
            (inps.find("direct lattice vectors") != std::string::npos)){
            std::array<qpp::vector3<REAL>, 3 > _cell;
            for(int i = 0; i < 3; i++){
                std::getline(inp, inps);
                _cell[i] = vec_from_string<REAL>(inps);
              }
            if (bFirstCellParsed) cells.push_back(_cell);
            else bFirstCellParsed = true;
            bLineChecked = true;
          }

        if (!bParseGeomData && !bLineChecked)
          if (inps.find("POSITION") != std::string::npos){

              std::getline(inp, inps);

              local_atom_count = 0;

              qpp::periodic_cell<REAL> cell(cells[total_frames-1][0],
                  cells[total_frames-1][1],
                  cells[total_frames-1][2]);

              geom_list.push_back(new qpp::geometry<REAL,decltype(cell)>(cell));
              vel_list.resize(vel_list.size()+1);
              total_frames += 1;

              bParseGeomData = true;
              bLineChecked = true;
            }

        if (bParseGeomData && !bLineChecked){
            if (inps.find("------------------------") == std::string::npos){
                qpp::vector3<REAL> pos = vec_from_string<REAL>(inps);
                qpp::vector3<REAL> vel = vec_from_string<REAL>(inps, 3, 4, 5);
                geom_list[total_frames-1]->
                    add(atom_types[atom_lookup_v[local_atom_count]],
                    pos);
                vel_list[vel_list.size()-1].push_back(vel);
                local_atom_count += 1;
              }
            else bParseGeomData = false;
            bLineChecked = true;
          }

        if ((inps.find("total energy   ETOTAL =") != std::string::npos) &&
            !bLineChecked){
            std::vector<STRING> etotal = split(inps);
            REAL etotal_val = 0.0;
            //std::cout<<etotal[4]<<std::endl;
            if (s2t(etotal[4], etotal_val))
              toten.push_back(etotal_val);
            bLineChecked = true;
          }

        if ((inps.find("kin. lattice  EKIN_LAT=") != std::string::npos) &&
            !bLineChecked){
            std::vector<STRING> temp_l = split(inps);
            REAL temp_val = 0.0;
            if (s2t(temp_l[5], temp_val))
              temperature.push_back(temp_val);
            bLineChecked = true;
          }

      }//end while

  }

  template<class REAL, class CELL>
  void read_vasp_outcar_md_with_frames(
      std::basic_istream<CHAR,TRAITS> & inp,
      geometry<REAL, CELL> &geom,
      std::vector<std::vector<vector3<REAL> > > &frames,
      std::vector<std::vector<qpp::vector3<REAL> > > &vel_list,
      std::vector<REAL> &toten,
      std::vector<REAL> &temperature){

    STRING inps;

    bool bAtomTypesFilled = false;
    bool bAtomNumFilled = false;
    bool bFirstCellParsed = false;
    bool bParseGeomData = false;

    std::vector<STRING> atom_types;
    std::vector<int> atom_count;
    std::vector<std::array<qpp::vector3<REAL>, 3 > > cells;

    int total_frames = 0;
    int local_atom_count = 0;
    std::vector<int> atom_lookup_v;

    while(std::getline(inp, inps)){
        bool bLineChecked = false;

        if (!bAtomTypesFilled && !bLineChecked)
          if (inps.find("POSCAR") != std::string::npos){
              std::vector<STRING> atypes_l = split(inps);
              bAtomTypesFilled = true;
              bLineChecked = true;
              for (int i = 1; i < atypes_l.size(); i++)
                atom_types.push_back(atypes_l[i]);
            }

        if (!bAtomNumFilled  && !bLineChecked)
          if (inps.find("ions per type") != std::string::npos){
              std::vector<STRING> acount_l = split(inps);
              for (int i = 4; i < acount_l.size(); i++){
                  int _atc = 0;
                  s2t(acount_l[i], _atc);
                  atom_count.push_back(_atc);
                }
              bAtomNumFilled = true;
              bLineChecked = true;

              //build atom lookup table
              for(int at_c = 0; at_c < atom_types.size(); at_c++)
                for(int ac_c = 0; ac_c< atom_count[at_c]; ac_c++)
                  atom_lookup_v.push_back(at_c);
            }

        if (!bLineChecked &&
            (inps.find("direct lattice vectors") != std::string::npos)){
            std::array<qpp::vector3<REAL>, 3 > _cell;
            for(int i = 0; i < 3; i++){
                std::getline(inp, inps);
                _cell[i] = vec_from_string<REAL>(inps);
              }
            if (bFirstCellParsed) cells.push_back(_cell);
            else bFirstCellParsed = true;
            bLineChecked = true;
          }

        if (!bParseGeomData && !bLineChecked)
          if (inps.find("POSITION") != std::string::npos){

              std::getline(inp, inps);
              local_atom_count = 0;

              qpp::periodic_cell<REAL> cell(cells[total_frames-1][0],
                  cells[total_frames-1][1],
                  cells[total_frames-1][2]);

              //geom_list.push_back(new qpp::geometry<REAL,decltype(cell)>(cell));
              frames.resize(frames.size()+1);
              vel_list.resize(vel_list.size()+1);
              total_frames += 1;

              bParseGeomData = true;
              bLineChecked = true;
            }

        if (bParseGeomData && !bLineChecked){
            if (inps.find("------------------------") == std::string::npos){
                qpp::vector3<REAL> pos = vec_from_string<REAL>(inps);
                qpp::vector3<REAL> vel = vec_from_string<REAL>(inps, 3, 4, 5);
                //geom_list[total_frames-1]->add(atom_types[atom_lookup_v[local_atom_count]],pos);
                frames[frames.size()-1].push_back(pos);
                vel_list[vel_list.size()-1].push_back(vel);
                local_atom_count += 1;
              }
            else bParseGeomData = false;
            bLineChecked = true;
          }

        if (inps.find("total energy   ETOTAL =") != std::string::npos && !bLineChecked){
            std::vector<STRING> etotal = split(inps);
            REAL etotal_val = 0.0;
            //std::cout<<etotal[4]<<std::endl;
            if (s2t(etotal[4], etotal_val))
              toten.push_back(etotal_val);
            bLineChecked = true;
          }

        if (inps.find("kin. lattice  EKIN_LAT=") != std::string::npos && !bLineChecked){
            std::vector<STRING> temp_l = split(inps);
            REAL temp_val = 0.0;
            if (s2t(temp_l[5], temp_val))
              temperature.push_back(temp_val);
            bLineChecked = true;
          }

      }//end while

    //loadout first frame into geometry
    geom.DIM = 3;

    for (uint i = 0; i < atom_lookup_v.size(); i++){
        geom.add(atom_types[atom_lookup_v[i]], frames[0][i]);
      }

  }

  template< class REAL, class CELL >
  void write_vasp_poscar(std::basic_ostream<CHAR,TRAITS>  & out, qpp::geometry<REAL,CELL> & geom){

    STRING poscar_comment = "";

    for (int i = 0; i < geom.n_types(); i++)
      poscar_comment += geom.atom_of_type(i) + " ";
    out << poscar_comment << std::endl;
    out << "1.00000000" << std::endl;

    for (int i = 0; i < 3; i++)
      out << fmt::format("{:15.8f} {:15.8f} {:15.8f}",
          geom.cell.v[i][0],
          geom.cell.v[i][1],
          geom.cell.v[i][2]) << std::endl;
    out << poscar_comment << std::endl;
    for (int i = 0; i < geom.n_types(); i++)
      out << geom.get_atom_count_by_type(i) << " ";
    out << std::endl;
    out << "cartesian" << std::endl;

    for (int i = 0; i < geom.n_types(); i++)
      for (int q = 0; q < geom.nat(); q++)
        if (geom.type_table(q) == i)
          std::cout << fmt::format("{:15.8f} {:15.8f} {:15.8f}",
               geom.pos(q)[0],
               geom.pos(q)[1],
               geom.pos(q)[2]) << std::endl;
  }
}
#endif
