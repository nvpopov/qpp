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

  template <typename REAL = float, typename STR_CLASS = std::string>
  class comp_chem_data_entry_t {
    private:
      std::variant<int, REAL, bool, STR_CLASS, std::vector<comp_chem_data_entry_t>,
      std::map<STR_CLASS, comp_chem_data_entry_t> > p_data;

    public:
      template <typename T>
      T get() {
        return std::get<T>(p_data);
      }

      template <typename T>
      T get_if() {
        return std::get_if<T>(p_data);
      }

      template <typename T>
      void set(T t_inst) {
        p_data = t_inst;
      }

  };

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
      std::vector<vector3<REAL> > disp;
      REAL frequency{REAL(0)};
      REAL intensity{REAL(0)};
      REAL reduced_mass{REAL(0)};
      REAL raman_activity{REAL(0)};
      REAL depolarization{REAL(0)};
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
      std::vector<vector3<REAL> > cell_v;
      comp_chem_program_t comp_chem_program{comp_chem_program_t::pr_unknown};
      uint32_t ccd_flags;
      int DIM{0};
      int tot_num_atoms{0};
      int tot_num_electrons{0};
      REAL tot_charge{0};
      int mult{0};
      bool is_unrestricted{false};
      int n_alpha{0};
      int n_beta{0};
      int n_spin_states{-1};
      bool m_is_terminated_normally{false};
      comp_chem_program_run_t run_t{comp_chem_program_run_t::rt_unknown};

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

  template <class REAL>
  bool validate_ccd(comp_chem_program_data_t<REAL> &ccd_inst, uint32_t flags) {
    return true;
  }

  template <class REAL>
  bool compile_geometry(comp_chem_program_data_t<REAL> &ccd_inst,
                        geometry<REAL, periodic_cell<REAL> > &g,
                        uint32_t compile_flags = ccd_cf_default_flags) {

    if ((ccd_inst.init_pos.empty() || ccd_inst.init_atom_names.empty())
        || (compile_flags & ccd_cf_allow_null_init_geom)) return false;

    if ((ccd_inst.init_pos.size() != ccd_inst.init_atom_names.size())
        || (compile_flags & ccd_cf_allow_different_size_pos_names)) return false;

    if (ccd_inst.DIM != ccd_inst.cell_v.size()) return false;

    g.DIM = ccd_inst.DIM;

    if (g.DIM > 0)
      for (size_t i = 0; i < ccd_inst.DIM; i++) g.cell.v[i] = ccd_inst.cell_v[i];

    for (size_t i = 0; i < ccd_inst.init_atom_names.size(); i++)
      g.add(ccd_inst.init_atom_names[i], ccd_inst.init_pos[i]);

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
    anim.frame_data[0].resize(ccd_inst.init_pos.size());
    for (size_t i = 0; i < ccd_inst.init_pos.size(); i++)
      anim.frame_data[0][i] = ccd_inst.init_pos[i];

    anim_rec.push_back(std::move(anim));
    return true;
  }

  template <class REAL>
  bool compile_animation(comp_chem_program_data_t<REAL> &ccd_inst,
                         std::vector<geom_anim_record_t<REAL> > &anim_rec,
                         uint32_t compile_flags = ccd_cf_default_flags) {

    if (ccd_inst.run_t != comp_chem_program_run_t::rt_geo_opt &&
        ccd_inst.run_t != comp_chem_program_run_t::rt_md &&
        ccd_inst.run_t != comp_chem_program_run_t::rt_vib &&
        ccd_inst.run_t != comp_chem_program_run_t::rt_raman) return false;

    bool copy_steps_content = false;

    geom_anim_type stored_anim_type{geom_anim_type::anim_static};
    std::string stored_anim_name;

    switch (ccd_inst.run_t) {
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
        anim.frame_data.resize(ccd_inst.steps.size());
        for (size_t i = 0; i < ccd_inst.steps.size(); i++) {
            anim.frame_data[i].resize(ccd_inst.steps[i].pos.size());
            for (size_t q = 0; q < ccd_inst.steps[i].pos.size(); q++)
              anim.frame_data[i][q] = ccd_inst.steps[i].pos[q];
          }
        anim_rec.push_back(std::move(anim));
        return true;
      }
    else {
        if (ccd_inst.run_t == comp_chem_program_run_t::rt_vib ||
            ccd_inst.run_t == comp_chem_program_run_t::rt_raman)
          for (size_t v = 0; v < ccd_inst.vibs.size(); v++) {
              geom_anim_record_t<REAL> anim;
              anim.m_anim_type = stored_anim_type;
              anim.m_anim_name = fmt::format("vibration {}", v);

              const int total_frames_upwards = 10;
              const int total_frames = total_frames_upwards * 2 + 1;
              anim.frame_data.resize(total_frames);

              for (int i = 0; i < total_frames; i++) {
                  anim.frame_data[i].resize(ccd_inst.tot_num_atoms);
                  //transform index
                  int tf_index = i;
                  if (i > total_frames_upwards) tf_index = total_frames - (i+1);
                  for (size_t q = 0; q < ccd_inst.vibs[v].disp.size(); q++) {
                      anim.frame_data[i][q] = ccd_inst.init_pos[q] +
                                              ccd_inst.vibs[v].disp[q] *
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
