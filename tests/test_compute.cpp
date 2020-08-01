#include "catch.hpp"
#include <geom/lace3d.hpp>
#include <compute/rdf.hpp>
#include <io/vasp_io.hpp>
#include <fstream>

using namespace qpp;

TEST_CASE("Radial density function - main") {

   SECTION ("Resize test") {

     geometry<float, periodic_cell<float> > g1(3);
     std::ifstream istr("../examples/io/ref_data/vasp/La44F148.POSCAR");
     read_vasp_poscar(istr, g1);

     /* check data */
     REQUIRE(g1.nat() == 192);

//     /* compute and check rdf */
//     std::vector<std::vector<float> > data;
//     compute_rdf_naive(g1, data, 0.1f, 4.0f, 20);
//     REQUIRE(data.size() == g1.nat());
//     REQUIRE(data[0].size() == 20);

   }

}
