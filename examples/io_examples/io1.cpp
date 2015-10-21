#include <io/qpparser.hpp>
#include <geom/geom.hpp>
#include <data/globals.hpp>
#include <iostream>
#include <fstream>
#include <io/qpparser.hpp>
#include <io/compile.hpp>

using namespace qpp;

void calc_dist(std::vector<double> & dist, std::vector<int> & deg, std::vector<double> & rm,
	       geometry<3,double> * geom, int N, int M, int L)
{
  for (int n=0; n<N; n++)
    for (int m=0; m<M; m++)
      for (int l=0; l<L; l++)
	{
	  geometry<3,double> shifted;
	  shifted.copy(*geom);

	  lace::vector3d<double> shift(1.*n/N, 1.*m/M, 1.*l/L);
	  for (int n=0; n<shifted.nat(); n++)
	    {
	      shifted.coord(n) += shift;
	      for (int i=0; i<3; i++)
		if (shifted.coord(n)(i) > 1)
		  shifted.coord(n)(i) -= 1;
	    }
	  //	  shifted.write(std::cout);

	  for (int i=0; i<shifted.nat(); i++)
	    for (int j=0; j<i; j++)
	      {
		lace::vector3d<double> r1,r2;
		r1 = shifted.coord(i);
		r2 = shifted.coord(j);
		dist.push_back( lace::norm( shifted.position(i) - shifted.position(j) ) );
		deg.push_back((N - (int)(N*std::abs(r2.x()-r1.x())))*
			      (M - (int)(M*std::abs(r2.y()-r1.y())))*
			      (L - (int)(L*std::abs(r2.z()-r1.z()))) );

		qpp_object * pat = global::root.find1(shifted.atom(i),qtype_atom | qtype_data_double);
		//pat->write(std::cout);
		double m1 = pat->parameter<double>("mass")->value();

		pat = global::root.find1(shifted.atom(j),qtype_atom | qtype_data_double);
		double m2 = pat->parameter<double>("mass")->value();
		rm.push_back(m1*m2/(m1+m2));
	      }
	}
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
    qpp_read_compile(*inp, decls, global::root);

    std::vector< geometry<3,double>*> geoms;

    for (int i=0; i<decls.size(); i++)
      if ( decls[i]->gettype() & qtype_geometry )
	geoms.push_back( (geometry<3,double>*)(decls[i]) );

    std::cout << "=============================================\n";
    /*
    for (int i=0; i<geoms.size(); i++)
      {
	//geoms[i]->write(std::cout);
	std::cout << geoms[i]->nat() << "\n\n";
	for (int j=0; j<geoms[i]->nat(); j++)
	  std::cout << geoms[i]->atom(j) << " " << geoms[i]->position(j) << "\n";
      }
    */

    int N,M,L;
    qpp_parameter<int> *p = global::root.parameter<int>("N");
    N = p->value();

    p = global::root.parameter<int>("M");
    M = p->value();

    p = global::root.parameter<int>("L");
    L = p->value();

    std::cout  << "N= " << N << " M= " << M << " L= " << L << "\n";

    global::root.write(std::cout);

    qpp_parameter<double> *pr = global::root.parameter<double>("delta");
    double delta = pr->value();

    pr = global::root.parameter<double>("R");
    double R = pr->value();

    pr = global::root.parameter<double>("w");
    double w = pr->value();

    for (int n=0; n<geoms.size(); n++)
      {
	std::vector<double> r12, rm;
	std::vector<int> deg;
	calc_dist(r12,deg,rm,geoms[n],N,M,L);

	double x = 0e0;
	std::string s = geoms[n]->name()+".dat";
	std::ofstream rdf(s.c_str());
	while(x<=R)
	  {
	    double y=0e0;
	    for (int i=0; i<r12.size(); i++)
	      y += std::sqrt(rm[i])*exp(-(x-r12[i])*(x-r12[i])*rm[i]/(2*w*w))/
		(sqrt(2*pi)*deg[i]*r12[i]*r12[i]);
	    
	    rdf << x << " " << y << std::endl;
	    x += delta;
	  }
      }
}
