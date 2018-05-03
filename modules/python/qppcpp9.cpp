#include "qppcpp.hpp"
#include <basis/basis.hpp>
#include <basis/ecp.hpp>

template<qpp::qpp_bastype BT, class REAL>
void py_basis_export(const char * pyname)
{
  qpp::qpp_shell<BT,REAL>::py_props();
  class_<qpp::qpp_shell<BT,REAL> >(pyname, init<int,int,optional<qpp::qpp_angtype> >())
    .def(init<const qpp::qpp_shell<BT,REAL> &>())
    .def("nprim",    & qpp::qpp_shell<BT,REAL>::nprim)
    .def("nshells",  & qpp::qpp_shell<BT,REAL>::nshells)
    .def_readwrite("label", & qpp::qpp_shell<BT,REAL>::py_label)
    .def_readwrite("l", & qpp::qpp_shell<BT,REAL>::py_l)
    .def_readwrite("alpha", & qpp::qpp_shell<BT,REAL>::py_alpha)
    .def_readwrite("coeff", & qpp::qpp_shell<BT,REAL>::py_coeff)
    ;
}

template <class FREAL>
void py_ecp_export(const char * pyname)
{
  qpp::atomic_ecp<FREAL>::py_props();
  class_<qpp::atomic_ecp<FREAL> >(pyname, init<int>())
    .def(init<>())
    .def(init<const list &>())
    .def("L", &qpp::atomic_ecp<FREAL>::L )
    .def("empty",  &qpp::atomic_ecp<FREAL>::empty)
    .def_readwrite("n", &qpp::atomic_ecp<FREAL>::py_n )
    .def_readwrite("coeff", &qpp::atomic_ecp<FREAL>::py_coeff )
    .def_readwrite("alpha", &qpp::atomic_ecp<FREAL>::py_alpha )
    .def_readwrite("nprim", &qpp::atomic_ecp<FREAL>::py_nprim)
    .def_readwrite("name", &qpp::atomic_ecp<FREAL>::name)
    ;
}

void qpp_export9()
{
  py_basis_export<qpp::qbas_gauss,float>("gauss_shell_f");
  py_basis_export<qpp::qbas_gauss,double>("gauss_shell_d");
  py_basis_export<qpp::qbas_slater,float>("slater_shell_f");
  py_basis_export<qpp::qbas_slater,double>("slater_shell_d");
  py_ecp_export<float>("ecp_f");
  py_ecp_export<double>("ecp_d");
  qpp::atomic_basis<qpp::qbas_gauss,float>::py_export("atomic_basis_gf");
  qpp::atomic_basis<qpp::qbas_gauss,double>::py_export("atomic_basis_gd");
}
