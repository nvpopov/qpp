#ifndef _QPP_MOLECULE_H
#define _QPP_MOLECULE_H

#include <geom/geom.hpp>
#include <string>
#include <lace/lace.hpp>

namespace qpp{
  
  template<class ATOM, int DIM, class VALTYPE>
  class molecule : public geometry<ATOM,DIM,VALTYPE>{

  public:

    //typedef index<DIM> index;
    typedef typename geometry<ATOM,DIM,VALTYPE>::iterator iterator;
    using geometry<ATOM,DIM,VALTYPE>::natm_types;
    using geometry<ATOM,DIM,VALTYPE>::size;
    using geometry<ATOM,DIM,VALTYPE>::coord;
    using geometry<ATOM,DIM,VALTYPE>::atm_type_table;

    // Molecule has unique string identifier
    std::string name;

    // Neighbours table

  private:

    std::vector<int> _nnbr;
    std::vector<std::vector<index<DIM> > > _nbr_table;
    lace::matrix<VALTYPE,lace::symmetric> _nbr_disttable;
    
  public:

    // Number of neighbours of i-th atom
    inline int nnbr(int i){return _nnbr[i];}

    // j-th neighbour of i-th atom
    inline index<DIM> nbr_table(int i, int j){return _nbr_table[i][j];}

    // Largest distance for which atoms at1 and at2 are considered
    // to be neighbours
    // Can be used as lvalue, f.e.
    // nbr_distance("Si","O") = 2.7;
    inline VALTYPE & nbr_distance(ATOM at1, ATOM at2)
    {return _nbr_disttable(type_of_atom(at1),type_of_atom(at2));}

    // Set all neighbours distances to one value
    void set_default_nbr_distance(VALTYPE dist)
    {
      _nbr_disttable = dist;

      //    for (int i=0; i<_nbr_disttable.size(0); i++)
      //	{
      //	  for (int j=0; j<_nbr_disttable.size(1); j++)
      //	    std::cout << _nbr_disttable(i,j);
      //	  std::cout << "\n";
      //	}
    }

    void build_nbr_table()
    {
      //fixme - very inefficient!!!
      _nnbr.resize(size());
      //     std::cout << size() << "\n";
      _nbr_table.resize(size());
      for (int i=0; i<size(); i++)
	{
	  _nbr_table[i].clear();
	  _nnbr[i]=0;
	}

      for (int i=0; i<size(); i++)
	{
	  //	  std::cout << i <<"\n";
	  iterator j(*this);
	  for (j = j.begin(); j!=j.end(); j++)
	    if (j!=index<DIM>(i))
	      {
		VALTYPE r12 = lace::norm(coord(i) - coord(j));
		//std::cout << j.atom();
		//for (int k=0; k < DIM; k++)
		//  std::cout << " " << j.cell(k);
		//std::cout << "\n";
		//std::cout << "r(i)=" << coord(i) << "\n";
		//std::cout << "r(j)=" << coord(j) << "\n";
		//std::cout << "r(i-j)=" << coord(i)-coord(j) << "\n";
		//std::cout << "t1=" << atm_type_table(i) << " t2=" << atm_type_table(j) 
		//	  << " r12=" <<_nbr_disttable(atm_type_table(i),atm_type_table(j))
		//	  << "\n";
		//std::cout << "alive\n";
		if ( r12 <= _nbr_disttable(atm_type_table(i),atm_type_table(j.atom())) )
		  {
		    _nbr_table[i].push_back(j);
		    _nnbr[i]++;
		  }
		//std::cout << "alive1\n";
	      }
	}
    }

    virtual void build_type_table()
    {
      geometry<ATOM,DIM,VALTYPE>::build_type_table();
      _nbr_disttable.resize(natm_types(),natm_types());
      //      std::cout << natm_types() << "\n";
    }

  };

};

#endif
