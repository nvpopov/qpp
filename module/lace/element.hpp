#ifndef _LACE_ELEMENT_H
#define _LACE_ELEMENT_H

#include <lace/complex.hpp>
#include <lace/shape.hpp>

namespace _lace_storage{


  template <typename VALTYPE>
  struct _hermitian_element;

  // Special wrapper for complex to implement matrix elements of hermitian matrix
  template<class COMPLEX>
  class _complex_reference{
    COMPLEX *ref;
    bool conjugate;
    
    friend class _hermitian_element<COMPLEX>;

    _complex_reference(COMPLEX &a, bool conj = false)
    {
      ref = &a;
      conjugate = conj;
      //      nwrappers++;
    }
    
  public:
    // for debug purpose
    static int nwrappers;

    inline operator COMPLEX()
    {
      COMPLEX res;
      if (conjugate)
	res =  lace::conj(*ref);
      else
	res = *ref;
      //      delete this;
      return res;
    }
    
    inline COMPLEX operator=(COMPLEX a)
    {
      if (conjugate)
	*ref = lace::conj(a);
      else
	*ref = a;
      //      delete this;
      return a;
    }

    inline COMPLEX operator+=(COMPLEX a)
    {
      if (conjugate)
	{
	  *ref += lace::conj(a);
	  return lace::conj(*ref);
	}
      else
	{
	*ref += a;
	return *ref;      
	}
    }

    //debug
    ~_complex_reference(){}
    //    { nwrappers--; std::cout << " del "; }
    
  };

  //debug
  template<class COMPLEX>
  int _complex_reference<COMPLEX>::nwrappers = 0;

  // ------------------------------------------------------------------

  template<typename VALTYPE,matrix_type MTRTYPE>
  struct _element;

  template<typename VALTYPE,matrix_type MTRTYPE>
  class matrix_storage;

  template <typename VALTYPE>
  struct _hermitian_element{

    typedef VALTYPE& type;
    
    static inline type newelem(VALTYPE &x, bool)
    {
      return x;
    }
    
  };
  
  template <>
  struct _hermitian_element<lace::fcomplex>
  {
    typedef _complex_reference<lace::fcomplex> type;
    
  private:
    friend class  _element<lace::fcomplex,hermitian>;
    friend class  _element<lace::fcomplex,hermband>;
    friend class  matrix_storage<lace::fcomplex,hermitian>;
    friend class  matrix_storage<lace::fcomplex,hermband>;

    static inline type newelem(lace::fcomplex &x, bool c)
    {
      return type(x,c);
    }

  };

  template <>
  struct _hermitian_element<lace::dcomplex>
  {
    typedef _complex_reference<lace::dcomplex> type;
    
  private:
    friend class _element<lace::dcomplex,hermitian>;
    friend class _element<lace::dcomplex,hermband>;
    friend class  matrix_storage<lace::dcomplex,hermitian>;
    friend class  matrix_storage<lace::dcomplex,hermband>;

    static inline type newelem(lace::dcomplex &x, bool c)
    {
      return type(x,c);
    }

  };

  // ------------------------------------------------------------------
  
  template<typename VALTYPE,matrix_type MTRTYPE>
  struct _element{
    typedef VALTYPE& type;    

    static inline type newelem(VALTYPE &x, bool)
    {
      return x;
    }
  };

  template<typename VALTYPE>
  struct _element<VALTYPE,hermitian>{
    typedef typename _hermitian_element<VALTYPE>::type type;

  private:
    friend class matrix_storage<VALTYPE,hermitian>;

    static inline type newelem(VALTYPE &x, bool c)
    {
      return _hermitian_element<VALTYPE>::newelem(x,c);
    }    
  };

  template<typename VALTYPE>
  struct _element<VALTYPE,hermband>{
    typedef typename _hermitian_element<VALTYPE>::type type;

  private:
    friend class matrix_storage<VALTYPE,hermband>;
    
    static inline type newelem(VALTYPE &x, bool c)
    {
      return _hermitian_element<VALTYPE>::newelem(x,c);
    }    
  };
  
};

#endif 

