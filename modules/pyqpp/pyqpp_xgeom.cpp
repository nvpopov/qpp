#include <pyqpp/pyqpp.hpp>
#include <symm/gen_cell.hpp>
#include <geom/xgeom.hpp>

namespace py = pybind11;

void pyqpp_xgeom_export (pybind11::module m) {

  py::enum_<qpp::basic_types>(m, "basic_types", py::arithmetic(), "basic_types")
          .value("type_int", qpp::basic_types::type_int, "type_int")
          .value("type_real", qpp::basic_types::type_real, "type_real")
          .value("type_double", qpp::basic_types::type_double, "type_double")
          .value("type_float", qpp::basic_types::type_float, "type_float")
          .value("type_bool", qpp::basic_types::type_bool, "type_bool")
          .value("type_string", qpp::basic_types::type_string, "type_string")
          .export_values();

  qpp::xgeometry<float, qpp::periodic_cell<float>>::py_export(m, "xgeometry_f");

  qpp::xgeometry<float, qpp::gen_cell<float,qpp::matrix3<float>>>::py_export(m, "xgeometry_pgf");
  qpp::xgeometry<float, qpp::gen_cell<float,qpp::rotrans<float>>>::py_export(m, "xgeometry_cgf");

#ifdef PYTHON_EXP_EXT
  qpp::xgeometry<double,qpp::periodic_cell<double> >::py_export(m, "xgeometry_d");
  qpp::xgeometry<double,qpp::gen_cell<double,
      qpp::matrix3<double> > >::py_export(m, "xgeometry_pgd");
  qpp::xgeometry<double,qpp::gen_cell<double,
      qpp::rotrans<double>  > >::py_export(m, "xgeometry_cgd");
#endif

}
