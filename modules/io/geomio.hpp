#ifndef QPP_GEOMIO_H
#define QPP_GEOMIO_H

#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>


#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <algorithm>

//TODO add splitting utils to strfun
//#include <boost/algorithm/string/split.hpp>
//#include <boost/algorithm/string/trim.hpp>
//#include <boost/algorithm/string.hpp>

namespace qpp {

  /// \brief function for reading simple xyz format into geometry object
  /// \param inp
  /// \param geom
  template<class REAL, class CELL>
  void read_xyz(std::basic_istream<CHAR_EX,TRAITS> & inp, geometry<REAL, CELL> & geom) {

    STRING_EX s;
    std::getline(inp,s);
    int nat = std::stoi(s);
    //fmt::print("nat={}\n", nat);
    std::getline(inp,s);

    if (geom.DIM == 3) {
        std::vector<std::string_view> splt = split_sv(s, " ");
        if (splt.size() == 9) {

            geom.cell(0) = vector3<REAL>(std::stof(splt[0].data()),
                std::stof(splt[1].data()),
                std::stof(splt[2].data()));

            geom.cell(1) = vector3<REAL>(std::stof(splt[3].data()),
                std::stof(splt[4].data()),
                std::stof(splt[5].data()));

            geom.cell(2) = vector3<REAL>(std::stof(splt[6].data()),
                std::stof(splt[7].data()),
                std::stof(splt[8].data()));
          }

        if (splt.size() == 6) {
            geom.cell = periodic_cell<REAL>(std::stof(splt[0].data()), std::stof(splt[1].data()),
                std::stof(splt[2].data()), std::stof(splt[3].data()),std::stof(splt[4].data()),
                std::stof(splt[5].data()));
          }

      }

    for (int i = 0; i < nat; i++) {
        std::getline(inp,s);
        //	char s1[max_atomic_name_length];
        std::vector<std::string_view> splt = split_sv(s, " ");
        geom.add(
              std::string(splt[0]),
            std::stof(splt[1].data()),
            std::stof(splt[2].data()),
            std::stof(splt[3].data())
            );
      }
  }

  /// \brief function for reading xyz with charges format into geometry object
  /// \param inp
  /// \param geom
  template<class REAL, class CELL>
  void read_xyzq(std::basic_istream<CHAR_EX,TRAITS> & inp,
                 xgeometry<REAL,CELL> & geom,
                 bool preserve_geom = false, int xgeom_charge_field_idx = 4) {

    STRING_EX s;
    std::getline(inp,s);
    int nat;
    std::basic_stringstream<CHAR_EX,TRAITS>(s) >> nat;
    std::getline(inp,s);
    // fixme - check these are numbers!

    std::vector<std::string_view> splt = split_sv(s, " ");

    int nf = int(splt.size());

    std::vector<REAL> vv;

    bool no_conversion_errors{true};
    bool force3d{false};

    try {
      for (int i = 0; i < nf; i++) vv.push_back(std::stod(splt[i].data()));
    }
    catch (...) {
      no_conversion_errors = false;
    }

    if (no_conversion_errors) {
        switch (nf) {
          case 9: {
              geom.cell(0) = vector3<REAL>(vv[0],vv[1],vv[2]);
              geom.cell(1) = vector3<REAL>(vv[3],vv[4],vv[5]);
              geom.cell(2) = vector3<REAL>(vv[6],vv[7],vv[8]);
              force3d = true;
              break;
            }
          case 6: {
              //fmt::print("@XYZQ CELL6 {} {} {} {} {} {}\n", vv[0],vv[1],vv[2],vv[3],vv[4],vv[5]);
              periodic_cell<REAL> tc = periodic_cell<REAL>(vv[0],vv[1],vv[2],vv[3],vv[4],vv[5]);
              geom.cell(0) = tc(0);
              geom.cell(1) = tc(1);
              geom.cell(2) = tc(2);
              force3d = true;
              break;
            }
          case 1 : {
              geom.cell(0) = vector3<REAL>(vv[0], 0, 0);
              geom.cell(1) = vector3<REAL>(0, vv[0], 0);
              geom.cell(2) = vector3<REAL>(0, 0, vv[0]);
              force3d = true;
              break;
            }
          default:
            break;
          }
      }

    if (force3d) {
        geom.DIM = 3;
        geom.cell.DIM = 3;
      }

    if (!preserve_geom) {
        geom.clear();
        geom.set_format({"charge"},{type_real});
      }

    for (int i = 0; i<nat; i++) {

        std::getline(inp,s);
        std::vector<std::string_view> splt = split_sv(s);

        if (splt.size() == 5) {
            std::string s1 = std::string(splt[0]);
            REAL x = std::stod(splt[1].data());
            REAL y = std::stod(splt[2].data());
            REAL z = std::stod(splt[3].data());
            REAL q = std::stod(splt[4].data());
            geom.add(s1,x,y,z);
            geom.template xfield<REAL>(xgeom_charge_field_idx, i) = q;
          }
      }
  }

  template<class REAL, class CELL>
  void read_xyzq_wrp_def(std::basic_istream<CHAR_EX,TRAITS> & inp,
                         xgeometry<REAL,CELL> & geom) {
    read_xyzq(inp, geom, true);
  }

  // -------------------------------------------------------------------//
  //                writing geometry into simple xyz                    //
  // -------------------------------------------------------------------//
  template< class REAL, class TRANSFORM >
  void write_xyz(std::basic_ostream<CHAR_EX,TRAITS>  & out,
                 const qpp::geometry<REAL,TRANSFORM> & geom){
    out << geom.nat() << "\n";

    if (geom.DIM>0)
      for (int d = 0; d<geom.DIM; d++)
        for (int i=0; i<3; i++)
          out << fmt::format("{:12.6f} ", (geom.cell)(d)(i));
    //out << geom.name();
    out << std::endl;
    for (int i=0; i<geom.size(); i++)
      out << fmt::format("{:8s} {:12.6f} {:12.6f} {:12.6f}\n", geom.atom(i),
                         geom.coord(i)(0),  geom.coord(i)(1), geom.coord(i)(2));
  }

  // -------------------------------------------------------------------//
  //                writing geometry into simple xyz                    //
  // -------------------------------------------------------------------//
  template< class REAL, class TRANSFORM >
  void write_xyzq(std::basic_ostream<CHAR_EX,TRAITS>  & out,
                  const qpp::xgeometry<REAL,TRANSFORM> & geom){
    out << geom.nat() << "\n";

    if (geom.DIM>0)
      for (int d = 0; d<geom.DIM; d++)
        for (int i=0; i<3; i++)
          out << fmt::format("{:4.3f} ", geom.cell(d)(i));
    //out << geom.name();
    out << std::endl;
    for (int i=0; i<geom.nat(); i++)
      out <<
             fmt::format("{:8s} {:12.6f} {:12.6f} {:12.6f} {:12.6f}\n",
                         geom.atom(i),geom.coord(i)(0), geom.coord(i)(1),
                         geom.coord(i)(2), geom.charge(i));
  }
  // -------------------------------------------------------------------//
  //        writing geometry into xyz file together with displacements       //
  // -------------------------------------------------------------------//

  /*
    template< int DIM, class REAL, class TRANSFORM  >
    void write_xyz(std::basic_ostream<CHAR,TRAITS>  & out,
       const qpp::geometry<DIM,REAL,TRANSFORM> & geom,
       const qpp::molecule_vector<DIM,REAL,TRANSFORM> & v)
    {
      out << geom.nat() << "\n";

      for (int d = 0; d<DIM; d++)
        for (int i=0; i<3; i++)
    out << boost::format("%12.6f") % geom.cell(d,i);

      out << geom.name();
      out << "\n";
      for (int i=0; i<geom.size(); i++)
        out << boost::format("%-4s %12.6f %12.6f %12.6f atom_vector %12.6f %12.6f %12.6f\n") % geom.atom(i)
    % geom.coord(i)(0) % geom.coord(i)(1) % geom.coord(i)(2) % v(i,0) % v(i,1) % v(i,2);
    }
    */

  template< class REAL, class CELL>
  void write_ngbr(std::basic_ostream<CHAR_EX,TRAITS>  & out,
                  neighbours_table<REAL,CELL> & ngbr){
    for (int i=0; i<ngbr.geom->nat(); i++){
        out << i << " " << ngbr.geom->atom(i);
        std::vector<index> nn;

        for (int j=0; j<ngbr.n(i); j++)
          nn.push_back(ngbr(i,j));
        std::sort(nn.begin(),nn.end(),compare_atindex);

        for (int j=0; j<nn.size(); j++)
          out << " " << nn[j] << " "
              << norm(ngbr.geom->position(i)-ngbr.geom->position(nn[j]));
        out << "\n";

      }
  }



}

#endif
