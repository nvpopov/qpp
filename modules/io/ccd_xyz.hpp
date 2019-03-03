#ifndef QPP_XYZ_CCD_IO_H
#define QPP_XYZ_CCD_IO_H

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

  enum xyz_parser_state {
    state_none,
    state_atom_count,
    state_comment,
    state_atom_data,
    state_post_coords
  };

  template<class REAL>
  void read_ccd_from_xyz_file(std::basic_istream<CHAR,TRAITS> &inp,
                              comp_chem_program_data_t<REAL> &output) {

    std::locale loc1("C");
    std::string s;

    output.m_DIM = 0;
    output.m_comp_chem_program = comp_chem_program_t::pr_unknown;

    xyz_parser_state p_state{state_atom_count};

    int atom_c{0};
    int frame_idx{0};
    bool init_filled{false};

    uint64_t cur_line{0};

    while (!inp.eof()) {

        sgetline(inp, s, cur_line);
        if (inp.eof()) continue;

        if (p_state == xyz_parser_state::state_atom_count) {

            output.m_tot_nat = str2int(cur_line, s);
            p_state = xyz_parser_state::state_comment;
            continue;
          }

        if (p_state == xyz_parser_state::state_comment) {
            //do something
            p_state = xyz_parser_state::state_atom_data;
            atom_c = 0;
            if (!init_filled) {
                output.m_init_atoms_pos.resize(output.m_tot_nat);
                output.m_init_atoms_names.resize(output.m_tot_nat);
              } else {
                //if multiframe file -> copy content from init geom to first frame
                if (frame_idx == 0) {
                    output.m_steps.resize(output.m_steps.size()+1);
                    //output.steps[frame_idx].pos.resize(output.tot_num_atoms);
                    output.m_steps[frame_idx].m_atoms_pos = output.m_init_atoms_pos;
                    frame_idx +=1;
                  }
                output.m_steps.resize(output.m_steps.size()+1);
                output.m_steps[frame_idx].m_atoms_pos.resize(output.m_tot_nat);
              }
            continue;
          }

        if (p_state == xyz_parser_state::state_atom_data) {

            bool string_contains_tab = s.find("\t") != std::string::npos;
            if (string_contains_tab) replace_string_inplace(s, "\t", " ");
            std::vector<std::string_view> splt = split_sv(s, " ");
            check_min_split_size(splt, 4, cur_line, s);

            vector3<REAL> pos(str2real(splt, 1, cur_line, s),
                              str2real(splt, 2, cur_line, s),
                              str2real(splt, 3, cur_line, s));

            if (!init_filled) {
                output.m_init_atoms_names[atom_c] = std::string(splt[0]);
                output.m_init_atoms_pos[atom_c] = pos;
              } else {
                 output.m_steps[frame_idx].m_atoms_pos[atom_c] = pos;
              }

            atom_c+=1;
            if (atom_c == output.m_tot_nat) {
                atom_c = 0;
                if (!init_filled) {
                    init_filled = true;
                  }
                else {
                    frame_idx += 1;
                  }
                p_state = xyz_parser_state::state_atom_count;
              }

            continue;

          }

      }

    if (output.m_steps.size() > 0) output.m_run_t = comp_chem_program_run_t::rt_geo_opt;

    if (output.m_tot_nat == 0)
      throw parsing_error_t(cur_line, s, "Invalid XYZ file");

  }

}

#endif
