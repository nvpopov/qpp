#ifndef QPP_CP2K_CCD_IO_H
#define QPP_CP2K_CCD_IO_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <geom/geom.hpp>
#include <geom/geom_anim.hpp>
#include <io/comp_chem_data.hpp>

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
    cp2k_op_parse_eigen_values_unocc
  };

  template<class REAL>
  void read_ccd_from_cp2k_output(std::basic_istream<CHAR,TRAITS> &inp,
                                 comp_chem_program_data_t<REAL> &output) {

    std::locale loc1("C");
    std::string s;

    cp2k_output_parser_state p_state{cp2k_output_parser_state::cp2k_op_state_none};
    bool is_init_parsed{false};

    output.m_DIM = 0;
    output.m_comp_chem_program = comp_chem_program_t::pr_cp2k;
    bool is_fisrt_spin_subspace{false};

    while (!inp.eof()) {

        std::getline(inp, s);
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
                  output.m_run_t = comp_chem_program_run_t::rt_geo_opt;
                if (s.find("ENERGY") != std::string::npos)
                  output.m_run_t = comp_chem_program_run_t::rt_energy;
                if (s.find("GRADIENT") != std::string::npos)
                  output.m_run_t = comp_chem_program_run_t::rt_grad;
                continue;
              } // End of Parse run type

            //Parse cell info
            if (s.find("CELL_TOP| Vector") != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                //int cell_v_idx = 0;

                if (splt[2] == "a") output.m_DIM = 1;
                if (splt[2] == "b") output.m_DIM = 2;
                if (splt[2] == "c") output.m_DIM = 3;

                vector3<REAL> cell_v{std::stod(splt[4].data()), std::stod(splt[5].data()),
                      std::stod(splt[6].data())};

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
                std::getline(inp, s); //read next line "- Atoms:"
                if (s.find("Atoms:") != std::string::npos) {
                    std::vector<std::string_view> splt = split_sv(s, " ");
                    output.m_tot_nat = std::stoi(splt[2].data());
                    output.m_init_atoms_names.reserve(output.m_tot_nat);
                    output.m_init_atoms_pos.reserve(output.m_tot_nat);
                  }
                continue;
              }

            if (s.find("DFT| Number of spin states") != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                output.m_n_spin_states = std::stoi(splt[5].data());
                if (output.m_n_spin_states == 1) output.m_is_unrestricted = false;
                else output.m_is_unrestricted = true;
                continue;
              }

            if (s.find("DFT| Multiplicity") != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                output.m_mult = std::stoi(splt[2].data());
                continue;
              }

            if (s.find("DFT| Charge") != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                output.m_tot_charge = std::stod(splt[2].data());
                continue;
              }

            if (s.find("MODULE QUICKSTEP:  ATOMIC COORDINATES IN angstrom") != std::string::npos) {
//                  MODULE QUICKSTEP:  ATOMIC COORDINATES IN angstrom
//
//                   Atom  Kind  Element       X           Y           Z          Z(eff)       Mass
//
//                        1     1 Ba  56    0.000000    0.000000    0.000000     10.00     137.3270
//  idx                   0     1 2   3     4           5           6            7         8

                for (int i = 0; i < 3; i++) std::getline(inp, s); //read 3 lines
                for (int i = 0; i < output.m_tot_nat; i++) {
                    std::getline(inp, s);
                    std::vector<std::string_view> splt = split_sv(s, " ");
                    output.m_init_atoms_names.push_back(std::string(splt[2]));
                    vector3<REAL> pos{std::stod(splt[4].data()), std::stod(splt[5].data()),
                          std::stod(splt[6].data())};
                    output.m_init_atoms_pos.push_back(std::move(pos));
                  }
                is_init_parsed = true;
                continue;
              }

          } // end of !is_init_parsed

        // start of is_init_parsed == true
        if (is_init_parsed) {
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

                if (s.find("HFX_") != std::string::npos || s.find("-----") != std::string::npos) {
                    continue;
                  }

                if (s.find("P_Mix") != std::string::npos || s.find("Diag.") != std::string::npos ||
                    s.find("OT") != std::string::npos || s.find("DIIS") != std::string::npos) {
                    //fmt::print(std::cout, "{}\n", s);
                    std::vector<std::string_view> splt = split_sv(s, " ");
                    size_t tot_l = splt.size();

                    if (splt[1] == "OT") {
                        comp_chem_program_scf_step_info_t<REAL> scf_info;
                        scf_info.m_iter = std::stoi(splt[0].data());
                        if (tot_l == 8) scf_info.m_toten = std::stod(splt[6].data());
                        if (tot_l == 6) scf_info.m_toten = std::stod(splt[5].data());
                        output.m_steps.back().m_scf_steps.push_back(std::move(scf_info));
                      }
                    continue;
                  }
              }

            //mulliken pop per atom
            if (s.find("Mulliken Population Analysis") != std::string::npos) {
                for (auto i = 0; i < 2; i++) std::getline(inp, s); //read two common lines
                output.m_steps.back().m_mulliken_pop_per_atom.reserve(output.m_tot_nat);
                for (size_t i = 0; i < output.m_tot_nat; i++) {
                    std::getline(inp, s);
                    std::vector<std::string_view> splt = split_sv(s, " "); // 3 - pop 4 - charge
                    std::pair<REAL, REAL> mr{std::stod(splt[3].data()), std::stod(splt[4].data())};
                    output.m_steps.back().m_mulliken_pop_per_atom.push_back(std::move(mr));
                  }
                continue;
              }
            //end mulliken pop per atom

            //start eigenvalues parsing
            if (s.find("Eigenvalues of the occupied subspace spin") != std::string::npos) {
                is_fisrt_spin_subspace = s.find("1") != std::string::npos;//determine spin subspace
                std::getline(inp, s); //read common line --------
                p_state = cp2k_output_parser_state::cp2k_op_parse_eigen_values_occ;
                continue;
              }

            if (s.find("Lowest Eigenvalues of the unoccupied subspace") != std::string::npos) {
                is_fisrt_spin_subspace = s.find("1") != std::string::npos;//determine spin subspace
                std::getline(inp, s);//read common line --------
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

                if (s.find("iter") != std::string::npos) {
                    continue;
                  }

                std::vector<std::string_view> splt = split_sv(s, " ");
                //fmt::print(std::cout, "{}\n", s);
                for (size_t i = 0; i < splt.size(); i++) {
                    REAL sp_eigen_value = std::stod(splt[i].data());

                    if (p_state == cp2k_output_parser_state::cp2k_op_parse_eigen_values_occ) {
                        if (is_fisrt_spin_subspace)
                          output.m_steps.back().m_eigen_values_spin_1_occ.push_back(sp_eigen_value);
                        else
                          output.m_steps.back().m_eigen_values_spin_2_occ.push_back(sp_eigen_value);
                      }

                    if (p_state == cp2k_output_parser_state::cp2k_op_parse_eigen_values_unocc) {
                        if (is_fisrt_spin_subspace)
                          output.m_steps.back().m_eigen_values_spin_1_unocc.push_back(
                                sp_eigen_value);
                        else
                          output.m_steps.back().m_eigen_values_spin_2_unocc.push_back(
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
                    std::getline(inp, s);
                    std::vector<std::string_view> splt = split_sv(s, " ");
                    REAL x = std::stod(splt[1].data());
                    REAL y = std::stod(splt[2].data());
                    REAL z = std::stod(splt[3].data());
                    vector3<REAL> pg{x, y, z};
                    if (add_to_pos) output.m_steps.back().m_atoms_pos.push_back(std::move(pg));
                    else output.m_steps.back().m_atoms_grads.push_back(std::move(pg));
                  }
              } //end of parsing trajectory and gradient

          } // end of is_init_parsed == true

      }

  }

}

#endif
