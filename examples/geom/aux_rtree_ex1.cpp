#include <iostream>
#include <geom/geom.hpp>
#include <data/ptable.hpp>
#include <geom/aux_rtree.hpp>
#include <io/geomio.hpp>
#include <data/symmetric_key.hpp>
#include <map>

int main(){
  qpp::periodic_cell<float> cell({4,0,0},{0,6,0},{0,0,4});
  qpp::geometry<float,decltype(cell)> g(cell);
  qpp::aux_rtree<float> artree(g);
//  g.add("C",       -1.676283510,      0.000000000,      1.911126199);
//  g.add("O",       -1.753146399,      1.141923181,      1.514919538);
//  g.add("O",       -1.604477009,     -1.066694960,      1.079653080);
//  g.add("H",       -1.628395866,     -0.711301327,      0.174843873);
//  g.add("Co",       0,5,0);
//  g.add("C",       -1.647886655,     -0.422100383,      3.375898205);
//  g.add("H",       -2.475776531,     -1.122649475,      3.538396631);
//  g.add("Co",       0,0,0);
//  g.add("N",      0,0,0);
//  g.add("H",       -2.565816675,      1.205870339,      4.156284306);
//  g.add("H",       -0.956315270,      1.314146931,      4.156322052);
//  g.add("H",       -0.733613146,     -1.005425023,      3.538407817);
//  g.add("H",       -22.733613146,     -1.005425023,      3.538407817);
//  g.add("H",       -12.733613146,     -4.005425023,      3.538407817);
//  g.add("H",       -12.733613146,     -5.005425023,      3.538407817);
//  g.insert(6, "S",       -1.721124037,      0.666230718,      4.332560746);

  std::ifstream si2("../examples/io/ref_data/nanotube.xyz");
  read_xyz(si2, g);

//  qpp::rtree_box_nd<float, qpp::vector2<float>, 2> r_2d, r1_2d, r2_2d;
//  r_2d.rect_min = {-1, -2};
//  r_2d.rect_max = { 1,  1};
//  r_2d.split(r1_2d, r2_2d);
//  std::cout << r1_2d << std::endl << r2_2d << std::endl;

//  qpp::rtree_box_nd<float> r, r1, r2;
//  r.rect_min = {-10, -10, -10};
//  r.rect_max = { 10,  10,  10};
//  r.split(r1, r2);
////  bool bInCurRect = r1.point_inside(g.r(0));
////  std::cout << int(bInCurRect) << std::endl;
//  std::cout << r1 << std::endl << r2 << std::endl;

  artree.debug_print();
  std::vector<qpp::rtree_node_content<float>*> res;
//  artree.query_sphere(2, qpp::vector3<float>(0.2127, -1.1952, 1.4338), &res);
//  std::cout << "test query size = " << res.size() << std::endl;
//  std::map<qpp::sym_key<int>, float> map1;
//  map1[qpp::sym_key<int>(1,2)] = 2.3;

//  std::cout << "tsp = " << map1[qpp::sym_key<int>(1,2)] << " " <<
//               map1[qpp::sym_key<int>(2,1)] << std::endl;

//  artree.find_neighbours(2257);
  artree.find_all_neighbours();
//  std::cout << "ntest = " << artree.n(2257) << std::endl;
}



