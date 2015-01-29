#include <zpt/zpt.hpp>
#include <io/geomio.hpp>
#include <fstream>

typedef qpp::zpattern<0,double> zpt;

int main()
{
  qpp::geometry<0> G;

  double a = 1.6;
  double atet = 109.47122063449;
  double rmin = .9*a, rmax = 1.1*a, amin = atet*.95, amax = atet*1.05;

  G.add("Si",0,0,0);
  G.add("Si",a,0,0);
  G.add("Si",4*a/3,2*a*sqrt(2.)/3,0);

  G.write(std::cout);


  std::vector<zpt*> patterns;
  int current;
  zpt* self;

  // ---------------------------------------------------
  current = patterns.size();
  patterns.push_back(new zpt);
  self = patterns[current];

  patterns[current] -> add_point(zpt::zpt_point("A","Si"),zpt::zsearch);
  patterns[current] -> add_point(zpt::zpt_point("B","Si"),zpt::zsearch);
  patterns[current] -> add_point(zpt::zpt_point("C","Si"),zpt::zsearch);
  patterns[current] -> add_point(zpt::zpt_point("D","Si"),zpt::zinsert);
  patterns[current] -> add_point(zpt::zpt_point("X","Si"),zpt::zavoid);

  patterns[current] -> add_relation(* new zpt::bond_relation("A","B", rmin, rmax, *self));
  patterns[current] -> add_relation(* new zpt::bond_relation("A","C", rmin, rmax, *self));
  patterns[current] -> add_relation(* new zpt::angle_relation("B","A","C", amin, amax, *self));

  patterns[current] -> add_relation(* new zpt::bond_relation("A","D", 
				     *new zpt::linear_dependence(a,*self), *self));
  patterns[current] -> add_relation(* new zpt::angle_relation("B","A","D", 
				     *new zpt::linear_dependence(atet,*self), *self));
  patterns[current] -> add_relation(* new zpt::dyhedral_relation("C","B","A","D", 
				     *new zpt::linear_dependence(120.0,*self), *self));
  patterns[current] -> add_relation(* new zpt::bond_relation("D","X", 0e0, .7*a, *self));
  

  // ---------------------------------------------------
  current = patterns.size();
  patterns.push_back(new zpt);
  self = patterns[current];

  patterns[current] -> add_point(zpt::zpt_point("A","Si"),zpt::zsearch);
  patterns[current] -> add_point(zpt::zpt_point("B","Si"),zpt::zsearch);
  patterns[current] -> add_point(zpt::zpt_point("C","Si"),zpt::zsearch);
  patterns[current] -> add_point(zpt::zpt_point("D","Si"),zpt::zinsert);
  patterns[current] -> add_point(zpt::zpt_point("X","Si"),zpt::zavoid);

  patterns[current] -> add_relation(* new zpt::bond_relation("A","B", rmin, rmax, *self));
  patterns[current] -> add_relation(* new zpt::bond_relation("A","C", rmin, rmax, *self));
  patterns[current] -> add_relation(* new zpt::angle_relation("B","A","C", amin, amax, *self));

  patterns[current] -> add_relation(* new zpt::bond_relation("A","D", 
				     *new zpt::linear_dependence(a,*self), *self));
  patterns[current] -> add_relation(* new zpt::angle_relation("B","A","D", 
				     *new zpt::linear_dependence(atet,*self), *self));
  patterns[current] -> add_relation(* new zpt::dyhedral_relation("C","B","A","D", 
				     *new zpt::linear_dependence(120.0,*self), *self));
  patterns[current] -> add_relation(* new zpt::bond_relation("D","X", 0e0, .7*a, *self));
  


  // ---------------------------------------------------
  current = patterns.size();
  patterns.push_back(new zpt);
  self = patterns[current];

  patterns[current] -> add_point(zpt::zpt_point("A","Si"),zpt::zsearch);
  patterns[current] -> add_point(zpt::zpt_point("B","Si"),zpt::zsearch);
  patterns[current] -> add_point(zpt::zpt_point("C","Si"),zpt::zsearch);
  patterns[current] -> add_point(zpt::zpt_point("D","Si"),zpt::zinsert);
  patterns[current] -> add_point(zpt::zpt_point("X","Si"),zpt::zavoid);

  patterns[current] -> add_relation(* new zpt::bond_relation("A","B", rmin, rmax, *self));
  patterns[current] -> add_relation(* new zpt::bond_relation("B","C", rmin, rmax, *self));
  patterns[current] -> add_relation(* new zpt::angle_relation("A","B","C", amin, amax, *self));

  patterns[current] -> add_relation(* new zpt::bond_relation("C","D", 
				     *new zpt::linear_dependence(a,*self), *self));
  patterns[current] -> add_relation(* new zpt::angle_relation("B","C","D", 
				     *new zpt::linear_dependence(atet,*self), *self));
  patterns[current] -> add_relation(* new zpt::dyhedral_relation("A","B","C","D", 
				     *new zpt::linear_dependence(180.0,*self), *self));
  patterns[current] -> add_relation(* new zpt::bond_relation("D","X", 0e0, .7*a, *self));
  

  bool contin = true;
  for (int i=0; i<patterns.size(); i++)
    patterns[i] -> init(G);
  qpp::init_rand();
  qpp::random_integer_lister lst,lst1;

  std::ofstream f("si.xyz");

  while(contin)
    {
      contin = false;
      lst.set(0,patterns.size()-1);
      for (int i=lst.begin(); !lst.end(); i=lst.next())
	{
	  std::cout << "------------------------ i=" << i << "---------------------------\n";
	  if ( patterns[i]->apply(lst1))
	    {
	      contin = true;
	      qpp::write_xyz(f,G);
	      qpp::write_xyz(std::cout,G);
	    }
	}
    }
}

