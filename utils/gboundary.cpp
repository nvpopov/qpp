#include<geom/geom.hpp>
#include<io/geomio.hpp>
#include<io/qpparser.hpp>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <initializer_list>
#endif

#include <geom/shape.hpp>

#define DIM 3
typedef lace::vector3d<double> v3d;
typedef lace::vector3d<int> i3d;

bool twocells = false, should_adjust = false, should_integer = false;

double eps = 0.5;

std::string psgrph[12]={
  "",
  "-------------- BOUNDARY CONFIGURATION -----------------\n",
  "",
  "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\<------- Z12",
  " \\\\\\\\\\\\\\\\\\\\ GRAIN 1 \\\\\\\\\\\\\\\\\\\\",
  "  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\<----- Z11",
  "",
  "",
  "", 
  "  /////////////////////////////<----- Z21",
  " ////////// GRAIN 2 //////////",
  "/////////////////////////////<------- Z22"};

// -------------------------------------------------------------------------

int iround(double x)
{
  int s = x<0 ? -1 : 1;
  x *= s;
  return s*int(x+5e-1);
}

// -------------------------------------------------------------------------

void adj_thick(double & z, const qpp::periodic_cell<DIM> & cell, const i3d & a, const i3d & b, i3d & c)
{
  v3d aa = a(0)*cell(0)+a(1)*cell(1)+a(2)*cell(2);
  v3d bb = b(0)*cell(0)+b(1)*cell(1)+b(2)*cell(2);

  v3d n = aa%bb;
  n /= norm(n);

  v3d cfrac = cell.cart2frac(z*n);

  for (int i=0; i<3; i++)
    {
      c(i) = iround(cfrac(i));
      cfrac(i)=c(i);
    }
  
  //std::cerr << "before z= " << z;

  z = scal(n,cell.frac2cart(cfrac));

  //std::cerr << " after z= " << z << "\n";
}

// -------------------------------------------------------------------------

void usage()
{
  std::cout << "\nUSAGE: gboundary [OPTION] STRUCTURES.qpp\n";
  std::cout << "Construct a supercell with double grain boundary.\n";
  std::cout << "STRUCTURES.qpp must contain unit cell parameters and atoms\n";
  std::cout << "in qpp format. If STRUCTURES.qpp contains two separate unit cells\n";
  std::cout << "then phase boundary will be constructed. Output is to be found in\n";
  std::cout << "\"gb.qpp\" file.\n\n";
  std::cout << "  -gulp, -g        Create GULP input named \"gb.gin\". Make sure to\n";
  std::cout << "                   add necessary header and tail with GULP options\n";
  std::cout << "                   and potentials\n";
  std::cout << "  -cp2k            Create &SUBSYS section of CP2K input in \"gb.cp2k\"\n";
  std::cout << "  -xyz             Create \"gb.xyz\" file.\n";
  std::cout << "These options can be combined.\n";
}

// -------------------------------------------------------------------------

void center(qpp::geometry<DIM> *uc)
{
  std::cout << "Lattice vectors:\n";
  for (int i=0; i<3; i++)
    std::cout << boost::format("%10.6f %10.6f %10.6f\n") % uc->cell(i)(0) % uc->cell(i)(1) % uc->cell(i)(2);
  std::cout << "Unit cell:\n";
  for (int i=0; i<uc->nat(); i++)
    std::cout << boost::format("%3i %-2s %10.6f %10.6f %10.6f\n") % (i+1) % uc->atom(i) 
      % uc->coord(i)(0) % uc->coord(i)(1) % uc->coord(i)(2);
  std::cout << "Which atom should be in the coordinate origin (0=leave unit cell intact)?\n";
  int at;
  std::cin >> at;
  at--;
  if (at==-1)
    return;
  
  v3d r0 = uc -> coord(at);

  for (int i=0; i<uc->nat(); i++)
    uc->coord(i) -= r0;
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
  
//--------------------------------------------------------------------------

void write_cell(std::ostream & f, qpp::geometry<DIM> & G)
{
  f << "%BLOCK lattice_cart\n";
  f << G.cell(0)(0) << " " << G.cell(0)(1) << " " << G.cell(0)(2) << "\n";
  f << G.cell(1)(0) << " " << G.cell(1)(1) << " " << G.cell(1)(2) << "\n";
  f << G.cell(2)(0) << " " << G.cell(2)(1) << " " << G.cell(2)(2) << "\n";
  f << "%ENDBLOCK lattice_cart\n\n%BLOCK positions_abs\n";
  for (int i=0; i<G.nat(); i++)
    f << G.atom(i) << " " << G.coord(i)(0) << " " 
      << G.coord(i)(1) << " " << G.coord(i)(2) << "\n";
  f << "%ENDBLOCK positions_abs\n";
}
  
//- --------------------------------------------------

qpp::xtr_geometry<DIM> & grain(const qpp::geometry<3> & uc1, 
			       const i3d & ga, const i3d & gb,
			       double z1, double z2, 
			       const v3d & displ = 0e0, double h=3e0)
{
  qpp::geometry<DIM> uc(uc1);
  //  std::cerr << & uc.cell << " " << & uc.symm() << "\n";
  
  lace::vector3d<double> a = ga(0)*uc.cell(0) + ga(1)*uc.cell(1) + ga(2)*uc.cell(2);
  lace::vector3d<double> b = gb(0)*uc.cell(0) + gb(1)*uc.cell(1) + gb(2)*uc.cell(2);
  double aa = norm(a), bb = norm(b), cosf = scal(a,b)/(aa*bb);
  
  lace::vector3d<double> n3 = a%b, n2 = n3%a, n1;
  n3 /= norm(n3);
  n2 /= norm(n2);
  n1 = n2%n3;
  
  lace::matrix3d<double> R(n1,n2,n3);
  R = R.T();

  for (int i=0; i<uc.nat(); i++)
    uc.coord(i) = R*uc.coord(i);
  for (int i=0; i<3; i++)
    uc.cell(i) = R*uc.cell(i);  

  /*
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      std::cerr << i << " " << j << " " << R(i,0)*R(j,0)+R(i,1)*R(j,1)+R(i,2)*R(j,2) << "\n";
  */

  //std::cerr << R*a << R*b << "\n";

  v3d box2, box0;
  if (should_adjust)
    {
      i3d gc, gc1;
      double z = z2-z1, z11=z1;
      
      adj_thick(z,uc.cell,ga,gb,gc);

      adj_thick(z11,uc.cell,ga,gb,gc1);
      
      box2 = gc(0)*uc.cell(0) + gc(1)*uc.cell(1) + gc(2)*uc.cell(2) + v3d(0,0,2*eps);
      box0 = gc1(0)*uc.cell(0) + gc1(1)*uc.cell(1) + gc1(2)*uc.cell(2) + v3d(0,0, -eps);
    }
  else
    {
      box2 = v3d(0,0,z2-z1+2*eps);
      box0 = v3d(0,0,z1-eps);
    }
        
  qpp::qpp_shape_parallel<double> box(R*a, R*b, box2, box0);
  box.scale(1e0+1e-5);

  /*
  std::cerr << "Structural element:\n";
  write_xyz(std::cerr,uc);
  std::cerr << & uc.cell << " " << & uc.symm() << "\n";
  for (int i=0; i<3; i++)
    std::cerr << uc.cell(i) << uc.symm()(i) << "\n";
  */

  v3d c1 = box.fmin(uc.cell), c2 = box.fmax(uc.cell);

  //  std::cerr << c1 << c2 << "\n";

  int N1 = iround(c1(0)) - 3, N2 = iround(c2(0)) + 3,
    M1 = iround(c1(1)) - 3, M2 = iround(c2(1)) + 3,
    L1 = iround(c1(2)) - 3, L2 = iround(c2(2)) + 3;
  
  qpp::xtr_geometry<3> *G = new qpp::xtr_geometry<3>(0,0,1);

  /*
  v3d trans = uc.cell.cart2frac(v3d(0,0,z2-z1));
  int ti=(int)trans(0)+1,
    tj=(int)trans(1)+1,tk=(int)trans(2)+1;
  */

  for (int i=N1; i<=N2; i++)
    for (int j=M1; j<=M2; j++)
      for (int k=L1; k<=L2; k++)
	for (int at = 0; at<uc.nat(); at++)
	  if ( box.within( uc.position(qpp::index<3>(should_integer ? 0 : at,i,j,k)) ) )
	    {
	      v3d r = uc.position(qpp::index<3>(at,i,j,k));
	      bool srf = r(2)>z1+h && r(2)<z2-h;
	      //G->add(uc.atom(at),r+displ, {}, {}, {srf});
	      G->add(uc.atom(at),r+displ);
	      G->xtr_bool(0,G->nat()-1) = srf;
	      /*
	      if (box.within(r))
		G->add(uc.atom(at),r);
	      else
		G->add(uc.atom(at),uc.position(qpp::index<3>(at,i+ti,j+tj,k+tk)));	
	      */
	    }

  G->cell(0) = R*a;
  G->cell(1) = R*b;

  if (should_adjust)
    {
      i3d gc;
      double z = z1+z2;
      
      adj_thick(z,uc.cell,ga,gb,gc);
      
      v3d c = gc(0)*uc.cell(0) + gc(1)*uc.cell(1) + gc(2)*uc.cell(2) + 2*displ;
      
      G->cell(2) = c;
    }
  else
    {
      G->cell(2) = v3d(0,0,z1+z2) + 2*displ;
    }

  return *G;
}

// -----------------------------------------------------------------

int main(int argc, char **argv)
{ 
  bool gulp = false, xyz=false, cp2k=false, ocell=false;
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
      else if (opt=="-cell")
	ocell=true;
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
  
  qpp::geometry<DIM> *uc1=NULL, *uc2=NULL;
  qpp::periodic_cell<DIM> *cell1=NULL, *cell2=NULL;
  
  for (int i=0; i<decls.size(); i++)
    if (decls[i]->gettype() & qpp::qtype_geometry)
      {
	if (uc1==NULL)
	  uc1 = (qpp::geometry<DIM>*)decls[i];
	else
	  uc2 = (qpp::geometry<DIM>*)decls[i];
      }
    else if (decls[i]->gettype() & qpp::qtype_vectors)
      {
	if (cell1==NULL)
	  cell1 = (qpp::periodic_cell<DIM>*)decls[i];
	else
	  cell2 = (qpp::periodic_cell<DIM>*)decls[i];
      }
  
  if (uc1==NULL || cell1==NULL)
    {
      std::cerr << "Either unit cell or lattice vectors are not defined\n";
      exit(1);
    }

  uc1->cell = *cell1;

  for (int i=0; i<uc1->nat(); i++)
    //fixme kostyl!!
    // make it recognize "frac" option
    uc1->coord(i) = uc1->cell.frac2cart(uc1->coord(i));

  if (cell2==NULL)
    cell2 = cell1;
  if (uc2==NULL)
    uc2 = new qpp::geometry<DIM>(*uc1);
  else
    {
      std::cout << "Two unit cells in input - phase boundary construction presumed\n";
      twocells = true;
      uc2->cell = *cell2;
      for (int i=0; i<uc2->nat(); i++)
	uc2->coord(i) = uc2->cell.frac2cart(uc2->coord(i));
    }

  // std::cout << "Should I set coordinate origin at some atom position in unit\n";
  // std::cout << "cell? (Recommended for phase boundary)\nPlease answer y/n\n";
  // std::cin >> ynanswer;
  
  // if (ynanswer=="y" || ynanswer=="Y" || ynanswer=="yes" || ynanswer=="Yes")
  //   should_center = true;
  
  //  if (should_center)

  std::cout << "------------------- UNIT CELL 1 -------------------\n";
  center(uc1);
  if (twocells)
    {
      std::cout << "------------------- UNIT CELL 2 -------------------\n";
      center(uc2);
    }

  i3d a1,a2,b1,b2;

  psgrph[6] =   "   ----------- a1 ------------>";
  psgrph[8] =   "   ----------- a2 ------------>";
  for (int i=0; i<12; i++)
    std::cout << psgrph[i] << "\n";
  
  std::cout << "\nEnter coinciding vectors a1 -> a2 (six integers pls)\n";
  std::cin >> a1(0) >> a1(1) >> a1(2) >> a2(0) >> a2(1) >> a2(2);

  psgrph[6] =   "   ----------- b1 ------------>";
  psgrph[8] =   "   ----------- b2 ------------>";
  for (int i=0; i<12; i++)
    std::cout << psgrph[i] << "\n";
  
  std::cout << "Enter coinciding vectors b1 -> b2 (six integers pls)\n"; 
  std::cin >> b1(0) >> b1(1) >> b1(2) >> b2(0) >> b2(1) >> b2(2);

  psgrph[6] =   "       " + qpp::t2s(a1) + "x" + qpp::t2s(b1);
  psgrph[8] =   "       " + qpp::t2s(a2) + "x" + qpp::t2s(b2);

  std::cout << "Should I adjust thickness and position of grains to the nearest\n";
  std::cout << "integer numbers of unit cells? (Recommended for phase boundary)(y/n)\n";
  std::cin >> ynanswer;
  if (ynanswer=="y" || ynanswer=="Y" || ynanswer=="yes" || ynanswer=="Yes")
    should_adjust = true;

  double z11,z12,z21,z22;
  i3d c11,c12,c21,c22;

  for (int i=0; i<12; i++)
    std::cout << psgrph[i] << "\n";
  std::cout << "\nEnter Z11:\n";
  std::cin >> z11;
  if (should_adjust)
    adj_thick(z11,uc1->cell,a1,b1,c11);
    
  psgrph[5] += " = " + qpp::t2s(z11);

  for (int i=0; i<12; i++)
    std::cout << psgrph[i] << "\n";
  std::cout << "\nEnter Z12:\n";
  std::cin >> z12;
  if (should_adjust)
    adj_thick(z12,uc1->cell,a1,b1,c12);
    
  psgrph[3] += " = " + qpp::t2s(z12);

  for (int i=0; i<12; i++)
    std::cout << psgrph[i] << "\n";
  std::cout << "\nEnter Z21:\n";
  std::cin >> z21;
  if (should_adjust)
    adj_thick(z21,uc2->cell,a2,b2,c21);
    
  psgrph[9] += " = " + qpp::t2s(z21);

  for (int i=0; i<12; i++)
    std::cout << psgrph[i] << "\n";
  std::cout << "\nEnter Z22:\n";
  std::cin >> z22;
  if (should_adjust)
    adj_thick(z22,uc2->cell,a2,b2,c22);
    
  psgrph[11] += " = " + qpp::t2s(z22);

  for (int i=0; i<12; i++)
    std::cout << psgrph[i] << "\n";

  std::cout << "Should I build grains of integer number of unit cells (guarantees\n";
  std::cout << "stochiometry but not symmetry)?(y/n)\n";

  std::cin >> ynanswer;
  if (ynanswer=="y" || ynanswer=="Y" || ynanswer=="yes" || ynanswer=="Yes")
    should_integer = true;
  
  v3d displ;
  std::cout << "Enter the displacement vector of one GRAIN 1 with respect to GRAIN 2 (three real numbers)\n";  
  std::cin >> displ(0) >> displ(1) >> displ(2);

  double hl;
  std::cout << "Enter the thickness of modifiable layer (where geometry optimization\n";
  std::cout << "or pattern construction will be applied):\n";
  std::cin >> hl;

  qpp::xtr_geometry<DIM> *g1, *g2;

  g1 = &grain(*uc1, a1, b1, z11, z12, displ, hl);
  g2 = &grain(*uc2, a2, b2, z21, z22, v3d(0,0,0), hl);
  
  qpp::xtr_geometry<DIM> G(0,0,1);

  //  std::cerr << g1->nat() << g2->nat() << "\n";

  G.xbool_name(0) = "boundary";

  for (int i=0; i<g1->nat(); i++)
    {
      G.add(g1->atom(i), g1->coord(i));
      G.xtr_bool(0,G.nat()-1) = g1->xtr_bool(0,i);
    }
  for (int i=0; i<g2->nat(); i++)
    {
      G.add(g2->atom(i), g2->coord(i));
      G.xtr_bool(0,G.nat()-1) = g2->xtr_bool(0,i);
    }

  G.cell(0) = g1->cell(0);
  G.cell(1) = g1->cell(1);
  G.cell(2) = g1->cell(2) - g2->cell(2);
  
  G.build_type_table();
  G.update_types = true;
  G.ngbr.default_distance = 2*eps;
  G.ngbr.build_disttable();
  G.ngbr.build();
  G.add_dependent(&(G.ngbr));
  
  bool contin = true;
  while (contin)
    {
      contin = false;
      int i;
      for (i=0; i<G.nat(); i++)
	if ( G.ngbr.n(i)>0 )
	  {
	    contin = true;
	    break;
	  }
      if (contin)
	{
	  qpp::index<DIM> j = G.ngbr(i,0);
	  if ( G.position(i).z() < G.position(j).z())
	    G.erase(i);
	  else
	    G.erase(j);
	}
    }
  
  std::ofstream fqpp("gb.qpp");
  G.cell.write(fqpp);
  G.write(fqpp);
  fqpp.close();
  
  if (xyz)
    {
      std::stringstream s;
      v3d a = G.cell(0), b = G.cell(1), c = G.cell(2); 
      s << norm(a) << " " <<  norm(b) << " " <<  norm(c) << " " 
	<< std::acos(scal(b,c)/(norm(b)*norm(c)))*180/qpp::pi << " " 
	<< std::acos(scal(c,a)/(norm(c)*norm(a)))*180/qpp::pi << " " 
	<< std::acos(scal(a,b)/(norm(a)*norm(b)))*180/qpp::pi;
      
      G.setname(s.str());

      std::ofstream fxyz("gb.xyz");
      qpp::write_xyz(fxyz,G);
      fxyz.close();
    }

  if (gulp)
    {
      std::ofstream fgulp("gb.gin");
      write_gulp(fgulp,G);
      fgulp.close();
    }
  
  if (cp2k)
    {
      std::ofstream fcp2k("gb.cp2k");
      write_cp2k(fcp2k,G);
      fcp2k.close();
    }

  if (ocell)
    {
      std::ofstream fcell("gb.cell");
      write_cell(fcell,G);
      fcell.close();
    }

  std::cout << "Number of atoms:\n";
  std::vector<int> natt(G.n_atom_types(),0);
  for (int i=0; i<G.nat(); i++)
    natt[G.type_table(i)]++;
  for (int i=0; i<G.n_atom_types(); i++)
    std::cout << G.atom_of_type(i) << " " << natt[i] << "\n";
}
