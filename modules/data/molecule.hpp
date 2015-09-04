#ifndef _QPP_MOLECULE_H
#define _QPP_MOLECULE_H

#include <vector>
#include <data/qppdata.hpp>
#include <geom/geom.hpp>
#include <data/atom.hpp>
#include <basis/basis.hpp>
#include <io/compile.hpp>

namespace qpp{

  template< int DIM, class CREAL=double, class FREAL=double, class TRANSFORM = periodic_cell<DIM,CREAL> >
  class molecule : public qpp_declaration{

  public:
    
    TRANSFORM * cell;
    geometry<DIM,CREAL,TRANSFORM> * geom;
    std::vector<qpp_atom<FREAL>*> atoms;

    molecule(const STRING & __name, qpp_object *__owner = NULL, 
	     qpp_param_array * __parm = NULL, 
	     int __line=-1, const STRING & __file=""):
      qpp_declaration("molecule",__name,__owner,__parm,__line,__file)
    {
      
    }

    molecule(qpp_declaration * d) :
      qpp_declaration("molecule", d->name(), d->owner(),
		      d->parameters(), d->line(), d->file())
    {

      //debug
      //      std::cerr << "Molecule constructor\n";

      for (int i=0; i<d->n_decl(); i++) 
	//	add_decl( *qpp_compile(d->decl(i)) );      
	add_decl( *(d->decl(i)) );      
      /*
	{
	  // debug
	  std::cerr << "Molecule constructor: before compiled " << i << "\n";

	  qpp_object *rd = raw->decl(i);
	  rd->write(std::cerr);
	  std::cerr << "-------------sdfsdf---------------\n";

	  qpp_object * d = qpp_compile(rd);

	  add_decl( *d );      
	  
	  //debug
	  std::cerr << "Molecule constructor: compiled " << i << "\n";
	}
      */

      // Find geometry
      int i=0;
      bool found = false;

      //debug
      /*
      std::cerr << " ------------ Molecule: nested objects ----------------------\n";
      for (i=0; i<n_decl(); i++)
	std::cerr << "nested type = " << std::hex << decl(i)->gettype() << std::dec << "\n";
      */

      for (i=0; i<n_decl(); i++)
	if ((decl(i)->gettype() & qtype_vectors) &&
	    (decl(i)->name() == ""))
	  {
	    found = true;
	    break;
	  }
      if (found)
	cell = (TRANSFORM*)decl(i);
      else
	{
	  cell = new TRANSFORM;
	  add_decl(*cell);
	}

      i=0; 
      found = false;
      for (i=0; i<n_decl(); i++)
	if ((decl(i)->gettype() & (qtype_geometry | qtype_xgeometry)) &&
	    (decl(i)->name() == ""))
	  {
	    found = true;
	    break;
	  }
      if (found)
	geom = (geometry<DIM,CREAL,TRANSFORM>*)decl(i);
      else
	{
	  geom = new geometry<DIM,CREAL,TRANSFORM>();
	  add_decl(*geom);
	}
      for (i=0; i<n_decl(); i++)
	if (decl(i) -> gettype() & qtype_atom )
	  atoms.push_back( (qpp_atom<FREAL>*)decl(i) );
      
    }

    molecule(const molecule<DIM,CREAL,FREAL,TRANSFORM> & m)
    {
      //fixme - implement this
    }


  };


};

#endif
