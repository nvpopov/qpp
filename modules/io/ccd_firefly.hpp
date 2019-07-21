#ifndef QPP_GMS_FF_IO_H
#define QPP_GMS_FF_IO_H

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
#include <array>

namespace qpp {

  enum pcg_ff_p_state {
    s_none,
    s_init_read_crds_header,
    s_init_read_crds,
    s_init_tot_num_atoms,
    s_init_tot_num_electorns,
    s_init_tot_charge,
    s_init_mult,
    s_init_num_alpha_beta,
    s_init_control_sect,
    s_scf_parsing,
    s_coord_parsing,
    s_grad_parsing,
    s_eigen_vectors_section_parsing,
    s_eigen_vectors_section_parsing_idx,
    s_eigen_vectors_section_parsing_energy,
    s_eigen_vectors_section_parsing_sym,
    s_eigen_vectors_section_parsing_decomposition,
    s_mulliken_lowdin_pop_with_charges,
    s_electrostatic_moments,
    s_vib_header,
    s_vib_general,
    s_vib_displ
  };

  const std::string s_init_read_crds_header_str =
      "ATOM      ATOMIC                      COORDINATES (BOHR)";

  const std::string s_init_read_crds_after_header_str =
      "CHARGE         X                   Y                   Z";

  const std::string s_init_tot_num_electons_str =
      "NUMBER OF ELECTRONS                 =";

  const std::string s_init_tot_charge_str =
      "CHARGE OF MOLECULE                  =";

  const std::string s_init_tot_mult_str =
      "STATE MULTIPLICITY                  =";

  const std::string s_init_tot_num_occup_alpha =
      "NUMBER OF OCCUPIED ORBITALS (ALPHA) =";

  const std::string s_init_tot_num_occup_beta =
      "NUMBER OF OCCUPIED ORBITALS (BETA ) =";

  const std::string s_init_tot_num_atoms_str =
      "TOTAL NUMBER OF ATOMS               =";

  const std::string s_init_control_section_str =
      "$CONTRL OPTIONS";

  const std::string s_scf_parsing_header_str =
      "ITER EX DEM  TOTAL ENERGY      E CHANGE  DENSITY CHANGE     ORB. GRAD";

  const std::string s_scf_parsing_header_str_v2 =
      "ITER EX DEM  TOTAL ENERGY      E CHANGE  DENSITY CHANGE    DIIS ERROR";

  const std::string s_coordinates_header_str =
      "COORDINATES OF ALL ATOMS ARE (ANGS)";

  const std::string s_eq_geom_located_str =
      "***** EQUILIBRIUM GEOMETRY LOCATED *****";

  const std::string s_terminated_normally_str =
      "EXECUTION OF FIREFLY TERMINATED NORMALLY";

  const std::string s_gradients_header_str =
      "ATOM     ZNUC       DE/DX         DE/DY         DE/DZ";

  const std::string s_eigen_vectors_section =
      "          EIGENVECTORS";

  const std::string s_eigen_vectors_secton_molecular_orbitals =
      "          MOLECULAR ORBITALS";

  const std::string s_eigen_end_of =
      "...... END";

  const std::string s_eigen_end_ff_outdated =
      "WARNING! THIS VERSION OF";

  const std::string s_eigen_end_ff_outdated_v2 =
      " WARNING! YOU ARE USING OUTDATED";

  const std::string s_eigen_end_ff_outdated_v3 =
      " WARNING! ";

  const std::string s_mulliken_lowdin_section_str =
      "TOTAL MULLIKEN AND LOWDIN ATOMIC POPULATIONS";

  const std::string s_electrostatic_moments_str =
      "          ELECTROSTATIC MOMENTS";

  const std::string s_vib_header_str =
      "     FREQUENCIES IN CM**-1, IR INTENSITIES IN DEBYE**2/AMU-ANGSTROM**2";

  const std::string s_vib_displ_stop_str =
      "REFERENCE ON SAYVETZ CONDITIONS";

  template<class REAL>
  void read_ccd_from_firefly_output(std::basic_istream<CHAR_EX,TRAITS> & inp,
                                    comp_chem_program_data_t<REAL> &output) {

    std::locale loc1("C");
    std::string s;

    pcg_ff_p_state p_state{s_none};

    bool b_init_parsed{false};
    size_t cur_step{0};
    bool b_atoms_bootstraped{false};
    int vib_line_size{0};
    int vib_line_seek{0};

    output.m_DIM = 0;
    output.m_comp_chem_program = comp_chem_program_e::pr_firefly;

    uint64_t cur_line{0};

    while (!inp.eof()) {

        sgetline(inp, s, cur_line);

        //start parsing initial section
        if (!b_init_parsed) {

            //reading initial coordinates
            if (p_state == pcg_ff_p_state::s_none &&
                s.find(s_init_read_crds_header_str) != std::string::npos) {
                p_state = pcg_ff_p_state::s_init_read_crds_header;
                continue;
              }

            if (p_state == pcg_ff_p_state::s_init_read_crds_header &&
                s.find(s_init_read_crds_after_header_str)!= std::string::npos) {
                p_state = pcg_ff_p_state::s_init_read_crds;
                continue;
              }

            if (p_state == pcg_ff_p_state::s_init_read_crds) {
                std::vector<std::string_view> splt = split_sv(s, " ");

                if (splt.size() != 5) {
                    p_state = pcg_ff_p_state::s_none;
                    b_atoms_bootstraped = true;
                  } else {

                    std::array<REAL, 4> _qxyz;
                    for (int i = 0; i < 4; i++)
                      _qxyz[i] = str2real(splt, i + 1, cur_line, s);

                    if (!output.m_steps.empty()) {
                        vector3<REAL> _pos{_qxyz[1], _qxyz[2], _qxyz[3]};
                        output.m_steps[cur_step].m_atoms_pos.push_back(_pos);
                      }
                    else {
                        vector3<REAL> _pos{_qxyz[1], _qxyz[2], _qxyz[3]};
                        output.m_init_apos.push_back(_pos*bohr_to_angs);
                        output.m_init_achg.push_back(_qxyz[0]);
                        check_min_split_size(splt, 1, cur_line, s);
                        std::string at_name = std::string(splt[0]);
                        output.m_init_anames.push_back(std::move(at_name));
                      }
                  }

                continue;
              }
            //end of reading initial coordinates

            //total number of electrons in init section
            if (s.find(s_init_tot_num_electons_str) != std::string::npos) {

                std::vector<std::string_view> splt = split_sv(s, " ");
                output.m_tot_nelec = str2int(splt, 4, cur_line, s);
                continue;
              }

            //total charge in init section
            if (s.find(s_init_tot_charge_str) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                output.m_tot_charge = str2real(splt, 4, cur_line, s);
                continue;
              }

            //multiplicity in init section
            if (s.find(s_init_tot_mult_str) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                output.m_mult = str2int(splt, 3, cur_line, s);;
                continue;
              }

            //num occup alpha in init section
            if (s.find(s_init_tot_num_occup_alpha) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                output.m_n_alpha = str2int(splt, 6, cur_line, s);
                output.m_is_unrestricted = true;
                continue;
              }

            //num occup beta in init section
            if (s.find(s_init_tot_num_occup_beta) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                output.m_n_beta = str2int(splt, 7, cur_line, s);;
                output.m_is_unrestricted = true;
                continue;
              }

            //total atoms in init section
            if (s.find(s_init_tot_num_atoms_str) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                output.m_tot_nat = str2int(splt, 5, cur_line, s);
                continue;
              }

            if (s.find(s_init_control_section_str) != std::string::npos) {

                sgetline(inp, s, cur_line); // read -------
                sgetline(inp, s, cur_line); // SCFTYP=RHF RUNTYP=OPTIMIZE EXETYP=RUN
                std::vector<std::string_view> splt = split_sv(s, " ");

                if (splt.size() >= 0) {
                    if (splt[0] == "SCFTYP=RHF") output.m_is_unrestricted = false;
                    if (splt[0] == "SCFTYP=UHF") output.m_is_unrestricted = true;
                  }

                if (splt.size() >= 1) {
                    if (splt[1] == "RUNTYP=OPTIMIZE")
                      output.m_run_t = comp_chem_program_run_e::rt_geo_opt;
                    if (splt[1] == "RUNTYP=ENERGY")
                      output.m_run_t = comp_chem_program_run_e::rt_energy;
                    if (splt[1] == "RUNTYP=GRADIENT")
                      output.m_run_t = comp_chem_program_run_e::rt_grad;
                    if (splt[1] == "RUNTYP=HESSIAN")
                      output.m_run_t = comp_chem_program_run_e::rt_vib;
                    if (splt[1] == "RUNTYP=RAMAN")
                      output.m_run_t = comp_chem_program_run_e::rt_raman;
                  }

                b_init_parsed = true;
                p_state = pcg_ff_p_state::s_none;
                continue;
              }

          } //end parsing initial section

        //start parsing calc data
        if (p_state == s_none &&
            (s.find(s_scf_parsing_header_str) != std::string::npos ||
             s.find(s_scf_parsing_header_str_v2) != std::string::npos)) {
            p_state = pcg_ff_p_state::s_scf_parsing;
            output.m_steps.resize(output.m_steps.size() + 1);
            cur_step = output.m_steps.size() - 1;
            continue;
          }

        //parsing scf iter
        if (p_state == pcg_ff_p_state::s_scf_parsing) {
            //std::cout << s << std::endl;
            std::vector<std::string_view> splt = split_sv(s, " ");
            if (splt.size() >= 7 && s.find("FINAL") == std::string::npos &&
                s.find("INITIATING") == std::string::npos) {
                //fill scf step info
                comp_chem_program_scf_step_info_t<REAL> _scf_step;

                std::array<int, 3> en_line_i;
                for (int i = 0; i < 3; i++) en_line_i[i] = str2int(splt, i, cur_line, s);

                std::array<REAL, 4> en_line_f;
                for (int i = 0; i < 4; i++) en_line_f[i] = str2real(splt, i + 3, cur_line, s);

                _scf_step.m_iter = en_line_i[0];
                _scf_step.m_ex = en_line_i[1];
                _scf_step.m_dem = en_line_i[2];

                _scf_step.m_toten = en_line_f[0];
                _scf_step.m_e_change = en_line_f[1];
                _scf_step.m_d_change = en_line_f[2];
                _scf_step.m_generic_error = en_line_f[3];

                output.m_steps[cur_step].m_scf_steps.push_back(std::move(_scf_step));

              }

            if (s.find("-----------------") != std::string::npos || s.length() == 1) {
                if (!output.m_steps[cur_step].m_scf_steps.empty())
                  output.m_steps[cur_step].m_toten =
                      output.m_steps[cur_step].m_scf_steps.back().m_toten;
                p_state = pcg_ff_p_state::s_none;
              }
            continue;
          }

        //Eigenvectors sections begin
        if (s.find(s_eigen_vectors_section) != std::string::npos ||
            s.find(s_eigen_vectors_secton_molecular_orbitals) != std::string::npos) {
            //std::cout << s << std::endl;
            p_state = pcg_ff_p_state::s_eigen_vectors_section_parsing_idx;
            sgetline(inp, s, cur_line); //read ------------
            sgetline(inp, s, cur_line); //read empty line
            //std::cout << s << std::endl;
            continue;
          }

        if (p_state == pcg_ff_p_state::s_eigen_vectors_section_parsing_idx) {
            //skip on final iteration
            // 60  H  20  S  -0.351994  -0.322156   0.298750   0.258882   0.379640


            //------------------------------
            //properties for the RHF density
            if (s.length() == 1 || s.find(s_eigen_end_ff_outdated) != std::string::npos ||
                s.find(s_eigen_end_ff_outdated_v2) != std::string::npos ||
                s.find(s_eigen_end_ff_outdated_v3) != std::string::npos) {
                p_state = pcg_ff_p_state::s_none;
                continue;
              }
            p_state = pcg_ff_p_state::s_eigen_vectors_section_parsing_energy;
            continue;
          }

        if (p_state == pcg_ff_p_state::s_eigen_vectors_section_parsing_energy) {
            std::vector<std::string_view> splt = split_sv(s, " ");
            for (size_t i = 0; i < splt.size(); i++)
              output.m_steps.back().m_eigen_values_spin_1_occ.push_back(
                    str2real(splt, i, cur_line, s));
            p_state = pcg_ff_p_state::s_eigen_vectors_section_parsing_sym;
            continue;
          }

        if (p_state == pcg_ff_p_state::s_eigen_vectors_section_parsing_sym) {
            p_state = pcg_ff_p_state::s_eigen_vectors_section_parsing_decomposition;
            continue;
          }

        if (p_state == pcg_ff_p_state::s_eigen_vectors_section_parsing_decomposition) {
            if (s.find(s_eigen_end_of) != std::string::npos) {
                p_state = pcg_ff_p_state::s_none;
                continue;
              }
            if (s.length() == 1) {
                p_state = pcg_ff_p_state::s_eigen_vectors_section_parsing_idx;
                continue;
              }
            continue;
          }

        //Eigenvectors section end

        if (s.find(s_mulliken_lowdin_section_str) != std::string::npos) {
            sgetline(inp, s, cur_line);
            p_state = pcg_ff_p_state::s_mulliken_lowdin_pop_with_charges;
            continue;
          }

        if (p_state == pcg_ff_p_state::s_mulliken_lowdin_pop_with_charges) {

            std::vector<std::string_view> splt = split_sv(s, " ");
            if (splt.size() != 6) {
                p_state = pcg_ff_p_state::s_none;
                continue;
              }

            std::array<REAL, 4> pa;
            for (int i = 0; i < 4; i++) pa[i] = str2real(splt, i + 2, cur_line, s);

            output.m_steps[cur_step].m_mulliken_pop_per_atom.push_back(
                  std::pair<REAL, REAL>(pa[0], pa[1]));
            output.m_steps[cur_step].m_lowdin_pop_per_atom.push_back(
                  std::pair<REAL, REAL>(pa[2], pa[3]));

            continue;

          }

        if (s.find(s_electrostatic_moments_str) != std::string::npos) {
            for (int i = 0 ; i < 5; i++) sgetline(inp, s, cur_line);
            p_state = pcg_ff_p_state::s_electrostatic_moments;
            continue;
          }

        if (p_state == pcg_ff_p_state::s_electrostatic_moments) {

            std::vector<std::string_view> splt = split_sv(s, " ");

            if (splt.size() != 4) {
                p_state = pcg_ff_p_state::s_none;
                continue;
              }

            std::array<REAL, 3> dv;
            for (int i = 0; i < 3; i++) dv[i] = str2real(splt, i, cur_line, s);

            output.m_steps[cur_step].m_dipole_moment = vector3<REAL>(dv[0], dv[1], dv[2]);
            p_state = pcg_ff_p_state::s_none;

            continue;

          }

        //parsing vibrations
        if (s.find(s_vib_header_str) != std::string::npos) {
            //header scenario
            //run type == vib:
            //    FREQUENCIES IN CM**-1, IR INTENSITIES IN DEBYE**2/AMU-ANGSTROM**2
            //newline
            //
            //run type == raman:
            //FREQUENCIES IN CM**-1, IR INTENSITIES IN DEBYE**2/AMU-ANGSTROM**2
            //RAMAN ACTIVITIES  IN ANGSTROM**4/AMU, DEPOLARIZATIONS ARE DIMENSIONLESS
            //newline
            //

            if (output.m_run_t == comp_chem_program_run_e::rt_raman) sgetline(inp, s, cur_line);
            sgetline(inp, s, cur_line); //read empty line
            p_state = pcg_ff_p_state::s_vib_general;
            continue;
          }

        if (p_state == pcg_ff_p_state::s_vib_general) {
            if (s.find(s_vib_displ_stop_str) != std::string::npos) {
                p_state = pcg_ff_p_state::s_none;
                continue;
              }

            // for rt = vib
            //like this:
            //            1           2           3           4           5
            //FREQUENCY:         5.89        1.44        0.01        0.01        0.01
            //REDUCED MASS:      3.94009     4.46293     6.50413     6.50391     6.50391
            //IR INTENSITY:      0.00000     0.00000     0.00000     0.00000     0.00000
            //
            // for rt = raman
            //            1           2           3           4           5
            //FREQUENCY:         5.89        1.46        0.04        0.03        0.01
            //REDUCED MASS:      3.93944     4.46292     6.50391     6.50391     6.50439
            //IR INTENSITY:      0.00000     0.00000     0.00000     0.00000     0.00000
            //RAMAN ACTIVITY:       12.675       1.828       0.000       0.000       0.000
            //DEPOLARIZATION:        0.750       0.749       0.009       0.238       0.749

            std::vector<std::string_view> splt_s0 = split_sv(s, " ");
            vib_line_size = splt_s0.size();
            //allocate new vibrations
            output.m_vibs.resize(output.m_vibs.size() + vib_line_size);
            for (int i = 0; i < vib_line_size; i++)
              output.m_vibs[output.m_vibs.size() - i - 1].m_disp.resize(output.m_tot_nat);
            int tv = output.m_vibs.size();

            sgetline(inp, s, cur_line);
            std::vector<std::string_view> splt_s1 = split_sv(s, " ");
            for (size_t i = 1; i < vib_line_size + 1; i++)
              output.m_vibs[tv-vib_line_size + i - 1].m_frequency =
                  str2real(splt_s1, i, cur_line, s);

            sgetline(inp, s, cur_line);
            std::vector<std::string_view> splt_s2 = split_sv(s, " ");
            for (size_t i = 1; i < vib_line_size + 1; i++)
              output.m_vibs[tv-vib_line_size + i - 1].m_reduced_mass =
                  str2real(splt_s2, i + 1, cur_line, s);

            sgetline(inp, s, cur_line);
            std::vector<std::string_view> splt_s3 = split_sv(s, " ");
            for (size_t i = 1; i < vib_line_size + 1; i++)
              output.m_vibs[tv-vib_line_size+i-1].m_intensity =
                  str2real(splt_s3, i + 1, cur_line, s);

            if (output.m_run_t == comp_chem_program_run_e::rt_raman) {
                sgetline(inp, s, cur_line);
                std::vector<std::string_view> splt_ram_act = split_sv(s, " ");
                for (size_t i = 1; i < vib_line_size + 1; i++)
                  output.m_vibs[tv-vib_line_size+i-1].m_raman_activity =
                      str2real(splt_ram_act, i + 1, cur_line, s);

                sgetline(inp, s, cur_line);
                std::vector<std::string_view> splt_depol = split_sv(s, " ");
                for (size_t i = 1; i < vib_line_size + 1; i++)
                  output.m_vibs[tv-vib_line_size+i-1].m_depolarization =
                      str2real(splt_depol, i, cur_line, s);

              }

            //read empty line
            sgetline(inp, s, cur_line);
            vib_line_seek = 0;
            p_state = pcg_ff_p_state::s_vib_displ;
            continue;

          }

        if (p_state == pcg_ff_p_state::s_vib_displ) {

            if (s.length() == 1) {
                for (int i = 0; i < 10; i++) sgetline(inp, s, cur_line);
                p_state = pcg_ff_p_state::s_vib_general;
                continue;
              }

            std::vector<std::string_view> splt = split_sv(s, " ");
            int total_elems = splt.size() - vib_line_size;

            if (total_elems == 3) {
                //X LINE
                for (int i = 0 ; i < vib_line_size; i++) {
                    output.m_vibs[output.m_vibs.size() - vib_line_size + i].
                        m_disp[vib_line_seek][0] = str2real(splt, i + 3, cur_line, s);
                    continue;
                  }
              }

            if (total_elems == 1) {
                //Y OR Z LINE
                size_t i_stride = ( splt[0] == "Y" ) ? 1 : 2;

                for (int i = 0 ; i < vib_line_size; i++)
                  output.m_vibs[output.m_vibs.size() - vib_line_size + i].
                      m_disp[vib_line_seek][i_stride] =  str2real(splt, i + 1, cur_line, s);

                if (i_stride == 2) vib_line_seek +=1;
                continue;
              }
            //non empty line

            continue;
          }


        //end parsing of vibrations

        //found COORDINATES OF ALL ATOMS
        if (s.find(s_coordinates_header_str) != std::string::npos) {
            sgetline(inp, s, cur_line); //read next line  "ATOM CHARGE X Y Z"
            sgetline(inp, s, cur_line); //read next line --------
            p_state = pcg_ff_p_state::s_coord_parsing;
            //output.steps[cur_step].pos.reserve(output.tot_num_atoms);
            continue;
          }

        //parsing coordinates
        if (p_state == pcg_ff_p_state::s_coord_parsing) {
            std::vector<std::string_view> splt = split_sv(s, " ");
            if (splt.size() != 5) {
                p_state = pcg_ff_p_state::s_none;
              } else {
                REAL x,y,z;
                x = str2real(splt, 2, cur_line, s);
                y = str2real(splt, 3, cur_line, s);
                z = str2real(splt, 4, cur_line, s);
                if (!output.m_steps.empty()) {
                    output.m_steps[cur_step].m_atoms_pos.push_back(vector3<REAL>(x,y,z));
                  }
                else if (!b_atoms_bootstraped) {
                    output.m_init_apos.push_back(vector3<REAL>(x,y,z));
                    std::string at_name = std::string(splt[0]);
                    output.m_init_anames.push_back(std::move(at_name));
                  }
                continue;
              }
          }

        if (s.find(s_gradients_header_str) != std::string::npos) {
            sgetline(inp, s, cur_line); //read -------
            p_state = pcg_ff_p_state::s_grad_parsing;
            continue;
          }

        if (p_state == pcg_ff_p_state::s_grad_parsing) {
            std::vector<std::string_view> splt = split_sv(s, " ");
            if (splt.size() != 6) {
                p_state = pcg_ff_p_state::s_none;
              } else  {
                REAL gx,gy,gz;
                gx = str2real(splt, 3, cur_line, s);
                gy = str2real(splt, 4, cur_line, s);
                gz = str2real(splt, 5, cur_line, s);
                output.m_steps[cur_step].m_atoms_grads.push_back(vector3<REAL>(gx,gy,gz));
              }
            continue;
          }

        //found ***** EQUILIBRIUM GEOMETRY LOCATED *****
        if (s.find(s_eq_geom_located_str) != std::string::npos) {
            output.m_is_terminated_normally = true;
            continue;
          }

        if (s.find(s_terminated_normally_str) != std::string::npos) {
            output.m_is_terminated_normally = true;
            continue;
          }

        //end parsing calc data
      }

    if (!b_init_parsed)
      throw parsing_error_t(cur_line, s, "Invalid Firefly output file");

  }

}

#endif
