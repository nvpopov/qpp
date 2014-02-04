#ifndef _QPP_GEOM_EXTRAS_H
#define _QPP_GEOM_EXTRAS_H

#include <geom/geom.h>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <initializer_list>
#endif

namespace qpp{

  // -----------------------------------------------------
  
  // Molecule vector is the 3N - dimensional vector, i.e.
  // the object which ascribes usual 3d vector to every atom
  // of some molecule.
  // These can be the displacements of atoms or normal mode vector,
  // or something else.

  template<class ATOM, int DIM, class VALTYPE>
  class molecule_vector
  {
    geometry<ATOM,DIM,VALTYPE> *owner;

  public:
    std::vector<lace::vector3d<VALTYPE> > coord;

    //    friend 
    // molecule_vector<POINT,DIM,VALTYPE> operator*(VALTYPE s, const molecule_vector<POINT,DIM,VALTYPE> &v);

  public:

    molecule_vector(){owner=NULL;}

    molecule_vector(geometry<ATOM,DIM,VALTYPE> *_owner)
    {
      setgeom(_owner);      
    }

    molecule_vector(const molecule_vector<ATOM,DIM,VALTYPE> & v)
    {
      setgeom(v.owner);
      if (owner != NULL)
	for (int i=0; i<size(); i++)
	  coord[i] = v.coord[i];
    }

    inline geometry<ATOM,DIM,VALTYPE> *geom() const
    {
      return owner;
    }

    void setgeom(geometry<ATOM,DIM,VALTYPE> *_owner)
    {
      owner = _owner;
      if (owner!=NULL)
	{
	  coord.resize(owner -> size());
	  for (int i=0; i < coord.size(); i++)
	    coord[i] = VALTYPE(0);
	}
    }

    inline int size() const
    {
      return coord.size();
    }

    inline VALTYPE & operator()(int i, int j)
    {
      return coord[i](j);
    }

    inline lace::vector3d<VALTYPE> & operator()(int i)
    {
      return coord[i];
    }

    inline VALTYPE & operator[](int i)
    {
      return coord[i/3](i%3);
    }

    molecule_vector<ATOM,DIM,VALTYPE>  operator+(const molecule_vector<ATOM,DIM,VALTYPE> &v)
    {
      assert(size() == v.size());
      molecule_vector<ATOM,DIM,VALTYPE> res(owner);
      for (int i=0; i < coord.size(); i++)
	res.coord[i] = coord[i] + v.coord[i];
      return res;
    }

    molecule_vector<ATOM,DIM,VALTYPE>  operator-(const molecule_vector<ATOM,DIM,VALTYPE> &v)
    {
      assert(size() == v.size());
      molecule_vector<ATOM,DIM,VALTYPE> res(owner);
      for (int i=0; i < coord.size(); i++)
	res.coord[i] = coord[i] - v.coord[i];
      return res;
    }

    molecule_vector<ATOM,DIM,VALTYPE>  operator*(VALTYPE s)
    {
      molecule_vector<ATOM,DIM,VALTYPE> res(owner);
      for (int i=0; i < coord.size(); i++)
	res.coord[i] = s*coord[i];
      return res;
    }

    molecule_vector<ATOM,DIM,VALTYPE>  operator/(VALTYPE s)
    {
      molecule_vector<ATOM,DIM,VALTYPE> res(owner);
      for (int i=0; i < coord.size(); i++)
	res.coord[i] = coord[i]/s;
      return res;
    }

    VALTYPE norm()
    {
      VALTYPE s = VALTYPE(0);
      for (int i=0; i < coord.size(); i++)
	s += lace::scal(coord[i],coord[i]);
      return std::sqrt(s);
    }

  };

  template<class ATOM, int DIM, class VALTYPE>
  molecule_vector<ATOM,DIM,VALTYPE> operator*(VALTYPE s, const molecule_vector<ATOM,DIM,VALTYPE> &v)
  {
    molecule_vector<ATOM,DIM,VALTYPE> res(v.geom());
    for (int i=0; i < v.coord.size(); i++)
      res.coord[i] = s*v.coord[i];
    return res;
  }

  template<class ATOM, int DIM, class VALTYPE>
  typename lace::numeric_type<VALTYPE>::real scal(molecule_vector<ATOM,DIM,VALTYPE> &v1, 
						  molecule_vector<ATOM,DIM,VALTYPE> &v2)
  {
    typename lace::numeric_type<VALTYPE>::real s;
    for (int i=0; i<v1.size()*3; i++)
      s += lace::conj(v1[i])*v2[i];
    return s;
  }

  template<class ATOM, int DIM, class VALTYPE, class TRANSFORM>
  molecule_vector<ATOM,DIM,VALTYPE> operator*(TRANSFORM T, molecule_vector<ATOM,DIM,VALTYPE> &v)
  {
    lace::matrix3d<VALTYPE> R(T);
    molecule_vector<ATOM,DIM,VALTYPE> res(v.geom());
    for (int i=0; i < v.size(); i++)
      {
	lace::vector3d<VALTYPE> rnew = T * v.geom()->atom_coord(i);
	int j;
	bool found = false;
	for (j=0; j<v.size(); j++)
	  if ( lace::norm(rnew - v.geom()->atom_coord(j) ) <= symmtol )
	    {
	      found = true; break;
	    }
	// fixme - think about this behavoir for non-symmetric mols
	if (!found) j = i;
	res(j) = R*v(i);
      }
    
    return res;
  }


  // ---------------- Geometry with extra fields - for storing any additional data -------------------

  template<class ATOM, int DIM, class VALTYPE, class charT = char, class traits = std::char_traits<charT> >
  class xtr_geometry : public geometry<ATOM,DIM,VALTYPE,charT,traits>{
  
    std::vector<VALTYPE> chrg;

    std::vector<std::vector<VALTYPE> >  _xtr_real;
    std::vector<std::vector<int> >      _xtr_int;
    std::vector<std::vector<short> >    _xtr_bool;

    int nxreal, nxint, nxbool;
    bool xchrg;

    using geometry<ATOM,DIM,VALTYPE,charT,traits>::atm;
    using geometry<ATOM,DIM,VALTYPE,charT,traits>::crd;
    using geometry<ATOM,DIM,VALTYPE,charT,traits>::size;
    using geometry<ATOM,DIM,VALTYPE,charT,traits>::_name;
    using typename geometry<ATOM,DIM,VALTYPE,charT,traits>::string;

  public:

    xtr_geometry(bool charge = true, int n_xtr_real=0, int n_xtr_int=0, int n_xtr_bool=0, string __name = "") :
      _xtr_real(n_xtr_real), _xtr_int(n_xtr_int), _xtr_bool(n_xtr_bool), geometry<ATOM,DIM,VALTYPE,charT,traits>(__name)
    {
      xchrg = charge;
      nxreal = n_xtr_real;
      nxint = n_xtr_int;
      nxbool = n_xtr_bool;
    }

    virtual int gettype()
    {
      return geometry<ATOM,DIM,VALTYPE,charT,traits>::gettype() | qppdata_xgeom;
    }

    /*    ~xtr_geometry()
    {
      std::cout << "destructor\n";
      std::cout << "  real\n";
      if (nxint>0)
	delete _xtr_int;
      std::cout << "  int\n";
      if (nxbool>0)
	delete _xtr_bool;
      std::cout << "  bool\n";
      }*/

    VALTYPE & xtr_real(int i, int j)
    {
      return _xtr_real[j][i];
    }

    int & xtr_int(int i, int j)
    {
      return _xtr_int[j][i];
    }

    bool & xtr_bool(int i, int j)
    {
      return * ((bool*) & _xtr_bool[j][i]);
    }

    VALTYPE & charge(int i)
    {
      return chrg[i];
    }

    virtual void add_point(ATOM a, const lace::vector3d<VALTYPE> & r)
    {
      geometry<ATOM,DIM,VALTYPE,charT,traits>::add_point(a,r);

      if (xchrg)
	chrg.push_back( VALTYPE(0) );   
      for (int i=0; i<nxreal; i++)
	_xtr_real[i].push_back( VALTYPE(0) );
      for (int i=0; i<nxint; i++)
	_xtr_int[i].push_back(0);
      for (int i=0; i<nxbool; i++)
	_xtr_bool[i].push_back( false );
    }

    virtual void add_point(ATOM a, VALTYPE _x, VALTYPE _y, VALTYPE _z)
    {
      add_point(a, lace::vector3d<VALTYPE>(_x,_y,_z));
    }

    virtual void del_point(const int j)
    {
      geometry<ATOM,DIM,VALTYPE,charT,traits>::del_point(j);
      for (int i=0; i<nxreal; i++)
	_xtr_real[i].erase(_xtr_real[i].begin()+j);
      for (int i=0; i<nxint; i++)
	_xtr_int[i].erase(_xtr_int[i].begin()+j);
      for (int i=0; i<nxbool; i++)
	_xtr_bool[i].erase(_xtr_bool[i].begin()+j);
      if (xchrg)
	chrg.erase(chrg.begin()+j);  
    }

    virtual void insert_point(const int j, ATOM a, const lace::vector3d<VALTYPE> &r)
    {
      geometry<ATOM,DIM,VALTYPE,charT,traits>::insert_point(j,a,r);

      if (xchrg)
	chrg.insert(chrg.begin()+j, VALTYPE(0) );  
      for (int i=0; i<nxreal; i++)
	_xtr_real[i].insert(_xtr_real[i].begin()+j, VALTYPE(0) );
      for (int i=0; i<nxint; i++)
	_xtr_int[i].insert(_xtr_int[i].begin()+j, 0);
      for (int i=0; i<nxbool; i++)
	_xtr_bool[i].insert(_xtr_bool[i].begin()+j, false);
    }

    virtual void insert_point(const int j, ATOM a, const VALTYPE _x, const VALTYPE _y, const VALTYPE _z)
    {
      insert_point(j,a,lace::vector3d<VALTYPE>(_x,_y,_z));
    }

#ifdef __GXX_EXPERIMENTAL_CXX0X__

    void add_point(ATOM a, const lace::vector3d<VALTYPE> & r, VALTYPE q, std::initializer_list<VALTYPE> xtr = {}, 
		   std::initializer_list<int> xti = {}, std::initializer_list<bool> xtb = {})
    {
      geometry<ATOM,DIM,VALTYPE,charT,traits>::add_point(a,r);

      if (xchrg)
	chrg.push_back( q );

      typename std::initializer_list<VALTYPE>::iterator ir = xtr.begin();
      for (int i=0; i<nxreal; i++)
	{
	  _xtr_real[i].push_back( ir == xtr.end() ? VALTYPE(0) : *ir );
	  ir++;
	}

      typename std::initializer_list<int>::iterator ii = xti.begin();
      for (int i=0; i<nxint; i++)
	{
	  _xtr_int[i].push_back( ii == xti.end() ? 0 : *ii );
	  ii++;
	}

      typename std::initializer_list<bool>::iterator ib = xtb.begin();
      for (int i=0; i<nxbool; i++)
	{
	  _xtr_bool[i].push_back( ib == xtb.end() ? false : *ib );
	  ib++;
	}
    }

    void insert_point(const int j, ATOM a, const lace::vector3d<VALTYPE> &r, VALTYPE q, std::initializer_list<VALTYPE> xtr = {}, 
		   std::initializer_list<int> xti = {}, std::initializer_list<bool> xtb = {})
    {
      geometry<ATOM,DIM,VALTYPE,charT,traits>::insert_point(j,a,r);
      if (xchrg)
	chrg.insert( chrg.begin()+j, q );

      typename std::initializer_list<VALTYPE>::iterator ir = xtr.begin();
      for (int i=0; i<nxreal; i++)
	{
	  _xtr_real[i].insert( _xtr_real[i].begin()+j, ir == xtr.end() ? VALTYPE(0) : *ir );
	  ir++;
	}

      typename std::initializer_list<int>::iterator ii = xti.begin();
      for (int i=0; i<nxint; i++)
	{
	  _xtr_int[i].insert( _xtr_int[i].begin()+j, ii == xti.end() ? 0 : *ii );
	  ii++;
	}

      typename std::initializer_list<bool>::iterator ib = xtb.begin();
      for (int i=0; i<nxbool; i++)
	{
	  _xtr_bool[i].insert( _xtr_bool[i].begin()+j, ib == xtb.end() ? false : *ib );
	  ib++;
	}
    }

#else
#warning You need to enable -std=c++11 or -std=gnu++11 to have add_point and insert_point with extra fields. Everything else is working, however.
#endif

    virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "geometry";
      if (_name != "")
	os << " " << _name;
      os << "(" << DIM << "d,atom,x,y,z";
      if (xchrg)
	os << ",charge";
      for (int i=0; i<nxreal; i++)
	os << ",real";
      for (int i=0; i<nxint; i++)
	os << ",int";
      for (int i=0; i<nxbool; i++)
	os << ",bool";
      os << ")\n";
      for (int k=0; k<offset+2; k++) os << " ";
      os << "{\n";

      for (int i=0; i<size(); i++)
	{
	  for (int k=0; k<offset+4; k++) os << " ";
	  os << boost::format("%-5s %11.6f %11.6f %11.6f") % atm[i]->name  % crd[i].x() % crd[i].y() %crd[i].z();

	  if (xchrg)
	    os << boost::format(" %11.6f") % charge(i);
	  for (int j=0; j<nxreal; j++)
	    os <<  boost::format(" %11.6f") % xtr_real(i,j);
	  for (int j=0; j<nxint; j++)
	    os << boost::format(" %5i") % xtr_int(i,j);
	  for (int j=0; j<nxbool; j++)
	    os << boost::format(" %s") % (xtr_bool(i,j) ? "true" : "false");
	  os << "\n";
	}

      for (int k=0; k<offset+2; k++) os << " ";
      os << "}\n";
    }

  };


};

#endif
