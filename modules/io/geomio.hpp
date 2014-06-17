#ifndef _QPP_GEOMIO_H
#define _QPP_GEOMIO_H

#include <lace/lace3d.hpp>
//#include <lace/lace.hpp>
//#include <symm/symm.hpp>
#include <geom/geom.hpp>
#include <geom/geom_extras.hpp>
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

  int strnf(const STRING & s)
  {
    std::basic_stringstream<CHAR,TRAITS> ss(s);
    STRING a;
    int nf = 0;
    for (nf=0; ss >> a; a!="") nf++;
    return nf;
  }

  // -------------------------------------------------------------------//
  //     function for reading simple xyz format into geometry object    //
  // -------------------------------------------------------------------//
  
  template< int DIM, class VALTYPE=double>
  void read_xyz(std::basic_istream<CHAR,TRAITS> & inp, geometry<DIM,VALTYPE> & geom)
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
	    VALTYPE vv[nf];
	    std::basic_stringstream<CHAR,TRAITS> ss(s);
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
	STRING s1;
	VALTYPE x,y,z;
	std::basic_stringstream<CHAR,TRAITS> tmps(s);
	tmps >> s1 >> x >> y >> z;
	geom.add(s1,x,y,z);
      } 
  }
  
  // -------------------------------------------------------------------//  
  //                writing geometry into simple xyz                    //
  // -------------------------------------------------------------------//
  template< int DIM, class VALTYPE=double, class TRANSFORM >
  void write_xyz(std::basic_ostream<CHAR,TRAITS>  & out, 
		 const qpp::gen_geometry<DIM,VALTYPE,TRANSFORM> & geom)
  {
    out << geom.nat() << "\n";
    /*
    if (DIM>0)
      for (int d = 0; d<DIM; d++)
	for (int i=0; i<3; i++)
	  out << boost::format("%12.6f") % geom.cell(d,i);
    else
    */
    out << geom.name();
    out << "\n";
    for (int i=0; i<geom.size(); i++)
      out << boost::format("%-4s %12.6f %12.6f %12.6f\n") % geom.atom(i) % geom.coord(i)(0) 
	% geom.coord(i)(1) % geom.coord(i)(2);
  }

  // -------------------------------------------------------------------//
  //        writing geometry into xyz file together with displacements       //
  // -------------------------------------------------------------------//
  template< int DIM, class VALTYPE=double, class TRANSFORM  >
  void write_xyz(std::basic_ostream<CHAR,TRAITS>  & out, 
		 const qpp::gen_geometry<DIM,VALTYPE,TRANSFORM> & geom,
		 const qpp::molecule_vector<DIM,VALTYPE,TRANSFORM> & v)
  {
    out << geom.nat() << "\n";
    /*
    for (int d = 0; d<DIM; d++)
      for (int i=0; i<3; i++)
	out << boost::format("%12.6f") % geom.cell(d,i);
    */
    out << geom.name();
    out << "\n";
    for (int i=0; i<geom.size(); i++)
      out << boost::format("%-4s %12.6f %12.6f %12.6f atom_vector %12.6f %12.6f %12.6f\n") % geom.atom(i) 
	% geom.coord(i)(0) % geom.coord(i)(1) % geom.coord(i)(2) % v(i,0) % v(i,1) % v(i,2);
  }

};

#endif
