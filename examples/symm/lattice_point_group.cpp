#include <iostream>
#include <symm/autosymm.hpp>

using namespace qpp;

int main(){

  // Create cell

  periodic_cell<float> cl({0,1,1},{1,0,1},{1,1,0});
  array_group<matrix3<float> >  G;

  bravais_point_group(G, cl, float(.1));

}


