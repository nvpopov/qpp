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
  struct scalar_volume_t {
      std::array<vector3<REAL>,3> m_axis;
      std::array<uint16_t, 3> m_steps;
      uint16_t m_tot_atoms;
      std::vector<REAL> m_field;
      bool m_has_negative_values{false};
  };


  template<class REAL>
  const REAL get_field_value_at(const int ix,
                                const int iy,
                                const int iz,
                                scalar_volume_t<REAL> &volume) {
    //return field[ix * ix_size * iy_size + iy_size * iy + iz];
    if (ix < 0 || iy < 0 || iz < 0 ||
        ix >= volume.m_steps[0] ||
        iy >= volume.m_steps[1] ||
        iz >= volume.m_steps[2]) return 0;
    else return volume.m_field[iz + volume.m_steps[2] * (iy +  volume.m_steps[1] * ix)];
  }

  template<class REAL, class CELL>
  void read_cube(std::basic_istream<CHAR,TRAITS> & inp,
                 geometry<REAL, CELL> &geom,
                 scalar_volume_t<REAL> &volume) {
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
            volume.m_tot_atoms = num_voxels;
          } else {
            volume.m_steps[i-1] = num_voxels;
            volume.m_axis[i-1] =
                vector3<REAL>(vx * bohr_to_angs, vy * bohr_to_angs, vz * bohr_to_angs);
          }
      }

    if (volume.m_tot_atoms > 0)
      for (uint16_t i = 0; i < volume.m_tot_atoms; i++) {
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

    uint32_t total_step = std::accumulate(volume.m_steps.begin(), volume.m_steps.end(), 0);

    std::vector<std::string> lsp;

    volume.m_field.reserve(total_step);
    REAL v0;
    while(std::getline(inp, s)) {
        lsp = split(s);
        for(auto &elem : lsp) {
            v0 = std::stod(elem.data());
            if (v0 < -0.01) {
                volume.m_has_negative_values = true;
                //std::cout << "!" << v0 << std::endl;
              }
            volume.m_field.push_back(v0);
          }
      }

  }
}

#endif
