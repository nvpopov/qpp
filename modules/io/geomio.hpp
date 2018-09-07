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

  ///
  /// \brief function for reading simple xyz format into geometry object
  /// \param inp
  /// \param geom
  ///
  template<class REAL, class CELL>
  void read_xyz(std::basic_istream<CHAR,TRAITS> & inp, geometry<REAL, CELL> & geom){

    STRING s;
    std::getline(inp,s);
    int nat;
    std::basic_stringstream<CHAR,TRAITS>(s) >> nat;
    std::getline(inp,s);
    // fixme - check these are numbers!
    if (geom.DIM==3){
      int nf = strnf(s);
      if ( nf==9 || nf == 6 ){
        REAL vv[nf];
        std::basic_stringstream<CHAR,TRAITS> ss(s);
        for (int i=0; i<nf; i++) ss >> vv[i];
        if (nf==9) {
          geom.cell(0) = {vv[0],vv[1],vv[2]};
          geom.cell(1) = {vv[3],vv[4],vv[5]};
          geom.cell(2) = {vv[6],vv[7],vv[8]};
        } else geom.cell = periodic_cell<REAL>(vv[0],vv[1],vv[2],vv[3],vv[4],vv[5]);
      }
    }

    for (int i = 0; i<nat; i++){
      std::getline(inp,s);
      if (i==0){
      // Analise the line, recognize .xyz type
      }
      //	char s1[max_atomic_name_length];
      STRING s1;
      REAL x,y,z;
      std::basic_stringstream<CHAR,TRAITS> tmps(s);
      tmps >> s1 >> x >> y >> z;
      geom.add(s1,x,y,z);
    }
  }

///
/// \brief function for reading xyz with charges format into geometry object
/// \param inp
/// \param geom
///
  template<class REAL, class CELL>
  void read_xyzq(std::basic_istream<CHAR,TRAITS> & inp,
               xgeometry<REAL,CELL> & geom){
    STRING s;
    std::getline(inp,s);
    int nat;
    std::basic_stringstream<CHAR,TRAITS>(s) >> nat;
    std::getline(inp,s);
    // fixme - check these are numbers!
    if (geom.DIM==3){
        int nf = strnf(s);
        if ( nf==9 || nf == 6 ){
            REAL vv[nf];
            std::basic_stringstream<CHAR,TRAITS> ss(s);
            for (int i=0; i<nf; i++) ss >> vv[i];
            if (nf==9){
                geom.cell(0) = {vv[0],vv[1],vv[2]};
                geom.cell(1) = {vv[3],vv[4],vv[5]};
                geom.cell(2) = {vv[6],vv[7],vv[8]};
            }
            else geom.cell = periodic_cell<REAL>(vv[0],vv[1],vv[2],vv[3],vv[4],vv[5]);
        }
    }

    geom.clear();
    geom.set_format({"charge"},{type_real});

    for (int i = 0; i<nat; i++){
      std::getline(inp,s);
      if (i==0){
      // Analyze the line, recognize .xyz type
      }
      //	char s1[max_atomic_name_length];
      STRING s1;
      REAL x,y,z,q;
      std::basic_stringstream<CHAR,TRAITS> tmps(s);
      tmps >> s1 >> x >> y >> z >> q;
      geom.xadd(s1,x,y,z,q);
    }
}
/*
  template< class REAL, class CELL>
  void read_xyzq(std::basic_istream<CHAR,TRAITS> & inp, xgeometry<REAL,CELL> & geom)
  {
    STRING s;
    std::getline(inp,s);
    int nat;
    std::basic_stringstream<CHAR,TRAITS>(s) >> nat;
    std::getline(inp,s);
    // fixme - check these are numbers!
    if (DIM==3)
      {
  int nf = strnf(s);
  if ( nf==9 || nf == 6 )
    {
      REAL vv[nf];
      std::basic_stringstream<CHAR,TRAITS> ss(s);
      for (int i=0; i<nf; i++) ss >> vv[i];
      if (nf==9)
        {
    (*geom.cell)(0) = {vv[0],vv[1],vv[2]};
    (*geom.cell)(1) = {vv[3],vv[4],vv[5]};
    (*geom.cell)(2) = {vv[6],vv[7],vv[8]};
        }
      else
        geom.cell = new periodic_cell<DIM,REAL>(vv[0],vv[1],vv[2],vv[3],vv[4],vv[5]);
    }
      }
    for (int i = 0; i<nat; i++)
      {
  std::getline(inp,s);
  if (i==0)
    {
      // Analise the line, recognize .xyz type
    }
  //	char s1[max_atomic_name_length];
  STRING s1;
  REAL x,y,z,q;
  std::basic_stringstream<CHAR,TRAITS> tmps(s);
  tmps >> s1 >> x >> y >> z >> q;
  geom.add(s1,{x,y,z},{q},{},{});
      }
    geom.field_names({"charge"});
  }
  */
// -------------------------------------------------------------------//
//                writing geometry into simple xyz                    //
// -------------------------------------------------------------------//
template< class REAL, class TRANSFORM >
void write_xyz(std::basic_ostream<CHAR,TRAITS>  & out,
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
void write_xyzq(std::basic_ostream<CHAR,TRAITS>  & out,
                const qpp::xgeometry<REAL,TRANSFORM> & geom){
  out << geom.nat() << "\n";

  if (geom.DIM>0)
    for (int d = 0; d<geom.DIM; d++)
      for (int i=0; i<3; i++)
        out << fmt::format("{:12.6f}\n", geom.cell(d)(i));
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
void write_ngbr(std::basic_ostream<CHAR,TRAITS>  & out,
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
