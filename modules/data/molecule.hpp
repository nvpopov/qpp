#ifndef _QPP_MOLECULE_H
#define _QPP_MOLECULE_H

#include <vector>
#include <data/qppdata.hpp>
#include <geom/geom.hpp>
#include <data/atom.hpp>
#include <basis/basis.hpp>

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

    molecule(qpp_declaration * raw) :
      qpp_declaration("molecule", raw->name(), raw->owner(),
		      raw->parameters(), raw->line(), raw->file())
    {

      for (int i=0; i<raw->n_decl(); i++)
	//	add_decl( qpp_compile(*raw->decl(i)) );      
	add_decl( *raw->decl(i) );

      // Find geometry
      int i=0;
      bool found = false;
      for (i=0; i<raw->n_decl(); i++)
	if ((raw->decl(i)->gettype() & qtype_vectors) &&
	    (raw->decl(i)->name() == ""))
	  {
	    found = true;
	    break;
	  }
      if (found)
	cell = (TRANSFORM*)raw->decl(i);
      else
	{
	  cell = new TRANSFORM;
	  add_decl(*cell);
	}

      i=0; 
      found = false;
      for (i=0; i<raw->n_decl(); i++)
	if ((raw->decl(i)->gettype() & (qtype_geometry | qtype_xgeometry)) &&
	    (raw->decl(i)->name() == ""))
	  {
	    found = true;
	    break;
	  }
      if (found)
	geom = (geometry<DIM,CREAL,TRANSFORM>*)raw->decl(i);
      else
	{
	  geom = new geometry<DIM,CREAL,TRANSFORM>();
	  add_decl(*geom);
	}
      for (i=0; i<raw->n_decl(); i++)
	if (raw -> decl(i) -> category() == "atom")
	  {
	    //debug
	    //std::cout << "atom decl " << i << "\n";
	    atoms.push_back(new qpp_atom<FREAL>((qpp_declaration*)raw->decl(i), this));
	  }
      
    }

  };


};

#endif
