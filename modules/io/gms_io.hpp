#ifndef _QPP_GMS_IO
#define _QPP_GMS_IO

#include <io/molio.hpp>
#include <boost/format.hpp>

namespace qpp{

  template <int DIM, class CREAL=double, class FREAL=double, 
	    class TRANSFORM = periodic_cell<DIM,CREAL> >
  class molwriter_gms_input : public molecule_data_output<DIM,CREAL,FREAL,TRANSFORM>{
  protected:
    using molecule_data_output<DIM,CREAL,FREAL,TRANSFORM>::_output;
    using molecule_data_output<DIM,CREAL,FREAL,TRANSFORM>::_output_name;
  public:
    molwriter_gms_input(OSTREAM  & __output) :
      molecule_data_output<DIM,CREAL,FREAL,TRANSFORM>(__output)
    {}

    molwriter_gms_input(const STRING & __output_name):
      molecule_data_output<DIM,CREAL,FREAL,TRANSFORM>(__output_name)
    {
      _output = new OFSTREAM(_output_name.c_str());
    }

    virtual void write_shell(const qpp_shell<qbas_gauss,FREAL> & sh)
    {
      bool lshell = false;
      if (sh.nshells()==2 && sh.l(0)==0 && sh.l(1)==1)
	lshell = true;

      for (int s = 0; s < (lshell ? 1 : sh.nshells() ); s++)
	{
	  STRING lbl;
	  if (lshell)
	    lbl = "L";
	  else
	    switch(sh.l(s))
	      {
	      case 0: lbl = "S"; break;
	      case 1: lbl = "P"; break;
	      case 2: lbl = "D"; break;
	      case 3: lbl = "F"; break;
	      }

	  *_output << boost::format("%7s  %4i") % lbl % sh.nprim() << std::endl;
	  for (int i=0; i<sh.nprim(); i++)
	    {
	      *_output << boost::format("%4i %13.6f %10.6f") % 
		(i+1) % sh.alpha(i) % sh.coeff(s,i);
	      if (lshell)
		*_output << boost::format(" %10.6f") % sh.coeff(1,i);
	      *_output << std::endl;
	    }
	}
    }

    void write_data(molecule<DIM,CREAL,FREAL,TRANSFORM> & mol)
    {
      xtr_geometry<DIM,CREAL,TRANSFORM> * xgeom = NULL;
      bool haschrg = false;
      if (mol.geom->gettype() & qtype_xgeometry)
	{
	  xgeom = (xtr_geometry<DIM,CREAL,TRANSFORM>*)mol.geom;
	  haschrg = xgeom->has_charges();
	}

      *_output << " $data" << std::endl << mol.name()  << std::endl << "c1"  << std::endl;
      for (int n=0; n<mol.geom->nat(); n++)
	{
	  CREAL q=0e0;
	  if (haschrg)
	    q = xgeom->charge(n);
	  else if (mol.atoms[mol.type_idx[mol.geom->type(n)]]->classical != NULL)
	    q = mol.atoms[mol.type_idx[mol.geom->type(n)]]->classical->charge;
	  lace::vector3d<CREAL> r = mol.geom->position(n);
	  *_output << boost::format("%-10s %8.5f %13.8f %13.8f %13.8f") % mol.geom->atom(n) % 
	    q % r.x() % r.y() % r.z() << std::endl;
	}
    }

    virtual void write(molecule<DIM,CREAL,FREAL,TRANSFORM> & mol)
    {
      // data section      
    }

  };

};
#endif
