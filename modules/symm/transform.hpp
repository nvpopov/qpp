#ifndef _QPP_TRANSFORM_H
#define _QPP_TRANSFORM_H

#include <geom/lace3d.hpp>
//#include <geom/cell.hpp>
#include <consts.hpp>
#include <vector>

#ifdef PY_EXPORT
#include <boost/python.hpp>
namespace bp = boost::python;
namespace sn = boost::python::self_ns;
#endif


namespace qpp{

  // ----------------------------------------------------------------

  template<class REAL>
  struct rotrans
  {
    //typedef typename BOUNDARY::real real;
    
    static REAL translation_tolerance,rotation_tolerance;
    static rotrans<REAL> unity;
    
    vector3d<REAL> T;
    matrix3d<REAL> R;

    //BOUNDARY * cell;
    
    rotrans()
    {
      T = REAL(0);
      R = REAL(1);
    }

    rotrans(const rotrans<REAL> & a)
    {
      T = a.T;
      R = a.R;

      //      cell = a.cell;
    }
    
    rotrans(const vector3d<REAL> &_T)
    {
      T=_T;
      R = REAL(1);
      //      cell = NULL;
    }
    
    rotrans(const matrix3d<REAL> & _R)
    {
      T = REAL(0);
      R = _R;
      //cell = NULL;
    }
    
    rotrans(const vector3d<REAL> &_T, const matrix3d<REAL> &_R)//, BOUNDARY * _cell = NULL)
    {
      T = _T;
      R = _R;
      //cell = _cell;
    }
    
    inline rotrans<REAL> operator*(const rotrans<REAL> & b) const
    {
      vector3d<REAL> t = T + R*b.T;
      //if (cell!=NULL)
      //t = cell->reduce(t);
      return rotrans<REAL>(t, R*b.R);
    }

    inline bool operator==(const rotrans<REAL> & b) const
    {
      return norm(T - b.T) <= translation_tolerance && norm(R - b.R) <= rotation_tolerance;
    }

    inline bool operator!=(const rotrans<REAL> & b) const
    {
      return norm(T - b.T) > translation_tolerance || norm(R - b.R) > rotation_tolerance;
    }

    inline vector3d<REAL> operator*(const vector3d<REAL> & v) const
    {						
      vector3d<REAL> res = T+R*v; 
      //if (cell!=NULL)
      //res = cell -> reduce(res);
      return res;
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int k=0; k<offset; k++) os << " ";
      os << "rotrans(" << T << "," << R << ")";
    }


#ifdef PY_EXPORT

    inline vector3d<REAL> py_mulv(const vector3d<REAL> & v) const {return (*this)*v; }
    inline rotrans<REAL> py_mulr(const rotrans<REAL> & b) const {return (*this)*b; }

#endif

  };

  template<typename _CharT, class _Traits, class VALTYPE>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& __os, const rotrans<VALTYPE> & r)
  {
    r.write(__os);
    return __os;
  }


  template<class REAL>
  REAL rotrans<REAL>::translation_tolerance = 1e-10;
  
  template<class REAL>
  REAL rotrans<REAL>::rotation_tolerance = 1e-10;
  
  template<class REAL>
  rotrans<REAL> rotrans<REAL>::unity(vector3d<REAL>(0e0),matrix3d<REAL>(1e0));
				      
  template<class REAL>
  rotrans<REAL> invert(const rotrans<REAL> & R)
  {
    matrix3d<REAL> A = invert(R.R);
    vector3d<REAL> t = - A*R.T;
    return rotrans<REAL>(t, A);
  }
  
  template<class REAL>
  rotrans<REAL> pow(const rotrans<REAL> & R, int n)
  {
    // fixme - very inefficient
    rotrans<REAL> A =  rotrans<REAL>::unity;
    if (n>0)
      {
	while (n-- > 0)
	  A = R*A;
      }
    else if (n<0)
      {
	rotrans<REAL>  B = invert(R);
	while (n++ < 0)
	  A = B*A;
      }
    return A;
  }

  // ----------------------------------------------------------------
#ifdef PY_EXPORT

  template<class REAL>
  inline rotrans<REAL> py_invert_rt(const rotrans<REAL> & R) {return invert(R);}
  
  template<class REAL>
  inline rotrans<REAL> py_pow_rt(const rotrans<REAL> & R, int n) {return pow(R,n);}

#endif

  // ----------------------------------------------------------------
  
  template<class REAL>
  struct translation
  {
    //typedef typename BOUNDARY::real real;
    static REAL translation_tolerance;

    static translation<REAL> unity;
    
    vector3d<REAL> T;
    
    translation()
    { T = 0e0; }

    translation( const translation<REAL> & a)
    {
      T = a.T;
    }

    translation(const vector3d<REAL> & t)
    {
      T = t;
    }
    
    inline translation<REAL> operator*(const translation<REAL> & b) const
    {
      vector3d<REAL> res = T+b.T; 
      return translation<REAL>(res);
    }

    inline bool operator==(const translation<REAL> & b) const
    {
      return norm(T - b.T) <= translation_tolerance;
    }

    inline bool operator!=(const translation<REAL> & b) const
    {
      return norm(T - b.T) > translation_tolerance;
    }

    inline vector3d<REAL> operator*(const vector3d<REAL> & v) const
    {
      vector3d<REAL> res = T+v; 
      return res;
    }

    inline operator vector3d<REAL>() const
    {
      return T;
    }

  };
  
  template<class REAL>
  REAL translation<REAL>::translation_tolerance = 1e-10;
  
  template<class REAL>
  translation<REAL>  translation<REAL>::unity(vector3d<REAL>(0e0));

  template<class REAL>
  translation<REAL> invert(const translation<REAL> & R)
  {
    return translation<REAL>(-R.T);
  }

  template<class REAL>
  translation<REAL> pow(const translation<REAL> & R, int n)
  {
    return translation<REAL>(R.T*n);
  }

};

#endif
