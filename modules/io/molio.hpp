#ifndef _QPP_MOLIO_H
#define _QPP_MOLIO_H

#include <lace/lace3d.hpp>
//#include <lace/lace.hpp>
#include <symm/symm.hpp>
#include <geom/geom.hpp>
#include <geom/molecule.hpp>
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

  //---------------------------------------------------------
  template<int DIM, class VALTYPE, typename _CharT = std::string::value_type, 
	   class _Traits = std::char_traits<_CharT> >
  class molecule_data_input{
  protected:
    std::basic_istream<_CharT, _Traits> *input;

  public:

    molecule_data_input(std::basic_istream<_CharT, _Traits>  & _input)
    {
      input = & _input;
    }

    ~molecule_data_input(){}

    virtual molecule<DIM,VALTYPE>* read() =0;

    virtual void read(molecule<DIM,VALTYPE> & mol) =0;

  };

  //---------------------------------------------------------
  template<int DIM, class VALTYPE, typename _CharT = std::string::value_type, 
	   class _Traits = std::char_traits<_CharT> >
  class molecule_data_output{
  protected:    
    std::basic_ostream<_CharT, _Traits> *output;
    
  public:
    
    molecule_data_output(std::basic_ostream<_CharT, _Traits>  & _output)
    {
      output = & _output;
    }

    ~molecule_data_output(){}

    virtual void write(molecule<DIM,VALTYPE> & mol) =0;

  };

  const int max_atomic_name_length = 80;

  // ----------------------- QPP Native format -------------------------

  template<int DIM, class VALTYPE, typename _CharT = std::string::value_type, 
	   class _Traits = std::char_traits<_CharT> >
  class qpp_molecule_output : public molecule_data_output<DIM,VALTYPE,_CharT,_Traits> {
    
    using molecule_data_output<DIM,VALTYPE,_CharT,_Traits>::output;

  public:
    
    qpp_molecule_output(std::ostream  & _output) : 
      molecule_data_output<DIM,VALTYPE,_CharT,_Traits>(_output)
    { }

    virtual void write(molecule<DIM,VALTYPE> & mol)
    {
      (*output) << "molecule " << mol.name << "{\n";

      if (DIM > 0)
	{
	  (*output) << "  vectors{\n"; 
	  for (int i=0; i<DIM; i++)
	    (*output) << boost::format("%12.6f %12.6f %12.6f\n") % 
	      mol.cell(i).x() % mol.cell(i).y() % mol.cell(i).z();
	  (*output) << "  }\n"; 
	}

      for (int t=0; t < mol.n_atom_types(); t++)
	(*output) << "  atom " << mol.atom_of_type(t).info() << "\n";

      (*output) << "  geometry{\n";

      for (int i=0; i < mol.size(); i++)
	(*output) << "    " << boost::format("%-10s %12.6f %12.6f %12.6f\n") % mol.atom(i).name 
	  % mol.coord(i)(0) % mol.coord(i)(1) % mol.coord(i)(2);

      (*output) << "  }\n}\n";
    }

  };

  // ------------------------- Simple xyz format ------------------------------

  template<int DIM, class VALTYPE, typename _CharT = std::string::value_type, 
	   class _Traits = std::char_traits<_CharT> >
  class xyz_molecule_input : public molecule_data_input<DIM,VALTYPE,_CharT,_Traits>{

    using molecule_data_input<DIM,VALTYPE,_CharT,_Traits>::input;

  public:

    xyz_molecule_input(std::basic_istream<_CharT,_Traits> &_input) :
      molecule_data_input<DIM,VALTYPE,_CharT,_Traits>(_input)
    {}

    
    virtual molecule<DIM,VALTYPE>* read()
    {

    }

    virtual void read(molecule<DIM,VALTYPE> & mol)
    {   
      //      std::cout << "xyz read\n";

      std::string s;
      std::getline(*input,s);
      int nat;
      std::stringstream(s) >> nat;
      std::getline(*input,s);

      //std::cout << "nat=" << nat << "\n";

      // fixme - check these are numbers!
      if (DIM==3)
	{
	  std::vector<std::string> fs;
	  boost::trim_left_if(s,boost::is_any_of(" \t"));
	  boost::split(fs, s, boost::is_any_of(" \t"),boost::token_compress_on);
	  
	  // for (int i=0; i<fs.size(); i++)
	  //  std::cout << i << fs[i] << "\n";
	  
	  int nf = fs.size();
	  if ( nf==9 || nf == 6 )
	    {
	      VALTYPE vv[nf];
	      for (int i=0; i<nf; i++) std::stringstream(fs[i]) >> vv[i];
	      if (nf==9)
		{
		  mol.cell(0) = lace::vector3d<VALTYPE>(vv[0],vv[1],vv[2]);
		  mol.cell(1) = lace::vector3d<VALTYPE>(vv[3],vv[4],vv[5]);
		  mol.cell(2) = lace::vector3d<VALTYPE>(vv[6],vv[7],vv[8]);
		}
	      else
		mol.cell() = periodic_cell<DIM,VALTYPE>(vv[0],vv[1],vv[2],vv[3],vv[4],vv[5]);
	    }
	  //std::cout << "vectors read\n";
	}
      for (int i = 0; i<nat; i++)
	{
	  std::getline(*input,s);
	  if (i==0)
	    {
	      // fixme - Analise the line, recognize .xyz type
	    }
	  char s1[max_atomic_name_length];
	  VALTYPE x,y,z;
	  std::stringstream tmps(s);
	  tmps >> s1 >> x >> y >> z;
	  mol.add(qpp_atom(s1),x,y,z);
	} 
    }

  };

};

#endif
