#ifndef QPP_CUBE_H
#define QPP_CUBE_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <geom/geom.hpp>
#include <geom/xgeom.hpp>

#include <assert.h>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>
#include <numeric>
#include <unsupported/Eigen/CXX11/Tensor>
#include <data/ptable.hpp>

namespace qpp {
  template<class REAL>
  const REAL get_field_value_at(const uint32_t ix,
                                const uint32_t iy,
                                const uint32_t iz,
                                const uint32_t ix_size,
                                const uint32_t iy_size,
                                std::vector<REAL> &field){
    return field[ix * ix_size * iy_size + iy_size * iy + iz];
  }

  template<class REAL>
  struct cube_header_t {
      std::array<vector3<REAL>,3> axis;
      std::array<uint16_t, 3> steps;
      uint16_t tot_atoms;
  };

  template<class REAL, class CELL>
  void read_cube(std::basic_istream<CHAR,TRAITS> & inp,
                 geometry<REAL, CELL> &geom,
                 cube_header_t<REAL> &cube_header,
                 std::vector<REAL> &field){
    std::string s;

    //comment line 1
    std::getline(inp, s);
    std::string c1 = s;

    //comment line 2
    std::getline(inp, s);
    std::string c2 = s;

    //        //4 line data
    //        std::vector<int>   f_col;
    //        std::vector<vector3<REAL> > f_sec;

    for (uint8_t i = 0; i < 4; i++){
        std::string _s;
        std::getline(inp, _s);
        std::vector<std::string> lsp = split(_s);

        int num_voxels = 0;
        s2t((lsp[0]), num_voxels);

        REAL vx = 0.0f;
        REAL vy = 0.0f;
        REAL vz = 0.0f;
        s2t(lsp[1], vx);
        s2t(lsp[2], vy);
        s2t(lsp[3], vz);

        //std::cout << fmt::format("{} {} {} {}\n", num_voxels, vx, vy, vz);

        if (i == 0){
            cube_header.tot_atoms = num_voxels;
          } else {
            cube_header.steps[i-1] = num_voxels;
            cube_header.axis[i-1] = vector3<REAL>(vx, vy, vz);
          }
        //                f_col.push_back(num_voxels);
        //                f_sec.push_back(vector3<REAL>(vx, vy, vz));
      }

    if (cube_header.tot_atoms > 0)
      for (uint16_t i = 0; i < cube_header.tot_atoms; i++){
          std::string _s;
          std::getline(inp, _s);
          std::vector<std::string> lsp = split(_s);

          int at_num = 0;
          s2t((lsp[0]), at_num);

          REAL vx = 0.0f;
          REAL vy = 0.0f;
          REAL vz = 0.0f;
          s2t(lsp[2], vx);
          s2t(lsp[3], vy);
          s2t(lsp[4], vz);

          std::string at_name = ptable::get_inst()->symbol_by_number(at_num);
          geom.add(at_name, vector3<REAL>(vx, vy, vz));
        }

    uint32_t total_step = std::accumulate(cube_header.steps.begin(),
                                          cube_header.steps.end(), 0);

    std::vector<std::string> lsp;

    field.reserve(total_step);

    while(std::getline(inp, s)){
        lsp = split(s);
        for(auto &elem : lsp){
            REAL v0 = 0.0f;
            s2t(elem, v0);
            field.push_back(v0);
          }
      }

  }
}

#endif
