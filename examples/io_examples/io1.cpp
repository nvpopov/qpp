#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <geom/geom.hpp>
#include <iostream>
#include <fstream>
#include <io/qpparser.hpp>
int main(int argc, char **argv)
{
  std::istream * inp;
  if (argc > 1)
    inp = new std::ifstream(argv[1]);
  else
    inp = & std::cin;

  _qpp_internal::tokenizer t(*inp);
  
  qpp::qpp_object *q = parse_declaration(t);
  
  q -> write(std::cout);
  
  qpp::qpp_declaration * d =  (qpp::qpp_declaration*)q;
  
  
  std::cout << " -------------------------- Types ---------------------------\n";

  for (int i=0; i < d->n_decl(); i++)
    {
      std::cout << "nested " << i << " type= " << d->nested_decl(i).gettype() << "\n";
      d->nested_decl(i).write(std::cout);
    }
  
  std::cout << " -------------------------- Geometries ---------------------------\n";
  
  for (int i=0; i < d->n_decl(); i++)
    if ( (d->nested_decl(i).gettype() & qpp::qtype_geometry) || 
	 (d->nested_decl(i).gettype() & qpp::qtype_xgeometry))
      d->nested_decl(i).write(std::cout);
  std::cout << " -------------------------- Basis sets ---------------------------\n";
  for (int i=0; i < d->n_decl(); i++)
    if ( (d->nested_decl(i).gettype() & qpp::qtype_basis) )
      d->nested_decl(i).write(std::cout);
  
}

