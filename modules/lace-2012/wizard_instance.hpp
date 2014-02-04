#ifndef _LACE_WIZARD_INSTANCE_H
#define _LACE_WIZARD_INSTANCE_H

#include <lace-2012/wizard.hpp>

namespace _lace_main{


  /* -------------------------------------------------------- *
   *              The wizard class instantiation              *
   * -------------------------------------------------------- */

  template<class VALTYPE>
  m_unary_engine<VALTYPE> *wizard<VALTYPE>::_m_unary [n_matrix_type] = 
    {
      new default_m_unary<VALTYPE,rectang>,      
      new default_m_unary<VALTYPE,symmetric>,	 
      new default_m_unary<VALTYPE,hermitian>//,    
      //     new default_m_unary<VALTYPE,banddiag>,	 
      //     new default_m_unary<VALTYPE,symmband>,     
      //     new default_m_unary<VALTYPE,hermband>,  	 
      //     new default_m_unary<VALTYPE,triang>
    };

  template<class VALTYPE>
  v_unary_engine<VALTYPE> *wizard<VALTYPE>::_v_unary [n_vector_type] =
    {
      new default_v_unary<VALTYPE,dense>//,
      //      new default_v_unary<VALTYPE,sparse>
    };

  template<class VALTYPE>
  m_convertor_engine<VALTYPE> *wizard<VALTYPE>::_m_convertor [n_matrix_type][n_matrix_type] = 
    { 
      {
	new copy_m_convertor<VALTYPE,rectang,rectang>,
	new default_m_convertor<VALTYPE,rectang,symmetric>,
      }, 
      {
	new default_m_convertor<VALTYPE,symmetric,rectang>, 
	new copy_m_convertor<VALTYPE,symmetric,symmetric>
      } 
    };

  template<class VALTYPE>
  v_convertor_engine<VALTYPE> *wizard<VALTYPE>::_v_convertor [n_vector_type][n_vector_type] = 
    { 
      {
	new default_v_convertor<VALTYPE,dense,dense>
      }
    };

  template<class VALTYPE>
  mm_binary_engine<VALTYPE> *wizard<VALTYPE>::_m_binary [n_matrix_type][n_matrix_type] = 
    { 
      {
	new rectang_mm_binary<VALTYPE>,      
	new default_mm_binary<VALTYPE,rectang,symmetric>,	 
	new default_mm_binary<VALTYPE,rectang,hermitian>// ,    
// 	new default_mm_binary<VALTYPE,rectang,banddiag>,	 
// 	new default_mm_binary<VALTYPE,rectang,symmband>,     
// 	new default_mm_binary<VALTYPE,rectang,hermband>,  	 
// 	new default_mm_binary<VALTYPE,rectang,triang>  	 
      }, 
      {
	new default_mm_binary<VALTYPE,symmetric,rectang>,    
	new default_mm_binary<VALTYPE,symmetric,symmetric>,	 
	new default_mm_binary<VALTYPE,symmetric,hermitian>// ,  
// 	new default_mm_binary<VALTYPE,symmetric,banddiag>,	 
// 	new default_mm_binary<VALTYPE,symmetric,symmband>,   
// 	new default_mm_binary<VALTYPE,symmetric,hermband>,   
// 	new default_mm_binary<VALTYPE,symmetric,triang>  	 
      },
      {
	new default_mm_binary<VALTYPE,hermitian,rectang>,    
	new default_mm_binary<VALTYPE,hermitian,symmetric>,	 
	new default_mm_binary<VALTYPE,hermitian,hermitian>// ,  
// 	new default_mm_binary<VALTYPE,hermitian,banddiag>,	 
// 	new default_mm_binary<VALTYPE,hermitian,symmband>,   
// 	new default_mm_binary<VALTYPE,hermitian,hermband>,   
// 	new default_mm_binary<VALTYPE,hermitian,triang>  	 
      }// ,
//       {
// 	new default_mm_binary<VALTYPE,banddiag,rectang>,    
// 	new default_mm_binary<VALTYPE,banddiag,symmetric>,	 
// 	new default_mm_binary<VALTYPE,banddiag,hermitian>,  
// 	new default_mm_binary<VALTYPE,banddiag,banddiag>,	 
// 	new default_mm_binary<VALTYPE,banddiag,symmband>,   
// 	new default_mm_binary<VALTYPE,banddiag,hermband>,   
// 	new default_mm_binary<VALTYPE,banddiag,triang>  	 
//       },
//       {
// 	new default_mm_binary<VALTYPE,symmband,rectang>,    
// 	new default_mm_binary<VALTYPE,symmband,symmetric>,	 
// 	new default_mm_binary<VALTYPE,symmband,hermitian>,  
// 	new default_mm_binary<VALTYPE,symmband,banddiag>,	 
// 	new default_mm_binary<VALTYPE,symmband,symmband>,   
// 	new default_mm_binary<VALTYPE,symmband,hermband>,   
// 	new default_mm_binary<VALTYPE,symmband,triang>  	 
//       },
//       {
// 	new default_mm_binary<VALTYPE,hermband,rectang>,    
// 	new default_mm_binary<VALTYPE,hermband,symmetric>,	 
// 	new default_mm_binary<VALTYPE,hermband,hermitian>,  
// 	new default_mm_binary<VALTYPE,hermband,banddiag>,	 
// 	new default_mm_binary<VALTYPE,hermband,symmband>,   
// 	new default_mm_binary<VALTYPE,hermband,hermband>,   
// 	new default_mm_binary<VALTYPE,hermband,triang>  	 
//       },
//       {
// 	new default_mm_binary<VALTYPE,triang,rectang>,    
// 	new default_mm_binary<VALTYPE,triang,symmetric>,	 
// 	new default_mm_binary<VALTYPE,triang,hermitian>,  
// 	new default_mm_binary<VALTYPE,triang,banddiag>,	 
// 	new default_mm_binary<VALTYPE,triang,symmband>,   
// 	new default_mm_binary<VALTYPE,triang,hermband>,   
// 	new default_mm_binary<VALTYPE,triang,triang>  	 
//      }
    };

  template<typename VALTYPE>
  vv_binary_engine<VALTYPE> *wizard<VALTYPE>::_v_binary [n_vector_type][n_vector_type] =
    {
      {new default_vv_binary<VALTYPE,dense,dense>}
    };

  template<typename VALTYPE>
  vm_binary_engine<VALTYPE> *wizard<VALTYPE>::_vm_binary[n_vector_type][n_matrix_type]=
    {
      {
	new default_vm_binary<VALTYPE,dense,rectang>,
	new default_vm_binary<VALTYPE,dense,symmetric>
      }
    };

  template<class VALTYPE>
  mmm_ternary_engine<VALTYPE> *wizard<VALTYPE>::_m_ternary [n_matrix_type][n_matrix_type][n_matrix_type] = 
    { 
      {
	{
	  new blas_mmm_ternary<VALTYPE,rectang,rectang,rectang>,      
	  new default_mmm_ternary<VALTYPE,rectang,rectang,symmetric>
	},
	{
	  new default_mmm_ternary<VALTYPE,rectang,symmetric,rectang>,      
	  new default_mmm_ternary<VALTYPE,rectang,symmetric,symmetric>
	}
      }
    };

  template<typename VALTYPE>
  vmv_ternary_engine<VALTYPE> *wizard<VALTYPE>::_vmv_ternary [n_vector_type][n_matrix_type][n_vector_type] = 
    {
      {
	{
	  new default_vmv_ternary<VALTYPE,dense,rectang,dense>
	},
	{
	  new default_vmv_ternary<VALTYPE,dense,symmetric,dense>
	}
      }
    };

};

#endif
