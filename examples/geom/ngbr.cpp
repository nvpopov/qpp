#include <geom/ngbr.hpp>

int main()
{
  qpp::geometry<double> amino(0);

  amino.add("N",          1.75524,       -0.03055,       -0.15305);
  amino.add("C",          0.46128,        0.62257,        0.10589);
  amino.add("C",         -0.74491,       -0.32028,       -0.01207);
  amino.add("O",         -1.89675,        0.44072,        0.26071);
  amino.add("H",          1.76784,       -0.40647,       -1.07847);
  amino.add("H",          1.89801,       -0.77424,        0.49847);
  amino.add("H",          0.36238,        1.46995,       -0.60184);
  amino.add("H",          0.50565,        1.07184,        1.11828);
  amino.add("H",         -0.66487,       -1.16329,        0.70383);
  amino.add("H",         -0.80945,       -0.76139,       -1.02735);
  amino.add("H",         -2.63443,       -0.14886,        0.18560);

  qpp::bonding_table<double> dt;
  dt.default_distance = 1.5;
  dt.set_pair("C","C",1.7);

  qpp::neighbours_table<double> b(amino,dt);

  amino.write(std::cout);

  for (int t=0; t<amino.n_atom_types(); t++)
    std::cout << "type " << t << " = " << amino.atom_of_type(t) << "\n";
  for (int i=0; i<amino.nat(); i++)
    std::cout << i << " " << amino.atom(i) << " " << amino.type(i) << "\n";

  dt.write(std::cout);

  //b.reference_mode = true;
  b.build();

  std::cout << "ngbr finished\n";

  for (int i=0; i<amino.nat(); i++)
    {
      std::cout << "atom " << i;
      for (int j=0; j<b.n(i); j++)
	std::cout << " " << b(i,j);
      std::cout << std::endl;
    }

}
