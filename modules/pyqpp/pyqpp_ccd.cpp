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

#include <io/ccd_cp2k.hpp>
#include <io/ccd_firefly.hpp>
#include <io/ccd_xyz.hpp>
#include <io/fdstream.hpp>

using namespace qpp;

template<auto FUNC, typename REAL>
void pyqpp_ccd_func_template(int fd, comp_chem_program_data_t<REAL> &ccd) {

  boost::fdistream inp(fd);
  FUNC(inp, ccd);

}

template<typename REAL>
void pyqpp_ccd_io_export_tmpl(py::module m) {

  auto io_m = m.def_submodule("io");

  io_m.def("read_ccd_from_cp2k_output",
           &pyqpp_ccd_func_template<read_ccd_from_cp2k_output<REAL>, REAL>);
  io_m.def("read_ccd_from_firefly_output",
           &pyqpp_ccd_func_template<read_ccd_from_firefly_output<REAL>, REAL>);
  io_m.def("read_ccd_from_xyz_file",
           &pyqpp_ccd_func_template<read_ccd_from_xyz_file<REAL>, REAL>);

}

template<typename REAL>
void pyqpp_ccd_scf_step_export_tmpl(py::module m, const char * pyname) {

  py::class_<comp_chem_program_scf_step_info_t<REAL>,
      std::shared_ptr<comp_chem_program_scf_step_info_t<REAL> > >
      py_ccd_scf_step(m, pyname);

  py_ccd_scf_step.def_readonly("iter", &comp_chem_program_scf_step_info_t<REAL>::m_iter)
                 .def_readonly("ex", &comp_chem_program_scf_step_info_t<REAL>::m_ex)
                 .def_readonly("dem", &comp_chem_program_scf_step_info_t<REAL>::m_dem)
                 .def_readonly("toten", &comp_chem_program_scf_step_info_t<REAL>::m_toten)
                 .def_readonly("e_change", &comp_chem_program_scf_step_info_t<REAL>::m_e_change)
                 .def_readonly("d_change", &comp_chem_program_scf_step_info_t<REAL>::m_d_change)
                 .def_readonly("error", &comp_chem_program_scf_step_info_t<REAL>::m_generic_error);

}

template<typename REAL>
void pyqpp_ccd_step_export_tmpl(py::module m, const char * pyname) {

  py::class_<comp_chem_program_step_t<REAL>,
      std::shared_ptr<comp_chem_program_step_t<REAL> > >
      py_ccd_step(m, pyname);

  py_ccd_step.def_readonly("toten", &comp_chem_program_step_t<REAL>::m_toten)
             .def_readonly("pos", &comp_chem_program_step_t<REAL>::m_atoms_pos)
             .def_readonly("grad", &comp_chem_program_step_t<REAL>::m_atoms_grads)
             .def_readonly("vel", &comp_chem_program_step_t<REAL>::m_atoms_vels)
             .def_readonly("en_spin_1_o",
                           &comp_chem_program_step_t<REAL>::m_eigen_values_spin_1_occ)
             .def_readonly("en_spin_1_u",
                           &comp_chem_program_step_t<REAL>::m_eigen_values_spin_1_unocc)
             .def_readonly("en_spin_2_o",
                           &comp_chem_program_step_t<REAL>::m_eigen_values_spin_2_occ)
             .def_readonly("en_spin_2_u",
                           &comp_chem_program_step_t<REAL>::m_eigen_values_spin_2_unocc)
             .def_readonly("en_gap_spin_1", &comp_chem_program_step_t<REAL>::m_energy_gap_spin_1)
             .def_readonly("en_gap_spin_2", &comp_chem_program_step_t<REAL>::m_energy_gap_spin_2)
             .def_readonly("dipole_moment", &comp_chem_program_step_t<REAL>::m_dipole_moment)
             .def_readonly("gr_min", &comp_chem_program_step_t<REAL>::m_grad_min)
             .def_readonly("gr_max", &comp_chem_program_step_t<REAL>::m_grad_max)
             .def_readonly("gr_av", &comp_chem_program_step_t<REAL>::m_grad_aver)
             .def_readonly("ngr_min", &comp_chem_program_step_t<REAL>::m_grad_norm_min)
             .def_readonly("ngr_max", &comp_chem_program_step_t<REAL>::m_grad_norm_max)
             .def_readonly("ngr_av", &comp_chem_program_step_t<REAL>::m_grad_norm_average)
             .def_readonly("cell_is_animable", &comp_chem_program_step_t<REAL>::m_cell_is_animable)
             .def_readonly("cell", &comp_chem_program_step_t<REAL>::m_cell);

}

template<typename REAL>
void pyqpp_ccd_vib_export_tmpl(py::module m, const char * pyname) {

  py::class_<comp_chem_program_vibration_info_t<REAL>,
      std::shared_ptr<comp_chem_program_vibration_info_t<REAL> > >
      py_ccd_vib(m, pyname);

  py_ccd_vib.def_readonly("freq", &comp_chem_program_vibration_info_t<REAL>::m_frequency)
            .def_readonly("disp", &comp_chem_program_vibration_info_t<REAL>::m_disp)
            .def_readonly("intensity", &comp_chem_program_vibration_info_t<REAL>::m_intensity)
            .def_readonly("red_mass", &comp_chem_program_vibration_info_t<REAL>::m_reduced_mass)
            .def_readonly("raman_act", &comp_chem_program_vibration_info_t<REAL>::m_raman_activity)
            .def_readonly("depol", &comp_chem_program_vibration_info_t<REAL>::m_depolarization);

}

template<typename REAL>
void pyqpp_ccd_export_tmpl(py::module m, const char * pyname) {

  py::class_<comp_chem_program_data_t<REAL>, std::shared_ptr<comp_chem_program_data_t<REAL> > >
      py_ccd(m, pyname);

  py_ccd.def(py::init<>())
        .def_readonly("runtype", &comp_chem_program_data_t<REAL>::m_run_t)
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
        .def_readonly("init_anames", &comp_chem_program_data_t<REAL>::m_init_anames)
        .def_readonly("init_achg", &comp_chem_program_data_t<REAL>::m_init_achg)
        .def_readonly("init_apos", &comp_chem_program_data_t<REAL>::m_init_apos)
        .def_readonly("steps", &comp_chem_program_data_t<REAL>::m_steps)
        .def_readonly("vibs", &comp_chem_program_data_t<REAL>::m_vibs);

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

  pyqpp_ccd_vib_export_tmpl<float>(m, "ccd_vib_f");
  pyqpp_ccd_scf_step_export_tmpl<float>(m, "ccd_scf_step_f");
  pyqpp_ccd_step_export_tmpl<float>(m, "ccd_step_f");
  pyqpp_ccd_export_tmpl<float>(m, "ccd_f");
  pyqpp_ccd_io_export_tmpl<float>(m);

#ifdef PYTHON_EXP_EXT
  pyqpp_ccd_vib_export_tmpl<double>(m, "ccd_vib_d");
  pyqpp_ccd_scf_step_export_tmpl<double>(m, "ccd_scf_step_d");
  pyqpp_ccd_step_export_tmpl<double>(m, "ccd_step_d");
  pyqpp_ccd_export_tmpl<double>(m, "ccd_d");
  pyqpp_ccd_io_export_tmpl<double>(m);
#endif

}
