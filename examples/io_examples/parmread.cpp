#include <io/qpparser.hpp>
#include <iostream>

using namespace qpp;

int main(int argc, char **argv)
{
  try{
    qpp::tokenizer t(std::cin);

    qpp::qpp_param_array p;
    _qpp_internal::parse_parameters(p,t);

    std::cout << "--------------\n";
    p.write(std::cout);
    std::cout << "\n";
  }
  
catch (qpp::qpp_exception & e)
    {
      std::cerr << "QPP exception:\n";
      std::cerr << e.what() << "\n";
    }
}

