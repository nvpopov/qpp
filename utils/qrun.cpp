#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <geom/geom.hpp>
#include <iostream>
#include <fstream>
#include <io/qpparser.hpp>
#include <data/globals.hpp>
#include <io/compile.hpp>
int main(int argc, char **argv)
{
  //try{
    std::istream * inp;
    if (argc > 1)
      inp = new std::ifstream(argv[1]);
    else
      inp = & std::cin;

    std::vector<qpp::qpp_object*> decls;

    qpp::qpp_read(*inp,decls,&qpp::global::root);

    for (int i=0; i<decls.size(); i++)
      qpp::global::root.add(*qpp::qpp_compile(decls[i]));

    qpp::global::root.run();

    qpp::global::root.write(std::cout);
    /*
  }
  catch (qpp::qpp_exception & e)
    {
      std::cerr << "QPP exception:\n";
      std::cerr << e.what() << "\n";
    }
    */
}

