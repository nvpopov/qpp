#include <pyqpp/pyqpp.hpp>
#include <symm/gcell.hpp>
#include <geom/xgeom.hpp>

void pyqpp_xgeom_export(pybind11::module m){

  qpp::xgeometry<float, qpp::periodic_cell<float>  >
      ::py_export(m, "xgeometry_f");
  qpp::xgeometry<double,qpp::periodic_cell<double> >
      ::py_export(m, "xgeometry_d");

  qpp::xgeometry<float, qpp::generalized_cell<float,
      qpp::matrix3<float>  > >::py_export(m, "xgeometry_pgf");
  qpp::xgeometry<double,qpp::generalized_cell<double,
      qpp::matrix3<double> > >::py_export(m, "xgeometry_pgd");
  qpp::xgeometry<float, qpp::generalized_cell<float,
      qpp::rotrans<float>   > >::py_export(m, "xgeometry_cgf");
  qpp::xgeometry<double,qpp::generalized_cell<double,
      qpp::rotrans<double>  > >::py_export(m, "xgeometry_cgd");

}
