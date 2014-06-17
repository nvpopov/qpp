#include <geom/geom.hpp>
#include <io/geomio.hpp>
#include <iostream>
#include <algorithm>

int main(int argc, char* argv[])
{
  if (argc!=2)
    {
      std::cout << "Usage: geomstat file.xyz\n";
      exit(0);
    }

  qpp::geometry<0> G;
  std::ifstream inp(argv[1]);
  read_xyz(inp,G);

  //write_xyz(std::cout,G);
  double b, ravg;
  lace::vector3d<double> r0=0;
  std::vector<double> rr0;

  G.build_type_table();

  //std::cout << "Enter default bonding distance\n";
  //std::cin >> b;
  G.ngbr.set_distance("C","C",1.7);

  G.ngbr.default_distance = b;
  G.ngbr.build_disttable();
  G.ngbr.build();

  for (int i=0; i<G.nat(); i++)
    r0 += G.coord(i);

  r0 /= G.nat();
  std::cout << "Geometric molecule centre is " << r0 << "\n";
  
  ravg = 0e0;  
  for (int i=0; i<G.nat(); i++)
    {
      double dist = norm(G.coord(i)-r0);
      rr0.push_back(dist);
      ravg += dist;
    }
  ravg /= G.nat();

  std::sort(rr0.begin(),rr0.end());

  std::cout << boost::format("Average distance from centre = %13.8f\n") % ravg;
  std::cout << boost::format("Minimum = %13.8f \nMaximum = %13.8f\n") % rr0[0] % rr0[rr0.size()-1];

  rr0.clear();
  for (int i=0; i<G.nat(); i++)
    for (int j=0; j<G.ngbr.n(i); j++)
      if ( i > G.ngbr(i,j) )
	rr0.push_back(norm(G.coord(i) - G.coord(G.ngbr(i,j))));

  std::sort(rr0.begin(),rr0.end());
  double rcurr=0, eps = 1e-2;
  int nb = 0;
  ravg = 0e0;

  std::cout << "Bonding distances:\n";
  for (int i=0; i<rr0.size(); i++)
    {
      if ( rr0[i]-rcurr > eps)
	{
	  if (nb>0)
	    std::cout << nb << " x " << rcurr << "\n";
	  rcurr = rr0[i];
	  nb = 1;
	}
      else nb++;
      ravg += rr0[i];
    }
  std::cout << nb << " x " << rcurr << "\n";
  ravg /= rr0.size();
  std::cout << boost::format("Average interatomic distance = %13.8f\n") % ravg;
}
