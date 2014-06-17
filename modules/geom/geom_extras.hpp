#ifndef _QPP_GEOM_EXTRAS_H
#define _QPP_GEOM_EXTRAS_H

#include <geom/geom.hpp>
#include <geom/manyfold.hpp>

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

  template< int DIM, class VALTYPE=double, class TRANSFORM = periodic_cell<DIM,VALTYPE> >
  class molecule_vector // fixme : public qpp_object<>
  {
    gen_geometry<DIM,VALTYPE,TRANSFORM> *owner;

  public:
    std::vector<lace::vector3d<VALTYPE> > coord;
    typedef molecule_vector<DIM, VALTYPE,TRANSFORM> molvec;

    //    friend 
    // molecule_vector<POINT,DIM,VALTYPE> operator*(VALTYPE s, const molecule_vector<POINT,DIM,VALTYPE> &v);

  public:

    molecule_vector(){owner=NULL;}

    molecule_vector(gen_geometry<DIM, VALTYPE, TRANSFORM> & _owner)
    {
      setgeom(&_owner);      
    }

    molecule_vector(const molvec & v)
    {
      setgeom(v.owner);
      if (owner != NULL)
	for (int i=0; i<size(); i++)
	  coord[i] = v.coord[i];
    }

    inline gen_geometry<DIM, VALTYPE, TRANSFORM> *geom() const
    {
      return owner;
    }

    void setgeom(gen_geometry<DIM, VALTYPE, TRANSFORM> *_owner)
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
    { return coord[i](j); }

    inline VALTYPE operator()(int i, int j) const
    { return coord[i](j); }

    inline lace::vector3d<VALTYPE> & operator()(int i)
    { return coord[i]; }

    inline lace::vector3d<VALTYPE> operator()(int i) const
    { return coord[i]; }

    inline VALTYPE & operator[](int i)
    { return coord[i/3](i%3); }

    inline VALTYPE operator[](int i) const
    { return coord[i/3](i%3); }

    molecule_vector<DIM,VALTYPE,TRANSFORM>  operator+(const molecule_vector<DIM,VALTYPE,TRANSFORM> &v)
    {
      assert(size() == v.size());
      molvec res(owner);
      for (int i=0; i < coord.size(); i++)
	res.coord[i] = coord[i] + v.coord[i];
      return res;
    }

    molvec  operator-(const molvec &v)
    {
      assert(size() == v.size());
      molvec res(owner);
      for (int i=0; i < coord.size(); i++)
	res.coord[i] = coord[i] - v.coord[i];
      return res;
    }

    molvec  operator*(VALTYPE s)
    {
      molvec res(owner);
      for (int i=0; i < coord.size(); i++)
	res.coord[i] = s*coord[i];
      return res;
    }

    molvec operator/(VALTYPE s)
    {
      molvec res(owner);
      for (int i=0; i < coord.size(); i++)
	res.coord[i] = coord[i]/s;
      return res;
    }

    VALTYPE norm() const
    {
      VALTYPE s = VALTYPE(0);
      for (int i=0; i < coord.size(); i++)
	s += lace::scal(coord[i],coord[i]);
      return std::sqrt(s);
    }

  };

  template< int DIM, class VALTYPE, class TRANSFORM>
  molecule_vector<DIM, VALTYPE, TRANSFORM> 
  operator*(VALTYPE s, const molecule_vector<DIM, VALTYPE, TRANSFORM> &v)
  {
    molecule_vector<DIM, VALTYPE, TRANSFORM> res(v.geom());
    for (int i=0; i < v.coord.size(); i++)
      res.coord[i] = s*v.coord[i];
    return res;
  }

  template< int DIM, class VALTYPE, class TRANSFORM>
  VALTYPE scal(const molecule_vector<DIM,VALTYPE,TRANSFORM> &v1, 
	       const molecule_vector<DIM,VALTYPE,TRANSFORM> &v2)
  {
    VALTYPE s;
    for (int i=0; i<v1.size()*3; i++)
      s += lace::conj(v1[i])*v2[i];
    return s;
  }

  template< int DIM, class VALTYPE, class TRANSFORM, class SYMOP>
  molecule_vector<DIM,VALTYPE,TRANSFORM> 
  operator*(const SYMOP & T, const molecule_vector<DIM,VALTYPE,TRANSFORM> &v)
  {
    lace::matrix3d<VALTYPE> R(T);
    molecule_vector<DIM,VALTYPE,TRANSFORM> res(*v.geom());
    for (int i=0; i < v.size(); i++)
      {
	lace::vector3d<VALTYPE> rnew = T * v.geom()->coord(i);
	int j;
	bool found = false;
	for (j=0; j<v.size(); j++)
	  if ( lace::norm(rnew - v.geom()-> coord(j) ) <= symmtol )
	    {
	      found = true; break;
	    }
	// fixme - think about this behavoir for non-symmetric mols
	// fixme - what goes first T transform of the transform coord -> position ?
	if (!found) j = i;
	res(j) = R*v(i);
      }
    
    return res;
  }

  // ------------------------ Rotrance - rotational & translational operations ----------

  template<int DIM, class VALTYPE>
  struct rotrans
  {
    static VALTYPE ttol,rtol;

    lace::vector3d<VALTYPE> T;
    lace::matrix3d<VALTYPE> R;

    periodic_cell<DIM,VALTYPE> * cell;
    
    rotrans(periodic_cell<DIM,VALTYPE> * _cell = NULL)
    {
      T = VALTYPE(0);
      R = VALTYPE(1);
      cell = _cell;
    }
    
    rotrans(const lace::vector3d<VALTYPE> &_T, periodic_cell<DIM,VALTYPE> * _cell = NULL)
    {
      T=_T;
      R = VALTYPE(1);
      cell = _cell;
    }
    
    rotrans(const lace::matrix3d<VALTYPE> & _R, periodic_cell<DIM,VALTYPE> * _cell = NULL)
    {
      T = VALTYPE(0);
      R = _R;
      cell = _cell;
    }

    rotrans(const lace::vector3d<VALTYPE> &_T, const lace::matrix3d<VALTYPE> &_R, 
	    periodic_cell<DIM,VALTYPE> * _cell = NULL)
    {
      T = _T;
      R = _R;
      cell = _cell;
    }

    inline rotrans<DIM,VALTYPE> operator*(const rotrans<DIM,VALTYPE> & b) const
    {
      lace::vector3d<VALTYPE> t = T + R*b.T;
      if (cell != NULL)
	t = cell -> reduce(t);
      return rotrans<DIM,VALTYPE>(t, R*b.R, cell);
    }

    inline bool operator==(const rotrans<DIM,VALTYPE> & b)
    {
      return norm(T - b.T) < ttol && norm(R - b.R) < rtol;
    }

    inline lace::vector3d<VALTYPE> operator*(const lace::vector3d<VALTYPE> & v) const
    {
      return T+R*v;
    }

  };

  template<int DIM, class VALTYPE>
  VALTYPE rotrans<DIM,VALTYPE>::ttol = 1e-10;

  template<int DIM, class VALTYPE>
  VALTYPE rotrans<DIM,VALTYPE>::rtol = 1e-10;

  template<int DIM, class VALTYPE>
  rotrans<DIM,VALTYPE> invert(const rotrans<DIM,VALTYPE> & R)
  {
    lace::matrix3d<VALTYPE> A = invert(R.R);
    lace::vector3d<VALTYPE> t = - A*R.T;
    if (R.cell != NULL)
      t = R.cell -> reduce(t);

    return( rotrans<DIM,VALTYPE>(t, A, R.cell) );
  }

  template<int DIM, class VALTYPE>
  rotrans<DIM,VALTYPE> pow(const rotrans<DIM,VALTYPE> & R, int n)
  {
    // fixme - very inefficient
    rotrans<DIM,VALTYPE> A;
    A.cell = R.cell;
    if (n>0)
      {
	while (n-- > 0)
	  A = R*A;
      }
    else if (n<0)
      {
	rotrans<DIM,VALTYPE>  B = invert(R);
	while (n++ < 0)
	  A = B*A;
      }
    return A;
  }

  // ---------------------- Periodic cell generalisation for any symmetries -------------
  //                       However, without the various stuff in periodic cell

  template<int DIM,class VALTYPE=double>
  struct gen_symplicator :  public qpp_object{

    rotrans<DIM,VALTYPE> R[DIM];
    int order[DIM];
    // fixme - think better about order
    //  order is the maximum number of times the rotrans can be applied
    // in other words, R^order is considered to equal unity even if it is not

    VALTYPE geomtol;

    STRING _name;

    gen_symplicator(const STRING &__name = "")
    {
      _name = __name;
      geomtol = default_geomtol;
    }

    inline rotrans<DIM,VALTYPE> & operator()(int i)
    { return R[i]; } 

    inline rotrans<DIM,VALTYPE> operator()(int i) const
    { return R[i]; } 

    virtual STRING category() const
    {
      return "symplicator";
      // fixme - is this a correct name
    }

    virtual STRING name() const
    {
      return _name;
    }

    virtual int n_next() const
    { return 0; }

    virtual qpp_object* next(int i)
    { return NULL;}

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
      // fixme - it's not "vectors"
    }

    virtual void error(STRING const & what)
    { //fixme
    }

    virtual STRING error()
    {
      //fixme
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      // fixme - implement this
    }

  };

  // ---------------------------------------------------------------------------------

  template<int DIM, class VALTYPE=double >
  struct symplicator : public gen_symplicator<DIM,VALTYPE>{

    using gen_symplicator<DIM,VALTYPE>::order;
    
    symplicator(const STRING & __name = "") : gen_symplicator<DIM,VALTYPE>(__name)
    {}

    lace::vector3d<VALTYPE> transform(const lace::vector3d<VALTYPE> &r, index<DIM> I) const
    {
      rotrans<DIM,VALTYPE> A;
      for (int d = 0; d<DIM; d++)
	A = pow( (*this)(d), I.cell(d)) * A;
      return A*r;
    }

  };

  // ----------------------------- Geometry on the manyfold surface ----------------------
  
  template<int DIM,class VALTYPE=double >
  class surf_symplicator : public gen_symplicator<DIM,VALTYPE>{

    parametric_surface<VALTYPE> * _mfold;

  public:
    using gen_symplicator<DIM,VALTYPE>::order;
    using gen_symplicator<DIM,VALTYPE>::geomtol;
    
    surf_symplicator(parametric_surface<VALTYPE> & __mfold, 
		     const STRING & __name = "") : gen_symplicator<DIM,VALTYPE>(__name)
    {
      _mfold = & __mfold;
    }

    inline parametric_surface<VALTYPE> & mfold()
    {
      return *_mfold;
    }

    lace::vector3d<VALTYPE> transform(const lace::vector3d<VALTYPE> &r, index<DIM> I) const
    {
      rotrans<DIM,VALTYPE> A;
      for (int d = 0; d<DIM; d++)
	A = pow( (*this)(d), I.cell(d)) * A;
      lace::vector3d<VALTYPE> r1 = A*r;
      return _mfold->map(lace::vector2d<VALTYPE>(r1(0), r1(1) ));
    }

    // -------------------------------------------------------

    void symmtrap(lace::vector3d<VALTYPE> & r, VALTYPE symmtrap_radius)
    {
      index<DIM> a(0), b(0);
      for (int d = 0; d<DIM; d++)
	b.cell(d) = order[d];

      index<DIM> I=a;

      lace::vector2d<VALTYPE> p = mfold().project(r), p0=p;	  
      std::vector<lace::vector3d<VALTYPE> > rr;
      rr.push_back( transform(r,0) );
      
      while (true)
	{
	  //std::cout << I;
	  lace::vector3d<VALTYPE> r1 = transform(r,I);
	  VALTYPE dist = norm(rr[0] - r1);
	  if ( dist < symmtrap_radius && dist > geomtol)
	    rr.push_back(r1);
	  
	  int d=0;
	  while (d<DIM)
	    {
	      I.cell(d)++;
	      if (I.cell(d)>=order[d])
		{
		  for (int dd=0; dd<=d; dd++)
		    I.cell(dd)=0;
		  d++;
		}
	      else
		break;
	    }
	  if (d==DIM)
	    break;
	}
      //std::cout << "\n";
      
      if ( rr.size()>1 )
	{
	  r = 0;
	  for (int i=0; i<rr.size(); i++)
	    r += rr[i];
	  r /= rr.size();
	  std::cout << "symmtrap: ";
	  for (int i=0; i<rr.size(); i++) 
	    std::cout << " " << rr[i];
	  std::cout << "\n" << p0 << " => " << p << "\n";
	  r.x() = p.x;
	  r.y() = p.y;
	  r.z() = 0e0;
	}
    }


  };  

  

  
  // ---------------- Geometry with extra fields - for storing any additional data -------------------

  template< int DIM, class VALTYPE=double >
  class xtr_geometry : public geometry<DIM,VALTYPE>{
  
    //    std::vector<VALTYPE> chrg;

    std::vector<std::vector<VALTYPE> >  _xtr_real;
    std::vector<std::vector<int> >      _xtr_int;
    std::vector<std::vector<short> >    _xtr_bool;

    std::vector<STRING> _field_name;

    int nxreal, nxint, nxbool;
    //bool xchrg;

    using geometry<DIM,VALTYPE>::atm;
    using geometry<DIM,VALTYPE>::crd;
    using geometry<DIM,VALTYPE>::size;
    using geometry<DIM,VALTYPE>::_name;

  public:

    xtr_geometry(int n_xtr_real=0, int n_xtr_int=0, int n_xtr_bool=0, STRING __name = "") :
      _xtr_real(n_xtr_real), _xtr_int(n_xtr_int), _xtr_bool(n_xtr_bool), 
      _field_name(n_xtr_real + n_xtr_int + n_xtr_bool),
      geometry<DIM,VALTYPE>(__name)
    {
      //xchrg = charge;
      nxreal = n_xtr_real;
      nxint = n_xtr_int;
      nxbool = n_xtr_bool;      
    }

    virtual int gettype()
    {
      return geometry<DIM,VALTYPE>::gettype() | data_xgeometry;
    }

    /*
    ~xtr_geometry()
    {
      std::cout << "destructor\n";
      std::cout << "  real\n";
      if (nxint>0)
	delete _xtr_int;
      std::cout << "  int\n";
      if (nxbool>0)
	delete _xtr_bool;
      std::cout << "  bool\n";
      }
    */

    STRING & field_name(int i)
    { return _field_name[i]; }

    STRING field_name(int i) const
    { return _field_name[i]; }

    STRING & xreal_name(int i)
    { return _field_name[i]; }

    STRING xreal_name(int i) const
    { return _field_name[i]; }

    STRING & xint_name(int i)
    { return _field_name[nxreal+i]; }

    STRING xint_name(int i) const
    { return _field_name[nxreal+i]; }

    STRING & xbool_name(int i)
    { return _field_name[nxreal+nxint+i]; }

    STRING xbool_name(int i) const
    { return _field_name[nxreal+nxint+i]; }

    VALTYPE xtr_real(int i, int j) const
    { return _xtr_real[j][i]; }

    VALTYPE & xtr_real(int i, int j)
    { return _xtr_real[j][i]; }

    int xtr_int(int i, int j) const
    { return _xtr_int[j][i]; }

    int & xtr_int(int i, int j)
    { return _xtr_int[j][i]; }

    bool xtr_bool(int i, int j) const
    { return * ((bool*) & _xtr_bool[j][i]); }

    bool & xtr_bool(int i, int j)
    { return * ((bool*) & _xtr_bool[j][i]); }
    /*
    VALTYPE charge(int i) const
    { return chrg[i]; }

    VALTYPE & charge(int i)
    { return chrg[i]; }
    */
    virtual void erase(const int j)
    {
      geometry<DIM,VALTYPE>::erase(j);
      for (int i=0; i<nxreal; i++)
	_xtr_real[i].erase(_xtr_real[i].begin()+j);
      for (int i=0; i<nxint; i++)
	_xtr_int[i].erase(_xtr_int[i].begin()+j);
      for (int i=0; i<nxbool; i++)
	_xtr_bool[i].erase(_xtr_bool[i].begin()+j);
      //     if (xchrg)
      //	chrg.erase(chrg.begin()+j);  
    }

#ifdef __GXX_EXPERIMENTAL_CXX0X__

    void add(STRING a, const lace::vector3d<VALTYPE> & r,
	     std::initializer_list<VALTYPE> xtr = {}, 
	     std::initializer_list<int> xti = {}, 
	     std::initializer_list<bool> xtb = {})
    {
      geometry<DIM,VALTYPE>::add(a,r);

      //      if (xchrg)
      //	chrg.push_back( q );

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

    void insert(const int j, STRING a, const lace::vector3d<VALTYPE> &r,
		      std::initializer_list<VALTYPE> xtr = {}, 
		      std::initializer_list<int> xti = {}, 
		      std::initializer_list<bool> xtb = {})
    {
      geometry<DIM,VALTYPE>::insert(j,a,r);
      //if (xchrg)
      //	chrg.insert( chrg.begin()+j, q );

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
#warning You need to enable -std=c++11 or -std=gnu++11 to have "add" and "insert" with extra fields. Everything else is working, however.

    virtual void add(STRING a, const lace::vector3d<VALTYPE> & r)
    {
      geometry<DIM,VALTYPE>::add(a,r);

      //if (xchrg)
      //	chrg.push_back( VALTYPE(0) );   
      for (int i=0; i<nxreal; i++)
	_xtr_real[i].push_back( VALTYPE(0) );
      for (int i=0; i<nxint; i++)
	_xtr_int[i].push_back(0);
      for (int i=0; i<nxbool; i++)
	_xtr_bool[i].push_back( false );
    }

    virtual void insert(const int j, STRING a, const lace::vector3d<VALTYPE> &r)
    {
      geometry<DIM,VALTYPE>::insert(j,a,r);

      //if (xchrg)
      //	chrg.insert(chrg.begin()+j, VALTYPE(0) );  
      for (int i=0; i<nxreal; i++)
	_xtr_real[i].insert(_xtr_real[i].begin()+j, VALTYPE(0) );
      for (int i=0; i<nxint; i++)
	_xtr_int[i].insert(_xtr_int[i].begin()+j, 0);
      for (int i=0; i<nxbool; i++)
	_xtr_bool[i].insert(_xtr_bool[i].begin()+j, false);
    }

#endif

    virtual void add(STRING a, VALTYPE _x, VALTYPE _y, VALTYPE _z)
    {
      add(a, lace::vector3d<VALTYPE>(_x,_y,_z));
    }

    virtual void insert(const int j, STRING a, const VALTYPE _x, const VALTYPE _y, const VALTYPE _z)
    {
      insert(j,a,lace::vector3d<VALTYPE>(_x,_y,_z));
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "geometry";
      if (_name != "")
	os << " " << _name;
      os << "(" << DIM << "d,atom,x,y,z";
      for (int i=0; i<nxreal; i++)
	{
	  os << ",";
	  if ( xreal_name(i) != "")
	    os << xreal_name(i) << "=";
	  os << "real";
	}
      for (int i=0; i<nxint; i++)
	{
	  os << ",";
	  if ( xint_name(i) != "")
	    os << xint_name(i) << "=";
	  os << "int";
	}
      for (int i=0; i<nxbool; i++)
	{
	  os << ",";
	  if ( xbool_name(i) != "")
	    os << xbool_name(i) << "=";
	  os << "bool";
	}
      os << ")\n";
      for (int k=0; k<offset+2; k++) os << " ";
      os << "{\n";

      for (int i=0; i<size(); i++)
	{
	  for (int k=0; k<offset+4; k++) os << " ";
	  os << boost::format("%-5s %11.6f %11.6f %11.6f") % atm[i] % crd[i].x() % crd[i].y() %crd[i].z();

	  //if (xchrg)
	  //  os << boost::format(" %11.6f") % charge(i);
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
