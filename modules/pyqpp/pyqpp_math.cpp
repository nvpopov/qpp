#include <pyqpp/pyqpp.hpp>
#include <mathf/specfunc.hpp>


void pyqpp_math_export (py::module m) {

  m.def("Ylm_spherical_f", qpp::py_ylm_spherical<float>);
  m.def("Pl_legendre_f",   qpp::py_pl_legendre<float>);
  
#ifdef PYTHON_EXP_EXT

  m.def("Ylm_spherical_d", qpp::py_ylm_spherical<double>);
  m.def("Pl_legendre_d",   qpp::py_pl_legendre<double>);

#endif
}
