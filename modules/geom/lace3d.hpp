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
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
namespace py = pybind11;
#endif

namespace qpp {

  const double tol_equiv = 1e-8;


  template <typename ELEM> using vector2 = Eigen::Matrix<ELEM, 2, 1>;
  //template <typename ELEM> using vector3 = Eigen::Matrix<ELEM, 3, 1>;
  template <typename ELEM> using vector4 = Eigen::Matrix<ELEM, 4, 1>;
  template <typename ELEM, int n> using vectorn = Eigen::Matrix<ELEM, n, 1>;

  template <typename ELEM> using matrix2 = Eigen::Matrix<ELEM, 2, 2>;
  // template <typename ELEM> using matrix3 = Eigen::Matrix<ELEM, 3, 3>;
  template <typename ELEM> using matrix4 = Eigen::Matrix<ELEM, 4, 4>;
  template <typename ELEM, int n> using matrixnn = Eigen::Matrix<ELEM, n, n>;
  template <typename ELEM, int n, int m> using matrixnm = Eigen::Matrix<ELEM, n, m>;


  template<int FIXED_N, int FIXED_M>
  struct check_is_vector3{
    static const bool value = false;
  };

  template<>
  struct check_is_vector3<3, 1>{
    static const bool value = true;
  };

  template<int FIXED_N, int FIXED_M>
  struct check_is_matrix3{
    static const bool value = false;
  };

  template<>
  struct check_is_matrix3<3, 3>{
    static const bool value = true;
  };

  template <typename VALTYPE, int N, int M>
  class generic_matrix : public Eigen::Matrix<VALTYPE, N , M >{
  public:
    static typename numeric_type<VALTYPE>::norm tol_equiv;

    generic_matrix(void):Eigen::Matrix<VALTYPE, N , M >() {}

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    generic_matrix(VALTYPE x, VALTYPE y, VALTYPE z):
      Eigen::Matrix<VALTYPE, N , M >(){
      *this<<x,y,z;
    }

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    generic_matrix(const generic_matrix<VALTYPE, 3, 1> &v1,
                   const generic_matrix<VALTYPE, 3, 1> &v2,
                   const generic_matrix<VALTYPE, 3, 1> &v3):
      Eigen::Matrix<VALTYPE, N , M >(){
      (*this).row(0) = v1;
      (*this).row(1) = v2;
      (*this).row(2) = v3;
    }

    generic_matrix(VALTYPE xyz):Eigen::Matrix<VALTYPE, N , M >(){
      (*this) = generic_matrix<VALTYPE, N , M>::Constant(N, M, xyz);
    }

    template<typename OtherDerived>
    generic_matrix(const Eigen::MatrixBase<OtherDerived>& other)
      :Eigen::Matrix<VALTYPE, N , M >(other){ }

    template<typename OtherDerived>
    generic_matrix& operator=(const Eigen::MatrixBase <OtherDerived>& other){
      this->Eigen::Matrix<VALTYPE, N , M >::operator=(other);
      return *this;
    }

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    const STRING to_string_vec(){
      return fmt::format("[{}, {}, {}]", (*this)[0], (*this)[1], (*this)[2]);
    }

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    const STRING to_string_matr(){
      return fmt::format("[{},\n {},\n {}]",
                         (*this).row(0),
                         (*this).row(1),
                         (*this).row(2));
    }

#ifdef PY_EXPORT
    static const generic_matrix<VALTYPE, N , M> identity_proxy(){
      return generic_matrix<VALTYPE, N , M>::Identity();
    }

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    const generic_matrix<VALTYPE, N , M> normalized_proxy(){
      return (*this).normalized();
    }

    const generic_matrix<VALTYPE, N , M> mul_proxy(const VALTYPE& other){
      generic_matrix<VALTYPE, N , M> _tmv(
            this->Eigen::Matrix<VALTYPE, N , M >::operator*(other));
      return _tmv;
    }

    const generic_matrix<VALTYPE, N , M> div_proxy(const VALTYPE& other){
      generic_matrix<VALTYPE, N , M> _tmv(
            this->Eigen::Matrix<VALTYPE, N , M >::operator/(other));
      return _tmv;
    }

    const generic_matrix<VALTYPE, N , M> sum_proxy
    (const generic_matrix<VALTYPE, N , M>& other){
      generic_matrix<VALTYPE, N , M> _tmv(
            this->Eigen::Matrix<VALTYPE, N , M >::operator+(other));
      return _tmv;
    }

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    const generic_matrix<VALTYPE, N , M> cross_product_proxy
    (const generic_matrix& other){
      return (*this).cross(other);
    }

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    const generic_matrix<VALTYPE, N , M> inverse_proxy(){
      return (*this).inverse();
    }

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    const generic_matrix<VALTYPE, N , M> transpose_proxy(){
      return (*this).transpose();
    }

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    const VALTYPE dot_product_proxy(const generic_matrix<VALTYPE, N , M>& other){
      return (*this).dot(other);
    }

    const generic_matrix<VALTYPE, N , M>
    sub_proxy(const generic_matrix<VALTYPE, N , M>& other){
      generic_matrix<VALTYPE, N , M> _tmv(
            this->Eigen::Matrix<VALTYPE, N , M >::operator-(other));
      return _tmv;
    }

    bool equal_proxy(const generic_matrix<VALTYPE, N , M> & b){
      return ((*this) - b).norm() <=  tol_equiv;
    }

    bool nequal_proxy(const generic_matrix<VALTYPE, N , M> &b){
      return ! ((*this)==b);
    }

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    generic_matrix(const py::list &l){
      //TOODO check
      for (int i=0; i<3; i++)
        (*this)[i] = py::cast<VALTYPE>(l[i]);
    }

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    generic_matrix(const py::tuple &l){
      //TOODO check
      for (int i=0; i<3; i++)
        (*this)[i] = py::cast<VALTYPE>(l[i]);
    }

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    inline VALTYPE py_getitem(int i) const
    { return (*this)[i]; }

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    inline void py_setitem(int i, VALTYPE v)
    { (*this)[i] = v;  }

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    inline VALTYPE py_getx(){return (*this)[0];}

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    inline VALTYPE py_gety(){return (*this)[1];}

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    inline VALTYPE py_getz(){return (*this)[2];}

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    inline void py_setx(VALTYPE v){ (*this)[0]=v;}

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    inline void py_sety(VALTYPE v){ (*this)[1]=v;}

    template<typename = std::enable_if<check_is_vector3<N , M>::value> >
    inline void py_setz(VALTYPE v){ (*this)[2]=v;}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline VALTYPE py_getxx() const {return (*this)(0,0);}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline VALTYPE py_getxy() const {return (*this)(0,1);}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline VALTYPE py_getxz() const {return (*this)(0,2);}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline VALTYPE py_getyx() const {return (*this)(1,0);}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline VALTYPE py_getyy() const {return (*this)(1,1);}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline VALTYPE py_getyz() const {return (*this)(1,2);}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline VALTYPE py_getzx() const {return (*this)(2,0);}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline VALTYPE py_getzy() const {return (*this)(2,1);}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline VALTYPE py_getzz() const {return (*this)(2,2);}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline void py_setxx(VALTYPE v) {(*this)(0,0) = v;}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline void py_setxy(VALTYPE v) {(*this)(0,1) = v;}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline void py_setxz(VALTYPE v) {(*this)(0,2) = v;}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline void py_setyx(VALTYPE v) {(*this)(1,0) = v;}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline void py_setyy(VALTYPE v) {(*this)(1,1) = v;}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline void py_setyz(VALTYPE v) {(*this)(1,2) = v;}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline void py_setzx(VALTYPE v) {(*this)(2,0) = v;}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline void py_setzy(VALTYPE v) {(*this)(2,1) = v;}

    template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
    inline void py_setzz(VALTYPE v) {(*this)(2,2) = v;}


#endif

  };

  template<class VALTYPE>
  using vector3 = generic_matrix<VALTYPE, 3, 1>;

  template<class VALTYPE>
  using matrix3 = generic_matrix<VALTYPE, 3, 3>;

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
    Eigen::ComplexEigenSolver<Eigen::Matrix<VALTYPE, 3 , 3> > ces;
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
    Eigen::ComplexEigenSolver<Eigen::Matrix<VALTYPE, 3 , 3>> ces;
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

  template<class VALTYPE, int N, int M>
  typename numeric_type<VALTYPE>::norm generic_matrix<VALTYPE, N, M>::tol_equiv = 1e-8;
}
#endif
