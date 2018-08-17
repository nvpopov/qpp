#ifndef _QPP_EXTENTS_OBS_H
#define _QPP_EXTENTS_OBS_H

#include <typeinfo>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <geom/geom.hpp>
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

    vector3<REAL> max_pos;
    vector3<REAL> min_pos;
    geometry<REAL, CELL> * geom;

    extents_observer( geometry<REAL, CELL> & g){
      geom = &g;
      geom->add_observer(*this);
      max_pos = vector3<REAL>(0.0, 0.0, 0.0);
      min_pos = vector3<REAL>(0.0, 0.0, 0.0);
    }

    void cmp_pos(const vector3<REAL> &vPosCm){
      if ((vPosCm(0) > max_pos(0)) &&
          (vPosCm(1) > max_pos(1)) &&
          (vPosCm(2) > max_pos(2)) ) max_pos = vPosCm;

      if ((vPosCm(0) < min_pos(0)) &&
          (vPosCm(1) < min_pos(1)) &&
          (vPosCm(2) < min_pos(2)) ) min_pos = vPosCm;
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
