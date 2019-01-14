#include <pyqpp/pyqpp.hpp>
#include <symm/autosymm.hpp>
#include <symm/shoenflis.hpp>
#include <symm/point_groups.hpp>
#include <symm/permut.hpp>

template<class REAL>
void def_autosymm (py::module m, const char * pyname) {

  m.def("best_transform", &qpp::py_best_transform<REAL>);
  m.def("best_axes", &qpp::best_axes<REAL>);
  m.def("unitarize", &qpp::unitarize<REAL>);
  //m.def("rotate_transform", &qpp::rotate_pair<REAL>);
  m.def("analyze_transform", &qpp::py_analyze_transform<REAL>);
  m.def("find_point_symm", &qpp::find_point_symm<REAL>);
  m.def("bravais_point_group", &qpp::bravais_point_group<REAL>);
  m.def("bravais_point_group1", &qpp::bravais_point_group1<REAL>);
  m.def("find_cryst_symm", &qpp::py_find_cryst_symm2<REAL>);
  m.def("find_cryst_symm", &qpp::py_find_cryst_symm1<REAL>);
  m.def("find_point_subgroups", &qpp::py_find_point_subgroups1<REAL,true>);
  m.def("find_point_subgroups", &qpp::py_find_point_subgroups1<REAL,false>);
  m.def("find_point_subgroups", &qpp::py_find_point_subgroups2<REAL,true>);
  m.def("find_point_subgroups", &qpp::py_find_point_subgroups2<REAL,false>);
  m.def("find_translations", &qpp::py_find_translations<REAL>);
  //m.def("finitize_point_group", &qpp::finitize_point_group<REAL>);
  m.def("fix_point_group", &qpp::py_fix_point_group<REAL>);
  m.def("complete_point_group", &qpp::complete_point_group<REAL>);
  py::class_<qpp::shnfl<REAL> >(m, pyname)
    .def("Cs",  & qpp::shnfl<REAL>::Cs )
    .def("Ci",  & qpp::shnfl<REAL>::Ci )
    .def("Cn",  & qpp::shnfl<REAL>::Cn )
    .def("Cnv", & qpp::shnfl<REAL>::Cnv )
    .def("Cnh", & qpp::shnfl<REAL>::Cnh )
    .def("Dn",  & qpp::shnfl<REAL>::Dn )
    .def("Dnh", & qpp::shnfl<REAL>::Dnh )
    .def("Dnd", & qpp::shnfl<REAL>::Dnd )
    .def("S2n", & qpp::shnfl<REAL>::S2n )
    .def("T",   & qpp::shnfl<REAL>::T )
    .def("Td",  & qpp::shnfl<REAL>::Td )
    .def("Th",  & qpp::shnfl<REAL>::Th )
    .def("O",   & qpp::shnfl<REAL>::O )
    .def("Oh",  & qpp::shnfl<REAL>::Oh )
    .def("I",   & qpp::shnfl<REAL>::I )
    .def("Ih",  & qpp::shnfl<REAL>::Ih )
    .def("group", & qpp::shnfl<REAL>::group )
    .def("groups_by_order", & qpp::shnfl<REAL>::groups_by_order );
  std::string fpname = fmt::format("{0}_{1}",pyname,"fingerprint");
  qpp::shnfl<REAL>::fingerprint::py_export(m,fpname.c_str());

  m.def("pg_approx_find",   &qpp::pg_approx_find<REAL>);
  m.def("pg_approx_mutab",  &qpp::pg_approx_multab<REAL>);
  m.def("pg_max_order",     &qpp::pg_max_order<REAL>,
	py::arg("G"), py::arg("angle_error") = 8*qpp::matrix3<REAL>::tol_equiv);
}

void pyqpp_autosymm_export (py::module m) {

  def_autosymm<float>(m, "shnfl_f");

#ifdef PYTHON_EXP_EXT
  def_autosymm<double>(m, "shnfl_d");
#endif

  qpp::permutation::py_export(m);

}
