#include<geom/geom.hpp>
#include<io/geomio.hpp>
#include<io/qpparser.hpp>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <initializer_list>
#endif

#include <geom/shape.hpp>
#include <algorithm>

#define DIM 3
typedef lace::vector3d<double> v3d;
typedef lace::vector3d<int> i3d;

double z11,z12,z21,z22;

struct tosort
{
  int at;
  double z;

  tosort(int _at, double _z)
  {
    at=_at; z=_z;
  }
};

double dist(double z)
{
  return std::min( std::abs(z-z11), std::min( std::abs(z-z12), 
					      std::min( std::abs(z-z21), std::abs(z-z22))));
}

bool mycmp(const tosort & s1, const tosort & s2)
{
  return dist(s1.z) < dist(s2.z);
}

void usage()
{
  std::cout << "\nUSAGE: stochiom [OPTION] STRUCTURE.qpp\n";
  std::cout << "Makes the structure stochiometric.\n";
  std::cout << "STRUCTURES.qpp must contain unit cell parameters and atoms\n";
  std::cout << "in qpp format. Output is to be found in \"stoch.qpp\" file.\n\n";
  std::cout << "";
  std::cout << "  -gulp, -g        Create GULP input named \"stoch.gin\". Make sure to\n";
  std::cout << "                   add necessary header and tail with GULP options\n";
  std::cout << "                   and potentials\n";
  std::cout << "  -cp2k            Create &SUBSYS section of CP2K input in \"stoch.cp2k\"\n";
  std::cout << "  -xyz             Create \"stoch.xyz\" file.\n";
  std::cout << "These options can be combined.\n";
}
// -------------------------------------------------------------------------

void write_gulp(std::ostream & f, const qpp::geometry<DIM> & G)
{
  f << "vectors\n";
  for (int i=0; i<3; i++)
    f << G.cell(i)(0) << " " << G.cell(i)(1) << " " << G.cell(i)(2) << "\n";
  f << "cartesian 1\n";
  for (int i=0; i<G.nat(); i++)
    f << G.atom(i) << " core " << G.coord(i)(0)  << " " 
      << G.coord(i)(1)  << " " << G.coord(i)(2) << "\n"
      << G.atom(i) << " shel " << G.coord(i)(0)  << " " 
      << G.coord(i)(1)  << " " << G.coord(i)(2) << "\n";
}

//--------------------------------------------------------------------------

void write_cp2k(std::ostream & f, qpp::geometry<DIM> & G)
{
  f << "  &SUBSYS\n    &CELL\n";
  f << "      A " << G.cell(0)(0) << " " << G.cell(0)(1) << " " << G.cell(0)(2) << "\n";
  f << "      B " << G.cell(1)(0) << " " << G.cell(1)(1) << " " << G.cell(1)(2) << "\n";
  f << "      C " << G.cell(2)(0) << " " << G.cell(2)(1) << " " << G.cell(2)(2) << "\n";
  f << "    &END CELL\n    &COORD\n";
  for (int i=0; i<G.nat(); i++)
    f << "       " << G.atom(i) << " " << G.coord(i)(0) << " " 
      << G.coord(i)(1) << " " << G.coord(i)(2) << "\n";
  f << "    &END COORD\n";
  
  G.build_type_table();
  for (int i=0; i<G.n_atom_types(); i++)
    f << "    &KIND " << G.atom_of_type(i) << "\n    &END KIND\n";
  f << "  &END SUBSYS\n";
}
  
// -----------------------------------------------------------------

int main(int argc, char **argv)
{
  bool gulp = false, xyz=false, cp2k=false;
  std::string fname, ynanswer;
  
  if (argc < 2)
    {
      usage();
      exit(0);
    }
  
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
  
  std::ifstream f(fname.c_str());
  
  std::vector<qpp::qpp_object*> decls;
  qpp::qpp_read(f,decls);
  
  qpp::geometry<DIM> *G=NULL;
  qpp::periodic_cell<DIM> *cell=NULL;
  
  for (int i=0; i<decls.size(); i++)
    if (decls[i]->gettype() & qpp::qtype_geometry)
      G = (qpp::geometry<DIM>*)decls[i];
    else if (decls[i]->gettype() & qpp::qtype_vectors)
      cell = (qpp::periodic_cell<DIM>*)decls[i];
  
  if (G==NULL || cell==NULL)
    {
      std::cerr << "Either unit cell or lattice vectors are not defined\n";
      exit(1);
    }

  G->cell = *cell;

  G->build_type_table();
  G->update_types = true;

  std::vector<int> natt(G->n_atom_types(),0), stoch(G->n_atom_types()), todel(G->n_atom_types());
  for (int i=0; i<G->nat(); i++)
    natt[G->type_table(i)]++;

  std::cout << "Number of atoms:\n";
  for (int i=0; i<G->n_atom_types(); i++)
    std::cout << G->atom_of_type(i) << " " << natt[i] << "\n";
  
  int nmin = * std::min_element(natt.begin(),natt.end());
  for (int i=0; i<G->n_atom_types(); i++)
    stoch[i] = natt[i]/nmin;

  std::cout << "Assuming stochiometry\n";
  for (int i=0; i<G->n_atom_types(); i++)
    std::cout << G->atom_of_type(i) << "_" << stoch[i] << " ";
  std::cout << "\nIs it correct?(y/n)";

  std::cin >> ynanswer;
  if (!(ynanswer=="y" || ynanswer=="Y" || ynanswer=="yes" || ynanswer=="Yes"))
    {
      std::cout << "Enter structural formula:\n";
      for (int i=0; i<G->n_atom_types(); i++)
	{
	  std::cout << G->atom_of_type(i) << ":";
	  std::cin >> stoch[i];
	}
    }

  int NUC = natt[0]/stoch[0];
  for (int i=1; i<G->n_atom_types(); i++)
    {
      int NUC1 = natt[i]/stoch[i];
      if (NUC>NUC1)
	NUC = NUC1;
    }
  
  for (int i=0; i<G->n_atom_types(); i++)
    todel[i] = natt[i] - NUC*stoch[i];

  std::cout << "To delete:\n";
  for (int i=0; i<G->n_atom_types(); i++)
    std::cout << G->atom_of_type(i) << " " << todel[i] << "\n";

  z11 = z12 = -1;
  z21 = z22 =  1;

  for (int i=0; i<G->nat(); i++)
    {
      double z = G->coord(i).z();
      if (z11<0 || (z>0 && z11>z))
	z11 = z;
      if (z12<z)
	z12 = z;
      if (z21>0 || (z<0 && z21<z))
	z21 = z;
      if (z22>z)
	z22 = z;
    }

  //std::cout << z22 << " " << z21 << " " << z11 << " " << z12 << "\n";

  std::vector< std::vector<tosort> > satt(G->n_atom_types());
  for (int i=0; i<G->nat(); i++)
    satt[G->type(i)].push_back(tosort(i,G->coord(i).z()));

  for (int i=0; i<G->n_atom_types(); i++)
    std::sort(satt[i].begin(),satt[i].end(),mycmp);

  
  for (int i=0; i<G->n_atom_types(); i++)
    {
      std::cout << G->atom_of_type(i)<< "\n";
      for (int j=0; j<satt[i].size(); j++)
	std::cout << G->atom(satt[i][j].at) << " " << satt[i][j].at << " " << satt[i][j].z << " " << dist(satt[i][j].z) << "\n";
    }


  std::vector<int> atdel;

  for (int i=0; i<G->n_atom_types(); i++)
    for (int j=0; j<todel[i]; j++)
      atdel.push_back(satt[i][j].at);

  std::sort(atdel.begin(), atdel.end());

  
  for (int i=0; i<atdel.size(); i++)
    std::cout << atdel[i] << " ";
  std::cout << "\n";
  
  for (int i=atdel.size()-1; i>=0; i--)
    G->erase(atdel[i]);

  
  std::ofstream fqpp("stoch.qpp");
  G->cell.write(fqpp);
  G->write(fqpp);
  fqpp.close();
  
  if (xyz)
    {
      std::stringstream s;
      v3d a = G->cell(0), b = G->cell(1), c = G->cell(2); 
      s << norm(a) << " " <<  norm(b) << " " <<  norm(c) << " " 
	<< std::acos(scal(b,c)/(norm(b)*norm(c)))*180/qpp::pi << " " 
	<< std::acos(scal(c,a)/(norm(c)*norm(a)))*180/qpp::pi << " " 
	<< std::acos(scal(a,b)/(norm(a)*norm(b)))*180/qpp::pi;
      
      G->setname(s.str());

      std::ofstream fxyz("stoch.xyz");
      qpp::write_xyz(fxyz,*G);
      fxyz.close();
    }

  if (gulp)
    {
      std::ofstream fgulp("stoch.gin");
      write_gulp(fgulp,*G);
      fgulp.close();
    }
  
  if (cp2k)
    {
      std::ofstream fcp2k("stoch.cp2k");
      write_cp2k(fcp2k,*G);
      fcp2k.close();
    }

  for (int i=0; i<G->n_atom_types(); i++)
    natt[i] = 0;

  for (int i=0; i<G->nat(); i++)
    natt[G->type_table(i)]++;
  std::cout << "Number of atoms:\n";
  for (int i=0; i<G->n_atom_types(); i++)
    std::cout << G->atom_of_type(i) << " " << natt[i] << "\n";
}



