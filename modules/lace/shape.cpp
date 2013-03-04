#ifndef _LACE_SHAPING_H
#define _LACE_SHAPING_H

#include<lace/shape.hpp>
#include<lace/range.hpp>

namespace _lace_storage
{

  using _lace_expressions::sub;

  matrix_shape transp_shape(matrix_shape shp)
  {
    if ( is_banded(shp.mtype) )
      return matrix_shape( shp.mtype, shp.m, shp.n, shp.kl, shp.ku );
    else if ( shp.mtype == triang )
      {
	matrix_shape::uplo tag;
	if (shp.tag == matrix_shape::lower) tag = matrix_shape::upper;
	else tag = matrix_shape::lower;
	
	return matrix_shape( shp.mtype, shp.n, tag);
      }
    else
      return matrix_shape( shp.mtype, shp.m, shp.n);
  }

  matrix_shape MIJ_shape(matrix_shape shp, sub I, sub J )
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

  vector_shape MIj_shape(matrix_shape shp, sub I, int j)
  {
    I.reduce(0,shp.m);
    return vector_shape(dense,I.size());
  }

  vector_shape MiJ_shape(matrix_shape shp, int i, sub J)
  {
    J.reduce(0,shp.n);
    return vector_shape(dense,J.size());
  }

  vector_shape VI_shape(vector_shape shp, sub I )
  {
    // fixme -- is it always dense?
    I.reduce(0,shp.n);
    return vector_shape(dense,I.size());
  }

  bool mtr_is_convertable(matrix_shape dest, matrix_shape src)
  {
    
    bool convertable = _lace_storage::is_convertable(dest.mtype,src.mtype) && 
      (dest.n == src.n && dest.m == src.m);
    
    if (convertable)
      {
	if ( is_banded(dest.mtype) && is_banded(src.mtype) )
	  {
	    convertable =  ( dest.ku >= src.ku && dest.kl >= src.kl );
	  }
	
	if ( dest.mtype == triang && src.mtype == triang)
	  convertable = ( dest.tag == src.tag );
      }
    return convertable;
  }

  bool vtr_is_convertable(vector_shape dest, vector_shape src)
  {
    return ! (dest.vtype!=dense && src.vtype==dense);
  }

  matrix_shape reshape(matrix_type dst, matrix_shape src) 
  {
    assert( _lace_storage::is_convertable(dst, src.mtype) && "Invalid matrix conversion" );

    // We have to check additional parameters of the shape
    if ( dst == triang ) return matrix_shape(dst, src.n, src.tag);
    else if ( is_banded(dst)) return matrix_shape(dst, src.n, src.m, src.ku, src.kl );	  
    else return matrix_shape(dst, src.n, src.m);
  }
  
  /*  matrix_shape reshape(matrix_expression<VALTYPE> &src)
  {
    matrix<VALTYPE,MTP_SRC> *SRC = (matrix<VALTYPE,MTP_SRC>*)(&src);
    return reshape( SRC -> shape() );
    } */

  bool mtr_is_addable(matrix_shape dest, matrix_shape src)
  {
    matrix_type MTP_DST = dest.mtype,
                MTP_SRC = src.mtype;
    // fixme -- this is not enough
    //      return shp1.n == shp2.n && shp1.m == shp2.m;
    
    // fixme -- the same as is_convertable -- is it right?
    
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

  matrix_shape MpM_shape(matrix_shape shp1, matrix_shape shp2)
  {
    matrix_type MTP_DST = shp1.mtype,
                MTP_SRC = shp2.mtype;
    if ( ! mtr_is_addable(shp1,shp2) ) return _lace_storage::empty_shape();
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
  
    
  bool mtr_is_multiplicable(matrix_shape shp1, matrix_shape shp2)
  {
    return shp1.m == shp2.n;
  }

  matrix_shape MxM_shape(matrix_shape shp1, matrix_shape shp2)
  {
    if ( ! mtr_is_multiplicable(shp1,shp2) ) return _lace_storage::empty_shape();
    else
      {
	int n = shp1.n, m = shp2.m;
	
	// fixme - think about the shape of banded*banded and of triang*triang
	return matrix_shape(rectang,n,m);
      }
  }  
    
  bool vtr_is_addable(vector_shape dest, vector_shape src)
  {
    // fixme think if this is sufficient!
    if ( dest.vtype == dense && src.vtype == dense )
      return dest.n == src.n;
  }

  vector_shape VpV_shape(vector_shape shp1, vector_shape shp2)
  {
    if ( vtr_is_addable(shp1,shp2) )
      return vector_shape(shp1.vtype, shp1.n);
    else
      return vector_shape();
  }

  matrix_shape VxV_shape(vector_shape shp1, vector_shape shp2)
  {
    return matrix_shape(rectang,shp1.n,shp2.n);
  }

  vector_shape MxV_shape(matrix_shape mshp, vector_shape vshp)
  {
    return vector_shape(dense,mshp.n);
  }

    
};

#endif
