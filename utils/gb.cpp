#include<geom/geom.hpp>
#include<io/geomio.hpp>
#include<io/qpparser.hpp>
#include <initializer_list>
#include <geom/shape.hpp>

#define DIM 3
typedef lace::vector3d<double> v3d;
typedef lace::vector3d<int> i3d;

const  double eps = 0.3;

bool adjust=false;

int iround(double x)
{
  int s = x<0 ? -1 : 1;
  x *= s;
  return s*int(x+5e-1);
}

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
  
  std::cerr << "before z= " << z;

  z = scal(n,cell.frac2cart(cfrac));

  std::cerr << " after z= " << z << "\n";
}

qpp::xtr_geometry<DIM> & grain(const qpp::geometry<3> & uc1, 
			       const i3d & ga, const i3d & gb,
			       double z1, double z2, 
			       const v3d & shift = 0e0, double h=3e0)
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

  /*
  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      std::cerr << i << " " << j << " " << R(i,0)*R(j,0)+R(i,1)*R(j,1)+R(i,2)*R(j,2) << "\n";
  */

  //std::cerr << R*a << R*b << "\n";


  qpp::qpp_shape_parallel<double> box(R*a, R*b, v3d(0,0,z2-z1+eps),v3d(0,0,z1-eps));
  //box.scale(1e0-1e-5);

  for (int i=0; i<uc.nat(); i++)
    uc.coord(i) = R*uc.coord(i);
  for (int i=0; i<3; i++)
    uc.cell(i) = R*uc.cell(i);  

  /*
  std::cerr << "Structural element:\n";
  write_xyz(std::cerr,uc);
  std::cerr << & uc.cell << " " << & uc.symm() << "\n";
  for (int i=0; i<3; i++)
    std::cerr << uc.cell(i) << uc.symm()(i) << "\n";
  */

  v3d c1 = box.fmin(uc.cell), c2 = box.fmax(uc.cell);

  //  std::cerr << c1 << c2 << "\n";

  int N1 = (int)c1(0) - 1, N2 = (int)c2(0) + 1,
    M1 = (int)c1(1) - 1, M2 = (int)c2(1) + 1,
    L1 = (int)c1(2) - 1, L2 = (int)c2(2) + 1;
  
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
	  if ( box.within( uc.position(qpp::index<3>(at,i,j,k)) ) )
	    {
	      v3d r = uc.position(qpp::index<3>(at,i,j,k));
	      bool srf = r(2)>z1+h && r(2)<z2-h;
	      //std::cerr<< at << " " << r << " " << srf << "\n";
	      G->add(uc.atom(at),r+shift, {}, {}, {srf});
	      /*
	      if (box.within(r))
		G->add(uc.atom(at),r);
	      else
		G->add(uc.atom(at),uc.position(qpp::index<3>(at,i+ti,j+tj,k+tk)));	
	      */
	    }

  G->cell(0) = R*a;
  G->cell(1) = R*b;

  if (adjust)
    {
      i3d gc;
      double z = z1+z2;
      
      adj_thick(z,uc.cell,ga,gb,gc);
      
      v3d c = gc(0)*uc.cell(0) + gc(1)*uc.cell(1) + gc(2)*uc.cell(2) + 2*shift;
      
      G->cell(2) = c;
    }
  else
    {
      G->cell(2) = v3d(0,0,z1+z2) + 2*shift;
    }

  return *G;
}

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
    f = new std::ifstream(fname);
  
  std::vector<qpp::qpp_object*> decls;
  qpp::qpp_read(*f,decls);
  
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
      std::cerr << "Two cells\n";
      uc2->cell = *cell2;
      for (int i=0; i<uc2->nat(); i++)
	uc2->coord(i) = uc2->cell.frac2cart(uc2->coord(i));
    }
  
  i3d a1,a2,b1,b2;

  std::cerr << "Enter coinciding vectors a1 -> a2\n";
  std::cin >> a1(0) >> a1(1) >> a1(2) >> a2(0) >> a2(1) >> a2(2);

  std::cerr << "Enter coinciding vectors b1 -> b2\n";
  std::cin >> b1(0) >> b1(1) >> b1(2) >> b2(0) >> b2(1) >> b2(2);

  double  h,d, hl;

  std::cerr << "Enter grain thickness and the distance between grains\n";
  std::cin >> h >> d;

  std::string sadjust;
  std::cerr << "Should I adjust them to the nearest integer numbers of unit cells?(y/n)\n";
  std::cin >> sadjust;

  if (sadjust=="y" || sadjust=="Y" || sadjust=="yes" || sadjust=="Yes")
    adjust = true;

  v3d displ;
  std::cerr << "Enter the displacement vector of one grain with respect to another\n";  
  std::cin >> displ(0) >> displ(1) >> displ(2);

  std::cerr << "Enter the thickness of modifiable layer:\n";
  std::cin >> hl;

  double z11 =  d/2, z12 =  h + d/2;
  double z22 = -d/2, z21 = -h - d/2;

  i3d c11,c12,c21,c22;

  if (adjust)
    {
      adj_thick(z11,uc1->cell,a1,b1,c11);
      adj_thick(z12,uc1->cell,a1,b1,c12);
      adj_thick(z21,uc2->cell,a2,b2,c21);
      adj_thick(z22,uc2->cell,a2,b2,c22);
    }

  // int io=0;
  // while (uc1->atom(io)!="Zr") io++;
  // v3d r0 = uc1->coord(io);
  // for (int i=0; i<uc1->nat(); i++)
  //   uc1->coord(i) = uc1->coord(i)-r0;

  // io=0;
  // while (uc2->atom(io)!="Zr") io++;
  // r0 = uc2->coord(io);

  // for (int i=0; i<uc2->nat(); i++)
  //   uc2->coord(i) = uc2->coord(i)-r0;
  
  qpp::xtr_geometry<3> * g1 = &grain(*uc1, a1, b1, z11,  z12, v3d(0,0,0), hl);

  //debug
  std::cerr << "grain1\n";

  qpp::xtr_geometry<3> * g2 = &grain(*uc2, a2, b2, z21, z22, displ, hl);
  
  //debug
  std::cerr << "grain2\n";

  g1->cell(2) = g1->cell(2) - g2->cell(2);
  
  for (int i=0; i<g2->nat(); i++)
    {
      //std::cerr << i << "\n";
      g1->add(g2->atom(i), g2->coord(i), {}, {}, {g2->xtr_bool(0,i)});
    }

  //debug
  std::cerr << "Merged\n";

  //  qpp::write_xyz(std::cout,*g1);

  g1 -> build_type_table();
  g1 -> update_types = true;
  g1 -> ngbr.default_distance = 1.0;
  g1 -> ngbr.build_disttable();
  g1 -> ngbr.build();

  g1 -> add_dependent(&(g1->ngbr));

  bool contin = true;
  while (contin)
    {
      contin = false;
      int i;
      for (i=0; i<g1 -> nat(); i++)
	if ( g1->ngbr.n(i)>0 )
	  {
	    contin = true;
	    break;
	  }
      if (contin)
	{
	  qpp::index<DIM> j = g1->ngbr(i,0);
	  if ( g1->position(i).z() < g1->position(j).z())
	    g1->erase(i);
	  else
	    g1->erase(j);
	}
    }

  std::ofstream f1("gb.qpp"),f2("gb.xyz"),f3("coord");


  f3 << "vectors\n";
  for (int i=0; i<3; i++)
    f3 << g1->cell(i)(0) << " " << g1->cell(i)(1) << " " << g1->cell(i)(2) << "\n";
  f3 << "cartesian 1\n";
  for (int i=0; i<g1->nat(); i++)
    f3 << g1->atom(i) << " core " << g1->coord(i)(0)  << " " 
       << g1->coord(i)(1)  << " " << g1->coord(i)(2) << "\n"
       << g1->atom(i) << " shel " << g1->coord(i)(0)  << " " 
       << g1->coord(i)(1)  << " " << g1->coord(i)(2) << "\n";

  g1->cell.write(f1);
  g1->write(f1);

  /*
  for (int i=0; i<g1->nat(); i++)
    if (g1->xtr_bool(0,i))
      g1->atom(i) = "Cl";
  */

  std::stringstream s;
  v3d a = g1->cell(0), b = g1->cell(1), c = g1->cell(2); 
  s << norm(a) << " " <<  norm(b) << " " <<  norm(c) << " " 
    << std::acos(scal(b,c)/(norm(b)*norm(c)))*180/qpp::pi << " " 
    << std::acos(scal(c,a)/(norm(c)*norm(a)))*180/qpp::pi << " " 
    << std::acos(scal(a,b)/(norm(a)*norm(b)))*180/qpp::pi;

  g1 -> setname(s.str());

  qpp::write_xyz(f2,*g1);

  f1.close();
  f2.close();
  f3.close();

  g1 -> build_type_table();
  std::vector<int> natt(g1->n_atom_types(),0);
  for (int i=0; i<g1->nat(); i++)
    natt[g1->type_table(i)]++;
  for (int i=0; i<g1->n_atom_types(); i++)
    std::cout << g1->atom_of_type(i) << " " << natt[i] << "\n";

}
