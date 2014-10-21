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

  template< int DIM, class CREAL=double, class TRANSFORM = periodic_cell<DIM,CREAL> >
  class molecule_vector // fixme : public qpp_object<>
  {
    geometry<DIM,CREAL,TRANSFORM> *owner;

  public:
    std::vector<lace::vector3d<CREAL> > coord;
    typedef molecule_vector<DIM, CREAL,TRANSFORM> molvec;

    //    friend 
    // molecule_vector<POINT,DIM,CREAL> operator*(CREAL s, const molecule_vector<POINT,DIM,CREAL> &v);

  public:

    molecule_vector(){owner=NULL;}

    molecule_vector(geometry<DIM, CREAL, TRANSFORM> & _owner)
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

    inline geometry<DIM, CREAL, TRANSFORM> *geom() const
    {
      return owner;
    }

    void setgeom(geometry<DIM, CREAL, TRANSFORM> *_owner)
    {
      owner = _owner;
      if (owner!=NULL)
	{
	  coord.resize(owner -> size());
	  for (int i=0; i < coord.size(); i++)
	    coord[i] = CREAL(0);
	}
    }

    inline int size() const
    {
      return coord.size();
    }

    inline CREAL & operator()(int i, int j)
    { return coord[i](j); }

    inline CREAL operator()(int i, int j) const
    { return coord[i](j); }

    inline lace::vector3d<CREAL> & operator()(int i)
    { return coord[i]; }

    inline lace::vector3d<CREAL> operator()(int i) const
    { return coord[i]; }

    inline CREAL & operator[](int i)
    { return coord[i/3](i%3); }

    inline CREAL operator[](int i) const
    { return coord[i/3](i%3); }

    molecule_vector<DIM,CREAL,TRANSFORM>  operator+(const molecule_vector<DIM,CREAL,TRANSFORM> &v)
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

    molvec  operator*(CREAL s)
    {
      molvec res(owner);
      for (int i=0; i < coord.size(); i++)
	res.coord[i] = s*coord[i];
      return res;
    }

    molvec operator/(CREAL s)
    {
      molvec res(owner);
      for (int i=0; i < coord.size(); i++)
	res.coord[i] = coord[i]/s;
      return res;
    }

    CREAL norm() const
    {
      CREAL s = CREAL(0);
      for (int i=0; i < coord.size(); i++)
	s += lace::scal(coord[i],coord[i]);
      return std::sqrt(s);
    }

  };

  template< int DIM, class CREAL, class TRANSFORM>
  molecule_vector<DIM, CREAL, TRANSFORM> 
  operator*(CREAL s, const molecule_vector<DIM, CREAL, TRANSFORM> &v)
  {
    molecule_vector<DIM, CREAL, TRANSFORM> res(v.geom());
    for (int i=0; i < v.coord.size(); i++)
      res.coord[i] = s*v.coord[i];
    return res;
  }

  template< int DIM, class CREAL, class TRANSFORM>
  CREAL scal(const molecule_vector<DIM,CREAL,TRANSFORM> &v1, 
	       const molecule_vector<DIM,CREAL,TRANSFORM> &v2)
  {
    CREAL s;
    for (int i=0; i<v1.size()*3; i++)
      s += lace::conj(v1[i])*v2[i];
    return s;
  }

  template< int DIM, class CREAL, class TRANSFORM, class SYMOP>
  molecule_vector<DIM,CREAL,TRANSFORM> 
  operator*(const SYMOP & T, const molecule_vector<DIM,CREAL,TRANSFORM> &v)
  {
    lace::matrix3d<CREAL> R(T);
    molecule_vector<DIM,CREAL,TRANSFORM> res(*v.geom());
    for (int i=0; i < v.size(); i++)
      {
	lace::vector3d<CREAL> rnew = T * v.geom()->coord(i);
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

  template<int DIM, class CREAL>
  struct rotrans
  {
    static CREAL ttol,rtol;

    lace::vector3d<CREAL> T;
    lace::matrix3d<CREAL> R;

    periodic_cell<DIM,CREAL> * cell;
    
    rotrans(periodic_cell<DIM,CREAL> * _cell = NULL)
    {
      T = CREAL(0);
      R = CREAL(1);
      cell = _cell;
    }
    
    rotrans(const lace::vector3d<CREAL> &_T, periodic_cell<DIM,CREAL> * _cell = NULL)
    {
      T=_T;
      R = CREAL(1);
      cell = _cell;
    }
    
    rotrans(const lace::matrix3d<CREAL> & _R, periodic_cell<DIM,CREAL> * _cell = NULL)
    {
      T = CREAL(0);
      R = _R;
      cell = _cell;
    }

    rotrans(const lace::vector3d<CREAL> &_T, const lace::matrix3d<CREAL> &_R, 
	    periodic_cell<DIM,CREAL> * _cell = NULL)
    {
      T = _T;
      R = _R;
      cell = _cell;
    }

    inline rotrans<DIM,CREAL> operator*(const rotrans<DIM,CREAL> & b) const
    {
      lace::vector3d<CREAL> t = T + R*b.T;
      if (cell != NULL)
	t = cell -> reduce(t);
      return rotrans<DIM,CREAL>(t, R*b.R, cell);
    }

    inline bool operator==(const rotrans<DIM,CREAL> & b)
    {
      return norm(T - b.T) < ttol && norm(R - b.R) < rtol;
    }

    inline lace::vector3d<CREAL> operator*(const lace::vector3d<CREAL> & v) const
    {
      return T+R*v;
    }

  };

  template<int DIM, class CREAL>
  CREAL rotrans<DIM,CREAL>::ttol = 1e-10;

  template<int DIM, class CREAL>
  CREAL rotrans<DIM,CREAL>::rtol = 1e-10;

  template<int DIM, class CREAL>
  rotrans<DIM,CREAL> invert(const rotrans<DIM,CREAL> & R)
  {
    lace::matrix3d<CREAL> A = invert(R.R);
    lace::vector3d<CREAL> t = - A*R.T;
    if (R.cell != NULL)
      t = R.cell -> reduce(t);

    return( rotrans<DIM,CREAL>(t, A, R.cell) );
  }

  template<int DIM, class CREAL>
  rotrans<DIM,CREAL> pow(const rotrans<DIM,CREAL> & R, int n)
  {
    // fixme - very inefficient
    rotrans<DIM,CREAL> A;
    A.cell = R.cell;
    if (n>0)
      {
	while (n-- > 0)
	  A = R*A;
      }
    else if (n<0)
      {
	rotrans<DIM,CREAL>  B = invert(R);
	while (n++ < 0)
	  A = B*A;
      }
    return A;
  }

  // ---------------------- Periodic cell generalisation for any symmetries -------------
  //                       However, without the various stuff in periodic cell

  template<int DIM,class CREAL=double>
  struct gen_symplicator :  public qpp_object{

    rotrans<DIM,CREAL> R[DIM];
    int order[DIM];
    // fixme - think better about order
    //  order is the maximum number of times the rotrans can be applied
    // in other words, R^order is considered to equal unity even if it is not

    CREAL geomtol;

    STRING _name;

    gen_symplicator(const STRING &__name = "")
    {
      _name = __name;
      geomtol = default_geomtol;
    }

    inline rotrans<DIM,CREAL> & operator()(int i)
    { return R[i]; } 

    inline rotrans<DIM,CREAL> operator()(int i) const
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
	d = qtype_dim0;
      else if (DIM==1)
	d = qtype_dim1;
      else if (DIM==2)
	d = qtype_dim2;
      else if (DIM==3)
	d = qtype_dim3;
      return qtype_vectors | d;
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

  template<int DIM, class CREAL=double >
  struct symplicator : public gen_symplicator<DIM,CREAL>{

    using gen_symplicator<DIM,CREAL>::order;
    
    symplicator(const STRING & __name = "") : gen_symplicator<DIM,CREAL>(__name)
    {}

    lace::vector3d<CREAL> transform(const lace::vector3d<CREAL> &r, index<DIM> I) const
    {
      rotrans<DIM,CREAL> A;
      for (int d = 0; d<DIM; d++)
	A = pow( (*this)(d), I.cell(d)) * A;
      return A*r;
    }

  };

  // ----------------------------- Geometry on the manyfold surface ----------------------
  
  template<int DIM,class CREAL=double >
  class surf_symplicator : public gen_symplicator<DIM,CREAL>{

    parametric_surface<CREAL> * _mfold;

  public:
    using gen_symplicator<DIM,CREAL>::order;
    using gen_symplicator<DIM,CREAL>::geomtol;
    
    surf_symplicator(parametric_surface<CREAL> & __mfold, 
		     const STRING & __name = "") : gen_symplicator<DIM,CREAL>(__name)
    {
      _mfold = & __mfold;
    }

    inline parametric_surface<CREAL> & mfold()
    {
      return *_mfold;
    }

    lace::vector3d<CREAL> transform(const lace::vector3d<CREAL> &r, index<DIM> I) const
    {
      rotrans<DIM,CREAL> A;
      for (int d = 0; d<DIM; d++)
	A = pow( (*this)(d), I.cell(d)) * A;
      lace::vector3d<CREAL> r1 = A*r;
      return _mfold->map(lace::vector2d<CREAL>(r1(0), r1(1) ));
    }

    // -------------------------------------------------------

    void symmtrap(lace::vector3d<CREAL> & r, CREAL symmtrap_radius)
    {
      index<DIM> a(0), b(0);
      for (int d = 0; d<DIM; d++)
	b.cell(d) = order[d];

      index<DIM> I=a;

      lace::vector2d<CREAL> p = mfold().project(r), p0=p;	  
      std::vector<lace::vector3d<CREAL> > rr;
      rr.push_back( transform(r,0) );
      
      while (true)
	{
	  //std::cout << I;
	  lace::vector3d<CREAL> r1 = transform(r,I);
	  CREAL dist = norm(rr[0] - r1);
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

  template< int DIM, class CREAL=double, class TRANSFORM = periodic_cell<DIM,CREAL> >
  class xtr_geometry : public geometry<DIM,CREAL,TRANSFORM>{
  
    //    std::vector<CREAL> chrg;

    std::vector<std::vector<CREAL> >  _xtr_real;
    std::vector<std::vector<int> >      _xtr_int;
    std::vector<std::vector<short> >    _xtr_bool;

    std::vector<STRING> _field_name;

    int nxreal, nxint, nxbool;
    //bool xchrg;

    using geometry<DIM,CREAL>::atm;
    using geometry<DIM,CREAL>::crd;
    using geometry<DIM,CREAL>::size;
    using geometry<DIM,CREAL>::_name;

  public:

    xtr_geometry(int n_xtr_real=0, int n_xtr_int=0, int n_xtr_bool=0, STRING __name = "") :
      _xtr_real(n_xtr_real), _xtr_int(n_xtr_int), _xtr_bool(n_xtr_bool), 
      _field_name(n_xtr_real + n_xtr_int + n_xtr_bool),
      geometry<DIM,CREAL>(__name)
    {
      //xchrg = charge;
      nxreal = n_xtr_real;
      nxint = n_xtr_int;
      nxbool = n_xtr_bool;      
    }

    virtual qppobject_type gettype() const
    {
      return geometry<DIM,CREAL>::gettype() | qtype_xgeometry;
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

    int n_xreal() const
    { return nxreal; }

    int n_xint() const
    { return nxint;}

    int n_xbool() const
    { return nxbool;}

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

    CREAL xtr_real(int i, int j) const
    { return _xtr_real[i][j]; }

    CREAL & xtr_real(int i, int j)
    { return _xtr_real[i][j]; }

    int xtr_int(int i, int j) const
    { return _xtr_int[i][j]; }

    int & xtr_int(int i, int j)
    { return _xtr_int[i][j]; }

    bool xtr_bool(int i, int j) const
    { return * ((bool*) & _xtr_bool[i][j]); }

    bool & xtr_bool(int i, int j)
    { return * ((bool*) & _xtr_bool[i][j]); }
    /*
    CREAL charge(int i) const
    { return chrg[i]; }

    CREAL & charge(int i)
    { return chrg[i]; }
    */
    virtual void erase(const int j)
    {
      //debug
      /*
      std::cerr << "erase of xtr_geometry:enter\n";
      std::cerr << j << " " << size(); 
      for (int i=0; i<nxreal; i++) std::cerr << " " << _xtr_real[i].size();
      for (int i=0; i<nxint; i++) std::cerr << " " << _xtr_int[i].size();
      for (int i=0; i<nxbool; i++) std::cerr << " " << _xtr_bool[i].size();
      std::cerr << "\n";
      */

      geometry<DIM,CREAL>::erase(j);
      for (int i=0; i<nxreal; i++)
	_xtr_real[i].erase(_xtr_real[i].begin()+j);
      for (int i=0; i<nxint; i++)
	_xtr_int[i].erase(_xtr_int[i].begin()+j);
      for (int i=0; i<nxbool; i++)
	_xtr_bool[i].erase(_xtr_bool[i].begin()+j);
      //     if (xchrg)
      //	chrg.erase(chrg.begin()+j);  
      //std::cerr << "erase of xtr_geometry:exit\n";
    }

#ifdef __GXX_EXPERIMENTAL_CXX0X__

    void add(const STRING & a, const lace::vector3d<CREAL> & r,
	     std::initializer_list<CREAL> xtr, 
	     std::initializer_list<int> xti = {}, 
	     std::initializer_list<bool> xtb = {})
    {
      //std::cerr << "xtr_geometry::add entry\n";

      //      if (xchrg)
      //	chrg.push_back( q );

      typename std::initializer_list<CREAL>::iterator ir = xtr.begin();
      for (int i=0; i<nxreal; i++)
	{
	  _xtr_real[i].push_back( ir == xtr.end() ? CREAL(0) : *ir );
	  if (ir != xtr.end() ) 
	    ir++;
	}

      typename std::initializer_list<int>::iterator ii = xti.begin();
      for (int i=0; i<nxint; i++)
	{
	  _xtr_int[i].push_back( ii == xti.end() ? 0 : *ii );
	  if (ii != xti.end() ) 
	    ii++;
	}

      typename std::initializer_list<bool>::iterator ib = xtb.begin();
      for (int i=0; i<nxbool; i++)
	{
	  _xtr_bool[i].push_back( ib == xtb.end() ? false : *ib );
	  if (ib != xtb.end() ) 
	    ib++;
	}
      geometry<DIM,CREAL>::add(a,r);
    }

    void insert(const int j, const STRING & a, const lace::vector3d<CREAL> &r,
		std::initializer_list<CREAL> xtr, 
		std::initializer_list<int> xti = {}, 
		std::initializer_list<bool> xtb = {})
    {
      //if (xchrg)
      //	chrg.insert( chrg.begin()+j, q );

      typename std::initializer_list<CREAL>::iterator ir = xtr.begin();
      for (int i=0; i<nxreal; i++)
	{
	  _xtr_real[i].insert( _xtr_real[i].begin()+j, ir == xtr.end() ? CREAL(0) : *ir );
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
      geometry<DIM,CREAL>::insert(j,a,r);
    }

#else
#warning You need to enable -std=c++11 or -std=gnu++11 to have "add" and "insert" with extra fields. Everything else is working, however.

#endif

    virtual void add(const STRING &a, const lace::vector3d<CREAL> & r)
    {

      //std::cerr << "xtr_geometry::add entry\n";
      //if (xchrg)
      //	chrg.push_back( CREAL(0) );   
      for (int i=0; i<nxreal; i++)
	_xtr_real[i].push_back( CREAL(0) );
      for (int i=0; i<nxint; i++)
	_xtr_int[i].push_back(0);
      for (int i=0; i<nxbool; i++)
	_xtr_bool[i].push_back( false );
      geometry<DIM,CREAL>::add(a,r);
    }

    virtual void insert(const int j, STRING a, const lace::vector3d<CREAL> &r)
    {

      //if (xchrg)
      //	chrg.insert(chrg.begin()+j, CREAL(0) );  
      for (int i=0; i<nxreal; i++)
	_xtr_real[i].insert(_xtr_real[i].begin()+j, CREAL(0) );
      for (int i=0; i<nxint; i++)
	_xtr_int[i].insert(_xtr_int[i].begin()+j, 0);
      for (int i=0; i<nxbool; i++)
	_xtr_bool[i].insert(_xtr_bool[i].begin()+j, false);
      geometry<DIM,CREAL>::insert(j,a,r);
    }

    virtual void add(STRING a, CREAL _x, CREAL _y, CREAL _z)
    {
      add(a, lace::vector3d<CREAL>(_x,_y,_z));
    }

    virtual void insert(const int j, STRING a, const CREAL _x, const CREAL _y, const CREAL _z)
    {
      insert(j,a,lace::vector3d<CREAL>(_x,_y,_z));
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
	    os <<  boost::format(" %11.6f") % xtr_real(j,i);
	  for (int j=0; j<nxint; j++)
	    os << boost::format(" %5i") % xtr_int(j,i);
	  for (int j=0; j<nxbool; j++)
	    os << boost::format(" %s") % (xtr_bool(j,i) ? "true" : "false");
	  os << "\n";
	}

      for (int k=0; k<offset+2; k++) os << " ";
      os << "}\n";
    }

  };

};

#endif
