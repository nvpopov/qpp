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

}

