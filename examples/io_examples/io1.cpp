#include <io/qpparser.hpp>
#include <iostream>
#include <fstream>

int main()
{
  std::ifstream inp("example.qpp");
  _qpp_internal::tokenizer t(inp);
  
  qpp::qpp_object *q = parse_declaration(t);

  q -> write(std::cout);

  qpp::qpp_declaration * d =  (qpp::qpp_declaration*)q;

  for (int i=0; i < d->n_decl(); i++)
    if ( (d->nested_decl(i).gettype() & qpp::data_geometry) || 
	 (d->nested_decl(i).gettype() & qpp::data_xgeometry))
      d->nested_decl(i).write(std::cout);
}

