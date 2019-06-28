#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#pragma pop_macro("slots")
namespace py = pybind11;

#include <pyqpp/pyqpp.hpp>
#include <io/comp_chem_data.hpp>
#include <io/ccd_programs.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

using namespace qpp;

template<typename REAL>
void pyqpp_ccd_export_tmpl(py::module m, const char * pyname) {

  py::class_<comp_chem_program_data_t<REAL>, std::shared_ptr<comp_chem_program_data_t<REAL> > >
      py_comp_chem_program_data(m, pyname);

  py_comp_chem_program_data.def_readonly("runtype",
                                         &comp_chem_program_data_t<REAL>::m_run_t);

  py_comp_chem_program_data.def_readonly("program",
                                         &comp_chem_program_data_t<REAL>::m_comp_chem_program);

}

void pyqpp_ccd_export(py::module m) {

  py::enum_<comp_chem_program_e>(m, "comp_chem_program_e", py::arithmetic(), "")
      .value("pr_unknown", pr_unknown, "pr_unknown")
      .value("pr_vasp", pr_vasp, "pr_vasp")
      .value("pr_firefly", pr_firefly, "pr_firefly")
      .value("pr_pc_gamess", pr_pc_gamess, "pr_pc_gamess")
      .value("pr_cp2k", pr_cp2k, "pr_cp2k")
      .value("pr_orca", pr_orca, "pr_orca")
      .value("pr_molcas", pr_molcas, "pr_molcas")
      .value("pr_molden", pr_molden, "pr_molden")
      .export_values();

  py::enum_<comp_chem_program_run_e>(m, "comp_chem_program_run_e", py::arithmetic(), "")
      .value("rt_unknown", rt_unknown, "rt_unknown")
      .value("rt_energy", rt_energy, "rt_energy")
      .value("rt_grad", rt_grad, "rt_grad")
      .value("rt_geo_opt", rt_geo_opt, "rt_geo_opt")
      .value("rt_cell_opt", rt_cell_opt, "rt_cell_opt")
      .value("rt_md", rt_md, "rt_md")
      .value("rt_vib", rt_vib, "rt_vib")
      .value("rt_raman", rt_raman, "rt_raman")
      .value("rt_tddft", rt_tddft, "rt_tddft")
      .value("rt_spectrum", rt_spectrum, "rt_spectrum")
      .export_values();

  pyqpp_ccd_export_tmpl<float>(m, "comp_chem_program_data_f_t");
#ifdef PYTHON_EXP_EXT
  pyqpp_ccd_export_tmpl<double>(m, "comp_chem_program_data_d_t");
#endif

}
