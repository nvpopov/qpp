#ifndef _LACE3D_H
#define _LACE3D_H

#include <cmath>
#include <complex>
#include <ostream>
#include <sstream>
#include <initializer_list>

#include <data/types.hpp>
#include <consts.hpp>
//#include <lace/complex.hpp>

#ifdef PY_EXPORT
#include <boost/python/list.hpp>
#include <boost/python.hpp>
#endif

namespace qpp{


  template <class VALTYPE, int DIM>
  class simple_vector{
  protected:
    VALTYPE r[DIM];
    //friend void py_vector3d_export<VALTYPE>(const char * pyname);

  public:

    simple_vector(){};

    simple_vector(VALTYPE s)
    {
      for(int i=0; i<DIM; i++)
	r[i] = s;
    }

    simple_vector(const simple_vector<VALTYPE,DIM> & v)
    {
      for(int i=0; i<DIM; i++)
	r[i] = v.r[i];
    }

    simple_vector(const std::initializer_list<VALTYPE> & li)
    {
      if (li.size() != DIM)
	throw std::range_error("Wrong number of vector components");
      int d=0;
      for (int x : li)
	r[d++] = x;
    }

    inline VALTYPE& operator()(int i)
    {
      return r[i];
    }

    inline VALTYPE& operator[](int i)
    {
      return r[i];
    }

    inline VALTYPE operator()(int i) const
    {
      return r[i];
    }

    inline typename numeric_type<VALTYPE>::norm norm2() const
    {
      VALTYPE s=0e0;
      for (int i=0; i<DIM; i++)
	s+=std::conj(r[i])*r[i];
      return std::abs(s);
    }

    inline typename numeric_type<VALTYPE>::norm norm() const
    {return std::sqrt(norm2());}

    inline simple_vector<VALTYPE,DIM> operator+(const simple_vector<VALTYPE,DIM> & v) const
    {
      simple_vector<VALTYPE,DIM> res(0e0);
      for (int i=0; i<DIM; i++)
	res.r[i] = r[i] + v.r[i];
      return res;
    }

    inline simple_vector<VALTYPE,DIM> operator-(const simple_vector<VALTYPE,DIM> & v) const
    {
      simple_vector<VALTYPE,DIM> res(0e0);
      for (int i=0; i<DIM; i++)
	res.r[i] = r[i] - v.r[i];
      return res;
    }

    inline simple_vector<VALTYPE,DIM> operator*(VALTYPE s) const
    {
      simple_vector<VALTYPE,DIM> res(0e0);
      for (int i=0; i<DIM; i++)
	res.r[i] = s*r[i];
      return res;
    }

    inline simple_vector<VALTYPE,DIM> operator/(VALTYPE s) const
    {
      simple_vector<VALTYPE,DIM> res(0e0);
      for (int i=0; i<DIM; i++)
	res.r[i] = r[i]/s;
      return res;
    }

    inline simple_vector<VALTYPE,DIM>& operator=(const simple_vector<VALTYPE,DIM> & v)
    {
      for (int i=0; i<DIM; i++)
	r[i] = v.r[i];
      return *this;
    }

    inline simple_vector<VALTYPE,DIM>& operator+=(const simple_vector<VALTYPE,DIM> & v)
    {
      simple_vector<VALTYPE,DIM> res(0e0);
      for (int i=0; i<DIM; i++)
	r[i] += v.r[i];
      return *this;
    }

    inline simple_vector<VALTYPE,DIM>& operator-=(const simple_vector<VALTYPE,DIM> & v)
    {
      simple_vector<VALTYPE,DIM> res(0e0);
      for (int i=0; i<DIM; i++)
	r[i] -= v.r[i];
      return *this;
    }

    inline simple_vector<VALTYPE,DIM>& operator*=(VALTYPE s)
    {
      simple_vector<VALTYPE,DIM> res(0e0);
      for (int i=0; i<DIM; i++)
	r[i] *= s;
      return *this;
    }

    inline simple_vector<VALTYPE,DIM>& operator/=(VALTYPE s)
    {
      simple_vector<VALTYPE,DIM> res(0e0);
      for (int i=0; i<DIM; i++)
	r[i] /= s;
      return *this;
    }

    inline simple_vector<VALTYPE,DIM> operator-() const
    {
      simple_vector<VALTYPE,DIM> res;
      for (int i=0; i<DIM; i++)
	res.r[i] = -r[i];
      return res;
    }

  };

  // -----------------------------------------------------------------------

  template<class VALTYPE = double>
  class vector3d : public simple_vector<VALTYPE,3>{
  protected:
    using simple_vector<VALTYPE,3>::r;
    using simple_vector<VALTYPE,3>::norm;
    using simple_vector<VALTYPE,3>::norm2;

  public:

    static typename numeric_type<VALTYPE>::norm tol_equiv;
    // tolerance for two vector equivalence, i.e. a==b if |a-b|<tol_equiv

    vector3d(){}

    vector3d(VALTYPE s) :
      simple_vector<VALTYPE,3>(s){}
    
    inline void set(VALTYPE x, VALTYPE y, VALTYPE z)
    {
      r[0] = x; r[1] = y; r[2] = z;
    }

    vector3d(VALTYPE x, VALTYPE y, VALTYPE z)
    {
      set(x,y,z);
    }

    vector3d(const vector3d<VALTYPE> & v)
    {
      r[0] = v(0);
      r[1] = v(1);
      r[2] = v(2);
    }

    /*
    vector3d(const vector3d<VALTYPE>& v) :
      simple_vector<VALTYPE,3>(v){}
    */
    vector3d(const simple_vector<VALTYPE,3> & v) :
      simple_vector<VALTYPE,3>(v){}
    
    inline VALTYPE& x(){return r[0];}

    inline VALTYPE& y(){return r[1];}

    inline VALTYPE& z(){return r[2];}

    inline VALTYPE x() const {return r[0];}

    inline VALTYPE y() const {return r[1];}

    inline VALTYPE z() const {return r[2];}

    inline vector3d<VALTYPE> operator%(const vector3d<VALTYPE> & v) const
    {
      vector3d<VALTYPE> res( y()*v.z() - z()*v.y(), 
			     z()*v.x() - x()*v.z(), 
			     x()*v.y() - y()*v.x() );
      return res;
    }


    inline bool operator==(const vector3d<VALTYPE> & b)
    {
      return (*this - b).norm() <=  tol_equiv;
    }

    inline bool operator!=(const vector3d<VALTYPE> & b)
    {
      return ! ((*this)==b);
    }

    template<class VALTYPE2>
    explicit operator vector3d<VALTYPE2>() const
    {
      return vector3d<VALTYPE2>(r[0],r[1],r[2]);
    }

#ifdef PY_EXPORT

    // --------------- PYTHON -------------------------------

    inline VALTYPE py_getitem(int i) const
    { return r[i]; }
    
    inline void py_setitem(int i, VALTYPE v)
    { r[i] = v;  }

    inline vector3d<VALTYPE> py_mul(VALTYPE s) const
    { return (*this)*s;}

    inline vector3d<VALTYPE> py_div(VALTYPE s) const
    { return (*this)/s;}

    inline vector3d<VALTYPE> py_add(const vector3d<VALTYPE> & x)
    { return (*this)+x; }

    inline vector3d<VALTYPE> py_sub(const vector3d<VALTYPE> & x)
    { return (*this)-x; }

    /*
    inline  vector3d<VALTYPE> py_add(const  vector3d<VALTYPE> & b) const
    { return (*this)+b;}

    inline  vector3d<VALTYPE> py_sub(const  vector3d<VALTYPE> & b) const
    { return (*this)-b;}
    */

    inline typename numeric_type<VALTYPE>::norm py_norm2() const
    { return norm2(); }

    inline typename numeric_type<VALTYPE>::norm py_norm() const
    { return norm(); }

    inline VALTYPE py_getx(){return x();}
    inline VALTYPE py_gety(){return y();}
    inline VALTYPE py_getz(){return z();}

    inline void py_setx(VALTYPE v){ x()=v;}
    inline void py_sety(VALTYPE v){ y()=v;}
    inline void py_setz(VALTYPE v){ z()=v;}

    vector3d(const boost::python::list &l)
    {
      // Assuming that length & type checks have been performed inside python code
      for (int i=0; i<3; i++)
	r[i] = boost::python::extract<VALTYPE>(l[i]);
    }    

    vector3d(const boost::python::tuple &l)
    {
      // Assuming that length & type checks have been performed inside python code
      for (int i=0; i<3; i++)
	r[i] = boost::python::extract<VALTYPE>(l[i]);
    }    

#endif

  };

  template<class VALTYPE,int DIM>
  inline simple_vector<VALTYPE,DIM> operator*(VALTYPE s, const simple_vector<VALTYPE,DIM> &v)
  {
    return v.operator*(s);
  }

  template<class VALTYPE,int DIM>
  inline simple_vector<VALTYPE,DIM> operator*(int s, const simple_vector<VALTYPE,DIM> &v)
  {
    return v.operator*((VALTYPE)s);
  }

  template<class VALTYPE,int DIM>
  inline VALTYPE scal(const simple_vector<VALTYPE,DIM> & v1, 
		      const simple_vector<VALTYPE,DIM> & v2)
  {
    VALTYPE res=0e0;
    for (int i=0; i<DIM; i++)
      res += std::conj(v1(i))*v2(i);
    return res;
  }
 
  template<class VALTYPE,int DIM>
  inline typename numeric_type<VALTYPE>::norm norm2(const simple_vector<VALTYPE,DIM> & v)
  { 
    VALTYPE res=0e0;
    for (int i=0; i<DIM; i++)
      res += std::conj(v(i))*v(i);
    return std::abs(res);
  }

  template<class VALTYPE,int DIM>
  inline typename numeric_type<VALTYPE>::norm norm(const simple_vector<VALTYPE,DIM> & v)
  {
    return std::sqrt(norm2(v));
  }

 /*---------------------------------------------------------*/

  template<class VALTYPE = double>
  class matrix3d{
    VALTYPE a[9];

  public:

    typedef VALTYPE real;

    static matrix3d<VALTYPE> unity;
    
    static typename numeric_type<VALTYPE>::norm tol_equiv;

    matrix3d(){}

    matrix3d(const matrix3d<VALTYPE> & m)
    {
      for (int i=0; i<9; i++)
	a[i] = m.a[i];
    }

    matrix3d(VALTYPE axx, VALTYPE axy, VALTYPE axz,
	     VALTYPE ayx, VALTYPE ayy, VALTYPE ayz,
	     VALTYPE azx, VALTYPE azy, VALTYPE azz)
    {
      a[0] = axx; a[1] = axy; a[2] = axz;
      a[3] = ayx; a[4] = ayy; a[5] = ayz;
      a[6] = azx; a[7] = azy; a[8] = azz;
    }

    matrix3d(VALTYPE alpha)
    {
      a[0] = a[4] = a[8] = alpha;
      a[1] = a[2] = a[3] = a[5] = a[6] = a[7] = VALTYPE(0);      
    }

    matrix3d(const vector3d<VALTYPE> & a1, const vector3d<VALTYPE> & b, const vector3d<VALTYPE> & c)
    {
      a[0] = a1.x(); a[1] = b.x(); a[2] = c.x();
      a[3] = a1.y(); a[4] = b.y(); a[5] = c.y();
      a[6] = a1.z(); a[7] = b.z(); a[8] = c.z();
    }

    inline VALTYPE & operator()(int i, int j){ return a[i*3+j];}

    inline VALTYPE operator()(int i, int j) const{ return a[i*3+j];}

    //------------------------------------

    inline VALTYPE& xx(){return a[0];}

    inline VALTYPE& xy(){return a[1];}

    inline VALTYPE& xz(){return a[2];}

    inline VALTYPE& yx(){return a[3];}

    inline VALTYPE& yy(){return a[4];}

    inline VALTYPE& yz(){return a[5];}

    inline VALTYPE& zx(){return a[6];}

    inline VALTYPE& zy(){return a[7];}

    inline VALTYPE& zz(){return a[8];}

    //------------------------------------

    inline VALTYPE xx() const{return a[0];}
		             
    inline VALTYPE xy() const{return a[1];}
		             
    inline VALTYPE xz() const{return a[2];}

    inline VALTYPE yx() const{return a[3];}
		             
    inline VALTYPE yy() const{return a[4];}
		             
    inline VALTYPE yz() const{return a[5];}

    inline VALTYPE zx() const{return a[6];}
		             
    inline VALTYPE zy() const{return a[7];}
		             
    inline VALTYPE zz() const{return a[8];}

    inline vector3d<VALTYPE> operator()(int i) const
    {
      return vector3d<VALTYPE>(a[i],a[i+3],a[i+6]);
    } 

    //------------------------------------

    inline vector3d<VALTYPE> operator*(const vector3d<VALTYPE> & x) const
    {
      
      vector3d<VALTYPE> res( a[0]*x.x() + a[1]*x.y() + a[2]*x.z(), 
			     a[3]*x.x() + a[4]*x.y() + a[5]*x.z(),
			     a[6]*x.x() + a[7]*x.y() + a[8]*x.z());
      return res;
    }

    inline matrix3d<VALTYPE> operator*(const matrix3d<VALTYPE> & b) const
    {
      // fixme -- not efficient!!!
      
      matrix3d<VALTYPE> res;

      for(int i=0; i<3; i++)
	for(int j=0; j<3; j++)
	  {
	    res(i,j) = 0e0;
	    for (int k=0; k<3; k++)
	      res(i,j) += (*this)(i,k)*b(k,j);
	  }
      return res;
    }

    inline matrix3d<VALTYPE> T() const
    {
      return matrix3d<VALTYPE>( a[0], a[3], a[6],
				a[1], a[4], a[7],
				a[2], a[5], a[8]);
    }

    inline matrix3d<VALTYPE>& operator=(VALTYPE alpha)
    {
      a[0] = a[4] = a[8] = VALTYPE(alpha);
      a[1] = a[2] = a[3] = a[5] = a[6] = a[7] = VALTYPE(0);
      return *this;
    }

    inline matrix3d<VALTYPE> operator+(const matrix3d<VALTYPE> & b) const
    {
      return  matrix3d<VALTYPE>( a[0]+b(0,0), a[1]+b(0,1), a[2]+b(0,2),
				 a[3]+b(1,0), a[4]+b(1,1), a[5]+b(1,2),
				 a[6]+b(2,0), a[7]+b(2,1), a[8]+b(2,2));
    } 

    inline matrix3d<VALTYPE> operator-(const matrix3d<VALTYPE> & b) const
    {
      return  matrix3d<VALTYPE>( a[0]-b(0,0), a[1]-b(0,1), a[2]-b(0,2),
				 a[3]-b(1,0), a[4]-b(1,1), a[5]-b(1,2),
				 a[6]-b(2,0), a[7]-b(2,1), a[8]-b(2,2));
    } 

    inline matrix3d<VALTYPE> operator-() const
    {
      return  matrix3d<VALTYPE>( -a[0], -a[1], -a[2],
				 -a[3], -a[4], -a[5],
				 -a[6], -a[7], -a[8]);
    }

    inline matrix3d<VALTYPE> operator*(VALTYPE alpha) const
    {
      return  matrix3d<VALTYPE>( a[0]*alpha, a[1]*alpha, a[2]*alpha,
				 a[3]*alpha, a[4]*alpha, a[5]*alpha,
				 a[6]*alpha, a[7]*alpha, a[8]*alpha);
    }

    inline matrix3d<VALTYPE> operator/(VALTYPE alpha) const
    {
      return operator*(VALTYPE(1)/alpha);
    }

    inline matrix3d<VALTYPE> operator*=(VALTYPE alpha)
    {
      for (int i = 0; i<9; i++)
	a[i] *= alpha;
      return *this;
    }

    inline matrix3d<VALTYPE> operator/=(VALTYPE alpha)
    {
      for (int i = 0; i<9; i++)
	a[i] /= alpha;
      return *this;
    }

    inline typename numeric_type<VALTYPE>::norm norm2() const
    {
      VALTYPE s = 0e0;
      for (int i = 0; i<9; i++)
	s += std::conj(a[i])*a[i];
      return std::abs(s);
    }

    inline typename numeric_type<VALTYPE>::norm norm() const
    {
      return std::sqrt(norm2());
    }

    inline bool operator==(const matrix3d<VALTYPE> & b) const
    {
      return ((*this) - b ).norm() <= tol_equiv;
    }

    inline bool operator!=(const matrix3d<VALTYPE> & b) const
    {
      return ((*this) - b ).norm() > tol_equiv;
    }

    inline VALTYPE det() const
    {
      return 
	xx()*( yy()*zz() - yz()*zy() )-
	xy()*( yx()*zz() - zx()*yz() )+
	xz()*( yx()*zy() - zx()*yy() );
    }

#ifdef PY_EXPORT

    matrix3d(const boost::python::list &l)
    {
      // Assuming that length & type checks have been performed inside python code
      for (int i=0; i<9; i++)
	a[i] = boost::python::extract<VALTYPE>(l[i]);
    }    

    matrix3d(const boost::python::tuple &l)
    {
      // Assuming that length & type checks have been performed inside python code
      for (int i=0; i<9; i++)
	a[i] = boost::python::extract<VALTYPE>(l[i]);
    }    

    inline matrix3d<VALTYPE> py_muln(VALTYPE s) const
    { return (*this)*s;}

    inline matrix3d<VALTYPE> py_divn(VALTYPE s) const
    { return (*this)/s;}

    inline vector3d<VALTYPE> py_mulv(const vector3d<VALTYPE> & v)
    { return (*this)*v;}

    inline VALTYPE py_getitem(boost::python::tuple I) const
    { 
      int i = boost::python::extract<int>(I[0]), j = boost::python::extract<int>(I[1]);
      return (*this)(i,j); 
    }
    
    inline void py_setitem(boost::python::tuple I, VALTYPE v)
    { 
      int i = boost::python::extract<int>(I[0]), j = boost::python::extract<int>(I[1]);
      (*this)(i,j) = v; 
    }

    inline vector3d<VALTYPE> py_getitemv(int i) const
    {
      return (*this)(i);
    }

    inline void py_setitemv(int i, const vector3d<VALTYPE> & v)
    {
      a[i] = v(0);
      a[i+3] = v(1);
      a[i+6] = v(2);
    } 

    inline VALTYPE py_getxx() const {return xx();}
    inline VALTYPE py_getxy() const {return xy();}
    inline VALTYPE py_getxz() const {return xz();}
    inline VALTYPE py_getyx() const {return yx();}
    inline VALTYPE py_getyy() const {return yy();}
    inline VALTYPE py_getyz() const {return yz();}
    inline VALTYPE py_getzx() const {return zx();}
    inline VALTYPE py_getzy() const {return zy();}
    inline VALTYPE py_getzz() const {return zz();}

    inline void py_setxx(VALTYPE v) {xx() = v;}
    inline void py_setxy(VALTYPE v) {xy() = v;}
    inline void py_setxz(VALTYPE v) {xz() = v;}
    inline void py_setyx(VALTYPE v) {yx() = v;}
    inline void py_setyy(VALTYPE v) {yy() = v;}
    inline void py_setyz(VALTYPE v) {yz() = v;}
    inline void py_setzx(VALTYPE v) {zx() = v;}
    inline void py_setzy(VALTYPE v) {zy() = v;}
    inline void py_setzz(VALTYPE v) {zz() = v;}

#endif

  };
  
  template<class VALTYPE>
  inline VALTYPE det(const matrix3d<VALTYPE> & a)
  {
    return a.det();
  }

  template<class VALTYPE>
  inline VALTYPE det(const vector3d<VALTYPE> & a, const vector3d<VALTYPE> & b, const vector3d<VALTYPE> & c)
  {
    return 
	a.x()*( b.y()*c.z() - b.z()*c.y() )-
	a.y()*( b.x()*c.z() - c.x()*b.z() )+
	a.z()*( b.x()*c.y() - c.x()*b.y() );
  }

  template<class VALTYPE>
  inline double norm(const matrix3d<VALTYPE> & a)
  {
    return a.norm();
  }

  template<class VALTYPE>
  inline matrix3d<VALTYPE> operator*(VALTYPE alpha, const matrix3d<VALTYPE> & a)
  {
    return a*alpha;
  }

  template<class VALTYPE>
  typename numeric_type<VALTYPE>::norm matrix3d<VALTYPE>::tol_equiv = 1e-8;

  template<class VALTYPE>
  matrix3d<VALTYPE> matrix3d<VALTYPE>::unity(1e0);

  template<class VALTYPE>
  typename numeric_type<VALTYPE>::norm vector3d<VALTYPE>::tol_equiv = 1e-8;

  //-------------------------------------------------

  template<class VALTYPE>
  matrix3d<VALTYPE> outer(const vector3d<VALTYPE> & a,const vector3d<VALTYPE> & b)
  {
    matrix3d<VALTYPE> res;
    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
	res(i,j) = a(i)*b(j);
    return res;
  }

  //-------------------------------------------------

  template<class VALTYPE>
  matrix3d<VALTYPE> RotMtrx(const simple_vector<VALTYPE,3> & nn, VALTYPE phi)
  {
    vector3d<VALTYPE> n = nn/norm(nn);

    VALTYPE c = std::cos(phi), s = std::sin(phi);
    return matrix3d<VALTYPE>
      ( n(0)*n(0)*(1-c) + c,       n(0)*n(1)*(1-c) + n(2)*s,  n(0)*n(2)*(1-c) - n(1)*s,
	n(1)*n(0)*(1-c) - n(2)*s,  n(1)*n(1)*(1-c) + c,       n(1)*n(2)*(1-c) + n(0)*s,
	n(2)*n(0)*(1-c) + n(1)*s,  n(2)*n(1)*(1-c) - n(0)*s,  n(2)*n(2)*(1-c) + c    );
  }

  template<class VALTYPE>
  matrix3d<VALTYPE> Sigma(const simple_vector<VALTYPE,3> & nn)
  {
    vector3d<VALTYPE> n = nn/norm(nn);
    return matrix3d<VALTYPE>
      ( 1e0 - 2*n(0)*n(0), -2*n(0)*n(1),      -2*n(0)*n(2),
	-2*n(0)*n(1),      1e0 - 2*n(1)*n(1), -2*n(1)*n(2),
	-2*n(0)*n(2),      -2*n(1)*n(2),      1e0 - 2*n(2)*n(2) );
  } 

  template<class VALTYPE>
  vector3d<VALTYPE> solve3d(const matrix3d<VALTYPE> & A, const vector3d<VALTYPE> & b)
  {
    VALTYPE 
      D = det(A),
      X = det(b,    A(1), A(2)),
      Y = det(A(0), b,    A(2)),
      Z = det(A(0), A(1), b);
    return vector3d<VALTYPE>(X, Y, Z)/D;
  }

  template<class VALTYPE>
  matrix3d<VALTYPE> invert(const matrix3d<VALTYPE> & A)
  {
    matrix3d<VALTYPE> b(  A(1,1)*A(2,2) - A(1,2)*A(2,1), -A(0,1)*A(2,2) + A(0,2)*A(2,1),  A(0,1)*A(1,2) - A(1,1)*A(0,2),
			 -A(1,0)*A(2,2) + A(2,0)*A(1,2),  A(0,0)*A(2,2) - A(0,2)*A(2,0), -A(0,0)*A(1,2) + A(1,0)*A(0,2), 
			  A(1,0)*A(2,1) - A(2,0)*A(1,1), -A(0,0)*A(2,1) + A(2,0)*A(0,1),  A(0,0)*A(1,1) - A(1,0)*A(0,1));
    return b/det(A);
  }

  template<class VALTYPE>
  matrix3d<VALTYPE> pow(const matrix3d<VALTYPE> & A, int n)
  {
    // fixme - very inefficient
    matrix3d<VALTYPE> R=VALTYPE(1);
    if (n>0)
      {
	while (n-- > 0)
	  R = A*R;
      }
    else if (n<0)
      {
	matrix3d<VALTYPE>  B = invert(A);
	while (n++ < 0)
	  R = B*R;
      }
    return R;
  }

  template<class VALTYPE>
  vector3d<VALTYPE> solve3d(const vector3d<VALTYPE> & A0, const vector3d<VALTYPE> & A1, 
			    const vector3d<VALTYPE> & A2, const vector3d<VALTYPE> & b)
  {
    VALTYPE 
      D = det(A0, A1, A2),
      X = det(b,  A1, A2),
      Y = det(A0, b,  A2),
      Z = det(A0, A1, b);
    return vector3d<VALTYPE>(X, Y, Z)/D;
  }

  //-------------------------------------------------

  template<class REAL>
  inline std::complex<REAL> operator/(const std::complex<REAL> & c, int d)
  { return c/REAL(d); }

  //-------------------------------------------------

  template<class VALTYPE>
  vector3d<typename numeric_type<VALTYPE>::complex> solve_cubeq(VALTYPE a, VALTYPE b, VALTYPE c, VALTYPE d)
  // Solves ax^3 + bx^2 + cx + d = 0, a is assumed to be nonzero
  {
    typename numeric_type<VALTYPE>::complex I(0,1);
    VALTYPE s32 = .5*std::sqrt(3.);
    VALTYPE eps = vector3d<VALTYPE>::tol_equiv;
    vector3d<typename numeric_type<VALTYPE>::complex> res(0);

    b /= a;
    c /= a;
    d /= a;
    VALTYPE Q = (b*b-3*c)/9, R = d/2 - b*c/6 + b*b*b/27;
    int sgnr = (R>0) ? 1 : -1;

    if ( std::abs(Q) < eps )
      {
	VALTYPE R13 = std::pow(2*std::abs(R),1./3)*sgnr;
	res = {-1, VALTYPE(.5) + s32*I, VALTYPE(.5) - s32*I };
	res *= R13;
	for (int i=0; i<3; i++)
	  res(i) -= b/3;
      }

    else if (R*R<Q*Q*Q)
      // three real roots
      {
	VALTYPE SQ = std::sqrt(Q);
	VALTYPE theta = std::acos(R/(Q*SQ));
	res = {-2*SQ*std::cos(theta/3)-b/3, -2*SQ*std::cos((theta+2*pi)/3)-b/3, -2*SQ*std::cos((theta+4*pi)/3)-b/3};
      }

    else
      {
	VALTYPE A = -std::pow(std::abs(R)+std::sqrt(R*R-Q*Q*Q), 1./3)*sgnr;
	VALTYPE B=0;
	if ( std::abs(A)>eps)
	  B = Q/A;
	res = { -b/3 + A + B, -b/3 - (A + B)/2 + I*s32*(A - B), -b/3 - (A + B)/2 - I*s32*(A - B)};
      }

    return res;
  }

  //-------------------------------------------------

  template<class VALTYPE>
  vector3d<VALTYPE> diagon3d(const matrix3d<VALTYPE> & A)
  {
    VALTYPE b = A(0,0) + A(1,1) + A(2,2);
    VALTYPE c = A(0,1)*A(1,0) + A(1,2)*A(2,1) + A(2,0)*A(0,2) -
      A(0,0)*A(1,1) - A(1,1)*A(2,2) - A(2,2)*A(0,0);
    VALTYPE d = det(A);

    vector3d<typename numeric_type<VALTYPE>::complex> lbd = solve_cubeq(-VALTYPE(1e0),b,c,d);
    vector3d<VALTYPE> lbd_re;
    for (int i=0; i<3; i++)
      lbd_re(i) = lbd(i).real();
    return lbd_re;
  }

  template<class VALTYPE>
  void diagon3d(vector3d<typename numeric_type<VALTYPE>::complex> & eigvals, 
		matrix3d<typename numeric_type<VALTYPE>::complex> & eigvecs,
		const matrix3d<VALTYPE> & A)
  {
    typename numeric_type<VALTYPE>::real eps = vector3d<VALTYPE>::tol_equiv;
    
    VALTYPE offd = A(0,1)*A(0,1) + A(1,0)*A(1,0) + A(1,2)*A(1,2) +
      A(2,1)*A(2,1) + A(2,0)*A(2,0) + A(0,2)*A(0,2);

    if ( offd < eps*eps )
      // Already diagonal
      {
	eigvals = { A(0,0), A(1,1), A(2,2)};
	eigvecs = { {1,0,0}, {0,1,0}, {0,0,1} };
	return;
      }


    VALTYPE b = A(0,0) + A(1,1) + A(2,2);
    VALTYPE c = A(0,1)*A(1,0) + A(1,2)*A(2,1) + A(2,0)*A(0,2) -
      A(0,0)*A(1,1) - A(1,1)*A(2,2) - A(2,2)*A(0,0);
    VALTYPE d = det(A);

    eigvals = solve_cubeq(-VALTYPE(1),b,c,d);
    typename numeric_type<VALTYPE>::complex e0 = eigvals(0),
      e1 = eigvals(1), e2=eigvals(2), e;

    int ndiff;
    
    /*
    std::cout << "eigvals= " << eigvals << "\n";
    std::cout << " diffs: " << std::abs(e0-e1) << " "  << std::abs(e1-e2) << " " << std::abs(e2-e0) << 
      " eps= " << eps << "\n";
    */

    if ( std::abs(e0-e1)>eps &&  std::abs(e1-e2)>eps &&  std::abs(e2-e0)>eps)
      ndiff = 3;
    else if ( std::abs(e0-e1) <= eps &&  std::abs(e1-e2) <= eps &&  std::abs(e2-e0) <= eps)
      ndiff = 1;
    else
      {
	ndiff = 2;
	if ( std::abs(e1-e2) <= eps )
	  {
	    e=e2; e2=e0; e0=e;
	  }
	else if ( std::abs(e2-e0) <= eps )
	  {
	    e=e2; e2=e1; e1=e;
	  }
	eigvals = {e0,e1,e2};
      }

    //std::cout << "eigvals after sorting = " << eigvals << "\n";

    matrix3d<typename numeric_type<VALTYPE>::complex> AA, B, E;
    vector3d<typename numeric_type<VALTYPE>::complex> n0,n1,n2;

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
	AA(i,j)=A(i,j);
    E = 0;
    E(0,0) = E(1,1) = E(2,2) = 1;

    if (ndiff==1)
      {
	// e0, e1 and e2 
	//std::cout << "e0==e1==e2\n";
	n0 = {1,0,0};
	n1 = {0,1,0};
	n2 = {0,0,1};
      }
    else if (ndiff==2)
      // e0 == e1 != e2
      {
	//std::cout << "e0==e1!=e2\n";
	B = AA - e2*E;
	B /= B.norm();
	//B = B.T();

	int i=0;
	if ( norm(B(1))>norm(B(0)) )
	  i=1;
	if (norm(B(2))>norm(B(i)))
	  i=2;
	n0 = B(i)/norm(B(i));
	
	i=0;
	if ( norm(B(1)-n0*scal(n0,B(1))) > norm(B(0)-n0*scal(n0,B(0))))
	  i=1;
	if ( norm(B(2)-n0*scal(n0,B(2))) > norm(B(i)-n0*scal(n0,B(i))))
	  i=2;
	n1 = B(i)-n0*scal(n0,B(i));
	n1 /= norm(n1);
	
	/*
	B = (AA - e0*E);
	B /= B.norm();
	B = B*(AA - e0*E);
	B /= B.norm();
	//B = B.T();

	i=0;
	if ( norm(B(1))>norm(B(0)) )
	  i=1;
	if (norm(B(2))>norm(B(i)))
	  i=2;
	n2 = B(i)/norm(B(i));
	*/

	n2 = n0%n1;
	
      }
    else
      // e0 != e1 != e2
      {
	//std::cout << "e0!=e1!=e2\n";

	B = (AA - e1*E);
	B /= B.norm();
	B = B*(AA - e2*E);
	B /= B.norm();
	//B = B.T();

	int i=0;
	if ( norm(B(1))>norm(B(0)) )
	  i=1;
	if (norm(B(2))>norm(B(i)))
	  i=2;
	n0 = B(i)/norm(B(i));

	B = (AA - e0*E);
	B /= B.norm();
	B = B*(AA - e2*E);
	B /= B.norm();
	//B = B.T();

	i=0;
	if ( norm(B(1)-n0*scal(n0,B(1)))>norm(B(0)-n0*scal(n0,B(1))) )
	  i=1;
	if ( norm(B(2)-n0*scal(n0,B(2)))>norm(B(i)-n0*scal(n0,B(i))) )
	  i=2;

	n1 = B(i) - n0*scal(n0,B(i));
	n1 /= norm(n1);
	
	//n1 = B(i)/norm(B(i));

	B = (AA - e0*E);
	B /= B.norm();
	B = B*(AA - e1*E);
	B /= B.norm();
	//B = B.T();

	i=0;
	if ( norm(B(1)-n0*scal(n0,B(1))-n1*scal(n1,B(1)))>norm(B(0)-n0*scal(n0,B(0))-n1*scal(n1,B(0))) )
	  i=1;
	if ( norm(B(2)-n0*scal(n0,B(2))-n1*scal(n1,B(2)))>norm(B(i)-n0*scal(n0,B(i))-n1*scal(n1,B(i))) )
	  i=2;
	
	n2 = B(i)-n0*scal(n0,B(i))-n1*scal(n1,B(i));
	n2 /= norm(n2);	
	//n2 = B(i)/norm(B(i));
      }

    int i=0;
    if (std::abs(n0(i))<std::abs(n0(1))) i=1;
    if (std::abs(n0(i))<std::abs(n0(2))) i=2;
    n0 *= std::abs(n0(i))/n0(i);

    i=0;
    if (std::abs(n1(i))<std::abs(n1(1))) i=1;
    if (std::abs(n1(i))<std::abs(n1(2))) i=2;
    n1 *= std::abs(n1(i))/n1(i);

    i=0;
    if (std::abs(n2(i))<std::abs(n2(1))) i=1;
    if (std::abs(n2(i))<std::abs(n2(2))) i=2;
    n2 *= std::abs(n2(i))/n2(i);

    for (int i=0; i<3; i++)
      {
	eigvecs(i,0) = n0(i);
	eigvecs(i,1) = n1(i);
	eigvecs(i,2) = n2(i);
      }    
  }

  template<class VALTYPE>
  bool diagon3d(vector3d<VALTYPE> & eigvals, matrix3d<VALTYPE> & eigvecs,
		const matrix3d<VALTYPE> & A)
  {
    vector3d<typename numeric_type<VALTYPE>::complex> ceigvals; 
    matrix3d<typename numeric_type<VALTYPE>::complex> ceigvecs;
    VALTYPE eps = vector3d<VALTYPE>::tol_equiv;

    bool res = true;
    diagon3d(ceigvals,ceigvecs,A);

    for (int i=0; i<3; i++)
      {
	eigvals(i) = ceigvals(i).real();
	if ( std::abs(ceigvals(i).imag()) > eps )
	  res = false;
      }

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
	{
	  eigvecs(i,j) = ceigvecs(i,j).real();
	  if ( std::abs(ceigvecs(i,j).imag()) > eps )
	    res = false;
	}
    return res;
  }

#ifdef PY_EXPORT
  
  template<class VALTYPE>
  inline vector3d<VALTYPE> py_diagon3dv(const matrix3d<VALTYPE> & A)
  { return diagon3d(A); }

  template<class VALTYPE>
  inline void py_diagon3dm(vector3d<typename numeric_type<VALTYPE>::complex> & eigvals, 
			   matrix3d<typename numeric_type<VALTYPE>::complex> & eigvecs,
			   const matrix3d<VALTYPE> & A)
  { diagon3d(eigvals,eigvecs,A); }

  template<class VALTYPE>
  inline bool py_diagon3dreal(vector3d<VALTYPE> & eigvals, matrix3d<VALTYPE> & eigvecs,
			      const matrix3d<VALTYPE> & A)
  { return diagon3d(eigvals,eigvecs,A); }

  template<class VALTYPE>
  inline VALTYPE py_detm(const matrix3d<VALTYPE> & a)
  { return det(a); }

  template<class VALTYPE>
  inline VALTYPE py_detv(const vector3d<VALTYPE> & a, const vector3d<VALTYPE> & b, const vector3d<VALTYPE> & c)
  { return det(a,b,c); }

  template<class VALTYPE>
  inline vector3d<VALTYPE> py_solve3m(const matrix3d<VALTYPE> & A, const vector3d<VALTYPE> & b)
  { return solve3d(A,b);}

  template<class VALTYPE>
  inline vector3d<VALTYPE> py_solve3v(const vector3d<VALTYPE> & A0, const vector3d<VALTYPE> & A1, 
				      const vector3d<VALTYPE> & A2, const vector3d<VALTYPE> & b)
  { return solve3d(A0,A1,A2,b);}

  template<class VALTYPE>
  inline matrix3d<VALTYPE> py_invert_mtr(const matrix3d<VALTYPE> & A)
  { return invert(A);}

  template<class VALTYPE>
  inline matrix3d<VALTYPE> py_pow_mtr(const matrix3d<VALTYPE> & A, int n) {return pow(A,n);}

  template<class VALTYPE>
  inline matrix3d<VALTYPE> py_rotmtrx_v(const vector3d<VALTYPE> & nn, VALTYPE phi)
  {  return RotMtrx(nn,phi);}

  template<class VALTYPE>
  inline matrix3d<VALTYPE> py_rotmtrx_t(const boost::python::tuple & nn, VALTYPE phi)
  {  return RotMtrx(vector3d<VALTYPE>(nn),phi);}

  template<class VALTYPE>
  inline matrix3d<VALTYPE> py_rotmtrx_l(const boost::python::list & nn, VALTYPE phi)
  {  return RotMtrx(vector3d<VALTYPE>(nn),phi);}

  template<class VALTYPE>
  inline matrix3d<VALTYPE> py_sigma_v(const vector3d<VALTYPE> & nn)
  {  return Sigma(nn);}

  template<class VALTYPE>
  inline matrix3d<VALTYPE> py_sigma_t(const boost::python::tuple & nn)
  {  return Sigma(vector3d<VALTYPE>(nn));}

  template<class VALTYPE>
  inline matrix3d<VALTYPE> py_sigma_l(const boost::python::list & nn)
  {  return Sigma(vector3d<VALTYPE>(nn));}

#endif

  //-------------------------------------------------

  //template<class VALTYPE>
  // bool diagon3d(const matrix3d<VALTYPE> & A, 
  // 		matrix3d<VALTYPE> & Q, vector3d<VALTYPE> &lambda)
  // {
  //   const VALTYPE tol = 1e-10;
  //   const int N = 100;

  //   matrix3d<VALTYPE> AA = A;
    
  //   n=0;
  //   while (n<3)
  //     {
  // 	vector3d<VALTYPE> x(1,0,0), x1;

  // 	x1 = AA*x;
  // 	if (norm(x1)<tol)
  // 	  {
  // 	    lambda(n) = 0e0;
  // 	    Q(n) = x;
  // 	    continue;
  // 	  }

  // 	n++;
  //     }
  // }

  //-------------------------------------------------

  template<typename _CharT, class _Traits, class VALTYPE>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& __os, const matrix3d<VALTYPE> & a)
  {
    std::basic_ostringstream<_CharT, _Traits> __s;
    __s.flags(__os.flags());
    __s.imbue(__os.getloc());
    __s.precision(__os.precision());
    __s  << "matrix3(" 
	 << a(0,0) << "," << a(0,1) << "," << a(0,2) << ",  "
	 << a(1,0) << "," << a(1,1) << "," << a(1,2) << ",  "
	 << a(2,0) << "," << a(2,1) << "," << a(2,2) << ")" ;
    return __os << __s.str();
  }

  // -------------------------- 2d vectors ---------------------------

  template <class VALTYPE>
  class vector2d : public simple_vector<VALTYPE,2>{
  protected:
    using simple_vector<VALTYPE,2>::r;

  public:
    vector2d()
    {}

    vector2d(VALTYPE _x, VALTYPE _y)
    {
      r[0] = _x;
      r[1] = _y;
    }

    vector2d(const simple_vector<VALTYPE,2>& v) :
      simple_vector<VALTYPE,2>(v){}

    vector2d(const vector2d & v) :
      simple_vector<VALTYPE,2>(v){}

  };

  // ------------------------------------------------------------------
  //                          2d matrix
  // ------------------------------------------------------------------

  template<class VALTYPE>
  class matrix2d{
    VALTYPE a[4];

  public:

    matrix2d(VALTYPE a00, VALTYPE a01, VALTYPE a10, VALTYPE a11)
    {
      a[0] = a00;
      a[1] = a01;
      a[2] = a10;
      a[3] = a11;
    }

    matrix2d(const vector2d<VALTYPE> & a0, const vector2d<VALTYPE> & a1)
    {
      a[0] = a0.x;
      a[1] = a1.x;
      a[2] = a0.y;
      a[3] = a1.y;
    }

    inline VALTYPE & operator()(int i, int j)
    {
      return a[2*i+j];
    }

    inline VALTYPE operator()(int i, int j) const
    {
      return a[2*i+j];
    }

    // fixme - implement everything else!

  };

  template<typename _CharT, class _Traits, class VALTYPE, int DIM>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& __os, const simple_vector<VALTYPE, DIM> &v)
  {
    std::basic_ostringstream<_CharT, _Traits> __s;
    __s.flags(__os.flags());
    __s.imbue(__os.getloc());
    __s.precision(__os.precision());
    __s << "(";
    if (DIM>0)
      __s << v(0);
    for (int i=1; i<DIM; i++)
      __s << "," << v(i);
    __s <<  ")";
    return __os << __s.str();
  }

};

#endif
