#ifndef _QPP_VASP_IO_NATIVE
#define _QPP_VASP_IO_NATIVE
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>

//#include <lace/lace3d.hpp>
//#include <lace/lace.hpp>
//#include <symm/symm.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>
//#include <geom/geom_extras.hpp>
//#include <geom/molecule.hpp>

#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>

namespace qpp{

  template<class REAL>
  qpp::vector3d<REAL> vec_from_string(STRING &_inst){
    std::vector<STRING> vfs_l = split(_inst);
    REAL vx, vy, vz = 0.0;
    s2t(vfs_l[0], vx);
    s2t(vfs_l[1], vy);
    s2t(vfs_l[2], vz);
    return qpp::vector3d<REAL>(vx, vy, vz);
  }

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

    //Construct cell
    qpp::vector3d<REAL> va = vec_from_string<REAL>(poscar_a);
    qpp::vector3d<REAL> vb = vec_from_string<REAL>(poscar_b);
    qpp::vector3d<REAL> vc = vec_from_string<REAL>(poscar_c);
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

            if (poscar_coord_type == "cart")
                geom.add(atypes_l[i], vec_from_string<REAL>(poscar_arecord));

            if (poscar_coord_type == "frac"){
                qpp::vector3d<REAL> cv =
                    vec_from_string<REAL>(poscar_arecord);
                    qpp::vector3d<REAL> vpos =
                        va * cv[0] + vb * cv[1] + vc * cv[2];
                    geom.add(atypes_l[i], vpos);
              }
          }
      }
  }

  template< class REAL, class CELL >
  void write_vasp_poscar(
      std::basic_ostream<CHAR,TRAITS>  & out,
      const qpp::geometry<REAL,CELL> & geom){

  }
}
#endif
