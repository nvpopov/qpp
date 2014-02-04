#ifndef _QPP_MANYFOLD
#define _QPP_MANYFOLD

#include <lace/lace3d.hpp>
#include <constants.hpp>
#include <io/qppdata.hpp>
#include <mathf/specfunc.hpp>
#include <cmath>

namespace lace{

  // -------------------------- 2d vectors ---------------------------
  // fixme - implement necessary operations, move to separate file in lace

  template <class VALTYPE>
  struct vector2d{
    VALTYPE x,y;

    vector2d()
    {
      x = VALTYPE(0);
      y = VALTYPE(0);
    }

    vector2d(VALTYPE _x, VALTYPE _y)
    {
      x = _x;
      y = _y;
    }

    inline VALTYPE & operator()(int i)
    {
      if (i==0)
	return x;
      else if (i==1)
	return y;
    }

    inline vector2d<VALTYPE> operator+(vector2d<VALTYPE> b)
    {
      return vector2d<VALTYPE>(x+b.x,y+b.y);
    }

    inline vector2d<VALTYPE> operator-(vector2d<VALTYPE> b)
    {
      return vector2d<VALTYPE>(x-b.x,y-b.y);
    }

    inline vector2d<VALTYPE> operator*(VALTYPE s)
    {
      return vector2d<VALTYPE>(x*s,y*s);
    }

    inline vector2d<VALTYPE> operator/(VALTYPE s)
    {
      return vector2d<VALTYPE>(x/s,y/s);
    }

  };

  template<class VALTYPE>
  inline vector2d<VALTYPE> operator*(VALTYPE s, vector2d<VALTYPE> a)
  {
    return vector2d<VALTYPE>(a.x*s,a.y*s);
  }

  template<class VALTYPE>
  inline VALTYPE norm(vector2d<VALTYPE> a)
  {
    return std::sqrt(a.x*a.x+a.y*a.y);
  }

  // ------------------------------------------------------------------

};

namespace qpp{

  template <class VALTYPE, class charT=std::string::value_type , class traits = std::char_traits<charT> >
  class parametric_surface : public qpp_object<charT,traits>{

  protected:
    
    using typename qpp_object<charT,traits>::string;
    string _name;

  public:
    
    virtual lace::vector3d<VALTYPE> parm2xyz(VALTYPE xi, VALTYPE eta) =0;
    // get the point on the surface corresponding to xi and eta parameters values

    virtual lace::vector3d<VALTYPE> d2d3(lace::vector2d<VALTYPE> v)
    {
      return parm2xyz(v.x, v.y);
    }

    virtual lace::vector2d<VALTYPE> xyz2parm(lace::vector3d<VALTYPE> r) =0;
    // get the point on surface closest to r

    virtual lace::vector2d<VALTYPE> ruler(lace::vector2d<VALTYPE> from, lace::vector2d<VALTYPE> direction, 
				    VALTYPE distance) =0;
    // find the point at "distance" from the given "from" point in given "direction"

    virtual lace::vector2d<VALTYPE> protractor(lace::vector2d<VALTYPE> point1, lace::vector2d<VALTYPE> point2, 
					 VALTYPE distance, VALTYPE angle) =0;
    // find the point at "distance" from point1 and at "angle" to the point1-point2 direction
    
    virtual VALTYPE xi_min() =0;
    virtual VALTYPE xi_max() =0;
    virtual VALTYPE eta_min() =0;
    virtual VALTYPE eta_max() =0;

    virtual lace::matrix3d<VALTYPE> gtensor(VALTYPE xi, VALTYPE eta) =0;
    // Covariant metric tensor;
    // fixme - its not 3x3, but 2x2 matrix!

    virtual string name()
    {
      return _name;
    }

    virtual int gettype()
    {
      return qppdata_manyfold;
    }

  };

  /*
  template <class VALTYPE>
  class parametric_sphere : public parametric_surface<VALTYPE>{

  };
  */

  template <class VALTYPE, class charT=std::string::value_type , class traits = std::char_traits<charT> >
  class parametric_torus : public parametric_surface<VALTYPE,charT,traits>{

    using typename qpp_object<charT,traits>::string;
    using parametric_surface<VALTYPE,charT,traits>::parm2xyz;

    VALTYPE a,b;
    lace::vector3d<VALTYPE> origin, axis;
    lace::matrix3d<VALTYPE> Rot;
    
  protected:
    using parametric_surface<VALTYPE,charT,traits>::_name;

  public:

    parametric_torus( VALTYPE _a, VALTYPE _b, string __name = "") : origin(0,0,0), axis(0,0,1)
    {
      a = _a; 
      b = _b;
      Rot = VALTYPE(1);
      _name = __name;
    }

    parametric_torus( VALTYPE _a, VALTYPE _b, lace::vector3d<VALTYPE> _origin, 
		      lace::vector3d<VALTYPE> _axis, string __name = "")
    {
      a = _a; 
      b = _b;
      origin = _origin;
      axis = _axis;
      
      axis = axis/norm(axis);
      lace::vector3d<VALTYPE> n( axis.y(), -axis.x(), 0);
      VALTYPE phi = std::acos(axis.z());

      Rot = lace::RotMtrx(n,phi);
      _name = __name;
    }

    virtual lace::vector3d<VALTYPE> parm2xyz(VALTYPE theta, VALTYPE phi)
    {
      lace::vector3d<VALTYPE> r;
      r.z() = b*std::sin(theta);
      r.x() = a - b*std::cos(theta);
      r.y() = r.x()*std::sin(phi);
      r.x() *= std::cos(phi);

      return origin + Rot*r;
    }

    virtual lace::vector2d<VALTYPE> xyz2parm(lace::vector3d<VALTYPE> r)
    {}
    // get the point on surface closest to r

    virtual lace::vector2d<VALTYPE> ruler(lace::vector2d<VALTYPE> from, lace::vector2d<VALTYPE> direction, 
				    VALTYPE distance)
    {
      // fixme - this is very approximate and should work ugly on small torus!
      lace::vector2d<VALTYPE> r = direction*distance/norm(direction);
      r.x /= b;
      r.y /= a - b*std::cos(from.x);
      return from + r;
    }

    virtual lace::vector2d<VALTYPE> protractor(lace::vector2d<VALTYPE> point1, lace::vector2d<VALTYPE> point2, 
					 VALTYPE distance, VALTYPE alpha)
    {
      // fixme - this is very approximate and should work ugly on small torus!
      lace::vector2d<VALTYPE> delta0 = point1-point2;
      VALTYPE theta = point2.x, 
	phi = point2.y,
	g1 = b,
	g2 = a - b*std::cos(theta),
	beta = atanxy(g1*delta0.x, g2*delta0.y);
      lace::vector2d<VALTYPE> n( std::cos(alpha+beta), std::sin(alpha+beta) );
      return ruler(point2,n,distance);
    }
    
    virtual VALTYPE xi_min()
    {
      return 0;
    }

    virtual VALTYPE xi_max()
    {
      return 2*pi;
    }

    virtual VALTYPE eta_min()
    {
      return 0;
    }

    virtual VALTYPE eta_max()
    {
      return 2*pi;
    }

    virtual lace::matrix3d<VALTYPE> gtensor(VALTYPE theta, VALTYPE phi)
    {

    }


    // derived from qpp_object
    virtual string category()
    {
      return "torus";
    }

    virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
    {
      // fixme - write all data 
      for (int k=0; k<offset; k++) os << " ";
      os << "torus";
      if (_name != "")
	os << " " << _name;
      os << "(" << a << "," << b << ")";
      if (offset>0)
	os << ";\n";
      
    }

  };
  
  // ----------------------------------------------------------------------------

  template <class VALTYPE, class charT=std::string::value_type , class traits = std::char_traits<charT> >
  class parametric_plane : public parametric_surface<VALTYPE,charT,traits>{

    using typename qpp_object<charT,traits>::string;
    //    using parametric_surface<VALTYPE,charT,traits>::parm2xyz;

    lace::vector3d<VALTYPE> origin,axis1,axis2;
    
  protected:
    using parametric_surface<VALTYPE,charT,traits>::_name;

  public:

    parametric_plane( string __name = "") : origin(0,0,0), axis1(1,0,0), axis2(0,1,0)
    {
      _name = __name;
    }

    parametric_plane( lace::vector3d<VALTYPE> _origin, lace::vector3d<VALTYPE> _axis1,  
		      lace::vector3d<VALTYPE> _axis2, string __name = "")
    {
      origin = _origin;
      axis1 = _axis1;
      axis2 = _axis2;
      _name = __name;
    }

    virtual lace::vector3d<VALTYPE> parm2xyz(VALTYPE x, VALTYPE y)
    {
      return origin + axis1*x + axis2*y;
    }

    virtual lace::vector2d<VALTYPE> xyz2parm(lace::vector3d<VALTYPE> r)
    {}
    // get the point on surface closest to r

    virtual lace::vector2d<VALTYPE> ruler(lace::vector2d<VALTYPE> from, lace::vector2d<VALTYPE> direction, 
				    VALTYPE distance)
    {
      return from + distance*direction/norm(direction);
    }

    virtual lace::vector2d<VALTYPE> protractor(lace::vector2d<VALTYPE> point1, lace::vector2d<VALTYPE> point2, 
					 VALTYPE distance, VALTYPE alpha)
    {
      lace::vector2d<VALTYPE> delta0 = point1-point2;
      VALTYPE beta = atanxy(delta0.x, delta0.y);
      lace::vector2d<VALTYPE> n( std::cos(alpha+beta), std::sin(alpha+beta) );
      return ruler(point2,n,distance);
    }
    
    virtual VALTYPE xi_min()
    {
      return 0;
    }

    virtual VALTYPE xi_max()
    {
      return 0;
    }

    virtual VALTYPE eta_min()
    {
      return 0;
    }

    virtual VALTYPE eta_max()
    {
      return 0;
    }

    virtual lace::matrix3d<VALTYPE> gtensor(VALTYPE theta, VALTYPE phi)
    {

    }


    // derived from qpp_object
    virtual string category()
    {
      return "plane";
    }

    virtual void write(std::basic_ostream<charT,traits> &os, int offset=0)
    {
      // fixme - write all data 
      for (int k=0; k<offset; k++) os << " ";
      os << "plane";
      if (_name != "")
	os << " " << _name;
      os << "(" << ")";
      if (offset>0)
	os << ";\n";
      
    }

  };

};

#endif
