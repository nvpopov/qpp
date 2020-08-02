#include <catch.hpp>
#include <geom/xgeom.hpp>
#include <geom/builders.hpp>
#include <symm/gen_cell.hpp>
#include <io/geomio.hpp>
#include <symm/point_groups.hpp>
#include <symm/autosymm.hpp>

using namespace qpp;

TEST_CASE("find point groups - simple - D3d") {

  // Create geometry
  geometry<float> g;
  g.add("C", 0., 0., -.7);
  g.add("C", 0., 0.,  .7);
  g.add("H", .8, 0.,  .95);
  g.add("H",-.8, 0., -.95);
  g.add("H",-.4, .7,  .95);
  g.add("H",-.4,-.7,  .95);
  g.add("H", .4, .7, -.95);
  g.add("H", .4,-.7, -.95);

  array_group<matrix3<float> > G;

  float eps = .1;
  vector3<float> new_centre;
  find_point_symm(G, g, new_centre, eps);

  REQUIRE(G.m_name == "D3d");

}

TEST_CASE("Point groups - manual build") {

  // Create main axis vector and corresponding rotation matrix
  auto main_axis = vector3<float>(0, 0, 1);
  int n_order = 4;
  auto main_rot = RotMtrx(main_axis, float(2*pi/n_order));

  // Create U2 rotation matrix
  // Note the brace initialization of axis vector
  auto u2_rot = RotMtrx({1, 0, 0}, float(pi));

  // Create empty group in array form
  array_group<matrix3<float> > G_array;

  // Add elements
  G_array.generate(main_rot);
  G_array.generate(u2_rot);

  // Check the number of elements
  //std::cout << "Number of elements in D4 group = " << G_array.size() << std::endl;
  REQUIRE(G_array.size() == 8);

  // Now we add the mirror plane and turn D4 into D4h
  auto mirror = Sigma<float>({0,0,1});
  G_array.generate(mirror);

  //std::cout << "Number of elements in D4h group = " << G_array.size() << std::endl;
  REQUIRE(G_array.size() == 16);

  // Convert the group from array to generator form
  genform_group<matrix3<float> > G;
  generator_form(G,G_array);

  // Print the generators
//  std::cout << "Number of D4h group generators = "
//            << G.DIM << std::endl << "Generators are:" << std::endl;
  REQUIRE(G.DIM == 3);

  REQUIRE(G.generators[0] == matrix3<float> {
                                 -0.000000, -1.000000, 0.000000,
                                  1.000000, -0.000000, 0.000000,
                                  0.000000, 0.000000, 1.000000
                             });
  REQUIRE(G.end()(0)+1 == 4);

  REQUIRE(G.generators[1] == matrix3<float> {
                                 1.000000, 0.000000, 0.000000,
                                 0.000000, -1.000000, 0.000000,
                                 0.000000, -0.000000, -1.000000
                             });
  REQUIRE(G.end()(1)+1 == 2);

  REQUIRE(G.generators[2] == matrix3<float> {
                                 1.000000, -0.000000, -0.000000,
                                 -0.000000, 1.000000, -0.000000,
                                 -0.000000, -0.000000, -1.000000
                             });
  REQUIRE(G.end()(2)+1 == 2);

//  for (int i=0; i<G.DIM; i++)
//    std::cout << G.generators[i] << std::endl << "the order is " << G.end()(i)+1 << std::endl;

}

TEST_CASE("inspect rotrans(from fps_tests.cpp)") {

  double a = 2.76;
  qpp::periodic_cell<double> cell({0,a,a}, {a,0,a}, {a,a,0});

  qpp::rotrans<double,true> r(
      qpp::vector3<double>(0,a,a),
      qpp::RotMtrx({0,0,1}, qpp::pi/6)*qpp::Sigma(qpp::vector3<double>(0,0,1)),
      & cell);

  std::vector<qpp::index> idx;
  for (qpp::index I: qpp::inspect_rotrans(r,1e-5)) idx.push_back(I);

  REQUIRE(idx.size() == 1);
  REQUIRE(idx[0] == qpp::index{-1, 0, 0});

}

TEST_CASE("bravais point group(from lattice_point_group.cpp") {

  periodic_cell<float> cl({0,1,1}, {1,0,1}, {1,1,0});
  array_group<matrix3<float> >  G;

  bravais_point_group(G, cl, float(.1));

  //std::cout << G.m_name << std::endl;
  REQUIRE(G.m_name == "Oh");

}

TEST_CASE("nullspace(from livecs.cpp") {

  qpp::matrix<double> A(4,5);
  //qpp::vector3<double> a(1,2,3), b(1,0,1), c(2,0,0);

  A <<
      0, 2, 1, 1, 0,
      1, 4, 1, 3, 2,
      2, 6, 1, 2, 1,
      3, 8, 1.0001, 5, 4;

  //std::cout << "matrix was\n" << A << "\nrank is "<< qpp::matrix_rank(A, .0000001)<< "\n";
  REQUIRE(qpp::matrix_rank(A, .0000001) == 4);

  auto L = qpp::LI_vectors(A,.000001);

  std::vector<int> I,D;
  qpp::matrix<double> ns;

  qpp::nullspace(I, D, ns, A, .000001);

//  std::cout << "indep\n";
//  for (int i:I)
//    std::cout << i << " ";
//  std::cout << "\n";
  REQUIRE(I.size() == 4);
  REQUIRE(I[0] == 0);
  REQUIRE(I[1] == 1);
  REQUIRE(I[2] == 2);
  REQUIRE(I[3] == 3);

//  std::cout << "dep\n";
//  for (int i:D)
//    std::cout << i << " ";
//  std::cout << "\n";

  REQUIRE(D.size() == 1);
  REQUIRE(D[0] == 4);

//  std::cout << "nulspace\n" << ns << "\n";

//  for (int q = 0; q < 5; q++)
//    std::cout << fmt::format("{:8.16f}", ns(q, 0)) << std::endl;

  REQUIRE(ns(0, 0) == Approx(1.0000005328791555).epsilon(1e-10));
  REQUIRE(ns(1, 0) == Approx(-0.5000002664410588).epsilon(1e-10));
  REQUIRE(ns(2, 0) == Approx(0.0000005329058008).epsilon(1e-10));
  REQUIRE(ns(3, 0) == Approx(0.9999999999881589).epsilon(1e-10));
  REQUIRE(ns(4, 0) == Approx(-1.0000000000000000).epsilon(1e-10));

}

TEST_CASE("subspace(from subsp.cpp)") {

  rotrans<double> R1 = rotrans<double>({1,0,0},RotMtrx({0,1,1},2*pi/4));
  //rotrans<double> R1 = rotrans<double>({1,1,-1},Sigma<double>({1,1,-1}));
  auto S1 = invariant_subspace(rotrans4d(R1));

//  std::cout << "dim(S1)= " << S1.dim << " point(S1)= " << S1.point << std::endl
//            << " axis(S1)= " << S1.axis << std::endl  << S1.X << std::endl
//            << "orths= " << std::endl << S1.orths << std::endl;

  REQUIRE(S1.dim == 1);
  REQUIRE(S1.point == vector3<double>{0.500000000000, 0.353553390593, -0.353553390593});
  REQUIRE(S1.axis == vector3<double>{0.000000000000, 0.707106781187, 0.707106781187});
  REQUIRE(S1.X(0, 0) == Approx(-0.377964473).epsilon(1e-9));
  REQUIRE(S1.X(0, 1) == Approx(0.15430335).epsilon(1e-9));
  REQUIRE(S1.X(1, 0) == Approx(0.0).epsilon(1e-9));
  REQUIRE(S1.X(1, 1) == Approx(0.7637626158).epsilon(1e-9));
  REQUIRE(S1.X(2, 0) == Approx(0.5345224838).epsilon(1e-9));
  REQUIRE(S1.X(2, 1) == Approx(0.5455447256).epsilon(1e-9));
  REQUIRE(S1.X(3, 0) == Approx(-0.755928946).epsilon(1e-9));
  REQUIRE(S1.X(3, 1) == Approx(0.3086066999).epsilon(1e-9));

  matrix<double> ref_ort1(4, 2);
  ref_ort1(0, 0) = 1.5418e-16;
  ref_ort1(0, 1) = 0.408248;
  ref_ort1(1, 0) = 0.707107;
  ref_ort1(1, 1) = 0.288675;
  ref_ort1(2, 0) = 0.707107;
  ref_ort1(2, 1) = -0.288675;
  ref_ort1(3, 0) = 0.0;
  ref_ort1(3, 1) = 0.816497;

  REQUIRE(S1.orths.isApprox(ref_ort1, 1e-6));

  rotrans<double> R2 = rotrans<double>({1,1,1},Sigma<double>({1,1,1}));
  auto S2 = invariant_subspace(rotrans4d(R2));

//  std::cout << "dim(S2)= " << S2.dim << " point(S2)= " << S2.point << std::endl
//            << " axis(S2)= " << S2.axis << std::endl  << S2.X << std::endl
//            << "orths= " << std::endl << S2.orths << std::endl;

  REQUIRE(S2.dim == 2);
  REQUIRE(S2.point == vector3<double>{0.500000000000, 0.500000000000, 0.500000000000});
  REQUIRE(S2.axis == vector3<double>{0.577350269190, 0.577350269190, 0.577350269190});
  REQUIRE(S2.X(0, 0) == Approx(0).epsilon(1e-9));
  REQUIRE(S2.X(0, 1) == Approx(0).epsilon(1e-9));
  REQUIRE(S2.X(0, 2) == Approx(0.8997354108).epsilon(1e-9));
  REQUIRE(S2.X(1, 0) == Approx(0.8320502943).epsilon(1e-9));
  REQUIRE(S2.X(1, 1) == Approx(-0.2690691176).epsilon(1e-9));
  REQUIRE(S2.X(1, 2) == Approx(-0.2117024496).epsilon(1e-9));
  REQUIRE(S2.X(2, 0) == Approx(0.0).epsilon(1e-9));
  REQUIRE(S2.X(2, 1) == Approx(0.8744746322).epsilon(1e-9));
  REQUIRE(S2.X(2, 2) == Approx(-0.2117024496).epsilon(1e-9));
  REQUIRE(S2.X(3, 0) == Approx(0.5547001962).epsilon(1e-9));
  REQUIRE(S2.X(3, 1) == Approx(0.4036036764).epsilon(1e-9));
  REQUIRE(S2.X(3, 2) == Approx(0.3175536744).epsilon(1e-9));

  matrix<double> ref_ort2(4, 3);
  ref_ort2(0, 0) = 0.0;
  ref_ort2(0, 1) = 0.816497;
  ref_ort2(0, 2) = 0.377964;
  ref_ort2(1, 0) = -0.707107;
  ref_ort2(1, 1) = -0.408248;
  ref_ort2(1, 2) = 0.377964;
  ref_ort2(2, 0) = 0.707107;
  ref_ort2(2, 1) = -0.408248;
  ref_ort2(2, 2) = 0.377964;
  ref_ort2(3, 0) = 0.0;
  ref_ort2(3, 1) = 0.0;
  ref_ort2(3, 2) = 0.755929;

  REQUIRE(S2.orths.isApprox(ref_ort2, 1e-6));

  auto S3 = S1 & S2;

//  std::cout << "dim(S3)= " << S3.dim << " point(S3)= " << S3.point << std::endl
//            << " axis(S3)= " << S3.axis << std::endl  << S3.X << std::endl
//            << "orths= " << std::endl << S3.orths << std::endl;

  REQUIRE(S3.dim == 0);
  REQUIRE(S3.point == vector3<double>{0.500000000000, 0.853553390593, 0.146446609407});
  REQUIRE(S3.axis == vector3<double>{0.000000000000, 0.000000000000, 0.000000000000});
  REQUIRE(S3.X(0, 0) == Approx(0.3535533906).epsilon(1e-9));
  REQUIRE(S3.X(1, 0) == Approx(0.6035533906).epsilon(1e-9));
  REQUIRE(S3.X(2, 0) == Approx(0.1035533906).epsilon(1e-9));
  REQUIRE(S3.X(3, 0) == Approx(0.7071067812).epsilon(1e-9));

  matrix<double> ref_ort3(4, 1);
  ref_ort3(0, 0) = 0.353553;
  ref_ort3(1, 0) = 0.603553;
  ref_ort3(2, 0) = 0.103553;
  ref_ort3(3, 0) = 0.707107;

  REQUIRE(S3.orths.isApprox(ref_ort3, 1e-6));

}

TEST_CASE("has_symmtery(from autosymm.cpp") {

  matrix3<double> C4x = RotMtrx({1,0,0}, pi/2);
  matrix3<double> C4y = RotMtrx({0,1,0}, pi/2);
  matrix3<double> I = matrix3<double>::Identity()*-1;

  array_group<matrix3<double> > OH;

  OH.generate(C4x);
  OH.generate(C4y);
  OH.generate(I);

  //matrix3d<double>::tol_equiv = 1e-6;

  gen_cell<double,matrix3<double> > Oh;
  generator_form(Oh,OH);

  //std::cout << "orders: " << Oh.begin() << Oh.end() << "\n";
  REQUIRE(Oh.begin() == qpp::index{0, 0, 0});
  REQUIRE(Oh.end() == qpp::index{5, 3, 1});

  geometry<double, decltype(Oh) > UF6(0);
  UF6.add("U",0,0,0);
  UF6.add("F", 3, 0, 0);
  UF6.add("F",-3, 0, 0);
  UF6.add("F", 0, 3, 0);
  UF6.add("F", 0,-3, 0);
  UF6.add("F", 0, 0, 3);
  UF6.add("F", 0, 0,-3);

  UF6.add("F_shl", 3, 0, 0);
  UF6.add("F_shl",-3, 0, 0);
  UF6.add("F_shl", 0, 3, 0);
  UF6.add("F_shl", 0,-3, 0);
  UF6.add("F_shl", 0, 0, 3);
  UF6.add("F_shl", 0, 0,-3.0);

  //std::cout << has_symmetry(UF6, Oh) << "\n";
  REQUIRE(has_symmetry(UF6, Oh));

}

//TEST_CASE("chartab(from chartab.cpp)") {

//  /*
//  auto C3 = RotMtrx({0,0,1},2*pi/3);
//  auto Sig = Sigma<double>({0,1,0});

//  generated_group<matrix3d<double> > T;
//  T.generator(C3);
//  T.generator(Sig);
//  */

//  auto C4 = RotMtrx({1,0,0}, pi/2);
//  auto C3 = RotMtrx({1,1,1}, 2 * pi/3);
//  auto C31 = RotMtrx({1,-1,-1}, 2 * pi/3);

//  array_group<matrix3<double> > T;
//  T.generate(C4);
//  T.generate(C3);
//  // T.generator(C31);

//  std::cout << "Group size = " << T.size() << std::endl;

//  std::cout << std::setprecision(6) << std::fixed;

//  for (int g=0; g<T.size(); g++)
//    std::cout << g << std::endl << T[g] << std::endl;

//  group_analyzer<decltype(C3), decltype(T)> A(T);

//  std::cout << "N classes = " << A.n_classes() << "\n";
//  for (int c=0; c< A.n_classes(); c++)
//  {
//    for (int j=0; j<A.class_size(c); j++)
//      std::cout << A.class_element(c,j) << " ";
//    std::cout << std::endl;
//  }

//  group_characters<std::complex<double>,decltype(C3), decltype(T)> chi(T,A);
//  //group_characters<double,decltype(C3), decltype(T)> chi(T,A);

//  std::cout << "N IRREP = " << chi.nirrep << std::endl;

//  /*
//  for (int irrep = 0; irrep < chi.nirrep; irrep++)
//    {

//}*/

//        std::cout << chi.chi << std::endl;

//}
