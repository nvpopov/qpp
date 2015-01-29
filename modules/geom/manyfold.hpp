#ifndef _QPP_MANYFOLD
#define _QPP_MANYFOLD

#include <lace/lace3d.hpp>
#include <data/qppdata.hpp>
#include <mathf/constants.hpp>
#include <mathf/specfunc.hpp>
#include <geom/geom.hpp>
#include <cmath>

#define v2d lace::vector2d<VALTYPE>
#define v3d lace::vector3d<VALTYPE>

namespace qpp{

  // ------------------ Parametric surface --------------------

  int const default_maxiter = 100;

  template <class VALTYPE>
  class parametric_surface : public qpp_object{

  public:

    VALTYPE geomtol;
    int maxiter;


    /*
    virtual VALTYPE xi_min() =0;
    virtual VALTYPE xi_max() =0;
    virtual VALTYPE eta_min() =0;
    virtual VALTYPE eta_max() =0;
    */

    // limits of the parametric domain    
    virtual v2d parmin() const =0;
    virtual v2d parmax() const =0;

    virtual v3d map(const v2d &v) const =0;
    // get the point on the surface corresponding to xi and eta parameters values

    v3d parm2cart(const VALTYPE & xi, const VALTYPE & eta) const
    // get the point on the surface corresponding to xi and eta parameters values
    {
      return map(v2d(xi,eta));
    }

    virtual v2d project(const v3d & r) const =0;
    // get the point on surface closest to r

    virtual VALTYPE dx_dxi(const VALTYPE & xi, const VALTYPE & eta, int i, int j) const =0;
    // derivatives of cartesian coondinates over parameters

    virtual v3d normal(const v2d &v) const =0;
    // get the vector normal to the surface

    virtual lace::matrix2d<VALTYPE> gtensor(const v2d &v) const =0;
    // Covariant metric tensor;

    virtual v2d ruler(const v2d & from, const v2d & direction, 
				    const VALTYPE & distance) const =0;
    // find the point at "distance" from the given "from" point in given "direction"

    virtual v2d protract(v2d a, v2d b,VALTYPE distance, VALTYPE angle) =0;
    // find the point at "distance" from point1 and at "angle" (surface angle - angle between the tangents) 
    // to the point1-point2 direction

    virtual v2d triangul(v2d a, v2d b, VALTYPE distance, VALTYPE angle) =0;
    // the same, but the "angle" is between the direction in 3d space
    
    virtual std::vector<v2d> triangul2b(v2d a1, VALTYPE b1, v2d a2, VALTYPE b2) =0;
    // find the points situated at distance b1 from point a1 and at distance b2 from the point a2

    virtual VALTYPE surface_angle(v2d p1, v2d p2, v2d p3) =0;

    // from qpp_object

    virtual qppobject_type gettype() const
    {
      return qtype_manyfold;
    }

    virtual int n_nested() const
    { return 0; }

    virtual qpp_object* nested(int i) const
    { return NULL; }
    
  };


  // --------------------------------------------------------------------
  // The important class of surfaces with diagonal metric tensor
  template <class VALTYPE>
  class orthoparametric_surface : public parametric_surface<VALTYPE>
  {

    using parametric_surface<VALTYPE>::dx_dxi;

  public:

    using parametric_surface<VALTYPE>::geomtol;
    using parametric_surface<VALTYPE>::maxiter;
    using parametric_surface<VALTYPE>::map;
    using parametric_surface<VALTYPE>::project;

    virtual v2d gdiag(const v2d &v) const =0;
    // Square root of the diagonal components of the metric tensor

    virtual lace::matrix2d<VALTYPE> gtensor(const v2d &v) const
    // Covariant metric tensor;
    {
      v2d g = gdiag(v);
      return lace::matrix2d<VALTYPE>(g(0)*g(0), VALTYPE(0), VALTYPE(0), g(1)*g(1));
    }

    virtual v3d normal(const v2d &v) const
    // get the vector normal to the surface
    {
      v3d n1, n2;
      for (int j=0; j<3; j++)
	{
	  n1(j) = dx_dxi(v.x, v.y, j, 0);
	  n2(j) = dx_dxi(v.x, v.y, j, 1);
	}
      return n1%n2 /(norm(n1)*norm(n2));
    }
    
    virtual v2d ruler(const v2d & from, const v2d & direction, 
					  const VALTYPE & distance) const
    // find the point at "distance" from the given "from" point in given "direction"
    {      
      v3d r0 = map(from);
      v3d nperp = normal(from), ntan=0;
      for (int i=0; i<3; i++)
	for (int j=0; j<2; j++)
	  ntan(i) += dx_dxi(from(0),from(1),i,j)*direction(j);
      ntan /= norm(ntan);
      
      v3d n3 = nperp%ntan;
      
      v3d r1, r2, dr;
      v2d p1, p2;

      r1 = r0 + ntan*distance;
      p1 = project(r1);

      while (true)
	{
	  r2 = map(p1);
	  dr = r2 - r0;
	  dr -= n3*scal(n3,dr);
	  dr *= distance/norm(dr);
	  r2 = r0 + dr;
	  p2 = project(r2);

	  if ( norm(r1-r2) < geomtol ) break;

	  r1 = r2;
	  p1 = p2;
	}

      return p2;
    }

    virtual v2d protract(v2d a, v2d b, VALTYPE distance, VALTYPE angle)
    // find the point at "distance" from point1 and at "angle" to the point1-point2 direction
    {
      v3d A = map(a), B = map(b);
      v3d nperp = normal(b), n, nba,nbc;

      nba = A-B;
      nba -= nperp*scal(nba,nperp);
      nba /= norm(nba);

      nbc =  nba*std::cos(angle) + (nperp % nba)*std::sin(angle);
      n =  - nba*std::sin(angle) + (nperp % nba)*std::cos(angle);
      
      //std::cout << "np= " << nperp << " norm = " << norm(nperp) << "\n";
      //std::cout << "nbc= " << nbc << " norm = " << norm(nbc) << "\n";
      //std::cout << "n= " << n << " norm = " << norm(n) << "\n";

      v3d C = B + distance*nbc, C2;
      v2d c = project(C), c2;
      
      int ii = maxiter;
      
      while (ii-->0)
	{
	  C2 = map(c);
	  C2 -= n*scal(n,C2-B);
	  C2 = B + distance*(C2-B)/norm(C2-B);
	  c2 = project(C2);

	  //std::cout << norm(C-C2) << " " << geomtol*pi/180 << "\n";

	  if (norm(C-C2) < geomtol*pi/180) break;

	  C=C2;
	  c=c2;
	}
      return c2;
    }
    
    virtual v2d triangul(v2d a, v2d b, VALTYPE distance, VALTYPE angle)
    {
      v3d A = map(a), B = map(b);
      v3d nperp = normal(b), n, n0;

      n0 = A-B;
      n0 /= norm(n0);
      n = nperp % n0;
      n /= norm(n);

      VALTYPE ca = std::cos(angle), sa = std::sin(angle), AB = norm(A-B);
      v3d C = B + distance*((A-B)*ca/AB + n*sa), C2;
      v2d c = project(C), c2;
      C2 = map(c);
      
      while (true)
	{
	  /*
	  std::cout << A << B << C << "\n";
	  std::cout << distance << " " << norm(B-C)<< "\n";
	  std::cout << angle*180/pi << " " << std::acos(scal(C-B,A-B)/(norm(B-C)*norm(B-A)))*180/pi << "\n";	  
	  */
	  // distance
	  C2 = B + distance*(C2-B)/norm(C2-B);
	  C2 = map(project(C2));

	  //angle
	  n = n0 - (C2-B)*scal(C2-B,n0)/norm2(C2-B);
	  n /= norm(n);

	  VALTYPE r = norm(C2-B),
	    x = (r*ca - scal(C2-B,n0))/(scal(n,n0)-scal(n,C2-B)*ca/r);
	  C2 += x*n;

	  c2 = project(C2);
	  C2 = map(c2);
	  
	  // std::cout << norm(C-C2) << " " <<  geomtol*pi/180 << "\n";
	  if (norm(C-C2) < geomtol*pi/180) break;

	  C=C2;
	  c=c2;
	}
      return c2;
    }

    virtual std::vector<v2d> triangul2b(v2d a1, VALTYPE b1, v2d a2, VALTYPE b2)
    {
      v3d A1 = map(a1), A2 = map(a2);      
      v3d DA = A2 - A1, N1 = DA/norm(DA);

      VALTYPE A = norm(DA);
      VALTYPE x = (b1*b1 - b2*b2 + A*A)/(2*A);
      VALTYPE y = std::sqrt(b1*b1 - x*x);      
      
      std::vector<v2d> res;

      if (b1+b2<A)
	{
	  //std::cout << "triangle rule violated: " << b1 << " " << b2 << " " << A << "\n";
	  return res;
	}

      for (int sgn=-1; sgn<=1; sgn+=2)
	{
	  v2d r, r1;	  
	  v3d R, R1;

	  v3d N2 = N1 % normal((a1+a2)/2) * sgn;

	  int it = maxiter;

	  while(it-- > 0)
	    {
	      R = A1 + N1*x + N2*y;
	      r = project(R);
	      
	      R1 = map(r);
	      N2 = R1 - A1;
	      N2 = N2 - N1*scal(N2,N1);
	      N2 /= norm(N2);

	      //std::cout << norm(R-R1) << "\n";
	      if ( norm(R-R1) < geomtol ) break;
	      
	      r = r1;
	      R = R1;
	    }

	  res.push_back(r);
	}
      return res;
    }

    virtual VALTYPE surface_angle(v2d p1, v2d p2, v2d p3)
    {
      v3d n = normal(p2);
      v3d r1 = map(p1), r2 = map(p2), r3 = map(p3);
      v3d n1 = r1-r2, n2 = r3-r2;

      n1 = n1 - n*scal(n,n1);
      n2 = n2 - n*scal(n,n2);

      n1 /= norm(n1);
      n2 /= norm(n2);

      return std::acos(scal(n1,n2));
    }


  };

  // -----------------------------------------------------------------------------------
  
  template <class VALTYPE>
  class parametric_sphere : public orthoparametric_surface<VALTYPE>{
    
    VALTYPE R;

  protected:
    using parametric_surface<VALTYPE>::_name;
    
  public:

    using parametric_surface<VALTYPE>::geomtol;
    using parametric_surface<VALTYPE>::maxiter;

    parametric_sphere(const VALTYPE & _R)
    { 
      R=_R;
      geomtol=default_geomtol;
      maxiter = default_maxiter;
    }

    // limits of the parametric domain    
    virtual v2d parmin() const 
    {
      return v2d( 0, 0);
    }

    virtual v2d parmax() const
    {
      return v2d( pi, 2*pi);
    }

    virtual v3d map(const v2d &v) const
    // get the point on the surface corresponding to xi and eta parameters values
    {
      VALTYPE st = std::sin(v(0));
      return v3d(R*st*std::cos(v(1)), R*st*std::sin(v(1)), R*std::cos(v(0)));
    }

    virtual v2d project(const v3d & r) const
    // get the point on surface closest to r
    {
      return v2d(std::acos(r.z()/norm(r)), atanxy(r.x(),r.y()) );
    }

    virtual VALTYPE dx_dxi(const VALTYPE & theta, const VALTYPE & phi, int i, int j) const
    // derivatives of cartesian coondinates over parameters
    {
      if (j==0)
	{
	  if (i==0)
	    return R*std::cos(theta)*std::cos(phi);
	  else if (i==1)
	    return R*std::cos(theta)*std::sin(phi);
	  else if (i==2)
	    return -R*std::sin(theta);
	}
      else if (j==1)
	{
	  if (i==0)
	    return -R*std::sin(theta)*std::sin(phi);
	  else if (i==1)
	    return R*std::sin(theta)*std::cos(phi);
	  else if (i==2)
	    return VALTYPE(0);
	}
      //fixme - i,j range checking
    }
    
    v2d gdiag(const v2d &v) const
    {	
      return v2d(R, R*std::sin(v.x));
    }
 
    // derived from qpp_object
    virtual STRING category() const
    {
      return "sphere";
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      // fixme - write all data 
      for (int k=0; k<offset; k++) os << " ";
      os << "sphere";
      if (_name != "")
	os << " " << _name;
      os << "(" << R << ")";
      if (offset>0)
	os << ";\n";
      
    }

  };

  // -----------------------------------------------------------------------------------------------

  template <class VALTYPE>
  class parametric_torus : public orthoparametric_surface<VALTYPE>{

    VALTYPE a,b;
    v3d origin, axis;
    lace::matrix3d<VALTYPE> Rot;
    
  protected:
    using parametric_surface<VALTYPE>::_name;

  public:

    using parametric_surface<VALTYPE>::geomtol;
    using parametric_surface<VALTYPE>::maxiter;

    parametric_torus( VALTYPE _a, VALTYPE _b, STRING __name = "") : origin(0,0,0), axis(0,0,1)
    {
      a = _a; 
      b = _b;
      Rot = VALTYPE(1);
      _name = __name;
      geomtol = default_geomtol;
      maxiter = default_maxiter;
    }

    parametric_torus( VALTYPE _a, VALTYPE _b, v3d _origin, 
		      v3d _axis, STRING __name = "") 
    {
      a = _a; 
      b = _b;
      origin = _origin;
      axis = _axis;
      
      axis = axis/norm(axis);
      v3d n( axis.y(), -axis.x(), 0);
      VALTYPE phi = std::acos(axis.z());

      Rot = lace::RotMtrx(n,phi);
      _name = __name;
      geomtol = default_geomtol;
      maxiter = default_maxiter;
    }

    virtual v2d parmin() const
    {
      return v2d(VALTYPE(0),VALTYPE(0));
    }
    virtual v2d parmax() const
    {
      return v2d(2*pi,2*pi);
    }

    virtual v3d map(const v2d &v) const
    // get the point on the surface corresponding to xi and eta parameters values
    {
      v3d r;
      VALTYPE theta = v.x, phi = v.y;
      r.z() = b*std::sin(theta);
      r.x() = a - b*std::cos(theta);
      r.y() = r.x()*std::sin(phi);
      r.x() *= std::cos(phi);

      return origin + Rot*r;
    }

    virtual v2d project(const v3d & r) const
    // get the point on surface closest to r
    {
      v3d r1 = invert(Rot)*(r-origin);
      VALTYPE phi = atanxy(r1.x(),r1.y());
      VALTYPE theta = atanxy(a-std::sqrt(r1.x()*r1.x()+r1.y()*r1.y()), r1.z());
      return v2d(theta,phi);
    }

    virtual VALTYPE dx_dxi(const VALTYPE & theta, const VALTYPE & phi, int i, int j) const
    // derivatives of cartesian coondinates over parameters
    {
      if (j==0)
	{
	  if (i==0)
	    return  b*std::sin(theta)*std::cos(phi);
	  else if (i==1)
	    return  b*std::sin(theta)*std::sin(phi);
	  else if (i==2)
	    return  b*std::cos(theta);
	}
      else if (j==1)
	{
	  if (i==0)
	    return -(a - b*std::cos(theta))*std::sin(phi);
	  else if (i==1)
	    return  (a - b*std::cos(theta))*std::cos(phi);
	  else if (i==2)
	    return VALTYPE(0);
	}
      //fixme - i,j range checking      
    }

    v2d gdiag(const v2d &v) const
    {	
      return v2d(b, a - b*std::cos(v.x));
    }
 
    // derived from qpp_object
    virtual STRING category() const
    {
      return "torus";
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
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

  template <class VALTYPE>
  class parametric_plane : public orthoparametric_surface<VALTYPE>{

    v3d origin, axis;
    lace::matrix3d<VALTYPE> Rot;
    
  protected:
    using parametric_surface<VALTYPE>::_name;

  public:

    using parametric_surface<VALTYPE>::geomtol;
    using parametric_surface<VALTYPE>::maxiter;

    parametric_plane(STRING __name = "") : origin(0,0,0), axis(0,0,1)
    {
      Rot = VALTYPE(1);
      _name = __name;
      geomtol = default_geomtol;
      maxiter = default_maxiter;
    }

    parametric_plane( v3d _origin, v3d _axis, STRING __name = "") 
    {
      origin = _origin;
      axis = _axis;
      
      axis = axis/norm(axis);
      v3d n( axis.y(), -axis.x(), 0);
      VALTYPE phi = std::acos(axis.z());

      Rot = lace::RotMtrx(n,phi);
      _name = __name;
      geomtol = default_geomtol;
      maxiter = default_maxiter;
    }

    virtual v2d parmin() const
    {
      return v2d(VALTYPE(0),VALTYPE(0));
    }
    virtual v2d parmax() const
    {
      return v2d(VALTYPE(0),VALTYPE(0));
    }

    virtual v3d map(const v2d &v) const
    // get the point on the surface corresponding to xi and eta parameters values
    {
      v3d r;
      r.x() = v.x;
      r.y() = v.y;
      r.z() = VALTYPE(0);

      return origin + Rot*r;
    }

    virtual v2d project(const v3d & r) const
    // get the point on surface closest to r
    {
      v3d r1 = invert(Rot)*(r-origin);
      return v2d(r1.x(),r1.y());
    }

    virtual VALTYPE dx_dxi(const VALTYPE & theta, const VALTYPE & phi, int i, int j) const
    // derivatives of cartesian coondinates over parameters
    {
      return Rot(i,j);
      //fixme - i,j range checking      
    }

    v2d gdiag(const v2d &v) const
    {	
      return v2d(VALTYPE(1),VALTYPE(1));
    }
 
    // derived from qpp_object
    virtual STRING category() const
    {
      return "plane";
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      // fixme - write all data 
      for (int k=0; k<offset; k++) os << " ";
      os << "plane";
      if (_name != "")
	os << " " << _name;
      if (offset>0)
	os << ";\n";
      
    }

  };

  // ---------------------------------------------------------------------

  template <class VALTYPE>
  void decl2surf(qpp_declaration * decl, parametric_surface<VALTYPE> & surf)
  {}


  /*
  template <class VALTYPE, class charT=std::string::value_type , class traits = std::char_traits<charT> >
  class parametric_plane : public parametric_surface<VALTYPE,charT,traits>{

    using typename qpp_object<charT,traits>::string;
    //    using parametric_surface<VALTYPE,charT,traits>::parm2xyz;

    v3d origin,axis1,axis2;
    
  protected:
    using parametric_surface<VALTYPE,charT,traits>::_name;

  public:

    parametric_plane( string __name = "") : origin(0,0,0), axis1(1,0,0), axis2(0,1,0)
    {
      _name = __name;
    }

    parametric_plane( v3d _origin, v3d _axis1,  
		      v3d _axis2, string __name = "")
    {
      origin = _origin;
      axis1 = _axis1;
      axis2 = _axis2;
      _name = __name;
    }

    virtual v3d parm2xyz(VALTYPE x, VALTYPE y)
    {
      return origin + axis1*x + axis2*y;
    }

    virtual v2d xyz2parm(v3d r)
    {}
    // get the point on surface closest to r

    virtual v2d ruler(v2d from, v2d direction, 
				    VALTYPE distance)
    {
      return from + distance*direction/norm(direction);
    }

    virtual v2d protractor(v2d point1, v2d point2, 
					 VALTYPE distance, VALTYPE alpha)
    {
      v2d delta0 = point1-point2;
      VALTYPE beta = atanxy(delta0.x, delta0.y);
      v2d n( std::cos(alpha+beta), std::sin(alpha+beta) );
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

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0)
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
  */

#undef v2d
#undef v3d

};

#endif
