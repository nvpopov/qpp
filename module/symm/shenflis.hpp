#ifndef _QPP_SHENFLIS_H
#define _QPP_SHENFLIS_H

#include <symm/symm.hpp>
#include <lace/lace3d.hpp>
#include <physconst.hpp>
#include <sstream>

namespace qpp{

  template<class VALTYPE>
  class shoenflis
  {
  public:
    typedef lace::vector3d<double> vec3d;
    typedef lace::matrix3d<double> mat3d;
    
    class point_group : public symmetry_group<mat3d,VALTYPE>
    {
      //using symmetry_group<mat3d,VALTYPE>::n_irrep;
      //using symmetry_group<mat3d,VALTYPE>::chi;
      //using symmetry_group<mat3d,VALTYPE>::dim_irrep;

      std::vector<std::string> irrep_name;

      typedef symmetry_group<mat3d,VALTYPE> basetype;

      void name_irreps()
      {
	double chitol = 1e-3;
	int first = 1;
	if (N_improper>N_proper)
	  first = basetype::index(lace::RotMtrx(vec3d(0,0,1),-2*pi/N_improper)*lace::Sigma(vec3d(0,0,1)));

	std::cout << "first=" << first << "\n";

	irrep_name.resize(basetype::n_irrep());
	for (int i=0; i<basetype::n_irrep(); i++)
	  {
	    std::stringstream ss;
	    if (basetype::dim_irrep(i)==1)
	      {
		//std::cout << "chi(i,first)=" << basetype::chi(i,first) << "\n";
		if (lace::abs(basetype::chi(i,basetype::class_of(first))-1.0)<chitol)
		  ss << "A";
		else 
		  ss << "B";
	      }
	    else if (basetype::dim_irrep(i)==2)
	      {
		ss << "E";
	      }
	    else if (basetype::dim_irrep(i)==3)
	      {
		ss << "T";
	      }
	    irrep_name[i] = ss.str();
	  }
      }

    public:
      int N_proper;
      int N_improper;

      std::string irrep_notion(int irrep)
      {
	return irrep_name[irrep];
      }
      
      virtual void build_all()
      {
	symmetry_group<mat3d,VALTYPE>::build_all();
	name_irreps();
      }
    };

    static point_group & S_n(int N)
    {
      assert( N%2==0 && "S group must have even order");
      point_group * G = new point_group;
      G -> N_proper = N/2;
      G -> N_improper = N;
      for (int i = 1; i<N; i++)
	{
	  std::stringstream ss;
	  ss << "S_" << N;
	  if (i>1) ss << "^" << i;
	  if (i%2==1)
	    G -> add(lace::RotMtrx(vec3d(0e0,0e0,1e0), -2*i*pi/N)*lace::Sigma(vec3d(0,0,1e0)),ss.str());
	  else
	    G -> add(lace::RotMtrx(vec3d(0e0,0e0,1e0), -2*i*pi/N),ss.str());
	}
      return *G;
    }    
    
    static point_group & C_n(int N)
    {
      point_group * G = new point_group;
      G -> N_proper = N;
      G -> N_improper = 0;

      for (int i = 1; i<N; i++)
	{
	  std::stringstream ss;
	  ss << "C_" << N;
	  if (i>1) ss << "^" << i;
	  G -> add(lace::RotMtrx(vec3d(0e0,0e0,1e0), -2*i*pi/N),ss.str());
	}
      return *G;
    }

    static point_group & C_nv(int N)
    {
      point_group * G = & C_n(N);
      if (N==2)
	{
	  G -> add(lace::Sigma(vec3d(0,1,0)), "\\sigma_x");
	  G -> add(lace::Sigma(vec3d(1,0,0)), "\\sigma_y");
	}
      else if (N==4)
	{
	  G -> add(lace::Sigma(vec3d(0,1,0)), "\\sigma_x");
	  G -> add(lace::Sigma(vec3d(1,0,0)), "\\sigma_y");
	  G -> add(lace::Sigma(vec3d(1,-1,0)),"\\sigma_{x+y}");
	  G -> add(lace::Sigma(vec3d(1,1,0)), "\\sigma_{x-y}");
	}
      else if (N==6)
	{
	  double s3 = std::sqrt(3e0);
	  G -> add(lace::Sigma(vec3d(0,1,0)),   "\\sigma_x");
  	  G -> add(lace::Sigma(vec3d(1,0,0)),   "\\sigma_y");
  	  G -> add(lace::Sigma(vec3d(-1,s3,0)), "\\sigma_{30}");
  	  G -> add(lace::Sigma(vec3d(-s3,1,0)), "\\sigma_{60}");
  	  G -> add(lace::Sigma(vec3d(s3,1,0)),  "\\sigma_{120}");
  	  G -> add(lace::Sigma(vec3d(1,s3,0)),  "\\sigma_{150}");
	}
      else
	{
	  for (int i = 0; i<N; i++)
	    {
	      vec3d n=0e0;
	      n.x() = std::cos(2*i*pi/N);
	      n.y() = std::sin(2*i*pi/N);
	      std::stringstream ss;
	      ss << "\\sigma_" << i;
	      G -> add(lace::Sigma(n), ss.str());
	    }
	}
      return *G;
    }

    static point_group & D_n(int N)
    {
      point_group * G = & C_n(N);
      if (N==2)
	{
	  G -> add(lace::RotMtrx(vec3d(1,0,0),pi), "U_{x}");
	  G -> add(lace::RotMtrx(vec3d(0,1,0),pi), "U_{y}");
	}
      else if (N==4)
	{
	  G -> add(lace::RotMtrx(vec3d(1,0,0),pi), "U_{x}");
	  G -> add(lace::RotMtrx(vec3d(0,1,0),pi), "U_{y}");
	  G -> add(lace::RotMtrx(vec3d(1,1,0),pi), "U_{x+y}");
	  G -> add(lace::RotMtrx(vec3d(1,-1,0),pi),"U_{x-y}");
	}
      else if (N==6)
	{
	  double s3 = std::sqrt(3e0);
	  G -> add(lace::RotMtrx(vec3d(1,0,0),pi),  "U_{x}");
  	  G -> add(lace::RotMtrx(vec3d(0,1,0),pi),  "U_{y}");
  	  G -> add(lace::RotMtrx(vec3d(s3,1,0),pi), "U_{30}");
  	  G -> add(lace::RotMtrx(vec3d(1,s3,0),pi), "U_{60}");
  	  G -> add(lace::RotMtrx(vec3d(-1,s3,0),pi),"U_{120}");
  	  G -> add(lace::RotMtrx(vec3d(-s3,1,0),pi),"U_{150}");
	}
      else
	{
	  for (int i = 0; i<N; i++)
	    {
	      vec3d n=0e0;
	      n.x() = std::cos(2*i*pi/N);
	      n.y() = std::sin(2*i*pi/N);
	      std::stringstream ss;
	      ss << "U_" << i;
	      G -> add(lace::RotMtrx(n,pi), ss.str());
	    }
	}
      return *G;
    }

    static point_group & D_nh(int N)
    {
      point_group * G = & D_n(N);
      mat3d I = -1e0;
      
      G -> N_improper = N;

      if (N==2)
	{
	  G -> add(I,"I");
	  G -> add(lace::Sigma(vec3d(1,0,0)),"\\sigma_x");
	  G -> add(lace::Sigma(vec3d(0,1,0)),"\\sigma_y");
	  G -> add(lace::Sigma(vec3d(0,0,1)),"\\sigma_z");
	}
      else if (N==3)
	{
	  G -> add(lace::Sigma(vec3d(0,0,1)),"\\sigma_z");
	  G -> add(lace::RotMtrx(vec3d(0,0,1), 2*pi/3)*lace::Sigma(vec3d(0,0,1)),"S_3");
	  G -> add(lace::RotMtrx(vec3d(0,0,1), 4*pi/3)*lace::Sigma(vec3d(0,0,1)),"S_3^2");
	  G -> add(lace::Sigma(vec3d(0,1,0)),"\\sigma_0");
	  double s3 = std::sqrt(3e0);
	  G -> add(lace::Sigma(vec3d(s3,1,0)),"\\sigma_1");
	  G -> add(lace::Sigma(vec3d(s3,-1,0)),"\\sigma_2");
	}
      else if (N==4)
	{
	  G -> add(I,"I");
	  G -> add(lace::Sigma(vec3d(1,0,0)),"\\sigma_x");
	  G -> add(lace::Sigma(vec3d(0,1,0)),"\\sigma_y");
	  G -> add(lace::Sigma(vec3d(0,0,1)),"\\sigma_z");
	  G -> add(lace::Sigma(vec3d(1,1,0)),"\\sigma_{x+y}");
	  G -> add(lace::Sigma(vec3d(1,-1,0)),"\\sigma_{x-y}");
	  G -> add(lace::RotMtrx(vec3d(0,0,1),  pi/2)*lace::Sigma(vec3d(0,0,1)),"S_{4}");
	  G -> add(lace::RotMtrx(vec3d(0,0,1),3*pi/2)*lace::Sigma(vec3d(0,0,1)),"S_{4}^3");	}
      
      return *G;
    }

    static point_group & D_nd(int N)
    {
      point_group * G = & D_n(N);
      G -> N_improper = 2*N;
      for (int i=0; i<N; i++)
	{
	  std::stringstream ss;
	  ss << "\\sigma_{d" << i << "}";
	  VALTYPE phi = (i+.5)*pi/N;
	  G -> add(lace::Sigma(vec3d(std::sin(phi),-std::cos(phi),0)),ss.str());
	}
      for (int i=0; i<2*N; i++)
	{
	  std::stringstream ss;
	  ss << "S_" << 2*N;
	  if (i>1) ss << "^" << i;
	  if (i%2==1)
	    G -> add(lace::RotMtrx(vec3d(0e0,0e0,1e0), -2*i*pi/(2*N))*lace::Sigma(vec3d(0,0,1e0)),ss.str());
	}
      
      //  G -> build_multab();
      //for (int g=0; g<G->size(); g++)
      //for (int h=0; h<G->size(); h++)
      //  std::cout << G->notion(g) << "*" << G->notion(h) << "=" << G->notion(G->multab(g,h)) << "\n";
      return *G;
      
    }

    static point_group & T()
    {
      point_group * G = new point_group;
      G -> N_proper = 2;
      G -> N_improper = 0;
      G -> add(lace::RotMtrx(vec3d(1,0,0),pi),"C_{2x}");
      G -> add(lace::RotMtrx(vec3d(0,1,0),pi),"C_{2y}");
      G -> add(lace::RotMtrx(vec3d(0,0,1),pi),"C_{2z}");
      G -> add(lace::RotMtrx(vec3d(1,1, 1),2*pi/3),"C_{3(111)}");
      G -> add(lace::RotMtrx(vec3d(1,-1,-1),2*pi/3),"C_{3(1\\overline{11})}");
      G -> add(lace::RotMtrx(vec3d(-1,1,-1),2*pi/3),"C_{3(\\overline{1}1\\overline{1})}");
      G -> add(lace::RotMtrx(vec3d(-1,-1,1),2*pi/3),"C_{3(\\overline{11}1)}");
      G -> add(lace::RotMtrx(vec3d(1,1, 1),4*pi/3),"C_{3(111)}^2");
      G -> add(lace::RotMtrx(vec3d(1,-1,-1),4*pi/3),"C_{3(1\\overline{11})}^2");
      G -> add(lace::RotMtrx(vec3d(-1,1,-1),4*pi/3),"C_{3(\\overline{1}1\\overline{1})}^2");
      G -> add(lace::RotMtrx(vec3d(-1,-1,1),4*pi/3),"C_{3(\\overline{11}1)}^2");
      return * G;
    }

    static point_group & O()
    {
      point_group *G = new point_group;
      G -> N_proper = 4;
      G -> N_improper = 0;
      G -> add(lace::RotMtrx(vec3d(1,0,0),  pi/2),"C_{4x}");
      G -> add(lace::RotMtrx(vec3d(1,0,0),  pi),  "C_{4x}^2");
      G -> add(lace::RotMtrx(vec3d(1,0,0),3*pi/2),"C_{4x}^3");
      G -> add(lace::RotMtrx(vec3d(0,1,0),  pi/2),"C_{4y}");
      G -> add(lace::RotMtrx(vec3d(0,1,0),  pi),  "C_{4y}^2");
      G -> add(lace::RotMtrx(vec3d(0,1,0),3*pi/2),"C_{4y}^3");
      G -> add(lace::RotMtrx(vec3d(0,0,1),  pi/2),"C_{4z}");
      G -> add(lace::RotMtrx(vec3d(0,0,1),  pi),  "C_{4z}^2");
      G -> add(lace::RotMtrx(vec3d(0,0,1),3*pi/2),"C_{4z}^3");
      G -> add(lace::RotMtrx(vec3d(1, 1,0),pi),"C_{2,x+y}");
      G -> add(lace::RotMtrx(vec3d(1,-1,0),pi),"C_{2,x-y}");
      G -> add(lace::RotMtrx(vec3d(1,0, 1),pi),"C_{2,x+z}");
      G -> add(lace::RotMtrx(vec3d(1,0,-1),pi),"C_{2,x-z}");
      G -> add(lace::RotMtrx(vec3d(0,1, 1),pi),"C_{2,y+z}");
      G -> add(lace::RotMtrx(vec3d(0,1,-1),pi),"C_{2,y-z}");
  
      G -> add(lace::RotMtrx(vec3d(1,1, 1),2*pi/3),"C_{3{<}111{>}}");
      G -> add(lace::RotMtrx(vec3d(1,1,-1),2*pi/3),"C_{3{<}11\\overline{1}{>}}");
      G -> add(lace::RotMtrx(vec3d(1,-1,1),2*pi/3),"C_{3{<}1\\overline{1}1{>}}");
      G -> add(lace::RotMtrx(vec3d(-1,1,1),2*pi/3),"C_{3{<}\\overline{1}11{>}}");
      G -> add(lace::RotMtrx(vec3d(1,1, 1),4*pi/3),"C_{3{<}111{>}}^2");
      G -> add(lace::RotMtrx(vec3d(1,1,-1),4*pi/3),"C_{3{<}11\\overline{1}{>}}^2");
      G -> add(lace::RotMtrx(vec3d(1,-1,1),4*pi/3),"C_{3{<}1\\overline{1}1{>}}^2");
      G -> add(lace::RotMtrx(vec3d(-1,1,1),4*pi/3),"C_{3{<}\\overline{1}11{>}}^2");

      return * G;
    }

    static point_group & Td()
    {
      point_group * G = & T(); 
      G -> N_improper = 4;

      G -> add(lace::Sigma(vec3d( 1, 1, 0)),"\\sigma_{x+y}");
      G -> add(lace::Sigma(vec3d( 1,-1, 0)),"\\sigma_{x-y}");
      G -> add(lace::Sigma(vec3d( 1, 0, 1)),"\\sigma_{x+z}");
      G -> add(lace::Sigma(vec3d( 1, 0,-1)),"\\sigma_{x-z}");
      G -> add(lace::Sigma(vec3d( 0, 1, 1)),"\\sigma_{y+z}");
      G -> add(lace::Sigma(vec3d( 0, 1,-1)),"\\sigma_{y-z}");
      G -> add(lace::RotMtrx(vec3d(1,0,0),  pi/2)*lace::Sigma(vec3d(1,0,0)),"S_{4x}");
      G -> add(lace::RotMtrx(vec3d(1,0,0),3*pi/2)*lace::Sigma(vec3d(1,0,0)),"S_{4x}^3");
      G -> add(lace::RotMtrx(vec3d(0,1,0),  pi/2)*lace::Sigma(vec3d(0,1,0)),"S_{4y}");
      G -> add(lace::RotMtrx(vec3d(0,1,0),3*pi/2)*lace::Sigma(vec3d(0,1,0)),"S_{4y}^3");
      G -> add(lace::RotMtrx(vec3d(0,0,1),  pi/2)*lace::Sigma(vec3d(0,0,1)),"S_{4z}");
      G -> add(lace::RotMtrx(vec3d(0,0,1),3*pi/2)*lace::Sigma(vec3d(0,0,1)),"S_{4z}^3");
      
      return *G;
    }

    static point_group & Oh()
    {
      point_group * G = & O();
      G -> N_improper = 4;

      mat3d I = -1e0;

      G -> add(I,"I");

      G -> add(lace::Sigma(vec3d(1,0,0)),"\\sigma_x");
      G -> add(lace::Sigma(vec3d(0,1,0)),"\\sigma_y");
      G -> add(lace::Sigma(vec3d(0,0,1)),"\\sigma_z");
      
      G -> add(lace::Sigma(vec3d(1, 1, 0)),"\\sigma_{x+y}");
      G -> add(lace::Sigma(vec3d(1,-1, 0)),"\\sigma_{x-y}");
      G -> add(lace::Sigma(vec3d(1, 0, 1)),"\\sigma_{x+z}");
      G -> add(lace::Sigma(vec3d(1, 0,-1)),"\\sigma_{x-z}");
      G -> add(lace::Sigma(vec3d(0, 1, 1)),"\\sigma_{y+z}");
      G -> add(lace::Sigma(vec3d(0, 1,-1)),"\\sigma_{y-z}");

      G -> add(lace::RotMtrx(vec3d(1,0,0),  pi/2)*lace::Sigma(vec3d(1,0,0)),"S_{4x}");
      G -> add(lace::RotMtrx(vec3d(1,0,0),3*pi/2)*lace::Sigma(vec3d(1,0,0)),"S_{4x}^3");
      G -> add(lace::RotMtrx(vec3d(0,1,0),  pi/2)*lace::Sigma(vec3d(0,1,0)),"S_{4y}");
      G -> add(lace::RotMtrx(vec3d(0,1,0),3*pi/2)*lace::Sigma(vec3d(0,1,0)),"S_{4y}^3");
      G -> add(lace::RotMtrx(vec3d(0,0,1),  pi/2)*lace::Sigma(vec3d(0,0,1)),"S_{4z}");
      G -> add(lace::RotMtrx(vec3d(0,0,1),3*pi/2)*lace::Sigma(vec3d(0,0,1)),"S_{4z}^3");

      G -> add(lace::RotMtrx(vec3d(1, 1, 1),  pi/3)*lace::Sigma(vec3d(1, 1, 1)),  "S_{6<111>}");
      G -> add(lace::RotMtrx(vec3d(1, 1, 1),5*pi/3)*lace::Sigma(vec3d(1, 1, 1)),  "S_{6<111>}^5");
      G -> add(lace::RotMtrx(vec3d(1, 1,-1),  pi/3)*lace::Sigma(vec3d(1, 1,-1)),  "S_{6<11\\overline{1}>}");
      G -> add(lace::RotMtrx(vec3d(1, 1,-1),5*pi/3)*lace::Sigma(vec3d(1, 1,-1)),  "S_{6<11\\overline{1}>}^5");
      G -> add(lace::RotMtrx(vec3d(1,-1, 1),  pi/3)*lace::Sigma(vec3d(1,-1, 1)),  "S_{6<1\\overline{1}1>}");
      G -> add(lace::RotMtrx(vec3d(1,-1, 1),5*pi/3)*lace::Sigma(vec3d(1,-1, 1)),  "S_{6<1\\overline{1}1>}^5");
      G -> add(lace::RotMtrx(vec3d(-1, 1, 1),  pi/3)*lace::Sigma(vec3d(-1, 1, 1)),"S_{6<\\overline{1}11>}");
      G -> add(lace::RotMtrx(vec3d(-1, 1, 1),5*pi/3)*lace::Sigma(vec3d(-1, 1, 1)),"S_{6<\\overline{1}11>}^5");

      return * G;
    }

  };


};
#endif
