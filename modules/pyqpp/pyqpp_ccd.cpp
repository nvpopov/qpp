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
void pyqpp_ccd_step_export_tmpl(py::module m, const char * pyname) {

  py::class_<comp_chem_program_step_t<REAL>, std::shared_ptr<comp_chem_program_step_t<REAL> > >
      py_ccd_step(m, pyname);

  py_ccd_step.def_readonly("toten", &comp_chem_program_step_t<REAL>::m_toten);

}

template<typename REAL>
void pyqpp_ccd_export_tmpl(py::module m, const char * pyname) {

  py::class_<comp_chem_program_data_t<REAL>, std::shared_ptr<comp_chem_program_data_t<REAL> > >
      py_ccd(m, pyname);

  py_ccd.def_readonly("runtype", &comp_chem_program_data_t<REAL>::m_run_t)
        .def_readonly("program", &comp_chem_program_data_t<REAL>::m_comp_chem_program)
        .def_readonly("is_qmmm", &comp_chem_program_data_t<REAL>::m_is_qmmm)
        .def_readonly("DIM", &comp_chem_program_data_t<REAL>::m_DIM)
        .def_readonly("tot_nat", &comp_chem_program_data_t<REAL>::m_tot_nat)
        .def_readonly("tot_nelec", &comp_chem_program_data_t<REAL>::m_tot_nelec)
        .def_readonly("tot_charge", &comp_chem_program_data_t<REAL>::m_tot_charge)
        .def_readonly("mult", &comp_chem_program_data_t<REAL>::m_mult)
        .def_readonly("is_unrestricted", &comp_chem_program_data_t<REAL>::m_is_unrestricted)
        .def_readonly("n_alpha", &comp_chem_program_data_t<REAL>::m_n_alpha)
        .def_readonly("n_beta", &comp_chem_program_data_t<REAL>::m_n_beta)
        .def_readonly("n_spin_states", &comp_chem_program_data_t<REAL>::m_n_spin_states)
        .def_readonly("terminated_norm", &comp_chem_program_data_t<REAL>::m_is_terminated_normally)
        .def_readonly("gr_norm_min", &comp_chem_program_data_t<REAL>::m_global_gradient_norm_min)
        .def_readonly("gr_norm_max", &comp_chem_program_data_t<REAL>::m_global_gradient_norm_max)
        .def_readonly("init_atoms_names", &comp_chem_program_data_t<REAL>::m_init_atoms_names)
        .def_readonly("init_atoms_charges", &comp_chem_program_data_t<REAL>::m_init_atoms_charges)
        .def_readonly("steps", &comp_chem_program_data_t<REAL>::m_steps);

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

  pyqpp_ccd_step_export_tmpl<float>(m, "ccd_step_f");
  pyqpp_ccd_export_tmpl<float>(m, "ccd_f");

#ifdef PYTHON_EXP_EXT
  pyqpp_ccd_step_export_tmpl<double>(m, "ccd_step_d");
  pyqpp_ccd_export_tmpl<double>(m, "ccd_d");
#endif

}
