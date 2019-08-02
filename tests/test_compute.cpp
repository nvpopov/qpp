#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <geom/lace3d.hpp>
#include <compute/rdf.hpp>
#include <fstream>

using namespace qpp;

TEST_CASE("Radial density function - main") {

   SECTION ("Basic test1") {

     REQUIRE(2 + 2 == 4) ;

   }

}
