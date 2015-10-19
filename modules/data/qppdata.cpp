#include "data/qppdata.hpp"

namespace qpp
{
  template<>
  const qppobject_type qtype_data<int>::type = qtype_data_int;
  template<>
  const qppobject_type qtype_data<bool>::type = qtype_data_bool;
  template<>
  const qppobject_type qtype_data<double>::type = qtype_data_double;
  template<>
  const qppobject_type qtype_data<float>::type = qtype_data_float;
  template<>
  const qppobject_type qtype_data<STRING>::type = qtype_data_string;

  template<>
  const qppobject_type qtype_data<int>::input_type = qtype_data_int;
  template<>
  const qppobject_type qtype_data<bool>::input_type = qtype_data_bool;
  template<>
  const qppobject_type qtype_data<double>::input_type = qtype_data_double | qtype_data_int;
  template<>
  const qppobject_type qtype_data<float>::input_type = qtype_data_float | qtype_data_double | qtype_data_int;
  template<>
  const qppobject_type qtype_data<STRING>::input_type = qtype_data_string;

  template<>
  const STRING qtype_data<int>::name = "int";
  template<>
  const STRING qtype_data<bool>::name = "bool";
  template<>
  const STRING qtype_data<double>::name = "double";
  template<>
  const STRING qtype_data<float>::name = "float";
  template<>
  const STRING qtype_data<STRING>::name = "string";

  template<>
  const qppobject_type qtype_dim<0>::type = qtype_dim0;
  template<>
  const qppobject_type qtype_dim<1>::type = qtype_dim1;
  template<>
  const qppobject_type qtype_dim<2>::type = qtype_dim2;
  template<>
  const qppobject_type qtype_dim<3>::type = qtype_dim3;

  void qpp_object::error(STRING const & what, int line, STRING const & fname)
  {
    SSTREAM ss;
    ss << what;
    if (line > -1)
      ss << " at line " << line;
    if (fname!="")
      ss << " in file " << fname;
    _error = ss.str();
    std::cerr << _error << std::endl;
    throw qpp_exception(this);
  }

  int getdim(const qppobject_type & t)
  {
    if (t & qtype_dim0)
      return 0;
    else if (t & qtype_dim1)
      return 1;
    else if (t & qtype_dim2)
      return 2;
    else if (t & qtype_dim3)
      return 3;
    // fixme - what we return in other case?
  }

  bool typematch(const qppobject_type & tp, const qppobject_type & ptrn, int tpmode = 2)
  {
    switch(tpmode)
      {
      case 0:
	// Check that tp is a subset of ptrn bits
	if ( tp & (~ptrn) )
	  return false;
	else
	  return tp & ptrn;
      case 1:
	// check types are equal
	return tp == ptrn;
      }
  }

}
