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

  std::string convert<std::string, const char*>::get(const char* t)
  { return std::string(t); }

  bool convert<bool,short>::get(short t)
  { return (bool)t; }

  bool & convert<bool&,short&>::get(short & t)
  { return *(bool*)(&t); }

  double    convert<double,float>::get(float t){return (double)t;}
  double      convert<double,int>::get(int t){return (double)t;}
  float     convert<float,double>::get(double t){return (float)t;}
  float        convert<float,int>::get(int t){return (float)t;}

  // ------------------------------------------------------------------------

  STRING_EX attributes<bool>::name        = "bool";
  basic_types attributes<bool>::type   = type_bool;

  STRING_EX attributes<int>::name         = "int";
  basic_types attributes<int>::type    = type_int;

  STRING_EX attributes<float>::name       = "float";
  basic_types attributes<float>::type  = type_float;

  STRING_EX attributes<double>::name      = "double";
  basic_types attributes<double>::type = type_double;

  STRING_EX attributes<STRING_EX>::name      = "string";
  basic_types attributes<STRING_EX>::type = type_string;

};
