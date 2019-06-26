#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <geom/lace3d.hpp>

using namespace qpp;
using v3f = vector3<float>;
using m3f = matrix3<float>;

TEST_CASE( "Basic vector3<T> tests", "[vector3<T>]" ) {

  v3f vf;
  v3f zero_vf = v3f::Zero();
  v3f v_one{1.0f, 1.0f, 1.0f};
  v3f v_two(2.0f, 2.0f, 2.0f);
  v3f v_nt1(0.0f, 3.0f, 0.0f);
  v3f v_x(1.0f, 0.0f, 0.0f);
  v3f v_y(0.0f, 1.0f, 0.0f);
  v3f v_z(0.0f, 0.0f, 1.0f);

  //testing vector equivalence
  REQUIRE( abs(zero_vf[0]) + abs(zero_vf[0]) + abs(zero_vf[0]) <= v3f::tol_equiv);

  //testing vec + vec
  REQUIRE( v3f(v3f(1.0f, 1.0f, -1.0f) + v3f(2.0f, 2.0f, 1.0f)) == v3f(3.0f, 3.0f, 0.0f));

  //testing scalar product
  REQUIRE( v3f(1,2,3).dot(v3f(1,5,7)) == Approx(32));

  //testing vec * scalar
  REQUIRE( v3f(v_one * 2.0f) == v_two );

  //testing normalization
  REQUIRE( v3f(v_nt1.normalized()) == v_y );

  //testing cross product
  REQUIRE( v3f(v_x.cross(v_y)) == v_z) ;
}

TEST_CASE( "Basic matrix3<T> tests", "[vector3<T>]" ) {

  m3f m1 = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
  m3f m1_m = {{-1.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}};

  //testing unity
  REQUIRE (m1 == m3f::unity);

  //testing matrix summation
  REQUIRE( m3f(m1+m1_m) == m3f(m3f::Zero()) );

  //testing mat mult
  REQUIRE( m3f(m1*m1_m) == m1_m);

  //testing mat mul 2
  m3f m_b1 = {{1,	2, 3},
              {2, 4, 2},
              {3, 4, 1}};

  m3f m_b2 = {{3, 4, 5},
              {1, 2, 4},
              {2, 3, 4}};

  m3f m_br = {{11, 17, 25},
              {14, 22, 34},
              {15, 23, 35}};

  REQUIRE( m3f(m_b1*m_b2) == m_br);

  //testing mat mul + inverse
  REQUIRE( m3f(m_br * m_b2.inverse()) == m_b1);

  //testing direct inverse
  m3f m_it = { {1, 2, 4}, {5, 2, 1}, {3, 4, 1} };
  m3f m_it_i = { {-1.0f/25, 7.0f/25, -3.0f/25},
                 {-1.0f/25, -11.0f/50, 19.0f/50},
                 {7.0f/25, 1.0f/25, -4.0f/25}
               };
  REQUIRE( m3f(m_it.inverse())== m_it_i);

  //testing matrix determinant
  m3f m_dt = {{2, 4, 1}, {2, 24, 23}, {12, 23,1}};
  REQUIRE( m_dt.determinant() == Approx(-156));

  SECTION("Matrix power") {

    m3f m_pt = {
      {2, 3, 4},
      {1, 5, 2},
      {5, 4, 3}
    };

    m3f m_pt_res2 = {
      {27, 37, 26},
      {17, 36, 20},
      {29, 47, 37}
    };

    m3f m_pt_res3 = {
      {221, 370, 260},
      {170, 311, 200},
      {290, 470, 321}
    };

    REQUIRE(m3f(m_pt.pow(1.0f)) == m_pt );
    REQUIRE(m3f(m_pt.pow(2.0f)) == m_pt_res2 );
    REQUIRE(m3f(m_pt.pow(3.0f)) == m_pt_res3 );

  }

  //diagonalization test
  SECTION("Diagonalization test") {

    m3f m_di_t = {{1,2,1}, {6,-1,0}, {-1, -2, -1}};
    Eigen::ComplexEigenSolver<Eigen::Matrix<float, 3 , 3> > ces;
    ces.compute(m_di_t);
    Eigen::Array<typename numeric_type<float>::complex, Eigen::Dynamic, 1> lbd;
    lbd = ces.eigenvalues();

    v3f m_di_t_ev = diagon3d(m_di_t);

    REQUIRE( lbd[0].real() == Approx(0).margin(0.01) );
    REQUIRE( lbd[1].real() == Approx(3).margin(0.01) );
    REQUIRE( lbd[2].real() == Approx(-4).margin(0.01) );

    REQUIRE( m_di_t_ev[0] == Approx(-4).margin(0.01) );
    REQUIRE( m_di_t_ev[1] == Approx(3).margin(0.01) );
    REQUIRE( m_di_t_ev[2] == Approx(0).margin(0.01) );

  }

  SECTION("Linear equations test") {

    m3f m_a_l = {{2, 1, 3}, {2, 6, 8}, {6, 8, 18}};
    v3f v_a_l = {1, 3, 5};
    v3f v_a_l_answ = {3.0f/10, 2.0f/5, 0.0f};
    v3f sec_a = solve3(m_a_l, v_a_l);
    //    v3f v_a_l_answ_eigen3 = m_a_l.inverse() * v_a_l;

    //    REQUIRE(v_a_l_answ_eigen3.isApprox(v_a_l_answ));

    REQUIRE(sec_a[0] == Approx(v_a_l_answ[0]));
    REQUIRE(sec_a[1] == Approx(v_a_l_answ[1]));
    REQUIRE(sec_a[2] == Approx(v_a_l_answ[2]));
    REQUIRE(sec_a == v_a_l_answ);

    v3f ma_r0 = {2, 1, 3};
    v3f ma_r1 = {2, 6, 8};
    v3f ma_r2 = {6, 8, 18};

    v3f sec_a2 = solve3(ma_r0, ma_r1, ma_r2, v_a_l);
    REQUIRE(sec_a2[0] == Approx(v_a_l_answ[0]));
    REQUIRE(sec_a2[1] == Approx(v_a_l_answ[1]));
    REQUIRE(sec_a2[2] == Approx(v_a_l_answ[2]));

  }

  SECTION("Testing rotation matrices") {

    m3f rot_m_x = {
      {1.0f, 0.0f,           0.0f},
      {0.0f, cos(float(pi) / 4.0f), -sin(float(pi)/4.0f)},
      {0,    sin(float(pi)/4.0f),   cos(float(pi) / 4.0f)}
    };
    v3f rot_m_x_a = v3f(1.0f, 0.0f, 0.0f);
    m3f rot_m_x_i = RotMtrx<float>(rot_m_x_a, float(pi)/4.0f);
    REQUIRE( rot_m_x == rot_m_x_i);

    m3f rot_m_y = {
      {cos(float(pi) / 4.0f), 0.0f, sin(float(pi)/4.0f)},
      {0.0f,           1.0f, 0.0f},
      {-sin(float(pi)/4.0f), 0.0f, cos(float(pi) / 4.0f)}
    };
    v3f rot_m_y_a = v3f(0.0f, 1.0f, 0.0f);
    m3f rot_m_y_i = RotMtrx<float>(rot_m_y_a, float(pi)/4.0f);
    REQUIRE( rot_m_y == rot_m_y_i);

    m3f rot_m_z = {
      {cos(float(pi) / 4.0f), -sin(float(pi)/4.0f),  0.0f},
      {sin(float(pi)/4.0f),   cos(float(pi) / 4.0f), 0.0f},
      {0.0,            0.0f,           1.0f}
    };
    v3f rot_m_z_a = v3f(0.0f, 0.0f, 1.0f);
    m3f rot_m_z_i = RotMtrx<float>(rot_m_z_a, float(pi)/4.0f);
    REQUIRE( rot_m_z == rot_m_z_i);
  }

  SECTION("Testing sigma matrices") {

    m3f s_m_u = m3f::unity;

    m3f s_m_y = {
      { 1,  0,  0},
      { 0, -1,  0},
      { 0,  0,  1}
    };

    v3f s_m_ay(0.0f, 1.0f, 0.0f);
    m3f s_m_y_g = Sigma(s_m_ay);

    REQUIRE(s_m_y_g == s_m_y);

  }

}

TEST_CASE( "lace3d miscellaneous tests" ) {

  SECTION("Solving cubic equations") {
    vector3<typename numeric_type<float>::complex> res_ce = solve_cubeq(1.0f, 4.0f, -8.0f, 7.0f);
    REQUIRE(res_ce[0].real() == Approx(-5.6389));
    REQUIRE(res_ce[0].imag() == Approx(0.0));
    REQUIRE(res_ce[1].real() == Approx(0.81944));
    REQUIRE(res_ce[1].imag() == Approx(-0.75492));
    REQUIRE(res_ce[2].real() == Approx(0.81944));
    REQUIRE(res_ce[2].imag() == Approx(0.75492));

    vector3<typename numeric_type<float>::complex> res_ce2 = solve_cubeq(3.0f, 33.0f, 1.0f, 31.0f);
    REQUIRE(res_ce2[0].real() == Approx(-11.0544));
    REQUIRE(res_ce2[0].imag() == Approx(0.0));
    REQUIRE(res_ce2[1].real() == Approx(0.02720).margin(0.001));
    REQUIRE(res_ce2[1].imag() == Approx(-0.96645));
    REQUIRE(res_ce2[2].real() == Approx(0.02720).margin(0.001));
    REQUIRE(res_ce2[2].imag() == Approx(0.96645));
  }

}



