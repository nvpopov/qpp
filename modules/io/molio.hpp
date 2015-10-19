#ifndef _QPP_MOLIO_H
#define _QPP_MOLIO_H

#include <lace/lace3d.hpp>
//#include <lace/lace.hpp>
#include <data/qppdata.hpp>
//#include <symm/symm.hpp>
#include <geom/geom.hpp>
#include <data/molecule.hpp>

namespace qpp{

  //---------------------------------------------------------
  template <int DIM, class CREAL=double, class FREAL=double, 
	    class TRANSFORM = periodic_cell<DIM,CREAL> >
  class molecule_data_input{
  protected:
    ISTREAM *_input;
    STRING _input_name;

  public:

    molecule_data_input(ISTREAM  & __input)
    {
      _input = & __input;
      _input_name = "";
    }

    molecule_data_input(const STRING & __input_name)
    {
      _input_name = __input_name;
      _input = NULL;
    }

    ~molecule_data_input(){}

    virtual molecule<DIM,CREAL,FREAL,TRANSFORM>* read() =0;

    virtual void read(molecule<DIM,CREAL,FREAL,TRANSFORM> & mol) =0;

  };

  //---------------------------------------------------------

  template <int DIM, class CREAL=double, class FREAL=double, 
	    class TRANSFORM = periodic_cell<DIM,CREAL> >
  class molecule_data_output{
  protected:    
    OSTREAM *_output;
    STRING _output_name;
    
  public:
    
    molecule_data_output(OSTREAM  & __output)
    {
      _output = & __output;
      _output_name = "";
    }

    molecule_data_output(const STRING & __output_name)
    {
      _output_name = __output_name;
      _output = NULL;
    }

    ~molecule_data_output(){}

    virtual void write(molecule<DIM,CREAL,FREAL,TRANSFORM> & mol) =0;

  };

  const int max_atomic_name_length = 80;

  // ----------------------- QPP Native format -------------------------
  /*
  template <int DIM, class CREAL=double, class FREAL=double, 
	    class TRANSFORM = periodic_cell<DIM,CREAL> >
  class qpp_molecule_output : public molecule_data_output<DIM,CREAL,FREAL,TRANSFORM> {
    
    using molecule_data_output<DIM,CREAL,FREAL,TRANSFORM>::_output;
    using molecule_data_output<DIM,CREAL,FREAL,TRANSFORM>::_output_name;

  public:
    
    qpp_molecule_output(OSTREAM  & __output) : 
      molecule_data_output<DIM,VALTYPE,_CharT,_Traits>(__output)
    {}

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
  */
  // ------------------------- Simple xyz format ------------------------------
  /*
  template <int DIM, class CREAL=double, class FREAL=double, 
	    class TRANSFORM = periodic_cell<DIM,CREAL> >
  class xyz_molecule_input : public molecule_data_input<DIM,CREAL,FREAL,TRANSFORM>{

    using molecule_data_input<DIM,CREAL,FREAL,TRANSFORM>::_input;
    using molecule_data_input<DIM,CREAL,FREAL,TRANSFORM>::_input_name;

  public:

    xyz_molecule_input(ISTREAM &__input) :
      molecule_data_input<DIM,CREAL,FREAL,TRANSFORM>(_input)
    {}

    xyz_molecule_input(const STRING &__input_name) :
      molecule_data_input<DIM,CREAL,FREAL,TRANSFORM>(__input_name)
    {
      _input = new IFSTREAM(_input_name);
    }

    
    virtual molecule<DIM,CREAL,FREAL,TRANSFORM>* read()
    {
    }

    virtual void read(molecule<DIM,CREAL,FREAL,TRANSFORM> & mol)
    {   
      //      std::cout << "xyz read\n";

      STRING s;
      std::getline(*_input,s);
      int nat;
      SSTREAM(s) >> nat;
      std::getline(*_input,s);

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
	      CREAL vv[nf];
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
	  CHAR s1[max_atomic_name_length];
	  CREAL x,y,z;
	  SSTREAM tmps(s);
	  tmps >> s1 >> x >> y >> z;
	  mol.add(s1,x,y,z);
	} 
    }

  };
  */
};

#endif
