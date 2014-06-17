#include <geom/geom_extras.hpp>
#include <io/geomio.hpp>
#include <lace/lace3d.hpp>

using namespace qpp;

int main()
{
  parametric_torus<double> tor(4,2);
  surf_symplicator<3,double> symm(tor);
 
  symm(0) = lace::vector3d<double>(0, 2*pi/3, 0);
  symm(1) = Sigma(lace::vector3d<double>(0,1,0));
  symm(2) = Sigma(lace::vector3d<double>(1,0,0));

  gen_geometry<3, double, surf_symplicator<3,double> > G(symm);

  /*
  int n=2, m=5;
  for (int i=0; i<=n; i++)
    for (int j=0; j<=m; j++)
      G.add("C", j*pi/m, i*2*pi/(6*n), 0);
  */
  G.add("Si",0,0,0);
  G.add("O",.5,.5,0);
  G.add("Si",pi,0,0);
  G.add("O",pi-.3,.2,0);
  G.add("H",pi/3,pi/3,0);

  geometry<0,double> GG;

  gen_geometry<3,double,symplicator<3,double> >::iterator 
    i( qpp::index<3>(0, 0,0,0), qpp::index<3>( G.nat()-1, 3,2,2) );

  for ( i=i.begin(); i!=i.end(); i++ )
    {
      lace::vector3d<double> r = G.position(i);
      bool found = false;
      for (int j=0; j<GG.nat(); j++)
	if ( GG.atom(j)==G.atom(i) && norm(GG.coord(j)-r) < 1e-3)
	  {
	    found = true;
	    break;
	  }
      if (!found)
      GG.add(G.atom(i), r );
    }
  
  std::ofstream f("surf.xyz");
  write_xyz(f,GG);

  std::ofstream f1("surf1.xyz");
  GG.clear();
  for (int j=0; j<G.nat(); j++)
    GG.add(G.atom(j), G.position(j));
  write_xyz(f1,GG);

  G.ngbr.default_distance = 1.8;
  G.build_type_table();
  G.ngbr.build_disttable();
  G.ngbr.build();

  for (int j=0; j<G.nat(); j++)
    for (int k=0; k<G.ngbr.n(j); k++)
      std::cout << j << " " << G.ngbr(j,k) << " |r|= " << norm(G.position(j) - G.position(G.ngbr(j,k))) 
		<< " r= " << G.position(G.ngbr(j,k)) << "\n";
  

}
