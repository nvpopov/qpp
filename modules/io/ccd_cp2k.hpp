#ifndef QPP_CP2K_CCD_IO_H
#define QPP_CP2K_CCD_IO_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <geom/geom.hpp>
#include <geom/geom_anim.hpp>
#include <io/comp_chem_data.hpp>
#include <io/parsing_exceptions.hpp>

#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>

namespace qpp {

  enum cp2k_output_parser_state {

    cp2k_op_state_none,
    cp2k_op_parse_scf,
    cp2k_op_parse_explicit_step_data,
    cp2k_op_parse_eigen_values_occ,
    cp2k_op_parse_eigen_values_unocc,
    cp2k_op_parse_tddfpt_state_en_tr_dm,
    cp2k_op_parse_tddfpt_state_picture

  };

  template<class REAL>
  void read_ccd_from_cp2k_output(std::basic_istream<CHAR_EX,TRAITS> &inp,
                                 comp_chem_program_data_t<REAL> &output) {

    std::locale loc1("C");
    std::string s;

    cp2k_output_parser_state p_state{cp2k_output_parser_state::cp2k_op_state_none};
    bool is_init_parsed{false};

    output.m_DIM = 0;
    output.m_comp_chem_program = comp_chem_program_e::pr_cp2k;
    bool is_first_spin_subspace{false};

    bool alpha_spin_num_isset{false};
    bool beta_spin_num_isset{false};

    uint64_t cur_line{0};

    /* tddft stuff */
    int cur_tddft_state{-1};

    while (!inp.eof()) {

        sgetline(inp, s, cur_line);

        if (inp.eof()) continue;

        if (!is_init_parsed) {

//            if (s.find(" DFT| Spin restricted") != std::string::npos) {
//                output.is_unrestricted = false;
//                continue;
//              }

//            if (s.find(" DFT| Spin unrestricted") != std::string::npos) {
//                output.is_unrestricted = true;
//                continue;
//              }

            //Parse run type
            if (s.find("GLOBAL| Run type") != std::string::npos) {
                if (s.find("GEO_OPT") != std::string::npos)
                  output.m_run_t = comp_chem_program_run_e::rt_geo_opt;
                if (s.find("ENERGY") != std::string::npos)
                  output.m_run_t = comp_chem_program_run_e::rt_energy;
                if (s.find("GRADIENT") != std::string::npos)
                  output.m_run_t = comp_chem_program_run_e::rt_grad;
                if (s.find("CELL_OPT") != std::string::npos)
                  output.m_run_t = comp_chem_program_run_e::rt_cell_opt;
                continue;
              } // End of Parse run type

            //Parse cell info
            if (s.find("CELL_TOP| Vector") != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");

                //int cell_v_idx = 0;
                check_min_split_size(splt, 2, cur_line, s);
                if (splt[2] == "a") output.m_DIM = 1;
                if (splt[2] == "b") output.m_DIM = 2;
                if (splt[2] == "c") output.m_DIM = 3;

                vector3<REAL> cell_v = vec_from_str_ex<REAL>(s, splt, cur_line, 4, 5, 6);
                output.m_cell_v.push_back(std::move(cell_v));

                continue;
              } // End of parse cell info

            //Parse total atom count
            if (s.find("Total number of            -") != std::string::npos) {
//            Total number of            - Atomic kinds:                                   2
//                                       - Atoms:                                         96
//                                       - Shell sets:                                    96
//                                       - Shells:                                       704
//                                       - Primitive Cartesian functions:                640
//                                       - Cartesian basis functions:                   1760
//                                       - Spherical basis functions:                   1664
                sgetline(inp, s, cur_line); //read next line "- Atoms:"
                if (s.find("Atoms:") != std::string::npos) {
                    std::vector<std::string_view> splt = split_sv(s, " ");
                    check_min_split_size(splt, 3, cur_line, s);
                    output.m_tot_nat = str2int(splt, 2, cur_line, s);
                    output.m_init_anames.reserve(output.m_tot_nat);
                    output.m_init_apos.reserve(output.m_tot_nat);
                  }
                continue;
              }

            if (s.find("DFT| Number of spin states") != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                check_min_split_size(splt, 6, cur_line, s);
                output.m_n_spin_states = str2int(splt, 5, cur_line, s);
                if (output.m_n_spin_states == 1) output.m_is_unrestricted = false;
                else output.m_is_unrestricted = true;
                continue;
              }

            if (s.find("DFT| Multiplicity") != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                check_min_split_size(splt, 3, cur_line, s);
                output.m_mult = str2int(splt, 2, cur_line, s);
                continue;
              }

            if (s.find("DFT| Charge") != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                check_min_split_size(splt, 3, cur_line, s);
                output.m_tot_charge = str2real<REAL>(splt, 2, cur_line, s);
                continue;
              }

            if (s.find("MODULE QUICKSTEP:  ATOMIC COORDINATES IN angstrom") != std::string::npos) {
//                  MODULE QUICKSTEP:  ATOMIC COORDINATES IN angstrom
//
//                   Atom  Kind  Element       X           Y           Z          Z(eff)       Mass
//
//                        1     1 Ba  56    0.000000    0.000000    0.000000     10.00     137.3270
//  idx                   0     1 2   3     4           5           6            7         8

                for (int i = 0; i < 3; i++) sgetline(inp, s, cur_line); //read 3 lines
                for (int i = 0; i < output.m_tot_nat; i++) {

                    sgetline(inp, s, cur_line);
                    std::vector<std::string_view> splt = split_sv(s, " ");
                    check_min_split_size(splt, 7, cur_line, s);
                    output.m_init_anames.push_back(std::string(splt[2]));

                    vector3<REAL> pos = vec_from_str_ex<REAL>(s, splt, cur_line, 4, 5, 6);
                    output.m_init_apos.push_back(std::move(pos));

                  }

                is_init_parsed = true;
                continue;

              }

          } // end of !is_init_parsed

        // start of is_init_parsed == true
        if (is_init_parsed) {

            //Number of electrons:  768
            //  0    1     2         3
            if (s.find("Number of electrons") != std::string::npos) {

                std::vector<std::string_view> splt = split_sv(s, " ");
                check_min_split_size(splt, 4, cur_line, s);
                size_t num_electrons = str2int(splt, 3, cur_line, s);

                if (!alpha_spin_num_isset) {
                    alpha_spin_num_isset = true;
                    output.m_n_alpha = num_electrons;
                    continue;
                  }

                if (!beta_spin_num_isset) {
                    beta_spin_num_isset = true;
                    output.m_n_beta = num_electrons;
                    continue;
                  }

                continue;

              }

            if (s.find("SCF WAVEFUNCTION OPTIMIZATION") != std::string::npos) {
                output.m_steps.resize(output.m_steps.size() + 1);
                p_state = cp2k_output_parser_state::cp2k_op_parse_scf;
                continue;
              }

            if (p_state == cp2k_output_parser_state::cp2k_op_parse_scf) {

                if (s.find("  *** SCF") != std::string::npos) {
                    p_state = cp2k_output_parser_state::cp2k_op_state_none;
                    continue;
                  }

                if (s.find("HFX_") != std::string::npos || s.find("-----") != std::string::npos ||
                    s.find("POWELL|") != std::string::npos) {
                    continue;
                  }

                if (s.find("P_Mix") != std::string::npos || s.find("Diag.") != std::string::npos ||
                    s.find("OT") != std::string::npos || s.find("DIIS") != std::string::npos) {

                    //fmt::print(std::cout, "{}\n", s);
                    std::vector<std::string_view> splt = split_sv(s, " ");
                    size_t tot_l = splt.size();

                    if (tot_l > 0 && splt[1] == "OT") {

                        comp_chem_program_scf_step_info_t<REAL> scf_info;
                        check_min_split_size(splt, 1, cur_line, s);
                        scf_info.m_iter = std::stoi(splt[0].data());
                        if (tot_l == 8) scf_info.m_toten = str2real<REAL>(splt, 6, cur_line, s);
                        if (tot_l == 6) scf_info.m_toten = str2real<REAL>(splt, 5, cur_line, s);
                        output.m_steps.back().m_scf_steps.push_back(std::move(scf_info));

                      }

                    continue;

                  }

              }

            if (s.find("ENERGY|") != std::string::npos) {

                //ENERGY| Total FORCE_EVAL ( QS ) energy (a.u.):            -8615.216698379990703
                //  0      1     2         3 4 5   6        7               8
                std::vector<std::string_view> splt = split_sv(s, " "); // 3 - pop 4 - charge
                check_min_split_size(splt, 9, cur_line, s);
                output.m_steps.back().m_toten = str2real<double>(splt, 8, cur_line, s);
                //fmt::print("{} {} \n", output.m_steps.size(), s);
                continue;

              }

            //Mulliken pop per atom
            if (s.find("Mulliken Population Analysis") != std::string::npos) {

                for (auto i = 0; i < 2; i++) sgetline(inp, s, cur_line); //read two common lines
                output.m_steps.back().m_mulliken_pop_per_atom.reserve(output.m_tot_nat);
                output.m_steps.back().m_mulliken_spin_pop_per_atom.reserve(output.m_tot_nat);
                output.m_steps.back().m_mulliken_net_chg_per_atom.reserve(output.m_tot_nat);

                for (size_t i = 0; i < output.m_tot_nat; i++) {

                    sgetline(inp, s, cur_line);
                    std::vector<std::string_view> splt = split_sv(s, " "); // 3 - pop 4 - charge
                    check_min_split_size(splt, 5, cur_line, s);
                    std::pair<REAL, REAL> mr{str2real<REAL>(splt, 3, cur_line, s),
                                             str2real<REAL>(splt, 4, cur_line, s)};
                    output.m_steps.back().m_mulliken_pop_per_atom.push_back(std::move(mr));
                    output.m_steps.back().m_mulliken_spin_pop_per_atom.push_back(
                          str2real<REAL>(splt, 5, cur_line, s));
                    output.m_steps.back().m_mulliken_net_chg_per_atom.push_back(
                          str2real<REAL>(splt, 6, cur_line, s));
                  }

                continue;

              }
            //end Mulliken pop per atom

            //Hirschfield pop per atom
            if (s.find("Hirshfeld Charges") != std::string::npos) {

                for (auto i = 0; i < 2; i++) sgetline(inp, s, cur_line); //read two common lines
                output.m_steps.back().m_lowdin_pop_per_atom.reserve(output.m_tot_nat);
                output.m_steps.back().m_lowdin_net_chg_per_atom.reserve(output.m_tot_nat);
                output.m_steps.back().m_lowdin_spin_pop_per_atom.reserve(output.m_tot_nat);

                for (size_t i = 0; i < output.m_tot_nat; i++) {

                    sgetline(inp, s, cur_line);
                    std::vector<std::string_view> splt = split_sv(s, " "); // 3 - pop 4 - charge
                    check_min_split_size(splt, 5, cur_line, s);
                    std::pair<REAL, REAL> mr{str2real<REAL>(splt, 3, cur_line, s),
                                             str2real<REAL>(splt, 4, cur_line, s)};
                    output.m_steps.back().m_lowdin_pop_per_atom.push_back(std::move(mr));
                    output.m_steps.back().m_lowdin_spin_pop_per_atom.push_back(
                          str2real<REAL>(splt, 5, cur_line, s));
                    output.m_steps.back().m_lowdin_net_chg_per_atom.push_back(
                          str2real<REAL>(splt, 6, cur_line, s));
                  }

                continue;

              }
            //end Hirschfield pop per atom

            //start eigenvalues parsing
            if (s.find("Eigenvalues of the occupied subspace spin") != std::string::npos) {

                is_first_spin_subspace = s.find("1") != std::string::npos;//determine spin subspace
                sgetline(inp, s, cur_line); //read common line --------
                p_state = cp2k_output_parser_state::cp2k_op_parse_eigen_values_occ;
                continue;

              }

            if (s.find("Lowest Eigenvalues of the unoccupied subspace") != std::string::npos) {

                is_first_spin_subspace = s.find("1") != std::string::npos;//determine spin subspace
                sgetline(inp, s, cur_line); //read common line --------
                p_state = cp2k_output_parser_state::cp2k_op_parse_eigen_values_unocc;
                continue;

              }

            if (p_state == cp2k_output_parser_state::cp2k_op_parse_eigen_values_occ ||
                p_state == cp2k_output_parser_state::cp2k_op_parse_eigen_values_unocc) {

                if (s.find("Fermi") != std::string::npos || s.length() == 1 ||
                    s.length() == 2) {
                    p_state = cp2k_output_parser_state::cp2k_op_state_none;
                    continue;
                  }

                if (s.find("iter") != std::string::npos || s.find("WARNING") != std::string::npos
                    || s.find("current gradient /") != std::string::npos) {
                    continue;
                  }

                std::vector<std::string_view> splt = split_sv(s, " ");
                //fmt::print(std::cout, "{}\n", s);
                for (size_t i = 0; i < splt.size(); i++) {

                    REAL sp_eigen_value = str2real<REAL>(splt, i, cur_line, s);

                    if (p_state == cp2k_output_parser_state::cp2k_op_parse_eigen_values_occ) {
                        if (is_first_spin_subspace)
                          output.m_steps.back().m_eigen_values_spin_1_occ.push_back(
                                sp_eigen_value);
                        else
                          output.m_steps.back().m_eigen_values_spin_2_occ.push_back(
                                sp_eigen_value);
                      }

                    if (p_state == cp2k_output_parser_state::cp2k_op_parse_eigen_values_unocc) {
                        if (is_first_spin_subspace)
                          output.m_steps.back().m_eigen_values_spin_1_unocc.push_back(
                                sp_eigen_value);
                        else output.m_steps.back().m_eigen_values_spin_2_unocc.push_back(
                              sp_eigen_value);
                      }

                  }

                continue;

              }

            //end eigenvalues parsing

            // start of parsing trajectory and gradient
            if (s.find(" i =") != std::string::npos) {

                bool add_to_pos = output.m_steps.back().m_atoms_pos.empty();

                for (size_t i = 0; i < output.m_tot_nat; i++) {

                    sgetline(inp, s, cur_line);
                    std::vector<std::string_view> splt = split_sv(s, " ");
                    vector3<REAL> pg = vec_from_str_ex<REAL>(s, splt, cur_line, 1, 2, 3);
                    if (add_to_pos) output.m_steps.back().m_atoms_pos.push_back(std::move(pg));
                    else output.m_steps.back().m_atoms_grads.push_back(std::move(pg));

                  }

                //read line after coords or grads, here may be cell info
                sgetline(inp, s, cur_line);
                std::vector<std::string_view> splt = split_sv(s, " ");
                if (splt.size() == 12) {

                    vector3<REAL> c_a = vec_from_str_ex<REAL>(s, splt, cur_line, 2, 3, 4);
                    vector3<REAL> c_b = vec_from_str_ex<REAL>(s, splt, cur_line, 5, 6, 7);
                    vector3<REAL> c_c = vec_from_str_ex<REAL>(s, splt, cur_line, 8, 9, 10);

//                    fmt::print("\n cell info: {}\n", s);
//                    fmt::print("@CCD_CP2K: ca {} {} {}\n",   c_a[0], c_a[1], c_a[2]);
//                    fmt::print("@CCD_CP2K: cb {} {} {}\n",   c_b[0], c_b[1], c_b[2]);
//                    fmt::print("@CCD_CP2K: cc {} {} {}\n\n", c_c[0], c_c[1], c_c[2]);

                    auto &step = output.m_steps.back();
                    step.m_cell_is_animable = true;
                    step.m_cell[0] = std::move(c_a);
                    step.m_cell[1] = std::move(c_b);
                    step.m_cell[2] = std::move(c_c);

                  }

                continue;

              } //end of parsing trajectory and gradient

            /* tddft parsing */
            if (s.find("number   energy (eV)       x           y           z     strength (a.u.)")
                != std::string::npos) {

                sgetline(inp, s, cur_line); // read unnecessary line --------------------------
                p_state = cp2k_output_parser_state::cp2k_op_parse_tddfpt_state_en_tr_dm;
                continue;

              }

            /*
             * Section looks like:
             State    Excitation        Transition dipole (a.u.)        Oscillator
             number   energy (eV)       x           y           z     strength (a.u.)
             ------------------------------------------------------------------------
     TDDFPT|      1       0.89402   1.0262E-01  6.4435E-03  3.4425E-01   2.82732E-03
     0            1         2          3            4           5            6
            */
            if (p_state == cp2k_output_parser_state::cp2k_op_parse_tddfpt_state_en_tr_dm) {

                std::vector<std::string_view> splt = split_sv(s, " ");

                if (s.find("TDDFPT|") != std::string::npos) {

                    check_min_split_size(splt, 7, cur_line, s);

                    REAL exc_en  = str2real<REAL>(splt, 2, cur_line, s);
                    REAL dip_x   = str2real<REAL>(splt, 3, cur_line, s);
                    REAL dip_y   = str2real<REAL>(splt, 4, cur_line, s);
                    REAL dip_z   = str2real<REAL>(splt, 5, cur_line, s);
                    REAL osc_str = str2real<REAL>(splt, 6, cur_line, s);

                    tddft_transitions_t<REAL> tddft_tr_rec;
                    tddft_tr_rec.m_en_ev = exc_en;
                    tddft_tr_rec.m_osc_str = osc_str;
                    tddft_tr_rec.m_trans_dipole_moment = {dip_x, dip_y, dip_z};

                    /* placeholder from/to states*/
//                    tddft_tr_rec.m_to_state.push_back({
//                                                        output.m_tddft_trans_rec.size()+1,
//                                                        1.0
//                                                      });

                    output.m_tddft_trans_rec.push_back(std::move(tddft_tr_rec));

                  } else {
                    p_state = cp2k_output_parser_state::cp2k_op_state_none;
                  }

                continue;

              }

            /* parsing tddft`s picture of states*/
            if (p_state == cp2k_output_parser_state::cp2k_op_state_none &&
                s.find("Excitation analysis") != std::string::npos) {

                for (size_t q = 0; q < 4; q++)
                  sgetline(inp, s, cur_line); // read unnecessary line, total 5

                p_state = cp2k_output_parser_state::cp2k_op_parse_tddfpt_state_picture;
                cur_tddft_state = -1;
                continue;

              }

            if (p_state == cp2k_output_parser_state::cp2k_op_parse_tddfpt_state_picture) {

                std::vector<std::string_view> splt = split_sv(s, " ");
                auto splt_size = splt.size();

                switch (splt_size) {

                  case 0 : {
                      p_state = cp2k_output_parser_state::cp2k_op_state_none;
                      break;
                    }

                  case 1 : {
//                      fmt::print(std::cout, "output.m_tddft.size = {}, "
//                                            "line = \"{}\", "
//                                            "cur_tddft_state = {}\n",
//                                 output.m_tddft_trans_rec.size(),
//                                 s,
//                                 cur_tddft_state);
                      cur_tddft_state++;
                      break;
                    }

                  case 5 : {

                      bool is_alpha_lhs = splt[1].find("alpha") != std::string::npos;
                      bool is_alpha_rhs = splt[3].find("alpha") != std::string::npos;

                      size_t lhs_orb_num = str2int<REAL>(splt, 0, cur_line, s);
                      size_t rhs_orb_num = str2int<REAL>(splt, 2, cur_line, s);

                      REAL exc_ampl = str2real<REAL>(splt, 4, cur_line, s);

                      output.m_tddft_trans_rec[cur_tddft_state].m_transition.push_back({
                        lhs_orb_num, is_alpha_lhs ? ccd_spin_e::spin_alpha : ccd_spin_e::spin_beta,
                        rhs_orb_num, is_alpha_rhs ? ccd_spin_e::spin_alpha : ccd_spin_e::spin_beta,
                        exc_ampl
                      });

                      break;

                    }

                  default : {
                      p_state = cp2k_output_parser_state::cp2k_op_state_none;
                      break;
                    }

                  }

                continue;

              }

            /* end of tddft parsing */

          } // end of is_init_parsed == true

      }

    if (output.m_tot_nat == 0 || !is_init_parsed)
      throw parsing_error_t(cur_line, s, "Invalid CP2K output file");

  }

} // namespace qpp

#endif
