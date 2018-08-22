#include <iostream>
#include <geom/geom.hpp>
#include <data/ptable.hpp>
#include <geom/tws_tree.hpp>
#include <io/geomio.hpp>
#include <data/symmetric_key.hpp>
#include <map>

int main(){
  qpp::periodic_cell<float> cell({4,0,0},{0,6,0},{0,0,4});
  qpp::geometry<float,decltype(cell)> g(cell);
  qpp::tws_tree<float> artree(g);

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
  std::vector<qpp::tws_node_content<float>*> res;
//  artree.query_sphere(2, qpp::vector3<float>(0.2127, -1.1952, 1.4338), &res);
//  std::cout << "test query size = " << res.size() << std::endl;
//  std::map<qpp::sym_key<int>, float> map1;
//  map1[qpp::sym_key<int>(1,2)] = 2.3;

//  std::cout << "tsp = " << map1[qpp::sym_key<int>(1,2)] << " " <<
//               map1[qpp::sym_key<int>(2,1)] << std::endl;

//  artree.find_neighbours(2257);
  artree.find_all_neighbours();
  qpp::ray<float> r1(qpp::vector3<float>(1.0, 1.0, 1.0),
                     qpp::vector3<float>(0.0, 1.0, 0.0));
  float stored;
  std::cout << "ray test "
            << qpp::ray_sphere_test(&r1,
                                    qpp::vector3<float>(1.0, 4.0, 2.19f), 1.2f)
            << std::endl;
//  std::cout << "ntest = " << artree.n(2257) << std::endl;
}



