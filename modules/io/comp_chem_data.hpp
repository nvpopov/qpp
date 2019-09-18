#ifndef QPP_COMP_CHEM_PROG_OUTPUT_H
#define QPP_COMP_CHEM_PROG_OUTPUT_H

#include <vector>
#include <variant>
#include <numeric>
#include <map>
#include <geom/lace3d.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/geom_anim.hpp>
#include <io/ccd_programs.hpp>
#include <data/generic_array.hpp>

namespace qpp {

  enum ccd_spin_e {

    spin_alpha,
    spin_beta

  };

  enum comp_chem_program_run_e {

    rt_unknown,
    rt_energy,
    rt_grad,
    rt_geo_opt,
    rt_cell_opt,
    rt_md,
    rt_vib,
    rt_raman,
    rt_tddft,
    rt_spectrum

  };

  static std::map<comp_chem_program_e, std::string> ccdprog2str = {

    std::make_pair(pr_unknown, "Unknown"),
    std::make_pair(pr_vasp,    "VASP"),
    std::make_pair(pr_firefly, "PC Gamess Firefly"),
    std::make_pair(pr_cp2k,    "CP2K"),
    std::make_pair(pr_orca,    "Orca"),
    std::make_pair(pr_molcas,  "OpenMolcas"),
    std::make_pair(pr_molden,  "Molden"),

  };

  static std::map<comp_chem_program_run_e, std::string> ccdrt2str = {

    std::make_pair(rt_unknown,  "Unknown"),
    std::make_pair(rt_energy,   "Single-point energy"),
    std::make_pair(rt_grad,     "Gradients calculation"),
    std::make_pair(rt_geo_opt,  "Geometry optimization"),
    std::make_pair(rt_cell_opt, "Cell optimization"),
    std::make_pair(rt_md,       "Molecular dynamics"),
    std::make_pair(rt_vib,      "Vibrations calculation"),
    std::make_pair(rt_raman,    "Raman spectrum calculation"),
    std::make_pair(rt_tddft,    "TDDFT energy calculation"),
    std::make_pair(rt_spectrum, "Generic spectrum calculation")

  };

  template <class REAL>
  struct comp_chem_program_vibration_info_t {

      generic_array_t<vector3<REAL>, REAL > m_disp;
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
      double m_toten{double(0)};
      double m_e_change{double(0)};
      double m_d_change{double(0)};
      double m_generic_error{double(0)};

  };

  template <class REAL>
  struct comp_chem_program_step_t {

      std::vector<comp_chem_program_scf_step_info_t<REAL> > m_scf_steps;
      double m_toten{double(0)};
      generic_array_t<vector3<REAL>, REAL > m_atoms_pos;
      generic_array_t<vector3<REAL>, REAL > m_atoms_grads;
      generic_array_t<vector3<REAL>, REAL > m_atoms_vels;

      std::vector<REAL> m_eigen_values_spin_1_occ;
      std::vector<REAL> m_eigen_values_spin_1_unocc;
      std::vector<REAL> m_eigen_values_spin_2_occ;
      std::vector<REAL> m_eigen_values_spin_2_unocc;
      REAL m_energy_gap_spin_1;
      REAL m_energy_gap_spin_2;

      // atomic population
      std::vector<std::pair<REAL, REAL> > m_mulliken_pop_per_atom;
      std::vector<REAL> m_mulliken_net_chg_per_atom;
      std::vector<REAL> m_mulliken_spin_pop_per_atom;

      std::vector<std::pair<REAL, REAL> > m_lowdin_pop_per_atom;
      std::vector<REAL> m_lowdin_net_chg_per_atom;
      std::vector<REAL> m_lowdin_spin_pop_per_atom;

      vector3<REAL> m_dipole_moment{0};

      // gradient stuff
      vector3<REAL> m_grad_min{0,0,0};
      vector3<REAL> m_grad_max{0,0,0};
      vector3<REAL> m_grad_aver{0,0,0};
      REAL m_grad_norm_min{10};
      REAL m_grad_norm_max{0};
      REAL m_grad_norm_average{0};

      // for cell_opt steps
      bool m_cell_is_animable{false};
      std::array<vector3<REAL>, 3> m_cell;

  };

  template<class REAL>
  struct tddft_transition_rec_t {

      size_t m_from{0};
      size_t m_from_spin{ccd_spin_e::spin_alpha};

      size_t m_to{0};
      size_t m_to_spin{ccd_spin_e::spin_alpha};

      REAL m_amplitude{0};

  };

  template<class REAL>
  struct tddft_transitions_t {

      bool m_all_lhs_equal{false};
      bool m_all_rhs_equal{false};

      REAL m_en_ev{0};
      REAL m_osc_str{0};
      vector3<REAL> m_trans_dipole_moment;

      /* lhs state, lhs spin, rhs state, rhs spin, amplitude */
      std::vector<tddft_transition_rec_t<REAL > > m_transition;

  };

  template <class REAL>
  struct comp_chem_program_data_t {

      // initial values
      generic_array_t<vector3<REAL>, REAL > m_init_apos; // initial atoms pos
      std::vector<std::string> m_init_anames; // initial atoms names
      std::vector<REAL> m_init_achg; // initial atoms charges

      // general data
      std::vector<comp_chem_program_step_t<REAL> > m_steps;
      std::vector<comp_chem_program_vibration_info_t<REAL> > m_vibs;

      // general info about the run
      comp_chem_program_e m_comp_chem_program{comp_chem_program_e::pr_unknown};
      comp_chem_program_run_e m_run_t{comp_chem_program_run_e::rt_unknown};
      uint32_t m_ccd_flags;

      std::vector<vector3<REAL> > m_cell_v;
      bool m_is_qmmm{false};
      bool m_need_to_extract_mm{false};
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

      vector3<REAL> m_global_gradient_min{0,0,0};
      vector3<REAL> m_global_gradient_max{0,0,0};
      vector3<REAL> m_global_gradient_average{0,0,0};
      REAL m_global_gradient_norm_min{10};
      REAL m_global_gradient_norm_max{0};

      std::vector<tddft_transitions_t<REAL> > m_tddft_trans_rec;

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

    if (ccd_inst.m_run_t == comp_chem_program_run_e::rt_geo_opt && !ccd_inst.m_steps.empty()) {

        int total_valid_steps = 0;

        //calculate extremal gradient values for each step
        for (auto &step : ccd_inst.m_steps)
          if (!step.m_atoms_grads.empty()) {
              total_valid_steps += 1;
              for (size_t i = 0; i < step.m_atoms_grads.size(); i++) {

                  REAL grad_norm = step.m_atoms_grads[i].norm();

                  if (grad_norm > step.m_grad_norm_max) {
                      step.m_grad_norm_max = grad_norm;
                      step.m_grad_max = step.m_atoms_grads[i];
                    }

                  if (grad_norm < step.m_grad_norm_min) {
                      step.m_grad_norm_min = grad_norm;
                      step.m_grad_min = step.m_atoms_grads[i];
                    }

                  if (grad_norm > ccd_inst.m_global_gradient_norm_max)
                    ccd_inst.m_global_gradient_norm_max = grad_norm;

                  if (grad_norm < ccd_inst.m_global_gradient_norm_min)
                    ccd_inst.m_global_gradient_norm_min = grad_norm;

                  step.m_grad_aver += step.m_atoms_grads[i];
                  step.m_grad_norm_average += grad_norm;
                }

              step.m_grad_aver /= step.m_atoms_grads.size();
              step.m_grad_norm_average /= step.m_atoms_grads.size();

            }
      }

    /* tddft data compilation */
    if (!ccd_inst.m_tddft_trans_rec.empty())
      for (auto &rec : ccd_inst.m_tddft_trans_rec) {

          bool all_lhs_equal{true};
          bool all_rhs_equal{true};

          if (rec.m_transition.size() > 1)
            for (size_t i = 1; i < rec.m_transition.size(); i++) {

                if (rec.m_transition[i-1].m_from != rec.m_transition[i].m_from)
                  all_lhs_equal = false;

                if (rec.m_transition[i-1].m_to != rec.m_transition[i].m_to)
                  all_lhs_equal = false;

              }

          rec.m_all_lhs_equal = all_lhs_equal;
          rec.m_all_rhs_equal = all_rhs_equal;

        }

    return true;

  }

  template <class REAL>
  bool compile_geometry(comp_chem_program_data_t<REAL> &ccd_inst,
                        geometry<REAL, periodic_cell<REAL> > &g,
                        uint32_t compile_flags = ccd_cf_default_flags) {

    if ((ccd_inst.m_init_apos.empty() || ccd_inst.m_init_anames.empty())
        || (compile_flags & ccd_cf_allow_null_init_geom)) return false;

    if ((ccd_inst.m_init_apos.size() != ccd_inst.m_init_anames.size())
        || (compile_flags & ccd_cf_allow_different_size_pos_names)) return false;

    if (ccd_inst.m_DIM != ccd_inst.m_cell_v.size()) return false;

    if (ccd_inst.m_tot_nat == 0 && !ccd_inst.m_init_anames.empty())
      ccd_inst.m_tot_nat = ccd_inst.m_init_anames.size();

    g.DIM = ccd_inst.m_DIM;

    if (g.DIM > 0)
      for (size_t i = 0; i < ccd_inst.m_DIM; i++) g.cell.v[i] = ccd_inst.m_cell_v[i];

    for (size_t i = 0; i < ccd_inst.m_init_anames.size(); i++)
      g.add(ccd_inst.m_init_anames[i], ccd_inst.m_init_apos[i]);

    if (ccd_inst.m_init_achg.size() == ccd_inst.m_tot_nat && g.is_xgeometry()) {

        xgeometry<REAL, periodic_cell<REAL> > *xsrc = nullptr;
        xsrc = (xgeometry<REAL, periodic_cell<REAL> >*)(&g);

        if (xsrc)
          for (size_t q = 0; q < xsrc->nat(); q++) xsrc->charge(q) = ccd_inst.m_init_achg[q];

      }

    return true;

  }

  template <class REAL>
  bool compile_static_animation(comp_chem_program_data_t<REAL> &ccd_inst,
                                std::vector<geom_anim_record_t<REAL> > &anim_rec,
                                uint32_t compile_flags = ccd_cf_default_flags) {

    geom_anim_record_t<REAL> anim;

    anim.m_anim_type = geom_anim_t::anim_static;
    anim.m_anim_name = "static";
    anim.frames.resize(1);
    anim.frames[0].atom_pos.resize(ccd_inst.m_init_apos.size());
    for (size_t i = 0; i < ccd_inst.m_init_apos.size(); i++)
      anim.frames[0].atom_pos[i] = ccd_inst.m_init_apos[i];

    anim_rec.push_back(std::move(anim));
    return true;

  }

  template <class REAL>
  bool compile_animation(comp_chem_program_data_t<REAL> &ccd_inst,
                         std::vector<geom_anim_record_t<REAL> > &anim_rec,
                         uint32_t compile_flags = ccd_cf_default_flags) {

    if (ccd_inst.m_run_t != comp_chem_program_run_e::rt_geo_opt &&
        ccd_inst.m_run_t != comp_chem_program_run_e::rt_md &&
        ccd_inst.m_run_t != comp_chem_program_run_e::rt_vib &&
        ccd_inst.m_run_t != comp_chem_program_run_e::rt_raman &&
        ccd_inst.m_run_t != comp_chem_program_run_e::rt_cell_opt) return false;

    bool copy_steps_content = false;

    geom_anim_t stored_anim_type{geom_anim_t::anim_static};
    std::string stored_anim_name;

    switch (ccd_inst.m_run_t) {

      case comp_chem_program_run_e::rt_geo_opt :
        stored_anim_type = geom_anim_t::anim_geo_opt;
        copy_steps_content = true;
        stored_anim_name = "geo_opt";
        break;

      case comp_chem_program_run_e::rt_cell_opt :
        stored_anim_type = geom_anim_t::anim_generic;
        copy_steps_content = true;
        stored_anim_name = "cell_opt";
        break;

      case comp_chem_program_run_e::rt_md :
        stored_anim_type = geom_anim_t::anim_md;
        copy_steps_content = true;
        stored_anim_name = "mol_dyn";
        break;

      case comp_chem_program_run_e::rt_vib :
        stored_anim_type = geom_anim_t::anim_vib;
        copy_steps_content = false;
        stored_anim_name = "vib";
        break;

      case comp_chem_program_run_e::rt_raman :
        stored_anim_type = geom_anim_t::anim_vib;
        copy_steps_content = false;
        stored_anim_name = "vib";
        break;

      default:
        return false;
        break;

      };

    bool is_cell_opt =
        ccd_inst.m_run_t == comp_chem_program_run_e::rt_cell_opt && ccd_inst.m_DIM > 0;

    if (copy_steps_content) {

        geom_anim_record_t<REAL> anim;
        anim.m_anim_type = stored_anim_type;
        anim.m_anim_name = stored_anim_name;

        auto valid_step = [&is_cell_opt](comp_chem_program_step_t<REAL> &step) {
          return !step.m_atoms_pos.empty() && (!is_cell_opt || step.m_cell_is_animable);
        };

        // pre-calculation of valid steps
        int steps_valid_c =
            std::count_if(ccd_inst.m_steps.begin(), ccd_inst.m_steps.end(), valid_step);

        anim.frames.resize(steps_valid_c);
        int steps_c = -1;

        // we're starting to form an animation
        for (size_t i = 0; i < ccd_inst.m_steps.size(); i++)

          if (valid_step(ccd_inst.m_steps[i])) {

              steps_c += 1;

              // copy cell info
              if (is_cell_opt) {
                  anim.frames[steps_c].m_cell_is_animable = true;
                  for (size_t cell_i = 0; cell_i < ccd_inst.m_DIM; cell_i++)
                    anim.frames[steps_c].m_cell[cell_i] = ccd_inst.m_steps[i].m_cell[cell_i];
                }

              // copy atom pos data
              anim.frames[steps_c].atom_pos.resize(ccd_inst.m_steps[i].m_atoms_pos.size());
              for (size_t q = 0; q < ccd_inst.m_steps[i].m_atoms_pos.size(); q++)
                anim.frames[steps_c].atom_pos[q] = ccd_inst.m_steps[i].m_atoms_pos[q];

            } // the animation has been formed. put it in the geom_anim_record_t

        // final decision on variable cell animation
        anim.m_variable_cell_anim = is_cell_opt && (steps_valid_c > 0);

        anim_rec.push_back(std::move(anim));
        return true;

      } // if (copy_steps_content)

    else {

        if (ccd_inst.m_run_t == comp_chem_program_run_e::rt_vib ||
            ccd_inst.m_run_t == comp_chem_program_run_e::rt_raman)
          for (size_t v = 0; v < ccd_inst.m_vibs.size(); v++) {
              geom_anim_record_t<REAL> anim;
              anim.m_anim_type = stored_anim_type;
              anim.m_anim_name = fmt::format("f={} cm-1", ccd_inst.m_vibs[v].m_frequency);

              const int total_frames_upwards = 10;
              const int total_frames = total_frames_upwards * 2 + 1;
              anim.frames.resize(total_frames);

              for (int i = 0; i < total_frames; i++) {
                  anim.frames[i].atom_pos.resize(ccd_inst.m_tot_nat);
                  //transform index
                  int tf_index = i;
                  if (i > total_frames_upwards) tf_index = total_frames - (i+1);
                  for (size_t q = 0; q < ccd_inst.m_vibs[v].m_disp.size(); q++) {
                      anim.frames[i].atom_pos[q] =
                          ccd_inst.m_init_apos[q] + ccd_inst.m_vibs[v].m_disp[q] *
                          (REAL(tf_index) / total_frames_upwards);
                    }
                }
              anim_rec.push_back(std::move(anim));
            }

      }

    return true;

  }

} // namespace qpp

#endif
