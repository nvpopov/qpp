#include <pyqpp/pyqpp.hpp>
#include <geom/ngbr.hpp>

void pyqpp_neighbours_export (py::module m){
  qpp::bonding_table<float>::py_export(m, "bonding_table_f");
  qpp::bonding_table<double>::py_export(m, "bonding_table_d");

  qpp::neighbours_table<float, qpp::periodic_cell<float> >
      ::py_export(m, "ngbr_table_f");
  qpp::neighbours_table<double, qpp::periodic_cell<double>>
      ::py_export(m, "ngbr_table_d");
}
