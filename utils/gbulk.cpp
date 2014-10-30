#include<geom/geom.hpp>
#include<io/geomio.hpp>
#include<io/qpparser.hpp>

typedef lace::vector3d<double> v3d;
#define DIM 3

int main(int argc, char **argv)
{ 
  bool gulp = false, xyz=false, cp2k=false;
  std::string fname="";
  
  for(int i=1; i<argc; i++)
    {       
      std::string opt = argv[i];
      if (opt=="-gulp" || opt=="-g")
	gulp = true;
      else if (opt=="-xyz" )
	xyz=true;
      else if (opt=="-cp2k")
	cp2k=true;
      else if (fname=="")
	fname = opt;
      else
	{
	  std::cerr << "Unrecognized option " << argv[i] << "\n";
	  exit(1);
	}
    }
  
  std::istream *f;
  if (fname == "")
    f = &std::cin;
  else
    f = new std::ifstream(fname.c_str());
  
  std::vector<qpp::qpp_object*> decls;
  qpp::qpp_read(*f,decls);
  
  qpp::geometry<DIM> * uc=NULL;
  qpp::periodic_cell<DIM> * cell=NULL;
  
  for (int i=0; i<decls.size(); i++)
    if (decls[i]->gettype() & qpp::qtype_geometry)
      uc = (qpp::geometry<DIM>*)decls[i];
    else if (decls[i]->gettype() & qpp::qtype_vectors)
      cell = (qpp::periodic_cell<DIM>*)decls[i];

  if (uc==NULL || cell==NULL)
    {
      std::cerr << "Either unit cell or lattice vectors are not defined\n";
      exit(1);
    }

  uc->cell = *cell;

  for (int i=0; i<uc->nat(); i++)
    //fixme kostyl!!
    // make it recognize "frac" option
    uc->coord(i) = uc->cell.frac2cart(uc->coord(i));

  int N,M,L;
  std::cerr << "Enter N,M,L numbers to replicate the unit cell NxMxL:\n";
  std::cin >> N >> M >> L;

  qpp::geometry<DIM> G;
  qpp::index<DIM> Ibgn, Iend(uc->nat()-1,N-1,M-1,L-1);
  qpp::geometry<DIM>::iterator I(Ibgn,Iend);
  
  for (I=I.begin(); I!=I.end(); I++)
    G.add(uc->atom(I),uc->position(I));

  G.cell(0) = (*cell)(0)*N;
  G.cell(1) = (*cell)(1)*M;
  G.cell(2) = (*cell)(2)*L;

  if (xyz)
    {
      std::ofstream xyzp("bulk.xyz");
      write_xyz(xyzp,G);
    }
  if (gulp)
    {
      std::ofstream ginp("bulk.gin");
      ginp << "vectors\n";
      for (int i=0; i<3; i++)
	ginp << G.cell(i)(0) << " " << G.cell(i)(1) << " " << G.cell(i)(2) << "\n";
      ginp << "cartesian 1\n";
      for (int i=0; i<G.nat(); i++)
	ginp << G.atom(i) << " core " << G.coord(i)(0)  << " " 
	     << G.coord(i)(1)  << " " << G.coord(i)(2) << "\n"
	     << G.atom(i) << " shel " << G.coord(i)(0)  << " " 
	     << G.coord(i)(1)  << " " << G.coord(i)(2) << "\n";
    }
  if (cp2k)
    {
      std::ofstream cinp("bulk.inp");
      cinp << "  &SUBSYS\n    &CELL\n";
      cinp << "      A " << G.cell(0)(0) << " " << G.cell(0)(1) << " " << G.cell(0)(2) << "\n";
      cinp << "      B " << G.cell(1)(0) << " " << G.cell(1)(1) << " " << G.cell(1)(2) << "\n";
      cinp << "      C " << G.cell(2)(0) << " " << G.cell(2)(1) << " " << G.cell(2)(2) << "\n";
      cinp << "    &END CELL\n    &COORD\n";
      for (int i=0; i<G.nat(); i++)
	cinp << "       " << G.atom(i) << " " << G.coord(i)(0) << " " 
	     << G.coord(i)(1) << " " << G.coord(i)(2) << "\n";
      cinp << "    &END COORD\n";

      G.build_type_table();
      for (int i=0; i<G.n_atom_types(); i++)
	cinp << "    &KIND " << G.atom_of_type(i) << "\n    &END KIND\n";
      cinp << "  &END SUBSYS\n";
    }
  
  G.cell.write(std::cout);
  G.write(std::cout);

}

