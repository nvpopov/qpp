#ifndef _LACE_BLAS_MV_H
#define _LACE_BLAS_MV_H

#include<lace/complex.hpp>
#include<lace/shape.hpp>
#include<lace/storage.hpp>
#include<lace/globals.hpp>
#include<lace/range.hpp>

namespace _lace_storage{

  // ---------------------------- Submatrix to vector ------------------------------

  template<class VALTYPE, vector_type VTP, matrix_type MTP>
  void mtr_column(vector_storage<VALTYPE,VTP> &v, matrix_storage<VALTYPE,MTP> &M, int j, VALTYPE beta)
  {
    for (int i=0; i<v.size(); i++)
      if (v.unique(i) && M.defined(i,j))
	v(i) += beta*M(i,j);
  }

  template<class VALTYPE, vector_type VTP, matrix_type MTP>
  void mtr_column(vector_storage<VALTYPE,VTP> &v, sub Iv, matrix_storage<VALTYPE,MTP> &M, sub IM, int j, 
		  VALTYPE beta)
  {
    Iv.reduce(0,v.size());
    IM.reduce(0,M.size(0));
    int im = IM.begin();
    for (int iv = Iv.begin(); iv < Iv.end(); iv += Iv.inc)
      {
	if (v.unique(iv) && M.defined(im,j))
	  v(iv) += beta*M(im,j);
	im += IM.inc;
      }
  }

  template<class VALTYPE, vector_type VTP, matrix_type MTP>
  void mtr_row(vector_storage<VALTYPE,VTP> &v, matrix_storage<VALTYPE,MTP> &M, int i, VALTYPE beta)
  {
    for (int j=0; j<v.size(); j++)
      if (v.unique(j) && M.defined(i,j))
	v(j) += beta*M(i,j);
  }

  template<class VALTYPE, vector_type VTP, matrix_type MTP>
  void mtr_row(vector_storage<VALTYPE,VTP> &v, sub Jv, matrix_storage<VALTYPE,MTP> &M, int i, sub JM, 
		  VALTYPE beta)
  {
    Jv.reduce(0,v.size());
    JM.reduce(0,M.size(1));
    int jm = JM.begin();
    for (int jv = Jv.begin(); jv < Jv.end(); jv += Jv.inc)
      {
	if (v.unique(jv) && M.defined(i,jm))
	  v(jv) += beta*M(i,jm);
	jm += JM.inc;
      }
  }

  // --------------------- Matrix by vector multiplication -----------------------------
  
  template<class VALTYPE, vector_type VTPA, matrix_type MTP, vector_type VTPB>
  void mul_mv(vector_storage<VALTYPE,VTPA> &U, matrix_storage<VALTYPE,MTP> &A,
	      vector_storage<VALTYPE,VTPB> &V, VALTYPE alpha, VALTYPE beta, int OP = 0 )
  {
    for(int i=0; i < U.size(); i++)
      if ( U.unique(i))
	{
	  VALTYPE r = VALTYPE(0);
	  if (OP == 0)
	    {
	      for (int j=0; j < V.size(); j++)
		if ( A.defined(i,j) && V.defined(j) )
		  r += A(i,j)*V(j);
	    }
	  else if (OP == _transp)
	    {
	      for (int j=0; j < V.size(); j++)
		if ( A.defined(j,i) && V.defined(j) )
		  r += A(j,i)*V(j);
	    }
	  else if (OP == _herm)
	    {
	      for (int j=0; j < V.size(); j++)
		if ( A.defined(j,i) && V.defined(j) )
		  r += lace::conj(A(j,i))*V(j);
	    }
	  // fixme OP == _herm
	  U(i) *= alpha;
	  U(i) += beta*r;
	}
  }
  

  template<class VALTYPE, vector_type VTPA, matrix_type MTP, vector_type VTPB>
  void mul_mv(vector_storage<VALTYPE,VTPA> &U, sub Iu,
	      matrix_storage<VALTYPE,MTP> &A, sub IA, sub JA,
	      vector_storage<VALTYPE,VTPB> &V, sub Jv,
	      VALTYPE alpha, VALTYPE beta, int OP = 0 )
  {
    int iA = IA.begin();
    for(int iu = Iu.begin(); iu < Iu.end(); iu += Iu.inc)
      {
	if ( U.unique(iu))
	  {
	    VALTYPE r = VALTYPE(0);
	    if (OP == 0)
	      {
		int jA = JA.begin();
		for (int jv=Jv.begin(); jv < Jv.end(); jv += Jv.inc)
		  {
		    if ( A.defined(iA,jA) && V.defined(jv) )
		      r += A(iA,jA)*V(jv);
		    jA += JA.inc;
		    
		  }	  
	      }
	    else if (OP == _transp)
	      {
		int jA = JA.begin();
		for (int jv=Jv.begin(); jv < Jv.end(); jv += Jv.inc)
		  {
		    if ( A.defined(iA,jA) && V.defined(jv) )
		      r += A(jA,iA)*V(jv);
		    jA += JA.inc;
		    
		  }	  
	      }
	    else if (OP == _herm)
	      {
		int jA = JA.begin();
		for (int jv=Jv.begin(); jv < Jv.end(); jv += Jv.inc)
		  {
		    if ( A.defined(iA,jA) && V.defined(jv) )
		      r += lace::conj(A(jA,iA))*V(jv);
		    jA += JA.inc;
		    
		  }	  
	      }
	    U(iu) *= alpha;
	    U(iu) += beta*r;
	  }
	iA += IA.inc;
      }
  }
    
  // --------------------------------- Outer product ----------------------------------

  template<class VALTYPE, vector_type VTPA, matrix_type MTP, vector_type VTPB>
  void outer_prod(matrix_storage<VALTYPE,MTP> &A, vector_storage<VALTYPE,VTPA> &U, 
		  vector_storage<VALTYPE,VTPB> &V, VALTYPE alpha, VALTYPE beta )
  {
    for (int i = 0; i < A.size(0); i++)
      for (int j = 0; j < A.size(1); j++)
	if ( A.unique(i,j) )
	  A(i,j) = alpha*A(i,j) + beta * U(i) * V(j);
    
  }
  
  template<class VALTYPE, vector_type VTPA, matrix_type MTP, vector_type VTPB>
  void outer_prod(matrix_storage<VALTYPE,MTP> &A, sub IA, sub JA,
		  vector_storage<VALTYPE,VTPA> &U, sub Iu,
		  vector_storage<VALTYPE,VTPB> &V, sub Jv,
		  VALTYPE alpha, VALTYPE beta )
  {
    int iu = Iu.begin();
    for (int iA = IA.begin(); iA <= IA.end(); iA += IA.inc)
      {
	int jv = Jv.begin();
	for (int jA = JA.begin(); jA <= JA.end(); jA += JA.inc)
	  {
	    if ( A.unique(iA,jA))
	      A(iA,jA) = alpha*A(iA,jA) + beta * U(iu) * V(jv);
	    jv += Jv.inc;
	  }
	iu += Iu.inc;
      }
  } 
  
};

#endif
