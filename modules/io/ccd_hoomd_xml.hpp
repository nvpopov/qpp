#ifndef QPP_HOOMD_XML_CCD_IO_H
#define QPP_HOOMD_XML_CCD_IO_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <geom/geom.hpp>
#include <geom/geom_anim.hpp>
#include <io/comp_chem_data.hpp>
#include <io/parsing_exceptions.hpp>
#include <pugixml.hpp>

#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>

namespace qpp {

  template<class REAL>
  void read_ccd_from_hoomd_xml(std::basic_istream<CHAR_EX,TRAITS> &inp,
                               comp_chem_program_data_t<REAL> &output) {

    std::locale loc1("C");

    pugi::xml_document doc;
    doc.load(inp);

    pugi::xml_node hoomd_xml_node  = doc.child("hoomd_xml");
    pugi::xml_node conf_node       = hoomd_xml_node.child("configuration");
    pugi::xml_node pos             = conf_node.child("position");
    pugi::xml_node type            = conf_node.child("type");
    //pugi::xml_node mass            = conf_node.child("mass");
    pugi::xml_node charge          = conf_node.child("charge");

    /* reading the required data */
    auto sv_pos = split_sv(pos.text().get(), "\n");
    auto sv_names = split_sv(type.text().get(), "\n");

    output.m_init_apos.reserve(sv_pos.size());
    output.m_init_anames.reserve(sv_pos.size());
    float x{0}, y{0}, z{0};

    for (const auto &rec : sv_pos) {

        auto sv_pos_ex = split_sv(rec, " ");
        s2t(sv_pos_ex[0].data(), x);
        s2t(sv_pos_ex[1].data(), y);
        s2t(sv_pos_ex[2].data(), z);
        output.m_init_apos.push_back({x,y,z});

      }

    for (const auto &rec : sv_names) {

        output.m_init_anames.push_back(std::string(rec));

      }

    /* end of reading the required data*/

    /* reading the charges, etc. */
    if (!charge.empty()) {

        auto sv_charges = split_sv(charge.text().get(), "\n");
        output.m_init_achg.reserve(sv_charges.size());

        float charge_val{0};

        for (const auto &rec : sv_charges) {
            s2t(rec.data(), charge_val);
            output.m_init_achg.push_back(charge_val);

          }

      }
    /* end of reading the charges*/

  }

} // namespace qpp

#endif
