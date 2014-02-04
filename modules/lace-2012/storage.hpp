
#ifndef _LACE_STORAGE_H
#define _LACE_STORAGE_H

#include <lace-2012/shape.hpp>
#include <lace-2012/element.hpp>
#include <cstring>

namespace _lace_storage{

//   using _lace_basic::matrix_type;
//   using _lace_basic::matrix_shape;
// //   using _lace_basic::matrix_shape_banded;
// //   using _lace_basic::matrix_shape_triang;

//   using _lace_basic::vector_type;
//   using _lace_basic::vector_shape;


  //---------------------------------------------//
  //              Reference counter              //
  //---------------------------------------------//


  // fixme - think better about reference counting and temporaries creation/release
  template <class PARENT>
  class refcounter
  {
    int nref;
    PARENT *parent;
  public:
    refcounter(PARENT *p){parent = p; nref = 1; }

    int operator()(){return nref;}

    void operator++(int i){nref++;}

    void operator--(int i){nref--; if(nref==0) delete parent;}

    ~refcounter(){}
  };




  /* --------------------------------------------------------- *
   *                                                           *
   *                Matrix storage classes                     *
   *                                                           *
   * --------------------------------------------------------- *
   *
   *   Storage classes implement the matrix storage mechanism
   * for different types of matricies. This is achieved by
   * template specialization for each type. 
   *   The most important methods (like element access) must be 
   * inline. "Most important" here means the methods which work with
   * elements of matrix and consequently might be called many times (N*M, say).
   *   The methods which work with the whole matrix are OK to be virtual, the 
   * penalty for virtual calls will be negligible
   */

  template<class VALTYPE, matrix_type MTRTYPE>
  class matrix_storage;

  //---------------------------------------------------//
  //             Dense rectangular matrix              //
  //---------------------------------------------------//

  template<class VALTYPE>
  class matrix_storage<VALTYPE,rectang>
  {
    // VALTYPE is a type of elements 
    // Meaningful VALTYPES are
    // double, float, complex<double> and complex<float>

    //  _vals -- the linear array of N*M values
    //  stored in column major form to be BLAS compatible
    VALTYPE *_vals;
    matrix_shape _shp;
    int _memsize;

    friend class _lace_expressions::matrix<VALTYPE,rectang>;

  public:

    // fixme -- think better about reference counting
    // fixme -- the shape

    // Reference counter is here to allow sereval matricies to
    // point at the same storage. These matricies, of course,
    // would have the same elemnts and changing one of them will
    // change the others.
    //
    // When a new matrix references this storage, the nref++ operation
    // should be done. When this matrix changes its storage or is deleted,
    // the nref-- operation decreases number of references by one.
    // When the number of references is zero (nobody uses this storage), the
    // storage is deleted and memory released.
  
    refcounter<matrix_storage<VALTYPE,rectang> > nref;

    // Empty constructor creates no matrix
    matrix_storage() : _shp(rectang,0,0), nref(this) 
    { _vals = NULL; }
    // fixme -empty shape
  
    // Use shape object to create matrix
    matrix_storage( matrix_shape shp) : _shp(shp), nref(this) 
    {
      _vals = NULL;
      resize(shp);
    }

    // Copy constructor
    matrix_storage( matrix_storage<VALTYPE,rectang> &s) : _shp(s._shp), nref(this) 
    {
      _memsize = s._memsize;
      _vals = new VALTYPE [_memsize];
    
      copy(s);
    };

    // Resize matrix assuming new shape. The current matrix is lost
    inline void resize(matrix_shape shp)
    {
      _shp = shp;
      assert( _shp.mtype == rectang && 
	      "Incosistent matrix type in matrix_storage<VALTYPE,rectang> constructor" );
      _memsize = _shp.n * _shp.m;

      if (_vals != NULL ) delete _vals;
      _vals = new VALTYPE [_memsize];
    }

    // Copy the the contents of s into this object
    inline void copy( matrix_storage<VALTYPE,rectang> &s )
    {
      std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    // Scale all matrix elements by value s
    inline void scale(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] *= s;
    }  

    inline void setval(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] = s;
    }
  
    // The access operator
    inline VALTYPE & operator()(int i, int j)
    {
      return _vals[ j*_shp.n + i ];
    }

    inline VALTYPE* ptr(int i, int j)
    {
      return &_vals[ j*_shp.n + i ];
    }

    // Returns the matrix shape
    matrix_shape shape()
    {
      return _shp;
    }

    // size(0) - number of raws
    // size(1) - number of columns
    inline int size(int dim)
    {
      return _shp.size(dim);
    }

    // defined(i,j) is true, if such element in this matrix can be non-zero and is stored
    //       in this object
    //   In rectangular matrix all elements are defined.
    //   In upper triangular -- only the upper triangular part and the diagonal are defined
    //   In banded matrix only the diagonal
    inline bool defined(int i, int j)
    { return true;}

    // unique(i,j) is true, if such element belongs to irreducible part of this matrix
    // for example, in symmetrix matrix elements are unique only with i<=j. 
    // Elements with i>j are easily obtained by A(i,j)=A(j,i)
    //
    // The relation between defined(i,j) and unique(i,j)
    // Of course, all elements that are unique(i,j) are also defined(i,j), but the opposite
    // might not be true.
    inline bool unique(int i, int j)
    { return true;}

    // Destructor
    ~matrix_storage()
    {
      if (_memsize > 0)
	delete _vals;
    }

  };

  //---------------------------------------------------//
  //             Dense symmetric matrix                //
  //---------------------------------------------------//

  // All the methods have the same meaning as for 
  // matrix_storage<VALTYPE,rectang>, only
  // implementation differs.
  // See the comments to matrix_storage<VALTYPE,rectang>

  template<class VALTYPE>
  class matrix_storage<VALTYPE,symmetric>
  {
  protected:

    VALTYPE *_vals;
    matrix_shape _shp;
    int _memsize;

    friend class _lace_expressions::matrix<VALTYPE,symmetric>;

  public:

    refcounter<matrix_storage<VALTYPE,symmetric> > nref;

    matrix_storage() : _shp(symmetric,0,0), nref(this){}

    matrix_storage( matrix_shape shp) : _shp(shp), nref(this)
    {
      _vals = NULL;
      resize(shp);
    }

    matrix_storage( matrix_storage<VALTYPE,symmetric> &s) : _shp(s._shp), nref(this)
    {
      _shp = s._shp;
      _memsize = s._memsize;
      _vals = new VALTYPE [_memsize];

      copy(s);
      // std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void resize(matrix_shape shp)
    {
      _shp = shp;
      assert( _shp.mtype == symmetric && 
	      "Incosistent matrix type in matrix_storage<VALTYPE,symmetric> constructor" );
      assert( _shp.n == _shp.m && "Attempt to create symmetric matrix with N != M " );
      _memsize = _shp.n*(_shp.n+1)/2;

      if (_vals != NULL) delete _vals;
      _vals = new VALTYPE [_memsize];
    }

    inline void copy( matrix_storage<VALTYPE,symmetric> &s)
    {
      std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void scale(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] *= s;
    }  

    inline void setval(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] = s;
    }
  
    // Access operator & function

    inline VALTYPE & operator()(int i, int j)
    {
      if ( j >= i )
	return _vals[ j*(j+1)/2 + i ];
      else
	return _vals[ i*(i+1)/2 + j ];
    }

    inline VALTYPE* ptr(int i, int j)
    {
      return unique(i,j) ? &_vals[ i*(i+1)/2 + j ] : NULL;
    }

    matrix_shape shape()
    {
      return _shp;
    }

    inline int size(int dim)
    {
      assert( (dim==0 || dim==1) && "Illegal dimension" );    
      return _shp.n;
    }

    inline bool defined(int i, int j)
    { return true;}

    inline bool unique(int i, int j)
    { return j<=i;}

    ~matrix_storage()
    {
      if (_memsize > 0)
	delete _vals;
    }

  };


  //---------------------------------------------------//
  //             Dense hermitian matrix                //
  //---------------------------------------------------//

  // The storage is organized exactly the same way, as for
  // symmetric matrix. The only difference is the behaviour
  // of matrix elements, which is implemented in matrix.hpp


  template<class VALTYPE>
  class matrix_storage<VALTYPE,hermitian>
  {
  protected:

    VALTYPE *_vals;
    matrix_shape _shp;
    int _memsize;

    friend class _lace_expressions::matrix<VALTYPE,hermitian>;

    //    typedef _complex_reference<VALTYPE> _element;
  public:

    refcounter<matrix_storage<VALTYPE,hermitian> > nref;

    matrix_storage() : _shp(hermitian,0,0), nref(this){}

    matrix_storage( matrix_shape shp) : _shp(shp), nref(this)
    {
      _vals = NULL;
      resize(shp);
    }

    matrix_storage( matrix_storage<VALTYPE,hermitian> &s) : _shp(s._shp), nref(this)
    {
      _shp = s._shp;
      _memsize = s._memsize;
      _vals = new VALTYPE [_memsize];

      copy(s);
      // std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void resize(matrix_shape shp)
    {
      _shp = shp;
      assert( _shp.mtype == hermitian && 
	      "Incosistent matrix type in matrix_storage<VALTYPE,hermitian> constructor" );
      assert( _shp.n == _shp.m && "Attempt to create hermitian matrix with N != M " );
      _memsize = _shp.n*(_shp.n+1)/2;

      if (_vals != NULL) delete _vals;
      _vals = new VALTYPE [_memsize];
    }

    // Unary BLAS operations:

    inline void copy( matrix_storage<VALTYPE,hermitian> &s)
    {
      std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void scale(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] *= s;
    }

    inline void setval(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] = s;
    }
  
    // Access operator & function

    inline typename _hermitian_element<VALTYPE>::type  operator()(int i, int j)
    {
      //      typename _hermitian_element<VALTYPE>::type *ref;      
      if ( j >= i )
	return _hermitian_element<VALTYPE>::newelem( _vals[ j*(j+1)/2 + i ], true);
      else
	return _hermitian_element<VALTYPE>::newelem( _vals[ i*(i+1)/2 + j ], false);
    }

    inline VALTYPE* ptr(int i, int j)
    {
      return unique(i,j) ? &_vals[ i*(i+1)/2 + j ] : NULL;
    }

    matrix_shape shape()
    {
      return _shp;
    }

    inline int size(int dim)
    {
      assert( (dim==0 || dim==1) && "Illegal dimension" );    
      return _shp.n;
    }

    inline bool defined(int i, int j)
    { return true;}

    inline bool unique(int i, int j)
    { return j<=i;}

    ~matrix_storage()
    {
      if (_memsize > 0)
	delete _vals;
    }

  };


  //---------------------------------------------------//
  //              Band diagonal matrix                 //
  //---------------------------------------------------//

  // All the methods have the same meaning as for 
  // matrix_storage<VALTYPE,rectang>, only
  // implementation differs.
  // See the comments to matrix_storage<VALTYPE,rectang>

  template<class VALTYPE>
  class matrix_storage<VALTYPE,banddiag>
  {
  protected:

    VALTYPE *_vals;
    matrix_shape _shp;
    int _memsize;

    VALTYPE zero;

    friend class _lace_expressions::matrix<VALTYPE,banddiag>;

    //    typedef _complex_reference<VALTYPE> _element;
  public:

    refcounter<matrix_storage<VALTYPE,banddiag> > nref;

    matrix_storage() : _shp(banddiag,0,0,0,0), nref(this){}

    matrix_storage( matrix_shape shp) : _shp(shp), nref(this)
    {
      _vals = NULL;
      resize(shp);
    }

    matrix_storage( matrix_storage<VALTYPE,banddiag> &s) : _shp(s._shp), nref(this)
    {
      _shp = s._shp;
      _memsize = s._memsize;
      _vals = new VALTYPE [_memsize];

      copy(s);
      // std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void resize(matrix_shape shp)
    {
//       _shp = shp;
//       assert( _shp.mtype == banddiag && 
// 	      "Incosistent matrix type in matrix_storage<VALTYPE,triang> constructor" );
//       assert( _shp.n == _shp.m && "Attempt to create triangular matrix with N != M " );
//       _memsize = _shp.n*(_shp.n+1)/2;

//       if (_vals != NULL) delete _vals;
//       _vals = new VALTYPE [_memsize];
    }

    // Unary BLAS operations:

    inline void copy( matrix_storage<VALTYPE,banddiag> &s)
    {
      std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void scale(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] *= s;
    }

    inline void setval(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] = s;
    }
  
    // Access operator & function

    inline VALTYPE & operator()(int i, int j)
    {
    }

    inline VALTYPE* ptr(int i, int j)
    {
    }

    matrix_shape shape()
    {
      return _shp;
    }

    inline int size(int dim)
    {
      assert( (dim==0 || dim==1) && "Illegal dimension" );    
      return _shp.n;
    }

    inline bool defined(int i, int j)
    { 
    }

    inline bool unique(int i, int j)
    { 
    }

    ~matrix_storage()
    {
      if (_memsize > 0)
	delete _vals;
    }

  };

  //---------------------------------------------------//
  //              Band symmetric matrix                //
  //---------------------------------------------------//

  // All the methods have the same meaning as for 
  // matrix_storage<VALTYPE,rectang>, only
  // implementation differs.
  // See the comments to matrix_storage<VALTYPE,rectang>

  template<class VALTYPE>
  class matrix_storage<VALTYPE,symmband>
  {
  protected:

    VALTYPE *_vals;
    matrix_shape _shp;
    int _memsize;

    VALTYPE zero;

    friend class _lace_expressions::matrix<VALTYPE,symmband>;

    //    typedef _complex_reference<VALTYPE> _element;
  public:

    refcounter<matrix_storage<VALTYPE,symmband> > nref;

    matrix_storage() : _shp(symmband,0,0,0,0), nref(this){}

    matrix_storage( matrix_shape shp) : _shp(shp), nref(this)
    {
      _vals = NULL;
      resize(shp);
    }

    matrix_storage( matrix_storage<VALTYPE,symmband> &s) : _shp(s._shp), nref(this)
    {
      _shp = s._shp;
      _memsize = s._memsize;
      _vals = new VALTYPE [_memsize];

      copy(s);
      // std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void resize(matrix_shape shp)
    {
//       _shp = shp;
//       assert( _shp.mtype == banddiag && 
// 	      "Incosistent matrix type in matrix_storage<VALTYPE,triang> constructor" );
//       assert( _shp.n == _shp.m && "Attempt to create triangular matrix with N != M " );
//       _memsize = _shp.n*(_shp.n+1)/2;

//       if (_vals != NULL) delete _vals;
//       _vals = new VALTYPE [_memsize];
    }

    // Unary BLAS operations:

    inline void copy( matrix_storage<VALTYPE,symmband> &s)
    {
      std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void scale(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] *= s;
    }

    inline void setval(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] = s;
    }
  
    // Access operator & function

    inline VALTYPE & operator()(int i, int j)
    {
    }

    inline VALTYPE* ptr(int i, int j)
    {
    }

    matrix_shape shape()
    {
      return _shp;
    }

    inline int size(int dim)
    {
      assert( (dim==0 || dim==1) && "Illegal dimension" );    
      return _shp.n;
    }

    inline bool defined(int i, int j)
    { 
    }

    inline bool unique(int i, int j)
    { 
    }

    ~matrix_storage()
    {
      if (_memsize > 0)
	delete _vals;
    }

  };

  //---------------------------------------------------//
  //              Band hermitian matrix                //
  //---------------------------------------------------//

  // All the methods have the same meaning as for 
  // matrix_storage<VALTYPE,rectang>, only
  // implementation differs.
  // See the comments to matrix_storage<VALTYPE,rectang>

  template<class VALTYPE>
  class matrix_storage<VALTYPE,hermband>
  {
  protected:

    VALTYPE *_vals;
    matrix_shape _shp;
    int _memsize;

    VALTYPE zero;

    friend class _lace_expressions::matrix<VALTYPE,hermband>;

    //    typedef _complex_reference<VALTYPE> _element;
  public:

    refcounter<matrix_storage<VALTYPE,hermband> > nref;

    matrix_storage() : _shp(hermband,0,0,0,0), nref(this){}

    matrix_storage( matrix_shape shp) : _shp(shp), nref(this)
    {
      _vals = NULL;
      resize(shp);
    }

    matrix_storage( matrix_storage<VALTYPE,hermband> &s) : _shp(s._shp), nref(this)
    {
      _shp = s._shp;
      _memsize = s._memsize;
      _vals = new VALTYPE [_memsize];

      copy(s);
      // std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void resize(matrix_shape shp)
    {
//       _shp = shp;
//       assert( _shp.mtype == hermband && 
// 	      "Incosistent matrix type in matrix_storage<VALTYPE,triang> constructor" );
//       assert( _shp.n == _shp.m && "Attempt to create triangular matrix with N != M " );
//       _memsize = _shp.n*(_shp.n+1)/2;

//       if (_vals != NULL) delete _vals;
//       _vals = new VALTYPE [_memsize];
    }

    // Unary BLAS operations:

    inline void copy( matrix_storage<VALTYPE,hermband> &s)
    {
      std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void scale(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] *= s;
    }

    inline void setval(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] = s;
    }
  
    // Access operator & function

    inline VALTYPE & operator()(int i, int j)
    {
    }

    inline VALTYPE* ptr(int i, int j)
    {
    }

    matrix_shape shape()
    {
      return _shp;
    }

    inline int size(int dim)
    {
      assert( (dim==0 || dim==1) && "Illegal dimension" );    
      return _shp.n;
    }

    inline bool defined(int i, int j)
    { 
    }

    inline bool unique(int i, int j)
    { 
    }

    ~matrix_storage()
    {
      if (_memsize > 0)
	delete _vals;
    }

  };

  //---------------------------------------------------//
  //                 Triangular matrix                 //
  //---------------------------------------------------//

  // The storage is organized exactly the same way, as for
  // symmetric matrix. The only difference is the behaviour
  // of matrix elements, which is implemented in matrix.hpp


  template<class VALTYPE>
  class matrix_storage<VALTYPE,triang>
  {
  protected:

    VALTYPE *_vals;
    matrix_shape _shp;
    int _memsize;

    VALTYPE zero;

    friend class _lace_expressions::matrix<VALTYPE,triang>;

    //    typedef _complex_reference<VALTYPE> _element;
  public:

    refcounter<matrix_storage<VALTYPE,triang> > nref;

    matrix_storage() : _shp(triang,0,0,matrix_shape::upper), nref(this){}

    matrix_storage( matrix_shape shp) : _shp(shp), nref(this)
    {
      _vals = NULL;
      resize(shp);
    }

    matrix_storage( matrix_storage<VALTYPE,triang> &s) : _shp(s._shp), nref(this)
    {
      _shp = s._shp;
      _memsize = s._memsize;
      _vals = new VALTYPE [_memsize];

      copy(s);
      // std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void resize(matrix_shape shp)
    {
      _shp = shp;
      assert( _shp.mtype == triang && 
	      "Incosistent matrix type in matrix_storage<VALTYPE,triang> constructor" );
      assert( _shp.n == _shp.m && "Attempt to create triangular matrix with N != M " );
      _memsize = _shp.n*(_shp.n+1)/2;

      if (_vals != NULL) delete _vals;
      _vals = new VALTYPE [_memsize];
    }

    // Unary BLAS operations:

    inline void copy( matrix_storage<VALTYPE,triang> &s)
    {
      std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
    }

    inline void scale(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] *= s;
    }

    inline void setval(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _memsize; i++)
	_vals[i] = s;
    }
  
    // Access operator & function

    inline VALTYPE & operator()(int i, int j)
    {
      //      typename _hermitian_element<VALTYPE>::type *ref;      
      if ( _shp.tag == matrix_shape::upper && i<=j )
	{
	  return _vals[j*(j+1)/2 + i];
	}
      else if ( _shp.tag == matrix_shape::lower && i>=j )
	{
	  return _vals[_shp.n*j - j*(j+1)/2 + i];
	}
      else
	{
	  zero = VALTYPE(0);
	  return  zero;
	}
    }

    inline VALTYPE* ptr(int i, int j)
    {
      if ( _shp.tag == matrix_shape::upper && i<=j )
	{
	  return &_vals[j*(j+1)/2 + i];
	}
      else if ( _shp.tag == matrix_shape::lower && i>=j )
	{
	  return &_vals[_shp.n*j - j*(j+1)/2 + i];
	}
      else
	return NULL;
    }

    matrix_shape shape()
    {
      return _shp;
    }

    inline int size(int dim)
    {
      assert( (dim==0 || dim==1) && "Illegal dimension" );    
      return _shp.n;
    }

    inline bool defined(int i, int j)
    { 
      return 
	(_shp.tag == matrix_shape::upper && i<=j) || 
	(_shp.tag == matrix_shape::lower && i>=j);
    }

    inline bool unique(int i, int j)
    { 
      return defined(i,j);
    }

    ~matrix_storage()
    {
      if (_memsize > 0)
	delete _vals;
    }

  };

  //---------------------------------------------------//
  //                   Non matrix                      //
  //---------------------------------------------------//

  // This is a storage for object which is not matrix
  // Consequently, this storage does nothing and contains
  // no matrix elements
  // The usage of such object is protomatrix (see engine.hpp)


  template<class VALTYPE>
  class matrix_storage<VALTYPE,nonmatrix>

  //
  // fixme - complete the implementation of banddiag
  {

    friend class _lace_expressions::matrix<VALTYPE,nonmatrix>;

  public:

    refcounter<matrix_storage<VALTYPE,nonmatrix> > nref;

    matrix_storage() : nref(this){}

    matrix_storage( matrix_shape shp) :  nref(this)
    {
      assert( shp.mtype == nonmatrix && 
	      "Incosistent matrix type in matrix_storage<VALTYPE,nonmatrix> constructor" );
    }

//     matrix_storage( matrix_storage<VALTYPE,banddiag> &s) : _shp(s._shp), nref(this)
//     {
//       //    _memsize = s._memsize;
//       //    _vals = new VALTYPE [_memsize];

//       //    std::memcpy(_vals, s._vals, _memsize*sizeof(VALTYPE) );
//     }

    matrix_shape shape(){return empty_shape();}

    inline int size(int dim)
    {
      return -1;
    }

    inline VALTYPE & operator()(int i, int j)
    {
      assert(false && "Matrix element of nonmatrix called");
    }

    inline bool defined(int i, int j)
    { return false;}

    inline bool unique(int i, int j)
    { return false;}

  };


  // fixme -- implement symmband,hermband and triang

  /* --------------------------------------------------------- *
   *                                                           *
   *                 Vector storage classes                    *
   *                                                           *
   * --------------------------------------------------------- */

  template<class VALTYPE, vector_type VTYPE>
  class vector_storage;

  //---------------------------------------------------//
  //                    Dense vector                   //
  //---------------------------------------------------//

  template<class VALTYPE>
  class vector_storage<VALTYPE,dense>{

    VALTYPE *_vals;
    vector_shape _shp;

    friend class _lace_expressions::vector<VALTYPE,dense>;

  public:
    refcounter<vector_storage<VALTYPE,dense> > nref;

    //    empty constructor
    vector_storage() : _shp(dense,0), nref(this) 
    { _vals = NULL; }

    // use shape to construct vector
    vector_storage( vector_shape shp) : _shp(shp) , nref(this) 
    {
      _vals = NULL;
      resize(shp);
    }

    // Copy constructor
    vector_storage( vector_storage<VALTYPE,dense> &s) : _shp(s._shp), nref(this) 
    {
      _vals = new VALTYPE [_shp.size()];
    
      copy(s);
    };

    // Resize matrix assuming new shape. The current matrix is lost
    inline void resize(vector_shape shp)
    {
      _shp = shp;
      assert( _shp.vtype == dense && 
	      "Incosistent vector type in vector_storage<VALTYPE,dense> constructor" );

      if (_vals != NULL ) delete _vals;
      _vals = new VALTYPE [_shp.size()];
    }

    // Copy the the contents of s into this object
    inline void copy( vector_storage<VALTYPE,dense> &s )
    {
      std::memcpy(_vals, s._vals, _shp.size()*sizeof(VALTYPE) );
    }

    // Scale all matrix elements by value s
    inline void scale(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _shp.size(); i++)
	_vals[i] *= s;
    }
  
    inline void setval(VALTYPE s)
    {
      // fixme -- to be replaced with BLAS call (dscal,cscal,sscal,zscal)
      for (int i = 0; i < _shp.size(); i++)
	_vals[i] = s;
    }

    // The access operator
    inline VALTYPE & operator()(int i)
    {
      return _vals[ i ];
    }

    inline VALTYPE * ptr(int i)
    {
      return _vals + i;
    }

    // Returns the matrix shape
    vector_shape& shape()
    {
      return * new vector_shape(_shp);
    }

    inline int size()
    {
      return _shp.size();
    }

    //fixme - not sure if this will be necessary
    inline bool defined(int i)
    { return true;}

    inline bool unique(int i)
    { return true;}

    ~vector_storage()
    {
      if (_shp.size() > 0)
	delete _vals;
    }

  };

  //---------------------------------------------------//
  //                    Non vector                     //
  //---------------------------------------------------//

  template<class VALTYPE>
  class vector_storage<VALTYPE,nonvector>{

    friend class _lace_expressions::vector<VALTYPE,nonvector>;

  public:
    refcounter<vector_storage<VALTYPE,nonvector> > nref;

    //    empty constructor
    vector_storage() : nref(this){}

    // use shape to construct vector
    vector_storage( vector_shape shp) : nref(this){}

    // Copy constructor
    vector_storage( vector_storage<VALTYPE,nonvector> &s) : nref(this){}

    // Resize matrix assuming new shape. The current matrix is lost
    inline void resize(vector_shape shp)
    {}

    // Copy the the contents of s into this object
    inline void copy( vector_storage<VALTYPE,nonvector> &s )
    {}

    // Scale all matrix elements by value s
    inline void scale(VALTYPE s)
    {}
  
    inline void setval(VALTYPE s)
    {}

    // The access operator
    inline VALTYPE & operator()(int i)
    {}

    inline VALTYPE * ptr(int i)
    {}

    // Returns the matrix shape
    vector_shape shape()
    {
      return * new vector_shape();
    }

    inline int size()
    {
      return 0;
    }

    //fixme - not sure if this will be necessary
//     inline bool defined(int i)
//     { return true;}

//     inline bool unique(int i)
//     { return true;}

    ~vector_storage()
    {}

  };

};

#endif
