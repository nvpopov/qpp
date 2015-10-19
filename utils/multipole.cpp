#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <iostream>
#include <fstream>
#include <io/qpparser.hpp>
#include <data/globals.hpp>
#include <io/compile.hpp>
//#include <symm/symm.hpp>

template<int DIM,class REAL>
void mmm(qpp::qpp_object * geom)
{
  qpp::xtr_geometry<DIM,REAL> * g = (qpp::xtr_geometry<DIM,REAL> *)geom;
  if (!g->has_charges())
    return;
  REAL q=0e0;
  lace::vector3d<REAL> D=0e0;
  lace::matrix3d<REAL> Q=0e0;
  REAL O[3][3][3];

  for (int i=0; i<3; i++)
    for (int j=0; j<3; j++)
      for (int k=0; k<3; k++)
	O[i][j][k]=0e0;

  std::cout << "===================================" << std::endl;
  g->write(std::cout);
  
  for (int i=0; i<g->nat(); i++)
    {
      lace::vector3d<REAL> r = g->position(i);
      q += g->charge(i);
      D += g->charge(i)*r;
      for (int j=0; j<3; j++)
	for (int k=0; k<3; k++)
	  Q(j,k) += g->charge(i)*(3*r(j)*r(k) - (j==k ? r.norm2() : 0e0));

      for (int j=0; j<3; j++)
	for (int k=0; k<3; k++)
	  for (int l=0; l<3; l++)
	    O[j][k][l] +=  g->charge(i)*(5*r(j)*r(k)*r(l)-
		r.norm2()*(j==k?r(l):0e0 + j==l?r(k):0e0 + k==l?r(j):0e0));
    }

  std::cout << "q = " << q << std::endl;
  std::cout << "D = " << D << std::endl;
  //std::cout << "Q = " << Q << std::endl;
  for (int i=0; i<3; i++)
    for (int j=0; j<=i; j++)
      std::cout << "Q " << i << " " << j << " " << Q(i,j) << std::endl;
  for (int i=0; i<3; i++)
    for (int j=0; j<=i; j++)
      for (int k=0; k<=j; k++)
	std::cout << "O " << i << " " << j << " " << k << " " << O[i][j][k] << std::endl;

  for (int n=0; n<g->nat(); n++)
    {
      lace::vector3d<REAL> r = g->position(n);
      std::cout << g->atom(n) << " core " << r.x() << " " << r.y() << " " << r.z() << " "<< g->charge(n) << "\n";
    }
}

template<class REAL>
void mm(qpp::qpp_object * geom)
{
  if (geom->gettype() & qpp::qtype_dim0)
    mmm<0,REAL>(geom);
  else if (geom->gettype() & qpp::qtype_dim1)
    mmm<1,REAL>(geom);
  else if (geom->gettype() & qpp::qtype_dim2)
    mmm<2,REAL>(geom);
  else if (geom->gettype() & qpp::qtype_dim3)
    mmm<3,REAL>(geom);
}

int main(int argc, char **argv)
{
  //try{
    std::istream * inp;
    if (argc > 1)
      inp = new std::ifstream(argv[1]);
    else
      inp = & std::cin;

    std::vector<qpp::qpp_object*> decls;

    /*
    qpp::qpp_read(*inp,decls,&qpp::global::root);

    for (int i=0; i<decls.size(); i++)
      qpp::global::root.add(*qpp::qpp_compile(decls[i]));
    */
    qpp::qpp_read_compile(*inp, decls, qpp::global::root);

    for (int i=0; i<qpp::global::root.n_nested(); i++)
      if (qpp::global::root.nested(i)->gettype() & qpp::qtype_xgeometry)
	{
	  if (qpp::global::root.nested(i)->gettype() & qpp::qtype_data_double)
	    mm<double>(qpp::global::root.nested(i));
	  else if (qpp::global::root.nested(i)->gettype() & qpp::qtype_data_float)
	    mm<float>(qpp::global::root.nested(i));
	}

    //symmetry_group<lace::matrix3d<double>,float> G = shoenflis<float>::S_n(6);
    /*
  }
  catch (qpp::qpp_exception & e)
    {
      std::cerr << "QPP exception:\n";
      std::cerr << e.what() << "\n";
    }
    */
}

