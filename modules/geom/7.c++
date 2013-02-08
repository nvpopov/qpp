#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/format.hpp>
//#include<iostream>
//#include <istream>
//#include <string>
//#include <streambuf>
#include<geom/geom.hpp>
#include<symm/shenflis.hpp>

const int namelength = 40;

template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
 //template <class ATOM, int DIM, class VALTYPE>
void read_xyz(std::basic_istream<_CharT, _Traits>  & inp, qpp::geometry<ATOM,DIM,VALTYPE> & geom)
{
  std::string s;
  std::getline(inp,s);
  int nat;
  std::stringstream(s) >> nat;
  std::getline(inp,s);
  for (int i = 0; i<nat; i++)
    {
      std::getline(inp,s);
      if (i==0)
	{
	  // Analise the line, recognize .xyz type
	}
      char s1[namelength];
      VALTYPE x,y,z;
      std::stringstream tmps(s);
      tmps >> s1 >> x >> y >> z;
      geom.add(ATOM(s1),x,y,z);
    } 
}

template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
void write_xyz(std::basic_ostream<_CharT, _Traits>  & out, qpp::geometry<ATOM,DIM,VALTYPE> & geom)
{
  out << geom.size() << "\n";
  for (int d = 0; d<DIM; d++)
    for (int i=0; i<3; i++)
      out << boost::format("%12.6f") % geom.cell(d,i);
  out << "\n";
  for (int i=0; i<geom.size(); i++)
    out << boost::format("%-4s %12.6f %12.6f %12.6f\n") % geom.atom(i) % geom.atom_coord(i)(0) 
	% geom.atom_coord(i)(1) % geom.atom_coord(i)(2);
}

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

int main()
{
  qpp::geometry<std::string,0,double> geom;
  std::ifstream inp("ch4.xyz");

  read_xyz(inp, geom);
  qpp::molecule_vector<std::string,0,double> v(&geom);

  //for (int i=0; i< geom.size(); i++)
  //  v(i) = geom.atom_coord(i);

  v(0,0) = -.2;
  v(1,0) = .5;

  qpp::shoenflis<double>::point_group G(qpp::shoenflis<double>::T());
  G.build_all();

  for (int g=0; g<G.size(); g++)
    {
      std::cout << G.notion(g) << "\n";
      write_xyz(std::cout, geom, G(g)*v);
    }
}

