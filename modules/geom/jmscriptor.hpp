#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <boost/format.hpp>
#include<geom/geom.hpp>
#include<symm/shenflis.hpp>

namespace qpp{

  const int namelength = 40;
  
  template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
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
  
  namespace jm
  {

    double length = 3e0;
    double delay = .1e0;
    int modsize=0;
    double bond=1.7;
    double hbond=1.1;
    
    bool movie = false;
    std::string imgfile;
    int img=0;

    int nstep=30;

    template <typename _CharT, class _Traits>
    void axis(std::basic_ostream<_CharT, _Traits>  & out, lace::vector3d<double> n, 
	      std::string name = "")
    {
      double l = length;
      n = n/lace::norm(n);
      out << "draw " << name << " line {" << -l*n(0) << " " << -l*n(1) << " " << -l*n(2) << "}{"<< l*n(0) << " " << l*n(1) << " " << l*n(2) << "} \">" << name << "\"\n";
    }

    template <typename _CharT, class _Traits>
    void sigma(std::basic_ostream<_CharT, _Traits>  & out, lace::vector3d<double> n, 
	       std::string name = "")
    {
      double l = length*std::sqrt(2e0);
      n = n/lace::norm(n);
      lace::vector3d<double> m(1,0,0);
      if (lace::abs(lace::scal(n,m)) > 1e0-1e-4)
	m = lace::vector3d<double>(0,1,0);
      m = m - n*lace::scal(n,m);
      m = m/lace::norm(m);
      lace::vector3d<double> k = m%n;
      out << "draw " << name << " plane {"<< -l*m(0) << " " << -l*m(1) << " " << -l*m(2) << "}{"<< -l*k(0) << " " << -l*k(1) << " " << -l*k(2) << "}{"<< l*m(0) << " " << l*m(1) << " " << l*m(2) << "}{"<< l*k(0) << " " << l*k(1) << " " << l*k(2) << "}  color translucent [100 100 200]\n";
    }

    template <typename _CharT, class _Traits>
    void Cn(std::basic_ostream<_CharT, _Traits>  & out, int n)
    {
      double l = length;
      out << "draw c" << n << " line {0 0 " << -l << "}{0 0 " << l << "} \">C" << n << "\"\n";
    }

    template <typename _CharT, class _Traits>
    void U2(std::basic_ostream<_CharT, _Traits>  & out, int n, int i)
    {
      double l = length;
      double phi = pi*i/n;
      double x = l*std::cos(phi), y = l*std::sin(phi);
      out << "draw U" << i << " line {" << -x << " " << -y  << " 0} {" << x << " " << y  << " 0}\">U2\"\n";
    }   

    template <typename _CharT, class _Traits>
    void sig_h(std::basic_ostream<_CharT, _Traits>  & out)
    {
      double l = length;
      out << "draw sigh plane {"<< -l << " " << -l << " 0 } { "<< -l << " " << l << " 0 } { "<< l << " " << l << " 0 } { "<< l << " " << -l << " 0 } color translucent [100 100 200]\n";
    }

    template <typename _CharT, class _Traits>
    void sig_v(std::basic_ostream<_CharT, _Traits>  & out, int n, int i)
    {
      double l = length;
      double phi = pi*i/n;
      double x = l*std::cos(phi), y = l*std::sin(phi);
      out << "draw sigv" << i << "  plane {"<< -x << " " << -y << " " << -l << "} { "<< -x << " " << -y << " " << l << "} { "<< x << " " << y << " " << l << "} { "<< x << " " << y << " " << -l << "} color translucent [100 100 200]\n";
    }

    template <typename _CharT, class _Traits>
    void sig_d(std::basic_ostream<_CharT, _Traits>  & out, int n, int i)
    {
      double l = length;
      double phi = pi*(i+.5)/n;
      double x = l*std::cos(phi), y = l*std::sin(phi);
      out << "draw sigd" << i << "  plane {"<< -x << " " << -y << " " << -l << "} { "<< -x << " " << -y << " " << l << "} { "<< x << " " << y << " " << l << "} { "<< x << " " << y << " " << -l << "} color translucent [100 100 200]\n";
    }

    template <typename _CharT, class _Traits>
    void reconnect(std::basic_ostream<_CharT, _Traits>  & out)
    {
      out << "connect;";
    }

    template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
    void load(std::basic_ostream<_CharT, _Traits>  & out, qpp::geometry<ATOM,DIM,VALTYPE> & geom)
    {
      out << "set appendNew false\n";
      out << "load append inline \"" << geom.size() << " \\n\\n" ;
      for (int i=0; i<geom.size(); i++)
	out << boost::format("%-4s %12.6f %12.6f %12.6f") % geom.atom(i) % geom.atom_coord(i)(0) 
	  % geom.atom_coord(i)(1) % geom.atom_coord(i)(2) << "\\n";
      out << "\"\n";
      modsize += geom.size();
    }
      
    template <typename _CharT, class _Traits>
    void wait(std::basic_ostream<_CharT, _Traits>  & out)
    {
      out << "wait\n";
    }

    template <typename _CharT, class _Traits>
    void jpeg(std::basic_ostream<_CharT, _Traits>  & out)
    {
      std::stringstream fname;      
      //      fname.setf('0');
      fname << imgfile;
      if (img < 10)
	fname << "000";
      else if (img < 100)
	fname << "00";
      else if (img < 1000)
	fname << "0";
      fname << img++ << ".gif";
      std::cout << fname.str() << "\n";;
      out << "write IMAGE GIF \"" << fname.str() << "\";";
    }

    template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
    void rotate(std::basic_ostream<_CharT, _Traits>  & out, qpp::geometry<ATOM,DIM,VALTYPE> & geom, 
		lace::vector3d<VALTYPE> n, VALTYPE phi, std::vector<int> * select = NULL)
    {
      std::vector<int> sel;
      if ( select == NULL)
	for (int i=0; i<geom.size(); i++)
	  sel.push_back(i);
      else
	sel = *select;
      out << "select atomno=" << sel[0]+1;
      for  (int i=1; i<sel.size(); i++)
	out << " or atomno=" << sel[i]+1;
      out << "\nfor (var i=1; i<=15; i++){rotateselected molecular axisangle {" << n(0) << " " << n(1) << " " << n(2) << " " << phi/15 << "};"; 
      if (movie) jpeg(out);	
      out<<" delay 0.1}\n";

      reconnect(out);
      for (int i=0; i<sel.size(); i++)
	{
	  int j = sel[i];
	  geom.atom_coord(j) = lace::RotMtrx(n,-pi*phi/180)*geom.atom_coord(j);
	}
    }

    template <typename _CharT, class _Traits>
    void selatoms(std::basic_ostream<_CharT, _Traits>  & out, std::vector<int> select)
    {
      out << "select atomno=" << select[0]+1;
      for  (int i=1; i<select.size(); i++)
	out << " or atomno=" << select[i]+1;
    }
		 
    template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
    void reflect(std::basic_ostream<_CharT, _Traits>  & out, qpp::geometry<ATOM,DIM,VALTYPE> & geom, 
		lace::vector3d<VALTYPE> n,  std::vector<int> * select = NULL)
    {
      lace::matrix3d<VALTYPE> Sigma = lace::Sigma(n);

      std::vector<int> sel;
      if ( select == NULL)
	for (int i=0; i<geom.size(); i++)
	  sel.push_back(i);
      else
	sel = *select;

      std::vector<int> ref;
      for (int i=0; i<sel.size(); i++)
	ref.push_back(modsize  + i);

      qpp::geometry<ATOM,DIM,VALTYPE> newat;
      for (int i=0; i<sel.size(); i++)
	{
	  int j = sel[i];
	  newat.add(geom.atom(j),Sigma*geom.atom_coord(j));
	}

      load(out,newat);
      
      selatoms(out,ref);
      out << "; color translucent 8\n";

      out << "for (var i = 0; i < 10; i++) {";
      selatoms(out,sel); 
      out << "; color translucent @i;";
      selatoms(out,ref);
      out << "; color translucent @{9-i};if (@i==2){";
      for (int i=0; i<sel.size(); i++)
	out << "connect (atomno=" << sel[i]+1 << ") (atomno=" 
	    << ref[i]+1 << ");";
      out << "} if (@i==6){";
      for (int i=0; i<sel.size(); i++)
	out << "connect (atomno=" << sel[i]+1 << ") (atomno=" 
	    << ref[i]+1 << ") delete;";
      out << "}  delay 0.1}";
 
      for (int i=sel.size()-1; i>=0; i--)
	{
	  int j = sel[i];
	  lace::vector3d<VALTYPE> r = geom.atom_coord(j), r1 = Sigma*r;
	  geom.atom_coord(j) = r1;
	  r1 = r1 - r;
	  out << "select atomno=" << j+1 << "; translateselected{" 
	      << r1(0) << " " << r1(1) << " " << r1(2) << "}; color translucent 0; delete atomno=" 
	      << ref[i] + 1 << ";";	  
	}
      reconnect(out);

    }

    template <typename _CharT, class _Traits>
    void enter(std::basic_ostream<_CharT, _Traits>  & out)
    {
      out << "\n";
    }

    template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
    void vectors(std::basic_ostream<_CharT, _Traits>  & out, molecule_vector<ATOM,DIM,VALTYPE> & vec)
    {
      for (int i=0; i < vec.geom()->size(); i++)
	out << "draw v" << i << " vector {atomno=" << i+1 << "}{" 
	    << vec(i,0) << " " << vec(i,1) << " " << vec(i,2) << "};";
    } 

    template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
    void hide_vectors(std::basic_ostream<_CharT, _Traits>  & out, molecule_vector<ATOM,DIM,VALTYPE> & vec, std::vector<int> * select)
    {
      if (select == NULL)
	for (int i=0; i < vec.geom()->size(); i++)
	  out << "draw v" << i << " off;";
      else 
	for (int i=0; i < select->size(); i++)
	  {
	    out << "draw v" << (*select)[i] << " off;";
	  }
    }
   
    template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
    void rotate(std::basic_ostream<_CharT, _Traits>  & out, qpp::geometry<ATOM,DIM,VALTYPE> & geom, 
		lace::vector3d<VALTYPE> n, VALTYPE phi, molecule_vector<ATOM,DIM,VALTYPE> & vec,
		std::vector<int> * select = NULL)
    {
      std::vector<int> sel;
      if ( select == NULL)
	for (int i=0; i<geom.size(); i++)
	  sel.push_back(i);
      else
	sel = *select;
      out << "select atomno=" << sel[0]+1;
      for  (int i=1; i<sel.size(); i++)
	out << " or atomno=" << sel[i]+1;
      out << "\n";
      for (int i=1; i<=nstep; i++)
	{
	  out << "rotateselected molecular axisangle {" << n(0) << " " << n(1) << " " << n(2) << " " << phi/nstep << "};"; 
	  molecule_vector<ATOM,DIM,VALTYPE> vec1=vec;
	  for (int k=0; k<sel.size(); k++)
	    {
	      int j = sel[k];
	      vec1(j) = lace::RotMtrx(n,-pi*phi*i/(180*nstep))*vec(j);
	    }
	  vectors(out,vec1);
	  if (movie) jpeg(out);
	}
      out <<  "connect;";      

      for (int i=0; i<sel.size(); i++)
	{
	  int j = sel[i];
	  geom.atom_coord(j) = lace::RotMtrx(n,-pi*phi/180)*geom.atom_coord(j);
	} 
	for (int i=0; i<sel.size(); i++)
	  {
	    int j = sel[i];
	    vec(j) = lace::RotMtrx(n,-pi*phi/180)*vec(j);
	  }
    }

    template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
    void reflect(std::basic_ostream<_CharT, _Traits>  & out, qpp::geometry<ATOM,DIM,VALTYPE> & geom, 
		 lace::vector3d<VALTYPE> n,  molecule_vector<ATOM,DIM,VALTYPE> & vec, 
		 std::vector<int> * select = NULL)
    {
      hide_vectors(out,vec,select);
      reflect(out,geom,n,select);
      if (select == NULL)
	for (int i=0; i<vec.size(); i++)
	  vec(i) = lace::Sigma(n)*vec(i);
      else
	for (int i=0; i<select->size(); i++)
	  {
	    int j = (*select)[i];
	    vec(j) = lace::Sigma(n)*vec(j);
	  }
      vectors(out,vec);
    }


    template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
    void refplicate(std::basic_ostream<_CharT, _Traits>  & out, qpp::geometry<ATOM,DIM,VALTYPE> & geom, 
		    lace::vector3d<VALTYPE> n,  std::vector<int> * select = NULL)
    {
      lace::matrix3d<VALTYPE> Sigma = lace::Sigma(n);

      std::vector<int> sel;
      if ( select == NULL)
	for (int i=0; i<geom.size(); i++)
	  sel.push_back(i);
      else
	sel = *select;

      std::vector<int> ref;
      for (int i=0; i<sel.size(); i++)
	ref.push_back(modsize  + i);

      qpp::geometry<ATOM,DIM,VALTYPE> newat;
      for (int i=0; i<sel.size(); i++)
	{
	  int j = sel[i];
	  newat.add(geom.atom(j),Sigma*geom.atom_coord(j));
	}

      load(out,newat);
      
      selatoms(out,ref);
      out << "; color translucent 8\n";

      //      out << "for (var i = 0; i < 10; i++) {";
      for (int i=0; i<10; i++)
	{
	  selatoms(out,sel); 
	  out << "; color translucent "<<i<<";";
	  selatoms(out,ref);
	  out << "; color translucent "<<9-i<<";";
	  if (i==2)
	    for (int j=0; j<sel.size(); j++)
	      out << "connect (atomno=" << sel[j]+1 << ") (atomno=" 
		  << ref[j]+1 << ");";
	  if (i==6)
	    for (int j=0; j<sel.size(); j++)
	      out << "connect (atomno=" << sel[j]+1 << ") (atomno=" 
		  << ref[j]+1 << ") delete;";
	  out << "  delay 0.1\n";
	  if (movie)
	    jpeg(out);
	}
      for (int i=0; i< sel.size(); i++)
	{
	  geom.add(newat.atom(i),newat.atom_coord(i));
	  out << "select atomno=" << sel[i]+1 << "; color translucent 0;";	  
	}
      if (movie)
	jpeg(out);

      reconnect(out);
    }

    template <class ATOM, int DIM, class VALTYPE, typename _CharT, class _Traits>
    void rotplicate(std::basic_ostream<_CharT, _Traits>  & out, qpp::geometry<ATOM,DIM,VALTYPE> & geom, 
		    lace::vector3d<VALTYPE> n, VALTYPE phi, std::vector<int> * select = NULL)
    {
      std::vector<int> sel;
      if ( select == NULL)
	for (int i=0; i<geom.size(); i++)
	  sel.push_back(i);
      else
	sel = *select;

      qpp::geometry<ATOM,DIM,VALTYPE> newat;
      for (int i=0; i<sel.size(); i++)
	{
	  int j = sel[i];
	  newat.add(geom.atom(j),geom.atom_coord(j));
	}

      load(out,newat);

      out << "select atomno=" << geom.size()+1;
      for  (int i=1; i<sel.size(); i++)
	out << " or atomno=" << geom.size()+i+1;
      for (int i=1; i<=nstep; i++)
	{
	  out << "\nrotateselected molecular axisangle {" << n(0) << " " << n(1) << " " << n(2) << " " << phi/nstep << "}; delay 0.1\n";
	  if (movie)
	    jpeg(out);
	}
      reconnect(out);
      if (movie)
	    jpeg(out);
      for (int i=0; i<sel.size(); i++)
	geom.add(newat.atom(i),lace::RotMtrx(n,-pi*phi/180)*newat.atom_coord(i));
    }

  };
  
};
