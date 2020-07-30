#ifndef QPP_SUBSPACE_H
#define QPP_SUBSPACE_H

#include <symm/transform.hpp>
#include <Eigen/Dense>

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

namespace qpp{

  template <class REAL> class subspace3;

  // -------------------------------------------------------------

  template<class REAL>
  subspace3<REAL> invariant_subspace(const matrix4<REAL> & R)
  {
    REAL eps = subspace3<REAL>::tol_equiv;
    matrix4<REAL> I = matrix4<REAL>::Identity();
    matrix4<REAL> RI = R-I;
    auto lu = RI.fullPivLu();
    lu.setThreshold(eps);
    matrix<REAL> x = lu.kernel();
    return subspace3(x);
  }

  template<class REAL, bool BOUND>
  subspace3<REAL> invariant_subspace(const rotrans<REAL,BOUND> & R)
  {
    return invariant_subspace(rotrans4d(R));
  }

  // -------------------------------------------------------------

  template <class REAL>
  class subspace3 {
  public:

    static REAL tol_equiv;
    
    int dim;
    vector3<REAL> point, axis;
    matrix<REAL> X, orths;
    matrix4<REAL> projector;

    void find_projector(){
      projector = matrix4<REAL>::Zero();
      for (int i=0; i<X.cols(); i++)
	projector += X.col(i)*X.col(i).transpose();
    }

    void XGS(){
      for (int i=0; i< X.cols(); i++)
	{
	  for (int j=0; j<i; j++)
	    X.col(i) -= X.col(j)*X.col(i).dot(X.col(j));
	  X.col(i).normalize();
	}      
    }
    
    void find_dim()
    {
      REAL eps = tol_equiv;
      dim = X.cols()-1;
      bool empty = true;
      for (int i=0; i<X.cols(); i++)
	if (std::abs(X(3,i))>eps)
	  {
	    empty = false;
	    break;
	  }
      if (empty)
	dim = -1;
    }

    void find_axes()    
    {
      REAL eps = tol_equiv;

      if (dim == -1 || dim == 3)
	{
	  point = axis = {0,0,0};
	  if (dim==3)
	    orths = matrix4<REAL>::Identity();
	}
      else if (dim==0)
	{
	  axis = {0,0,0};
	  point = {X(0,0),X(1,0),X(2,0)};
	  point /= X(3,0);
	  orths = X;
	}
      else
	{
	  int i=0;
	  while (abs(X(3,i)) < eps) i++;
	  vector4<REAL> n = X.col(i);
	  n /= n(3);
	  matrix<REAL> Y(4,X.cols());
	  for (int j=0; j<Y.cols()-1; j++)
	    {
	      Y.col(j) = X.col(j + (j<i ? 0:1) );
	      Y.col(j) -= n*Y.col(j)(3);
	    }
	  Y.col(Y.cols()-1) = n;
	  for (int j=0; j < Y.cols(); j++)
	    {
	      for (int k=0; k<j; k++)
		Y.col(j) -= Y.col(k)*Y.col(j).dot(Y.col(k));
	      Y.col(j).normalize();
	    }      
	
	  //	std::cout << std::endl << std::endl << Y << std::endl<< std::endl ;
	  orths = Y;
	  n = Y.col(Y.cols()-1);
	  point = {n(0),n(1),n(2)};
	  point /= n(3);
	  if (dim==1)
	    axis = vector3<REAL>(Y(0,0),Y(1,0),Y(2,0));
	  else
	    axis = vector3<REAL>(Y(0,0),Y(1,0),Y(2,0)).cross(vector3<REAL>(Y(0,1),Y(1,1),Y(2,1)));
      }
  }

    subspace3(int __dim, const vector3<REAL> & __pt,
	      const vector3<REAL> & __n = vector3<REAL>(0)) {
      dim = __dim;
      point = __pt;
      axis = __n;
      axis /= axis.norm();
      if (dim == 0)
	{
	  X = matrix<REAL>(4,1);
	  X << point, 1;	  
	}
      else if (dim == 1)
	{
	  X = matrix<REAL>(4,2);
	  X.col(0) << axis, 0;
	  X.col(1) << point, 1;
	}
      else if (dim == 2)
	{
	  X = matrix<REAL>(4,3);
	  vector3<REAL> n = {1,0,0};
	  if ( (n.cross(axis)).norm() < tol_equiv )
	    n = {0,1,0};
	  vector3<REAL> n1,n2;
	  n1 = n.cross(axis);
	  n2 = n1.cross(axis);
	  X.col(0) << n1, 0;
	  X.col(1) << n2, 0;
	  X.col(2) << point,1;
	}
      else if (dim==3)
	{
	  X = matrix4<REAL>::Identity();
	}
      XGS();
      std::cout << "X=" << std::endl << X << std::endl;
      orths = X;
      find_projector();
    }

    subspace3(const matrix<REAL> &_X){
      X = _X;
      XGS();
      find_dim();
      find_axes();
      find_projector();
    }
    
    subspace3(const subspace3<REAL> & L){
      X = L.X;
      point = L.point;
      axis = L.axis;
      dim = L.dim;
      orths = L.orths;
      projector = L.projector;
    }
    
    subspace3 & operator=(const subspace3<REAL> & L){
      dim = L.dim;
      point = L.point;
      axis = L.axis;
      X = L.X;
      orths = L.orths;
      projector = L.projector;
      return *this;
    }

    bool within (const vector3<REAL> & x) const {
      vector4<REAL> xx(x(0),x(1),x(2),1),
	diff = xx - projector*xx;
      return diff.norm() < tol_equiv;
    }

    bool within (const subspace3<REAL> & L) const {
      auto diff = projector*L.projector - L.projector;
      return diff.norm() < tol_equiv;
    }

    bool operator==(const subspace3<REAL> & L ) const {
      auto diff = projector - L.projector;
      return diff.norm() < tol_equiv;
    }

    bool operator!= (const subspace3<REAL> & L ) const {
      return !(*this == L);
    }

    subspace3<REAL> operator& (const subspace3<REAL> & L) const {
      matrix4<REAL> P = projector*L.projector;
      return invariant_subspace(P);	
    }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

    bool py_point_within (const vector3<REAL> & x) const {
      return within(x);
    }

    bool py_subspace_within (const subspace3<REAL> & L) const {
      return within(L);
    }    
    
    static void py_export(py::module m, const char * pyname){
      py::class_<subspace3<REAL> >(m, pyname)
	.def(py::init<int, const vector3<REAL> &, const vector3<REAL> &>(),
	     py::arg("dim"), py::arg("point"), py::arg("axis") = vector3<REAL>(0))
	.def(py::init<const matrix<REAL> &>(), py::arg("X"))
	.def("within", & subspace3<REAL>::py_point_within)
	.def("within", & subspace3<REAL>::py_subspace_within)
	.def_readwrite("dim", & subspace3<REAL>::dim)
	.def_readwrite("point", & subspace3<REAL>::point)
	.def_readwrite("axis", & subspace3<REAL>::axis)
	.def_readwrite("projector", & subspace3<REAL>::projector)
	.def_readwrite("orths", & subspace3<REAL>::orths)
	.def_readwrite_static("tol_equiv", & subspace3<REAL>::tol_equiv)
	.def("__eq__", [](const subspace3<REAL> &self, const subspace3<REAL> & other) -> bool
	     {return self == other; })
	.def("__ne__", [](const subspace3<REAL> &self, const subspace3<REAL> & other) -> bool
	     {return self != other; })
	.def("__and__", [](const subspace3<REAL> &self, const subspace3<REAL> & other) -> subspace3<REAL>
	     {return self & other; })
	;
    }

#endif

  };

  template<class REAL>
  REAL subspace3<REAL>::tol_equiv = vector3<REAL>::tol_equiv;
    
};

#endif
