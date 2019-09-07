#ifndef QPP_SCALAR_VOLUME_H
#define QPP_SCALAR_VOLUME_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

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

  template<class REAL>
  struct scalar_volume_t {

      std::array<vector3<REAL>,3> m_axis;
      std::array<uint16_t, 3> m_steps;
      vector3<REAL> m_offset{0, 0, 0};
      uint16_t m_tot_atoms;
      std::vector<REAL> m_field;
      bool m_has_negative_values{false};
      std::string m_name;
      int m_addr_mode{0};

      bool is_structure_equals(scalar_volume_t<REAL> &vol) {

        return m_field.size() == vol.m_field.size() &&
            m_steps[0] == vol.m_steps[0] &&
            m_steps[1] == vol.m_steps[1] &&
            m_steps[2] == vol.m_steps[2] &&
            m_offset == vol.m_offset &&
            m_axis[0] == vol.m_axis[0] &&
            m_axis[1] == vol.m_axis[1] &&
            m_axis[2] == vol.m_axis[2];

      }

  };

  template<class REAL>
  const REAL get_field_value_at(const int ix,
                                const int iy,
                                const int iz,
                                scalar_volume_t<REAL> &volume) {

    if (ix < 0 || iy < 0 || iz < 0 ||
        ix >= volume.m_steps[0] ||
        iy >= volume.m_steps[1] ||
        iz >= volume.m_steps[2]) return 0;
    else return volume.m_field[iz + volume.m_steps[2] * (iy +  volume.m_steps[1] * ix)];

  }

  template<class REAL>
  void set_field_value_at(const int ix,
                          const int iy,
                          const int iz,
                          const REAL new_field_val,
                          scalar_volume_t<REAL> &volume) {

    if (ix < 0 || iy < 0 || iz < 0 ||
        ix >= volume.m_steps[0] ||
        iy >= volume.m_steps[1] ||
        iz >= volume.m_steps[2]) return ;
    else
      volume.m_field[iz + volume.m_steps[2] * (iy +  volume.m_steps[1] * ix)]
          = new_field_val;

  }

  template<class REAL>
  const REAL get_field_value_at_v2(const int ix,
                                   const int iy,
                                   const int iz,
                                   scalar_volume_t<REAL> &volume) {

    if (ix < 0 || iy < 0 || iz < 0 ||
        ix >= volume.m_steps[0] ||
        iy >= volume.m_steps[1] ||
        iz >= volume.m_steps[2]) return 0;
    else return volume.m_field[iz + volume.m_steps[2] * volume.m_steps[1] * ix +
        volume.m_steps[2] * iy ];
  }

}

#endif
