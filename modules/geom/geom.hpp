#ifndef _QPP_GEOM_H
#define _QPP_GEOM_H

#include <vector>
#include <cmath>
#include <lace/lace3d.hpp>
//#include <lace/lace.hpp>
//#include <symm/symm.hpp>
#include <io/qppdata.hpp>
#include <constants.hpp>

namespace qpp{

  // ------------------- index class ----------------------
  // Index is a handy tool to reference atoms in this geometry
  // as well as atoms in neighbouring cells
  // For that purpose it is a complex index - it contains, besides
  // the number of atom it is currently pointning at, also the 
  // indicies of the cell.
  template <int DIM>
  class index{
  protected:
    int at;
    int cll[DIM];    
    
  public:
    inline index& operator=(int _at)
    {
      at=_at;
      for (int d=0; d<DIM; d++)
	cll[d] = 0;
      return *this;
    }
    
    inline operator int() const {return at;}
    
    inline int atom() const {return at;}

    inline int & atom() {return at;}
    
    inline int cell(int d) const {return cll[d];}

    inline int & cell(int d) {return cll[d];}
    
    inline void set(int _at, int i1=0, int i2=0, int i3=0, int i4=0, int i5=0)
    {
      at=_at;
      if (DIM>0)
	cll[0]=i1;
      if (DIM>1)
	cll[1]=i2;
      if (DIM>2)
	cll[2]=i3;
      if (DIM>3)
	cll[3]=i4;
      if (DIM>4)
	cll[4]=i5;
    }
    
    inline void setatom(int _at){at=_at;}
    
    inline void setcell(int d, int i){cll[d]=i;}
    
    index()
    { set(0); }
    
    index(int _at, int i1=0, int i2=0, int i3=0, int i4=0, int i5=0)
    { set(_at,i1,i2,i3,i4,i5); }      

    index(const index<DIM> & I)
    {
      at = I.at;
      for (int d =0; d<DIM; d++)
	cll[d] = I.cll[d];
    }
    
    inline bool operator==(const index<DIM> & I) const
    {
      bool res = (at == I.at);
      for (int d=0; d<DIM; d++)
	res = res && (cll[d] == I.cll[d]);
      return res;
    }

    inline bool operator!=(const index<DIM> &I) const
    {
      return ! ((*this)==I);
    }
    
  };

  template<int DIM>
  std::basic_ostream<CHAR,TRAITS>&
  operator<<(std::basic_ostream<CHAR,TRAITS>& __os, index<DIM> i)
  {
    std::basic_ostringstream<CHAR,TRAITS> __s;
    __s.flags(__os.flags());
    __s.imbue(__os.getloc());
    __s.precision(__os.precision());
    
    __s << i.atom();
    if (DIM>0)
      {
	__s << "("  << i.cell(0);
	for (int d=1; d<DIM; d++)
	  __s << "," << i.cell(d);
	__s << ")";
      }
    return __os << __s.str();
  }

  /* -----------------------------------------------------------
        The class TRANSFORM is not being defined, though it will be
      used as a template parameter.
      Any class having transform method can be substituted for TRANSFORM

      template <int DIM, class VALTYPE, ...>
      class A {

      public:
        lace::vector3d<VALTYPE> transform(const lace::vector3d<VALTYPE> &r, index<DIM> i) const;
      };
  */
  //--------------------------------------------------------------//

  // The struct to store 1, 2 or 3 translation vectors
  template<int DIM,class VALTYPE=double>
  struct periodic_cell :  public qpp_object{
    lace::vector3d<VALTYPE> v[DIM];

    STRING _name;

    periodic_cell(const STRING &__name = "")
    {
      _name = __name;
    }

    periodic_cell(VALTYPE a, VALTYPE b, VALTYPE c,
		  VALTYPE alpha, VALTYPE beta, VALTYPE gamma, STRING __name = "")
    // for DIM==3
    {
      v[0] = lace::vector3d<VALTYPE>(a,VALTYPE(0),VALTYPE(0));
      v[1] = lace::vector3d<VALTYPE>(b*std::cos(gamma), b*std::sin(gamma),
				     VALTYPE(0));
      VALTYPE nx = std::cos(beta);
      VALTYPE ny = (std::cos(alpha) - nx*std::cos(gamma))/std::sin(gamma);
      VALTYPE nz = std::sqrt(1-nx*nx-ny*ny);
      v[2] = lace::vector3d<VALTYPE>(nx,ny,nz)*c;

      _name = __name;
    }

    periodic_cell(lace::vector3d<VALTYPE > a, lace::vector3d<VALTYPE > b=0, lace::vector3d<VALTYPE > c=0)
    {
      _name = "";
      if (DIM>0)
	v[0] = a;
      if (DIM>1)
	v[1] = b;
      if (DIM>2)
	v[2] = c;
    }

    lace::vector3d<VALTYPE> transform(const lace::vector3d<VALTYPE> &r, index<DIM> i) const
    {
      if (DIM==0)
	return r;
      if (DIM==1)
	return r + v[0]*i.cell(0);
      if (DIM==2)
	return r + v[0]*i.cell(0)  + v[1]*i.cell(1);
      if (DIM==3)
	return r + v[0]*i.cell(0)  + v[1]*i.cell(1) + v[2]*i.cell(2);

    }


    inline lace::vector3d<VALTYPE> & operator()(int i)
    // fixme - not obvious convention
    { return v[i]; } 

    inline lace::vector3d<VALTYPE> operator()(int i) const
    { return v[i]; } 

    inline VALTYPE & operator()(int i, int j)
    { return v[i](j); }
    
    inline VALTYPE operator()(int i, int j) const
    { return v[i](j); }
    
    inline lace::vector3d<VALTYPE> frac2cart(lace::vector3d<VALTYPE> frac) const
    // transforms fractional coordinates to cartesian
    // Works for any DIM, but the vector frac still should be 3d
    // if DIM<3, frac(i) components with i>=DIM are not used
    { 
      lace::vector3d<VALTYPE> res=VALTYPE(0);
      for (int i=0; i<DIM; i++)
    	res+=frac(i)*v[i];
      return res;
    }
    
    //   inline lace::vector3d<VALTYPE> frac2cart(simple_vector<VALTYPE,DIM> frac)
    // fractional to cartesian coordinates
    // works for DIM=1,2,3
    // here we use simple_vector to pass fractional coords
    //{
    //  lace::vector3d<VALTYPE> res=VALTYPE(0);
    //  for (int i=0; i<DIM; i++)
    //	res+=frac(i)*v[i];
    // return res;
    //}

    inline lace::vector3d<VALTYPE> cart2frac(lace::vector3d<VALTYPE> r) const
    // cartesian to fractional
    // works for DIM==3 only
    { 
      lace::matrix3d<VALTYPE> A(v[0],v[1],v[2]);
      return lace::solve3d(A, r);
    }

    inline lace::vector3d<VALTYPE> reduce(lace::vector3d<VALTYPE> r)  const
    // Brings the point r into the volume of unit cell
    // by translations
    // unit cell is defined as parallelepiped with one vertex in
    // the coordinate origin
    // the others are pointed by v[0],v[1],v[2] vectors
    {
      lace::vector3d<VALTYPE> f = cart2frac(r);
      f(0) -= floor(f(0));
      f(1) -= floor(f(1));
      f(2) -= floor(f(2));
      return frac2cart(f);
    }

    inline lace::vector3d<VALTYPE> reduce_cntr(lace::vector3d<VALTYPE> r) const
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

    inline lace::vector3d<VALTYPE> reduce_wz(lace::vector3d<VALTYPE> r) const
    // Brings r into Wigner-Zeitz unit cell
    // fixme - implement this!
    {}

    inline bool in_cell(lace::vector3d<VALTYPE> r) const
    // Answers the question whether r belongs to the unit cell
    {
      lace::vector3d<VALTYPE> f = cart2frac(r);
      return 
        VALTYPE(0)<=f(0) && f(0) < VALTYPE(1) &&
        VALTYPE(0)<=f(1) && f(1) < VALTYPE(1) &&
        VALTYPE(0)<=f(2) && f(2) < VALTYPE(1);  
    }


    inline bool in_cell_cntr(lace::vector3d<VALTYPE> r) const
    // does r belong to unit cell centred at the coords origin?
    {
      lace::vector3d<VALTYPE> f = cart2frac(r);
      return 
        -VALTYPE(1)/2 <= f(0) && f(0) < VALTYPE(1)/2 &&
        -VALTYPE(1)/2 <= f(1) && f(1) < VALTYPE(1)/2 &&
        -VALTYPE(1)/2 <= f(2) && f(2) < VALTYPE(1)/2;   
    }

    inline bool in_cell_wz(lace::vector3d<VALTYPE> r) const
    // does r belong to Wigner-Zeitz unit cell
    // fixme - implement this!
    {}

    virtual STRING category() const
    {
      return "vectors";
    }

    virtual STRING name() const
    {
      return _name;
    }

    virtual qppobject_type gettype() const
    {
      int d;
      if (DIM==0)
	d = data_dim0;
      else if (DIM==1)
	d = data_dim1;
      else if (DIM==2)
	d = data_dim2;
      else if (DIM==3)
	d = data_dim3;
      return data_vectors | d;
    }

    virtual void error(STRING const &){}

    virtual STRING error(){return "";}

    virtual int n_next() const
    { return 0; }

    virtual qpp_object* next(int i)
    { return NULL; }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "vectors";
      if (_name != "")
	os << " " << _name;
      os << "(" << DIM << "d){\n";

      for (int i=0; i<DIM; i++)
	{
	  for (int k=0; k<offset+2; k++) os << " ";
	  os << boost::format(" %11.6f %11.6f %11.6f\n") % v[i](0) % v[i](1) % v[i](2);	  
	}

      for (int k=0; k<offset; k++) os << " ";
      os << "}\n";
    }

  };

  //--------------------------------------------------------------//

  // The geometry class stores atoms together with their
  // coordinates. As ATOM is a template parameter, you can
  // use almost everything as POINT, even emply class.
  //
  // In this latter case you get just points with coordinates
  // Such object can be used to store, say, displacement 
  // vectors or vibrational mode vectors.
  //
  // If ATOM is something more substatial, you can store any information
  // about atoms as well

  // geometry is an ancestor for molecule
  template< int DIM, class VALTYPE=double, class TRANSFORM = periodic_cell<DIM,VALTYPE> >
  class gen_geometry : public qpp_object{

  protected:

    //int nat;
    // Number of atoms/points

    std::vector<STRING> atm;
    // Storage of atoms

    std::vector<lace::vector3d<VALTYPE> > crd;
    // Their coordinates

    std::vector<char> _shadow;

    STRING _name, _error;

    TRANSFORM * trnf;

  public:
    //    periodic_cell<DIM,VALTYPE,charT,traits> cell;
    //    bool update_types, update_neighbours;
    bool update_types;

    VALTYPE geomtol;

    TRANSFORM & symm(){return *trnf;}
    
    // Unit cell vectors for 1,2,3d periodicity
    
    // ------------------- iterator class --------------------
    // Iterator allows you run through all (or some) atoms of this cell
    // and of surrounding cells
    
    class iterator : public index<DIM>{
      
      index<DIM> a, b;
      // a - from
      // b - to
      
      gen_geometry<DIM, VALTYPE, TRANSFORM> * geom;

      using index<DIM>::at;
      using index<DIM>::cll;

      void inc()
      {
	if (*this == b)
	  *this = end();

	if ( *this == end())
	  return;

	at++;
	if (at > b.atom() && DIM>0)
	  {
	    at=a.atom();
	    int d=0;
	    while(d < DIM)
	      {
		cll[d]++;
		if (cll[d] > b.cell(d))
		  {
		    for(int dd=0; dd<=d; dd++)
		      cll[d] = a.cell(dd);
		    d++;
		  }
		else 
		  break;
	      }
	  }
	
      }  
      
    public:
      
      iterator(gen_geometry<DIM, VALTYPE, TRANSFORM> &g)
      // default iterator goes through neighbouring cells only
      {
	a.setatom(0);
	for (int d=0; d < DIM; d++)
	  a.setcell(d,-1);
	b.setatom(g.nat() - 1);
	for (int d=0; d < DIM; d++)
	  b.setcell(d,1);
	geom = &g;
      }
      
      iterator(index<DIM> _a, index<DIM> _b)
      {
	a = _a;
	b = _b;
	geom = NULL;
      }

      iterator(index<DIM> _a, index<DIM> _b, gen_geometry<DIM, VALTYPE, TRANSFORM> &g)
      {
	a = _a;
	b = _b;
	geom = &g;
      }     

      inline index<DIM> begin()
      {
	iterator tmp(a,b,*geom);
	tmp = a;
	while ( geom != NULL && tmp != end() ? geom -> shadow(tmp) : false)
	  tmp.inc();
	return tmp;
      }
      
      //      inline index end(){return b;}

      inline index<DIM> end(){return index<DIM>(-1,0,0,0);}

      inline iterator& operator=(index<DIM> i)
      {
	at = i.atom();
	for (int d = 0; d<DIM; d++)
	  cll[d] = i.cell(d);
      }

      inline bool operator==(index<DIM> i)
      {
	bool res = (at == i.atom());
	if (res)
	  for (int d = 0; d<DIM; d++)
	    if ( cll[d] != i.cell(d) ) 
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
	  return at != i.atom() || cll[0] != i.cell(0);
	else if (DIM==2)
	  return at != i.atom() || cll[0] != i.cell(0) || cll[1] != i.cell(1);
	else if (DIM==3)
	  return at != i.atom() || cll[0] != i.cell(0) || cll[1] != i.cell(1) || cll[2] != i.cell(2);
      }
               
      iterator& operator++(int)
      {
	do
	  { inc();}
	while ( geom != NULL && *this != end() ? geom -> shadow(*this) : false);
      }

    };

    // ---------------------------------------------------------
  public:

    virtual int n_next() const
    {
      return DIM==0? 0 : 1;
    }

    virtual qpp_object* next(int i)
    {
      if (DIM>0 && i==1)
	return trnf;
      else
	return NULL;
    }

    virtual STRING category() const
    {
      return "geometry";
    }

    virtual STRING name() const
    {
      return _name;
    }

    void setname(STRING __name)
    {
      _name = __name;
    }

    virtual qppobject_type gettype() const
    {
      int d;
      if (DIM==0)
	d = data_dim0;
      else if (DIM==1)
	d = data_dim1;
      else if (DIM==2)
	d = data_dim2;
      else if (DIM==3)
	d = data_dim3;
      return data_geometry | d;
    }

    inline int size() const
    {return crd.size();}

    inline int nat() const
    {return crd.size();}

    inline STRING & atom(index<DIM> i)
    {return atm[i.atom()];}

    inline STRING atom(index<DIM> i) const
    {return atm[i.atom()];}

    // coord gives the coordinates of i-th atom in the cell
    inline lace::vector3d<VALTYPE> coord(int i) const{return crd[i];}

    inline lace::vector3d<VALTYPE>& coord(int i){return crd[i];}

    // Unlike coord(i), position(i) gives the coordinates of either
    // this atom in this unit cell or the coordinates of its image
    // in neighbouring cells
    // In other words
    // coord(i) = cell_coord(i) + atom_coord(i)
    inline lace::vector3d<VALTYPE> position(index<DIM> i)
    {
      return trnf -> transform(crd[i.atom()],i);
    }    

    virtual void error(STRING const & what)
    { 
      _error = what;
      throw qpp_exception(this);
    }

    virtual STRING error()
    {
      return _error;
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "geometry";
      if (_name != "")
	os << " " << _name;
      os << "(" << DIM << "d){\n";
      
      for (int i=0; i<size(); i++)
	{
	  for (int k=0; k<offset+2; k++) os << " ";
	  os << atm[i] << boost::format(" %11.6f %11.6f %11.6f\n") % crd[i].x() % crd[i].y() %crd[i].z();
	  
	}

      for (int k=0; k<offset; k++) os << " ";
      os << "}\n";
    }

    //------------------- Type table operations -------------------------

  private:
    std::vector<STRING> _atm_types;
    std::vector<int> _type_table;

  public:

    class neighbours_table;
    neighbours_table ngbr;

    // Number of atomic types in molecule
    inline int n_atom_types() const
    {
      return _atm_types.size();
    }
    
    // Reference to atom of type number t (not the atom number t in atomic list!)
    inline STRING atom_of_type(int t) const
    {
      return _atm_types[t];
    }

    // Number of type of certain ATOM at
    inline int type_of_atom(const STRING & at) const
    {
      int t;
      for (t=0; t < _atm_types.size(); t++)
	if ( _atm_types[t] == at )
	  break;
      if (t == _atm_types.size())
	return -1;
      else 
	return t;
    }
    
    // 
    inline int type_table(int i) const
    {return _type_table[i];}


    virtual void build_type_table()
    {
      _atm_types.clear();
      _type_table.resize(size());
      
      for (int i=0; i<size(); i++)
	{
	  int t = type_of_atom(atom(i));
	  if (t == -1)
	    {
	      t = _atm_types.size();
	      _atm_types.push_back(atom(i));
	    }
	  _type_table[i] = t;
	}
      ngbr.resize_disttable();
    }
    
    void clear_type_table()
    {
      _atm_types.clear();
      _type_table.resize(size());  
    }

    // ------------------- Neighbours table -----------------------
    class neighbours_table{
      std::vector<std::vector<index<DIM> > > _table;
      
      struct _ngbr_record{ 
	STRING at1, at2; 
	VALTYPE d;
	
	_ngbr_record(STRING _at1, STRING _at2, VALTYPE _d)
	{
	  at1 = _at1;
	  at2 = _at2;
	  d = _d;
	}
      };
      
      std::vector<_ngbr_record> _records;
      VALTYPE *_disttable;
      
      lace::vector3d<VALTYPE> Rmin, Rmax;
      VALTYPE grainsize;
      int grain_nx, grain_ny, grain_nz;
      std::vector<std::vector<index<DIM> > > _grains; 
      
      gen_geometry<DIM, VALTYPE, TRANSFORM> * geom;
      
      inline int _record_match(STRING at1, STRING at2, int i)
      {
	return ( at1 == _records[i].at1 && at2 == _records[i].at2 ) ||
	  ( at2 == _records[i].at1 && at1 == _records[i].at2 );
      }
      
      void _grain_setup()
      {
	// find largest neighbourung distance
	grainsize = VALTYPE(0);
	int ntp = geom->n_atom_types();
	for (int i=0; i<ntp*ntp; i++)
	  if (_disttable[i] > grainsize )
	    grainsize = _disttable[i];
	Rmin = Rmax = geom->position(0);
	for (int i=1; i<geom->size(); i++)
	  {
	    if ( Rmin.x() > geom->position(i).x() ) 
	      Rmin.x() = geom->position(i).x();
	    if ( Rmax.x() < geom->position(i).x() ) 
	      Rmax.x() = geom->position(i).x();
	    if ( Rmin.y() > geom->position(i).y() ) 
	      Rmin.y() = geom->position(i).y();
	    if ( Rmax.y() < geom->position(i).y() ) 
	      Rmax.y() = geom->position(i).y();
	    if ( Rmin.z() > geom->position(i).z() ) 
	      Rmin.z() = geom->position(i).z();
	    if ( Rmax.z() < geom->position(i).z() ) 
	      Rmax.z() = geom->position(i).z();
	  }
	grain_nx = int( (Rmax.x()-Rmin.x())/grainsize ) + 3;
	grain_ny = int( (Rmax.y()-Rmin.y())/grainsize ) + 3;
	grain_nz = int( (Rmax.z()-Rmin.z())/grainsize ) + 3;
	
	//debug
	//std::cout << "Grain setup:\n" << grain_nx<<"x"<<grain_ny<<"x"<<grain_nz<<"\n";
	//std::cout << "grain size= " << grainsize << " corners= " << Rmin << Rmax << "\n";
      }

      inline std::vector<index<DIM> > & grains(int i, int j, int k)
      {
	return _grains[i*grain_ny*grain_nz + j*grain_nz + k];
      }

      
      inline void to_grain(const index<DIM> & at)
      {
	lace::vector3d<VALTYPE> r = geom->position(at);
	int i = floor( (r.x()-Rmin.x())/grainsize ) + 1;
	int j = floor( (r.y()-Rmin.y())/grainsize ) + 1;
	int k = floor( (r.z()-Rmin.z())/grainsize ) + 1;
	
	if ( i>=0 && i<grain_nx && j>=0 && j<grain_ny && k>=0 && k<grain_nz)
	  {
	    //lace::vector3d<VALTYPE> r = geom->position(at);
	    bool found = false;
	    for (int l=0; l<grains(i,j,k).size(); l++)
	      if ( norm( r - geom->position(grains(i,j,k)[l])) < geom->geomtol &&
		   at.atom() == grains(i,j,k)[l].atom() )
		{
		  found = true;
		  break;
		}
	    
	    if (!found)
	      grains(i,j,k).push_back(at);
	  }
      }

      
      void _graining()
      {
	for (int i=0; i<_grains.size(); i++)
	  _grains[i].clear();
	_grains.clear();
	_grains.resize(grain_nx*grain_ny*grain_nz);

	for (int i=0; i<geom->nat(); i++)
	  if (! geom->shadow(i) )
	    to_grain(i);
	gen_geometry<DIM, VALTYPE, TRANSFORM>::iterator at(*geom);
	for ( at = at.begin(); at != at.end(); at++)
	  if ( at != index<DIM>(at,0,0,0) )
	    to_grain(at);

	//      debug
	/*
	  std::cout << "graining finished\n";
	  for (int i=0; i<grain_nx; i++)
	  for (int j=0; j<grain_ny; j++)
	  for (int k=0; k<grain_nz; k++)
	  {
	  std::cout << i << " " << j << " " << k;
	  for (int l=0; l<grains(i,j,k).size(); l++)
	  std::cout << " " << grains(i,j,k)[l];
	  std::cout << "\n";
	  }
	*/

      }

    public:

      VALTYPE default_distance;
      bool autoupdate;
      
      neighbours_table( gen_geometry<DIM, VALTYPE, TRANSFORM> & g)
      {
	_disttable = NULL;
	default_distance = VALTYPE(0);
	geom = & g;
      } 

      // Number of neighbours of i-th atom
      inline int n(int i)
      {
	return _table[i].size();
      }
      
      // j-th neighbour of i-th atom
      inline index<DIM> table(int i, int j) const
      {
	return _table[i][j];
      }

      inline index<DIM> operator()(index<DIM> i, int j) const
      {
	index<DIM> res = table(i,j);
	for (int a=0; a<DIM; a++)
	  res.setcell( a, res.cell(a)+i.cell(a) );
	return res;
      }

      VALTYPE distance(STRING at1, STRING at2)
      {
	bool found = false;
	int i;
	for (i=0; i<_records.size(); i++)
	  if (_record_match(at1,at2,i))
	    {
	      found = true;
	      break;
	    }
	return found? _records[i].d : default_distance;
      }

      void set_distance(STRING at1, STRING at2, VALTYPE d)
      {
	bool found = false;
	int i;
	for (i=0; i<_records.size(); i++)
	  if (_record_match(at1,at2,i))
	    {
	      found = true;
	      break;
	    }
	if (found)
	  _records[i].d = d;
	else
	  _records.push_back(_ngbr_record(at1,at2,d));
      }

      void clear_distance()
      {
	_records.clear();
      }
      
      inline void resize_disttable()
      {
	if (_disttable!=NULL)
	  delete _disttable;
	int N = geom->n_atom_types();
	_disttable = new VALTYPE[N*N];
      }
      
      VALTYPE distance(int i, int j)
      {
	if (_disttable!=NULL)
	  return _disttable[i*geom->n_atom_types()+j];
	else
	  return default_distance;
      }

      inline void build_disttable()
      {
	int n = geom->n_atom_types();
	for (int i=0; i<n; i++)
	  for (int j=0; j<=i; j++)
	    _disttable[n*i+j] = _disttable[n*j+i] = 
	      distance(geom->atom_of_type(i),geom->atom_of_type(j));
      }
    
      /*  
      void build()
      {
	_grain_setup();
	_graining();
	for (int i=0; i<_table.size(); i++)
	  _table[i].clear();
	
	_table.resize(geom->size());
	
	for (int i = 1; i < grain_nx; i++)
	  for (int j = 1; j < grain_ny; j++)
	    for (int k = 1; k < grain_nz; k++)
	      {
		int g1 = i*grain_ny*grain_nz + j*grain_nz + k;
		if (_grains[g1].size()>0)
		  for (int di=-1; di<=0; di++)
		    for (int dj=-1; dj<=-di; dj++) 
		      for (int dk=-1; dk<=-di || dk<=-dj; dk++)
			{
			  int g2 = (i+di)*grain_ny*grain_nz + (j+dj)*grain_nz + k+dk;
			  for (int c2 = 0; c2 < _grains[g2].size(); c2++)
			    for (int c1 = 0; c1 < ( g1==g2? c2 : _grains[g1].size()); c1++)
			      {
				index<DIM> at1 = _grains[g1][c1];
				index<DIM> at2 = _grains[g2][c2];
				VALTYPE r = norm(geom->position(at1) - geom->position(at2));
				
				//debug
				std::cout << at1 << " " << at2 << " " << r << "\n";

				if ( r <= distance(geom->type_table(at1), geom->type_table(at2)))
				  {
				    if ( at1 == index<DIM>(at1.atom()) )
				      {
					_table[at1].push_back(at2);

					//std::cout << at2 << " " << index<DIM>(at2.atom()) << 
					// " " << (at2 != index<DIM>(at2.atom())) << "\n";

					if ( at2 != index<DIM>(at2.atom()) )
					  {
					    //std::cout << "hoho\n";
					    for (int dd=0; dd<DIM; dd++)
					      at1.cell(dd)=-at2.cell(dd);
					    _table[at2].push_back(at1);	
					  }

				      }
				    if ( at2 == index<DIM>(at2.atom()) )
				      {
					_table[at2].push_back(at1);	
					/*
					if ( at1 != index<DIM>(at1.atom()) )
					  {
					    for (int dd=0; dd<DIM; dd++)
					      at2.setcell(dd,-at1.cell(dd));
					    _table[at1].push_back(at2);	
					  }

				      }
				  } //for (int c1 = 0; c1 < ( g1==g2? c2 : _grains[g1].size()); c1++)
				
			      }
			}
	      }
      }
      */
      void build()
      {
	_grain_setup();
	_graining();
	for (int i=0; i<_table.size(); i++)
	  _table[i].clear();
	
	_table.resize(geom->size());
	
	for (int i = 0; i < grain_nx; i++)
	  for (int j = 0; j < grain_ny; j++)
	    for (int k = 0; k < grain_nz; k++)
	      {
		int g1 = i*grain_ny*grain_nz + j*grain_nz + k;
		if (_grains[g1].size()>0)
		  for (int di=-1; di<=1; di++)
		    for (int dj=-1; dj<=1; dj++) 
		      for (int dk=-1; dk<=1; dk++)
			if ( 0 <= i+di && i+di < grain_nx &&  0 <= j+dj && j+dj < grain_ny  &&  
			     0 <= k+dk && k+dk < grain_nz)
			  {
			    int g2 = (i+di)*grain_ny*grain_nz + (j+dj)*grain_nz + k+dk;
			    for (int c1 = 0; c1 < _grains[g1].size(); c1++)
			      {
				index<DIM> at1 = _grains[g1][c1];
				if (at1 != index<DIM>(at1.atom()))
				  break;
				
				for (int c2 = 0; c2 < _grains[g2].size(); c2++)
				  {
				    index<DIM> at2 = _grains[g2][c2]; 
				    VALTYPE r = norm(geom->position(at1) - geom->position(at2));

				    if ( at1.atom() == at2.atom() && r < geom->geomtol)
				      continue;
				
				    if ( at1 != at2 && r <= distance(geom->type_table(at1), geom->type_table(at2)))
				      _table[at1].push_back(at2);
				
				  } 
				
			      }
			  }
	      }	
      }
      
    };

    // --------------- Constructors & destructors --------------------

    gen_geometry(TRANSFORM & _trnf, const STRING & __name = "") : ngbr(*this)
    {
      _name = __name;
      trnf = & _trnf;
      update_types = false;
      geomtol = default_geomtol;
      //update_neighbours = false;
    }

    ~gen_geometry()
    {
      //if (_ngbr_disttable!=NULL)
      //delete _ngbr_disttable;
    }

    void copy(const gen_geometry<DIM, VALTYPE, TRANSFORM> &G)
    {
      clear();
      atm = G.atm;
      crd = G.crd;
      _shadow = G._shadow;
      geomtol = G.geomtol;
    }

    // ----------------------- Manipulations with atoms -----------------------

    virtual void add(STRING a, const lace::vector3d<VALTYPE> & r)
    {
      atm.push_back(a);
      crd.push_back(r);
      _shadow.push_back((char)false);
      if (update_types)
	{
	  int t = type_of_atom(a);
	  if (t == -1)
	    {
	      t = _atm_types.size();
	      _atm_types.push_back(a);
	      /*if (update_neighbours)
		{
		  ngbr.resize_disttable();
		  ngbr.build_disttable();
		}	      
	      */
	    }
	  _type_table.push_back(t);
	}
    }

    virtual void add(STRING a, const VALTYPE _x, const VALTYPE _y, const VALTYPE _z)
    {
      add(a,lace::vector3d<VALTYPE>(_x,_y,_z));
    }

    virtual void erase(const int i)
    {
      atm.erase(atm.begin()+i);
      crd.erase(crd.begin()+i);
      _shadow.erase(_shadow.begin()+i);
      if (update_types)
	_type_table.erase(_type_table.begin()+i);
    }

    virtual void insert(int i, STRING a, const lace::vector3d<VALTYPE> &r)
    {
      atm.insert(atm.begin()+i,a);
      crd.insert(crd.begin()+i,r);
      _shadow.insert(_shadow.begin()+i,(char)false);
      if (update_types)
	{
	  int t = type_of_atom(a);
	  if (t == -1)
	    {
	      t = _atm_types.size();
	      _atm_types.push_back(a);
	      /*if (update_neighbours)
		{
		  ngbr.resize_disttable();
		  ngbr.build_disttable();
		}
	      */
	    }
	  _type_table.insert(_type_table.begin()+i,t);
	}
    }
    
    virtual void insert(int i, STRING a, const VALTYPE _x, const VALTYPE _y, const VALTYPE _z)
    {
      insert(i,a,lace::vector3d<VALTYPE>(_x,_y,_z));
    }

    void clear()
    {
      crd.clear();
      atm.clear();
      _shadow.clear();
      clear_type_table();
    }

    inline bool & shadow(int i)
    {
      return *((bool*)&_shadow[i]);
    }

  };

  template< int DIM, class VALTYPE=double >
  class geometry : public gen_geometry<DIM,VALTYPE,periodic_cell<DIM,VALTYPE> >{

  protected:
    using gen_geometry<DIM,VALTYPE,periodic_cell<DIM,VALTYPE> >::trnf;
    using gen_geometry<DIM,VALTYPE,periodic_cell<DIM,VALTYPE> >::crd;

  public:
    using gen_geometry<DIM,VALTYPE,periodic_cell<DIM,VALTYPE> >::nat;

    periodic_cell<DIM,VALTYPE> cell;
    
    geometry(const STRING & __name = "") : cell(),
	     gen_geometry<DIM,VALTYPE,periodic_cell<DIM,VALTYPE> >(cell, __name)
    {}

    geometry(lace::vector3d<VALTYPE> v1, lace::vector3d<VALTYPE> v2=0e0, 
	     lace::vector3d<VALTYPE> v3=0e0, const STRING &__name = "") : cell(v1,v2,v3),
	     gen_geometry<DIM,VALTYPE,periodic_cell<DIM,VALTYPE> >(cell, __name)
    {}

    inline lace::vector3d<VALTYPE> cell_coord(int i1=0, int i2=0, int i3=0) const
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
      for (int i=0; i<nat(); i++)
	crd[i] *= s;
    }

  };


};

#endif
