#include <iostream>
#include <geom/geom.hpp>
#include <boost/format.hpp>
#include <io/geomio.hpp>
#include <fstream>

// -------------- Type table & neighbours table for simple molecule ---------------------

bool compat(const qpp::index<3> & at1, const qpp::index<3> & at2)
{
  return at1.atom() > at2.atom();
}

int main()
{
  qpp::geometry<3> uc,g;

  std::ifstream f("a-quartz.uc");
  read_xyz(f,uc);

  uc.cell.write(std::cout);
  
  qpp::geometry<3>::iterator I(qpp::index<3>(0,-1,-1,-1), qpp::index<3>(uc.nat()-1, 1, 1, 1));

  for (I=I.begin(); I!=I.end(); I++)
    {
      std::string at = uc.atom(I);
      if ( I!=qpp::index<3>(I.atom()) )
	{
	  if (at=="Si")
	    at = "S";
	  else
	    at = "F";
	}
      g.add(at, uc.position(I));
      // std::cout << g.nat() << " " << at << " " << I << "\n"; 
    }

  g.cell(0) = uc.cell(0)*3;
  g.cell(1) = uc.cell(1)*3;
  g.cell(2) = uc.cell(2)*3;

  std::ofstream ff("a-qx3.xyz"), t1("ngbr1"), t2("ngbr2");

  write_xyz(ff,g);

  g.ngbr.default_distance = 1.7;
  g.build_type_table();
  g.ngbr.build_disttable();

  for (int i=g.nat()/1; i>50; i-=3) g.shadow(i)=true;
  g.ngbr.build();

  g.add_dependent(&g.ngbr);


  for (int i=g.nat()-1; i>0; i-=4) g.erase(i);  

  for (int i=10; i<g.nat(); i+=10) g.insert(i, g.atom(i/2), g.coord(i/2)*.5);  
  //  g.erase(192);

  for (int i=11; i<g.nat(); i+=17) g.add(g.atom(i/2), g.coord(i/2)*.5);  

  for (int i=0; i<g.nat(); i++)
    {
      t1 << i << " " << g.atom(i);
      std::vector<qpp::index<3> > nn;
      for (int j=0; j<g.ngbr.n(i); j++)
	nn.push_back(g.ngbr(i,j));
      std::sort(nn.begin(),nn.end(),compat);
      for (int j=0; j<nn.size(); j++)
	t1 << " " << nn[j];
      t1 << "\n";
    }

  g.ngbr.build();

  for (int i=0; i<g.nat(); i++)
    {
      t2 << i << " " << g.atom(i);
      std::vector<qpp::index<3> > nn;
      for (int j=0; j<g.ngbr.n(i); j++)
	nn.push_back(g.ngbr(i,j));
      std::sort(nn.begin(),nn.end(),compat);
      for (int j=0; j<nn.size(); j++)
	t2 << " " << nn[j];
      t2 << "\n";
    }
  /*
  uc.ngbr.default_distance = 1.7;
  uc.build_type_table();
  uc.ngbr.build_disttable();
  */
  /*
  g.ngbr.set_distance("Carbon","Carbon",1.8);
  g.ngbr.set_distance("Carbon","Oxygen",1.6);
  g.ngbr.set_distance("Coronium","Newtonium",8);
  g.ngbr.set_distance("Oxygen","Nitrogen",1.53);
  g.ngbr.set_distance("Carbon","Nitrogen",1.35);
  
  g.add("Carbon",       -1.676283510,      0.000000000,      1.911126199);
  g.add("Oxygen",       -1.753146399,      1.141923181,      1.514919538);
  g.add("Oxygen",       -1.604477009,     -1.066694960,      1.079653080);
  g.add("Hydrogen",       -1.628395866,     -0.711301327,      0.174843873);
  g.add("Coronium",       0,5,0);
  g.add("Carbon",       -1.647886655,     -0.422100383,      3.375898205);
  g.add("Hydrogen",       -2.475776531,     -1.122649475,      3.538396631);
  g.add("Coronium",       0,0,0);
  g.add("Newtonium",      0,0,0);
  g.add("Hydrogen",       -2.565816675,      1.205870339,      4.156284306);
  g.add("Hydrogen",       -0.956315270,      1.314146931,      4.156322052);
  g.add("Hydrogen",       -0.733613146,     -1.005425023,      3.538407817);
  g.insert(6, "Nitrogen",       -1.721124037,      0.666230718,      4.332560746);

  g.shadow(0) = true;
  g.shadow(1) = true;
  //  g.shadow(4) = true;

  //  g.build_ngbr_table();
  */

  /*
  std::cout << " --- Atomic types: ---\n";

  for (int i=0; i<uc.n_atom_types(); i++)
    std::cout << i << " = " << uc.atom_of_type(i) << "\n";

  std::cout << "\n --- Neighbouring distances table: ---\n";

  std::cout << "     ";
  for (int i=0; i<uc.n_atom_types(); i++)
    std::cout << boost::format("%10i") % i;
  std::cout << "\n";

  for (int i=0; i<uc.n_atom_types(); i++)
    {
      std::cout << boost::format("%5i") % i;
      for (int j=0; j<uc.n_atom_types(); j++)
	std::cout << boost::format("%10.5f") % uc.ngbr.distance(i,j);
      std::cout << "\n";
    }

  for (int i=0; i<uc.size(); i++)
    std::cout << uc.type_table(i) << " " << uc.coord(i).x() << " " << uc.coord(i).y() << " " << uc.coord(i).z() << "\n";
  */
  /*
  g._grain_setup();
  std::cout << g.grainsize << "\n";
  std::cout << g.Rmin << g.Rmax << g.grain_nx << " " << g.grain_ny << " " << g.grain_nz << "\n";

  g._graining();

  std::cout << "alive\n";

  int l=0;
  for (int i=0; i < g.grain_nx; i++ )
    for (int j=0; j < g.grain_ny; j++ )
      for (int k=0; k < g.grain_nz; k++ )
	for (int a=0; a< g.grains(i,j,k).size(); a++)
	  std::cout << i << " " << j << " " << k << " " << (g.grains(i,j,k)[a]) << "\n";
  */
  /*
  uc.ngbr.build();

  for (int i=0; i<uc.size(); i++)
    for (int j=0; j<uc.ngbr.n(i); j++)
      {
	qpp::index<3> k = uc.ngbr.table(i,j);
	std::cout << uc.atom(i) << " " << i << " " << uc.atom(k) << " " << k << " " <<  norm(uc.position(i) - uc.position(k)) << "\n";
      }
  */
  /*
  std::cout << "Iterator work:\n";
  qpp::geometry<3>::iterator i(g);
  for (i=i.begin(); i!=i.end(); i++)
    std::cout << i << " ";
  */
}

