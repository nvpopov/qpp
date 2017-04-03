#include <iostream>
#include <symm/gcell.hpp>
#include <geom/lace3d.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/builders.hpp>
#include <io/geomio.hpp>
#include <io/strfun.hpp>

template <class REAL>
void user_console_group(qpp::generated_group<qpp::matrix3d<REAL> > & G)
{
  std::string reply;
  int ichoice;
  do{
    std::cout << "Select point group (currently: " << G.size() << " operations)" << std::endl;
    std::cout << "1) Add rotation axis" << std::endl << "2) Add mirror plane" << std::endl 
	      << "3) Add inversion" << std::endl << "4) Add rotation-reflection axis" << std::endl
	      << "5) Done" << std::endl;

    do {
      std::cin >> reply;
    } while (!qpp::s2t(reply,ichoice) );

    qpp::vector3d<REAL> v;
    int n;

    switch(ichoice)
      {
      case 1: std::cout << "Enter axis vector:" << std::endl;
	std::cin >> v.x() >> v.y() >> v.z();
	std::cout << "Enter axis order:" << std::endl;
	std::cin >> n; 
	G.generator(qpp::RotMtrx(v/norm(v), 2*qpp::pi/n));
	break;
      case 2: std::cout << "Enter vector normal to plane" << std::endl;	
	std::cin >> v.x() >> v.y() >> v.z();
	G.generator(qpp::Sigma(v/norm(v)));
	break;
      case 3: G.generator(qpp::matrix3d<REAL>(-1,0,0,0,-1,0,0,0,-1));
	break;
      case 4: std::cout << "Enter axis vector:" << std::endl;
	std::cin >> v.x() >> v.y() >> v.z();
	std::cout << "Enter axis order:" << std::endl;
	std::cin >> n;
	if (2*(n/2)==n)
	  G.generator(qpp::RotMtrx(v/norm(v), 2*qpp::pi/n)*qpp::Sigma(v/norm(v)));
	else
	  std::cout << "Must be even number" << std::endl;
	break;
      }

  } while(ichoice!=5);
}

int main(int argc, char **argv)
{
  
  std::string fname;
  if (argc > 1)
    fname = argv[1];
  std::istream *f;
  if (fname == "")
    f = &std::cin;
  else
    f = new std::ifstream(fname.c_str());

  qpp::xgeometry<3,double,qpp::periodic_cell<3,double> > orig(1,0,0);
  qpp::read_xyzq(*f,orig);
  
  std::string reply;
  std::cout << "Should I transform fractional coordinates to cartesian?" << std::endl;
  std::cin >> reply;
  
  bool y_n;
  qpp::s2t<bool>(reply,y_n);

  if (y_n)
    for (int i=0; i<orig.nat(); i++)
      orig.coord(i) = orig.cell->frac2cart( orig.coord(i));

  std::cout << "Center the unit cell at:" << std::endl << "1) point (provide x,y,z coordinates)" << std::endl 
	    << "2) atom" << std::endl << "3) between two atoms" << std::endl << "4) between three atoms" 
	    << std::endl;

  int ichoice;
  qpp::vector3d<double> rcntr;
  int at1,at2,at3;
  
  do {
    std::cin >> reply;
  } while (!qpp::s2t(reply,ichoice) );

  switch (ichoice)
    {
    case 1: std::cout << "Enter coordinates" << std::endl;
      std::cin >> rcntr(0) >> rcntr(1) >> rcntr(2);
      break;
    case 2: std::cout << "Number of atom:" << std::endl;
      std::cin >> at1;
      rcntr = orig.coord(at1-1);
      break;
    case 3: std::cout << "Numbers of atoms:" << std::endl;
      std::cin >> at1 >> at2;
      rcntr = 0.5*(orig.coord(at1-1) + orig.coord(at2-1));
      break;
    case 4: std::cout << "Numbers of atoms:" << std::endl;
      std::cin >> at1 >> at2 >> at3;
      rcntr = 0.33333333333*(orig.coord(at1-1) + orig.coord(at2-1) + orig.coord(at3-1));
      break;
    }

  for (int i=0; i<orig.nat(); i++)
    orig.coord(i) -= rcntr;

  qpp::write_xyz(std::cout,orig);  

  //orig.write(std::cout);

  qpp::generated_group<qpp::matrix3d<double> > G;

  user_console_group(G);

  G.write(std::cout);

  qpp::xgeometry<3,double,qpp::periodic_cell<3,double> > res(1,0,0);

  for (int i=0; i<orig.nat(); i++)
    for (int j=0; j<G.size(); j++)
      res.add(orig.atom(i), G[j]*orig.coord(i), {orig.xreal(0,i)/G.size()},{},{});

  qpp::write_xyz(std::cout,res);  

}

