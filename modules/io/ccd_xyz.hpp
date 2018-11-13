#ifndef QPP_XYZ_CCD_IO_H
#define QPP_XYZ_CCD_IO_H

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

    output.DIM == 0;
    output.comp_chem_program = comp_chem_program_t::pr_unknown;

    xyz_parser_state p_state{state_atom_count};

    int atom_c{0};
    int frame_idx{0};
    bool init_filled{false};

    while (!inp.eof()) {

        std::getline(inp, s);
        if (inp.eof()) continue;

        if (p_state == xyz_parser_state::state_atom_count) {

            output.tot_num_atoms = std::stoi(s);
            p_state = xyz_parser_state::state_comment;
            continue;
          }

        if (p_state == xyz_parser_state::state_comment) {
            //do something
            p_state = xyz_parser_state::state_atom_data;
            atom_c = 0;
            if (!init_filled) {
                output.init_pos.resize(output.tot_num_atoms);
                output.init_atom_names.resize(output.tot_num_atoms);
              } else {
                //if multiframe file -> copy content from init geom to first frame
                if (frame_idx == 0) {
                    output.steps.resize(output.steps.size()+1);
                    //output.steps[frame_idx].pos.resize(output.tot_num_atoms);
                    output.steps[frame_idx].pos = output.init_pos;
                    frame_idx +=1;
                  }
                output.steps.resize(output.steps.size()+1);
                output.steps[frame_idx].pos.resize(output.tot_num_atoms);
              }
            continue;
          }

        if (p_state == xyz_parser_state::state_atom_data) {
            bool string_contains_tab = s.find("\t") != std::string::npos;
            if (string_contains_tab) replace_string_inplace(s, "\t", " ");
            std::vector<std::string_view> splt = split_sv(s, " ");
            //std::cout << s << std::endl;
            vector3<REAL> pos(
                  std::stod(splt[1].data()),
                  std::stod(splt[2].data()),
                  std::stod(splt[3].data()));

            if (!init_filled) {
                output.init_atom_names[atom_c] = std::string(splt[0]);
                output.init_pos[atom_c] = pos;
              } else {
                 output.steps[frame_idx].pos[atom_c] = pos;
              }

            atom_c+=1;
            if (atom_c == output.tot_num_atoms) {
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

    if (output.steps.size() > 0) output.run_t = comp_chem_program_run_t::rt_geo_opt;

  }

}

#endif
