#ifndef QPP_ORCA_CCD_IO_H
#define QPP_ORCA_CCD_IO_H

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

  enum orca_parser_state_e {

    orca_parse_none,
    orca_parse_init_coords,
    orca_parse_scf_section,
    orca_parse_geopt_coords,
    orca_parse_grads,
    orca_parse_tddft_states,
    orca_parse_tddft_tran_osc,
    orca_parse_orbital_energies

  };

  template<class REAL>
  void read_ccd_from_orca_output(std::basic_istream<CHAR_EX,TRAITS> &inp,
                                 comp_chem_program_data_t<REAL> &output) {

    std::locale loc1("C");
    std::string s;

    output.m_DIM = 0;
    output.m_comp_chem_program = comp_chem_program_e::pr_orca;

    orca_parser_state_e pstate{orca_parser_state_e::orca_parse_none};
    bool is_init_crds_parsed{false};

    uint64_t cur_line{0};

    // counter for reading tddft oscillator strength section
    size_t tddft_osc_str_trdpm_c{0};

    output.m_run_t = comp_chem_program_run_e::rt_energy;

    while (!inp.eof()) {

        sgetline(inp, s, cur_line);

        if (inp.eof()) continue;

        if (s.find("* Single Point Calculation *") != std::string::npos) {
            output.m_run_t = comp_chem_program_run_e::rt_energy;
            continue;
          }

        if (s.find("* Geometry Optimization Run *") != std::string::npos) {
            output.m_run_t = comp_chem_program_run_e::rt_geo_opt;
            continue;
          }

        if (!is_init_crds_parsed && s.find("CARTESIAN COORDINATES (A.U.)") != std::string::npos) {

            pstate = orca_parser_state_e::orca_parse_init_coords;
            sgetline(inp, s, cur_line);
            sgetline(inp, s, cur_line);
            continue;

          }

        if (pstate == orca_parser_state_e::orca_parse_init_coords) {

            if (s == "" || s.find("core") != std::string::npos) {
                pstate = orca_parser_state_e::orca_parse_none;
                is_init_crds_parsed = true;
                continue;
              }

            std::vector<std::string_view> splt = split_sv(s, " ");
            check_min_split_size(splt, 8, cur_line, s);

//            NO LB      ZA    FRAG     MASS         X           Y           Z
//             0 Br   25.0000*   0    79.900   -4.771181   -3.484277    9.467528
//             0  1      2       3      4          5           6           7
            std::string at_name = std::string(splt[1]);
            output.m_init_anames.push_back(std::move(at_name));
            output.m_init_achg.push_back(str2real(splt, 2, cur_line, s));
            output.m_init_apos.push_back({
                                           str2real(splt, 5, cur_line, s) * bohr_to_angs,
                                           str2real(splt, 6, cur_line, s) * bohr_to_angs,
                                           str2real(splt, 7, cur_line, s) * bohr_to_angs
                                         });

            continue;

          }

        if (s.find("Hartree-Fock type      HFTyp") != std::string::npos) {
//             Hartree-Fock type      HFTyp           .... UHF
//                0           1         2               3   4
            std::vector<std::string_view> splt = split_sv(s, " ");
            check_min_split_size(splt, 5, cur_line, s);
            if (splt[4] == "UHF") output.m_is_unrestricted = true;
            continue;
          }

        if (s.find("Multiplicity           Mult") != std::string::npos) {
//           Multiplicity    Mult      ....    2
//                0           1         2      3
            std::vector<std::string_view> splt = split_sv(s, " ");
            check_min_split_size(splt, 4, cur_line, s);
            output.m_mult = str2int(splt, 3, cur_line, s);
            continue;
          }

        if (s.find("Number of Electrons    NEL") != std::string::npos) {
//           Number of Electrons    NEL             ....  657
//                0  1     2         3                4    5
            std::vector<std::string_view> splt = split_sv(s, " ");
            check_min_split_size(splt, 6, cur_line, s);
            output.m_tot_nelec = str2int(splt, 5, cur_line, s);
            continue;
          }

        if (s.find("SCF ITERATIONS") != std::string::npos) {

            pstate = orca_parser_state_e::orca_parse_scf_section;
            sgetline(inp, s, cur_line);
            sgetline(inp, s, cur_line);

            output.m_steps.resize(output.m_steps.size() + 1);
            //fmt::print(std::cout, "output.m_steps.resize(output.m_steps.size() + 1)\n");
            continue;

          }

        if (pstate == orca_parser_state_e::orca_parse_scf_section &&
            (s.find("****************") != std::string::npos || s.size()==1)) {
            pstate = orca_parser_state_e::orca_parse_none;
            continue;
          }

        if (pstate == orca_parser_state_e::orca_parse_scf_section &&
            s.find("ITER") == std::string::npos &&
            s.find("***  Starting") == std::string::npos &&
            s.find("***Turning") == std::string::npos &&
            s.find("*** Restarting") == std::string::npos &&
            s.find("*** Resetting") == std::string::npos &&
            s.find("***DIIS") == std::string::npos &&
            s.find("SCF CONVERGED") == std::string::npos &&
            s.find("*** Initiating") == std::string::npos &&
            s.find("*** Removing") == std::string::npos &&
            s.find("**** Energy") == std::string::npos &&
            s.find(":") == std::string::npos) {

//            ITER       Energy         Delta-E        Max-DP      RMS-DP      [F,P]     Damp
//              0  -8136.7504381034   0.000000000000458.80750002  0.79296675  1.9269204 0.7000
//              0     1                    2           3             4           5         6
            std::vector<std::string_view> splt = split_sv(s, " ");
            if (splt.size() >= 6) {

                //fmt::print(std::cout, "!!{}\n", s);
                comp_chem_program_scf_step_info_t<REAL> scf_info;
                scf_info.m_iter = std::stoi(splt[0].data());
                scf_info.m_toten = str2real<REAL>(splt, 1, cur_line, s);
                output.m_steps.back().m_scf_steps.push_back(std::move(scf_info));

              }
            //check_min_split_size(splt, 2, cur_line, s);
            continue;

          }

        // geopt section begin

        if (s.find("CARTESIAN COORDINATES (ANGSTROEM)") != std::string::npos &&
            !output.m_steps.empty()) {

            sgetline(inp, s, cur_line);

            output.m_steps.back().m_atoms_pos.resize(output.m_init_anames.size());

            for (size_t i = 0; i < output.m_init_anames.size(); i++) {

                sgetline(inp, s, cur_line);

                std::vector<std::string_view> splt = split_sv(s, " ");
                check_min_split_size(splt, 4, cur_line, s);

                output.m_steps.back().m_atoms_pos[i] = {
                  str2real(splt, 1, cur_line, s),
                  str2real(splt, 2, cur_line, s),
                  str2real(splt, 3, cur_line, s),
                };

              }

            continue;

          }

        // geopt section end

        // read gradient begin
        if (s.find("CARTESIAN GRADIENT") != std::string::npos && !output.m_steps.empty()) {

            sgetline(inp, s, cur_line);
            sgetline(inp, s, cur_line);

            output.m_steps.back().m_atoms_grads.resize(output.m_init_anames.size());

            for (size_t i = 0; i < output.m_init_anames.size(); i++) {

                sgetline(inp, s, cur_line);

                std::vector<std::string_view> splt = split_sv(s, " ");
                check_min_split_size(splt, 4, cur_line, s);

                output.m_steps.back().m_atoms_grads[i] = {
                  str2real(splt, 3, cur_line, s),
                  str2real(splt, 4, cur_line, s),
                  str2real(splt, 5, cur_line, s),
                };

              }

            continue;

          }
        // read gradient end

        // read orbital energies
        if (s.find("ORBITAL ENERGIES") != std::string::npos) {
            pstate = orca_parser_state_e::orca_parse_orbital_energies;
            for (auto i = 0; i < 3; i++) sgetline(inp, s, cur_line);
            continue;
          }

        if (pstate == orca_parser_state_e::orca_parse_orbital_energies) {

            std::vector<std::string_view> splt = split_sv(s, " ");

            if (splt.size() < 2) {
                pstate = orca_parser_state_e::orca_parse_none;
                continue;
              }

            if (!output.m_steps.empty()) {

                REAL occ_ = str2real(splt, 1, cur_line, s);
                REAL e_eV = str2real(splt, 3, cur_line, s);

                if (std::abs(occ_) > 0.01) {
                    output.m_steps.back().m_eigen_values_spin_1_occ.push_back(e_eV);
                  } else {
                    output.m_steps.back().m_eigen_values_spin_1_unocc.push_back(e_eV);
                  }

              }

            continue;

          }

        // end read orbital energies

        // begin read mulliken charges

        if (s.find("MULLIKEN ATOMIC CHARGES") != std::string::npos && !output.m_steps.empty()) {

//            -----------------------
//            MULLIKEN ATOMIC CHARGES
//            -----------------------
//               0 H :    0.105884
//               1 N :   -0.221219
//               0 1 2    3
            sgetline(inp, s, cur_line);

            output.m_steps.back().m_mulliken_net_chg_per_atom.resize(output.m_init_anames.size());

            for (size_t i = 0; i < output.m_init_anames.size(); i++) {

                sgetline(inp, s, cur_line);
                std::vector<std::string_view> splt = split_sv(s, " ");

                output.m_steps.back().m_mulliken_net_chg_per_atom[i] =
                    str2real(splt, 3, cur_line, s);

              }

            continue;

          }

        // end read mulliken charges

        // tddft section begin

        if (s.find("TD-DFT/TDA EXCITED STATES") != std::string::npos) {
            pstate = orca_parser_state_e::orca_parse_tddft_states;
            continue;
          }

        if (s.find("ABSORPTION SPECTRUM VIA TRANSITION ELECTRIC DIPOLE MOMENTS")
            != std::string::npos) {

//            -----------------------------------------------------------------------------
//                     ABSORPTION SPECTRUM VIA TRANSITION ELECTRIC DIPOLE MOMENTS
//            ----------------------------------------------------------------------------- 1
//            State   Energy    Wavelength  fosc         T2        TX        TY        TZ   2
//                    (cm-1)      (nm)                 (au**2)    (au)      (au)      (au)  3
//            ----------------------------------------------------------------------------- 4

            for (auto i = 0; i < 4; i++) sgetline(inp, s, cur_line);
            pstate = orca_parser_state_e::orca_parse_tddft_tran_osc;
            tddft_osc_str_trdpm_c = 0;
            continue;

          }

        if (pstate == orca_parser_state_e::orca_parse_tddft_states) {

            if (s.find("-----------------------------") != std::string::npos) {
                pstate = orca_parser_state_e::orca_parse_none;
                continue;
              }

            if (s.find("STATE ") != std::string::npos) {

                // STATE  1:  E=   0.060753 au      1.653 eV    13333.8 cm**-1
                //   0    1   2       3     4          5  6      7     8
                std::vector<std::string_view> splt = split_sv(s, " ");
                check_min_split_size(splt, 7, cur_line, s);
                tddft_transitions_t<REAL> tddft_trans;
                tddft_trans.m_en_ev = str2real(splt, 5, cur_line, s);
                output.m_tddft_trans_rec.push_back(std::move(tddft_trans));

                continue;

              }

            if (s.find("->") != std::string::npos) {

                //328a -> 329a  :     0.964957 (c= -0.98232241)
                // 0   1   2    3         4     5    6
                std::vector<std::string_view> splt = split_sv(s, " ");
                check_min_split_size(splt, 7, cur_line, s);

                std::string st1 = std::string(splt[0]);
                std::string st2 = std::string(splt[2]);

                std::string st1_wpf = st1.substr(0, st1.size()-1);
                std::string st2_wpf = st2.substr(0, st2.size()-1);

                tddft_transition_rec_t<REAL> tr_rec;
                tr_rec.m_from_spin = st1.find("a") != std::string::npos ?
                                                      ccd_spin_e::spin_alpha :
                                                      ccd_spin_e::spin_beta;

                tr_rec.m_to_spin   = st2.find("a") != std::string::npos ?
                                                      ccd_spin_e::spin_alpha :
                                                      ccd_spin_e::spin_beta;

                tr_rec.m_from = std::stoi(st1_wpf);
                tr_rec.m_to = std::stoi(st2_wpf);
                tr_rec.m_amplitude = str2real(splt, 4, cur_line, s);
                //tr_rec.m_from = str2int(splt, 0, )

                output.m_tddft_trans_rec.back().m_transition.push_back(std::move(tr_rec));

              }

            continue;

          }

        if (pstate == orca_parse_tddft_tran_osc) {

             std::vector<std::string_view> splt = split_sv(s, " ");

             if (splt.size() <= 2) {
                 pstate = orca_parser_state_e::orca_parse_none;
                 continue;
               }

//             State   Energy    Wavelength  fosc         T2        TX        TY        TZ
//                     (cm-1)      (nm)                 (au**2)    (au)      (au)      (au)
//             -----------------------------------------------------------------------------
//                1   13333.8    750.0   0.151048483   3.72938  -0.00002   1.09931   1.58774
//                0      1        2          3           4         5         6          7
             output.m_tddft_trans_rec[tddft_osc_str_trdpm_c].m_osc_str =
                 str2real(splt, 3, cur_line, s);

             for (size_t i = 0; i < 3; i++)
               output.m_tddft_trans_rec[tddft_osc_str_trdpm_c].m_trans_dipole_moment[0 + i] =
                   str2real(splt, 5 + i, cur_line, s);

             tddft_osc_str_trdpm_c++;
             continue;

          }

        // tddft section end

      } // end of while loop

  } // end of function

} // namespace qpp

#endif
