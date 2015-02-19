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

void qpp_object::error(STRING const & what, int line, STRING const & fname)
{
	SSTREAM ss;
	ss << what;
	if (line > -1)
		ss << " at line " << line;
	if (fname!="")
		ss << " in file " << fname;
	_error = ss.str();
	throw qpp_exception(this);
}
}
