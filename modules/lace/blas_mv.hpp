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


};

#endif
