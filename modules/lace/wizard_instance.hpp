#ifndef _LACE_WIZARD_INSTANCE_H
#define _LACE_WIZARD_INSTANCE_H

#include <lace/wizard.hpp>

namespace _lace_main{


  /* -------------------------------------------------------- *
   *              The wizard class instantiation              *
   * -------------------------------------------------------- */

  template<class VALTYPE>
  m_unary_engine<VALTYPE> *wizard<VALTYPE>::_m_unary [n_matrix_type] = 
    {
      new m_unary<VALTYPE,rectang>,      
      new m_unary<VALTYPE,symmetric>,	 
      new m_unary<VALTYPE,hermitian>, 
      new m_unary<VALTYPE,banddiag>,	 
      new m_unary<VALTYPE,symmband>,     
      new m_unary<VALTYPE,hermband>,  	 
      new m_unary<VALTYPE,triang>
    };

  template<class VALTYPE>
  v_unary_engine<VALTYPE> *wizard<VALTYPE>::_v_unary [n_vector_type] =
    {
      new v_unary<VALTYPE,dense>//,
      //      new v_unary_engine<VALTYPE,sparse>
    };

  template<class VALTYPE>
  m_convertor_engine<VALTYPE> *wizard<VALTYPE>::_m_convertor [n_matrix_type][n_matrix_type] = 
    { 
      {
	new m_convertor<VALTYPE,rectang,rectang>,
	new m_convertor<VALTYPE,rectang,symmetric>,
	new m_convertor<VALTYPE,rectang,hermitian>
      }, 
      {
	new m_convertor<VALTYPE,symmetric,rectang>, 
	new m_convertor<VALTYPE,symmetric,symmetric>,
	new m_convertor<VALTYPE,symmetric,hermitian>
      },
      {
	new m_convertor<VALTYPE,hermitian,rectang>, 
	new m_convertor<VALTYPE,hermitian,symmetric>,
	new m_convertor<VALTYPE,hermitian,hermitian>
      } 
    };
  
  template<class VALTYPE>
  v_convertor_engine<VALTYPE> *wizard<VALTYPE>::_v_convertor [n_vector_type][n_vector_type] = 
    { 
      {
	new v_convertor<VALTYPE,dense,dense>
      }
    };
  
  template<class VALTYPE>
  mm_binary_engine<VALTYPE> *wizard<VALTYPE>::_m_binary [n_matrix_type][n_matrix_type] = 
    { 
      {
	new mm_binary<VALTYPE,rectang,rectang>,      
	new mm_binary<VALTYPE,rectang,symmetric>,	 
	new mm_binary<VALTYPE,rectang,hermitian>// ,    
// 	new mm_binary<VALTYPE,rectang,banddiag>,	 
// 	new mm_binary<VALTYPE,rectang,symmband>,     
// 	new mm_binary<VALTYPE,rectang,hermband>,  	 
// 	new mm_binary<VALTYPE,rectang,triang>  	 
      }, 
      {
	new mm_binary<VALTYPE,symmetric,rectang>,    
	new mm_binary<VALTYPE,symmetric,symmetric>,	 
	new mm_binary<VALTYPE,symmetric,hermitian>// ,  
// 	new default_mm_binary<VALTYPE,symmetric,banddiag>,	 
// 	new default_mm_binary<VALTYPE,symmetric,symmband>,   
// 	new default_mm_binary<VALTYPE,symmetric,hermband>,   
// 	new default_mm_binary<VALTYPE,symmetric,triang>  	 
      },
      {
	new mm_binary<VALTYPE,hermitian,rectang>,    
	new mm_binary<VALTYPE,hermitian,symmetric>,	 
	new mm_binary<VALTYPE,hermitian,hermitian>// ,  
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
      {new vv_binary<VALTYPE,dense,dense>}
    };
  
  template<typename VALTYPE>
  vm_binary_engine<VALTYPE> *wizard<VALTYPE>::_vm_binary[n_vector_type][n_matrix_type]=
    {
      {
	new vm_binary<VALTYPE,dense,rectang>,
	new vm_binary<VALTYPE,dense,symmetric>,
	new vm_binary<VALTYPE,dense,hermitian>
      }
    };
  
  template<class VALTYPE>
  mmm_ternary_engine<VALTYPE> *wizard<VALTYPE>::_m_ternary [n_matrix_type][n_matrix_type][n_matrix_type] = 
    { 
      {
        {
          new mmm_ternary<VALTYPE,rectang,rectang,rectang>,
          new mmm_ternary<VALTYPE,rectang,rectang,symmetric>,
          new mmm_ternary<VALTYPE,rectang,rectang,hermitian>,
          new mmm_ternary<VALTYPE,rectang,rectang,banddiag>,
          new mmm_ternary<VALTYPE,rectang,rectang,symmband>,
          new mmm_ternary<VALTYPE,rectang,rectang,hermband>,
          new mmm_ternary<VALTYPE,rectang,rectang,triang>
        },
        {
          new mmm_ternary<VALTYPE,rectang,symmetric,rectang>,
          new mmm_ternary<VALTYPE,rectang,symmetric,symmetric>,
          new mmm_ternary<VALTYPE,rectang,symmetric,hermitian>,
          new mmm_ternary<VALTYPE,rectang,symmetric,banddiag>,
          new mmm_ternary<VALTYPE,rectang,symmetric,symmband>,
          new mmm_ternary<VALTYPE,rectang,symmetric,hermband>,
          new mmm_ternary<VALTYPE,rectang,symmetric,triang>
        },
        {
          new mmm_ternary<VALTYPE,rectang,hermitian,rectang>,
          new mmm_ternary<VALTYPE,rectang,hermitian,symmetric>,
          new mmm_ternary<VALTYPE,rectang,hermitian,hermitian>,
          new mmm_ternary<VALTYPE,rectang,hermitian,banddiag>,
          new mmm_ternary<VALTYPE,rectang,hermitian,symmband>,
          new mmm_ternary<VALTYPE,rectang,hermitian,hermband>,
          new mmm_ternary<VALTYPE,rectang,hermitian,triang>
        },
        {
          new mmm_ternary<VALTYPE,rectang,banddiag,rectang>,
          new mmm_ternary<VALTYPE,rectang,banddiag,symmetric>,
          new mmm_ternary<VALTYPE,rectang,banddiag,hermitian>,
          new mmm_ternary<VALTYPE,rectang,banddiag,banddiag>,
          new mmm_ternary<VALTYPE,rectang,banddiag,symmband>,
          new mmm_ternary<VALTYPE,rectang,banddiag,hermband>,
          new mmm_ternary<VALTYPE,rectang,banddiag,triang>
        },
        {
          new mmm_ternary<VALTYPE,rectang,symmband,rectang>,
          new mmm_ternary<VALTYPE,rectang,symmband,symmetric>,
          new mmm_ternary<VALTYPE,rectang,symmband,hermitian>,
          new mmm_ternary<VALTYPE,rectang,symmband,banddiag>,
          new mmm_ternary<VALTYPE,rectang,symmband,symmband>,
          new mmm_ternary<VALTYPE,rectang,symmband,hermband>,
          new mmm_ternary<VALTYPE,rectang,symmband,triang>
        },
        {
          new mmm_ternary<VALTYPE,rectang,hermband,rectang>,
          new mmm_ternary<VALTYPE,rectang,hermband,symmetric>,
          new mmm_ternary<VALTYPE,rectang,hermband,hermitian>,
          new mmm_ternary<VALTYPE,rectang,hermband,banddiag>,
          new mmm_ternary<VALTYPE,rectang,hermband,symmband>,
          new mmm_ternary<VALTYPE,rectang,hermband,hermband>,
          new mmm_ternary<VALTYPE,rectang,hermband,triang>
        },
        {
          new mmm_ternary<VALTYPE,rectang,triang,rectang>,
          new mmm_ternary<VALTYPE,rectang,triang,symmetric>,
          new mmm_ternary<VALTYPE,rectang,triang,hermitian>,
          new mmm_ternary<VALTYPE,rectang,triang,banddiag>,
          new mmm_ternary<VALTYPE,rectang,triang,symmband>,
          new mmm_ternary<VALTYPE,rectang,triang,hermband>,
          new mmm_ternary<VALTYPE,rectang,triang,triang>
        }
      },
      {
        {
          new mmm_ternary<VALTYPE,symmetric,rectang,rectang>,
          new mmm_ternary<VALTYPE,symmetric,rectang,symmetric>,
          new mmm_ternary<VALTYPE,symmetric,rectang,hermitian>,
          new mmm_ternary<VALTYPE,symmetric,rectang,banddiag>,
          new mmm_ternary<VALTYPE,symmetric,rectang,symmband>,
          new mmm_ternary<VALTYPE,symmetric,rectang,hermband>,
          new mmm_ternary<VALTYPE,symmetric,rectang,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmetric,symmetric,rectang>,
          new mmm_ternary<VALTYPE,symmetric,symmetric,symmetric>,
          new mmm_ternary<VALTYPE,symmetric,symmetric,hermitian>,
          new mmm_ternary<VALTYPE,symmetric,symmetric,banddiag>,
          new mmm_ternary<VALTYPE,symmetric,symmetric,symmband>,
          new mmm_ternary<VALTYPE,symmetric,symmetric,hermband>,
          new mmm_ternary<VALTYPE,symmetric,symmetric,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmetric,hermitian,rectang>,
          new mmm_ternary<VALTYPE,symmetric,hermitian,symmetric>,
          new mmm_ternary<VALTYPE,symmetric,hermitian,hermitian>,
          new mmm_ternary<VALTYPE,symmetric,hermitian,banddiag>,
          new mmm_ternary<VALTYPE,symmetric,hermitian,symmband>,
          new mmm_ternary<VALTYPE,symmetric,hermitian,hermband>,
          new mmm_ternary<VALTYPE,symmetric,hermitian,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmetric,banddiag,rectang>,
          new mmm_ternary<VALTYPE,symmetric,banddiag,symmetric>,
          new mmm_ternary<VALTYPE,symmetric,banddiag,hermitian>,
          new mmm_ternary<VALTYPE,symmetric,banddiag,banddiag>,
          new mmm_ternary<VALTYPE,symmetric,banddiag,symmband>,
          new mmm_ternary<VALTYPE,symmetric,banddiag,hermband>,
          new mmm_ternary<VALTYPE,symmetric,banddiag,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmetric,symmband,rectang>,
          new mmm_ternary<VALTYPE,symmetric,symmband,symmetric>,
          new mmm_ternary<VALTYPE,symmetric,symmband,hermitian>,
          new mmm_ternary<VALTYPE,symmetric,symmband,banddiag>,
          new mmm_ternary<VALTYPE,symmetric,symmband,symmband>,
          new mmm_ternary<VALTYPE,symmetric,symmband,hermband>,
          new mmm_ternary<VALTYPE,symmetric,symmband,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmetric,hermband,rectang>,
          new mmm_ternary<VALTYPE,symmetric,hermband,symmetric>,
          new mmm_ternary<VALTYPE,symmetric,hermband,hermitian>,
          new mmm_ternary<VALTYPE,symmetric,hermband,banddiag>,
          new mmm_ternary<VALTYPE,symmetric,hermband,symmband>,
          new mmm_ternary<VALTYPE,symmetric,hermband,hermband>,
          new mmm_ternary<VALTYPE,symmetric,hermband,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmetric,triang,rectang>,
          new mmm_ternary<VALTYPE,symmetric,triang,symmetric>,
          new mmm_ternary<VALTYPE,symmetric,triang,hermitian>,
          new mmm_ternary<VALTYPE,symmetric,triang,banddiag>,
          new mmm_ternary<VALTYPE,symmetric,triang,symmband>,
          new mmm_ternary<VALTYPE,symmetric,triang,hermband>,
          new mmm_ternary<VALTYPE,symmetric,triang,triang>
        }
      },
      {
        {
          new mmm_ternary<VALTYPE,hermitian,rectang,rectang>,
          new mmm_ternary<VALTYPE,hermitian,rectang,symmetric>,
          new mmm_ternary<VALTYPE,hermitian,rectang,hermitian>,
          new mmm_ternary<VALTYPE,hermitian,rectang,banddiag>,
          new mmm_ternary<VALTYPE,hermitian,rectang,symmband>,
          new mmm_ternary<VALTYPE,hermitian,rectang,hermband>,
          new mmm_ternary<VALTYPE,hermitian,rectang,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermitian,symmetric,rectang>,
          new mmm_ternary<VALTYPE,hermitian,symmetric,symmetric>,
          new mmm_ternary<VALTYPE,hermitian,symmetric,hermitian>,
          new mmm_ternary<VALTYPE,hermitian,symmetric,banddiag>,
          new mmm_ternary<VALTYPE,hermitian,symmetric,symmband>,
          new mmm_ternary<VALTYPE,hermitian,symmetric,hermband>,
          new mmm_ternary<VALTYPE,hermitian,symmetric,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermitian,hermitian,rectang>,
          new mmm_ternary<VALTYPE,hermitian,hermitian,symmetric>,
          new mmm_ternary<VALTYPE,hermitian,hermitian,hermitian>,
          new mmm_ternary<VALTYPE,hermitian,hermitian,banddiag>,
          new mmm_ternary<VALTYPE,hermitian,hermitian,symmband>,
          new mmm_ternary<VALTYPE,hermitian,hermitian,hermband>,
          new mmm_ternary<VALTYPE,hermitian,hermitian,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermitian,banddiag,rectang>,
          new mmm_ternary<VALTYPE,hermitian,banddiag,symmetric>,
          new mmm_ternary<VALTYPE,hermitian,banddiag,hermitian>,
          new mmm_ternary<VALTYPE,hermitian,banddiag,banddiag>,
          new mmm_ternary<VALTYPE,hermitian,banddiag,symmband>,
          new mmm_ternary<VALTYPE,hermitian,banddiag,hermband>,
          new mmm_ternary<VALTYPE,hermitian,banddiag,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermitian,symmband,rectang>,
          new mmm_ternary<VALTYPE,hermitian,symmband,symmetric>,
          new mmm_ternary<VALTYPE,hermitian,symmband,hermitian>,
          new mmm_ternary<VALTYPE,hermitian,symmband,banddiag>,
          new mmm_ternary<VALTYPE,hermitian,symmband,symmband>,
          new mmm_ternary<VALTYPE,hermitian,symmband,hermband>,
          new mmm_ternary<VALTYPE,hermitian,symmband,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermitian,hermband,rectang>,
          new mmm_ternary<VALTYPE,hermitian,hermband,symmetric>,
          new mmm_ternary<VALTYPE,hermitian,hermband,hermitian>,
          new mmm_ternary<VALTYPE,hermitian,hermband,banddiag>,
          new mmm_ternary<VALTYPE,hermitian,hermband,symmband>,
          new mmm_ternary<VALTYPE,hermitian,hermband,hermband>,
          new mmm_ternary<VALTYPE,hermitian,hermband,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermitian,triang,rectang>,
          new mmm_ternary<VALTYPE,hermitian,triang,symmetric>,
          new mmm_ternary<VALTYPE,hermitian,triang,hermitian>,
          new mmm_ternary<VALTYPE,hermitian,triang,banddiag>,
          new mmm_ternary<VALTYPE,hermitian,triang,symmband>,
          new mmm_ternary<VALTYPE,hermitian,triang,hermband>,
          new mmm_ternary<VALTYPE,hermitian,triang,triang>
        }
      },
      {
        {
          new mmm_ternary<VALTYPE,banddiag,rectang,rectang>,
          new mmm_ternary<VALTYPE,banddiag,rectang,symmetric>,
          new mmm_ternary<VALTYPE,banddiag,rectang,hermitian>,
          new mmm_ternary<VALTYPE,banddiag,rectang,banddiag>,
          new mmm_ternary<VALTYPE,banddiag,rectang,symmband>,
          new mmm_ternary<VALTYPE,banddiag,rectang,hermband>,
          new mmm_ternary<VALTYPE,banddiag,rectang,triang>
        },
        {
          new mmm_ternary<VALTYPE,banddiag,symmetric,rectang>,
          new mmm_ternary<VALTYPE,banddiag,symmetric,symmetric>,
          new mmm_ternary<VALTYPE,banddiag,symmetric,hermitian>,
          new mmm_ternary<VALTYPE,banddiag,symmetric,banddiag>,
          new mmm_ternary<VALTYPE,banddiag,symmetric,symmband>,
          new mmm_ternary<VALTYPE,banddiag,symmetric,hermband>,
          new mmm_ternary<VALTYPE,banddiag,symmetric,triang>
        },
        {
          new mmm_ternary<VALTYPE,banddiag,hermitian,rectang>,
          new mmm_ternary<VALTYPE,banddiag,hermitian,symmetric>,
          new mmm_ternary<VALTYPE,banddiag,hermitian,hermitian>,
          new mmm_ternary<VALTYPE,banddiag,hermitian,banddiag>,
          new mmm_ternary<VALTYPE,banddiag,hermitian,symmband>,
          new mmm_ternary<VALTYPE,banddiag,hermitian,hermband>,
          new mmm_ternary<VALTYPE,banddiag,hermitian,triang>
        },
        {
          new mmm_ternary<VALTYPE,banddiag,banddiag,rectang>,
          new mmm_ternary<VALTYPE,banddiag,banddiag,symmetric>,
          new mmm_ternary<VALTYPE,banddiag,banddiag,hermitian>,
          new mmm_ternary<VALTYPE,banddiag,banddiag,banddiag>,
          new mmm_ternary<VALTYPE,banddiag,banddiag,symmband>,
          new mmm_ternary<VALTYPE,banddiag,banddiag,hermband>,
          new mmm_ternary<VALTYPE,banddiag,banddiag,triang>
        },
        {
          new mmm_ternary<VALTYPE,banddiag,symmband,rectang>,
          new mmm_ternary<VALTYPE,banddiag,symmband,symmetric>,
          new mmm_ternary<VALTYPE,banddiag,symmband,hermitian>,
          new mmm_ternary<VALTYPE,banddiag,symmband,banddiag>,
          new mmm_ternary<VALTYPE,banddiag,symmband,symmband>,
          new mmm_ternary<VALTYPE,banddiag,symmband,hermband>,
          new mmm_ternary<VALTYPE,banddiag,symmband,triang>
        },
        {
          new mmm_ternary<VALTYPE,banddiag,hermband,rectang>,
          new mmm_ternary<VALTYPE,banddiag,hermband,symmetric>,
          new mmm_ternary<VALTYPE,banddiag,hermband,hermitian>,
          new mmm_ternary<VALTYPE,banddiag,hermband,banddiag>,
          new mmm_ternary<VALTYPE,banddiag,hermband,symmband>,
          new mmm_ternary<VALTYPE,banddiag,hermband,hermband>,
          new mmm_ternary<VALTYPE,banddiag,hermband,triang>
        },
        {
          new mmm_ternary<VALTYPE,banddiag,triang,rectang>,
          new mmm_ternary<VALTYPE,banddiag,triang,symmetric>,
          new mmm_ternary<VALTYPE,banddiag,triang,hermitian>,
          new mmm_ternary<VALTYPE,banddiag,triang,banddiag>,
          new mmm_ternary<VALTYPE,banddiag,triang,symmband>,
          new mmm_ternary<VALTYPE,banddiag,triang,hermband>,
          new mmm_ternary<VALTYPE,banddiag,triang,triang>
        }
      },
      {
        {
          new mmm_ternary<VALTYPE,symmband,rectang,rectang>,
          new mmm_ternary<VALTYPE,symmband,rectang,symmetric>,
          new mmm_ternary<VALTYPE,symmband,rectang,hermitian>,
          new mmm_ternary<VALTYPE,symmband,rectang,banddiag>,
          new mmm_ternary<VALTYPE,symmband,rectang,symmband>,
          new mmm_ternary<VALTYPE,symmband,rectang,hermband>,
          new mmm_ternary<VALTYPE,symmband,rectang,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmband,symmetric,rectang>,
          new mmm_ternary<VALTYPE,symmband,symmetric,symmetric>,
          new mmm_ternary<VALTYPE,symmband,symmetric,hermitian>,
          new mmm_ternary<VALTYPE,symmband,symmetric,banddiag>,
          new mmm_ternary<VALTYPE,symmband,symmetric,symmband>,
          new mmm_ternary<VALTYPE,symmband,symmetric,hermband>,
          new mmm_ternary<VALTYPE,symmband,symmetric,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmband,hermitian,rectang>,
          new mmm_ternary<VALTYPE,symmband,hermitian,symmetric>,
          new mmm_ternary<VALTYPE,symmband,hermitian,hermitian>,
          new mmm_ternary<VALTYPE,symmband,hermitian,banddiag>,
          new mmm_ternary<VALTYPE,symmband,hermitian,symmband>,
          new mmm_ternary<VALTYPE,symmband,hermitian,hermband>,
          new mmm_ternary<VALTYPE,symmband,hermitian,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmband,banddiag,rectang>,
          new mmm_ternary<VALTYPE,symmband,banddiag,symmetric>,
          new mmm_ternary<VALTYPE,symmband,banddiag,hermitian>,
          new mmm_ternary<VALTYPE,symmband,banddiag,banddiag>,
          new mmm_ternary<VALTYPE,symmband,banddiag,symmband>,
          new mmm_ternary<VALTYPE,symmband,banddiag,hermband>,
          new mmm_ternary<VALTYPE,symmband,banddiag,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmband,symmband,rectang>,
          new mmm_ternary<VALTYPE,symmband,symmband,symmetric>,
          new mmm_ternary<VALTYPE,symmband,symmband,hermitian>,
          new mmm_ternary<VALTYPE,symmband,symmband,banddiag>,
          new mmm_ternary<VALTYPE,symmband,symmband,symmband>,
          new mmm_ternary<VALTYPE,symmband,symmband,hermband>,
          new mmm_ternary<VALTYPE,symmband,symmband,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmband,hermband,rectang>,
          new mmm_ternary<VALTYPE,symmband,hermband,symmetric>,
          new mmm_ternary<VALTYPE,symmband,hermband,hermitian>,
          new mmm_ternary<VALTYPE,symmband,hermband,banddiag>,
          new mmm_ternary<VALTYPE,symmband,hermband,symmband>,
          new mmm_ternary<VALTYPE,symmband,hermband,hermband>,
          new mmm_ternary<VALTYPE,symmband,hermband,triang>
        },
        {
          new mmm_ternary<VALTYPE,symmband,triang,rectang>,
          new mmm_ternary<VALTYPE,symmband,triang,symmetric>,
          new mmm_ternary<VALTYPE,symmband,triang,hermitian>,
          new mmm_ternary<VALTYPE,symmband,triang,banddiag>,
          new mmm_ternary<VALTYPE,symmband,triang,symmband>,
          new mmm_ternary<VALTYPE,symmband,triang,hermband>,
          new mmm_ternary<VALTYPE,symmband,triang,triang>
        }
      },
      {
        {
          new mmm_ternary<VALTYPE,hermband,rectang,rectang>,
          new mmm_ternary<VALTYPE,hermband,rectang,symmetric>,
          new mmm_ternary<VALTYPE,hermband,rectang,hermitian>,
          new mmm_ternary<VALTYPE,hermband,rectang,banddiag>,
          new mmm_ternary<VALTYPE,hermband,rectang,symmband>,
          new mmm_ternary<VALTYPE,hermband,rectang,hermband>,
          new mmm_ternary<VALTYPE,hermband,rectang,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermband,symmetric,rectang>,
          new mmm_ternary<VALTYPE,hermband,symmetric,symmetric>,
          new mmm_ternary<VALTYPE,hermband,symmetric,hermitian>,
          new mmm_ternary<VALTYPE,hermband,symmetric,banddiag>,
          new mmm_ternary<VALTYPE,hermband,symmetric,symmband>,
          new mmm_ternary<VALTYPE,hermband,symmetric,hermband>,
          new mmm_ternary<VALTYPE,hermband,symmetric,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermband,hermitian,rectang>,
          new mmm_ternary<VALTYPE,hermband,hermitian,symmetric>,
          new mmm_ternary<VALTYPE,hermband,hermitian,hermitian>,
          new mmm_ternary<VALTYPE,hermband,hermitian,banddiag>,
          new mmm_ternary<VALTYPE,hermband,hermitian,symmband>,
          new mmm_ternary<VALTYPE,hermband,hermitian,hermband>,
          new mmm_ternary<VALTYPE,hermband,hermitian,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermband,banddiag,rectang>,
          new mmm_ternary<VALTYPE,hermband,banddiag,symmetric>,
          new mmm_ternary<VALTYPE,hermband,banddiag,hermitian>,
          new mmm_ternary<VALTYPE,hermband,banddiag,banddiag>,
          new mmm_ternary<VALTYPE,hermband,banddiag,symmband>,
          new mmm_ternary<VALTYPE,hermband,banddiag,hermband>,
          new mmm_ternary<VALTYPE,hermband,banddiag,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermband,symmband,rectang>,
          new mmm_ternary<VALTYPE,hermband,symmband,symmetric>,
          new mmm_ternary<VALTYPE,hermband,symmband,hermitian>,
          new mmm_ternary<VALTYPE,hermband,symmband,banddiag>,
          new mmm_ternary<VALTYPE,hermband,symmband,symmband>,
          new mmm_ternary<VALTYPE,hermband,symmband,hermband>,
          new mmm_ternary<VALTYPE,hermband,symmband,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermband,hermband,rectang>,
          new mmm_ternary<VALTYPE,hermband,hermband,symmetric>,
          new mmm_ternary<VALTYPE,hermband,hermband,hermitian>,
          new mmm_ternary<VALTYPE,hermband,hermband,banddiag>,
          new mmm_ternary<VALTYPE,hermband,hermband,symmband>,
          new mmm_ternary<VALTYPE,hermband,hermband,hermband>,
          new mmm_ternary<VALTYPE,hermband,hermband,triang>
        },
        {
          new mmm_ternary<VALTYPE,hermband,triang,rectang>,
          new mmm_ternary<VALTYPE,hermband,triang,symmetric>,
          new mmm_ternary<VALTYPE,hermband,triang,hermitian>,
          new mmm_ternary<VALTYPE,hermband,triang,banddiag>,
          new mmm_ternary<VALTYPE,hermband,triang,symmband>,
          new mmm_ternary<VALTYPE,hermband,triang,hermband>,
          new mmm_ternary<VALTYPE,hermband,triang,triang>
        }
      },
      {
        {
          new mmm_ternary<VALTYPE,triang,rectang,rectang>,
          new mmm_ternary<VALTYPE,triang,rectang,symmetric>,
          new mmm_ternary<VALTYPE,triang,rectang,hermitian>,
          new mmm_ternary<VALTYPE,triang,rectang,banddiag>,
          new mmm_ternary<VALTYPE,triang,rectang,symmband>,
          new mmm_ternary<VALTYPE,triang,rectang,hermband>,
          new mmm_ternary<VALTYPE,triang,rectang,triang>
        },
        {
          new mmm_ternary<VALTYPE,triang,symmetric,rectang>,
          new mmm_ternary<VALTYPE,triang,symmetric,symmetric>,
          new mmm_ternary<VALTYPE,triang,symmetric,hermitian>,
          new mmm_ternary<VALTYPE,triang,symmetric,banddiag>,
          new mmm_ternary<VALTYPE,triang,symmetric,symmband>,
          new mmm_ternary<VALTYPE,triang,symmetric,hermband>,
          new mmm_ternary<VALTYPE,triang,symmetric,triang>
        },
        {
          new mmm_ternary<VALTYPE,triang,hermitian,rectang>,
          new mmm_ternary<VALTYPE,triang,hermitian,symmetric>,
          new mmm_ternary<VALTYPE,triang,hermitian,hermitian>,
          new mmm_ternary<VALTYPE,triang,hermitian,banddiag>,
          new mmm_ternary<VALTYPE,triang,hermitian,symmband>,
          new mmm_ternary<VALTYPE,triang,hermitian,hermband>,
          new mmm_ternary<VALTYPE,triang,hermitian,triang>
        },
        {
          new mmm_ternary<VALTYPE,triang,banddiag,rectang>,
          new mmm_ternary<VALTYPE,triang,banddiag,symmetric>,
          new mmm_ternary<VALTYPE,triang,banddiag,hermitian>,
          new mmm_ternary<VALTYPE,triang,banddiag,banddiag>,
          new mmm_ternary<VALTYPE,triang,banddiag,symmband>,
          new mmm_ternary<VALTYPE,triang,banddiag,hermband>,
          new mmm_ternary<VALTYPE,triang,banddiag,triang>
        },
        {
          new mmm_ternary<VALTYPE,triang,symmband,rectang>,
          new mmm_ternary<VALTYPE,triang,symmband,symmetric>,
          new mmm_ternary<VALTYPE,triang,symmband,hermitian>,
          new mmm_ternary<VALTYPE,triang,symmband,banddiag>,
          new mmm_ternary<VALTYPE,triang,symmband,symmband>,
          new mmm_ternary<VALTYPE,triang,symmband,hermband>,
          new mmm_ternary<VALTYPE,triang,symmband,triang>
        },
        {
          new mmm_ternary<VALTYPE,triang,hermband,rectang>,
          new mmm_ternary<VALTYPE,triang,hermband,symmetric>,
          new mmm_ternary<VALTYPE,triang,hermband,hermitian>,
          new mmm_ternary<VALTYPE,triang,hermband,banddiag>,
          new mmm_ternary<VALTYPE,triang,hermband,symmband>,
          new mmm_ternary<VALTYPE,triang,hermband,hermband>,
          new mmm_ternary<VALTYPE,triang,hermband,triang>
        },
        {
          new mmm_ternary<VALTYPE,triang,triang,rectang>,
          new mmm_ternary<VALTYPE,triang,triang,symmetric>,
          new mmm_ternary<VALTYPE,triang,triang,hermitian>,
          new mmm_ternary<VALTYPE,triang,triang,banddiag>,
          new mmm_ternary<VALTYPE,triang,triang,symmband>,
          new mmm_ternary<VALTYPE,triang,triang,hermband>,
          new mmm_ternary<VALTYPE,triang,triang,triang>
        }
      }
    };
  template<typename VALTYPE>
  vmv_ternary_engine<VALTYPE> *wizard<VALTYPE>::_vmv_ternary [n_vector_type][n_matrix_type][n_vector_type] = 
    {
      {
	{
	  new vmv_ternary<VALTYPE,dense,rectang,dense>
	},
	{
	  new vmv_ternary<VALTYPE,dense,symmetric,dense>
	},
	{
	  new vmv_ternary<VALTYPE,dense,hermitian,dense>
	},
	{
	  new vmv_ternary<VALTYPE,dense,banddiag,dense>
	},
	{
	  new vmv_ternary<VALTYPE,dense,symmband,dense>
	},
	{
	  new vmv_ternary<VALTYPE,dense,hermband,dense>
	},
	{
	  new vmv_ternary<VALTYPE,dense,triang,dense>
	}
      }
    };
};

#endif
