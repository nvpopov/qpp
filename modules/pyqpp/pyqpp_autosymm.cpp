#include <pyqpp/pyqpp.hpp>
#include <symm/autosymm.hpp>

template<class REAL>
void def_autosymm (py::module m) {

  m.def("best_transform", &qpp::py_best_transform<REAL>);
  m.def("rotate_transform", &qpp::rotate_pair<REAL>);
  m.def("analyze_transform", &qpp::py_analyze_transform<REAL>);
  m.def("find_point_symm", &qpp::find_point_symm<REAL>);
  m.def("bravais_point_group", &qpp::bravais_point_group<REAL>);
  m.def("find_cryst_symm", &qpp::py_find_cryst_symm2<REAL>);
  m.def("find_cryst_symm", &qpp::py_find_cryst_symm1<REAL>);
  m.def("find_point_subgroups", &qpp::py_find_point_subgroups1<REAL,true>);
  m.def("find_point_subgroups", &qpp::py_find_point_subgroups1<REAL,false>);
  m.def("find_point_subgroups", &qpp::py_find_point_subgroups2<REAL,true>);
  m.def("find_point_subgroups", &qpp::py_find_point_subgroups2<REAL,false>);
  m.def("find_translations", &qpp::py_find_translations<REAL>);

}

void pyqpp_autosymm_export (py::module m) {

  def_autosymm<float>(m);

#ifdef PYTHON_EXP_EXT
  def_autosymm<double>(m);
#endif

}
