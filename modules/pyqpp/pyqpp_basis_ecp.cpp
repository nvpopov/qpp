#include <pyqpp/pyqpp.hpp>
#include <basis/basis.hpp>
#include <basis/ecp.hpp>

template<qpp::qpp_bastype BT, class REAL>
void py_basis_export (py::module m, const char * pyname) {

  qpp::qpp_shell<BT, REAL>::py_props(m, pyname);
  py::class_<qpp::qpp_shell<BT, REAL> >(m, pyname)
    .def(py::init<int,int,/*optional<*/qpp::qpp_angtype >())
    .def(py::init<const qpp::qpp_shell<BT, REAL> &>())
    //TODO: add __str__
    .def("nprim",    & qpp::qpp_shell<BT,REAL>::nprim)
    .def("nshells",  & qpp::qpp_shell<BT,REAL>::nshells)
    .def_readwrite("label", & qpp::qpp_shell<BT,REAL>::py_label)
    .def_readwrite("l", & qpp::qpp_shell<BT,REAL>::py_l)
    .def_readwrite("alpha", & qpp::qpp_shell<BT,REAL>::py_alpha)
    .def_readwrite("coeff", & qpp::qpp_shell<BT,REAL>::py_coeff)
    ;

}

template <class FREAL>
void py_ecp_export (py::module m, const char * pyname) {

  qpp::atomic_ecp<FREAL>::py_props(m, pyname);
  py::class_<qpp::atomic_ecp<FREAL> >(m, pyname)
    .def(py::init<int>())
    .def(py::init<>())
    .def(py::init<const py::list &>())
    .def("L", &qpp::atomic_ecp<FREAL>::L )
    .def("empty",  &qpp::atomic_ecp<FREAL>::empty)
    .def_readwrite("n", &qpp::atomic_ecp<FREAL>::py_n )
    .def_readwrite("coeff", &qpp::atomic_ecp<FREAL>::py_coeff )
    .def_readwrite("alpha", &qpp::atomic_ecp<FREAL>::py_alpha )
    .def_readwrite("nprim", &qpp::atomic_ecp<FREAL>::py_nprim)
    .def_readwrite("name", &qpp::atomic_ecp<FREAL>::name)
    ;

}

void pyqpp_basis_ecp_export (pybind11::module m) {

  py::enum_<qpp::qpp_angtype>(m, "qpp_angtype", py::arithmetic())
      .value("qang_spherical", qpp::qpp_angtype::qang_spherical)
      .value("qang_cartesian", qpp::qpp_angtype::qang_cartesian);

  py::enum_<qpp::qpp_bastype>(m, "qpp_bastype", py::arithmetic())
      .value("qbas_gauss",  qpp::qpp_bastype::qbas_gauss)
      .value("qbas_slater", qpp::qpp_bastype::qbas_slater)
      .value("qbas_siesta", qpp::qpp_bastype::qbas_siesta)
      .value("qbas_pw",     qpp::qpp_bastype::qbas_pw)
      .value("qbas_none",   qpp::qpp_bastype::qbas_none)
      ;


  py_basis_export<qpp::qbas_gauss,float>(m, "gauss_shell_f");
  py_basis_export<qpp::qbas_slater,float>(m, "slater_shell_f");
  py_ecp_export<float>(m, "ecp_f");
  qpp::atomic_basis<qpp::qbas_gauss,float>::py_export(m, "atomic_basis_gf");

#ifdef PYTHON_EXP_EXT
  py_basis_export<qpp::qbas_gauss,double>(m, "gauss_shell_d");
  py_basis_export<qpp::qbas_slater,double>(m, "slater_shell_d");
  py_ecp_export<double>(m, "ecp_d");
  qpp::atomic_basis<qpp::qbas_gauss,double>::py_export(m, "atomic_basis_gd");
#endif
}
