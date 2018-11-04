#ifndef QPP_GMS_FF_IO_H
#define QPP_GMS_FF_IO_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <geom/geom.hpp>
#include <geom/geom_anim.hpp>
#include <io/general_qc_output.hpp>

#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>

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
    s_grad_parsing
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

  const std::string s_coordinates_header_str =
      "COORDINATES OF ALL ATOMS ARE (ANGS)";

  const std::string s_eq_geom_located_str =
      "***** EQUILIBRIUM GEOMETRY LOCATED *****";

  const std::string s_gradients_header_str =
      "ATOM     ZNUC       DE/DX         DE/DY         DE/DZ";

  template<class REAL, class CELL>
  void read_firefly_output(std::basic_istream<CHAR,TRAITS> & inp,
                           geometry<REAL, CELL> & geom,
                           comp_chem_program_output_t<REAL> &output) {

    std::locale loc1("C");
    std::string s;

    pcg_ff_p_state p_state{s_none};

    bool b_init_parsed{false};
    size_t cur_step{0};

    while (!inp.eof()) {

        std::getline(inp, s);

        //start parsing initial section
        if (!b_init_parsed) {

            //reading initial coordinates
            if (p_state == pcg_ff_p_state::s_none &&
                s.find(s_init_read_crds_header_str) != std::string::npos) {
                p_state = pcg_ff_p_state::s_init_read_crds_header;
                continue;
              }

            if (p_state == pcg_ff_p_state::s_init_read_crds_header &&
                s.find(s_init_read_crds_after_header_str)) {
                p_state = pcg_ff_p_state::s_init_read_crds;
                continue;
              }

            if (p_state == pcg_ff_p_state::s_init_read_crds) {
                std::vector<std::string_view> splt = split_sv(s, " ");

                if (splt.size() != 5) {
                    p_state = pcg_ff_p_state::s_none;
                    continue;
                  }
                continue;
              }
            //end of reading initial coordinates

            //total number of electrons in init section
            if (s.find(s_init_tot_num_electons_str) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                int tot_num_electrons = std::stoi(splt[4].data());
                output.tot_num_electrons = tot_num_electrons;
                continue;
              }

            //total charge in init section
            if (s.find(s_init_tot_charge_str) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                REAL tot_charge = std::stod(splt[4].data());
                output.tot_charge = tot_charge;
                continue;
              }

            //multiplicity in init section
            if (s.find(s_init_tot_mult_str) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                int tot_mult = std::stoi(splt[3].data());
                output.mult = tot_mult;
                continue;
              }

            //num occup alpha in init section
            if (s.find(s_init_tot_num_occup_alpha) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                int tot_occ_alpha = std::stoi(splt[6].data());
                output.n_alpha = tot_occ_alpha;
                output.is_unrestricted = true;
                continue;
              }

            //num occup beta in init section
            if (s.find(s_init_tot_num_occup_beta) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                int tot_occ_beta = std::stoi(splt[7].data());
                output.n_beta = tot_occ_beta;
                output.is_unrestricted = true;
                continue;
              }

            //total atoms in init section
            if (s.find(s_init_tot_num_atoms_str) != std::string::npos) {
                std::vector<std::string_view> splt = split_sv(s, " ");
                int tot_atoms = std::stoi(splt[5].data());
                output.tot_num_atoms = tot_atoms;
                continue;
              }

            if (s.find(s_init_control_section_str) != std::string::npos){
                std::getline(inp, s); // read -------
                std::getline(inp, s); // SCFTYP=RHF RUNTYP=OPTIMIZE EXETYP=RUN
                std::vector<std::string_view> splt = split_sv(s, " ");

                if (splt[0] == "SCFTYP=RHF") output.is_unrestricted = false;
                if (splt[0] == "SCFTYP=UHF") output.is_unrestricted = true;
                if (splt[1] == "RUNTYP=OPTIMIZE")
                  output.run_t = comp_chem_program_run_t::geo_opt;
                if (splt[1] == "RUNTYP=ENERGY")
                  output.run_t = comp_chem_program_run_t::energy;
                if (splt[1] == "RUNTYP=GRADIENT")
                  output.run_t = comp_chem_program_run_t::grad;

                b_init_parsed = true;
                p_state = pcg_ff_p_state::s_none;
                continue;
              }

          } //end parsing initial section

        //start parsing calc data
        if (p_state == s_none && s.find(s_scf_parsing_header_str) != std::string::npos) {
            p_state = pcg_ff_p_state::s_scf_parsing;
            output.steps.resize(output.steps.size() + 1);
            cur_step = output.steps.size() - 1;
            continue;
          }

        //parsing scf iter
        if (p_state == pcg_ff_p_state::s_scf_parsing) {
            //std::cout << s << std::endl;
            std::vector<std::string_view> splt = split_sv(s, " ");
            if (splt.size() == 7) {
                //fill scf step info
                comp_chem_program_scf_step_info_t<REAL> _scf_step;
                _scf_step.iter = std::stoi(splt[0].data());
                _scf_step.ex = std::stoi(splt[1].data());
                _scf_step.dem = std::stoi(splt[2].data());
                _scf_step.total_energy = std::stod(splt[3].data());
                _scf_step.e_change = std::stod(splt[4].data());
                _scf_step.d_change = std::stod(splt[5].data());
                _scf_step.orb_grad = std::stod(splt[6].data());

                output.steps[cur_step].scf_steps.push_back(std::move(_scf_step));
              }

            if (s.find("-----------------") != std::string::npos) {
                if (!output.steps[cur_step].scf_steps.empty())
                  output.steps[cur_step].total_energy =
                      output.steps[cur_step].scf_steps.back().total_energy;
                p_state = pcg_ff_p_state::s_none;
              }
            continue;
          }


        //found COORDINATES OF ALL ATOMS
        if (s.find(s_coordinates_header_str) != std::string::npos) {
            std::getline(inp, s); //read next line  "ATOM CHARGE X Y Z"
            std::getline(inp, s); //read next line --------
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
                x = std::stod(splt[2].data());
                y = std::stod(splt[3].data());
                z = std::stod(splt[4].data());
                if (!output.steps.empty()) {
                    output.steps[cur_step].pos.push_back(vector3<REAL>(x,y,z));
                  }
                else {
                    output.init_pos.push_back(vector3<REAL>(x,y,z));
                    std::string at_name = std::string(splt[0]);
                    output.init_atom_names.push_back(std::move(at_name));
                  }
                continue;
              }
          }

        if (s.find(s_gradients_header_str) != std::string::npos) {
            std::getline(inp, s); //read -------
            p_state = pcg_ff_p_state::s_grad_parsing;
            continue;
          }

        if (p_state == pcg_ff_p_state::s_grad_parsing) {
            std::vector<std::string_view> splt = split_sv(s, " ");
            if (splt.size() != 6) {
                p_state = pcg_ff_p_state::s_none;
              } else {
                REAL gx,gy,gz;
                gx = std::stod(splt[3].data());
                gy = std::stod(splt[4].data());
                gz = std::stod(splt[5].data());
                output.steps[cur_step].grad.push_back(vector3<REAL>(gx,gy,gz));
              }
            continue;
          }

        //found ***** EQUILIBRIUM GEOMETRY LOCATED *****
        if (s.find(s_eq_geom_located_str) != std::string::npos) {
            output.m_is_terminated_normally = true;
            continue;
          }

        //end parsing calc data
      }

  }

}

#endif
