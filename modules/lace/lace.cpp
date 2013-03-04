#include <iostream>
#include <cassert>
#include <cstring>
#include <lace/lace.hpp>
#include <string>
#include <sstream>
#include <boost/format.hpp>
#include <lace/matrix_expressions.hpp>

namespace _lace_expressions{

  void indent(int shift)
  {
    while(shift-- > 0) std::cout << " ";
  };
  
  int abstract_expression::xpr_counter = 0;
  int abstract_expression::xpr_total_number = 0;

  std::string stype(int t)
  {
    std::string tp;
    switch(t){
    case _scalar:   tp = "scalar"; break;
    case _matrix:   tp = "matrix"; break;
    case _vector:   tp = "vector"; break;
    case _rvector:  tp = "rawvector"; break;
    };
    return tp;
  }

  //  template<typename VALTYPE>
  //  bool is_literal(abstract_expression<VALTYPE> *x)
  bool is_literal(abstract_expression *x)
  {
    return (x->gettype() & _literal) != 0;
  }

  //  template<typename VALTYPE>
  //  bool is_sliteral(abstract_expression<VALTYPE> *x)
  bool is_sliteral(abstract_expression *x)
  {
    return (x->gettype() & _sliteral) != 0;
  }

  //  template<typename VALTYPE>
  //  bool is_summa(abstract_expression<VALTYPE> *x)
  bool is_summa(abstract_expression *x)
  {
    return (x->gettype() & _summa) != 0;
  }

  //  template<typename VALTYPE>
  //  int expr_type(abstract_expression<VALTYPE> *x)
  int expr_type(abstract_expression *x)
  {
    return (x->gettype()) & ( _scalar | _vector | _matrix | _rvector );
  }

  sub sub::full = sub(-1,-1,1);

};

namespace lace{
  
  bool globals::preserv_matrix = true;

  bool globals::debug = false;

  bool globals::auto_reshape = false;
  
};
