#ifndef _LACE_BLAS_MTR_H
#define _LACE_BLAS_MTR_H

#include<lace/complex.hpp>
#include<lace/shape.hpp>
#include<lace/storage.hpp>
#include<lace/globals.hpp>
#include<lace/range.hpp>

namespace _lace_storage{

  /* Templated BLAS interface
   * 
   * The meaningful VALTYPES are
   *       float
   *       double
   *       fcomplex
   *       dcomplex
   */

  const int _transp = 0x0100,
    _herm = 0x0200;
  
  // ------------------------------ Scaling -------------------------------

  /**@brief  A *= s
    Simplest and not efficient default implementation
  */

  template<typename VALTYPE, matrix_type MTP>
  void scale_mtr(matrix_storage<VALTYPE,MTP> &A, VALTYPE s)
  {
    for (int i = 0; i < A.size(0); i++)
      for (int j = 0; j < A.size(1); j++)
	if ( A.unique(i,j))
	  A(i,j) = A(i,j)*s;
  }

  template<typename VALTYPE, matrix_type MTP>
  void scale_mtr(matrix_storage<VALTYPE,MTP> &A, VALTYPE s, 
		 _lace_expressions::sub I, _lace_expressions::sub J)
  {
    I.reduce(0,A.size(0));
    J.reduce(0,A.size(1));
    for (int i = I.i1; i<=I.i2; i+=I.inc)
      for (int j = J.i1; j<=J.i2; j+=J.inc)
	if ( A.unique(i,j) ) 
	  A(i,j) = A(i,j)*s;	  
  }

  // ---------------------------- Filling with value ----------------------

 template<typename VALTYPE, matrix_type MTP>
  void fill_mtr(matrix_storage<VALTYPE,MTP> &A, VALTYPE s)
  {
    for (int i = 0; i < A.size(0); i++)
      for (int j = 0; j < A.size(1); j++)
	if ( A.unique(i,j))
	  A(i,j) = s;
  }

  template<typename VALTYPE, matrix_type MTP>
  void fill_mtr(matrix_storage<VALTYPE,MTP> &A, VALTYPE s, 
		 _lace_expressions::sub I, _lace_expressions::sub J)
  {
    I.reduce(0,A.size(0));
    J.reduce(0,A.size(1));
    for (int i = I.i1; i<=I.i2; i+=I.inc)
      for (int j = J.i1; j<=J.i2; j+=J.inc)
	if ( A.unique(i,j) ) 
	  A(i,j) = s;	  
  }

  // ------------------------------- Conversion ----------------------------------
  
  template<typename VALTYPE, matrix_type MTP_DST, matrix_type MTP_SRC>
  void convert_mtr(matrix_storage<VALTYPE,MTP_DST> & dest, matrix_storage<VALTYPE,MTP_SRC> & src)
  {
    assert( mtr_is_convertable(dest.shape(),src.shape()) && "Invalid matrix conversion" );

    // Not a very efficient way to do this, but it's default
    for (int i=0; i<src.size(0); i++)
      for (int j=0; j<src.size(1); j++)
	if ( dest.unique(i,j) )
	  dest(i,j) = (src.defined(i,j) ) ? src(i,j) : (VALTYPE)0;
  }

  template<typename VALTYPE, matrix_type MTP_DST, matrix_type MTP_SRC>
  void convert_mtr(matrix_storage<VALTYPE,MTP_DST> & dest, sub IA, sub JA,
		   matrix_storage<VALTYPE,MTP_SRC> & src,  sub IB, sub JB)
  {
    // Not a very efficient way to do this, but it's default
    int ib = IB.i1;
    for (int ia = IA.i1; ia<=IA.i2; ia += IA.inc)
      {
	int jb = JB.i1;
	for (int ja = JA.i1; ja <= JA.i2; ja += JA.inc)
	  {	      
	    if ( dest.unique(ia,ja) )
	      dest(ia,ja) = (src.defined(ib,jb) ) ? src(ib,jb) : (VALTYPE)0;
	    jb += JB.inc;
	  }
	ib += IB.inc;
      }
  }

  // ------------------------------- Addition ----------------------------

  /**@brief  A += beta*OP(B);
    Simplest and not efficient default implementation
   */
  template<typename VALTYPE, matrix_type MTPA, matrix_type MTPB>
  void add_mtr(matrix_storage<VALTYPE,MTPA> &A, matrix_storage<VALTYPE,MTPB> &B,
	     VALTYPE beta, int OP = 0)
  {

    if (lace::globals::debug)
      std::cout << "Addition of " << _lace_storage::mtype_spelling[MTPB] << " to " << 
	_lace_storage::mtype_spelling[MTPA] << "\n";
    
    if ( OP == 0)
      {
	
	for (int i = 0; i < A.size(0); i++)
	  for (int j = 0; j < A.size(1); j++)
	    if ( A.unique(i,j) && B.defined(i,j) )
	      A(i,j) += beta * B(i,j);
	
      }
    else if ( OP == _transp)
      {
	
	for (int i = 0; i < A.size(0); i++)
	  for (int j = 0; j < A.size(1); j++)
	    if ( A.unique(i,j) && B.defined(j,i) )
	      A(i,j) += beta * B(j,i);
	
      }
    else if ( OP == _herm)
      {
	
	for (int i = 0; i < A.size(0); i++)
	  for (int j = 0; j < A.size(1); j++)
	    if ( A.unique(i,j) && B.defined(j,i) )
	      A(i,j) += beta * lace::conj(B(j,i));
      }
  }

  template<typename VALTYPE, matrix_type MTPA, matrix_type MTPB>
  void add_mtr(matrix_storage<VALTYPE,MTPA> &A, sub IA, sub JA, 
	       matrix_storage<VALTYPE,MTPB> &B, sub IB, sub JB, 
	     VALTYPE beta, int OP = 0)
  {
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
		
		if ( A.unique(ia,ja) && B.defined(ib,jb) )
		  A(ia,ja) += beta * B(ib,jb);
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
		if ( A.unique(ia,ja) && B.defined(jb,ib) )
		  A(ia,ja) += beta * B(jb, ib);
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
		if ( A.unique(ia,ja) && B.defined(jb,ib) )
		  A(ia,ja) += beta * lace::conj( B(jb,ib) );
		jb += JB.inc;
	      }
	    ib +=IB.inc;
	  }	  
      }
  }
  
  
  //-----------------------------------------------------------------------------------------
  
  /**@fn
   * A = alpha*A + beta*OPB(B)*OPC(C)
   *
   */
  template<typename VALTYPE, matrix_type MTPA, matrix_type MTPB, matrix_type MTPC>
  void mul_mtr(matrix_storage<VALTYPE,MTPA> &A, matrix_storage<VALTYPE,MTPB> &B, 
	       matrix_storage<VALTYPE,MTPC> &C,
	       VALTYPE alpha, VALTYPE beta, int OP_B, int OP_C)
  {
    // fixme -- replace where possible with BLAS calls (dgemm, dsymm, dtrmm, etc)
    // fixme -- implement for OP = _herm
    
    for (int i=0; i< A.size(0); i++ )
      for (int k=0; k< A.size(1); k++ )
	if ( A.unique(i,k) )
	  {
	    VALTYPE aa = (VALTYPE)0;
	    
	      if ( OP_B == 0 && OP_C == 0 )
		{
		  for (int j=0; j<B.size(1); j++)
		    if ( B.defined(i,j) && C.defined(j,k) )
		      aa += B(i,j)*C(j,k);
		}
	      else if ( OP_B == _transp && OP_C == 0 )
		{
		  for (int j=0; j < B.size(0); j++)
		    if ( B.defined(j,i) && C.defined(j,k) )
		      aa += B(j,i)*C(j,k);
		}  
	      else if ( OP_B == 0 && OP_C == _transp )
		{
		  for (int j=0; j<B.size(1); j++)
		    if ( B.defined(i,j) && C.defined(k,j) )
		      aa += B(i,j)*C(k,j);
		}
	      else if ( OP_B == _transp && OP_C == _transp )
		{
		  for (int j=0; j<B.size(0); j++)
		    if ( B.defined(j,i) && C.defined(k,j) )
		      aa += B(j,i)*C(k,j);
		}
	      else if ( OP_B == _herm && OP_C == 0 )
		{
		  for (int j=0; j<B.size(0); j++)
		    if ( B.defined(j,i) && C.defined(j,k) )
		      aa += lace::conj(B(j,i))*C(j,k);
		}  
	      else if ( OP_B == 0 && OP_C == _herm )
		{
		  for (int j=0; j<B.size(1); j++)
		    if ( B.defined(i,j) && C.defined(k,j) )
		      aa += B(i,j)*lace::conj(C(k,j));
		}
	      else if ( OP_B == _herm && OP_C == _herm )
		{
		  for (int j=0; j<B.size(0); j++)
		    if ( B.defined(j,i) && C.defined(k,j) )
		      aa += lace::conj(B(j,i))*lace::conj(C(k,j));
		}
	      else if ( OP_B == _transp && OP_C == _herm )
		{
		  for (int j=0; j<B.size(0); j++)
		    if ( B.defined(j,i) && C.defined(k,j) )
		      aa += B(j,i)*lace::conj(C(k,j));
		}
	      else if ( OP_B == _herm && OP_C == _transp )
		{
		  for (int j=0; j<B.size(0); j++)
		    if ( B.defined(j,i) && C.defined(k,j) )
		      aa += lace::conj(B(j,i))*C(k,j);
		}
	      aa *= beta;
	      aa += alpha*A(i,k);
	      
	      A(i,k) = aa;
	  }
  }

  namespace mtr{
    
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
  };

  template<typename VALTYPE, matrix_type MTPA, matrix_type MTPB, matrix_type MTPC>
  void mul_mtr(matrix_storage<VALTYPE,MTPA> &A, sub IA, sub JA,
	       matrix_storage<VALTYPE,MTPB> &B, sub IB, sub JB,
	       matrix_storage<VALTYPE,MTPC> &C,	sub IC, sub JC,
	       VALTYPE alpha, VALTYPE beta, int OP_B, int OP_C)
  {
    int ib = mtr::begin(0,IB,JB,OP_B);
    
    for (int ia = IA.begin(); ia<=IA.end(); ia+=IA.inc)
      {
	int kc = mtr::begin(1,IC,JC,OP_C);
	for (int ka = JA.begin(); ka<=JA.end(); ka+=JA.inc)
	  {
	    if (A.unique(ia,ka))
	      {
		VALTYPE aa = VALTYPE(0);
		
		int jc = mtr::begin(0,IC,JC,OP_C);
		for (int jb = mtr::begin(1,IB,JB,OP_B); jb <= mtr::end(1,IB,JB,OP_B); 
		     jb += mtr::inc(1,IB,JB,OP_B))
		  {
		    VALTYPE bb, cc;
		    
		    if (OP_B == 0)
		      bb = B(ib,jb);
		    else if (OP_B == _transp)
		      bb = B(jb,ib);
		    else if (OP_B == _herm)
		      bb = lace::conj(B(jb,ib));
		    
		    if (OP_C == 0)
		      cc = C(jc,kc);
		    else if (OP_C == _transp)
		      cc = C(kc,jc);
		    else if (OP_C == _herm)
		      cc = lace::conj(C(kc,jc));
		    
		    aa += bb*cc;
		    
		    jc += mtr::inc(0,IC,JC,OP_C);
		    
		  }
		A(ia,ka) *= alpha;
		A(ia,ka) += beta*aa;
	      }
	    kc += mtr::inc(1,IC,JC,OP_C);
	  }
	ib += mtr::inc(0,IB,JB,OP_B);
      }
  }
  
  // ---------- Template specialization for mulmm ----------

  /*  template<>
  void mulmm<float,rectang,rectang,rectang>(matrix_storage<VALTYPE,MTPA> &A, 
					    matrix_storage<VALTYPE,MTPA> &B, 
					    matrix_storage<VALTYPE,MTPA> &C,
					    VALTYPE alpha, VALTYPE beta, int opb, int opc)
  
  template<>
  void mulmm<double,rectang,rectang,rectang>
  
  template<>
  void mulmm<lace::fcomplex,rectang,rectang,rectang>
  
  template<>
  void mulmm<lace::dcomplex,rectang,rectang,rectang>
  
  template<>
  void mulmm<float,symmetric,rectang,rectang>(matrix_storage<VALTYPE,MTPA> &A, 
					      matrix_storage<VALTYPE,MTPA> &B, 
					      matrix_storage<VALTYPE,MTPA> &C,
					      VALTYPE alpha, VALTYPE beta, int opb, int opc)
  
  template<>
  void mulmm<double,symmetric,rectang,rectang>
  template<>
  void mulmm<float,rectang,symmetric,rectang>(matrix_storage<VALTYPE,MTPA> &A, 
					      matrix_storage<VALTYPE,MTPA> &B, 
					      matrix_storage<VALTYPE,MTPA> &C,
					      VALTYPE alpha, VALTYPE beta, int opb, int opc)
  
  template<>
  void mulmm<double,rectang,symmetric,rectang>
  
  template<>
  void mulmm<lace::fcomplex,hermitian,rectang,rectang>
  
  template<>
  void mulmm<lace::dcomplex,hermitian,rectang,rectang>

  template<>
  void mulmm<lace::fcomplex,rectang,hermitian,rectang>
  
  template<>
  void mulmm<lace::dcomplex,rectang,hermitian,rectang>
  */
};

#endif
