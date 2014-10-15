#include <geom/geom_extras.hpp>
#include <io/geomio.hpp>
#include <lace/lace3d.hpp>

using namespace qpp;

int main()
{
  
  lace::matrix3d<double> I(-1, 0,  0,
			   0, -1,  0,
			   0,  0, -1);

  symplicator<2,double> c3v;
  //  int n=3, m=2;
  c3v(0) = RotMtrx( lace::vector3d<double>(0,0,1), 2*pi/3 );
  c3v(1) = Sigma( lace::vector3d<double>(0,1,0) );

  symplicator<2,double> ss;
  //int n=6, m=5;
  ss(0) = Sigma( lace::vector3d<double>(0,0,1) )*RotMtrx( lace::vector3d<double>(0,0,1), 2*pi/6 );
  ss(1) = rotrans<2,double>( lace::vector3d<double>(0,0,4), RotMtrx( lace::vector3d<double>(0,0,1), 2*pi/5 ) );

  symplicator<3,double> aq;
  int n=10, m=10, k=10;
  aq(0) = lace::vector3d<double>( 4.940656650000,  0.000000000000,  0.000000000000);
  aq(1) = lace::vector3d<double>(-2.470328325482,  4.278734169998,  0.000000000000);
  aq(2) = lace::vector3d<double>( 0.000000000000,  0.000000000000,  5.448611970000);  

  periodic_cell<3,double> bounds( aq(0).T*n, aq(1).T*m, aq(2).T*k);

  aq(2) = rotrans<3,double>( aq(2).T/3,
			     RotMtrx( lace::vector3d<double>(0,0,1), -2*pi/3 ));

  aq(0).cell =  & bounds;
  aq(1).cell =  & bounds;
  aq(2).cell =  & bounds;
  
  //  aq(2).cell = & bounds;

  //  gen_geometry<2,double,std::string,char,std::char_traits<char>, symplicator<2,double> > G(ss);
  geometry<3,double,symplicator<3,double> > G(aq);


  G.add("Si", -0.157112881952,  4.278734169998,  1.816202173796);
  //  G.add("Si", -1.131347339416,  1.988719243588,  3.632406168616);
  //  G.add("Si",  1.338981003295,  2.290014957683,  5.448610155906);
  G.add("O",   1.454968024887,  1.161718853750,  1.135769455231);
  //G.add("O",   3.232354995551,  0.664595723026,  2.951973480961);
  //G.add("O",   2.774182731779,  2.452419625642,  4.768177419078);
  //G.add("O",  -1.015360326364,  3.117015308396,  2.496634859680);
  G.add("O",   0.762026709732,  3.614138455191,  0.680430912443);
  //G.add("O",   0.303854400382,  1.826314601529,  4.312838899931);

  
  lace::vector3d<double> a(0.0168403,2.85249,0);
  /* = G.coord(0) + G.coord(1) + G.coord(2);
  a /= 3.;
  a.z() = 0e0;
  */
  for (int i = 0; i<G.nat(); i++)
    G.coord(i) -= a;
  
  
  std::cout << a << "\n";

  geometry<0,double> GG;

  geometry<3,double,symplicator<3,double> >::iterator 
    i( qpp::index<3>(0, -1, -1, 2), qpp::index<3>( G.nat()-1, 4, 4, 6) );

  for ( i=i.begin(); i!=i.end(); i++ )
    {
      lace::vector3d<double> r = G.position(i);

      //std::cout << i << " " << r << " " << bounds.in_cell(r) << "\n";
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
  
  std::ofstream f("spc.xyz");
  write_xyz(f,GG);

}
