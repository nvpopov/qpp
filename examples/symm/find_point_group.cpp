#include <iostream>
#include <symm/point_groups.hpp>

using namespace qpp;

int main(){

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
}

