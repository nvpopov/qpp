#ifndef _QPP_MOLECULE_H
#define _QPP_MOLECULE_H

#include <geom/geom.hpp>
#include <string>
//#include <lace/lace.hpp>
#include <geom/atom.hpp>
#include <vector>

namespace qpp{
  
  template<int DIM, class VALTYPE>
  class molecule{ //: public geometry<DIM,VALTYPE>{
    
  public:
    
    // Molecule always has unique string identifier
    std::string name;
    // typedef qpp_atom ATOM;
    
    // Atomic type table
    // fixme - think about forming type table when atoms are added
  private:
    
    geometry<qpp_atom*,DIM,VALTYPE> *geom; 

    std::vector<qpp_atom*> atm_types;
    std::vector<int> type_table;

    // Neighbours table stuff
    std::vector<int> _nnbr;
    std::vector<std::vector<index<DIM> > > _nbr_table;
    lace::matrix<VALTYPE,lace::symmetric> _nbr_disttable;
    
  public:

    molecule(std::string _name, geometry<qpp_atom*,DIM,VALTYPE> * _geom = new geometry<qpp_atom*,DIM,VALTYPE>)
    {
      name = _name;
      geom = _geom;
    }

    // Atom list manipulation methods

    inline qpp_atom& atom(int i){return *(geom -> atom(i));}

    inline void add(const qpp_atom &a, const lace::vector3d<VALTYPE> & r)
    {
      geom->add_point(a.copy(),r);
    }

    void add(const qpp_atom &a,  VALTYPE _x,  VALTYPE _y,  VALTYPE _z)
    {
      //      atm.push_back(a.copy());
      geom->add_point(a.copy(),_x,_y,_z);
    }

    void del( int i)
    {
      delete geom->getatom(i);
      //      atm.erase(atm.begin()+i);
      geom->del_point(i);
    }

    void insert(int i, const qpp_atom &a, const lace::vector3d<VALTYPE> & r)
    {
      //      atm.insert(atm.begin()+i,a.copy());
      geom->insert_point(i,a.copy(),r);
    }
    
    void insert(int i, const qpp_atom &a, VALTYPE _x, VALTYPE _y, VALTYPE _z)
    {
      //      atm.insert(atm.begin()+i,a.copy());
      geom->insert_point(i,a.copy(),_x,_y,_z);
    }

    inline int size() const
    {
      return geom->size();
    }

    periodic_cell<DIM,VALTYPE> & cell()
    {
      return geom->cell;
    }

    lace::vector3d<VALTYPE> & cell(int i)
    {
      return geom->cell(i);
    }

    lace::vector3d<VALTYPE> coord(index<DIM> i)
    {
      return geom->full_coord(i);
    }


    //------------------- Type table manipulations -------------------------


    // Number of atomic types in molecule
    inline int n_atom_types() const
    {
      return atm_types.size();
    }
    
    // Reference to atom of type number t (not the atom number t in atomic list!)
    inline qpp_atom& atom_of_type(int t) const
    {
      return *(atm_types[t]);
    }

    // Number of type of certain ATOM at
    inline int type_of_atom(const qpp_atom & at) const
    {
      int t;
      for (t=0; t < atm_types.size(); t++)
	if ( *(atm_types[t]) == at )
	  break;
      if (t == atm_types.size())
	return -1;
      else 
	return t;
    }

    inline int atom_type_table(int i) const
    {return type_table[i];}


    virtual void build_type_table()
    {
      atm_types.clear();
      type_table.resize(size());

      for (int i=0; i<size(); i++)
	{
	  int t = type_of_atom(atom(i));
	  if (t == -1)
	    {
	      t = atm_types.size();
	      atm_types.push_back(&atom(i));
	    }
	  type_table[i] = t;
	}
      _nbr_disttable.resize(n_atom_types(),n_atom_types());
    }

    void clear_type_table()
    {
      atm_types.clear();
      type_table.resize(size());  
    }

    //-------------------  Neighbours table -----------

    // Number of neighbours of i-th atom
    inline int nnbr(int i){return _nnbr[i];}

    // j-th neighbour of i-th atom
    inline index<DIM> nbr_table(int i, int j){return _nbr_table[i][j];}

    // Largest distance for which atoms at1 and at2 are considered
    // to be neighbours
    // Can be used as lvalue, f.e.
    // nbr_distance("Si","O") = 2.7;
    inline VALTYPE & nbr_distance(qpp_atom & at1, qpp_atom & at2)
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
	  typename geometry<qpp_atom*,DIM,VALTYPE>::iterator j(geom);
	  for (j = j.begin(); j!=j.end(); j++)
	    if (j!=index<DIM>(i))
	      {
		VALTYPE r12 = lace::norm(geom->full_coord(i) - geom->full_coord(j));
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
		if ( r12 <= _nbr_disttable(atom_type_table(i),atom_type_table(j.atom())) )
		  {
		    _nbr_table[i].push_back(j);
		    _nnbr[i]++;
		  }
		//std::cout << "alive1\n";
	      }
	}
    }

  };

};

#endif
