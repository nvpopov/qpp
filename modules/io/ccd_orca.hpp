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
    orca_parse_eigen_values,
    orca_parse_tddft

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

    while (!inp.eof()) {

        sgetline(inp, s, cur_line);

        if (inp.eof()) continue;

        if (s.find("* Single Point Calculation *") != std::string::npos) {
            output.m_run_t = comp_chem_program_run_e::rt_energy;
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

        if (s.find("SCF ITERATIONS") != std::string::npos) {

            pstate = orca_parser_state_e::orca_parse_scf_section;
            sgetline(inp, s, cur_line);
            sgetline(inp, s, cur_line);
            continue;

          }

      } // end of while loop

  } // end of function

} // namespace qpp

#endif
