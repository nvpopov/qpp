#include<geom/geom.hpp>
#include<io/geomio.hpp>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <initializer_list>
#endif

#include <geom/shape.hpp>
#include <geom/zpt.hpp>

#define DIM 3
#define REAL double

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

    qpp::geometry<DIM> * geom=NULL;
    qpp::xtr_geometry<DIM> * xgeom=NULL;
    qpp::periodic_cell<DIM> * cell;
    std::vector<qpp::zpattern<DIM>* > zpt;

    int nat;
    bool * noapply;

    for (int i=0; i<decls.size(); i++)
      if (decls[i]->gettype() & qpp::qtype_geometry)
	geom = (qpp::geometry<DIM>*)decls[i];
    //else if (decls[i]->gettype() & qpp::qtype_xgeometry)
    //	xgeom = (qpp::xtr_geometry<DIM>*)decls[i];
      else if (decls[i]->gettype() & qpp::qtype_vectors)
	cell = (qpp::periodic_cell<DIM>*)decls[i];
      else if (decls[i]-> category() == "zpattern")
	zpt.push_back(qpp::decl2zpt<DIM,REAL,qpp::periodic_cell<DIM,REAL> >((qpp::qpp_declaration*)decls[i]));

    if (geom->gettype()& qpp::qtype_xgeometry)
      xgeom = (qpp::xtr_geometry<DIM>*)geom;

    /*

    std::cout << geom << " " << (geom==NULL) << 
      " " << xgeom <<  " " << (xgeom==NULL) << "\n";

    std::cout << "type: " << geom->gettype() << " " << (geom->gettype()& qpp::qtype_xgeometry) << "\n";
    std::cout << "type: " << xgeom->gettype()<< "\n";
    */

    if (geom!=NULL)
      nat = geom -> nat();
    else if (xgeom!=NULL)
      nat = xgeom -> nat();
    noapply = new bool[nat];

    if (xgeom==NULL)
      for (int i=0; i<nat; i++)
	noapply[i] = false;
    else
      {
	std::cout << "xtra geometry\n";
	for (int i=0; i<nat; i++)
	  noapply[i] = xgeom -> xtr_bool(0,i);
      }

    if (DIM==0)
      cell = new qpp::periodic_cell<DIM>;
    cell -> write(std::cout);
    if (xgeom!=NULL)
      xgeom -> write(std::cout);
    
    geom -> write(std::cout);
    for (int i=0; i<zpt.size(); i++)
      zpt[i] -> write(std::cout);
    

    geom -> cell = *cell;

    std::cout << "before init\n";
    bool contin = true;
    for (int i=0; i<zpt.size(); i++)
      zpt[i] -> init(*geom);
    qpp::init_rand();
    qpp::random_integer_lister lst,lst1;

    std::ofstream f("build.xyz");

    std::cout << "DEPTH\n";
    for (int i=0; i<zpt.size(); i++)
      std::cout << i << " " << zpt[i]->depth() << "\n";
    
    while(contin)
      {
	contin = false;
	lst.set(0,zpt.size()-1);
	for (int i=lst.begin(); !lst.end(); i=lst.next())
	  {
	    std::cout << "------------------------ i=" << i << "---------------------------\n";
	    if ( zpt[i]->apply(lst1))
	      {
		contin = true;

		std::stringstream s;
		s << "pattern " << i << " = ";
		for (int k=0; k<zpt[i]->n_points(); k++)
		  s << " " << zpt[i]->bound(k)+1;
		
		geom->setname(s.str());
		
		qpp::write_xyz(f,*geom);
		//		qpp::write_xyz(std::cout,*geom);
	      }
	  }
      }

    geom->setname("");

    std::ofstream gin("grown.gin");
    gin << "vectors\n";
    for (int i=0; i<3; i++)
      gin << geom->cell(i)(0) << " " << geom->cell(i)(1) << " " << geom->cell(i)(2) << "\n";
    gin << "cartesian 1\n";
    for (int i=0; i<geom->nat(); i++)
      gin << geom->atom(i) << " core " << geom->coord(i)(0)  << " " 
	  << geom->coord(i)(1)  << " " << geom->coord(i)(2) << "\n"
	  << geom->atom(i) << " shel " << geom->coord(i)(0)  << " " 
	  << geom->coord(i)(1)  << " " << geom->coord(i)(2) << "\n";

    std::ofstream qp("grown.qpp");
    geom->cell.write(qp);
    geom->write(qp);

    std::vector<int> natt(geom->n_atom_types(),0);
    for (int i=0; i<geom->nat(); i++)
      natt[geom->type_table(i)]++;
    for (int i=0; i<geom->n_atom_types(); i++)
      std::cout << geom->atom_of_type(i) << " " << natt[i] << "\n";
    
  }
  catch (qpp::qpp_exception & e)
    {
      std::cout << e.what() << "\n";
      exit(1);
    }
}

