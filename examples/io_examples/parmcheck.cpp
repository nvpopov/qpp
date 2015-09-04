#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <geom/geom.hpp>
#include <iostream>
#include <fstream>
#include <io/qpparser.hpp>
#include <data/meta.hpp>
#include <data/globals.hpp>

int main(int argc, char **argv)
{
  try{

    std::ifstream inp(argv[1]);
    
    qpp::tokenizer t(inp), t1(std::cin);
    
    //qpp::qpp_array global("global");
    
    qpp::qpp_object *q = _qpp_internal::parse_declaration(t, &qpp::global::root);
    qpp::global::root.add(*q);
    qpp::metaparam_block * meta = create_metaparam(*(qpp::qpp_declaration*)q, &qpp::global::root);

    meta -> write(std::cout);

    while(true)
      {
	qpp::qpp_param_array p;
	_qpp_internal::parse_parameters(p,t1);
	qpp::metaparam_structure str(meta);

	//int i1=0, i2=-1;

	int res = meta->identify(p, str);
	//std::cout << "res = " << res << " i1= " << i1 << " i2= " << i2 << "\n";
	std::cout << "res = " << res <<  "\n";
	str.debug();
	std::cout << "---- normalized parmlist ----\n";
	str.get_params()->write(std::cout);
	std::cout << "\n";
	std::cout << "N metas= " << qpp::global::metas.size() << "\n";
      }


  }
  catch (qpp::qpp_exception & e)
    {
      std::cerr << "QPP exception:\n";
      std::cerr << e.what() << "\n";
    }
}
