#include "catch.hpp"
#include <geom/lace3d.hpp>
#include <geom/xgeom.hpp>
#include <geom/tws_tree.hpp>

using namespace qpp;

TEST_CASE("TWS tree") {

  SECTION ("Basic test") {

    xgeometry<double, periodic_cell<double>> g(3);
    g.set_cell_vector({5, 0, 0}, 0);
    g.set_cell_vector({0, 5, 0}, 0);
    g.set_cell_vector({0, 0, 5}, 0);
    g.add("C", {0, 0, 0});

    REQUIRE(g.nat() == 1);

    tws_tree_t<double, periodic_cell<double>, std::uint32_t> tr1(g);

  }

}

