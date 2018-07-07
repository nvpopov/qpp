#ifndef _LACE3D_H
#define _LACE3D_H
#pragma GCC diagnostic ignored "-Wnarrowing"
#include <cmath>
#include <complex>
#include <ostream>
#include <sstream>
#include <initializer_list>
#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>
#include <data/types.hpp>
#include <consts.hpp>
//#include <lace/complex.hpp>

#ifdef PY_EXPORT
#include <pybind11/pybind11.h>
namespace py = pybind11;
#endif

namespace qpp {

  const double tol_equiv = 1e-8;


  template <typename ELEM> using vector2 = Eigen::Matrix<ELEM, 2, 1>;
  template <typename ELEM> using vector3 = Eigen::Matrix<ELEM, 3, 1>;
  template <typename ELEM> using vector4 = Eigen::Matrix<ELEM, 4, 1>;
  template <typename ELEM, int n> using vectorn = Eigen::Matrix<ELEM, n, 1>;

  template <typename ELEM> using matrix2 = Eigen::Matrix<ELEM, 2, 2>;
  template <typename ELEM> using matrix3 = Eigen::Matrix<ELEM, 3, 3>;
  template <typename ELEM> using matrix4 = Eigen::Matrix<ELEM, 4, 4>;
  template <typename ELEM, int n> using matrixnn = Eigen::Matrix<ELEM, n, n>;
  template <typename ELEM, int n, int m> using matrixnm = Eigen::Matrix<ELEM, n, m>;

  template<class VALTYPE>
  vector3<VALTYPE> gen_vec3(VALTYPE x, VALTYPE y, VALTYPE z){
    vector3<VALTYPE> retvec;
    retvec << x, y, z;
    return retvec;
  }

  template<class VALTYPE>
  matrix3<VALTYPE> gen_matrix3(vector3<VALTYPE> v1,
                               vector3<VALTYPE> v2,
                               vector3<VALTYPE> v3){
    matrix3<VALTYPE> retm;
    retm.row(0) = v1;
    retm.row(1) = v2;
    retm.row(2) = v3;
  }

  template<class VALTYPE>
  matrix3<VALTYPE> RotMtrx(const vector3<VALTYPE> & nn, VALTYPE phi){
    vector3<VALTYPE> n = nn.normalized();
    matrix3<VALTYPE> m1 = Eigen::AngleAxis<VALTYPE>(phi, n).toRotationMatrix();
    return m1;
  }
  template<class VALTYPE>
  matrix3<VALTYPE> gen_matrix(const VALTYPE value){
    matrix3<VALTYPE> retm;
    for (int i = 0; i < 9; i++) retm << value;
    return retm;
  }

  template<class VALTYPE>
  matrix3<VALTYPE> Sigma(const vector3<VALTYPE> & nn){
    vector3<VALTYPE> n = nn.normalized();
    matrix3<VALTYPE> retm;
    retm << 1e0 - 2*n(0)*n(0), -2*n(0)*n(1),      -2*n(0)*n(2),
        -2*n(0)*n(1),      1e0 - 2*n(1)*n(1), -2*n(1)*n(2),
        -2*n(0)*n(2),      -2*n(1)*n(2),      1e0 - 2*n(2)*n(2) ;
    return retm;
  }

  template<class VALTYPE>
  vector3<VALTYPE> solve3(const matrix3<VALTYPE> & A,
                          const vector3<VALTYPE> & b){
    return A.inverse()*b;
  }

  template<class VALTYPE>
  vector3<VALTYPE> diagon3d(const matrix3<VALTYPE> & A){
    Eigen::ComplexEigenSolver<matrix3<VALTYPE> > ces;
    ces.compute(A);
    Eigen::Array<typename numeric_type<VALTYPE>::complex, Eigen::Dynamic, 1> lbd;
    vector3<VALTYPE> lbd_re;
    for (int i = 0; i < 3; i++)
      lbd_re(i) = lbd(i,0).real();
    return lbd_re;
  }

  template<class VALTYPE>
  void diagon3d(vector3<typename numeric_type<VALTYPE>::complex> & eigvals,
                matrix3<typename numeric_type<VALTYPE>::complex> & eigvecs,
                const matrix3<VALTYPE> & A){
    Eigen::ComplexEigenSolver<matrix3<VALTYPE> > ces;
    ces.compute(A);
    eigvals = ces.eigenvalues();
    eigvecs = ces.eigenvectors();
  }

  template<class VALTYPE>
  bool diagon3d(vector3<VALTYPE> & eigvals,
                matrix3<VALTYPE> & eigvecs,
                const matrix3<VALTYPE> & A){
    vector3<typename numeric_type<VALTYPE>::complex> ceigvals;
    matrix3<typename numeric_type<VALTYPE>::complex> ceigvecs;
    VALTYPE eps = vector3<VALTYPE>::tol_equiv;

    bool res = true;
    diagon3d(ceigvals,ceigvecs,A);

    for (int i=0; i<3; i++){
        eigvals(i) = ceigvals(i).real();
        if ( std::abs(ceigvals(i).imag()) > eps )
          res = false;
      }

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++){
          eigvecs(i,j) = ceigvecs(i,j).real();
          if ( std::abs(ceigvecs(i,j).imag()) > eps )
            res = false;
        }
    return res;
  }
}
#endif
