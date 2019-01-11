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
#include <consts.hpp>
#include <unsupported/Eigen/CXX11/Tensor>
#include <data/ptable.hpp>

namespace qpp {

  template<class REAL>
  struct cube_header_t {
      std::array<vector3<REAL>,3> axis;
      std::array<uint16_t, 3> steps;
      uint16_t tot_atoms;
  };

  template<class REAL>
  const REAL get_field_value_at(const uint32_t ix,
                                const uint32_t iy,
                                const uint32_t iz,
                                cube_header_t<REAL> &cube_header,
                                std::vector<REAL> &field) {
    //return field[ix * ix_size * iy_size + iy_size * iy + iz];
    return field[iz + cube_header.steps[2] *( iy +  cube_header.steps[1] * ix )];
  }

  template<class REAL, class CELL>
  void read_cube(std::basic_istream<CHAR,TRAITS> & inp,
                 geometry<REAL, CELL> &geom,
                 cube_header_t<REAL> &cube_header,
                 std::vector<REAL> &field) {
    std::string s;

    //comment line 1
    std::getline(inp, s);
    std::string c1 = s;

    //comment line 2
    std::getline(inp, s);
    std::string c2 = s;

    for (uint8_t i = 0; i < 4; i++) {
        std::string _s;
        std::getline(inp, _s);
        std::vector<std::string> lsp = split(_s);

        int num_voxels = 0;
        s2t((lsp[0].data()), num_voxels);

        REAL vx = 0.0f;
        REAL vy = 0.0f;
        REAL vz = 0.0f;
        s2t(lsp[1].data(), vx);
        s2t(lsp[2].data(), vy);
        s2t(lsp[3].data(), vz);

        if (i == 0) {
            cube_header.tot_atoms = num_voxels;
          } else {
            cube_header.steps[i-1] = num_voxels;
            cube_header.axis[i-1] =
                vector3<REAL>(vx * bohr_to_angs, vy * bohr_to_angs, vz * bohr_to_angs);
          }
      }

    if (cube_header.tot_atoms > 0)
      for (uint16_t i = 0; i < cube_header.tot_atoms; i++) {
          std::string _s;
          std::getline(inp, _s);
          std::vector<std::string> lsp = split(_s);

          int at_num = 0;
          s2t((lsp[0].data()), at_num);

          REAL vx = 0.0f;
          REAL vy = 0.0f;
          REAL vz = 0.0f;
          s2t(lsp[2].data(), vx);
          s2t(lsp[3].data(), vy);
          s2t(lsp[4].data(), vz);

          std::string at_name = ptable::get_inst()->symbol_by_number(at_num);
          geom.add(at_name, vector3<REAL>(vx * bohr_to_angs, vy * bohr_to_angs, vz * bohr_to_angs));
        }

    uint32_t total_step = std::accumulate(cube_header.steps.begin(), cube_header.steps.end(), 0);

    std::vector<std::string> lsp;

    field.reserve(total_step);
    REAL v0;
    while(std::getline(inp, s)) {
        lsp = split(s);
        for(auto &elem : lsp) {
            v0 = std::stod(elem.data());
            field.push_back(v0);
          }
      }

  }
}

#endif
