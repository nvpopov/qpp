#ifndef LACE3D_H
#define LACE3D_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
//#include <pybind11/stl.h>
#include <pybind11/iostream.h>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

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

namespace qpp {

  //const double tol_equiv = 1e-8;

  template <typename ELEM> using vector2 = Eigen::Matrix<ELEM, 2, 1>;
  template <typename ELEM> using _vector3 = Eigen::Matrix<ELEM, 3, 1>;
  template <typename ELEM> using vector4 = Eigen::Matrix<ELEM, 4, 1>;
  template <typename ELEM, int n> using vectorn = Eigen::Matrix<ELEM, n, 1>;

  template <typename ELEM> using matrix2 = Eigen::Matrix<ELEM, 2, 2>;
  // template <typename ELEM> using matrix3 = Eigen::Matrix<ELEM, 3, 3>;
  template <typename ELEM> using matrix4 = Eigen::Matrix<ELEM, 4, 4>;
  template <typename ELEM, int n> using matrixnn = Eigen::Matrix<ELEM, n, n>;
  template <typename ELEM, int n, int m> using matrixnm = Eigen::Matrix<ELEM, n, m>;


  template<int FIXED_N, int FIXED_M>
  struct check_is_vector3 {
      static const bool value = false;
  };

  template<>
  struct check_is_vector3<3, 1> {
      static const bool value = true;
  };

  template<int FIXED_N, int FIXED_M>
  struct check_is_matrix3 {
      static const bool value = false;
  };

  template<>
  struct check_is_matrix3<3, 3> {
      static const bool value = true;
  };

  template <typename VALTYPE, int N, int M>
  class generic_matrix : public Eigen::Matrix<VALTYPE, N , M > {
    public:
      static typename numeric_type<VALTYPE>::norm tol_equiv;
      static generic_matrix unity;

      static typename numeric_type<VALTYPE>::norm tol_equiv_default(){

        if constexpr(std::is_same<VALTYPE,float>::value) {
          return 1e-5;
        }
        if constexpr(std::is_same<VALTYPE,double>::value) {
          return 1e-8;
        }

        return 1e-8;
      }

      generic_matrix(void):Eigen::Matrix<VALTYPE, N , M >() {}

      template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      generic_matrix(VALTYPE x, VALTYPE y, VALTYPE z):
        Eigen::Matrix<VALTYPE, N , M >() {
        (*this)(0) = x;
        (*this)(1) = y;
        (*this)(2) = z;
      }

      template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      generic_matrix(const generic_matrix<VALTYPE, 3, 1> &v1,
                     const generic_matrix<VALTYPE, 3, 1> &v2,
                     const generic_matrix<VALTYPE, 3, 1> &v3):
        Eigen::Matrix<VALTYPE, N , M >() {
        (*this).row(0) = v1;
        (*this).row(1) = v2;
        (*this).row(2) = v3;
      }

      template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      generic_matrix(const VALTYPE v00, const VALTYPE v01, const VALTYPE v02,
                     const VALTYPE v10, const VALTYPE v11, const VALTYPE v12,
                     const VALTYPE v20, const VALTYPE v21, const VALTYPE v22):
        Eigen::Matrix<VALTYPE, N , M >() {

        (*this).row(0)(0) = v00;
        (*this).row(0)(1) = v01;
        (*this).row(0)(2) = v02;

        (*this).row(1)(0) = v10;
        (*this).row(1)(1) = v11;
        (*this).row(1)(2) = v12;

        (*this).row(2)(0) = v20;
        (*this).row(2)(1) = v21;
        (*this).row(2)(2) = v22;

      }

      generic_matrix(VALTYPE xyz):Eigen::Matrix<VALTYPE, N , M >() {
        (*this) = generic_matrix<VALTYPE, N , M>::Constant(N, M, xyz);
      }

      template<typename OtherDerived>
      generic_matrix(const Eigen::MatrixBase<OtherDerived>& other)
        :Eigen::Matrix<VALTYPE, N , M >(other) { }

      template<typename OtherDerived>
      generic_matrix& operator=(const Eigen::MatrixBase <OtherDerived>& other) {
        this->Eigen::Matrix<VALTYPE, N , M >::operator=(other);
        return *this;
      }

      inline bool operator==(const generic_matrix<VALTYPE, N , M> & b) const {
        return (*this-b).norm() < generic_matrix::tol_equiv;
      }

      inline bool operator!=(const generic_matrix<VALTYPE, N , M> &b) const {
        return ! ((*this)==b);
      }

      //template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      STRING_EX to_string_vec() const {
        return fmt::format("[ {:8.6f}, {:8.6f}, {:8.6f} ]",
                           (*this)[0], (*this)[1], (*this)[2]);
      }

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      STRING_EX to_string_matr() const {

        return fmt::format("[ {:8.6f}, {:8.6f}, {:8.6f}\n"
                           "   {:8.6f}, {:8.6f}, {:8.6f}\n"
                           "   {:8.6f}, {:8.6f}, {:8.6f} ]",
                           (*this).row(0)(0),
                           (*this).row(0)(1),
                           (*this).row(0)(2),
                           (*this).row(1)(0),
                           (*this).row(1)(1),
                           (*this).row(1)(2),
                           (*this).row(2)(0),
                           (*this).row(2)(1),
                           (*this).row(2)(2));

      }


#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
      static generic_matrix<VALTYPE, N , M> identity_proxy(){
        return generic_matrix<VALTYPE, N , M>::Identity();
      }

      // template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      generic_matrix<VALTYPE, N , M> normalized_proxy(){
        return (*this).normalized();
      }

      generic_matrix<VALTYPE, N , M> mul_proxy(const VALTYPE& other){
        generic_matrix<VALTYPE, N , M> _tmv(
              this->Eigen::Matrix<VALTYPE, N , M >::operator*(other));
        return _tmv;
      }

      generic_matrix<VALTYPE, N , M> div_proxy(const VALTYPE& other){
        generic_matrix<VALTYPE, N , M> _tmv(
              this->Eigen::Matrix<VALTYPE, N , M >::operator/(other));
        return _tmv;
      }

      generic_matrix<VALTYPE, N , M> pow_proxy(const VALTYPE& other){
        return (*this).pow(other);
      }

      generic_matrix<VALTYPE, N , M> sum_proxy
      (const generic_matrix<VALTYPE, N , M>& other){
        generic_matrix<VALTYPE, N , M> _tmv(
              this->Eigen::Matrix<VALTYPE, N , M >::operator+(other));
        return _tmv;
      }

      generic_matrix<VALTYPE, N , M> cross_product_proxy
      (const generic_matrix& other){
        return (*this).cross(other);
      }

      generic_matrix<VALTYPE, N , M> inverse_proxy(){
        return (*this).inverse();
      }

      generic_matrix<VALTYPE, 3 , 1> mv_mul_proxy
      (const generic_matrix<VALTYPE, 3 , 1> & other){
        return (*this)*other;
      }

      const generic_matrix<VALTYPE, 3 , 3> mm_mul_proxy
      (const generic_matrix<VALTYPE, 3 , 3> & other){
        return (*this)*other;
      }

      const generic_matrix<VALTYPE, N , M> transpose_proxy(){
        return (*this).transpose();
      }

      VALTYPE dot_product_proxy(const generic_matrix<VALTYPE, N , M>& other){
        return (*this).dot(other);
      }

      generic_matrix<VALTYPE, N , M> sub_proxy(const generic_matrix<VALTYPE, N , M>& other){
        generic_matrix<VALTYPE, N , M> _tmv(
              this->Eigen::Matrix<VALTYPE, N , M >::operator-(other));
        return _tmv;
      }

      bool equal_proxy(const generic_matrix<VALTYPE, N , M> & b){
        return (*this) == b;
      }

      bool nequal_proxy(const generic_matrix<VALTYPE, N , M> &b){
        return (*this) != b;
      }

      generic_matrix(const py::list &l){
        //TOODO check
        for (int i=0; i<3; i++)
          (*this)[i] = py::cast<VALTYPE>(l[i]);
      }

      generic_matrix(const py::tuple &l){
        //TOODO check
        for (int i=0; i<3; i++)
          (*this)[i] = py::cast<VALTYPE>(l[i]);
      }

      //template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      inline VALTYPE py_getitem_v(int i) const
      { return (*this)[i]; }

      //template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      inline void py_setitem_v(int i, VALTYPE v)
      { (*this)[i] = v;  }

      //template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      inline VALTYPE py_getx(){return (*this)[0];}

      //template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      inline VALTYPE py_gety(){return (*this)[1];}

      //template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      inline VALTYPE py_getz(){return (*this)[2];}

      //template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      inline void py_setx(VALTYPE v){ (*this)[0]=v;}

      //template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      inline void py_sety(VALTYPE v){ (*this)[1]=v;}

      //template<typename = std::enable_if<check_is_vector3<N , M>::value> >
      inline void py_setz(VALTYPE v){ (*this)[2]=v;}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline VALTYPE py_getxx() const {return (*this)(0,0);}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline VALTYPE py_getxy() const {return (*this)(0,1);}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline VALTYPE py_getxz() const {return (*this)(0,2);}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline VALTYPE py_getyx() const {return (*this)(1,0);}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline VALTYPE py_getyy() const {return (*this)(1,1);}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline VALTYPE py_getyz() const {return (*this)(1,2);}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline VALTYPE py_getzx() const {return (*this)(2,0);}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline VALTYPE py_getzy() const {return (*this)(2,1);}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline VALTYPE py_getzz() const {return (*this)(2,2);}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setxx(VALTYPE v) {(*this)(0,0) = v;}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setxy(VALTYPE v) {(*this)(0,1) = v;}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setxz(VALTYPE v) {(*this)(0,2) = v;}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setyx(VALTYPE v) {(*this)(1,0) = v;}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setyy(VALTYPE v) {(*this)(1,1) = v;}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setyz(VALTYPE v) {(*this)(1,2) = v;}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setzx(VALTYPE v) {(*this)(2,0) = v;}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setzy(VALTYPE v) {(*this)(2,1) = v;}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setzz(VALTYPE v) {(*this)(2,2) = v;}

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline VALTYPE py_getitem(py::tuple I) const{
        int i = py::cast<int>(I[0]), j = py::cast<int>(I[1]);
        return (*this)(i,j);
      }

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setitem(py::tuple I, VALTYPE v){
        int i = py::cast<int>(I[0]), j = py::cast<int>(I[1]);
        (*this)(i,j) = v;
      }

      // template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline generic_matrix<VALTYPE, 3, 1> py_getitemv(int i) const{
        return (*this)(i);
      }

      //template<typename = std::enable_if<check_is_matrix3<N , M>::value> >
      inline void py_setitemv(int i, const generic_matrix<VALTYPE, 3, 1> & v){
        (*this).row(i) = v;
      }


#endif

  };

  template<class VALTYPE>
  using vector3 = generic_matrix<VALTYPE, 3, 1>;

  template<class VALTYPE>
  using matrix3 = generic_matrix<VALTYPE, 3, 3>;

  template <typename VALTYPE>
  std::ostream& operator<< (std::ostream& stream, const vector3<VALTYPE> &gm) {
    stream << gm.to_string_vec();
    return stream;
  }

  template <typename VALTYPE>
  std::ostream& operator<< (std::ostream& stream, const matrix3<VALTYPE> &gm) {
    stream << gm.to_string_matr();
    return stream;
  }

  template<class VALTYPE>
  matrix3<VALTYPE> mat4_to_mat3(const matrix4<VALTYPE> _inmat){
    matrix3<VALTYPE> _res;
    for (int i = 0; i < 3; i++)
      for (int q = 0; q < 3; q++)
        _res(i,q) = _inmat(i,q);
    return _res;
  }

  template<class VALTYPE>
  vector3<VALTYPE> gen_vec3(VALTYPE x, VALTYPE y, VALTYPE z){
    vector3<VALTYPE> retvec;
    retvec(0) = x;
    retvec(1) = y;
    retvec(2) = z;
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
    for (int i = 0; i < 3; i++)
      for (int q = 0; q < 3; q++)
        retm(i,q) = value;
    return retm;
  }

  template<class VALTYPE>
  matrix3<VALTYPE> Sigma(const vector3<VALTYPE> & nn) {

    vector3<VALTYPE> n = nn.normalized();
    matrix3<VALTYPE> retm;
    retm.row(0)[0] = 1e0 - 2*n(0)*n(0);
    retm.row(0)[1] = -2*n(0)*n(1);
    retm.row(0)[2] = -2*n(0)*n(2);

    retm.row(1)[0] = -2*n(0)*n(1);
    retm.row(1)[1] = 1e0 - 2*n(1)*n(1);
    retm.row(1)[2] = -2*n(1)*n(2);

    retm.row(2)[0] = -2*n(0)*n(2);
    retm.row(2)[1] = -2*n(1)*n(2);
    retm.row(2)[2] =  1e0 - 2*n(2)*n(2) ;

    return retm;
  }

  template<class VALTYPE>
  vector3<VALTYPE> solve3(const matrix3<VALTYPE> & A,
                          const vector3<VALTYPE> & b){
    return A.inverse() * b;
  }

  template<class VALTYPE>
  vector3<VALTYPE> solve3(const vector3<VALTYPE> & A0,
                          const vector3<VALTYPE> & A1,
                          const vector3<VALTYPE> & A2,
                          const vector3<VALTYPE> & b){
    matrix3<VALTYPE> A(A0, A1, A2);
    return solve3(A, b);
  }

  template<class VALTYPE>
  vector3<typename numeric_type<VALTYPE>::complex> solve_cubeq(VALTYPE a, VALTYPE b, VALTYPE c,
                                                               VALTYPE d) {
    // Solves ax^3 + bx^2 + cx + d = 0, a is assumed to be nonzero

    typename numeric_type<VALTYPE>::complex I(0,1);
    VALTYPE s32 = .5*std::sqrt(3.);
    VALTYPE eps = vector3<VALTYPE>::tol_equiv;
    vector3<typename numeric_type<VALTYPE>::complex> res(0);

    b /= a;
    c /= a;
    d /= a;
    VALTYPE Q = (b*b-3*c)/9, R = d/2 - b*c/6 + b*b*b/27;
    int sgnr = (R>0) ? 1 : -1;

    if ( std::abs(Q) < eps ) {
        VALTYPE R13 = std::pow(2*std::abs(R),1./3)*sgnr;
        res = {-1, VALTYPE(.5) + s32*I, VALTYPE(.5) - s32*I };
        res *= R13;
        for (int i=0; i<3; i++)
          res(i) -= b/3;
      }

    else if (R*R<Q*Q*Q) {
        // three real roots
        VALTYPE SQ = std::sqrt(Q);
        VALTYPE theta = std::acos(R/(Q*SQ));
        res = {-2*SQ*std::cos(theta/3)-b/3,
               -2*SQ*std::cos((theta + 2 * VALTYPE(pi))/3)-b/3,
               -2*SQ*std::cos((theta + 4 * VALTYPE(pi))/3)-b/3};
      }

    else {
        VALTYPE A = -std::pow(std::abs(R)+std::sqrt(R*R-Q*Q*Q), 1./3)*sgnr;
        VALTYPE B=0;
        if ( std::abs(A)>eps) B = Q/A;
        res = { -b/3 + A + B,
                -b/3 - (A + B)/2 + I*s32*(A - B),
                -b/3 - (A + B)/2 - I*s32*(A - B)};
      }

    return res;
  }

  template<class VALTYPE>
  vector3<VALTYPE> diagon3d(const matrix3<VALTYPE> & A){
    VALTYPE b = A.row(0)[0] + A.row(1)[1] + A.row(2)[2];
    VALTYPE c = A.row(0)[1]*A.row(1)[0] + A.row(1)[2]*A.row(2)[1] + A.row(2)[0]*A.row(0)[2] -
                A.row(0)[0]*A.row(1)[1] - A.row(1)[1]*A.row(2)[2] - A.row(2)[2]*A.row(0)[0];
    VALTYPE d = A.determinant();

    vector3<typename numeric_type<VALTYPE>::complex> lbd = solve_cubeq(-VALTYPE(1e0),b,c,d);
    vector3<VALTYPE> lbd_re;
    for (int i=0; i<3; i++)
      lbd_re(i) = lbd(i).real();
    return lbd_re;
  }

  template<class VALTYPE>
  void diagon3d(vector3<typename numeric_type<VALTYPE>::complex> & eigvals,
                matrix3<typename numeric_type<VALTYPE>::complex> & eigvecs,
                const matrix3<VALTYPE> & A) {

    typename numeric_type<VALTYPE>::real eps = vector3<VALTYPE>::tol_equiv;

    VALTYPE offd = A(0,1)*A(0,1) + A(1,0)*A(1,0) + A(1,2)*A(1,2) +
                   A(2,1)*A(2,1) + A(2,0)*A(2,0) + A(0,2)*A(0,2);

    if ( offd < eps*eps ) {
        // Already diagonal

        int i0=0,i1,i2=2;

        for (int i=0; i<3; i++){
            if ( A(i,i) < A(i0,i0) )
              i0 = i;
            if ( A(i,i) > A(i2,i2) )
              i2 = i;
          }
        for (int i=0; i<3; i++)
          if (i!=i0 && i!=i2) i1 = i;

        eigvals = { A(i0,i0), A(i1,i1), A(i2,i2)};
        eigvecs = { {0,0,0}, {0,0,0}, {0,0,0} };
        eigvecs(i0,0) = VALTYPE(1);
        eigvecs(i1,1) = VALTYPE(1);
        eigvecs(i2,2) = VALTYPE(1);
        return;
      }


    VALTYPE b = A(0,0) + A(1,1) + A(2,2);
    VALTYPE c = A(0,1)*A(1,0) + A(1,2)*A(2,1) + A(2,0)*A(0,2) -
                A(0,0)*A(1,1) - A(1,1)*A(2,2) - A(2,2)*A(0,0);
    VALTYPE d = A.determinant();

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
    else {
        ndiff = 2;
        if ( std::abs(e1-e2) <= eps ) {
            e=e2; e2=e0; e0=e;
          }
        else if ( std::abs(e2-e0) <= eps ) {
            e=e2; e2=e1; e1=e;
          }
        eigvals = {e0,e1,e2};
      }

    //std::cout << "eigvals after sorting = " << eigvals << "\n";

    matrix3<typename numeric_type<VALTYPE>::complex> AA, B, E;
    vector3<typename numeric_type<VALTYPE>::complex> n0,n1,n2;
    vector3<typename numeric_type<VALTYPE>::complex> B0, B1, B2, Bi;

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
        AA(i,j)=A(i,j);

    E.setZero();
    E(0,0) = 1;
    E(1,1) = 1;
    E(2,2) = 1;

    if (ndiff==1) {
        // e0, e1 and e2
        //std::cout << "e0==e1==e2\n";
        n0 = {1,0,0};
        n1 = {0,1,0};
        n2 = {0,0,1};
      }
    else if (ndiff==2)  {
        // e0 == e1 != e2

        //std::cout << "e0==e1!=e2\n";
        B = AA - e2*E;
        B /= B.norm();
        //B = B.T();

        int i=0;

        B0 = B.row(0);
        B1 = B.row(1);
        B2 = B.row(2);
        Bi = B.row(i);

        if (B1.norm() > B1.norm()) i=1;
        if (B2.norm() > Bi.norm()) i=2;
        n0 = Bi / Bi.norm();

        i=0;

        Bi = B.row(i);
        if ((B1 - (n0 * (n0.dot(B1))) ).norm() > (B0 - (n0 * (n0.dot(B0))) ).norm()) {
            i=1;
            Bi = B.row(i);
          }

        if ((B2-n0 * n0.dot(B2) ).norm() > (Bi-n0 * n0.dot(Bi)).norm()) {
            i=2;
            Bi = B.row(i);
          }

        n1 = Bi-n0 * n0.dot(Bi);
        n1 /= n1.norm();

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

        n2 = n0.cross(n1);

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
        B0 = B.row(0);
        B1 = B.row(1);
        B2 = B.row(2);
        Bi = B.row(i);

        if (B1.norm() > B0.norm()) {
            i=1;
            Bi = B.row(i);
          }

        if (B2.norm() > Bi.norm()) {
            i=2;
            Bi = B.row(i);
          }

        n0 = Bi / Bi.norm();

        B = (AA - e0*E);
        B /= B.norm();
        B = B*(AA - e2*E);
        B /= B.norm();
        //B = B.T();

        i=0;

        B0 = B.row(0);
        B1 = B.row(1);
        B2 = B.row(2);
        Bi = B.row(i);

        if ( (B1-n0 * n0.dot(B1)).norm() > (B0-n0 * n0.dot(B1)).norm() ) {
            i=1;
            Bi = B.row(i);
          }


        if ( (B2-n0 * n0.dot(B2)).norm() > (Bi-n0 * n0.dot(Bi)).norm() ) {
            i=2;
            Bi = B.row(i);
          }

        n1 = Bi - n0*n0.dot(Bi);
        n1 /= n1.norm();

        //n1 = B(i)/norm(B(i));

        B = (AA - e0*E);
        B /= B.norm();
        B = B*(AA - e1*E);
        B /= B.norm();
        //B = B.T();

        i=0;
        B0 = B.row(0);
        B1 = B.row(1);
        B2 = B.row(2);
        Bi = B.row(i);

        if ((B1-n0*n0.dot(B1)-n1*n1.dot(B1)).norm() > (B0-n0*n0.dot(B0)-n1*n1.dot(B0)).norm() ) {
            i=1;
            Bi = B.row(i);
          }

        if ( (B2-n0*n0.dot(B2)-n1*n1.dot(B2)).norm() >
             (Bi-n0*n0.dot(Bi)-n1*n1.dot(Bi)).norm() ) {
            i=2;
            Bi = B.row(i);
          }

        n2 = Bi-n0*n0.dot(Bi)-n1*n1.dot(Bi);
        n2 /= n2.norm();
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

    matrix3<typename numeric_type<VALTYPE>::complex> eigvecs1;
    vector3<typename numeric_type<VALTYPE>::complex> eigvals1 = eigvals;

    for (int i=0; i<3; i++) {
        eigvecs1(i,0) = n0(i);
        eigvecs1(i,1) = n1(i);
        eigvecs1(i,2) = n2(i);
      }

    // sort eigenvalues in ascending order
    int i0=0,i1,i2=0;

    for (int i=0; i<3; i++){
        if ( eigvals(i).real() < eigvals(i0).real() )
          i0 = i;
        if ( eigvals(i).real() > eigvals(i2).real() )
          i2 = i;
      }
    for (int i=0; i<3; i++)
      if (i!=i0 && i!=i2) i1 = i;

    eigvals(0) = eigvals1(i0);
    eigvals(1) = eigvals1(i1);
    eigvals(2) = eigvals1(i2);

    for (int i=0; i<3; i++) {
        eigvecs(i,0) = eigvecs1(i,i0);
        eigvecs(i,1) = eigvecs1(i,i1);
        eigvecs(i,2) = eigvecs1(i,i2);
      }

  }

  // ---------------------------------------------------------

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
  typename numeric_type<VALTYPE>::norm generic_matrix<VALTYPE, N, M>::tol_equiv =
      generic_matrix<VALTYPE, N, M>::tol_equiv_default();

  /*
  template<int N, int M>
  float generic_matrix<float, N, M>::tol_equiv = 1e-10;

  template<int N, int M>
  double generic_matrix<double, N, M>::tol_equiv = 1e-5;


  template<> float generic_matrix<float, 3,3>::tol_equiv = 1e-10;

  template<> double generic_matrix<double, 3,3>::tol_equiv = 1e-5;

  template<> float generic_matrix<float, 3,1>::tol_equiv = 1e-10;

  template<> double generic_matrix<double, 3,1>::tol_equiv = 1e-5;
  */

  template<class VALTYPE, int N, int M>
  generic_matrix<VALTYPE, N, M> generic_matrix<VALTYPE, N, M>::unity =
      generic_matrix<VALTYPE, N, M>::Identity();

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  template<class VALTYPE>
  inline vector3<VALTYPE> py_diagon3dv(const matrix3<VALTYPE> & A)
  { return diagon3d(A); }

  template<class VALTYPE>
  inline void py_diagon3dm(
      vector3<typename numeric_type<VALTYPE>::complex> & eigvals,
      matrix3<typename numeric_type<VALTYPE>::complex> & eigvecs,
      const matrix3<VALTYPE> & A)
  { diagon3d(eigvals,eigvecs,A); }

  template<class VALTYPE>
  inline bool py_diagon3dreal(vector3<VALTYPE> & eigvals,
                              matrix3<VALTYPE> & eigvecs,
                              const matrix3<VALTYPE> & A)
  { return diagon3d(eigvals,eigvecs,A); }



  template<class VALTYPE>
  inline vector3<VALTYPE> py_solve3m(const matrix3<VALTYPE> & A,
                                     const vector3<VALTYPE> & b)
  { return solve3(A,b);}

  template<class VALTYPE>
  inline vector3<VALTYPE> py_solve3v(const vector3<VALTYPE> & A0,
                                     const vector3<VALTYPE> & A1,
                                     const vector3<VALTYPE> & A2,
                                     const vector3<VALTYPE> & b)
  { return solve3(A0,A1,A2,b);}

  template<class VALTYPE>
  inline matrix3<VALTYPE> py_rotmtrx_v(const vector3<VALTYPE> & nn,
                                       VALTYPE phi)
  {  return RotMtrx(nn,phi);}

  template<class VALTYPE>
  inline matrix3<VALTYPE> py_rotmtrx_t(const py::tuple & nn, VALTYPE phi)
  {  return RotMtrx(vector3<VALTYPE>(nn),phi);}

  template<class VALTYPE>
  inline matrix3<VALTYPE> py_rotmtrx_l(const py::list & nn, VALTYPE phi)
  {  return RotMtrx(vector3<VALTYPE>(nn),phi);}

  template<class VALTYPE>
  inline matrix3<VALTYPE> py_sigma_v(const vector3<VALTYPE> & nn)
  {  return Sigma(nn);}

  template<class VALTYPE>
  inline matrix3<VALTYPE> py_sigma_t(const py::tuple & nn)
  {  return Sigma(vector3<VALTYPE>(nn));}

  template<class VALTYPE>
  inline matrix3<VALTYPE> py_sigma_l(const py::list & nn)
  {  return Sigma(vector3<VALTYPE>(nn));}

#endif

}

#endif
