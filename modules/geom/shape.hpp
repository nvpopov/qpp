#ifndef _QPP_SHAPE_H
#define _QPP_SHAPE_H

#include <mathf/constants.hpp>
#include <data/qppdata.hpp>
#include <geom/geom.hpp>
#include <lace/lace3d.hpp>

#define v2d lace::vector2d<VALTYPE>
#define v3d lace::vector3d<VALTYPE>

namespace qpp{

  // ------------------ 3D primitives ------------------------

  template <class VALTYPE>
  class qpp_shape : public qpp_object{

  public:

    qpp_shape(const STRING & __name = "", qpp_object * __owner = NULL):
      qpp_object(__name,__owner)
    {}

    virtual bool within(const v3d & r) const =0;
    // Answers the question whether the r point is situated within the shape
    
    virtual v3d rmin() const =0;
    virtual v3d rmax() const =0;
    // Minimal & maximal cartesian coordinates of the shape

    virtual v3d fmin(const periodic_cell<3,VALTYPE> &v) const =0;
    virtual v3d fmax(const periodic_cell<3,VALTYPE> &v) const =0;
    // Minimal & maximal fractional coordinates of the shape for given translation vectors v

    virtual VALTYPE volume() const =0;

    virtual void scale(VALTYPE s) =0;
    virtual void move(const v3d & v) =0;

    // -------------------------------------

    virtual int n_nested() const
    { return 0;}

    virtual qpp_object* nested(int i) const
    { return NULL;}

    virtual qppobject_type gettype() const
    { return qtype_shape;}
    
  };

  // -------------------------------------------------------------------

  template <class VALTYPE>
  class qpp_shape_parallel : public qpp_shape<VALTYPE>{

    v3d crn, a[3];

    void fill_corners(v3d *corners) const
    {
      corners[0] = crn;
      corners[1] = crn+a[0];
      corners[2] = crn+a[1];
      corners[3] = crn+a[0]+a[1];
      corners[4] = crn+a[2];
      corners[5] = crn+a[0]+a[2];
      corners[6] = crn+a[1]+a[2];
      corners[7] = crn+a[0]+a[1]+a[2];
    }

  public:

    using qpp_shape<VALTYPE>::name;

    qpp_shape_parallel(const v3d & a1, const v3d & a2, const v3d & a3, const v3d & r0, 
		       const STRING & __name = "", qpp_object * __owner = NULL) :
      qpp_shape<VALTYPE>(__name, __owner)
    {
      crn = r0;
      a[0] = a1;
      a[1] = a2;
      a[2] = a3;
    }

    qpp_shape_parallel(const v3d & a1, const v3d & a2, const v3d & a3, 
		       const STRING & __name = "", qpp_object * __owner = NULL):
      qpp_shape<VALTYPE>(__name, __owner)
    {
       crn = 0e0;
      a[0] = a1;
      a[1] = a2;
      a[2] = a3;
    }
    
    qpp_shape_parallel(VALTYPE a1, VALTYPE a2, VALTYPE a3, 
		       const STRING & __name = "", qpp_object * __owner = NULL):
      qpp_shape<VALTYPE>(__name, __owner)
    {
      crn = 0e0;
      a[0] = v3d(a1,  0e0, 0e0);
      a[0] = v3d(0e0, a2,  0e0);
      a[0] = v3d(0e0, 0e0, a3);
    }

    qpp_shape_parallel(const qpp_shape_parallel<VALTYPE> & s)
    {
      crn = s.crn;
      a[0] = s.a[0];
      a[1] = s.a[1];
      a[2] = s.a[2];
    }

    virtual STRING category() const
    { return "parallel";}

    

    virtual qpp_object * copy() const
    {
      return new qpp_shape_parallel<VALTYPE>(*this);
    }

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int i=0; i<offset; i++)
	os << " ";
      os << "parallel";
      if (name() != "")
	os << " " << name();
      os << "( a=" << a[0] << ", b=" << a[1] << ", c=" << a[2] << ", corner=" << crn << ");\n";
    }

    // --------------------------------------------------

    virtual bool within(const v3d & r) const
    {
      if ( scal(r-crn,a[1]%a[2])*scal(r-crn-a[0],a[1]%a[2]) > 0e0)
	return false;
      if ( scal(r-crn,a[2]%a[0])*scal(r-crn-a[1],a[2]%a[0]) > 0e0)
	return false;
      if ( scal(r-crn,a[0]%a[1])*scal(r-crn-a[2],a[0]%a[1]) > 0e0)
	return false;
      return true;
    }
    
    virtual v3d rmin() const
    {
      v3d corners[8];
      fill_corners(corners);

      v3d res=crn;
      for (int i=0; i<8; i++)
	for (int j=0; j<3; j++)
	  if ( res(j) > corners[i](j))
	    res(j) = corners[i](j);

      return res;
    }

    virtual v3d rmax() const
    {
      v3d corners[8];
      fill_corners(corners);

      v3d res=crn;
      for (int i=0; i<8; i++)
	for (int j=0; j<3; j++)
	  if ( res(j) < corners[i](j))
	    res(j) = corners[i](j);

      return res;
    }

    virtual v3d fmin(const periodic_cell<3,VALTYPE> &v) const
    {
      v3d corners[8];
      fill_corners(corners);

      for (int i=0; i<8; i++)
	corners[i] = v.cart2frac(corners[i]);

      v3d res=corners[0];
      for (int i=1; i<8; i++)
	for (int j=0; j<3; j++)
	  if ( res(j) > corners[i](j))
	    res(j) = corners[i](j);
      
      return res;
    }

    virtual v3d fmax(const periodic_cell<3,VALTYPE> &v) const
    {
      v3d corners[8];
      fill_corners(corners);

      for (int i=0; i<8; i++)
	corners[i] = v.cart2frac(corners[i]);

      v3d res=corners[0];
      for (int i=1; i<8; i++)
	for (int j=0; j<3; j++)
	  if ( res(j) < corners[i](j))
	    res(j) = corners[i](j);
      
      return res;
    }

    // Minimal & maximal fractional coordinates of the shape for given translation vectors v

    virtual VALTYPE volume() const
    {
      return std::abs(det(a[0], a[1], a[2]));
    }

    virtual void scale(VALTYPE s)
    {
      a[0] *= s;
      a[1] *= s;
      a[2] *= s;
    }

    virtual void move(const v3d & v)
    {
      crn += v;
    }

  };

  // ------------------ 3D primitives ------------------------

  template <class VALTYPE>
  class qpp_shape_sphere : public qpp_shape<VALTYPE>{

    VALTYPE R;
    v3d r0;

  public:

    using qpp_shape<VALTYPE>::name;

    qpp_shape_sphere(VALTYPE _R, const STRING & __name = "", qpp_object * __owner = NULL):
      qpp_shape<VALTYPE>(__name, __owner)
    {
      R = _R;
      r0 = 0e0;
    }

    qpp_shape_sphere(VALTYPE _R, const v3d & _r0, 
		     const STRING & __name = "", qpp_object * __owner = NULL):
      qpp_shape<VALTYPE>(__name, __owner)
    {
      R = _R;
      r0 = _r0;
    }

    virtual STRING category() const
    { return "sphere";}

    virtual void write(std::basic_ostream<CHAR,TRAITS> &os, int offset=0) const
    {
      for (int i=0; i<offset; i++)
	os << " ";
      os << "sphere";
      if (name() != "")
	os << " " << name();
      os << "( R=" << R << ", center" << r0 << ");\n";
    }

    // --------------------------------------------------

    virtual bool within(const v3d & r) const
    {
      return norm(r-r0) <= R;
    }
    
    virtual v3d rmin() const
    {
      return r0 - v3d(R,R,R);
    }

    virtual v3d rmax() const
    {
      return r0 + v3d(R,R,R);
    }

    virtual v3d fmin(const periodic_cell<3,VALTYPE> &v) const
    {
      lace::matrix3d<VALTYPE> A(v[0],v[1],v[2]);
      lace::matrix3d<VALTYPE> B = invert(A);

      v3d res = 0e0;
      for (int i=0; i<3; i++)
	for (int j=0; j<3; j++)
	  res(i) += B(i,j)*B(i,j);
      for (int i=0; i<3; i++)
	res(i) = std::sqrt(res(i));
      return B*r0 - res;
    }

    virtual v3d fmax(const periodic_cell<3,VALTYPE> &v) const
    {      
      lace::matrix3d<VALTYPE> A(v[0],v[1],v[2]);
      lace::matrix3d<VALTYPE> B = invert(A);

      v3d res = 0e0;
      for (int i=0; i<3; i++)
	for (int j=0; j<3; j++)
	  res(i) += B(i,j)*B(i,j);
      for (int i=0; i<3; i++)
	res(i) = std::sqrt(res(i));
      return B*r0 + res;
    }

    // Minimal & maximal fractional coordinates of the shape for given translation vectors v

    virtual VALTYPE volume() const
    {
      return 4*qpp::pi*R*R*R/3;
    }

    virtual void scale(VALTYPE s)
    {
      R *= s;
    }

    virtual void move(const v3d & v)
    {
      r0 += v;
    }

  };

  // ----------------------------------------------------------------

  template<class VALTYPE>
  class qpp_geom_builder : public qpp_object {

  public:

  };

};

#undef v3d
#undef v2d

#endif
