#ifndef QPP_COMP_CHEM_PROG_OUTPUT_H
#define QPP_COMP_CHEM_PROG_OUTPUT_H

#include <data/compiler_fallback.hpp>
#include <vector>
#include <geom/lace3d.hpp>

namespace qpp {

  enum comp_chem_program_run_t {
    unknown,
    energy,
    grad,
    geo_opt,
    md,
    vib,
    tddft,
    spectrum
  };

  template <class REAL>
  struct comp_chem_program_vibration_info_t {
      std::vector<vector3<REAL> > disp;
      REAL frequency{REAL(0)};
      REAL intensity{REAL(0)};
      REAL reduced_mass{REAL(0)};
  };

  template <class REAL>
  struct comp_chem_program_scf_step_info_t {
      int iter{0};
      int ex{0};
      int dem{0};
      REAL total_energy{REAL(0)};
      REAL e_change{REAL(0)};
      REAL d_change{REAL(0)};
      REAL orb_grad_or_diis_error{REAL(0)};
  };

  template <class REAL>
  struct comp_chem_program_step_t {
      std::vector<comp_chem_program_scf_step_info_t<REAL> > scf_steps;
      REAL total_energy{REAL(0)};
      std::vector<vector3<REAL> > pos;
      std::vector<vector3<REAL> > grad;
      std::vector<vector3<REAL> > vels;
      std::vector<REAL> eigen_values;
      std::vector<std::pair<REAL, REAL> > mulliken_pop_per_atom;
      std::vector<std::pair<REAL, REAL> > lowdin_pop_per_atom;
      std::optional<vector3<REAL> >dipole_moment{std::nullopt};
  };

  template <class REAL>
  struct comp_chem_program_output_t {
      int DIM{0};
      int tot_num_atoms{0};
      int tot_num_electrons{0};
      REAL tot_charge{0};
      int mult{0};
      bool is_unrestricted{false};
      int n_alpha{0};
      int n_beta{0};
      bool m_is_terminated_normally{false};
      comp_chem_program_run_t run_t{comp_chem_program_run_t::unknown};
      std::vector<comp_chem_program_step_t<REAL> > steps;
      std::vector<vector3<REAL> > init_pos;
      std::vector<std::string> init_atom_names;
      std::vector<REAL> init_charges;
      std::vector<comp_chem_program_vibration_info_t<REAL> > vibs;
  };


}

#endif
