#include <iostream>
#include <fstream>
#include <geom/zpt.hpp>
#include <io/qppdata.hpp>
#include <io/qpparser.hpp>

#define DIM 0

int main(int argc, char **argv)
{
  try{
    std::istream * inp;
    if (argc > 1)
      inp = new std::ifstream(argv[1]);
    else
      inp = & std::cin;
  
    _qpp_internal::tokenizer t(*inp);
  
    std::vector<qpp::qpp_object*> decls;

    qpp::qpp_object * decl;
    while ( (decl=parse_declaration(t)) != NULL)
      decls.push_back(decl);

    std::vector<qpp::zpattern<DIM>* > z;

    /*
      for (int i=0; i<decls.size(); i++)
      if (decls[i]->category() == "zpattern")
      {
      qpp::qpp_declaration * zdecl = (qpp::qpp_declaration*)decls[i];
      for (int j = -1; j < zdecl->n_decl(); j++)
      std::cout << "zpt " << i << " decl " << j << " env(rcc_min)= " << zdecl->env("rcc_min",j) << "\n";
      }
    */

    for (int i=0; i<decls.size(); i++)
      if (decls[i]->category() == "zpattern")
	z.push_back( qpp::decl2zpt<DIM>((qpp::qpp_declaration*)decls[i]) );

    for (int i=0; i<z.size(); i++)
      z[i] -> write(std::cout);
  }
  catch (qpp::qpp_exception & e)
    {
      std::cout << e.what() << "\n";
      exit(1);
    }
}

    
