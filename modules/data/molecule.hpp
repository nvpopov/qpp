#ifndef _QPP_MOLECULE_H
#define _QPP_MOLECULE_H

#include <geom/geom.hpp>
#include <data/atom.hpp>
#include <basis/basis.hpp>

namespace qpp{

  template< int DIM, class CREAL=double, class TRANSFORM = periodic_cell<DIM,CREAL> >
  class molecule : public qpp_declaration{

  public:
    
    TRANSFORM * cell;
    geometry<DIM,CREAL,TRANSFORM> * geom;
    std::vector<qpp_atom*> atoms;

    molecule(const STRING & __name, qpp_object *__owner = NULL, 
	     qpp_param_array * __parm = NULL, 
	     int __line=-1, const STRING & __file=""):
      qpp_declaration("molecule",__name,__owner,__parm,__line,__file)
    {
      
    }

  };


};

#endif
