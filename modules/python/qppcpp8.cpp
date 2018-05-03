#include "qppcpp.hpp"
#include <symm/autosymm.hpp>

template<class REAL>
void def_autosymm()
{
  def("best_transform", qpp::py_best_transform<REAL>);
  def("rotate_transform", qpp::rotate_pair<REAL>);
  def("analyze_transform", qpp::py_analyze_transform<REAL>);
  def("find_point_symm", qpp::find_point_symm<REAL>);
  def("bravais_point_group", qpp::bravais_point_group<REAL>);
  def("find_cryst_symm", qpp::py_find_cryst_symm1<REAL>);
  def("find_cryst_symm", qpp::py_find_cryst_symm2<REAL>);
  def("find_point_subgroups", qpp::py_find_point_subgroups1<REAL>);
  def("find_point_subgroups", qpp::py_find_point_subgroups2<REAL>);
  def("find_translations", qpp::py_find_translations<REAL>);
}

void qpp_export8()
{
  def_autosymm<float>();
  def_autosymm<double>();
}
