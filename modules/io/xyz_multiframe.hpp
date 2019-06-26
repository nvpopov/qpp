#ifndef QPP_XYZ_MULTIFRAME_H
#define QPP_XYZ_MULTIFRAME_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <geom/geom.hpp>
#include <geom/geom_anim.hpp>
#include <io/pdb_name_reducer.hpp>

#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>

namespace qpp {
  using string = std::string;
  template<class REAL, class CELL>
  void read_xyz_multiframe (std::basic_istream<CHAR_EX,TRAITS> & inp,
                            geometry<REAL, CELL> & geom,
                            std::vector<geom_anim_record_t<float> > &anim,
                            bool keep_pdb_like_names = false ) {

    std::locale loc1("C");

    std::string s;

    int nat{0};
    bool bootstrap_geom{false};
    geom_anim_record_t<REAL> animr, anim_static;

    animr.m_anim_type = geom_anim_t::anim_generic;
    animr.m_anim_name = "animation1";

    anim_static.m_anim_type = geom_anim_t::anim_static;
    anim_static.m_anim_name = "static";
    anim_static.frames.resize(1);

    std::getline(inp, s);
    while (!inp.eof()) {
        //std::cout << s << std::endl;
        nat = std::stoi(s);
        std::getline(inp, s);

        animr.frames.resize(animr.frames.size()+1);

        for (int i = 0; i < nat; i++){
            std::getline(inp, s);
            std::vector<std::string_view> splt = split_sv(s, " ");

            //std::cout << splt[0].length() << std::endl;

            float x = std::stof(splt[1].data());
            float y = std::stof(splt[2].data());
            float z = std::stof(splt[3].data());

            vector3<float> displ{x, y, z};

            if (!bootstrap_geom) {
                std::string at_name = std::string(splt[0]);

                if (!keep_pdb_like_names) pbd_name_reducer::eval_change(at_name);
                else
                  if (at_name.length() == 2) {
                      std::transform(at_name.begin()+1, at_name.end(),
                                     at_name.begin()+1, ::tolower);
                      std::transform(at_name.begin(), at_name.begin()+1,
                                     at_name.begin(), ::toupper);
                    }

                geom.add(at_name, displ);

                anim_static.frames.back().atom_pos.push_back(displ);
              }
            animr.frames.back().atom_pos.push_back(std::move(displ));
          }

        if (!bootstrap_geom) bootstrap_geom = true;
        std::getline(inp, s);
      }

    if (!anim_static.frames.empty()) anim.push_back(std::move(anim_static));
    if (!animr.frames.empty()) anim.push_back(std::move(animr));

  }
}

#endif
