#ifndef QPP_COMP_CHEM_PROG_OUTPUT_H
#define QPP_COMP_CHEM_PROG_OUTPUT_H

#include <data/compiler_fallback.hpp>
#include <vector>
#include <variant>
#include <map>
#include <geom/lace3d.hpp>
#include <geom/geom.hpp>
#include <geom/geom_anim.hpp>

namespace qpp {

//  template <typename REAL = float, typename STR_CLASS = std::string>
//  class comp_chem_data_entry_t {
//    private:
//      std::variant<int, REAL, bool, STR_CLASS, std::vector<comp_chem_data_entry_t>,
//      std::map<STR_CLASS, comp_chem_data_entry_t> > p_data;

//    public:
//      template <typename T>
//      T get() {
//        return std::get<T>(p_data);
//      }

//      template <typename T>
//      T get_if() {
//        return std::get_if<T>(p_data);
//      }

//      template <typename T>
//      void set(T t_inst) {
//        p_data = t_inst;
//      }

//  };

  enum comp_chem_program_run_t {
    rt_unknown,
    rt_energy,
    rt_grad,
    rt_geo_opt,
    rt_md,
    rt_vib,
    rt_raman,
    rt_tddft,
    rt_spectrum
  };

  enum comp_chem_program_t {
    pr_unknown,
    pr_vasp,
    pr_firefly,
    pr_pc_gamess,
    pr_cp2k,
    pr_orca,
    pr_molcas
  };

  static std::map<comp_chem_program_t, std::string> ccdprog2str = {
    std::make_pair(pr_unknown, "Unknown"),
    std::make_pair(pr_vasp,    "VASP"),
    std::make_pair(pr_firefly, "PC Gamess Firefly"),
    std::make_pair(pr_cp2k,    "CP2K"),
    std::make_pair(pr_orca,    "Orca"),
    std::make_pair(pr_molcas,  "OpenMolcas"),
  };

  static std::map<comp_chem_program_run_t, std::string> ccdrt2str = {
    std::make_pair(rt_unknown,  "Unknown"),
    std::make_pair(rt_energy,   "Single-point energy"),
    std::make_pair(rt_grad,     "Gradients calculation"),
    std::make_pair(rt_geo_opt,  "Geometry optimization"),
    std::make_pair(rt_md,       "Molecular dynamics"),
    std::make_pair(rt_vib,      "Vibrations calculation"),
    std::make_pair(rt_raman,    "Raman spectrum calculation"),
    std::make_pair(rt_tddft,    "TDDFT energy calculation"),
    std::make_pair(rt_spectrum, "Generic spectrum calculation")
  };

  template <class REAL>
  struct comp_chem_program_vibration_info_t {
      std::vector<vector3<REAL> > m_disp;
      REAL m_frequency{REAL(0)};
      REAL m_intensity{REAL(0)};
      REAL m_reduced_mass{REAL(0)};
      REAL m_raman_activity{REAL(0)};
      REAL m_depolarization{REAL(0)};
  };

  template <class REAL>
  struct comp_chem_program_scf_step_info_t {
      int m_iter{0};
      int m_ex{0};
      int m_dem{0};
      REAL m_toten{REAL(0)};
      REAL m_e_change{REAL(0)};
      REAL m_d_change{REAL(0)};
      REAL m_orb_grad_or_diis_error{REAL(0)};
  };

  template <class REAL>
  struct comp_chem_program_step_t {
      std::vector<comp_chem_program_scf_step_info_t<REAL> > m_scf_steps;
      REAL m_toten{REAL(0)};
      std::vector<vector3<REAL> > m_atoms_pos;
      std::vector<vector3<REAL> > m_atoms_grads;
      std::vector<vector3<REAL> > m_atoms_vels;
      //std::vector<REAL> m_eigen_values;
      std::vector<REAL> m_eigen_values_spin_1_occ;
      std::vector<REAL> m_eigen_values_spin_1_unocc;
      std::vector<REAL> m_eigen_values_spin_2_occ;
      std::vector<REAL> m_eigen_values_spin_2_unocc;
      REAL m_energy_gap_spin_1;
      REAL m_energy_gap_spin_2;
      std::vector<std::pair<REAL, REAL> > m_mulliken_pop_per_atom;
      std::vector<std::pair<REAL, REAL> > m_lowdin_pop_per_atom;
      std::optional<vector3<REAL> > m_dipole_moment{std::nullopt};
  };

  template <class REAL>
  struct comp_chem_program_data_t {
      std::vector<comp_chem_program_step_t<REAL> > m_steps;
      std::vector<vector3<REAL> > m_init_atoms_pos;
      std::vector<std::string> m_init_atoms_names;
      std::vector<REAL> m_init_atoms_charges;
      std::vector<comp_chem_program_vibration_info_t<REAL> > m_vibs;
      std::vector<vector3<REAL> > m_cell_v;
      comp_chem_program_t m_comp_chem_program{comp_chem_program_t::pr_unknown};
      uint32_t m_ccd_flags;
      int m_DIM{0};
      int m_tot_nat{0};
      int m_tot_nelec{0};
      REAL m_tot_charge{0};
      int m_mult{0};
      bool m_is_unrestricted{false};
      int m_n_alpha{0};
      int m_n_beta{0};
      int m_n_spin_states{-1};
      bool m_is_terminated_normally{false};
      comp_chem_program_run_t m_run_t{comp_chem_program_run_t::rt_unknown};

      //comp_chem_data_entry_t<REAL> root;
  };


  //Compile geometry flags
  const uint32_t ccd_cf_default_flags                  = 0;
  const uint32_t ccd_cf_allow_null_init_geom           = 1 << 1;
  const uint32_t ccd_cf_allow_different_size_pos_names = 1 << 2;
  const uint32_t ccd_cf_apply_pdb_name_reducer         = 1 << 3;
  const uint32_t ccd_cf_apply_up_low_atom_name_scheme  = 1 << 4;
  const uint32_t ccd_cf_autocenter_geometry            = 1 << 5;
  const uint32_t ccd_cf_autocenter_steps_geometry      = 1 << 6;
  const uint32_t ccd_cf_check_cell_consistency         = 1 << 7;
  const uint32_t ccd_cf_remove_empty_geom_steps        = 1 << 8;

  template <class REAL>
  bool validate_ccd(comp_chem_program_data_t<REAL> &ccd_inst, uint32_t flags) {
    return true;
  }

  template <class REAL>
  bool compile_ccd(comp_chem_program_data_t<REAL> &ccd_inst, uint32_t flags) {

    if (flags & ccd_cf_remove_empty_geom_steps) {
        for (auto it = ccd_inst.m_steps.begin(); it != ccd_inst.m_steps.end();) {
            if(it->m_atoms_pos.empty()) it = ccd_inst.m_steps.erase(it);
            else ++it;
          }
      }

    return true;
  }

  template <class REAL>
  bool compile_geometry(comp_chem_program_data_t<REAL> &ccd_inst,
                        geometry<REAL, periodic_cell<REAL> > &g,
                        uint32_t compile_flags = ccd_cf_default_flags) {

    if ((ccd_inst.m_init_atoms_pos.empty() || ccd_inst.m_init_atoms_names.empty())
        || (compile_flags & ccd_cf_allow_null_init_geom)) return false;

    if ((ccd_inst.m_init_atoms_pos.size() != ccd_inst.m_init_atoms_names.size())
        || (compile_flags & ccd_cf_allow_different_size_pos_names)) return false;

    if (ccd_inst.m_DIM != ccd_inst.m_cell_v.size()) return false;

    g.DIM = ccd_inst.m_DIM;

    if (g.DIM > 0)
      for (size_t i = 0; i < ccd_inst.m_DIM; i++) g.cell.v[i] = ccd_inst.m_cell_v[i];

    for (size_t i = 0; i < ccd_inst.m_init_atoms_names.size(); i++)
      g.add(ccd_inst.m_init_atoms_names[i], ccd_inst.m_init_atoms_pos[i]);

    return true;
  }

  template <class REAL>
  bool compile_static_animation(comp_chem_program_data_t<REAL> &ccd_inst,
                                std::vector<geom_anim_record_t<REAL> > &anim_rec,
                                uint32_t compile_flags = ccd_cf_default_flags) {

    geom_anim_record_t<REAL> anim;

    anim.m_anim_type = geom_anim_type::anim_static;
    anim.m_anim_name = "static";
    anim.frame_data.resize(1);
    anim.frame_data[0].resize(ccd_inst.m_init_atoms_pos.size());
    for (size_t i = 0; i < ccd_inst.m_init_atoms_pos.size(); i++)
      anim.frame_data[0][i] = ccd_inst.m_init_atoms_pos[i];

    anim_rec.push_back(std::move(anim));
    return true;
  }

  template <class REAL>
  bool compile_animation(comp_chem_program_data_t<REAL> &ccd_inst,
                         std::vector<geom_anim_record_t<REAL> > &anim_rec,
                         uint32_t compile_flags = ccd_cf_default_flags) {

    if (ccd_inst.m_run_t != comp_chem_program_run_t::rt_geo_opt &&
        ccd_inst.m_run_t != comp_chem_program_run_t::rt_md &&
        ccd_inst.m_run_t != comp_chem_program_run_t::rt_vib &&
        ccd_inst.m_run_t != comp_chem_program_run_t::rt_raman) return false;

    bool copy_steps_content = false;

    geom_anim_type stored_anim_type{geom_anim_type::anim_static};
    std::string stored_anim_name;

    switch (ccd_inst.m_run_t) {
      case comp_chem_program_run_t::rt_geo_opt :
        stored_anim_type = geom_anim_type::anim_geo_opt;
        copy_steps_content = true;
        stored_anim_name = "geo_opt";
        break;
      case comp_chem_program_run_t::rt_md :
        stored_anim_type = geom_anim_type::anim_md;
        copy_steps_content = true;
        stored_anim_name = "mol_dyn";
        break;
      case comp_chem_program_run_t::rt_vib :
        stored_anim_type = geom_anim_type::anim_vib;
        copy_steps_content = false;
        stored_anim_name = "vib";
        break;
      case comp_chem_program_run_t::rt_raman :
        stored_anim_type = geom_anim_type::anim_vib;
        copy_steps_content = false;
        stored_anim_name = "vib";
        break;
      default:
        return false;
        break;
      };

    if (copy_steps_content) {

        geom_anim_record_t<REAL> anim;
        anim.m_anim_type = stored_anim_type;
        anim.m_anim_name = stored_anim_name;

        int non_empty_steps_count = std::count_if(ccd_inst.m_steps.begin(), ccd_inst.m_steps.end(),
                                                  [](comp_chem_program_step_t<REAL> &step) {
                                                    return !step.m_atoms_pos.empty();
                                                  });

        anim.frame_data.resize(non_empty_steps_count);
        int steps_c = -1;

        for (size_t i = 0; i < ccd_inst.m_steps.size(); i++) {
            if (!ccd_inst.m_steps[i].m_atoms_pos.empty()) {
                steps_c += 1;
                anim.frame_data[steps_c].resize(ccd_inst.m_steps[i].m_atoms_pos.size());
                for (size_t q = 0; q < ccd_inst.m_steps[i].m_atoms_pos.size(); q++)
                  anim.frame_data[steps_c][q] = ccd_inst.m_steps[i].m_atoms_pos[q];
              }
          }

        anim_rec.push_back(std::move(anim));
        return true;
      }

    else {
        if (ccd_inst.m_run_t == comp_chem_program_run_t::rt_vib ||
            ccd_inst.m_run_t == comp_chem_program_run_t::rt_raman)
          for (size_t v = 0; v < ccd_inst.m_vibs.size(); v++) {
              geom_anim_record_t<REAL> anim;
              anim.m_anim_type = stored_anim_type;
              anim.m_anim_name = fmt::format("vibration {}", v);

              const int total_frames_upwards = 10;
              const int total_frames = total_frames_upwards * 2 + 1;
              anim.frame_data.resize(total_frames);

              for (int i = 0; i < total_frames; i++) {
                  anim.frame_data[i].resize(ccd_inst.m_tot_nat);
                  //transform index
                  int tf_index = i;
                  if (i > total_frames_upwards) tf_index = total_frames - (i+1);
                  for (size_t q = 0; q < ccd_inst.m_vibs[v].m_disp.size(); q++) {
                      anim.frame_data[i][q] = ccd_inst.m_init_atoms_pos[q] +
                                              ccd_inst.m_vibs[v].m_disp[q] *
                                              (REAL(tf_index) / total_frames_upwards);
                    }
                }
              anim_rec.push_back(std::move(anim));
            }
      }

    return true;

  }

}

#endif
