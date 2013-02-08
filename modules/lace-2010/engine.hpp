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
  //
  //             unary_matrix_engine implementation 
  // ------------------------------------------------------------

  template<class VALTYPE, matrix_type MTRTYPE>
  class default_m_unary : public m_unary_engine<VALTYPE> {
  public:

    //    default_m_unary(){};

    virtual matrix_expression<VALTYPE>& create(matrix_shape shp)
    {
      return * new matrix<VALTYPE,MTRTYPE>(shp);
    }

    virtual void scale(matrix_expression<VALTYPE> &a, VALTYPE s)
    {
      matrix<VALTYPE,MTRTYPE> *A = (matrix<VALTYPE,MTRTYPE>*)(&a);
      A -> scale(s);
    }

    virtual void setval(matrix_expression<VALTYPE> &a, VALTYPE s)
    {
      matrix<VALTYPE,MTRTYPE> *A = (matrix<VALTYPE,MTRTYPE>*)(&a);
      (*A) = s;
    }

    virtual void scale(matrix_expression<VALTYPE> &a, VALTYPE s, sub I, sub J)
    {
      // fixme - use BLAS
      matrix<VALTYPE,MTRTYPE> *A = (matrix<VALTYPE,MTRTYPE>*)(&a);
      for (int i = I.i1; i<=I.i2; i+=I.inc)
	for (int j = J.i1; j<=J.i2; j+=J.inc)
	  if ( A -> unique(i,j) ) *(A -> ptr(i,j)) *= s;	  
    }

    virtual void setval(matrix_expression<VALTYPE> &a, VALTYPE s, sub I, sub J)
    {
      // fixme - use BLAS
      matrix<VALTYPE,MTRTYPE> *A = (matrix<VALTYPE,MTRTYPE>*)(&a);
      for (int i = I.i1; i<=I.i2; i+=I.inc)
	for (int j = J.i1; j<=J.i2; j+=J.inc)
	  if ( A -> unique(i,j) ) (*A)(i,j) = s;	  
    }

    virtual matrix_shape T_shape(matrix_shape shp)
    {
      if ( is_banded(MTRTYPE) )
	return matrix_shape( MTRTYPE, shp.m, shp.n, shp.kl, shp.ku );
      else if ( MTRTYPE == triang )
	{
	  matrix_shape::uplo tag;
	  if (shp.tag == matrix_shape::lower) tag = matrix_shape::upper;
	  else tag = matrix_shape::lower;

	  return matrix_shape( MTRTYPE, shp.n, tag);
	}
      else
	return matrix_shape( MTRTYPE, shp.m, shp.n);
    }

    virtual matrix_shape MIJ_shape(matrix_shape shp, sub I, sub J )
    {
      // fixme -- detalize the cases when resulting shape is not rectang
      if (lace::globals::debug)
	{
	  std::cout << "Submatrix shape requested: base shape is "; shp.debug();
	  std::cout << "I = "; I.debug();      std::cout << " J = "; J.debug();
	  std::cout << "\n";
	}

      I.reduce(0, shp.n);
      J.reduce(0, shp.m);      

      return matrix_shape(rectang,I.size(),J.size());
    }

    virtual vector_shape MIj_shape(matrix_shape shp, sub I, int j)
    {
      I.reduce(0,shp.m);
      return vector_shape(dense,I.size());
    }

    virtual vector_shape MiJ_shape(matrix_shape shp, int i, sub J)
    {
      J.reduce(0,shp.n);
      return vector_shape(dense,J.size());
    }

  };

  // ------------------------------------------------------------
  //             unary_vector_engine implementation 
  // ------------------------------------------------------------

  template<typename VALTYPE, vector_type VTYPE>
  class default_v_unary : public v_unary_engine<VALTYPE>
  {
  public:
    //    default_vector_unary(){}

    virtual vector_expression<VALTYPE>& create(vector_shape shp)
    {
      return * new vector<VALTYPE,VTYPE>(shp);
    }

    virtual void scale(vector_expression<VALTYPE> &a, VALTYPE s)
    {
      vector<VALTYPE,VTYPE> * _a = (vector<VALTYPE,VTYPE> *)(&a);
      _a -> scale(s);
    }

    virtual void setval(vector_expression<VALTYPE> &a, VALTYPE s)
    {
      vector<VALTYPE,VTYPE> * _a = (vector<VALTYPE,VTYPE> *)(&a);
      _a -> setval(s);
    }

    virtual void scale(vector_expression<VALTYPE> &a, VALTYPE s, sub I)
    {     
      // fixme - use BLAS
      vector<VALTYPE,VTYPE> *_a = (vector<VALTYPE,VTYPE>*)(&a);
      for (int i = I.i1; i<=I.i2; i+=I.inc)
	if ( _a -> unique(i) ) *(_a -> ptr(i)) *= s;	  
    }

    virtual void setval(vector_expression<VALTYPE> &a, VALTYPE s, sub I)
    {
      // fixme - use BLAS
      vector<VALTYPE,VTYPE> *_a = (vector<VALTYPE,VTYPE>*)(&a);
      for (int i = I.i1; i<=I.i2; i+=I.inc)
	if ( _a -> unique(i) ) *(_a -> ptr(i)) = s;
    }

    virtual vector_shape VI_shape(vector_shape shp, sub I )
    {
      // fixme -- is it always dense?
      I.reduce(0,shp.n);
      return vector_shape(dense,I.size());
    }

  };

  // ------------------------------------------------------------
  //             convertor_matrix_engine implementation 
  // ------------------------------------------------------------

  //-------------------------------------------------------------------------//
  //             The default convertor should work in most cases

  template<class VALTYPE, matrix_type MTP_DST, matrix_type MTP_SRC>
  class default_m_convertor : public m_convertor_engine<VALTYPE>
  {
   public:

    //    default_matrix_convertor(){}
    
    virtual bool is_convertable(matrix_shape dest, matrix_shape src)
    {
      
      bool convertable = _lace_storage::is_convertable(MTP_DST,MTP_SRC) && 
	(dest.n == src.n && dest.m == src.m);

      if (convertable)
	{
	  if ( is_banded(MTP_DST) && is_banded(MTP_SRC) )
	    {
	      convertable =  ( dest.ku >= src.ku && dest.kl >= src.kl );
	    }

	  if ( MTP_DST == triang && MTP_SRC == triang)
	    convertable = ( dest.tag == src.tag );
	}
      return convertable;
    }

    //--------------------------------------------------------------------------------//

    virtual void convert( matrix_expression<VALTYPE> &dest, matrix_expression<VALTYPE> &src)
    {

      matrix<VALTYPE,MTP_DST> *DST = (matrix<VALTYPE,MTP_DST>*)(&dest);  
      matrix<VALTYPE,MTP_SRC> *SRC = (matrix<VALTYPE,MTP_SRC>*)(&src);

      assert( is_convertable(DST->shape(),SRC->shape()) && "Invalid matrix conversion" );

      // Not a very efficient way to do this, but it's default
       for (int i=0; i<SRC->size(0); i++)
	for (int j=0; j<SRC->size(1); j++)
	  if ( DST -> unique(i,j) )
	    (*DST)(i,j) = (SRC -> defined(i,j) ) ? (*SRC)(i,j) : (VALTYPE)0;
    }

    virtual void convert( matrix_expression<VALTYPE> &dest, sub IA, sub JA,
			  matrix_expression<VALTYPE> &src,  sub IB, sub JB)
    {
      matrix<VALTYPE,MTP_DST> *DST = (matrix<VALTYPE,MTP_DST>*)(&dest);  
      matrix<VALTYPE,MTP_SRC> *SRC = (matrix<VALTYPE,MTP_SRC>*)(&src);
      
      //fixme -- insert proper convertability check
      //assert( is_convertable(DST->shape(),SRC->shape()) && "Invalid matrix conversion" );

      // Not a very efficient way to do this, but it's default
      int ib = IB.i1;
      for (int ia = IA.i1; ia<=IA.i2; ia += IA.inc)
	{
	  int jb = JB.i1;
	  for (int ja = JA.i1; ja <= JA.i2; ja += JA.inc)
	    {	      
	      if ( DST -> unique(ia,ja) )
		(*DST)(ia,ja) = (SRC -> defined(ib,jb) ) ? (*SRC)(ib,jb) : (VALTYPE)0;
	      jb += JB.inc;
	    }
	  ib += IB.inc;
	}
    }

    //--------------------------------------------------------------------------------//

    virtual matrix_shape reshape(matrix_shape src) 
    {
      assert( _lace_storage::is_convertable(MTP_DST, MTP_SRC) && "Invalid matrix conversion" );

      // We have to check additional parameters of the shape
      if ( MTP_DST == triang )
	return matrix_shape(MTP_DST, src.n, src.tag);

      else if ( is_banded(MTP_DST))
	return matrix_shape(MTP_DST, src.n, src.m, src.ku, src.kl );	  

      else
	return matrix_shape(MTP_DST, src.n, src.m);
    }
    
    virtual matrix_shape reshape(matrix_expression<VALTYPE> &src)
    {
      matrix<VALTYPE,MTP_SRC> *SRC = (matrix<VALTYPE,MTP_SRC>*)(&src);
      return reshape( SRC -> shape() );
    } 
    
    //--------------------------------------------------------------------------------//

    virtual matrix_expression<VALTYPE>& convert(matrix_expression<VALTYPE> &src)
    {
      matrix<VALTYPE,MTP_DST> *DST = new matrix<VALTYPE,MTP_DST>( reshape(src) );
      convert(*DST,src);
      return *DST;
    }
    
  };
  
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

      assert( is_convertable(DST->shape(),SRC->shape()) && "Invalid matrix conversion" );
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

  //---------------------------------------------------------------------------//
  //                                                                           //
  //                  binary_martix_engine implamentation                      //
  //---------------------------------------------------------------------------//

  template<class VALTYPE, matrix_type MTP_DST, matrix_type MTP_SRC>
  class default_mm_binary : public mm_binary_engine<VALTYPE>
  {
   public:

    //    default_matrix_binary(){}

    virtual bool is_addable(matrix_shape dest, matrix_shape src)
    {
      // fixme -- this is not enough
      //      return shp1.n == shp2.n && shp1.m == shp2.m;

      // fixme -- the same as is_convertable -- is it right?

      bool convertable = _lace_storage::is_convertable(MTP_DST,MTP_SRC) && (dest.n == src.n && dest.m == src.m);

      //      std::cout << "dimensions checked\n";

      if (convertable)
	{
	  if ( is_banded(MTP_DST) && is_banded(MTP_SRC) )
	    {
	      convertable =  ( dest.ku >= src.ku && dest.kl >= src.kl );
	    }

	  if ( MTP_DST == triang && MTP_SRC == triang)
	    convertable = ( dest.tag == src.tag );
	}
      return convertable;

    }

    virtual matrix_shape MpM_shape(matrix_shape shp1, matrix_shape shp2)
    {
      if ( ! is_addable(shp1,shp2) ) return _lace_storage::empty_shape();
      else
	{
	  matrix_type restype;
	  
	  bool _band_ = is_banded(MTP_DST) && is_banded(MTP_SRC);
	  bool _symm_ = is_symmetric(MTP_DST) && is_symmetric(MTP_SRC);
	  bool _herm_ = is_hermitian(MTP_DST) && is_hermitian(MTP_SRC);

	  if (_band_)
	    {
	      if (_symm_)
		restype = symmband;
	      else if (_herm_)
		restype = hermband;
	      else
		restype = banddiag;
	    }
	  else
	    {
	      if (_symm_)
		restype = symmetric;
	      else if (_herm_)
		restype = hermitian;
	      else
		restype = rectang;
	    }
	  
	  if ( MTP_DST == triang && MTP_SRC == triang && shp1.tag == shp2.tag )
	    restype = triang;

	  int ku, kl;
	  switch(restype){
	    
	  case banddiag:
	  case symmband: 
	  case hermband:
	    ku = std::max( shp1.ku, shp2.ku );
	    kl = std::max( shp1.kl, shp2.kl );

	    if ( ! restype == banddiag)
	      ku = kl = std::max(ku,kl);

	    return matrix_shape(restype, shp1.n, shp1.m, ku, kl);
	    break;
	    
	  case triang:
	    return matrix_shape(triang, shp1.n, shp1.tag );
	    break;

	  default:
	    return matrix_shape(restype, shp1.n, shp1.m);
	  }
	  
	}
    }
    
    virtual bool is_multiplicable(matrix_shape shp1, matrix_shape shp2)
    {
      return shp1.m == shp2.n;
    }

    virtual matrix_shape MxM_shape(matrix_shape shp1, matrix_shape shp2)
    {
      if ( ! is_multiplicable(shp1,shp2) ) return _lace_storage::empty_shape();
      else
	{
	  int n = shp1.n, m = shp2.m;

	  // fixme - think about the shape of banded*banded and of triang*triang
	  return matrix_shape(rectang,n,m);
	}
    }

    virtual void MpM(matrix_expression<VALTYPE> &a, matrix_expression<VALTYPE> &b, 
		     VALTYPE beta, int OP = 0)
    {
      // A += beta*B;
      // Simplest and not efficient default implementation
      // 
      // fixme -- try never use it, use BLAS instead
      matrix<VALTYPE,MTP_DST> *A = (matrix<VALTYPE,MTP_DST>*)(&a);
      matrix<VALTYPE,MTP_SRC> *B = (matrix<VALTYPE,MTP_SRC>*)(&b);

      std::cout << "Addition of " << _lace_storage::mtype_spelling[MTP_SRC] << " to " << 
	_lace_storage::mtype_spelling[MTP_DST] << "\n";

      if ( OP == 0)
	{
	  
	  for (int i = 0; i < A->size(0); i++)
	    for (int j = 0; j < A->size(1); j++)
	      if ( A -> unique(i,j) && B -> defined(i,j) )
		(*A)(i,j) += beta * (*B)(i,j);

	}
      else if ( OP == _transp)
	{
	  
	  for (int i = 0; i < A->size(0); i++)
	    for (int j = 0; j < A->size(1); j++)
	      if ( A -> unique(i,j) && B -> defined(j,i) )
		(*A)(i,j) += beta * (*B)(j,i);

	}
      else if ( OP == _herm)
	{
	  
	  for (int i = 0; i < A->size(0); i++)
	    for (int j = 0; j < A->size(1); j++)
	      if ( A -> unique(i,j) && B -> defined(j,i) )
		(*A)(i,j) += beta * lace::conj((*B)(j,i));
	}

    }

    virtual void MpM(matrix_expression<VALTYPE> &a, sub IA, sub JA, 
		     matrix_expression<VALTYPE> &b, sub IB, sub JB, 
		     VALTYPE beta, int OP = 0 )
    {
      matrix<VALTYPE,MTP_DST> *A = (matrix<VALTYPE,MTP_DST>*)(&a);
      matrix<VALTYPE,MTP_SRC> *B = (matrix<VALTYPE,MTP_SRC>*)(&b);
      
      //     std::cout << "Enterind subrange add_matrix\n";

      if ( OP == 0)
	{
	  // A(IA,JA) += beta*B(IB,JB)
	  int ib = IB.i1;
	  for (int ia = IA.i1; ia <= IA.i2; ia+=IA.inc)
	    {
	      int jb = JB.i1;
	      for (int ja = JA.i1; ja <= JA.i2; ja+=JA.inc)
		{
		  //std::cout << " A(" << ia << "," << ja << ")+=beta*B(" << ib << "," << jb << ")\n";

		  if ( A -> unique(ia,ja) && B -> defined(ib,jb) )
		    (*A)(ia,ja) += beta * (*B)(ib,jb);
		  jb += JB.inc;
		}
	      ib +=IB.inc;
	    }
	      
	}
      else if ( OP == _transp)
	{	  
	  // A(IA,JA) += beta*B(IB,JB)^T
	  int ib = IB.i1;
	  for (int ia = IA.i1; ia <= IA.i2; ia+=IA.inc)
	    {
	      int jb = JB.i1;
	      for (int ja = JA.i1; ja <= JA.i2; ja+=JA.inc)
		{
		  if ( A -> unique(ia,ja) && B -> defined(jb,ib) )
		    (*A)(ia,ja) += beta * (*B)(jb, ib);
		  jb += JB.inc;
		}
	      ib +=IB.inc;
	    }	      
	}
      else if ( OP == _herm)
	{
	  // A(IA,JA) += beta*B(IB,JB)^H
	  int ib = IB.i1;
	  for (int ia = IA.i1; ia <= IA.i2; ia+=IA.inc)
	    {
	      int jb = JB.i1;
	      for (int ja = JA.i1; ja <= JA.i2; ja+=JA.inc)
		{
		  if ( A -> unique(ia,ja) && B -> defined(jb,ib) )
		    (*A)(ia,ja) += beta * lace::conj( (*B)(jb,ib) );
		  jb += JB.inc;
		}
	      ib +=IB.inc;
	    }	  
	}
    }

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

  //---------------------------------------------------------------------------//
  //                                                                           //
  //                  binary_vector_engine implamentation                      //
  //---------------------------------------------------------------------------//

  template<class VALTYPE, vector_type VTP_DST, vector_type VTP_SRC>
  class default_vv_binary : public vv_binary_engine<VALTYPE>{
  public:
    
    virtual bool is_addable(vector_shape dest, vector_shape src)
    {
      // fixme think if this is sufficient!
      return dest.n == src.n;
    }

    virtual vector_shape VpV_shape(vector_shape shp1, vector_shape shp2)
    {
      // fixme think if this is sufficient!
      if (shp1.n == shp2.n)
	return vector_shape(VTP_DST, shp1.n);
      else
	return vector_shape();
    }

    virtual matrix_shape VxV_shape(vector_shape shp1, vector_shape shp2)
    {
      return matrix_shape(rectang,shp1.n,shp2.n);
    }

    virtual void VpV(vector_expression<VALTYPE> &u, vector_expression<VALTYPE> &v,
		     VALTYPE beta)
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);
      for ( int i = 0; i < U -> size(); i++ )
	(*U)(i) += beta*(*V)(i);
    }

    virtual void VpV(vector_expression<VALTYPE> &u, sub Iu,
		     vector_expression<VALTYPE> &v, sub Iv,
		     VALTYPE beta )
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);
      int iv = Iv.begin();
      for (int iu = Iu.begin(); iu <= Iu.end(); iu += Iu.inc)
	{

	  (*U)(iu) += beta * (*V)(iv);
	  std::cout << "iu= " << iu << " iv= " << iv 
		    << " v(iv) = " << (*V)(iv)<< " u(iu) = " << (*U)(iu) <<"\n";
	  iv += Iv.inc;
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
       
  //--------------------------------------------------------//
  //                  Matrix multiplication                 //
  //--------------------------------------------------------//

  template<class VALTYPE,matrix_type MTPA,matrix_type MTPB,matrix_type MTPC>
  class default_mmm_ternary : public mmm_ternary_engine<VALTYPE> {

    inline int begin(int dim, sub I, sub J, int OP)
    {
      if (dim==0)
	return ((OP & (_transp|_herm))!=0) ? J.begin() : I.begin();
      else
	return ((OP & (_transp|_herm))!=0) ? I.begin() : J.begin();
    }

    inline int end(int dim, sub I, sub J, int OP)
    {
      if (dim==0)
	return ((OP & (_transp|_herm))!=0) ? J.end() : I.end();
      else
	return ((OP & (_transp|_herm))!=0) ? I.end() : J.end();
    }

    inline int inc(int dim, sub I, sub J, int OP)
    {
      if (dim==0)
	return ((OP & (_transp|_herm))!=0) ? J.inc : I.inc;
      else
	return ((OP & (_transp|_herm))!=0) ? I.inc : J.inc;
    }


  public:
    
    //    default_matrix_ternary(){};
    
    virtual void MxM(matrix_expression<VALTYPE> &a, matrix_expression<VALTYPE> &b, 
		     matrix_expression<VALTYPE> &c, VALTYPE alpha, VALTYPE beta,
		     int OP_B = 0, int OP_C = 0)
    {
      // fixme -- replace where possible with BLAS calls (dgemm, dsymm, dtrmm, etc)
      // fixme -- implement for OP = _herm

      matrix<VALTYPE,MTPA> *A = (matrix<VALTYPE,MTPA>*)(&a);
      matrix<VALTYPE,MTPB> *B = (matrix<VALTYPE,MTPB>*)(&b);
      matrix<VALTYPE,MTPC> *C = (matrix<VALTYPE,MTPC>*)(&c);
      
      for (int i=0; i< A->size(0); i++ )
	for (int k=0; k< A->size(1); k++ )
	  if ( A->unique(i,k) )
	    {
	      VALTYPE aa = (VALTYPE)0;

	      if ( OP_B == 0 && OP_C == 0 )
		{
		  for (int j=0; j<B->size(1); j++)
		    if ( B->defined(i,j) && C->defined(j,k) )
		      aa += (*B)(i,j)*(*C)(j,k);
		}
	      else if ( OP_B == _transp && OP_C == 0 )
		{
		  for (int j=0; j<B->size(0); j++)
		    if ( B->defined(j,i) && C->defined(j,k) )
		      aa += (*B)(j,i)*(*C)(j,k);
		}  
	      else if ( OP_B == 0 && OP_C == _transp )
		{
		  for (int j=0; j<B->size(1); j++)
		    if ( B->defined(i,j) && C->defined(k,j) )
		      aa += (*B)(i,j)*(*C)(k,j);
		}
	      else if ( OP_B == _transp && OP_C == _transp )
		{
		  for (int j=0; j<B->size(0); j++)
		    if ( B->defined(j,i) && C->defined(k,j) )
		      aa += (*B)(j,i)*(*C)(k,j);
		}
	      else if ( OP_B == _herm && OP_C == 0 )
		{
		  for (int j=0; j<B->size(0); j++)
		    if ( B->defined(j,i) && C->defined(j,k) )
		      aa += lace::conj((*B)(j,i))*(*C)(j,k);
		}  
	      else if ( OP_B == 0 && OP_C == _herm )
		{
		  for (int j=0; j<B->size(1); j++)
		    if ( B->defined(i,j) && C->defined(k,j) )
		      aa += (*B)(i,j)*lace::conj((*C)(k,j));
		}
	      else if ( OP_B == _herm && OP_C == _herm )
		{
		  for (int j=0; j<B->size(0); j++)
		    if ( B->defined(j,i) && C->defined(k,j) )
		      aa += lace::conj((*B)(j,i))*lace::conj((*C)(k,j));
		}
	      else if ( OP_B == _transp && OP_C == _herm )
		{
		  for (int j=0; j<B->size(0); j++)
		    if ( B->defined(j,i) && C->defined(k,j) )
		      aa += (*B)(j,i)*lace::conj((*C)(k,j));
		}
	      else if ( OP_B == _herm && OP_C == _transp )
		{
		  for (int j=0; j<B->size(0); j++)
		    if ( B->defined(j,i) && C->defined(k,j) )
		      aa += lace::conj((*B)(j,i))*(*C)(k,j);
		}
	      aa *= beta;
	      aa += alpha*(*A)(i,k);

	      (*A)(i,k) = aa;
	    }
    }
    
    virtual void MxM(matrix_expression<VALTYPE> &a, sub IA, sub JA,
		     matrix_expression<VALTYPE> &b, sub IB, sub JB,
		     matrix_expression<VALTYPE> &c, sub IC, sub JC,
		     VALTYPE alpha, VALTYPE beta,
		     int OP_B = 0, int OP_C = 0)
    {
      // fixme -- replace where possible with BLAS calls (dgemm, dsymm, dtrmm, etc)
      // fixme -- implement this

      //      std::cout << "\nMxM for submatricies\n alpha= " << alpha << " beta = " << beta << "\n";

      matrix<VALTYPE,MTPA> *A = (matrix<VALTYPE,MTPA>*)(&a);
      matrix<VALTYPE,MTPB> *B = (matrix<VALTYPE,MTPB>*)(&b);
      matrix<VALTYPE,MTPC> *C = (matrix<VALTYPE,MTPC>*)(&c);  

      int ib = begin(0,IB,JB,OP_B);

      for (int ia = IA.begin(); ia<=IA.end(); ia+=IA.inc)
	{
	  int kc = begin(1,IC,JC,OP_C);
	  for (int ka = JA.begin(); ka<=JA.end(); ka+=JA.inc)
	    {
	      if (A->unique(ia,ka))
		{
		  VALTYPE aa = VALTYPE(0);
		  
		  int jc = begin(0,IC,JC,OP_C);
		  for (int jb = begin(1,IB,JB,OP_B); jb <= end(1,IB,JB,OP_B); jb += inc(1,IB,JB,OP_B))
		    {
		      VALTYPE bb, cc;

		      if (OP_B == 0)
			bb = (*B)(ib,jb);
		      else if (OP_B == _transp)
			bb = (*B)(jb,ib);
		      else if (OP_B == _herm)
			bb = lace::conj((*B)(jb,ib));

		      if (OP_C == 0)
			cc = (*C)(jc,kc);
		      else if (OP_C == _transp)
			cc = (*C)(kc,jc);
		      else if (OP_C == _herm)
			cc = lace::conj((*C)(kc,jc));

		      aa += bb*cc;

		      jc += inc(0,IC,JC,OP_C);

		      //std::cout << " ia = " << ia << " ka = " << ka << " ib = " << ib << " jb = " << jb << " jc = " << jc << " kc = " << kc << "\n"; 

		    }
		  (*A)(ia,ka) *= alpha;
		  (*A)(ia,ka) += beta*aa;
		}
	      kc += inc(1,IC,JC,OP_C);
	    }
	  ib += inc(0,IB,JB,OP_B);
	}
    }
    
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

  template<typename VALTYPE, vector_type VTP_DST, matrix_type MTP, vector_type VTP_SRC>
  class default_vmv_ternary : public vmv_ternary_engine<VALTYPE>{
  public:

    virtual bool MxV_conform(vector_shape dst, matrix_shape mshp, vector_shape src)
    {
      vector_shape res_shp = wizard<VALTYPE>::VM(VTP_SRC,MTP).MxV_shape(mshp,src);
      return wizard<VALTYPE>::V2V(VTP_DST,res_shp.vtype).is_convertable(dst,res_shp);
    }
    
    virtual void MxV(vector_expression<VALTYPE> &u, matrix_expression<VALTYPE> &a,
		     vector_expression<VALTYPE> &v, VALTYPE alpha, VALTYPE beta, int OP = 0 )
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      matrix<VALTYPE,MTP>     *A = (matrix<VALTYPE,MTP>*)(&a);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);

      for(int i=0; i < U -> size(); i++)
	if ( U -> unique(i))
	  {
	    VALTYPE r = VALTYPE(0);
	    if (OP == 0)
	      {
		for (int j=0; j < V -> size(); j++)
		  if ( A -> defined(i,j) && V -> defined(j) )
		    r += (*A)(i,j)*(*V)(j);
	      }
	    else if (OP == _transp)
	      {
		for (int j=0; j < V -> size(); j++)
		  if ( A -> defined(j,i) && V -> defined(j) )
		    r += (*A)(j,i)*(*V)(j);
	      }
	    // fixme OP == _herm
	    (*U)(i) *= alpha;
	    (*U)(i) += beta*r;
	  }
    }

    virtual void MxV(vector_expression<VALTYPE> &u, sub Iu,
		     matrix_expression<VALTYPE> &a, sub IA, sub JA,
		     vector_expression<VALTYPE> &v, sub Jv,
		     VALTYPE alpha, VALTYPE beta, int OP = 0 )
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      matrix<VALTYPE,MTP>     *A = (matrix<VALTYPE,MTP>*)(&a);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);

      int iA = IA.begin();
      for(int iu = Iu.begin(); iu < Iu.end(); iu += Iu.inc)
	{
	  if ( U -> unique(iu))
	    {
	      VALTYPE r = VALTYPE(0);
	      if (OP == 0)
		{
		  int jA = JA.begin();
		  for (int jv=Jv.begin(); jv < Jv.end(); jv += Jv.inc)
		    {
		      if ( A -> defined(iA,jA) && V -> defined(jv) )
			r += (*A)(iA,jA)*(*V)(jv);
		      jA += JA.inc;
		      
		    }	  
		}
	      
	      else if (OP == _transp)
		{
		  int jA = JA.begin();
		  for (int jv=Jv.begin(); jv < Jv.end(); jv += Jv.inc)
		    {
		      if ( A -> defined(iA,jA) && V -> defined(jv) )
			r += (*A)(jA,iA)*(*V)(jv);
		      jA += JA.inc;
		      
		    }	  
		}
	      //fixme OP == _herm
	      (*U)(iu) *= alpha;
	      (*U)(iu) += beta*r;
	    }
	  iA += IA.inc;
	}
    }
    
    virtual void VxV(matrix_expression<VALTYPE> &a, vector_expression<VALTYPE> &u, 
		     vector_expression<VALTYPE> &v, VALTYPE alpha, VALTYPE beta )
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      matrix<VALTYPE,MTP>     *A = (matrix<VALTYPE,MTP>*)(&a);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);

      for (int i = 0; i < A -> size(0); i++)
	for (int j = 0; j < A -> size(1); j++)
	  (*A)(i,j) = alpha*(*A)(i,j) + beta * (*U)(i) * (*V)(j);

    }
    
    virtual void VxV(matrix_expression<VALTYPE> &a, sub IA, sub JA,
		     vector_expression<VALTYPE> &u, sub Iu,
		     vector_expression<VALTYPE> &v, sub Jv,
		     VALTYPE alpha, VALTYPE beta )
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      matrix<VALTYPE,MTP>     *A = (matrix<VALTYPE,MTP>*)(&a);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);

      int iu = Iu.begin();
      for (int iA = IA.begin(); iA <= IA.end(); iA += IA.inc)
	{
	  int jv = Jv.begin();
	  for (int jA = JA.begin(); jA <= JA.end(); jA += JA.inc)
	    {
	      (*A)(iA,jA) = alpha*(*A)(iA,jA) + beta * (*U)(iu) * (*V)(jv);
	      jv += Jv.inc;
	    }
	  iu += Iu.inc;
	}
    } 
    
  };

};

#endif
