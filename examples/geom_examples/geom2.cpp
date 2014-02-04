#include <iostream>
#include <geom/geom.hpp>

// -------------- Type table & neighbours table ---------------------

int main()
{
  qpp::geometry<0> g;

  g.add("C",       -1.676283510,      0.000000000,      1.911126199);
  g.add("O",       -1.753146399,      1.141923181,      1.514919538);
  g.add("O",       -1.604477009,     -1.066694960,      1.079653080);
  g.add("H",       -1.628395866,     -0.711301327,      0.174843873);
  g.add("C",       -1.647886655,     -0.422100383,      3.375898205);
  g.add("H",       -2.475776531,     -1.122649475,      3.538396631);
  g.add("N",       -1.721124037,      0.666230718,      4.332560746);
  g.add("H",       -2.565816675,      1.205870339,      4.156284306);
  g.add("H",       -0.956315270,      1.314146931,      4.156322052);
  g.add("H",       -0.733613146,     -1.005425023,      3.538407817);

  g.build_type_table();

  std::cout << "--------------------- With build_type_table ----------------\n";

  for (int i=0; i<g.n_atom_types(); i++)
    std::cout << i << " = " << g.atom_of_type(i) << "\n";

  std::cout << "\n";

  for (int i=0; i<g.size(); i++)
    std::cout << g.type_table(i) << " " << g.coord(i) << "\n";

  qpp::geometry<0> g1;
  g1.update_types = true;  

  g1.add("Carbon",       -1.676283510,      0.000000000,      1.911126199);
  g1.add("Oxygen",       -1.753146399,      1.141923181,      1.514919538);
  g1.add("Oxygen",       -1.604477009,     -1.066694960,      1.079653080);
  g1.add("Hydrogen",       -1.628395866,     -0.711301327,      0.174843873);
  g1.add("Coronium",       0,0,0);
  g1.add("Carbon",       -1.647886655,     -0.422100383,      3.375898205);
  g1.add("Hydrogen",       -2.475776531,     -1.122649475,      3.538396631);
  g1.add("Coronium",       0,0,0);
  g1.add("Newtonium",      0,0,0);
  g1.add("Hydrogen",       -2.565816675,      1.205870339,      4.156284306);
  g1.add("Hydrogen",       -0.956315270,      1.314146931,      4.156322052);
  g1.add("Hydrogen",       -0.733613146,     -1.005425023,      3.538407817);
  
  g1.erase(4);
  g1.erase(7);
  g1.erase(6);

  g1.insert(6, "Nitrogen",       -1.721124037,      0.666230718,      4.332560746);

  std::cout << "--------------------- With auto update ----------------\n";

  for (int i=0; i<g1.n_atom_types(); i++)
    std::cout << i << " = " << g1.atom_of_type(i) << "\n";

  std::cout << "\n";

  for (int i=0; i<g1.size(); i++)
    std::cout << g1.type_table(i) << " " << g1.coord(i) << "\n";

}

