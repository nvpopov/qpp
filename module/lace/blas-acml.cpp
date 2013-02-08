#include "blas.hpp"
#include <acml.h>

namespace _lace_storage{

  // --------------- axpy -----------------
  
  template<>
  void axpy<double>(int n, double a, double *x, int incx, double *y, int incy)
  { daxpy(n,a,x,incx,y,incy); }

  template<>
  void axpy<float>(int n, float a, float *x, int incx, float *y, int incy)
  { saxpy(n,a,x,incx,y,incy); }

  template<>
  void axpy<lace::fcomplex>(int n, lace::fcomplex a, lace::fcomplex *x, int incx, lace::fcomplex *y, int incy)
  { caxpy(n, (complex*)&a, (complex*)x, incx, (complex*)y, incy); }

  template<>
  void axpy<lace::dcomplex>(int n, lace::dcomplex a, lace::dcomplex *x, int incx, lace::dcomplex *y, int incy)
  { zaxpy(n, (doublecomplex*)&a, (doublecomplex*)x, incx, (doublecomplex*)y, incy); }

  // ---------------- scal -----------------

  template<>
  void scal<float>(int n, float alpha, float *y, int incy)
  { sscal(n, alpha, y, incy); }

  template<>
  void scal<double>(int n, double alpha, double *y, int incy)
  { dscal(n, alpha, y, incy); }

  template<>
  void scal<lace::fcomplex>(int n, lace::fcomplex alpha, lace::fcomplex *y, int incy)
  { cscal(n, (complex*)(&alpha), (complex*)y, incy); }

  template<>
  void scal<lace::dcomplex>(int n, lace::dcomplex alpha, lace::dcomplex *y, int incy)
  { zscal(n, (doublecomplex*)(&alpha), (doublecomplex*)y, incy); }

  // ---------------- conj -----------------

  template<>
  void conj<float>(int n, float *y, int incy){}

  template<>
  void conj<double>(int n, double *y, int incy){}

  template<>
  void conj<lace::fcomplex>(int n, lace::fcomplex *x, int incx)
  {
    float *im0 = ((float*)x) + 1;
    scal<float>(n, float(-1), im0, incx*2);
  }

  template<>
  void conj<lace::dcomplex>(int n, lace::dcomplex *x, int incx)
  {
    double *im0 = ((double*)x) + 1;
    scal<double>(n, double(-1), im0, incx*2);
  }

  // ---------------- copy -----------------

  template<>
  void copy<float>(int n, float *x, int incx, float *y, int incy)
  { scopy(n, x, incx, y, incy); }

  template<>
  void copy<double>(int n, double *x, int incx, double *y, int incy)
  { dcopy(n, x, incx, y, incy); }

  template<>
  void copy<lace::fcomplex>(int n, lace::fcomplex *x, int incx, lace::fcomplex *y, int incy)
  { ccopy(n, (complex*)x, incx, (complex*)y, incy); }

  template<>
  void copy<lace::dcomplex>(int n, lace::dcomplex *x, int incx, lace::dcomplex *y, int incy)
  { zcopy(n, (doublecomplex*)x, incx, (doublecomplex*)y, incy); }

};

