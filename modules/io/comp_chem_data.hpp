#ifndef QPP_COMP_CHEM_PROG_OUTPUT_H
#define QPP_COMP_CHEM_PROG_OUTPUT_H

#include <data/compiler_fallback.hpp>
#include <vector>
#include <geom/lace3d.hpp>
#include <geom/geom.hpp>
#include <geom/geom_anim.hpp>

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
  struct comp_chem_program_data_t {
      std::vector<comp_chem_program_step_t<REAL> > steps;
      std::vector<vector3<REAL> > init_pos;
      std::vector<std::string> init_atom_names;
      std::vector<REAL> init_charges;
      std::vector<comp_chem_program_vibration_info_t<REAL> > vibs;
      std::optional<vector3<REAL> > cell_v0;
      std::optional<vector3<REAL> > cell_v1;
      std::optional<vector3<REAL> > cell_v2;
      uint32_t ccd_flags;
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
  };


  //Compile geometry flags
  const uint32_t ccd_cf_allow_null_init_geom           = 1 << 0;
  const uint32_t ccd_cf_allow_different_size_pos_names = 1 << 1;
  const uint32_t ccd_cf_apply_pdb_name_reducer         = 1 << 2;

  template <class REAL>
  bool validate_ccd(comp_chem_program_data_t<REAL> &ccd_inst, uint32_t flags) {
    return true;
  }

  template <class REAL>
  bool compile_geometry(comp_chem_program_data_t<REAL> &ccd_inst,
                        geometry<REAL, periodic_cell<REAL> > &g, uint32_t compile_flags = 0) {

    if ((ccd_inst.init_pos.empty() || ccd_inst.init_atom_names.empty())
        || (compile_flags & ccd_cf_allow_null_init_geom)) return false;

    if ((ccd_inst.init_pos.size() != ccd_inst.init_atom_names.size())
        || (compile_flags & ccd_cf_allow_different_size_pos_names)) return false;

    if (ccd_inst.DIM > 0 && !ccd_inst.cell_v0) return false;
    if (ccd_inst.DIM > 1 && !ccd_inst.cell_v0 && !ccd_inst.cell_v1) return false;
    if (ccd_inst.DIM > 2 && !ccd_inst.cell_v0 && !ccd_inst.cell_v1 && !ccd_inst.cell_v2)
      return false;

    g.DIM = ccd_inst.DIM;

    if (ccd_inst.DIM > 0 && ccd_inst.cell_v0) g.cell.v[0] = *(ccd_inst.cell_v0);
    if (ccd_inst.DIM > 1 && ccd_inst.cell_v1) g.cell.v[1] = *(ccd_inst.cell_v1);
    if (ccd_inst.DIM > 2 && ccd_inst.cell_v2) g.cell.v[2] = *(ccd_inst.cell_v2);

    for (size_t i = 0; i < ccd_inst.init_atom_names.size(); i++)
      g.add(ccd_inst.init_atom_names[i], ccd_inst.init_pos[i]);

    return true;
  }

  template <class REAL>
  bool compile_animation(comp_chem_program_data_t<REAL> &ccd_inst,
                         geom_anim_record_t<REAL> &anim_rec) {
    return true;
  }

}

#endif
