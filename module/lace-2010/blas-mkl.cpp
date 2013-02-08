#include "blas.hpp"
#include <mkl.h>

namespace _lace_storage{

  // --------------- axpy -----------------
  
  template<>
  void axpy<double>(int n, double a, double *x, int incx, double *y, int incy)
  { daxpy(&n,&a,x,&incx,y,&incy); }

  template<>
  void axpy<float>(int n, float a, float *x, int incx, float *y, int incy)
  { saxpy(&n,&a,x,&incx,y,&incy); }

  template<>
  void axpy<lace::fcomplex>(int n, lace::fcomplex a, lace::fcomplex *x, int incx, lace::fcomplex *y, int incy)
  { caxpy(&n, (MKL_Complex8*)(&a), (MKL_Complex8*)x, &incx, (MKL_Complex8*)y, &incy); }

  template<>
  void axpy<lace::dcomplex>(int n, lace::dcomplex a, lace::dcomplex *x, int incx, lace::dcomplex *y, int incy)
  { zaxpy(&n, (MKL_Complex16*)(&a), (MKL_Complex16*)x, &incx, (MKL_Complex16*)y, &incy); }

  // ---------------- scal -----------------

  template<>
  void scal<float>(int n, float alpha, float *y, int incy)
  { sscal(&n, &alpha, y, &incy); }

  template<>
  void scal<double>(int n, double alpha, double *y, int incy)
  { dscal(&n, &alpha, y, &incy); }

  template<>
  void scal<lace::fcomplex>(int n, lace::fcomplex alpha, lace::fcomplex *y, int incy)
  { cscal(&n, (MKL_Complex8*)(&alpha), (MKL_Complex8*)y, &incy); }

  template<>
  void scal<lace::dcomplex>(int n, lace::dcomplex alpha, lace::dcomplex *y, int incy)
  { zscal(&n, (MKL_Complex16*)(&alpha), (MKL_Complex16*)y, &incy); }

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
  { scopy(&n, x, &incx, y, &incy); }

  template<>
  void copy<double>(int n, double *x, int incx, double *y, int incy)
  { dcopy(&n, x, &incx, y, &incy); }

  template<>
  void copy<lace::fcomplex>(int n, lace::fcomplex *x, int incx, lace::fcomplex *y, int incy)
  { ccopy(&n, (MKL_Complex8*)x, &incx, (MKL_Complex8*)y, &incy); }

  template<>
  void copy<lace::dcomplex>(int n, lace::dcomplex *x, int incx, lace::dcomplex *y, int incy)
  { zcopy(&n, (MKL_Complex16*)x, &incx, (MKL_Complex16*)y, &incy); }

  // --------------------------------- mulmm ----------------------------------

  const int _transp = 0x0100,
            _herm = 0x0200;

  inline char blas_op(int op)
  {
    if (op == 0)
      return 'N';
    else if (op == _transp)
      return 'T';
    else if (op == _herm)
      return 'C';
  }


  template<>
  void mulmm<float,rectang,rectang,rectang>(matrix_shape shpa, float *A, 
					    matrix_shape shpb, float *B, 
					    matrix_shape shpc, float *C,
					    float alpha, float beta, 
					    int opa, int opb)
  {
    char transa = blas_op(opa), transb = blas_op(opb);
    int m = shpc.n;
    int n = shpc.m;
    int k = ((opa & (_transp|_herm)) != 0) ? shpa.n : shpa.m;
// void sgemm(const char *transa, const char *transb, const MKL_INT *m, const MKL_INT *n, const MKL_INT *k,
//            const float *alpha, const float *a, const MKL_INT *lda, const float *b, const MKL_INT *ldb,
//            const float *beta, float *c, const MKL_INT *ldc);

    sgemm(&transa, &transb, &m, &n, &k, &alpha, A, &shpa.n, B, &shpb.n, &beta, C, &shpc.n);
  }
  
  template<>
  void mulmm<double,rectang,rectang,rectang>(matrix_shape shpa, double *A, 
					     matrix_shape shpb, double *B, 
					     matrix_shape shpc, double *C,
					     double alpha, double beta,
					     int opa, int opb)
  {
    char transa = blas_op(opa), transb = blas_op(opb);
    int m = shpc.n;
    int n = shpc.m;
    int k = ((opa & (_transp|_herm)) != 0) ? shpa.n : shpa.m;
    //    std::cout << " dgemm parameters:\n " << transa << " " << transb << " " << m << " " << n << " " << k << " "<< alpha << " " << A <<" "<<shpa.n << " "<< B << " " << shpb.n << " " <<beta << " " << C<< " "<< shpc.n;
    dgemm(&transa, &transb, &m, &n, &k, &alpha, A, &shpa.n, B, &shpb.n, &beta, C, &shpc.n);
  }
  
  template<>
  void mulmm<lace::fcomplex,rectang,rectang,rectang>(matrix_shape shpa, lace::fcomplex *A, 
						     matrix_shape shpb, lace::fcomplex *B, 
						     matrix_shape shpc, lace::fcomplex *C,
						     lace::fcomplex alpha, lace::fcomplex beta,
						     int opa, int opb)
  {
    char transa = blas_op(opa), transb = blas_op(opb);
    int m = shpc.n;
    int n = shpc.m;
    int k = ((opa & (_transp|_herm)) != 0) ? shpa.n : shpa.m;
    cgemm(&transa, &transb, &m, &n, &k, (MKL_Complex8*)(&alpha), (MKL_Complex8*)A, &shpa.n, 
	  (MKL_Complex8*)B, &shpb.n, (MKL_Complex8*)(&beta), (MKL_Complex8*)C, &shpc.n);
  }
  
  template<>
  void mulmm<lace::dcomplex,rectang,rectang,rectang>(matrix_shape shpa, lace::dcomplex *A, 
						     matrix_shape shpb, lace::dcomplex *B, 
						     matrix_shape shpc, lace::dcomplex *C,
						     lace::dcomplex alpha, lace::dcomplex beta,
						     int opa, int opb)
  {
    char transa = blas_op(opa), transb = blas_op(opb);
    int m = shpc.n;
    int n = shpc.m;
    int k = ((opa & (_transp|_herm)) != 0) ? shpa.n : shpa.m;
    zgemm(&transa, &transb, &m, &n, &k, (MKL_Complex16*)(&alpha), (MKL_Complex16*)A, &shpa.n, 
	  (MKL_Complex16*)B, &shpb.n, (MKL_Complex16*)(&beta), (MKL_Complex16*)C, &shpc.n);
  }
  
//   template<>
//   void mulmm<float,symmetric,rectang,rectang>(matrix_shape shpa, float *A, 
// 					      matrix_shape shpb, float *B, 
// 					      matrix_shape shpc, float *C,
// 					      float alpha, float beta, 
// 					      int opa, int opb){}
  
//   template<>
//   void mulmm<double,symmetric,rectang,rectang>(matrix_shape shpa, double *A, 
// 					       matrix_shape shpb, double *B, 
// 					       matrix_shape shpc, double *C,
// 					       double alpha, double beta,
// 					       int opa, int opb){}
//   template<>
//   void mulmm<float,rectang,symmetric,rectang>(matrix_shape shpa, float *A, 
// 					      matrix_shape shpb, float *B, 
// 					      matrix_shape shpc, float *C,
// 					      float alpha, float beta, 
// 					      int opa, int opb){}
  
//   template<>
//   void mulmm<double,rectang,symmetric,rectang>(matrix_shape shpa, double *A, 
// 					       matrix_shape shpb, double *B, 
// 					       matrix_shape shpc, double *C,
// 					       double alpha, double beta,
// 					       int opa, int opb){}
  
//   template<>
//   void mulmm<lace::fcomplex,hermitian,rectang,rectang>(matrix_shape shpa, lace::fcomplex *A, 
// 						       matrix_shape shpb, lace::fcomplex *B, 
// 						       matrix_shape shpc, lace::fcomplex *C,
// 						       lace::fcomplex alpha, lace::fcomplex beta,
// 						       int opa, int opb){}
  
//   template<>
//   void mulmm<lace::dcomplex,hermitian,rectang,rectang>(matrix_shape shpa, lace::dcomplex *A, 
// 						       matrix_shape shpb, lace::dcomplex *B, 
// 						       matrix_shape shpc, lace::dcomplex *C,
// 						       lace::dcomplex alpha, lace::dcomplex beta,
// 						       int opa, int opb){}

//   template<>
//   void mulmm<lace::fcomplex,rectang,hermitian,rectang>(matrix_shape shpa, lace::fcomplex *A, 
// 						       matrix_shape shpb, lace::fcomplex *B, 
// 						       matrix_shape shpc, lace::fcomplex *C,
// 						       lace::fcomplex alpha, lace::fcomplex beta,
// 						       int opa, int opb){}
  
//   template<>
//   void mulmm<lace::dcomplex,rectang,hermitian,rectang>(matrix_shape shpa, lace::dcomplex *A, 
// 						       matrix_shape shpb, lace::dcomplex *B, 
// 						       matrix_shape shpc, lace::dcomplex *C,
// 						       lace::dcomplex alpha, lace::dcomplex beta,
// 						       int opa, int opb){}
   

};

