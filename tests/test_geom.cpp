#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <geom/xgeom.hpp>

using namespace qpp;

TEST_CASE( "Reciporal lattice tests" ) {

  periodic_cell<float> cell_0d;
  REQUIRE(cell_0d.DIM == 0);

  periodic_cell<float> cell_1d(1);
  REQUIRE(cell_1d.DIM == 1);

  periodic_cell<float> cell_2d(2);
  REQUIRE(cell_2d.DIM == 2);

  for (size_t i = 0; i < 3; i++) {
      REQUIRE(cell_0d.get_reciporal_vectors(i) == std::nullopt);
      REQUIRE(cell_1d.get_reciporal_vectors(i) == std::nullopt);
      REQUIRE(cell_2d.get_reciporal_vectors(i) == std::nullopt);
    }

  periodic_cell<float> cell_3d(3);
  REQUIRE(cell_3d.DIM == 3);

  cell_3d.v[0] = vector3<float>{10.0f,  0.0f,  0.0f};
  cell_3d.v[1] = vector3<float>{ 0.0f, 10.0f,  0.0f};
  cell_3d.v[2] = vector3<float>{ 0.0f,  0.0f, 15.0f};

  auto rec_a = cell_3d.get_reciporal_vectors(0);
  auto rec_b = cell_3d.get_reciporal_vectors(1);
  auto rec_c = cell_3d.get_reciporal_vectors(2);

  REQUIRE(((rec_a != std::nullopt) && (rec_b != std::nullopt) && (rec_c != std::nullopt)));
  REQUIRE((*rec_a == vector3<float>{0.1f, 0.0f, 0.0f}));
  REQUIRE((*rec_b == vector3<float>{0.0f, 0.1f, 0.0f}));
  REQUIRE((*rec_c == vector3<float>{0.0f, 0.0f, 0.0666667f}));

}
