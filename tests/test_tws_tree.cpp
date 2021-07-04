#include "catch.hpp"
#include <geom/lace3d.hpp>
#include <geom/xgeom.hpp>

#define NO_TWS_TREE_DEBUG
#include <geom/tws_tree.hpp>

using namespace qpp;

TEST_CASE("TWS tree") {
  SECTION ("Basic test - erase") {
    xgeometry<double, periodic_cell<double>> g(3);
    g.set_cell_vector({7, 0, 0}, 0);
    g.set_cell_vector({0, 7, 0}, 1);
    g.set_cell_vector({0, 0, 7}, 2);
    g.add("C", {0, 0, 0});
    g.add("C", {2.5, 2.5, 2.5});
    g.add("Ca",{1, 0, 0});

    REQUIRE(g.nat() == 3);

    tws_tree_t<double, periodic_cell<double>, std::uint32_t> tr1(g);
    tr1.m_rebuild_all_on_erase = false;
    tr1.m_rebuild_all_on_insert = false;
    tr1.do_action(act_clear_all | act_build_all);
    REQUIRE(tr1.n(0) == 1);
    REQUIRE(tr1.n(1) == 0);
    REQUIRE(tr1.n(2) == 1);

    REQUIRE(tr1.m_ngb_table.size() == 3);
    tr1.m_auto_bonding = true;
    tr1.m_auto_build = true;
    g.erase(1);
    REQUIRE(tr1.m_ngb_table.size() == 2);
    REQUIRE(tr1.n(0) == 1);
    REQUIRE(tr1.n(1) == 1);

    g.add("C", {2.5, 2.5, 2.5});
    REQUIRE(g.nat() == 3);
    REQUIRE(tr1.n(0) == 1);
    REQUIRE(tr1.n(1) == 1);
    REQUIRE(tr1.n(2) == 0);

    g.erase(2);
    g.erase(1);
    g.erase(0);

    g.add("C", {0, 0, 0});
    g.add("O", {2.5, 2.5, 2.5});
    g.add("Ca",{1, 0, 0});
    REQUIRE(g.n_atom_types() == 3);
    REQUIRE(g.type_of_atom(0) == 0);
    REQUIRE(g.type_of_atom(1) == 2);
    REQUIRE(g.type_of_atom(2) == 1);

    g.insert(1, "Zn", {2.8, 2.8, 2.8});
    REQUIRE(tr1.m_ngb_table.size() == 4);
    REQUIRE(g.nat() == 4);
    REQUIRE(g.n_atom_types() == 4);
    REQUIRE(g.type_of_atom(0) == 0); //C
    REQUIRE(g.type_of_atom(1) == 3); //Zn
    REQUIRE(g.type_of_atom(2) == 2); //0
    REQUIRE(g.type_of_atom(3) == 1); //Ca
    REQUIRE(g.atom_name(0) == "C");
    REQUIRE(g.atom_name(1) == "Zn");
    REQUIRE(g.atom_name(2) == "O");
    REQUIRE(g.atom_name(3) == "Ca");

    REQUIRE(tr1.n(0) == 1);
    REQUIRE(tr1.n(1) == 1);
    REQUIRE(tr1.n(2) == 1);
    REQUIRE(tr1.n(3) == 1);
    REQUIRE(tr1.m_bonding_table.m_dist[{g.type_of_atom(3), g.type_of_atom(0)}].m_bonding_dist
            == Approx(2.659999));
    REQUIRE(tr1.m_bonding_table.m_dist[{g.type_of_atom(0), g.type_of_atom(3)}].m_bonding_dist
            == Approx(2.659999));
    REQUIRE(tr1.m_bonding_table.m_dist[{g.type_of_atom(0), g.type_of_atom(1)}].m_bonding_dist
            == Approx(2.21));

    //Print out bonding dists
//    for (int i = 0; i < g.n_atom_types(); i++)
//      for (int j = 0; j < g.n_atom_types(); j++)
//        std::cout << fmt::format("(i={}, j={}, dist={})",
//                                 i, j, tr1.m_bonding_table.m_dist[{i,j}].m_bonding_dist)
//                  << std::endl;

  }
}

