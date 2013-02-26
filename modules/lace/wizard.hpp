
#ifndef _LACE_WIZARD_H
#define _LACE_WIZARD_H

//#include <lace/shape.hpp>
//#include <lace/storage.hpp>
//#include <lace/expressions.hpp>

#include<lace/blas_mtr.hpp>
#include<lace/blas_vtr.hpp>
#include<lace/blas_mv.hpp>
#include<lace/matrix.hpp>
#include<lace/vector.hpp>
//#include<lace/lace.hpp>

// Forward declarations
namespace _lace_main{

  using _lace_storage::matrix_type;
  using _lace_storage::n_matrix_type;
  using _lace_storage::matrix_shape;

  using _lace_storage::vector_type;
  using _lace_storage::n_vector_type;
  using _lace_storage::vector_shape;

  using _lace_storage::rectang;    
  using _lace_storage::symmetric;  
  using _lace_storage::hermitian;  
  using _lace_storage::banddiag;   
  using _lace_storage::symmband;   
  using _lace_storage::hermband;   
  using _lace_storage::triang;      

  using _lace_storage::dense;
  using _lace_storage::sparse;

  using _lace_expressions::matrix_expression;
  using _lace_expressions::vector_expression;
  using _lace_expressions::matrix;
  using _lace_expressions::vector;
  using _lace_expressions::sub;

  using _lace_expressions::_transp;
  using _lace_expressions::_herm;


  /* ====================================================== *
   *                                                        *
   *	         Definition of "engines"                    *
   *                                                        *
   * ====================================================== */


  // ------------  Unary operations --------------

  template<class VALTYPE>
  class m_unary_engine{
  public:

    virtual matrix_expression<VALTYPE>& create(matrix_shape shp) =0;

    virtual void scale(matrix_expression<VALTYPE> &a, VALTYPE s) =0;

    virtual void scale(matrix_expression<VALTYPE> &a, VALTYPE s, sub I, sub J) =0;

    virtual void fill(matrix_expression<VALTYPE> &a, VALTYPE s) =0;

    virtual void fill(matrix_expression<VALTYPE> &a, VALTYPE s, sub I, sub J) =0;

    // for debug
    virtual VALTYPE * ptr(matrix_expression<VALTYPE> &a, int i, int j) =0;

  };

  //------------------------------------------------------------------

  template<typename VALTYPE>
  class v_unary_engine{
  public:

    virtual vector_expression<VALTYPE>& create(vector_shape shp) =0;

    virtual void scale(vector_expression<VALTYPE> &a, VALTYPE s) =0;

    virtual void scale(vector_expression<VALTYPE> &a, VALTYPE s, sub I) =0;

    virtual void fill(vector_expression<VALTYPE> &a, VALTYPE s) =0;

    virtual void fill(vector_expression<VALTYPE> &a, VALTYPE s, sub I) =0;

    virtual VALTYPE * ptr(vector_expression<VALTYPE> &a, int i) =0;

  };

  // ----------------- Convertors ----------------------

  template<class VALTYPE>
  class m_convertor_engine{
  public:
    
    virtual void convert( matrix_expression<VALTYPE> &dest, sub IA, sub JA,
			  matrix_expression<VALTYPE> &src,  sub IB, sub JB) =0;

    virtual void convert( matrix_expression<VALTYPE> &dest, matrix_expression<VALTYPE> &src) =0;

  };

  template<class VALTYPE>
  class v_convertor_engine{
  public:
    
    virtual void convert( vector_expression<VALTYPE> &dest, sub Iu,
			  vector_expression<VALTYPE> &src,  sub Iv) =0;
    
    virtual void convert( vector_expression<VALTYPE> &dest, vector_expression<VALTYPE> &src) =0;
    
  };
    
  // -------------------- Binary operations ------------------

  template<class VALTYPE>
  class mm_binary_engine{
  public:

    virtual void MpM(matrix_expression<VALTYPE> &A, matrix_expression<VALTYPE> &B, 
		     VALTYPE beta, int OP = 0 ) =0;
    // performes A = A + beta*B;

    virtual void MpM(matrix_expression<VALTYPE> &A, sub IA, sub JA, 
		     matrix_expression<VALTYPE> &B, sub IB, sub JB, 
		     VALTYPE beta, int OP = 0 ) =0;
    // performes A(IA,JA) = A(IA,JA) + beta*B(IB,JB);

  };
    
  //------------------------------------------------------------------

  template<class VALTYPE>
  class vv_binary_engine{
  public:
    
    virtual void VpV(vector_expression<VALTYPE> &u, vector_expression<VALTYPE> &v, 
		       VALTYPE beta) =0;
    // performes u += beta*v

    virtual void VpV(vector_expression<VALTYPE> &u, sub Iu,
		     vector_expression<VALTYPE> &v, sub Iv,
		     VALTYPE beta ) =0;
    // performes u(Iu) += v(Iv)

  };

  //------------------------------------------------------------------

  template<class VALTYPE>
  class vm_binary_engine{
  public:

    virtual void MIj(vector_expression<VALTYPE> &v, matrix_expression<VALTYPE> &m, 
		     int j, VALTYPE beta) =0;

    virtual void MIj(vector_expression<VALTYPE> &v, sub Iv, matrix_expression<VALTYPE> &m, 
		     sub Im, int j, VALTYPE beta) =0;

    virtual void MiJ(vector_expression<VALTYPE> &v, matrix_expression<VALTYPE> &m, 
		     int i, VALTYPE beta) =0;

    virtual void MiJ(vector_expression<VALTYPE> &v, sub Jv, matrix_expression<VALTYPE> &m, 
		     int i, sub Jm, VALTYPE beta) =0;

  };

  // ---------------------- Ternary operations ------------------------

  template<class VALTYPE>
  class mmm_ternary_engine{
  public:

    virtual void MxM(matrix_expression<VALTYPE> &a, matrix_expression<VALTYPE> &b, 
		     matrix_expression<VALTYPE> &c, VALTYPE alpha, VALTYPE beta,
		     int OP_B = 0, int OP_C = 0) =0;
    // This should operate like DGEMM:
    // 
    //  a = alpha*a + beta*b*c

    virtual void MxM(matrix_expression<VALTYPE> &a, sub IA, sub JA,
		     matrix_expression<VALTYPE> &b, sub IB, sub JB,
		     matrix_expression<VALTYPE> &c, sub IC, sub JC,
		     VALTYPE alpha, VALTYPE beta,
		     int OP_B = 0, int OP_C = 0) =0;
    //  a(IA,JA) = alpha*a(IA,JA) + beta*b(IB,JB)*c(IC,JC)
  };

  template<class VALTYPE>
  class vmv_ternary_engine{
  public:

    //   virtual vector_shape MxV_shape(matrix_shape mshp, vector_shape vshp) = 0;

    virtual void MxV(vector_expression<VALTYPE> &u, matrix_expression<VALTYPE> &A,
		     vector_expression<VALTYPE> &v, VALTYPE alpha, VALTYPE beta, int OP = 0 ) = 0;
    // Does u = alpha*u + beta*A*v

    virtual void MxV(vector_expression<VALTYPE> &u, sub Iu,
		     matrix_expression<VALTYPE> &A, sub IA, sub JA,
		     vector_expression<VALTYPE> &v, sub Jv,
		     VALTYPE alpha, VALTYPE beta, int OP = 0 ) = 0;
    // Does u(Iu) = alpha*u(Iu) + beta*A(IA,JA)*v(Jv)

    virtual void VxV(matrix_expression<VALTYPE> &A, vector_expression<VALTYPE> &u, 
		     vector_expression<VALTYPE> &v, VALTYPE alpha, VALTYPE beta ) =0;
    // A = alpha*A + beta* u%v
    
    virtual void VxV(matrix_expression<VALTYPE> &A, sub IA, sub JA,
		     vector_expression<VALTYPE> &u, sub Iu,
		     vector_expression<VALTYPE> &v, sub Jv,
		     VALTYPE alpha, VALTYPE beta ) =0;
    // A(IA,JA) = alpha*A(IA,JA) + beta* u(Iu)%v(Jv)
    
  };


  /* ======================================================== *
   *                                                          *
   *      The wizard class -- main internal interface         *
   *                                                          *
   * ======================================================== */

  template<class VALTYPE>
  class wizard
  {
    static m_unary_engine<VALTYPE>      *_m_unary       [n_matrix_type];
    static m_convertor_engine<VALTYPE>  *_m_convertor   [n_matrix_type][n_matrix_type];
    static mm_binary_engine<VALTYPE>     *_m_binary      [n_matrix_type][n_matrix_type];
    static mmm_ternary_engine<VALTYPE>   *_m_ternary     [n_matrix_type][n_matrix_type][n_matrix_type];

    static v_unary_engine<VALTYPE>       *_v_unary       [n_vector_type];
    static v_convertor_engine<VALTYPE>   *_v_convertor   [n_vector_type][n_vector_type];
    static vv_binary_engine<VALTYPE>     *_v_binary      [n_vector_type][n_vector_type];
    static vm_binary_engine<VALTYPE>     *_vm_binary     [n_vector_type][n_matrix_type];
    static vmv_ternary_engine<VALTYPE>   *_vmv_ternary   [n_vector_type][n_matrix_type][n_vector_type];

  public:
  
    static inline m_unary_engine<VALTYPE>& M(matrix_type mtp)
    {
      return *_m_unary[mtp];
    }

    static inline m_convertor_engine<VALTYPE>& M2M(matrix_type mtp1, matrix_type mtp2)
    {
      return *_m_convertor[mtp1][mtp2];
    }

    static inline v_convertor_engine<VALTYPE>& V2V(vector_type vtp1, vector_type vtp2)
    {
      return *_v_convertor[vtp1][vtp2];
    }

    static inline mm_binary_engine<VALTYPE>& MM(matrix_type mtp1, matrix_type mtp2)
    {
      return *_m_binary[mtp1][mtp2];
    }

    static inline mmm_ternary_engine<VALTYPE>& MMM(matrix_type mtpa, matrix_type mtpb, 
							      matrix_type mtpc)
    {
      return *_m_ternary[mtpa][mtpb][mtpc];
    }

    static inline v_unary_engine<VALTYPE>& V(vector_type vtp)
    {
      return *_v_unary[vtp];
    }

    static inline vv_binary_engine<VALTYPE>& VV(vector_type vtp1, vector_type vtp2)
    {
      return *_v_binary[vtp1][vtp2];
    }

    static inline vm_binary_engine<VALTYPE>& VM(vector_type vtp, matrix_type mtp)
    {
      return *_vm_binary[vtp][mtp];
    }

    static inline vmv_ternary_engine<VALTYPE>& VMV(vector_type vtp1, matrix_type mtp, vector_type vtp2)
    {
      return *_vmv_ternary[vtp1][mtp][vtp2];
    }

  };

  /* ======================================================== *
   *                                                          *
   *                 Specialization of "engines"              *
   *                                                          *
   * ======================================================== */


  // ------------------------------------------------------------
  //
  //             unary_matrix_engine implementation 
  // ------------------------------------------------------------

  template<class VALTYPE, matrix_type MTRTYPE>
  class m_unary : public m_unary_engine<VALTYPE> {
  public:

    virtual matrix_expression<VALTYPE>& create(matrix_shape shp)
    {
      /* debug
      std::cout << "m_unary " << _lace_storage::mtype_spelling[MTRTYPE] << " called\n";
      shp.debug();
      */
      return * new matrix<VALTYPE,MTRTYPE>(shp);
    }

    virtual void scale(matrix_expression<VALTYPE> &a, VALTYPE s)
    {
      matrix<VALTYPE,MTRTYPE> *A = (matrix<VALTYPE,MTRTYPE>*)(&a);
      _lace_storage::scale_mtr(*(A->_mtr),s);
    }

    virtual void scale(matrix_expression<VALTYPE> &a, VALTYPE s, sub I, sub J)
    {
      matrix<VALTYPE,MTRTYPE> *A = (matrix<VALTYPE,MTRTYPE>*)(&a);
      _lace_storage::scale_mtr(*(A->_mtr),s,I,J);
    }

    virtual void fill(matrix_expression<VALTYPE> &a, VALTYPE s)
    {
      matrix<VALTYPE,MTRTYPE> *A = (matrix<VALTYPE,MTRTYPE>*)(&a);
      _lace_storage::fill_mtr(*(A->_mtr),s);
    }

    virtual void fill(matrix_expression<VALTYPE> &a, VALTYPE s, sub I, sub J)
    {
      matrix<VALTYPE,MTRTYPE> *A = (matrix<VALTYPE,MTRTYPE>*)(&a);
      _lace_storage::fill_mtr(*(A->_mtr),s,I,J);
    }

    virtual VALTYPE * ptr(matrix_expression<VALTYPE> &a, int i, int j)
    {
      matrix<VALTYPE,MTRTYPE> *A = (matrix<VALTYPE,MTRTYPE>*)(&a);
      return &((*A)(i,j));
    }

 };

  // ------------------------------------------------------------
  //             unary_vector_engine implementation 
  // ------------------------------------------------------------

  template<typename VALTYPE, vector_type VTYPE>
  class v_unary : public v_unary_engine<VALTYPE>
  {
  public:

    virtual vector_expression<VALTYPE>& create(vector_shape shp)
    {
      return * new vector<VALTYPE,VTYPE>(shp);
    }

    virtual void scale(vector_expression<VALTYPE> &a, VALTYPE s)
    {
      vector<VALTYPE,VTYPE> * _a = (vector<VALTYPE,VTYPE> *)(&a);
      _lace_storage::scale_vtr(*(_a->_vtr),s);
    }

    virtual void scale(vector_expression<VALTYPE> &a, VALTYPE s, sub I)
    {     
      vector<VALTYPE,VTYPE> *_a = (vector<VALTYPE,VTYPE>*)(&a);
      _lace_storage::scale_vtr(*(_a->_vtr),s,I);
    }

    virtual void fill(vector_expression<VALTYPE> &a, VALTYPE s)
    {
      vector<VALTYPE,VTYPE> * _a = (vector<VALTYPE,VTYPE> *)(&a);
      _lace_storage::fill_vtr(*(_a->_vtr),s);
    }

    virtual void fill(vector_expression<VALTYPE> &a, VALTYPE s, sub I)
    {     
      vector<VALTYPE,VTYPE> *_a = (vector<VALTYPE,VTYPE>*)(&a);
      _lace_storage::fill_vtr(*(_a->_vtr),s,I);
    }

    virtual VALTYPE * ptr(vector_expression<VALTYPE> &a, int i)
    {
      vector<VALTYPE,VTYPE> *_a = (vector<VALTYPE,VTYPE>*)(&a);
      return &((*_a)(i));
    }

 };

  // -----------------------------------------------------------------------

  template<class VALTYPE, matrix_type MTP_DST, matrix_type MTP_SRC>
  class m_convertor : public m_convertor_engine<VALTYPE>
  {
   public:    
    
    //--------------------------------------------------------------------------------//
    
    virtual void convert( matrix_expression<VALTYPE> &dest, matrix_expression<VALTYPE> &src)
    {
      matrix<VALTYPE,MTP_DST> *DST = (matrix<VALTYPE,MTP_DST>*)(&dest);  
      matrix<VALTYPE,MTP_SRC> *SRC = (matrix<VALTYPE,MTP_SRC>*)(&src);

      _lace_storage::convert_mtr(*(DST->_mtr),*(SRC->_mtr));
    }

    virtual void convert( matrix_expression<VALTYPE> &dest, sub IA, sub JA,
			  matrix_expression<VALTYPE> &src,  sub IB, sub JB)
    {
      matrix<VALTYPE,MTP_DST> *DST = (matrix<VALTYPE,MTP_DST>*)(&dest);  
      matrix<VALTYPE,MTP_SRC> *SRC = (matrix<VALTYPE,MTP_SRC>*)(&src);
      
      _lace_storage::convert_mtr(*(DST->_mtr), IA, JA, *(SRC->_mtr), IB, JB);
    }

    /*
    virtual matrix_expression<VALTYPE>& convert(matrix_expression<VALTYPE> &src)
    {
      matrix<VALTYPE,MTP_DST> *DST = new matrix<VALTYPE,MTP_DST>( reshape(src) );
      convert(*DST,src);
      return *DST;
    }
    */
  };

  // -----------------------------------------------------------------------

  template<class VALTYPE, vector_type VTP_DST, vector_type VTP_SRC>
  class v_convertor : public v_convertor_engine<VALTYPE>{
  public:
    

    virtual void convert( vector_expression<VALTYPE> &dest, sub Iu,
			  vector_expression<VALTYPE> &src,  sub Iv)
    {
      vector<VALTYPE,VTP_DST> *DEST = (vector<VALTYPE,VTP_DST>*)(&dest);
      vector<VALTYPE,VTP_SRC> *SRC  = (vector<VALTYPE,VTP_DST>*)(&src);
      
      _lace_storage::convert_vtr(*(DEST->_vtr), Iu, *(SRC->_vtr), Iv);
    }
    
    virtual void convert( vector_expression<VALTYPE> &dest, vector_expression<VALTYPE> &src)
    {
      assert(vtr_is_convertable(dest.shape(), src.shape()));
      vector<VALTYPE,VTP_DST> *DEST = (vector<VALTYPE,VTP_DST>*)(&dest);
      vector<VALTYPE,VTP_SRC> *SRC  = (vector<VALTYPE,VTP_DST>*)(&src);

      _lace_storage::convert_vtr(*(DEST->_vtr),*(SRC->_vtr));
    }

  };

  //---------------------------------------------------------------------------//
  //                                                                           //
  //                  binary_martix_engine implamentation                      //
  //---------------------------------------------------------------------------//

  template<class VALTYPE, matrix_type MTP_DST, matrix_type MTP_SRC>
  class mm_binary : public mm_binary_engine<VALTYPE>
  {
   public:

    virtual void MpM(matrix_expression<VALTYPE> &a, matrix_expression<VALTYPE> &b, 
		     VALTYPE beta, int OP = 0)
    {
      matrix<VALTYPE,MTP_DST> *A = (matrix<VALTYPE,MTP_DST>*)(&a);
      matrix<VALTYPE,MTP_SRC> *B = (matrix<VALTYPE,MTP_SRC>*)(&b);
      _lace_storage::add_mtr(*(A->_mtr), *(B->_mtr), beta, OP);
    }

    virtual void MpM(matrix_expression<VALTYPE> &a, sub IA, sub JA, 
		     matrix_expression<VALTYPE> &b, sub IB, sub JB, 
		     VALTYPE beta, int OP = 0 )
    {
      matrix<VALTYPE,MTP_DST> *A = (matrix<VALTYPE,MTP_DST>*)(&a);
      matrix<VALTYPE,MTP_SRC> *B = (matrix<VALTYPE,MTP_SRC>*)(&b);
      
      _lace_storage::add_mtr(*(A->_mtr), IA,JA, *(B->_mtr), IB, JB, beta, OP);
    }

  };

  //---------------------------------------------------------------------------//
  //                                                                           //
  //                  binary_vector_engine implamentation                      //
  //---------------------------------------------------------------------------//
  
  template<class VALTYPE, vector_type VTP_DST, vector_type VTP_SRC>
  class vv_binary : public vv_binary_engine<VALTYPE>{
  public:
    
    virtual void VpV(vector_expression<VALTYPE> &u, vector_expression<VALTYPE> &v,
		     VALTYPE beta)
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);
 
      _lace_storage::add_vtr(*(U->_vtr),*(V->_vtr),beta);
    }

    virtual void VpV(vector_expression<VALTYPE> &u, sub Iu,
		     vector_expression<VALTYPE> &v, sub Iv,
		     VALTYPE beta )
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);

      _lace_storage::add_vtr(*(U->_vtr), Iu, *(V->_vtr), Iv, beta);
    }

  };
     
  template<class VALTYPE, vector_type VTP, matrix_type MTP>
  class vm_binary: public vm_binary_engine<VALTYPE>{
  public:

    virtual void MIj(vector_expression<VALTYPE> &v, matrix_expression<VALTYPE> &m, 
		     int j, VALTYPE beta)
    {
      vector<VALTYPE,VTP> *V = (vector<VALTYPE,VTP>*)(&v);
      matrix<VALTYPE,MTP> *M = (matrix<VALTYPE,MTP>*)(&m);

      _lace_storage::mtr_column(*(V->_vtr), *(M->_mtr),j);
    }

    virtual void MIj(vector_expression<VALTYPE> &v, sub Iv, matrix_expression<VALTYPE> &m, 
		     sub Im, int j, VALTYPE beta)
    {
      vector<VALTYPE,VTP> *V = (vector<VALTYPE,VTP>*)(&v);
      matrix<VALTYPE,MTP> *M = (matrix<VALTYPE,MTP>*)(&m);

      _lace_storage::mtr_column(*(V->_vtr), Iv, *(M->_mtr), Im, j);
    }

    virtual void MiJ(vector_expression<VALTYPE> &v, matrix_expression<VALTYPE> &m, 
		     int i, VALTYPE beta)
    {
      vector<VALTYPE,VTP> *V = (vector<VALTYPE,VTP>*)(&v);
      matrix<VALTYPE,MTP> *M = (matrix<VALTYPE,MTP>*)(&m);

      _lace_storage::mtr_row(*(V->_vtr), *(M->_mtr),i);
    }

    virtual void MiJ(vector_expression<VALTYPE> &v, sub Jv, matrix_expression<VALTYPE> &m, 
		     int i, sub Jm, VALTYPE beta)
    {
      vector<VALTYPE,VTP> *V = (vector<VALTYPE,VTP>*)(&v);
      matrix<VALTYPE,MTP> *M = (matrix<VALTYPE,MTP>*)(&m);

      _lace_storage::mtr_row(*(V->_vtr), Jv, *(M->_mtr), i, Jm);
    }


  };

  //--------------------------------------------------------//
  //                  Matrix multiplication                 //
  //--------------------------------------------------------//

  template<class VALTYPE,matrix_type MTPA,matrix_type MTPB,matrix_type MTPC>
  class mmm_ternary : public mmm_ternary_engine<VALTYPE> {
  public:
        
    virtual void MxM(matrix_expression<VALTYPE> &a, matrix_expression<VALTYPE> &b, 
		     matrix_expression<VALTYPE> &c, VALTYPE alpha, VALTYPE beta,
		     int OP_B = 0, int OP_C = 0)
    {
      matrix<VALTYPE,MTPA> *A = (matrix<VALTYPE,MTPA>*)(&a);
      matrix<VALTYPE,MTPB> *B = (matrix<VALTYPE,MTPB>*)(&b);
      matrix<VALTYPE,MTPC> *C = (matrix<VALTYPE,MTPC>*)(&c); 

      _lace_storage::mul_mtr(*(A->_mtr), *(B->_mtr), *(C->_mtr), alpha, beta, OP_B, OP_C);
    }
    
    virtual void MxM(matrix_expression<VALTYPE> &a, sub IA, sub JA,
		     matrix_expression<VALTYPE> &b, sub IB, sub JB,
		     matrix_expression<VALTYPE> &c, sub IC, sub JC,
		     VALTYPE alpha, VALTYPE beta,
		     int OP_B = 0, int OP_C = 0)
    {
      matrix<VALTYPE,MTPA> *A = (matrix<VALTYPE,MTPA>*)(&a);
      matrix<VALTYPE,MTPB> *B = (matrix<VALTYPE,MTPB>*)(&b);
      matrix<VALTYPE,MTPC> *C = (matrix<VALTYPE,MTPC>*)(&c); 

      _lace_storage::mul_mtr(*(A->_mtr), IA, JA, 
			     *(B->_mtr), IB, JB,
			     *(C->_mtr), IC, JC, 
			     alpha, beta, OP_B, OP_C);      
    }
    
  };
  
  // --------------------------------------------------------
  //   Matrix by vector and outer product
  // --------------------------------------------------------


  template<typename VALTYPE, vector_type VTP_DST, matrix_type MTP, vector_type VTP_SRC>
  class vmv_ternary : public vmv_ternary_engine<VALTYPE>{
  public:

    virtual void MxV(vector_expression<VALTYPE> &u, matrix_expression<VALTYPE> &a,
		     vector_expression<VALTYPE> &v, VALTYPE alpha, VALTYPE beta, int OP = 0 )
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      matrix<VALTYPE,MTP>     *A = (matrix<VALTYPE,MTP>*)(&a);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);

      _lace_storage::mul_mv(*(U->_vtr),*(A->_mtr),*(V->_vtr),alpha,beta,OP);
    }

    virtual void MxV(vector_expression<VALTYPE> &u, sub Iu,
		     matrix_expression<VALTYPE> &a, sub IA, sub JA,
		     vector_expression<VALTYPE> &v, sub Jv,
		     VALTYPE alpha, VALTYPE beta, int OP = 0 )
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      matrix<VALTYPE,MTP>     *A = (matrix<VALTYPE,MTP>*)(&a);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);

      _lace_storage::mul_mv(*(U->_vtr), Iu, *(A->_mtr), IA, JA, *(V->_vtr), Jv, alpha, beta, OP);
    }
    
    virtual void VxV(matrix_expression<VALTYPE> &a, vector_expression<VALTYPE> &u, 
		     vector_expression<VALTYPE> &v, VALTYPE alpha, VALTYPE beta )
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      matrix<VALTYPE,MTP>     *A = (matrix<VALTYPE,MTP>*)(&a);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);

      _lace_storage::outer_prod(*(A->_mtr), *(U->_vtr), *(V->_vtr), alpha, beta);
    }
    
    virtual void VxV(matrix_expression<VALTYPE> &a, sub IA, sub JA,
		     vector_expression<VALTYPE> &u, sub Iu,
		     vector_expression<VALTYPE> &v, sub Jv,
		     VALTYPE alpha, VALTYPE beta )
    {
      vector<VALTYPE,VTP_DST> *U = (vector<VALTYPE,VTP_DST>*)(&u);
      matrix<VALTYPE,MTP>     *A = (matrix<VALTYPE,MTP>*)(&a);
      vector<VALTYPE,VTP_SRC> *V = (vector<VALTYPE,VTP_SRC>*)(&v);

      _lace_storage::outer_prod(*(A->_mtr), IA, JA, *(U->_vtr), Iu, *(V->_vtr), Jv, alpha, beta);
    } 
    
  };

};

#endif
