#ifndef _LACE_ENGINE_H
#define _LACE_ENGINE_H

//#include <lace/matrix.hpp>
#include <lace/wizard.hpp>
#include <lace/blas.hpp>
#include <typeinfo>

namespace _lace_main{

  using _lace_storage::rectang;    
  using _lace_storage::symmetric;  
  using _lace_storage::hermitian;  
  using _lace_storage::banddiag;   
  using _lace_storage::symmband;   
  using _lace_storage::hermband;   
  using _lace_storage::triang;      

  using _lace_storage::dense;
  using _lace_storage::sparse;

  using _lace_expressions::_transp;
  using _lace_expressions::_herm;
  using _lace_expressions::matrix;
  using _lace_expressions::vector;


  // ------------------------------------------------------------
  //             convertor_matrix_engine implementation 
  // ------------------------------------------------------------
  //
  //-------------------------------------------------------------------------//
  //             The default convertor should work in most cases

  
  template<class VALTYPE, matrix_type MTP_DST, matrix_type MTP_SRC>
  class copy_m_convertor : public default_m_convertor<VALTYPE,MTP_DST,MTP_SRC>
  {
  public:
    
    //    copy_matrix_convertor(){}
    
    //--------------------------------------------------------------------------------//
    
    virtual void convert( matrix_expression<VALTYPE> &dest, matrix_expression<VALTYPE> &src)
    {
      matrix<VALTYPE,MTP_DST> *DST = (matrix<VALTYPE,MTP_DST>*)(&dest);  
      matrix<VALTYPE,MTP_SRC> *SRC = (matrix<VALTYPE,MTP_SRC>*)(&src);

	//assert( is_convertable(DST->shape(),SRC->shape()) && "Invalid matrix conversion" );
      // Use copy method
      DST->copy(*SRC);
    }

  };

  //--------------------------------------------------------------------------------//
  

  template<class VALTYPE, vector_type VTP_DST, vector_type VTP_SRC>
  class default_v_convertor : public v_convertor_engine<VALTYPE>{
  public:
    
    virtual bool is_convertable(vector_shape dest, vector_shape src)
    {
      //fixme - think if this is sufficient!
      return dest.n == src.n;
    }

//     virtual vector_shape reshape(vector_shape src) =0;

//     virtual vector_shape reshape(vector_expression<VALTYPE> &src) =0;

    virtual void convert( vector_expression<VALTYPE> &dest, sub Iu,
			  vector_expression<VALTYPE> &src,  sub Iv)
    {
      //fixme -- insert proper convertability check
      //      assert(is_convertable(dest.shape(), src.shape()));
      assert( is_convertable( wizard<VALTYPE>::V(dest.vtype()).VI_shape(dest.shape(),Iu),
			      wizard<VALTYPE>::V(src.vtype()). VI_shape(src.shape(),Iv)) );

      vector<VALTYPE,VTP_DST> *DEST = (vector<VALTYPE,VTP_DST>*)(&dest);
      vector<VALTYPE,VTP_SRC> *SRC  = (vector<VALTYPE,VTP_DST>*)(&src);

      int iv = Iv.begin();
      for (int iu = Iu.begin(); iu <= Iu.end(); iu += Iu.inc)
	{
	  if ( DEST -> unique(iu))
	    (*DEST)(iu) = (*SRC)(iv);
	  iv += Iv.inc;
	}
    }
    
    virtual void convert( vector_expression<VALTYPE> &dest, vector_expression<VALTYPE> &src)
    {
      assert(is_convertable(dest.shape(), src.shape()));
      vector<VALTYPE,VTP_DST> *DEST = (vector<VALTYPE,VTP_DST>*)(&dest);
      vector<VALTYPE,VTP_SRC> *SRC  = (vector<VALTYPE,VTP_DST>*)(&src);

      for (int i=0; i < SRC -> size(); i++)
	if ( DEST -> unique(i))
	  (*DEST)(i) = (*SRC)(i);
    }

//     virtual vector_expression<VALTYPE>& convert(vector_expression<VALTYPE> &src) =0;
  };


  template<class VALTYPE>
  class rectang_mm_binary : public default_mm_binary<VALTYPE,rectang,rectang>{
  public:

    //    rectang_summator(){}

    virtual void MpM(matrix_expression<VALTYPE> &a, matrix_expression<VALTYPE> &b, 
		     VALTYPE beta, int OP = 0)
    {
      matrix<VALTYPE,rectang> *A = (matrix<VALTYPE,rectang>*)(&a);
      matrix<VALTYPE,rectang> *B = (matrix<VALTYPE,rectang>*)(&b);

      if ( OP == 0)
	_lace_storage::axpy( A->size(0) * A->size(1), beta, &((*B)(0,0)), 1, &((*A)(0,0)), 1);
      else if ( OP == _transp )
	for (int i = 0; i < A->size(1); i++)
	  _lace_storage::axpy( A->size(0), beta, &((*B)(i,0)), B->size(0), &((*A)(0,i)), 1);
      else if ( OP == _herm)
	{       
	  // fixme -- think how to do this efficiently

// 	  for (int i = 0; i < A->size(0); i++)
// 	    for (int j = 0; j < A->size(1); j++)
// 	      (*A)(i,j) += beta * lace::conj((*B)(j,i));
	  int n = A->size(0); 
	  int m = A->size(1); 
	  VALTYPE *cj = new VALTYPE [n];
	  for (int i = 0; i < m; i++)
	    {
	      _lace_storage::copy(n, &((*B)(i,0)), B->size(0), cj, 1 );
	      _lace_storage::conj(n, cj, 1);
	      _lace_storage::axpy(n, beta, cj, 1, &((*A)(0,i)), 1);
	    }
	  delete cj;
	}
    }
  };


  template<class VALTYPE, vector_type VTP, matrix_type MTP>
  class default_vm_binary : public vm_binary_engine<VALTYPE>{
  public:

    virtual bool MIj_conform(vector_shape vshp, matrix_shape mshp, sub I, int j)
    {}

    virtual bool MiJ_conform(vector_shape vshp, matrix_shape mshp, int i, sub J)
    {}

    virtual void MIj(vector_expression<VALTYPE> &v, matrix_expression<VALTYPE> &M, sub I, int j)
    {}

    virtual void MiJ(vector_expression<VALTYPE> &v, matrix_expression<VALTYPE> &M, int i, sub J)
    {}

    virtual vector_shape MxV_shape(matrix_shape mshp, vector_shape vshp)
    {
      if (mshp.m == vshp.n)
	return vector_shape(dense,mshp.n);
      else
	return vector_shape();
    }

//     virtual bool V2D_conform(matrix_shape mshp, vector_shape vshp) =0;

//     virtual bool D2V_conform(vector_shape vshp, matrix_shape mshp) =0;

//     virtual void V2D(matrix_expression<VALTYPE> &M, vector_expression<VALTYPE> &v) =0;

//     virtual void D2V(vector_expression<VALTYPE> &v, matrix_expression<VALTYPE> &M) =0;

  };
       

  template<class VALTYPE,matrix_type MTPA,matrix_type MTPB,matrix_type MTPC>
  class blas_mmm_ternary : public default_mmm_ternary<VALTYPE,MTPA,MTPB,MTPC> {
  public:
    
    virtual void MxM(matrix_expression<VALTYPE> &a, matrix_expression<VALTYPE> &b, 
		     matrix_expression<VALTYPE> &c, VALTYPE alpha, VALTYPE beta,
		     int OP_B = 0, int OP_C = 0)
    {
      matrix<VALTYPE,MTPA> *A = (matrix<VALTYPE,MTPA>*)(&a);
      matrix<VALTYPE,MTPB> *B = (matrix<VALTYPE,MTPB>*)(&b);
      matrix<VALTYPE,MTPC> *C = (matrix<VALTYPE,MTPC>*)(&c);  

      _lace_storage::mulmm<VALTYPE,MTPA,MTPB,MTPC>(B->shape(), B->ptr(0,0),
						   C->shape(), C->ptr(0,0), 
						   A->shape(), A->ptr(0,0),					   
						   beta,alpha, OP_B, OP_C);
    }

  };

  // -----------------------------------------------------------------------------------------

  */
};

#endif
