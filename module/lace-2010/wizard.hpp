
#ifndef _LACE_WIZARD_H
#define _LACE_WIZARD_H

//#include <lace/shape.hpp>
//#include <lace/storage.hpp>
#include <lace/matrix.hpp>
#include <lace/vector.hpp>
//#include <lace/expressions.hpp>

// Forward declarations
namespace _lace_main{

  using _lace_storage::matrix_type;
  using _lace_storage::n_matrix_type;

  using _lace_storage::vector_type;
  using _lace_storage::n_vector_type;

  using _lace_storage::rectang;    
  using _lace_storage::symmetric;  
  using _lace_storage::hermitian;  
  using _lace_storage::banddiag;   
  using _lace_storage::symmband;   
  using _lace_storage::hermband;   
  using _lace_storage::triang;      
  using _lace_expressions::matrix_expression;
  using _lace_expressions::vector_expression;
  using _lace_storage::matrix_type;
  using _lace_storage::matrix_shape;
  using _lace_storage::vector_type;
  using _lace_storage::vector_shape;
  using _lace_expressions::sub;


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

    virtual void setval(matrix_expression<VALTYPE> &a, VALTYPE s) =0;

    virtual void scale(matrix_expression<VALTYPE> &a, VALTYPE s, sub I, sub J) =0;

    virtual void setval(matrix_expression<VALTYPE> &a, VALTYPE s, sub I, sub J) =0;

    virtual matrix_shape T_shape(matrix_shape shp) =0;
    
    virtual matrix_shape MIJ_shape(matrix_shape shp, sub I, sub J ) =0;

    virtual vector_shape MIj_shape(matrix_shape shp, sub I, int j) = 0;

    virtual vector_shape MiJ_shape(matrix_shape shp, int i, sub J) = 0;

  };

  //------------------------------------------------------------------

  template<typename VALTYPE>
  class v_unary_engine{
  public:

    virtual vector_expression<VALTYPE>& create(vector_shape shp) =0;

    virtual void scale(vector_expression<VALTYPE> &a, VALTYPE s) =0;

    virtual void setval(vector_expression<VALTYPE> &a, VALTYPE s) =0;

    virtual void scale(vector_expression<VALTYPE> &a, VALTYPE s, sub I) =0;

    virtual void setval(vector_expression<VALTYPE> &a, VALTYPE s, sub I) =0;

    virtual vector_shape VI_shape(vector_shape shp, sub I ) =0;  
  };

  // ----------------- Convertors ----------------------

  template<class VALTYPE>
  class m_convertor_engine{
  public:
    
    virtual bool is_convertable(matrix_shape dest, matrix_shape src) =0;

    virtual matrix_shape reshape(matrix_shape src) =0;

    virtual matrix_shape reshape(matrix_expression<VALTYPE> &src) =0;

    virtual void convert( matrix_expression<VALTYPE> &dest, sub IA, sub JA,
			  matrix_expression<VALTYPE> &src,  sub IB, sub JB) =0;

    virtual void convert( matrix_expression<VALTYPE> &dest, matrix_expression<VALTYPE> &src) =0;

    virtual matrix_expression<VALTYPE>& convert(matrix_expression<VALTYPE> &src) =0;
  };

  template<class VALTYPE>
  class v_convertor_engine{
  public:
    
    virtual bool is_convertable(vector_shape dest, vector_shape src) =0;

//     virtual vector_shape reshape(vector_shape src) =0;

//     virtual vector_shape reshape(vector_expression<VALTYPE> &src) =0;

    virtual void convert( vector_expression<VALTYPE> &dest, sub Iu,
			  vector_expression<VALTYPE> &src,  sub Iv) =0;
    
    virtual void convert( vector_expression<VALTYPE> &dest, vector_expression<VALTYPE> &src) =0;
    
//     virtual vector_expression<VALTYPE>& convert(vector_expression<VALTYPE> &src) =0;
  };
    
  // -------------------- Binary operations ------------------

  template<class VALTYPE>
  class mm_binary_engine{
  public:
    
//     virtual bool is_addable(matrix_shape dest, matrix_shape src) =0;

//     virtual bool is_multiplicable(matrix_shape shp1, matrix_shape shp2) =0;

    virtual matrix_shape MpM_shape(matrix_shape shp1, matrix_shape shp2) =0;

    virtual matrix_shape MxM_shape(matrix_shape shp1, matrix_shape shp2) =0;
    // we put is_multiplicable() and multiplic_shape() into summator since they depend only
    // on two mtype parameters

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
    
    virtual bool is_addable(vector_shape dest, vector_shape src) =0;

    virtual vector_shape VpV_shape(vector_shape shp1, vector_shape shp2) =0;

    //    virtual matrix_shape prod_shape(matrix_shape shp1, matrix_shape shp2) =0;
    // we put is_multiplicable() and multiplic_shape() into summator since they depend only
    // on two mtype parameters

    virtual matrix_shape VxV_shape(vector_shape shp1, vector_shape shp2) =0;

    virtual void VpV(vector_expression<VALTYPE> &u, vector_expression<VALTYPE> &v, 
		       VALTYPE beta) =0;
    // performes A = A + beta*B;

    virtual void VpV(vector_expression<VALTYPE> &u, sub Iu,
		     vector_expression<VALTYPE> &v, sub Iv,
		     VALTYPE beta ) =0;
    // performes A(IA,JA) = A(IA,JA) + beta*B(IB,JB);

  };

  //------------------------------------------------------------------

  template<class VALTYPE>
  class vm_binary_engine{
  public:

    virtual bool MIj_conform(vector_shape vshp, matrix_shape mshp, sub I, int j) =0;

    virtual bool MiJ_conform(vector_shape vshp, matrix_shape mshp, int i, sub J) =0;

    virtual void MIj(vector_expression<VALTYPE> &v, matrix_expression<VALTYPE> &M, sub I, int j) =0;

    virtual void MiJ(vector_expression<VALTYPE> &v, matrix_expression<VALTYPE> &M, int i, sub J) =0;

    virtual vector_shape MxV_shape(matrix_shape mshp, vector_shape vshp) = 0;

//     virtual bool V2D_conform(matrix_shape mshp, vector_shape vshp) =0;

//     virtual bool D2V_conform(vector_shape vshp, matrix_shape mshp) =0;

//     virtual void V2D(matrix_expression<VALTYPE> &M, vector_expression<VALTYPE> &v) =0;

//     virtual void D2V(vector_expression<VALTYPE> &v, matrix_expression<VALTYPE> &M) =0;

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

    virtual bool MxV_conform(vector_shape dst, matrix_shape mshp, vector_shape src) =0;

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
    static m_unary_engine<VALTYPE>       *_m_unary       [n_matrix_type];
    static m_convertor_engine<VALTYPE>   *_m_convertor   [n_matrix_type][n_matrix_type];
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

};

#endif
