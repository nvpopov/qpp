#define PY_EXPORT

#include "qppcpp.hpp"
#include <symm/gcell.hpp>
#include <geom/xgeom.hpp>

void qpp_export4()
{  
  qpp::xgeometry<float, qpp::periodic_cell<float>  >::py_export("xgeometry_f");
  qpp::xgeometry<double,qpp::periodic_cell<double> >::py_export("xgeometry_d");
  qpp::xgeometry<float, qpp::generalized_cell<float,  qpp::matrix3d<float>  > >::py_export("xgeometry_pgf");
  qpp::xgeometry<double,qpp::generalized_cell<double, qpp::matrix3d<double> > >::py_export("xgeometry_pgd");
  qpp::xgeometry<float, qpp::generalized_cell<float,  qpp::rotrans<float>   > >::py_export("xgeometry_cgf");
  qpp::xgeometry<double,qpp::generalized_cell<double, qpp::rotrans<double>  > >::py_export("xgeometry_cgd");

}
