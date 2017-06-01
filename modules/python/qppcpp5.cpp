#define PY_EXPORT

#include "qppcpp.hpp"
#include <geom/ngbr.hpp>

void qpp_export5()
{ 
 
  qpp::bonding_table<float>::py_export("bonding_table_f");
  qpp::bonding_table<double>::py_export("bonding_table_d");

  qpp::neighbours_table<float, qpp::periodic_cell<float> >::py_export("ngbr_table_f");
  qpp::neighbours_table<double, qpp::periodic_cell<double> >::py_export("ngbr_table_d");

}
