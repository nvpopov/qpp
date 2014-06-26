#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <geom/geom.hpp>
#include <iostream>
#include <fstream>
#include <io/qpparser.hpp>
int main()
{
	std::ifstream inp("examplsde.qpp");
	_qpp_internal::tokenizer t(inp);

	qpp::qpp_object *q = parse_declaration(t);

	//q -> write(std::cout);

	qpp::qpp_declaration * d =  (qpp::qpp_declaration*)q;

	for (int i=0; i < d->n_decl(); i++)
		if ( (d->nested_decl(i).gettype() & qpp::data_geometry) ||
			 (d->nested_decl(i).gettype() & qpp::data_xgeometry))
		{
			qpp::geometry<3> *geom = (qpp::geometry<3>*)(&d->nested_decl(i));
			geom->build_type_table();
			for(int q=0; q<geom->nat(); q++)
			{
				std::cout<<geom->atom_of_type(geom->type_table(q))<<geom->coord(q)<<std::endl;
			}
		}
}

