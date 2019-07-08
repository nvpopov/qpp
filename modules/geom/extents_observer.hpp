#ifndef QPP_EXTENTS_OBS_H
#define QPP_EXTENTS_OBS_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
//#include <pybind11/stl.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

#include <typeinfo>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <geom/geom.hpp>
#include <geom/aabb.hpp>
#include <string>

namespace qpp {

  template <class REAL, class CELL = periodic_cell<REAL> >
  class extents_observer_t : public geometry_observer<REAL> {
    public:

      aabb_3d_t<REAL> aabb;
      geometry<REAL, CELL> * geom;
      bool first_data;

      extents_observer_t( geometry<REAL, CELL> & g) {
        geom = &g;
        geom->add_observer(*this);
        first_data = true;
        aabb.max = vector3<REAL>(0.0, 0.0, 0.0);
        aabb.min = vector3<REAL>(0.0, 0.0, 0.0);
      }

      void cmp_pos(const vector3<REAL> &pos_cmp_val) {
        if (first_data){
            aabb.max = pos_cmp_val;
            aabb.min = pos_cmp_val;
            first_data = false;
          }
        else {
            if (pos_cmp_val(0) >= aabb.max(0)) aabb.max[0] = pos_cmp_val(0);
            if (pos_cmp_val(1) >= aabb.max(1)) aabb.max[1] = pos_cmp_val(1);
            if (pos_cmp_val(2) >= aabb.max(2)) aabb.max[2] = pos_cmp_val(2);

            if (pos_cmp_val(0) < aabb.min(0)) aabb.min[0] = pos_cmp_val(0);
            if (pos_cmp_val(1) < aabb.min(1)) aabb.min[1] = pos_cmp_val(1);
            if (pos_cmp_val(2) < aabb.min(2)) aabb.min[2] = pos_cmp_val(2);
          }
      }

      void added( before_after st,
                  const STRING_EX & a,
                  const vector3<REAL> & r) override { cmp_pos(r); }

      void inserted(int at,
                    before_after st,
                    const STRING_EX & a,
                    const vector3<REAL> & r) override { cmp_pos(r); }

      void changed(int at,
                   before_after st,
                   const STRING_EX & a,
                   const vector3<REAL> & r) override { cmp_pos(r); }

      void erased(int at,
                  before_after st) override {}

      void shaded(int at,
                  before_after st,
                  bool sh) override { }

      void reordered(const std::vector<int> &,
                     before_after) override { }

  };

} // namespace qpp

#endif
