#include <geom/zpt.hpp>
#include <iostream>


#define DIM 0

double good   = -6.8;
double bad    = -6.0;
double awfull = -5.1;

double coef = 0.7;

int main(int argc, char **argv)
{
  try{
    std::istream * inp;
    
    if (argc > 1)
      inp = new std::ifstream(argv[1]);
    else
      inp = & std::cin;
    
    //inp = new std::ifstream("2.qpp");

    std::vector<qpp::qpp_object*> decls;
    qpp::qpp_read(*inp,decls);

    std::vector<qpp::geometry<DIM> *> geom;
    std::vector<qpp::xtr_geometry<DIM> *> xgeom;
    std::vector<qpp::periodic_cell<DIM> *> cell;
    std::vector<qpp::zpattern<DIM>* > zpt;

    int nat;

    for (int i=0; i<decls.size(); i++)
      if (decls[i]->gettype() & qpp::qtype_geometry)
	geom.push_back((qpp::geometry<DIM>*)decls[i]);
      else if (decls[i]->gettype() & qpp::qtype_vectors)
	cell.push_back((qpp::periodic_cell<DIM>*)decls[i]);
      else if (decls[i]-> category() == "zpattern")
	zpt.push_back(qpp::decl2zpt<DIM>((qpp::qpp_declaration*)decls[i]));

    for (int i=0; i<geom.size(); i++)
      if (geom[i]->gettype() & qpp::qtype_xgeometry)
	xgeom.push_back((qpp::xtr_geometry<DIM>*)geom[i]);
      else
	xgeom.push_back(NULL);

    if (DIM==0)
      for (int i=0; i<geom.size(); i++)
	geom[i] -> cell = * new qpp::periodic_cell<0>;
    else
      for (int i=0; i<geom.size(); i++)
	geom[i] -> cell = *(cell[i]);
    
    for (int i=0; i<zpt.size(); i++)
      {

	zpt[i] -> write(std::cout);
	std::ofstream xyz(zpt[i]->name() + ".xyz");

	for (int j=0; j<geom.size(); j++)
	  {
	    std::vector<double> en(geom[j]->nat(),0e0);

	    if (xgeom[j]!=NULL)
	      for (int k=0; k<xgeom[j]->nat(); k++)
		en[k] = xgeom[j] -> xtr_real(0,k);

	    // Energy correction to remedy Tersoff potentials 
	    /*
	    lace::vector3d<double> r0(0e0);
	    
	    for (int k=0; k<geom[j]->nat(); k++)
	      r0 += geom[j] -> position(i);

	    r0 /= geom[j]->nat();

	    double dist0,dist1;
	    for (int k=0; k<geom[j]->nat(); k++)
	      {
		double dist = norm(geom[j]->position(k)-r0);
		if (k==0)
		  {
		    dist0 = dist1 = dist;
		  }
		if (dist0>dist)
		  dist0 = dist;
		if (dist1 < dist)
		  dist1 = dist;
	      }
	    
	    for (int k=0; k<geom[j]->nat(); k++)
	      {
		en[k] -= coef * (norm(geom[j]->position(k)-r0)-dist0)/(dist1-dist0);
		xgeom[j] -> xtr_real(0,k) = en[k];
	      }
	    */
	    
	    zpt[i] -> init(*(geom[j]));

	    std::vector<std::vector<int> > matches;
	    std::vector<std::vector<double> > vals;
	    std::vector<double> cost;

	    zpt[i] -> search(matches,vals,cost);
	    
	    for (int k=0; k<matches.size(); k++)
	      //if (cost[k]<-32.)
	      {
		std::stringstream ss;
		
		ss << cost[k];
		
		for (int l=0; l<vals[k].size(); l++)
		  ss << " " << vals[k][l];
		
		for (int l=0; l< matches[k].size(); l++)
		  ss << " " << matches[k][l];
		
		std::cout << ss.str() << "\n";
	    
		qpp::geometry<DIM> g;
		g.copy(*geom[j]);

		// Colorize		
		for (int l=0; l<g.nat(); l++)
		  if (en[l] < good)
		    g.atom(l) = "N";
		  else if (en[l] > bad)
		    g.atom(l) = "O";
		
		// Show pattern
		for (int l=0; l< matches[k].size(); l++)
		  g.atom(matches[k][l]) = "B";
		
		g.setname(ss.str());
		
		qpp::write_xyz(xyz,g);
	      }

	    matches.clear();
	    vals.clear();
	    cost.clear();
	  }

	xyz.close();
      }    
  }
  catch (qpp::qpp_exception & e)
    {
      std::cout << e.what() << "\n";
      exit(1);
    }
}

