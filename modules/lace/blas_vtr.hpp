#ifndef _LACE_BLAS_VTR_H
#define _LACE_BLAS_VTR_H

#include<lace/storage.hpp>
#include<lace/range.hpp>

namespace _lace_storage
{
  
  // -------------------------------------- Scaling ----------------------------

  template<typename VALTYPE, vector_type VTP>
  void scale_vtr(vector_storage<VALTYPE,VTP> &a, VALTYPE s)
  {
    for (int i=0; i<a.size(); i++)
      if ( a.unique(i) )
	a(i) *= s;
  }

  template<typename VALTYPE, vector_type VTP>
  void scale_vtr(vector_storage<VALTYPE,VTP> &a, VALTYPE s, _lace_expressions::sub I)
  {
    I.reduce(0,a.size());
    for (int i = I.i1; i<=I.i2; i+=I.inc)
      if ( a.unique(i) ) 
	a(i) *= s;	  
  }
  
  // ----------------------------------- Filling with value ----------------------

  template<typename VALTYPE, vector_type VTP>
  void fill_vtr(vector_storage<VALTYPE,VTP> &a, VALTYPE s)
  {
    for (int i=0; i<a.size(); i++)
      if ( a.unique(i) )
	a(i) = s;
  }

  template<typename VALTYPE, vector_type VTP>
  void fill_vtr(vector_storage<VALTYPE,VTP> &a, VALTYPE s, _lace_expressions::sub I)
  {
    I.reduce(0,a.size());
    for (int i = I.i1; i<=I.i2; i+=I.inc)
      if ( a.unique(i) ) 
	a(i) = s;	  
  }

  // -------------------------- Conversion ------------------------------

  template<typename VALTYPE, vector_type VTP_DST, vector_type VTP_SRC>
  void convert_vtr( vector_storage<VALTYPE,VTP_DST> &dest, vector_storage<VALTYPE,VTP_SRC> &src)
  {
    assert(is_convertable(dest.shape(), src.shape()));
    
    for (int i=0; i < src.size(); i++)
      if ( dest.unique(i))
	dest(i) = src(i);
  }
  
  template<typename VALTYPE, vector_type VTP_DST, vector_type VTP_SRC>
  void convert_vtr(vector_storage<VALTYPE,VTP_DST> &dest, sub Iu,
		   vector_storage<VALTYPE,VTP_SRC> &src,  sub Iv)
  {
    // fixme - insert convertability check
    
    int iv = Iv.begin();
    for (int iu = Iu.begin(); iu <= Iu.end(); iu += Iu.inc)
      {
	if ( dest.unique(iu))
	  dest(iu) = src(iv);
	iv += Iv.inc;
      }
  }

  // ---------------------------------- Addition ------------------------

  template<typename VALTYPE, vector_type VTP_DST, vector_type VTP_SRC>
  void add_vtr(vector_storage<VALTYPE,VTP_DST> & u, vector_storage<VALTYPE,VTP_SRC> & v,
	       VALTYPE beta)
  {
    // fixme - conformity check!
    for ( int i = 0; i < u.size(); i++ )
      if ( u.unique(i) && v.defined(i) )
	u(i) += beta*v(i);
  }

  template<typename VALTYPE, vector_type VTP_DST, vector_type VTP_SRC>
  void add_vtr(vector_storage<VALTYPE,VTP_DST> & u, sub Iu,
	       vector_storage<VALTYPE,VTP_SRC> & v, sub Iv,
	       VALTYPE beta)
  {
    int iv = Iv.begin();
    for (int iu = Iu.begin(); iu <= Iu.end(); iu += Iu.inc)
      {
	if ( u.unique(iu) && v.defined(iv) )
	  u(iu) += beta * v(iv);
	iv += Iv.inc;
      }
  }  
  
};

#endif
