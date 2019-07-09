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
  void read_ccd_from_xyz_file(std::basic_istream<CHAR_EX,TRAITS> &inp,
                              comp_chem_program_data_t<REAL> &output) {

    std::locale loc1("C");
    std::string s;

    output.m_DIM = 0;
    output.m_comp_chem_program = comp_chem_program_e::pr_unknown;

    xyz_parser_state p_state{state_atom_count};

    int atom_c{0};
    int frame_idx{0};
    bool init_filled{false};

    uint64_t cur_line{0};

    while (!inp.eof()) {

        sgetline(inp, s, cur_line);
        if (inp.eof()) continue;

        if (p_state == xyz_parser_state::state_atom_count) {

            if (s.empty()) break;

            output.m_tot_nat = str2int(cur_line, s);
            p_state = xyz_parser_state::state_comment;
            continue;
          }

        if (p_state == xyz_parser_state::state_comment) {

            std::vector<REAL> vv;
            bool no_conversion_errors{true};
            bool force3d{false};
            std::vector<std::string_view> splt = split_sv(s, " ");
            int nf = int(splt.size());

            try {
              for (int i = 0; i < nf; i++) vv.push_back(std::stod(splt[i].data()));
            }
            catch (...) {
              no_conversion_errors = false;
            }

            if (no_conversion_errors) {
                switch (nf) {
                  case 9: {
                      output.m_cell_v.push_back(vector3<REAL>(vv[0],vv[1],vv[2]));
                      output.m_cell_v.push_back(vector3<REAL>(vv[3],vv[4],vv[5]));
                      output.m_cell_v.push_back(vector3<REAL>(vv[6],vv[7],vv[8]));
                      force3d = true;
                      break;
                    }
                  case 6: {
                      periodic_cell<REAL> cell(vv[0],vv[1],vv[2],vv[3],vv[4],vv[5]);
                      output.m_cell_v.push_back(cell.v[0]);
                      output.m_cell_v.push_back(cell.v[1]);
                      output.m_cell_v.push_back(cell.v[2]);
                      force3d = true;
                      break;
                    }
                  case 1 : {
                      output.m_cell_v.push_back(vector3<REAL>(vv[0], 0, 0));
                      output.m_cell_v.push_back(vector3<REAL>(0, vv[0], 0));
                      output.m_cell_v.push_back(vector3<REAL>(0, 0, vv[0]));
                      force3d = true;
                      break;
                    }
                  default:
                    break;
                  }
              }

            if (force3d) {
                output.m_DIM = 3;
              }

            p_state = xyz_parser_state::state_atom_data;
            atom_c = 0;

            if (!init_filled) {
                output.m_init_apos.resize(output.m_tot_nat);
                output.m_init_anames.resize(output.m_tot_nat);
              } else {
                //if multiframe file -> copy content from init geom to first frame
                if (frame_idx == 0) {
                    output.m_steps.resize(output.m_steps.size()+1);
                    //output.steps[frame_idx].pos.resize(output.tot_num_atoms);
                    output.m_steps[frame_idx].m_atoms_pos = output.m_init_apos;
                    frame_idx +=1;
                  }
                output.m_steps.resize(output.m_steps.size()+1);
                output.m_steps[frame_idx].m_atoms_pos.resize(output.m_tot_nat);
              }
            continue;

          }

        if (p_state == xyz_parser_state::state_atom_data) {

            bool string_contains_tab = s.find("\t") != std::string::npos;

            if (s.empty()) continue;

            if (string_contains_tab) replace_string_inplace(s, "\t", " ");
            std::vector<std::string_view> splt = split_sv(s, " ");

            if (splt.size() <= 3) continue;

            check_min_split_size(splt, 4, cur_line, s);

            vector3<REAL> pos(str2real(splt, 1, cur_line, s),
                              str2real(splt, 2, cur_line, s),
                              str2real(splt, 3, cur_line, s));

            if (!init_filled) {
                output.m_init_anames[atom_c] = std::string(splt[0]);
                output.m_init_apos[atom_c] = pos;
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

    if (output.m_steps.size() > 0) output.m_run_t = comp_chem_program_run_e::rt_geo_opt;

    if (output.m_tot_nat == 0)
      throw parsing_error_t(cur_line, s, "Invalid XYZ file");

  }

}

#endif
