#ifndef _LACE_COMPLEX_H
#define _LACE_COMPLEX_H

#include <cmath>
#include <sstream>

namespace lace{

  class fcomplex;

  class dcomplex;

  class lcomplex;

};

// --- Dumb template ---
// 
// Why not using templates for that?
// Doing this instead of defining complex<REALTYPE> seems to be really nasty, doesn't it?
//
// The reason is the ability to use implicit typecast for complex numbers, which doesn't
// work correctly when complex is defined with templates.

typedef long double longdouble;

#define REAL longdouble
#define complex lcomplex
#define altcomplex1 fcomplex
#define altcomplex2 dcomplex

#include <lace/complex_repeater.hpp>

#undef REAL
#undef complex
#undef altcomplex1
#undef altcomplex2


#define REAL double
#define complex dcomplex
#define altcomplex1 fcomplex
#define altcomplex2 lcomplex

#include <lace/complex_repeater.hpp>

#undef REAL
#undef complex
#undef altcomplex1
#undef altcomplex2


#define REAL float
#define complex fcomplex
#define altcomplex1 dcomplex
#define altcomplex2 lcomplex

#include <lace/complex_repeater.hpp>

#undef REAL
#undef complex
#undef altcomplex1
#undef altcomplex2

namespace lace{

  // The typecast constructors -- no templates here!!!
  // Just these six - and no more.

//   lcomplex::lcomplex( fcomplex z)
//   {
//     _re = z.re(); _im = z.im();
//   }

//   lcomplex::lcomplex( dcomplex z)
//   {
//     _re = z.re(); _im = z.im();
//   }

//   dcomplex::dcomplex( fcomplex z)
//   {
//     _re = z.re(); _im = z.im();
//   }

//   dcomplex::dcomplex( lcomplex z)
//   {
//     _re = z.re(); _im = z.im();
//   }

//   fcomplex::fcomplex( dcomplex z)
//   {
//     _re = z.re(); _im = z.im();
//   }

//   fcomplex::fcomplex( lcomplex z)
//   {
//     _re = z.re(); _im = z.im();
//   }

  inline float abs(float x)
  {
    return x<0 ? -x : x;
  }

  inline double abs(double x)
  {
    return x<0 ? -x : x;
  }

  inline long double abs(long double x)
  {
    return x<0 ? -x : x;
  }

  inline float conj(float x)
  { return x; }

  inline double conj(double x)
  { return x; }

  inline long double conj(long double x)
  { return x; }

  inline float real(float x)
  { return x; }

  inline double real(double x)
  { return x; }

  inline long double real(long double x)
  { return x; }


  template<typename VALTYPE>
  struct numeric_type;

  template<>
  struct numeric_type<float>
  {
    typedef float real;
    static bool is_real(){return true;}
    static bool is_complex(){return false;}
    static float I(){return float(0);}
  };

  template<>
  struct numeric_type<double>
  {
    typedef double real;
    static bool is_real(){return true;}
    static bool is_complex(){return false;}
    static double I(){return double(0);}
  };

  template<>
  struct numeric_type<longdouble>
  {
    typedef long double real;
    static bool is_real(){return true;}
    static bool is_complex(){return false;}
    static long double I(){return (long double)(0);}
  };

  template<>
  struct numeric_type<fcomplex>
  {
    typedef float real;
    static bool is_real(){return false;}
    static bool is_complex(){return true;}
    static fcomplex I(){return fcomplex(0,1);}
  };

  template<>
  struct numeric_type<dcomplex>
  {
    typedef double real;
    static bool is_real(){return false;}
    static bool is_complex(){return true;}
    static dcomplex I(){return dcomplex(0,1);}
  };

  template<>
  struct numeric_type<lcomplex>
  {
    typedef long double real;
    static bool is_real(){return false;}
    static bool is_complex(){return true;}
    static lcomplex I(){return lcomplex(0,1);}
  };

};

#endif
