#include <iostream>
#include <symm/groups.hpp>
#include <symm/group_theory.hpp>
#include <geom/lace3d.hpp>

using namespace qpp;

// This example shows how to manually build D4 and D4h point groups

int main()
{
  // Create main axis vector and corresponding rotation matrix
  auto main_axis = vector3<float>(0,0,1);
  int n_order = 4;
  auto main_rot = RotMtrx(main_axis,float(2*pi/n_order));

  // Create U2 rotation matrix
  // Note the brace initialization of axis vector
  auto u2_rot = RotMtrx({1,0,0},float(pi));

  // Create empty group in array form
  array_group<matrix3<float> > G_array;
  
  // Add elements
  G_array.generate(main_rot);
  G_array.generate(u2_rot);

  // Check the number of elements
  std::cout << "Number of elements in D4 group = " << G_array.size() << std::endl;

  // Now we add the mirror plane and turn D4 into D4h
  auto mirror = Sigma<float>({0,0,1});
  G_array.generate(mirror);
  
  std::cout << "Number of elements in D4h group = " << G_array.size() << std::endl;

  // Convert the group from array to generator form
  genform_group<matrix3<float> > G;
  generator_form(G,G_array);

  // Print the generators
  std::cout << "Number of D4h group generators = " << G.DIM << std::endl << "Generators are:" << std::endl;
  
  for (int i=0; i<G.DIM; i++)
    std::cout << G.generators[i] << std::endl << "the order is " << G.end()(i)+1 << std::endl;

}
