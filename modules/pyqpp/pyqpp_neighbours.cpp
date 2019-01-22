#include <pyqpp/pyqpp.hpp>
#include <geom/ngbr.hpp>
#include <symm/gen_cell.hpp>

void pyqpp_neighbours_export (py::module m) {

  qpp::bonding_table<float>::py_export(m, "bonding_table_f");
  qpp::neighbours_table<float, qpp::periodic_cell<float> >::py_export(m, "ngbr_table_f");
  qpp::neighbours_table<float, qpp::gen_cell<float, qpp::matrix3<float> > >::py_export(m, "ngbr_table_pgf");
  qpp::neighbours_table<float, qpp::gen_cell<float, qpp::rotrans<float> > >::py_export(m, "ngbr_table_cgf");

#ifdef PYTHON_EXP_EXT
  qpp::bonding_table<double>::py_export(m, "bonding_table_d");
  qpp::neighbours_table<double, qpp::periodic_cell<double>>::py_export(m, "ngbr_table_d");
  qpp::neighbours_table<double, qpp::gen_cell<double, qpp::matrix3<double> > >::py_export(m, "ngbr_table_pgd");
  qpp::neighbours_table<double, qpp::gen_cell<double, qpp::rotrans<double> > >::py_export(m, "ngbr_table_cgd");
#endif

}
