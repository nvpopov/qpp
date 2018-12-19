#include <iostream>
#include <geom/geom.hpp>
#include <data/ptable.hpp>
#include <geom/tws_tree.hpp>
#include <io/geomio.hpp>
#include <data/symmetric_key.hpp>
#include <map>

static std::array<qpp::vector3<float>, 1> a2
= {qpp::vector3<float>(0.1f, 0.2f, 0.3f)};

static qpp::vector3<float> a(0.1, 0.2, 0.3);

int main(){

  qpp::aabb_3d_t<float> box;
  box.min = qpp::vector3<float>(-9,-9,-9);
  box.max = qpp::vector3<float>(9,9,9);
  qpp::vector3<float> pos(3.78878,1.23105,-6.82411);
  qpp::vector3<float> vs = (box.max - box.min) / 2;
  qpp::vector3<float> p_f = pos;
  std::cout << box << std::endl;
  std::cout << fmt::format("p_f = {} {} {}", p_f[0], p_f[1], p_f[2]) << std::endl;

  std::cout << fmt::format("vs = {} {} {}", vs[0], vs[1], vs[2]) << std::endl;

  std::cout <<fmt::format("h {} {} {}",
                          (pos[0]/vs[0]),
      (pos[1]/vs[1]),
      (pos[2]/vs[2]))<<std::endl;
  std::cout <<fmt::format("h {} {} {}",
                          floor(pos[0]/vs[0]),
       floor(pos[1]/vs[1]),
       floor(pos[2]/vs[2]))<<std::endl;
  float val0 = pos[0]/vs[0];
  float val0_t = std::copysignf(1.0f, val0) * (round(fabs(pos[0]/vs[0])));
  float val1 = pos[1]/vs[1];
  float val1_t = std::copysignf(1.0f, val1) * (round(fabs(pos[1]/vs[1])));
  float val2 = pos[2]/vs[2];
  float val2_t = std::copysignf(1.0f, val2) * (round(fabs(pos[2]/vs[2])));

  std::cout <<fmt::format("h {} {} {}", val0_t, val1_t, val2_t)<<std::endl;


  qpp::periodic_cell<float> cell({4,0,0},{0,6,0},{0,0,4});
  qpp::xgeometry<float,decltype(cell)> g(cell);
  qpp::tws_tree_t<float> artree(g);

  std::ifstream si2("../examples/io/ref_data/dna.xyz");
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
  std::vector<qpp::tws_node_content_t<float>*> res;
  //  artree.query_sphere(2, qpp::vector3<float>(0.2127, -1.1952, 1.4338), &res);
  //  std::cout << "test query size = " << res.size() << std::endl;
  //  std::map<qpp::sym_key<int>, float> map1;
  //  map1[qpp::sym_key<int>(1,2)] = 2.3;

  //  std::cout << "tsp = " << map1[qpp::sym_key<int>(1,2)] << " " <<
  //               map1[qpp::sym_key<int>(2,1)] << std::endl;

  //  artree.find_neighbours(2257);
  artree.find_all_neighbours();
  qpp::ray_t<float> r1(qpp::vector3<float>(1.0, 1.0, 1.0),
                     qpp::vector3<float>(0.0, 1.0, 0.0));
  float stored;
  std::cout << "ray test "
            << qpp::ray_sphere_test(&r1,
                                    qpp::vector3<float>(1.0, 4.0, 2.19f), 1.2f)
            << std::endl;
  //  std::cout << "ntest = " << artree.n(2257) << std::endl;
  std::cout<<a2[0]<<std::endl;




}



