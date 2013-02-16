#ifndef _QPP_PERIODIC_H
#define _QPP_PERIODIC_H

#include <lace/lace3d.hpp>

namespace qpp{

  // The struct to store 1, 2 or 3 translation vectors
  template<class VALTYPE=double>
  struct periodic_cell{
    int dim;
    lace::vector3d<VALTYPE> v[3];
    
    //Constructors

    periodic_cell()
    {
      dim=0;
    }

    periodic_cell(lace::vector3d<VALTYPE> a)
    {
      dim=1;
      v[0] = a;
    }

    periodic_cell(lace::vector3d<VALTYPE> a, lace::vector3d<VALTYPE> b)
    {
      dim=2;
      v[0] = a;
      v[1] = b;
    }

    periodic_cell(lace::vector3d<VALTYPE> a, lace::vector3d<VALTYPE> b, lace::vector3d<VALTYPE> c)
    {
      dim=3;
      v[0] = a;
      v[1] = b;
      v[2] = c;
    }

    periodic_cell(VALTYPE a, VALTYPE b, VALTYPE c,
		  VALTYPE alpha, VALTYPE beta, VALTYPE gamma)
    // for DIM==3
    {
      dim=3;
      v[0] = lace::vector3d<VALTYPE>(a,VALTYPE(0),VALTYPE(0));
      v[1] = lace::vector3d<VALTYPE>(b*std::cos(gamma), b*std::sin(gamma),
				     VALTYPE(0));
      VALTYPE nx = std::cos(beta);
      VALTYPE ny = (std::cos(alpha) - nx*std::cos(gamma))/std::sin(gamma);
      VALTYPE nz = std::sqrt(1-nx*nx-ny*ny);
      v[2] = lace::vector3d<VALTYPE>(nx,ny,nz)*c;
    }

    inline lace::vector3d<VALTYPE> & operator()(int i)
    { 
      assert( i>=0 && i<dim && "Illegal dimension in periodic cell access operator");
      return v[i]; 
    } 

    inline VALTYPE & operator()(int i, int j)
    { return v[i](j); }
    
    inline lace::vector3d<VALTYPE> frac2cart(lace::vector3d<VALTYPE> frac)
    // transforms fractional coordinates to cartesian
    // only works for DIM==3
    // fixme - add the check here
    {
      assert(dim==3 && "frac2cart works only for 3d-periodicity");
      return frac(0)*v[0] + frac(1)*v[1] + frac(2)*v[2];
    }

    inline lace::vector3d<VALTYPE> frac2cart(VALTYPE f1, VALTYPE f2 = VALTYPE(0), VALTYPE f3 = VALTYPE(0))
    // fractional to cartesian coordinates
    // works for DIM=1,2,3
    // here we use simple_vector to pass fractional coords
    {
      lace::vector3d<VALTYPE> res = VALTYPE(0);
      if (dim>0) res += f1*v[0];
      if (dim>1) res += f2*v[1];
      if (dim==3) res += f3*v[2];
      return res;
    }

    inline lace::vector3d<VALTYPE> cart2frac(lace::vector3d<VALTYPE> r)
    // cartesian to fractional
    // works for DIM==3 only
    { 
      assert(dim==3 && "cart2frac works only for 3d-periodicity");
      lace::matrix3d<VALTYPE> A(v[0],v[1],v[2]);
      return lace::solve3d(A, r);
    }

    inline lace::vector3d<VALTYPE> reduce(lace::vector3d<VALTYPE> r)  
    // Brings the point r into the volume of unit cell
    // by translations
    // unit cell is defined as parallelepiped with one vertex in
    // the coordinate origin
    // the others are pointed by v[0],v[1],v[2] vectors
    {
      lace::vector3d<VALTYPE> f = cart2frac(r);
      f(0) -= int(f(0));
      f(1) -= int(f(1));
      f(2) -= int(f(2));
      return frac2cart(f);
    }

    inline lace::vector3d<VALTYPE> reduce_cntr(lace::vector3d<VALTYPE> r)  
    // Brings the point r into the volume of unit cell
    // by translations
    // unit cell is defined as parallelepiped CENTRED in the
    // coordinate origin
    {
      lace::vector3d<VALTYPE> f = cart2frac(r);
      for (int i=0; i<3; i++)
        {
          f(i) -= int(f(i));
          if ( f(i) > VALTYPE(1)/2 ) f(i)-=1;
        }
      return frac2cart(f);
    }

    inline lace::vector3d<VALTYPE> reduce_wz(lace::vector3d<VALTYPE> r)  
    // Brings r into Wigner-Zeitz unit cell
    // fixme - implement this!
    {}

    inline bool in_cell(lace::vector3d<VALTYPE> r)
    // Answers the question whether r belongs to the unit cell
    {
      lace::vector3d<VALTYPE> f = cart2frac(r);
      return 
        VALTYPE(0)<=f(0) && f(0) < VALTYPE(1) &&
        VALTYPE(0)<=f(1) && f(1) < VALTYPE(1) &&
        VALTYPE(0)<=f(2) && f(2) < VALTYPE(1);  
    }


    inline bool in_cell_cntr(lace::vector3d<VALTYPE> r)
    // does r belong to unit cell centred at the coords origin?
    {
      lace::vector3d<VALTYPE> f = cart2frac(r);
      return 
        -VALTYPE(1)/2 <= f(0) && f(0) < VALTYPE(1)/2 &&
        -VALTYPE(1)/2 <= f(1) && f(1) < VALTYPE(1)/2 &&
        -VALTYPE(1)/2 <= f(2) && f(2) < VALTYPE(1)/2;   
    }

    inline bool in_cell_wz(lace::vector3d<VALTYPE> r)
    // does r belong to Wigner-Zeitz unit cell
    // fixme - implement this!
    {}

  };

  //--------------------------------------------------------------//

  template<typename VALTYPE>
  class rotrans
  {

  };

  //--------------------------------------------------------------//


  // The geometry class stores atoms together with their
  // coordinates. As POINT is a template parameter, you can
  // use almost everything as POINT, even emply class.
  //
  // In this latter case you get just points with coordinates
  // Such object can be used to store, say, displacement 
  // vectors or vibrational mode vectors.
  //
  // If POINT is something more substatial, you can store any information
  // about atoms as well

  // geometry is an ancestor for molecule

  template<class POINT, class VALTYPE>
  class geometry{

    int nat;
    // Number of atoms/points

    std::vector<POINT> _atoms;
    // Storage for atoms/points

    std::vector<lace::vector3d<VALTYPE> > _coords;
    // Storage for coordinates

  public:
    periodic_cell<VALTYPE> cell;
    // Unit cell vectors for 1,2,3d periodicity


    // ------------------- index class ----------------------
    // Index is a handy tool to reference atoms in this geometry
    // as well as atoms in neighbouring cells
    // For that purpose it is a complex index - it contains, besides
    // the number of atom it is currently pointning at, also the 
    // indicies of the cell.
    class index{
    protected:
      int dim, pt, cl[3];
      
    public:
      inline index& operator=(int _at)
      {
	at=_at;
	if (dim>0)
	  cl(0)=0;
	if (dim>1)
	  cl(1)=0;
	if (dim>2)
	  cl(2)=0;
	return *this;
      }
    
      inline int atom(){return at;}
    
      inline int cell(int d){return cl(d);}
    
      inline void set(int _at, int i1=0, int i2=0, int i3=0)
      {
	at=_at;
	if (dim>0)
	  cl(0)=i1;
	if (dim>1)
	  cl(1)=i2;
	if (dim>2)
	  cl(2)=i3;
      }
    
    inline void setatom(int _at){at=_at;}
    
    inline void setcell(int d, int i){cl(d)=i;}
    
    index(){
      dim = 0;
    }
    
    index(int _at, int i1=0, int i2=0, int i3=0)
    {
      //	_check();
      set(_at,i1,i2,i3);
    }      
    
    inline bool operator==(index i)
    {
      if (dim != i.dim)
	return false;
      else if (dim==0)
	return at == i.at;
      else if (dim==1)
	return at == i.at && cll(0) == i.cll(0);
      else if (dim==2)
	return at == i.at && cll(0) == i.cll(0) && cll(1) == i.cll(1);
      else if (dim==3)
	return at == i.at && cll(0) == i.cll(0) && cll(1) == i.cll(1) && cll(2) == i.cll(2);
    }
    
  };


    // ------------------- iterator class --------------------
    // Iterator allows you run through all (or some) atoms of this cell
    // and of surrounding cells
        
    class iterator : public index<DIM>{

      index<DIM> a, b;
      // a - from
      // b - to

      using index<DIM>::at;
      using index<DIM>::cll;

    public:

      iterator(const geometry<ATOM,DIM,VALTYPE> &g)
      // default iterator goes through neighbouring cells only
      {
	a.setatom(0);
	for (int d=0; d < DIM; d++)
	  a.setcell(d,-1);
	b.setatom(g.nat - 1);
	for (int d=0; d < DIM; d++)
	  b.setcell(d,1);	
      }

      iterator(index<DIM> _a, index<DIM> _b)
      {
	a = _a;
	b = _b;
      }

      inline index<DIM> begin(){return a;}

      //      inline index end(){return b;}

      inline index<DIM> end(){return index<DIM>(-1,0,0,0);}

      inline iterator& operator=(index<DIM> i)
      {
	at = i.atom();
	for (int d = 0; d<DIM; d++)
	  cll(d) = i.cell(d);
      }

      inline bool operator==(index<DIM> i)
      {
	bool res = (at == i.atom());
	if (res)
	  for (int d = 0; d<DIM; d++)
	    if ( cll(d) != i.cell(d) ) 
	      {
		res = false;
		break;
	      }
	return res;
      }

      inline bool operator!=(index<DIM> i)
      {
	if (DIM==0)
	  return at != i.atom();
	else if (DIM==1)
	  return at != i.atom() || cll(0) != i.cell(0);
	else if (DIM==2)
	  return at != i.atom() || cll(0) != i.cell(0) || cll(1) != i.cell(1);
	else if (DIM==3)
	  return at != i.atom() || cll(0) != i.cell(0) || cll(1) != i.cell(1) || cll(2) != i.cell(2);
      }
               
      iterator& operator++(int)      
      {
	if (*this == b)
	  {
	    *this = end();
	    return *this;
	  }

	at++;
	if (at > b.atom() && DIM>0)
	  {
	    at=a.atom();
	    int d=0;
	    while(d < DIM)
	      {
		cll(d)++;
		if (cll(d) > b.cell(d))
		  {
		    for(int dd=0; dd<=d; dd++)
		      cll(d) = a.cell(dd);
		    d++;
		  }
		else 
		  break;
	      }
	  }
	return *this;

      }  

    };

    // ---------------------------------------------------------
  public:

    geometry(){nat=0;}

    geometry(lace::vector3d<VALTYPE> v1, lace::vector3d<VALTYPE> v2=0e0, 
	     lace::vector3d<VALTYPE> v3=0e0)
    {
      if (DIM>0)
	cell(0)=v1;
      if (DIM>1)
	cell(1)=v2;
      if (DIM>2)
	cell(2)=v3;
      nat = 0;
    }

    void add(const ATOM & a, const lace::vector3d<VALTYPE> & r)
    {
      atm.push_back(a);
      crd.push_back(r);
      nat++;
    }

    void add(const ATOM & a, VALTYPE _x, VALTYPE _y, VALTYPE _z)
    {
      atm.push_back(a);
      crd.push_back(lace::vector3d<VALTYPE>(_x,_y,_z));
      nat++;
    }

    void del(int i)
    {
      atm.erase(i);
      crd.erase(i);
      nat--;
    }

    void insert(int i, const ATOM & a, const lace::vector3d<VALTYPE> & r)
    {
      atm.insert(i,a);
      crd.insert(i,r);
      nat++;
    }
    
    void insert(int i, const ATOM & a, VALTYPE _x, VALTYPE _y, VALTYPE _z)
    {
      atm.insert(i,a);
      crd.insert(i,lace::vector3d<VALTYPE>(_x,_y,_z));
      nat++;
    }

    inline int size(){return atm.size();}

    inline ATOM& atom(index<DIM> i){return atm[i.atom()];}

    // Position gives the position of i-th atom
    inline lace::vector3d<VALTYPE>& atom_coord(int i){return crd[i];}

    // Unlike position(i), coord(i) gives the coordinates of either
    // this atom in this unit cell or the coordinates of its image
    // in neighbouring cells
    // In other words
    // coord(i) = cell_coord(i) + atom_coord(i)
    inline lace::vector3d<VALTYPE> coord(index<DIM> i)
    {
      if (DIM==0)
	return crd[i.atom()];
      if (DIM==1)
	return crd[i.atom()] + cell(0)*i.cell(0);
      if (DIM==2)
	return crd[i.atom()] + cell(0)*i.cell(0) 
	  + cell(1)*i.cell(1);
      if (DIM==3)
	return crd[i.atom()] + cell(0)*i.cell(0) 
	  + cell(1)*i.cell(1) + cell(2)*i.cell(2);
    }    

    inline lace::vector3d<VALTYPE> cell_coord(int i1=0, int i2=0, int i3=0)
    {
      lace::vector3d<VALTYPE> r=0e0;
      if (DIM>0)
	r += i1*cell(0);
      if (DIM>1)
	r += i2*cell(1);
      if (DIM>2)
	r += i3*cell(2);
      return r;
    } 

    void scale(VALTYPE s)
    {
      for (int i=0; i<DIM; i++)
	cell(i) *= s;
      for (int i=0; i<nat; i++)
	crd[i] *= s;
    }

    void clear()
    {
      crd.clear();
      atm.clear();
      nat = 0;
    }

    // Atomic type table
    // fixme - think about forming type table when atoms are added
  private:
    std::vector<ATOM> atm_types;
    std::vector<int> type_table;

  public:

    inline int natm_types(){return atm_types.size();}
    
    inline ATOM& atom_of_type(int t){return atm_types[t];}

    inline int type_of_atom(ATOM at)
    {
      int t;
      for (t=0; t < atm_types.size(); t++)
	if ( atm_types[t] == at )
	  break;
      if (t == atm_types.size())
	return -1;
      else 
	return t;
    }

    inline int atm_type_table(int i){return type_table[i];}

    virtual void build_type_table()
    {
      atm_types.clear();
      type_table.resize(size());

      for (int i=0; i<size(); i++)
	{
	  int t = type_of_atom(atm[i]);
	  if (t == -1)
	    {
	      t = atm_types.size();
	      atm_types.push_back(atm[i]);
	    }
	  type_table[i] = t;
	}

    }

  };


};

#endif
