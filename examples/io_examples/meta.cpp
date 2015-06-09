#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <geom/geom.hpp>
#include <iostream>
#include <fstream>
#include <io/qpparser.hpp>
#include <data/meta.hpp>
int main(int argc, char **argv)
{
  try{
    std::istream * inp;
    if (argc > 1)
      inp = new std::ifstream(argv[1]);
    else
      inp = & std::cin;
    
    qpp::tokenizer t(*inp);
    
    qpp::qpp_array global("global");
    
    qpp::qpp_object *q = _qpp_internal::parse_declaration(t, &global);
    global.add(*q);
    
    qpp::metaparam_block * meta = create_metaparam(*(qpp::qpp_declaration*)q, &global);
    std::cout << "\n---------------------------------------------\n";      

    q->write(std::cout);

    std::cout << "\n---------------------------------------------\n";      

    meta->write(std::cout);

    std::cout << "----structure----\n";
    qpp::metaparam_structure str(meta);
    for (int i=0; i<meta->n_nested(); i++)
      str.create_structure(0,i);

    str.debug();

  }
  catch (qpp::qpp_exception & e)
    {
      std::cerr << "QPP exception:\n";
      std::cerr << e.what() << "\n";
    }
}
