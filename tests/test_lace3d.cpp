#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <geom/lace3d.hpp>

using namespace qpp;

TEST_CASE( "Basic vector3<T> tests", "[vector3<T>]" ) {
  vector3<float> vf;
  vector3<float> zero_vf = vector3<float>::Zero();

  REQUIRE( abs(zero_vf[0]) + abs(zero_vf[0]) + abs(zero_vf[0]) <= vector3<float>::tol_equiv);
  REQUIRE( (vector3<float>(1.0f, 1.0f, -1.0f) + vector3<float>(2.0f, 2.0f, 1.0f)) == vector3<float>(3.0f, 3.0f, 0.0f));
  REQUIRE( vector3<float>(1,2,3).dot(vector3<float>(1,5,7)) - 32 <= vector3<float>::tol_equiv);
}

