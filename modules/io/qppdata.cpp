#include "io/qppdata.hpp"
namespace qpp{

template<>
const qppobject_type data_type<int>::type = data_type_int;
template<>
const qppobject_type data_type<bool>::type = data_type_bool;
template<>
const qppobject_type data_type<double>::type = data_type_double;
template<>
const qppobject_type data_type<float>::type = data_type_float;
template<>
const qppobject_type data_type<STRING>::type = data_type_string;

};
