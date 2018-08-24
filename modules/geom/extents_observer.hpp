#ifndef QPP_EXTENTS_OBS_H
#define QPP_EXTENTS_OBS_H

#include <typeinfo>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <geom/geom.hpp>
#include <geom/aabb.hpp>
#include <string>

#ifdef PY_EXPORT
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#endif

namespace qpp{

  template <class REAL, class CELL = periodic_cell<REAL> >
  class extents_observer : public geometry_observer<REAL>{
    public:

      aabb_3d<REAL> aabb;
      geometry<REAL, CELL> * geom;
      bool bFirstData;

      extents_observer( geometry<REAL, CELL> & g){
        geom = &g;
        geom->add_observer(*this);
        bFirstData = true;
        aabb.max = vector3<REAL>(0.0, 0.0, 0.0);
        aabb.min = vector3<REAL>(0.0, 0.0, 0.0);
      }

      void cmp_pos(const vector3<REAL> &vPosCm){
        if (bFirstData){
            aabb.max = vPosCm;
            aabb.min = vPosCm;
            bFirstData = false;
          }
        else {
            if ((vPosCm(0) >= aabb.max(0)) &&
                (vPosCm(1) >= aabb.max(1)) &&
                (vPosCm(2) >= aabb.max(2)) ) aabb.max = vPosCm;

            if ((vPosCm(0) <= aabb.min(0)) &&
                (vPosCm(1) <= aabb.min(1)) &&
                (vPosCm(2) <= aabb.min(2)) ) aabb.min = vPosCm;
          }
      }

      void added( before_after st,
                  const STRING & a,
                  const vector3<REAL> & r) override { cmp_pos(r); }

      void inserted(int at,
                    before_after st,
                    const STRING & a,
                    const vector3<REAL> & r) override { cmp_pos(r); }

      void changed(int at,
                   before_after st,
                   const STRING & a,
                   const vector3<REAL> & r) override { cmp_pos(r); }

      void erased(int at,
                  before_after st) override {}

      void shaded(int at,
                  before_after st,
                  bool sh) override { }

      void reordered(const std::vector<int> &,
                     before_after) override { }

  };

}
#endif
