#include <iostream>
#include <io/qppdata.hpp>
#include <io/qpparser.hpp>

int main()
{
  /*
  qpp::qpp_parameter_tree * x = new qpp::qpp_parameter_tree("guess","huckel");
  x->parameters.add(*new qpp::qpp_parameter_tree("norb","98"));

  qpp::qpp_parameter_tree * y = new qpp::qpp_parameter_tree("","swap");
  y->parameters.add(*new qpp::qpp_parameter_tree("","11"));
  y->parameters.add(*new qpp::qpp_parameter_tree("","13"));
  x->parameters.add(*y);

  x->debug(0);
  */

  _qpp_internal::tokenizer<char> t(std::cin);

  qpp::qpp_data_tree<char> * pl = _qpp_internal::parse_declaration(t);

  pl -> write(std::cout);

}
