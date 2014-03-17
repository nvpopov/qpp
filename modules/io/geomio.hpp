#ifndef _QPP_GEOMIO_H
#define _QPP_GEOMIO_H

#include <lace/lace3d.hpp>
//#include <lace/lace.hpp>
//#include <symm/symm.hpp>
#include <geom/geom.hpp>
//#include <geom/molecule.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ios>
#include <boost/format.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string.hpp>

namespace qpp{

  // index i/o

  /*
  template<typename _CharT, class _Traits, int DIM>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& __os, 
	     index<DIM> i)
  {
    std::basic_ostringstream<_CharT, _Traits> __s;
    __s.flags(__os.flags());
    __s.imbue(__os.getloc());
    __s.precision(__os.precision());
    __s << "(" << i.atom();
    for (int k=0; k<DIM; k++)
      __s << "," << i.cell(k); 
     __s << ")";
    return __os << __s.str();
  }
  */
  // --------------------------------------------------------------------//

  template<class charT = char, class traits = std::char_traits<charT> >
  int strnf(std::basic_string<charT,traits> s)
  {
    std::stringstream ss(s);
    std::basic_string<charT,traits> a;
    int nf = 0;
    for (nf=0; ss >> a; a!="") nf++;
    return nf;
  }

  // -------------------------------------------------------------------//
  //     function for reading simple xyz format into geometry object    //
  // -------------------------------------------------------------------//
  
  template< int DIM, class VALTYPE=double, class ATLABEL = std::string, class charT = char, 
	    class traits = std::char_traits<charT> >
  void read_xyz(std::basic_istream<charT, traits>  & inp, qpp::geometry<DIM,VALTYPE,ATLABEL,charT,traits> & geom)
  {
    std::basic_string<charT,traits> s;
    std::getline(inp,s);
    int nat;
    std::stringstream(s) >> nat;
    std::getline(inp,s);
    // fixme - check these are numbers!
    if (DIM==3)
      {
	int nf = strnf(s);
	if ( nf==9 || nf == 6 )
	  {
	    VALTYPE vv[nf];
	    std::stringstream ss(s);
	    for (int i=0; i<nf; i++) ss >> vv[i];
	    if (nf==9)
	      {
		geom.cell(0) = lace::vector3d<VALTYPE>(vv[0],vv[1],vv[2]);
		geom.cell(1) = lace::vector3d<VALTYPE>(vv[3],vv[4],vv[5]);
		geom.cell(2) = lace::vector3d<VALTYPE>(vv[6],vv[7],vv[8]);
	      }
	    else
	      geom.cell = periodic_cell<DIM,VALTYPE>(vv[0],vv[1],vv[2],vv[3],vv[4],vv[5]);
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
	std::basic_string<charT,traits> s1;
	VALTYPE x,y,z;
	std::stringstream tmps(s);
	tmps >> s1 >> x >> y >> z;
	geom.add(ATLABEL(s1),x,y,z);
      } 
  }
  
  // -------------------------------------------------------------------//  
  //                writing geometry into simple xyz                    //
  // -------------------------------------------------------------------//
  template< int DIM, class VALTYPE=double, class ATLABEL = std::string, class charT = char, 
	    class traits = std::char_traits<charT> >
  void write_xyz(std::basic_ostream<charT, traits>  & out, qpp::geometry<DIM,VALTYPE,ATLABEL,charT,traits> & geom)
  {
    out << geom.size() << "\n";
    if (DIM>0)
      for (int d = 0; d<DIM; d++)
	for (int i=0; i<3; i++)
	  out << boost::format("%12.6f") % geom.cell(d,i);
    else
      out << geom.name();
    out << "\n";
    for (int i=0; i<geom.size(); i++)
      out << boost::format("%-4s %12.6f %12.6f %12.6f\n") % geom.atom(i) % geom.coord(i)(0) 
	% geom.coord(i)(1) % geom.coord(i)(2);
  }
  /*
  // -------------------------------------------------------------------//
  //        writing geometry into xyz file together with displacements       //
  // -------------------------------------------------------------------//
  template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
  void write_xyz(std::basic_ostream<_CharT, _Traits>  & out, qpp::geometry<ATOM,DIM,VALTYPE> & geom, 
		 const qpp::molecule_vector<ATOM,DIM,VALTYPE> & v)
  {
    out << geom.size() << "\n";
    for (int d = 0; d<DIM; d++)
      for (int i=0; i<3; i++)
	out << boost::format("%12.6f") % geom.cell(d,i);
    out << "\n";
    qpp::molecule_vector<ATOM,DIM,VALTYPE> vv(v);
    for (int i=0; i<geom.size(); i++)
      out << boost::format("%-4s %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f\n") % geom.atom(i) 
	% geom.atom_coord(i)(0) % geom.atom_coord(i)(1) % geom.atom_coord(i)(2)
	% vv(i,0) % vv(i,1) % vv(i,2);
  }
  */


};

#endif
