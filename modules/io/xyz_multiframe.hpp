#ifndef QPP_XYZ_MULTIFRAME_H
#define QPP_XYZ_MULTIFRAME_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <geom/geom.hpp>
#include <geom/geom_anim.hpp>

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
  void read_xyz_multiframe (std::basic_istream<CHAR,TRAITS> & inp,
                            geometry<REAL, CELL> & geom,
                            std::vector<geom_anim_record_t<float> > &anim) {
    std::string s;

    int nat{0};
    bool bootstrap_geom{false};
    geom_anim_record_t<float> animr, anim_static;

    animr.m_anim_type = geom_anim_type::anim_generic;
    animr.m_anim_name = "animation1";

    anim_static.m_anim_type = geom_anim_type::anim_static;
    anim_static.m_anim_name = "static";
    anim_static.frame_data.resize(1);

    std::getline(inp, s);
    while (!inp.eof()){
        //std::cout << s << std::endl;
        nat = std::stoi(s);
        std::getline(inp, s);

        animr.frame_data.resize(animr.frame_data.size()+1);

        for (int i = 0; i < nat; i++){
            std::getline(inp, s);
            std::vector<std::string_view> splt = split_sv(s, " ");

            //std::cout << splt[0].length() << std::endl;

            float x = std::stof(splt[1].data());
            float y = std::stof(splt[2].data());
            float z = std::stof(splt[3].data());

            vector3<float> displ{x, y, z};

            if(!bootstrap_geom){
                geom.add(std::string(splt[0]), displ);
                anim_static.frame_data.back().push_back(displ);
              }

            animr.frame_data.back().push_back(std::move(displ));

          }

        if (!bootstrap_geom) bootstrap_geom = true;
        std::getline(inp, s);
      }

    if (!anim_static.frame_data.empty()) anim.push_back(std::move(anim_static));
    if (!animr.frame_data.empty()) anim.push_back(std::move(animr));

  }
}

#endif
