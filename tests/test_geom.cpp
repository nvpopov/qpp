#include <catch.hpp>
#include <geom/xgeom.hpp>
#include <geom/builders.hpp>
#include <symm/gen_cell.hpp>
#include <io/geomio.hpp>

using namespace qpp;

TEST_CASE("Reciporal lattice tests") {

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

TEST_CASE("xgeometry tests") {

  SECTION("Rich geometry(from xgeom1.cpp)") {
    periodic_cell<float> cl(0);

    xgeometry<float, periodic_cell<float> >
        G(cl,
          {"atom", "number", "charge", "x", "y", "z", "optx", "opty", "optz", "fullname"},
          {basic_types::type_string, basic_types::type_int, basic_types::type_real,
           basic_types::type_real, basic_types::type_real, basic_types::type_real,
           basic_types::type_bool, basic_types::type_bool, basic_types::type_bool,
           basic_types::type_string },
          "Rich_geometry");

    G.xadd("H",  1, 0.3,  1.1, 2.2, 3.3, true, false, false,  "Hydrogen");
    G.xadd("C",  7, 0.0,    4,   5,   6, false, true, true,   "Carbon");
    G.xadd("Nt", 0, 0.001, 56,  67,  78, false, false, false, "Newtonium");

    REQUIRE(G.nat() == 3);

    G.xinsert(0, "U", 92, 4.4, 9,8,7, true, true, true, "Uranuim");
    REQUIRE(G.nat() == 4);

    G.erase(3);
    REQUIRE(G.nat() == 3);

    REQUIRE(G.coord(1)(0) == 1.1f);
    REQUIRE(G.coord(1)(1) == 2.2f);
    REQUIRE(G.coord(1)(2) == 3.3f);

    G.coord(1)(0) = 7;
    G.coord(1)(1) = 8;
    G.coord(1)(2) = 9;

    REQUIRE(G.coord(1)(0) == 7.0f);
    REQUIRE(G.coord(1)(1) == 8.0f);
    REQUIRE(G.coord(1)(2) == 9.0f);

    REQUIRE(G.xfield<int>(1, 2) == 7);
    G.xfield<int>(1,2) = 77;
    REQUIRE(G.xfield<int>(1, 2) == 77);

    REQUIRE(G.xfield<bool>(6,0) == true);
    G.xfield<bool>(6,0) = false;
    REQUIRE(G.xfield<bool>(6,0) == false);

    G.add("H20", {-2.,-2.,-2.});
    G.xfill(3, "H2O", -1, 0.0, -2, 2, -2, true, true, true, "Rigid_H2O_molecule");
    REQUIRE(G.nat() == 4);
    REQUIRE(G.xfield<STRING_EX>(0, 3) == "H2O");
    REQUIRE(G.xfield<STRING_EX>(9, 3) == "Rigid_H2O_molecule");
    REQUIRE(G.xfield<STRING_EX>("fullname",3) == "Rigid_H2O_molecule");

  }

  SECTION("datum tests(from xgeom.cpp)") {

    periodic_cell<double> cl(0);
    xgeometry<double, periodic_cell<double> >
    g2(cl,
       {"atom",      "number", "z",       "charge",
            "x",       "y",       "mass",    "magmom",  "word"},
           {basic_types::type_string, basic_types::type_int, basic_types::type_real,
            basic_types::type_real, basic_types::type_real, basic_types::type_real,
            basic_types::type_real, basic_types::type_real, basic_types::type_string},
           "rich_geometry");

    g2.xadd("H",   1,   0.3, 0.6,   3,  6, 1.01, 3.731e-3, "hydrogen");
    g2.xadd("U",  92,   3.4, 4.4,   7,  9, 238,  1.23e-2,  "uranium");
    g2.xadd("Nt",  0, -42.0, 1e-8, 16, 25, 1e-5, 0e0,      "newtonium");

    REQUIRE(g2.mass(1) == 238);
    REQUIRE(g2.charge(0) == 0.6);

    g2.mass(1) = 235.0;
    g2.charge(0) = 0.55555;
    REQUIRE(g2.mass(1) == 235);
    REQUIRE(g2.charge(0) == 0.55555);
    REQUIRE(g2.nat() == 3);

    std::vector<qpp::datum> s = {qpp::datum("Hru"), qpp::datum(555),
                                 qpp::datum(-1.11), qpp::datum(2.22),
                                 qpp::datum(3.33), qpp::datum(-1.11),
                                 qpp::datum(2.22), qpp::datum(3.33),
                                 qpp::datum("piggy-piggy")};

    g2.add("", qpp::vector3<double>::Zero());
    g2.set_fields(-1, s);
    REQUIRE(g2.nat() == 4);
    REQUIRE(g2.xfield<STRING_EX>("atom", 3) == "Hru");
    REQUIRE(g2.xfield<STRING_EX>("word", 3) == "piggy-piggy");

  }

  //TODO: broken
  SECTION("autosymmetrize+replicate tests") {

    auto C4 = RotMtrx<double>({0,0,1}, pi/2);
    auto D2 = RotMtrx<double>({1,0,0},  pi);
    gen_cell<double, decltype(C4)> G({C4,D2});

    geometry<double,decltype(G)> geom(G);

    geom.auto_symmetrize = true;
    geom.auto_update_types = true;

    geom.default_symmetrize_radius = 1;

    geom.add("C", 0, 0.1, 1.);
    geom.add("H", 1,   2, 3);
    REQUIRE(geom.nat() == 2);

    geometry<double> geom2(0);
    geom2.auto_symmetrize = true;
    geom2.auto_update_types = true;
    replicate(geom2, geom, G, G.begin(), G.end());

    REQUIRE(geom2.nat() == 2);

  }

  SECTION("geom_oh") {

    auto C4 = RotMtrx<double>({0,0,1}, pi/2);
    auto C3 = RotMtrx<double>({1,1,1}, 2*pi/3);
    auto C31 = RotMtrx<double>({1,-1,-1}, 2*pi/3);
//    auto S6 = RotMtrx<double>({1,1,1},pi/3)*Sigma<double>({1,1,1});
    matrix3<double> Inv = matrix3<double>::Identity()*-1.0f;

    gen_cell<double, decltype(C4)> G({C4,C3,C31,Inv});
    geometry<double, decltype(G)> geom_src1(G);
    G.auto_orders();
    geom_src1.auto_symmetrize = true;
    geom_src1.auto_update_types = true;
    geom_src1.default_symmetrize_radius = 1.5;
    geom_src1.add("C", 0, 0, 1.);
    geom_src1.add("H", 1, 2, 3);

    geometry<double> geom_dst1(0);
    replicate(geom_dst1, geom_src1, G, G.begin(), G.end(), crowd_exclude);
    REQUIRE(geom_dst1.nat() == 54);

// TODO: default_symmetrize_radius???
//    geometry<double, decltype(G)> geom_src2(G);
//    G.auto_orders();
//    geom_src2.auto_symmetrize = true;
//    geom_src2.auto_update_types = true;
//    geom_src2.default_symmetrize_radius = 1;
//    geom_src2.add("C", 0, 0, 1.);
//    geom_src2.add("H", 1, 2, 3);
//    geometry<double> geom_dst2(0);
//    replicate(geom_dst2, geom_src2, G, G.begin(), G.end(), crowd_exclude );
//    REQUIRE(geom_dst2.nat() == 72);

//    std::cout << geom2.nat() << "\n\n";
//    for (int at=0; at<geom2.nat(); at++)
//      std::cout<<fmt::format("{} {:3.5f} {:3.4f}",
//                               geom2.atom(at),
//                               geom2.coord(at).x(),
//                               geom2.coord(at).y())<<std::endl;
//    std::ofstream ofstr("goh.xyz");
//    write_xyz(ofstr, geom2);

  }

  SECTION("ngb table") {

    geometry<double> g(3);
    std::ifstream inp("../examples/io/ref_data/xyz/si.xyz");
    read_xyz(inp,g);
    g.build_type_table();

    bonding_table<double> bt;
    bt.default_distance = 2.6;
    neighbours_table<double> ngbr(g,bt);
    ngbr.transl_mode=true;

    ngbr.build();

    std::vector<int> ngbr_n(g.size());
    for (auto i = 0; i < g.nat(); i++)
      ngbr_n[i] = ngbr.n(i);

    auto min_ngbs = std::min_element(begin(ngbr_n), end(ngbr_n));
    auto max_ngbs = std::max_element(begin(ngbr_n), end(ngbr_n));
    auto avg_ngbs = double(std::accumulate(begin(ngbr_n), end(ngbr_n), 0)) / double(g.size());

    REQUIRE(*min_ngbs == 3);
    REQUIRE(*max_ngbs == 5);
    REQUIRE(avg_ngbs == 4);

//    for (int i=0; i<g.size(); i++)
//      for (int j=0; j<ngbr.n(i); j++){
//        qpp::index k = ngbr.table(i,j);
//        std::cout << g.atom(i) << " " << i << " " <<
//            g.atom(k) << " " << k << " " <<
//            (g.pos(i) - g.pos(k)).norm() << "\n";
//      }

  }

  SECTION("ngb table(from geom3.cpp") {

    qpp::geometry<double, periodic_cell<double>> g;

    g.cell(0) = vector3<double>(4,0,0);
    g.cell(1) = vector3<double>(0,6,0);
    g.cell(2) = vector3<double>(0,0,4);

    g.add("Carbon",         -1.676283510,      0.000000000,      1.911126199);
    g.add("Oxygen",         -1.753146399,      1.141923181,      1.514919538);
    g.add("Oxygen",         -1.604477009,     -1.066694960,      1.079653080);
    g.add("Hydrogen",       -1.628395866,     -0.711301327,      0.174843873);
    g.add("Coronium",        0,                5,                0          );
    g.add("Carbon",         -1.647886655,     -0.422100383,      3.375898205);
    g.add("Hydrogen",       -2.475776531,     -1.122649475,      3.538396631);
    g.add("Coronium",        0,                0,                0          );
    g.add("Newtonium",       0,                0,                0          );
    g.add("Hydrogen",       -2.565816675,      1.205870339,      4.156284306);
    g.add("Hydrogen",       -0.956315270,      1.314146931,      4.156322052);
    g.add("Hydrogen",       -0.733613146,     -1.005425023,      3.538407817);
    g.insert(6, "Nitrogen", -1.721124037,      0.666230718,      4.332560746);

    g.build_type_table();
    REQUIRE(g.n_types() == 6);

    bonding_table<double> bt;
    neighbours_table<double> ngbr(g,bt);
    ngbr.transl_mode=true;

    bt.default_distance = 1.2;
    bt.set_pair("Carbon",   "Carbon",    1.8);
    bt.set_pair("Carbon",   "Oxygen",    1.6);
    bt.set_pair("Coronium", "Newtonium", 8);
    bt.set_pair("Oxygen",   "Nitrogen",  1.53);
    bt.set_pair("Carbon",   "Nitrogen",  1.35);
    ngbr.build();

    std::map<int, std::vector<int>> ngbr_n;
    for (auto i = 0; i < g.nat(); i++)
      ngbr_n[g.type_table(i)].push_back(ngbr.n(i));

    std::map<int, int> min_ngbs;
    std::map<int, int> max_ngbs;
    std::map<int, double> avg_ngbs;
    for (auto &&[key, value] : ngbr_n) {
      min_ngbs[key]  = *std::min_element(begin(value), end(value));
      max_ngbs[key]  = *std::max_element(begin(value), end(value));
      avg_ngbs[key] = double(std::accumulate(begin(value), end(value), 0)) / double(value.size());
    }

    REQUIRE(min_ngbs[0] == 0);
    REQUIRE(max_ngbs[0] == 0);
    REQUIRE(avg_ngbs[0] == 0);
    REQUIRE(min_ngbs[1] == 0);
    REQUIRE(max_ngbs[1] == 0);
    REQUIRE(avg_ngbs[1] == 0);
    REQUIRE(min_ngbs[2] == 0);
    REQUIRE(max_ngbs[2] == 0);
    REQUIRE(avg_ngbs[2] == 0);
    REQUIRE(min_ngbs[3] == 0);
    REQUIRE(max_ngbs[3] == 1);
    REQUIRE(avg_ngbs[3] == 0.5);
    REQUIRE(min_ngbs[4] == 0);
    REQUIRE(max_ngbs[4] == 0);
    REQUIRE(avg_ngbs[4] == 0);
    REQUIRE(min_ngbs[5] == 1);
    REQUIRE(max_ngbs[5] == 1);
    REQUIRE(avg_ngbs[5] == 1);

    //    for (int i=0; i<g.size(); i++)
    //      for (int j=0; j<ngbr.n(i); j++){
    //        qpp::index k = ngbr.table(i,j);
    //        std::cout << g.atom(i) << " " << i << " " <<
    //            g.atom(k) << " " << k << " " <<
    //            (g.pos(i) - g.pos(k)).norm() << "\n";
    //      }

  }

  SECTION("periodic tests") {

    periodic_cell<double> cell({4,0,0}, {0,6,0}, {0,0,4});
    geometry<double, decltype(cell)> g(cell);

    g.add("Carbon",         -1.676283510,      0.000000000,      1.911126199);
    g.add("Oxygen",         -1.753146399,      1.141923181,      1.514919538);
    g.add("Oxygen",         -1.604477009,     -1.066694960,      1.079653080);
    g.add("Hydrogen",       -1.628395866,     -0.711301327,      0.174843873);
    g.add("Coronium",        0,                5,                0          );
    g.add("Carbon",         -1.647886655,     -0.422100383,      3.375898205);
    g.add("Hydrogen",       -2.475776531,     -1.122649475,      3.538396631);
    g.add("Coronium",        0,                0,                0          );
    g.add("Newtonium",       0,                0,                0          );
    g.add("Hydrogen",       -2.565816675,      1.205870339,      4.156284306);
    g.add("Hydrogen",       -0.956315270,      1.314146931,      4.156322052);
    g.add("Hydrogen",       -0.733613146,     -1.005425023,      3.538407817);
    g.insert(6, "Nitrogen", -1.721124037,      0.666230718,      4.332560746);

    g.shadow(0,true);
    g.shadow(1,true);

    g.build_type_table();

    REQUIRE(g.nat() == 13);
    REQUIRE(g.n_types() == 6);

    int atoms_including_ngbs{0};
    for (qpp::iterator I(qpp::index::D(3).all(-1),qpp::index::D(3).all(1));!I.end(); I++)
      for (int at=0; at<g.nat(); at++) atoms_including_ngbs++;

    REQUIRE(atoms_including_ngbs == 351); // 13 * 27

    //access by index
    REQUIRE(g.r(12, qpp::index::D(3).all(-1))
            == vector3<double>{-4.733613146, -7.005425023, -0.461592183});
    REQUIRE(g.r(11, qpp::index::D(3).all(0))
            == vector3<double>{-0.95631527, 1.314146931, 4.156322052});
    REQUIRE(g.r(10, qpp::index::D(3).all(1))
            == vector3<double>{1.434183325, 7.205870339, 8.156284306});

  }

  SECTION("yet another ngb test(from ngbr.cpp") {

    qpp::geometry<double> amino(0);

    amino.add("N",          1.75524,       -0.03055,       -0.15305);
    amino.add("C",          0.46128,        0.62257,        0.10589);
    amino.add("C",         -0.74491,       -0.32028,       -0.01207);
    amino.add("O",         -1.89675,        0.44072,        0.26071);
    amino.add("H",          1.76784,       -0.40647,       -1.07847);
    amino.add("H",          1.89801,       -0.77424,        0.49847);
    amino.add("H",          0.36238,        1.46995,       -0.60184);
    amino.add("H",          0.50565,        1.07184,        1.11828);
    amino.add("H",         -0.66487,       -1.16329,        0.70383);
    amino.add("H",         -0.80945,       -0.76139,       -1.02735);
    amino.add("H",         -2.63443,       -0.14886,        0.18560);

    qpp::bonding_table<double> dt;
    dt.default_distance = 1.5;
    dt.set_pair("C","C",1.7);

    qpp::neighbours_table<double> b(amino,dt);

    //b.reference_mode = true;
    b.build();

//    for (int i=0; i<amino.nat(); i++)
//    {
//      std::cout << "atom " << i;
//      for (int j=0; j<b.n(i); j++)
//        std::cout << " " << b(i,j);
//      std::cout << std::endl;
//    }

    REQUIRE(b(0, 0) == 1);
    REQUIRE(b(0, 1) == 4);
    REQUIRE(b(0, 2) == 5);

    REQUIRE(b(1, 0) == 0);
    REQUIRE(b(1, 1) == 2);
    REQUIRE(b(1, 2) == 6);
    REQUIRE(b(1, 3) == 7);

    REQUIRE(b(2, 0) == 3);
    REQUIRE(b(2, 1) == 9);
    REQUIRE(b(2, 2) == 1);
    REQUIRE(b(2, 3) == 8);

    REQUIRE(b(3, 0) == 10);
    REQUIRE(b(3, 1) == 2);

    REQUIRE(b(4, 0) == 0);
    REQUIRE(b(5, 0) == 0);
    REQUIRE(b(6, 0) == 1);
    REQUIRE(b(7, 0) == 1);
    REQUIRE(b(8, 0) == 2);
    REQUIRE(b(9, 0) == 2);
    REQUIRE(b(10, 0) == 3);

  }

  SECTION("reorder test(from reorder.cpp") {

    geometry<double> g(0);

    g.add("C1", 1, 1, 1);
    g.add("C2", 1, 1, 0);
    g.add("C3", 1, 0, 0);
    g.add("C4", 0, 0, 0);

    geometry<double> g1(g);

    g1.reorder({2,0,3,1});

    REQUIRE(g.atom(0) == "C1");
    REQUIRE(g.atom(1) == "C2");
    REQUIRE(g.atom(2) == "C3");
    REQUIRE(g.atom(3) == "C4");
    REQUIRE(g.pos(0)  == vector3<double>{1, 1, 1});
    REQUIRE(g.pos(1)  == vector3<double>{1, 1, 0});
    REQUIRE(g.pos(2)  == vector3<double>{1, 0, 0});
    REQUIRE(g.pos(3)  == vector3<double>{0, 0, 0});

    REQUIRE(g1.atom(0) == "C3");
    REQUIRE(g1.atom(1) == "C1");
    REQUIRE(g1.atom(2) == "C4");
    REQUIRE(g1.atom(3) == "C2");
    REQUIRE(g1.pos(0)  == vector3<double>{1, 0, 0});
    REQUIRE(g1.pos(1)  == vector3<double>{1, 1, 1});
    REQUIRE(g1.pos(2)  == vector3<double>{0, 0, 0});
    REQUIRE(g1.pos(3)  == vector3<double>{1, 1, 0});

  }

}
