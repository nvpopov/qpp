#ifndef QPP_CCD_MOLDEN
#define QPP_CCD_MOLDEN

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

  enum molden_parser_state_e : size_t {
    molden_none,
    molden_format,
    molden_atoms,
    molden_freq,
    molden_fr_coords,
    molden_fr_norm_coords
  };

  const auto MOLDEN_HEADER        = "Molden Format";
  const auto MOLDEN_ATOMS         = "Atoms";
  const auto MOLDEN_FREQ          = "FREQ";
  const auto MOLDEN_FR_COORD      = "FR-COORD";
  const auto MOLDEN_FR_NORM_COORD = "FR-NORM-COORD";
  const auto MOLDEN_VIBRATION     = "vibration";
  const auto MOLDEN_ATOMS_AU      = "AU";

  template<class REAL>
  void read_ccd_from_molden(std::basic_istream<CHAR_EX,TRAITS> & inp,
                            comp_chem_program_data_t<REAL> &output) {

    std::locale loc1("C");
    std::string s;
    uint64_t cur_line{0};

    output.m_DIM = 0;
    output.m_comp_chem_program = comp_chem_program_e::pr_molden;

    molden_parser_state_e ps{molden_parser_state_e::molden_none};
    bool is_au{false}; // spatial units

    std::vector<vector3<REAL>> tmp_displ;

    int norm_mode_id = -1;

    while (!inp.eof()) {

        sgetline(inp, s, cur_line);

        if (s.empty()) continue;

        if (cur_line == 1 && (s.find(MOLDEN_HEADER) == std::string::npos))
          throw parsing_error_t(cur_line, "Wrong Header");

        if (s.find(MOLDEN_ATOMS) != std::string::npos) {
            std::vector<std::string_view> splt = split_sv(s, " ");
            is_au = (splt.size() > 0) && (splt[1].find(MOLDEN_ATOMS_AU) != std::string::npos);
            ps = molden_parser_state_e::molden_atoms;
            continue;
          } // [Atoms]

        if (s.find(MOLDEN_FREQ) != std::string::npos) {
            ps = molden_parser_state_e::molden_freq;
            output.m_run_t = comp_chem_program_run_e::rt_vib;
            continue;
          } // [FREQ]

        if (s.find(MOLDEN_FR_COORD) != std::string::npos) {
            if (!output.m_init_anames.empty() &&
                tmp_displ.size() != output.m_init_anames.size())
              tmp_displ.reserve(output.m_init_anames.size());
            ps = molden_parser_state_e::molden_fr_coords;
            continue;
          } // [FR-COORD]

        if (s.find(MOLDEN_FR_NORM_COORD) != std::string::npos) {
            ps = molden_parser_state_e::molden_fr_norm_coords;
            continue;
          } // [FR-NORM-COORD]

        if (ps == molden_parser_state_e::molden_freq) {
            comp_chem_program_vibration_info_t<REAL> vib_info;
            std::vector<std::string_view> splt = split_sv(s, " ");
            check_min_split_size(splt, 1, cur_line, s);
            vib_info.m_frequency = str2real(splt, 0, cur_line, s);
            output.m_vibs.push_back(std::move(vib_info));
            continue;
          }

        if (ps == molden_parser_state_e::molden_fr_coords) {
            std::vector<std::string_view> splt = split_sv(s, " ");
            check_min_split_size(splt, 4, cur_line, s);
            vector3<REAL> atom_displ_frame =
                vec_from_str_ex<REAL>(s, splt, cur_line, 1, 2, 3);
            if (is_au) atom_displ_frame *= bohr_to_angs;
            tmp_displ.push_back(std::move(atom_displ_frame));
            continue;
          }

        //parsing displacements for normal modes
        if (ps == molden_parser_state_e::molden_fr_norm_coords) {
            if (s.find(MOLDEN_VIBRATION) != std::string::npos) {
                norm_mode_id++;
                 if (!output.m_init_anames.empty())
                  output.m_vibs[norm_mode_id].m_disp.reserve(output.m_init_anames.size());
                continue;
              } else {
                std::vector<std::string_view> splt = split_sv(s, " ");
                check_min_split_size(splt, 3, cur_line, s);
                vector3<REAL> atom_displ = vec_from_str_ex<REAL>(s, splt, cur_line, 0, 1, 2);
                output.m_vibs[norm_mode_id].m_disp.push_back(std::move(atom_displ));
                continue;
              }
          }

        //parsing atoms positions and names
        if (ps == molden_parser_state_e::molden_atoms) {
            std::vector<std::string_view> splt = split_sv(s, " ");
            check_min_split_size(splt, 6, cur_line, s);
            vector3<REAL> atm_pos = vec_from_str_ex<REAL>(s, splt, cur_line, 3, 4, 5);
            if (is_au) atm_pos *= bohr_to_angs;
            output.m_init_apos.push_back(std::move(atm_pos));
            output.m_init_anames.push_back(std::string(splt[0]));
            continue;
          } // atoms after MOLDEN_ATOMS

      }

    output.m_tot_nat = output.m_init_anames.size();

  } // read_ccd_from_molden

} // namespace qpp

#endif
