#include "types.hpp"

namespace qpp{

  bool numeric_type<float>::is_real(){return true;}
  
  bool numeric_type<float>::is_complex(){return false;}
  
  float numeric_type<float>::I(){return float(0);}
  
  bool numeric_type<double>::is_real(){return true;}
  
  bool  numeric_type<double>::is_complex(){return false;}
  
  double  numeric_type<double>::I(){return double(0);}
  
  bool  numeric_type<long double>::is_real(){return true;}
  
  bool numeric_type<long double>::is_complex(){return false;}
  
  long double numeric_type<long double>::I(){return (long double)(0);}
  
  bool numeric_type<std::complex<float> >::is_real(){return false;}
  
  bool numeric_type<std::complex<float> >::is_complex(){return true;}
  
  std::complex<float> numeric_type<std::complex<float> >::I(){return std::complex<float>(0,1);}
  
  bool numeric_type<std::complex<double> >::is_real(){return false;}
  
  bool numeric_type<std::complex<double> >::is_complex(){return true;}
  
  std::complex<double> numeric_type<std::complex<double> >::I(){return std::complex<double>(0,1);}
  
  bool  numeric_type<std::complex<long double> >::is_real(){return false;}
  
  bool numeric_type<std::complex<long double> >::is_complex(){return true;}
  
  std::complex<long double> numeric_type<std::complex<long double> >::I(){return std::complex<long double>(0,1);}
  
  bool numeric_type<int>::is_real(){return true;}
  
  bool numeric_type<int>::is_complex(){return false;}
  
  int numeric_type<int>::I(){return 0;}
  // ------------------------------------------------------------------------
  
  STRING attributes<bool>::name   = "bool";

  STRING attributes<int>::name    = "int";

  STRING attributes<float>::name  = "float";

  STRING attributes<double>::name = "double";

};
