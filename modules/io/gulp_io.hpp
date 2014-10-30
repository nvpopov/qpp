#include <geom/geom.hpp>

namespace qpp{
  
  template< int DIM, class VALTYPE=double, class TRANSFORM >
  void write_ginp_coord(std::basic_ostream<CHAR,TRAITS>  & inp, 
			const qpp::gen_geometry<DIM,VALTYPE,TRANSFORM> & geom)
  {
    inp << "";
  }

};
