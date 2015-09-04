#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <geom/geom.hpp>
#include <iostream>
#include <fstream>
#include <data/molecule.hpp>

using namespace qpp;

int main(int argc, char **argv)
{
  try{
    std::istream * inp;
    if (argc > 1)
      inp = new std::ifstream(argv[1]);
    else
      inp = & std::cin;

    qpp::tokenizer t(*inp);

    //qpp::qpp_declaration global("decl","global");

    /*
    std::cout << "writing global\n";

    global.write(std::cout);
  
    std::cout << "reading decl\n";
    */

    //    qpp::qpp_object *q = _qpp_internal::parse_declaration(t, &global);
    qpp::qpp_object *q = _qpp_internal::parse_declaration(t, NULL);
    //global.add(*q);

    // qpp::molecule<0> mol((qpp::qpp_declaration*)q);

    qpp::qpp_object * m = qpp::qpp_compile(q);

    m->write(std::cout);

    qpp::molecule<0> * mol = (qpp::molecule<0>*)m;

    std::cout << "---------------------mol.vectors:------------------------\n";
    mol->cell->write(std::cout);

    std::cout << "---------------------mol.geom:------------------------\n";
    mol->geom->write(std::cout);

    std::cout << "---------------------mol.atoms:------------------------\n";
    for (int i=0; i< mol->atoms.size(); i++)
      mol->atoms[i]->write(std::cout);
   
  } 
  catch (qpp::qpp_exception & e)
    {
      std::cerr << "QPP exception:\n";
      std::cerr << e.what() << "\n";
    }
}

