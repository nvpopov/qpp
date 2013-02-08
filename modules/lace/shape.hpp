#ifndef _LACE_SHAPE_H
#define _LACE_SHAPE_H

#include<string>
#include<cassert>
#include<iostream>

namespace _lace_storage{

  //---------------------------------------------//
  //                Matrix types                 //
  //---------------------------------------------//
  
  enum matrix_type{
    rectang,    
    symmetric,  
    hermitian,  
    banddiag,   
    symmband,   
    hermband,   
    triang,
    nonmatrix
  };
  
  const std::string mtype_spelling [] = {"rectangular",
					 "symmetric",
					 "hermitian",
					 "banddiag",
					 "symmetric band",
					 "hermitian band",
					 "triangular",
					 "nonmatrix"};
  
  const int n_matrix_type = 7;
  
  //---------------------------------------------//
  //                Matrix shape                 //
  //---------------------------------------------//
  
  /* This object should store all information about
   * matrix storage form -- knowing matrix_shape
   * should be sufficient to create a new matrix
   * of this shape
   */
  
  struct matrix_shape{
    matrix_type mtype;
    
    /* n - number of raws
     * m - number of columns */
    int n, m; 

    /* ku - number of subdiags
     * kl - number of superdiags */
    int ku, kl;

    /* The enum type matrix_shape::uplo is used for
     * specifying upper/lower triangular matrix  */
    
    enum uplo {
      upper,
      lower
    };

    uplo tag;

    matrix_shape()
    {
      m=-1; n=-1; mtype=nonmatrix;
    }

    matrix_shape(matrix_type _mtype, int _n, int _m)
    { 
      mtype = _mtype;
      n = _n; 
      if (_m==-1) _m = _n;
      m = _m; 
    }
    
    matrix_shape(matrix_type _mtype, int _n, int _m, int _ku, int _kl)
    {
      assert( (mtype==banddiag || mtype==symmband || mtype==hermband) && 
	      "Banded matrix initialization with non-banded matrix type" );
      
      mtype = _mtype;
      n = _n; 
      if (_m==-1) _m = _n;
      m = _m; 

      if(_kl==-1) _kl = _ku;
      if (mtype==symmband || mtype==hermband)
	assert( _ku == _kl && "Symmetric or hermitian band matrix must have equal number of upper and lower subiags" );
      ku = _ku;
      kl = _kl;
    }  

    matrix_shape(matrix_type _mtype, int _n, uplo _tag)
    {
      assert( _mtype==triang && "Triangular matrix initialization with non-triangular matrix type" );

      mtype = _mtype;
      n = _n; 
      //if (_m==-1) _m = _n;
      m = _n; 

      tag = _tag;
    }

    ~matrix_shape(){}

    inline int size(int dim)
    {
      if (dim == 0)
	return n;
      else if (dim == 1)
	return m;
      else
	assert( false && "Illegal dimension" );
    }   

    bool operator==(matrix_shape shp)
    {
      bool result = (mtype == shp.mtype);
      if (result)
	result = (n == shp.n && m == shp.m);
      if ( result && mtype == triang )
	result = ( tag == shp.tag );
      if ( result && ( mtype == banddiag || mtype == symmband || mtype == hermband ))
	result = ( kl == shp.kl && ku == shp.ku );
      return result;
    }
    
    virtual void debug() 
    { 
      std::cout << "Shape " << mtype_spelling[mtype] << " dims: " << n << " x " << m << "\n"; 
    } 
    
  };  

  // Convertability check

  const bool conver_table[n_matrix_type][n_matrix_type] = 
    {
    // rectang  symmetric  hermitian  banddiag  symmband  hermband triang
      { true,     true,     true,      true,     true,     true,     true },  // rectang   
      { false,    true,     false,     false,    true,     false,    false},  // symmetric  
      { false,    false,    true,      false,    false,    true,     false},  // hermitian
      { false,    false,    false,     true,     true,     true,     false},  // banddiag   
      { false,    false,    false,     false,    true,     false,    false},  // symmband   
      { false,    false,    false,     false,    false,    true,     false},  // hermband
      { false,    false,    false,     false,    false,    false,    true }   // triang
    };

  inline bool is_convertable(matrix_type dest, matrix_type src)
  {
    return conver_table[dest][src];
  }

  //----------------------- Service functions ---------------------------

  inline matrix_shape empty_shape()
  {
    return matrix_shape();
  }

  inline bool is_empty(matrix_shape shp)
  {
    return shp.n <= 0 || shp.m <= 0;
  }
  
  inline bool is_banded(matrix_type mtype)
  {
    return ( mtype == banddiag || mtype == symmband || mtype == hermband);
  }

  inline bool is_symmetric(matrix_type mtype)
  {
    return ( mtype == symmetric || mtype == symmband );
  }

  inline bool is_hermitian(matrix_type mtype)
  {
    return ( mtype == hermitian || mtype == hermband );
  }

  //---------------------------------------------//
  //                Vector types                 //
  //---------------------------------------------//
  
  enum vector_type{
    dense,
    sparse,
    nonvector
  };

  const int n_vector_type = 2;

  const std::string vtype_spelling [] = { "Dense", "Sparse" };

  //---------------------------------------------//
  //                Vector shape                 //
  //---------------------------------------------//
  
  struct vector_shape{
    vector_type vtype;

    // The size of vector
    int n;

    vector_shape()
    {
      vtype = nonvector;
      n = -1;
    }

    vector_shape(vector_type _vtype, int _n){
      vtype = _vtype;
      n = _n;
    }

    inline int size()
    {
      return n;
    }    

    inline bool operator==(vector_shape shp)
    {
      return  vtype == shp.vtype && n == shp.n;
    }
  
    virtual void debug() 
    { 
      std::cout << "Vector shape " << vtype_spelling[vtype] << " dim: " << " x " << n << "\n"; 
    } 
  };

  inline bool is_empty(vector_shape shp)
  {
    return shp.n <= 0;
  }


//   vector_shape empty_shape()
//   {
//     return vector_shape();
//   }
  

};

namespace _lace_expressions{

  using _lace_storage::matrix_type;
  using _lace_storage::vector_type;

  // Forward declaration of vector and matrix main objects

//   template<class VALTYPE>
//   class matrix_object;

//   template<class VALTYPE> 
//   class vector_object;

  template<class VALTYPE, matrix_type MTRTYPE>
  class matrix;

  template<class VALTYPE, vector_type VECTYPE> 
  class vector;

};

#endif

