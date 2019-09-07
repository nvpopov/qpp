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
#include <array>
#include <consts.hpp>
#include <data/scalar_volume.hpp>
#include <data/ptable.hpp>

namespace qpp {

  template<class REAL, class CELL>
  void read_cube(std::basic_istream<CHAR_EX,TRAITS> & inp,
                 geometry<REAL, CELL> &geom,
                 scalar_volume_t<REAL> &volume) {

    std::string s;
    bool has_odd_field{false};

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
            has_odd_field = num_voxels < 0;
            volume.m_tot_atoms = std::abs(num_voxels);
            volume.m_offset[0] = vx * bohr_to_angs;
            volume.m_offset[1] = vy * bohr_to_angs;
            volume.m_offset[2] = vz * bohr_to_angs;
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
          geom.add(at_name,
                   vector3<REAL>(vx * bohr_to_angs, vy * bohr_to_angs, vz * bohr_to_angs));
        }

    //read odd line
    if (has_odd_field) std::getline(inp, s);

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
              }
            volume.m_field.push_back(v0);
          }
      }

  }

} // namespace qpp

#endif
