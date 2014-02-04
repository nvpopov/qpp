#include<iostream>
#include<boost/format.hpp>
#include<cmath>
#include<lace/lace.hpp>

using namespace lace;
using _lace_expressions::matrix_expression;

int main()
{
  lace::globals::debug = true;

  matrix_expression<double>::literal a("a"), b("b"), c("c"), d("d");

  matrix_expression<double> * x = &( d = a+b*c );

  x -> print_tree(1);

  _lace_expressions::abstract_expression* xa = x;

  _lace_expressions::canonical_expr<double>(xa);

  std::cout << "After canonical:\n";

   x -> print_tree(1);

}
