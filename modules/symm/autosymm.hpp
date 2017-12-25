#ifndef _QPP_AUTOSYMM_H
#define _QPP_AUTOSYMM_H

#include <geom/geom.hpp>
#include <geom/ngbr.hpp>
#include <symm/cell.hpp>
#include <symm/gcell.hpp>
#include <symm/transform.hpp>
#include <symm/group_theory.hpp>
#include <symm/spgw.hpp>
#include <Eigen/Dense>
#include <algorithm>

#ifdef PY_EXPORT
#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <python/qppython.hpp>

namespace bp = boost::python;
namespace sn = boost::python::self_ns;

#endif

namespace qpp{
  
  template<class REAL, class CELL>
  bool equiv_geoms( std::vector<int> & ord, 
		    const geometry<REAL,CELL> & g1, 
		    const geometry<REAL,CELL> & g2, 
		    REAL R = geometry<REAL,CELL>::tol_geom_default)
  {
    if (g1.nat() != g2.nat() )
      return false;

    int N = g1.nat();
    
    // fixme - inefficient for large molecules, N^2 scaling
    ord.resize(N);
    
    for (int i=0; i<N; i++)
      {
	bool found = false;
	for (int j=0; j<N; j++)
	  if ( norm2(g1.pos(i)-g2.pos(j)) < R*R && g1.atom(i) == g2.atom(j) )
	    {
	      found = true;
	      ord[i]=j;
	      break;
	    }
	if (!found)
	  return false;
      }

    return true;    
  }

  template<class REAL, class CELL>
  bool equiv_geoms( const geometry<REAL,CELL> & g1, 
		    const geometry<REAL,CELL> & g2, 
		    REAL R = geometry<REAL,CELL>::tol_geom_default)
  {
    std::vector<int> ord;
    return equiv_geoms(ord,g1,g2,R);
  }

  template<class REAL, class CELL>
  bool has_symmetry( geometry<REAL,CELL> & geom, CELL & symm, 
		     REAL R = geometry<REAL,CELL>::tol_geom_default)
  {
    CELL cell = geom.cell;
    geom.cell = symm;
    geom.DIM = symm.DIM;

    bonding_table<REAL> b;
    b.default_distance = R;
    neighbours_table<REAL,CELL> ngbr(geom,b);
    
    ngbr.build();

    bool res = true;
    int Ng = 1;
    for (int d = 0; d<symm.DIM; d++)
      Ng *= symm.end()(d) - symm.begin()(d) + 1;

    //std::cout << "Group orders: " << symm.begin() << symm.end() << "\n";
    //std::cout << "Group size = " << Ng << "\n";

    for (int i=0; i<geom.nat(); i++)
      {
	int found = 0;

	//std::cout << "atom " << i;

	for (int j=0; j<ngbr.n(i); j++)
	  {
	    index J = ngbr(i,j);
	    //std::cout << " " << J;

	    if ( geom.atom(i) == geom.atom(J) && 
		 J != index::D(symm.DIM).atom(J(0)))
	      {
		found++;
		//std::cout << "EQ";
	      }
	    if (found == Ng-1)
	      break;
	  }

	//std::cout << "\nnfound= " << found << "\n";

	if ( found != Ng-1)
	  {
	    res = false;
	    //break;
	  }
      }
    
    geom.cell = cell;
    geom.DIM = cell.DIM;
    return res;
  }

  template<class REAL>
  bool best_transform( matrix3d<REAL> & res,
		       const std::vector<vector3d<REAL> > &a, const std::vector<vector3d<REAL> > &b)
  {
    REAL eps = vector3d<REAL>::tol_equiv;

    matrix3d<REAL> C(0e0);
    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
	for (int k=0; k<a.size(); k++)
	  C(i,j) += a[k](j)*b[k](i);

    //std::cout << "C matrix= " << C << "\n";

    matrix3d<typename numeric_type<REAL>::complex> dv, SS(0e0);
    matrix3d<REAL> D = C*C.T(), S(0e0);
    vector3d<typename numeric_type<REAL>::complex> de;
 
    //std::cout << "C*C.T matrix= " << D << "\n";
   
    diagon3d(de,dv,D);

    /*
    std::cout << "C*C.T eigvals= " << de << "\n";
    std::cout << "C*C.T eigvecs= " << dv << "\n";
    */

    for (int i=0; i<3; i++)
      if (std::abs(de(i))<eps)
	return false;

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
	for (int k=0; k<3; k++)
	  SS(i,j) += std::conj(dv(i,k))*dv(j,k)/std::sqrt(de(k).real());

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
	{
	  S(i,j) = SS(i,j).real();
	  //std::cout << SS(i,j).imag() << " ";
	}
    //std::cout << "\n";

    res = S*C;
    return true;
  }

  template<class REAL>
  void rotate_pair( matrix3d<REAL> & R,
		   const vector3d<REAL> & a1, const vector3d<REAL> & a2,
		   const vector3d<REAL> & b1, const vector3d<REAL> & b2)
  {
    vector3d<REAL> a3 = a1%a2, b3 = b1%b2;
    a3 *= std::sqrt(norm(a1)*norm(a2))/norm(a3);
    b3 *= std::sqrt(norm(b1)*norm(b2))/norm(b3);
    
    best_transform(R,{a1,a2,a3},{b1,b2,b3});
  }

  template<class REAL>
  void analyze_transform(vector3d<REAL> & axis, REAL & phi, bool & inversion,
			 const matrix3d<REAL> & R)
  {
    REAL eps = vector3d<REAL>::tol_equiv;
    vector3d<typename numeric_type<REAL>::complex> e, nax;
    matrix3d<typename numeric_type<REAL>::complex> n;
    typename numeric_type<REAL>::complex I(0,1);

    inversion = det(R)<0;
    matrix3d<REAL> R1=REAL(inversion? -1:1)*R;
    diagon3d(e,n,R1);

    int i1=0,i2=0;
    for (int i=0; i<3; i++)
      {
	if ( e[i].imag() < e[i1].imag() )
	  i1 = i;
	if ( e[i].imag() > e[i2].imag() )
	  i2 = i;
      }

    int i0 = 3 - i1 - i2;

    // std::cout << " i0, i1, i2= " << i0 << " " << i1 << " " << i2 << " eigvals= " << e << "\n";
    
    if (i1==i2)
      {
	i0=0;
	for (int i=0; i<3; i++)
	  {
	    if ( e[i].real() < e[i1].real() )
	      i1 = i;
	    if ( e[i].real() > e[i0].real() )
	      i0 = i;	    
	  }
	i2 = 3 - i1 - i0;
      }
    

    //std::cout << " i0, i1, i2= " << i0 << " " << i1 << " " << i2 << " eigvals= " << e << "\n";

    nax = n(i0);
    
    int i=0;
    if ( std::abs(nax(i))<std::abs(nax(1))) i=1;
    if ( std::abs(nax(i))<std::abs(nax(2))) i=2;
    nax *= std::abs(nax(i))/nax(i);

    /*
    std::cout << "eigvecs= " << n(0) << "\n" 
	      << n(1) << "\n" << n(2) << "\n"
	      << " ax= " << nax << "\n";
    */

    axis(0) = nax(0).real();
    axis(1) = nax(1).real();
    axis(2) = nax(2).real();
    
    REAL cos = e[i1].real();
    if (cos > REAL(1))
      phi = 0;
    else if (cos<REAL(-1))
      phi = pi;
    else
      phi = std::acos(cos);

    if ( norm(R1-RotMtrx(axis,phi)) > norm(R1-RotMtrx(-axis,phi)) )
      axis *= -REAL(1);
  }
  


  // ------------------------------------------------------
  class permutation
  {
    std::vector<int> p;
    
  public:
    
    int N;
    
    //static permutation unity;
    
    permutation(int _N)
    {
      N = _N;
      for (int i=0; i<N; i++)
	p.push_back(i);
    }

    permutation(const permutation & b) 
    {
      //std::cout << "copy constructor\n";
      N = b.N;
      for (int i : b.p)
	p.push_back(i);
    }

    permutation(const std::vector<int> & li)
    {
      //std::cout << "list constructor\n";
      N = li.size();
      for (int j : li)
	p.push_back(j);
    
      /*
	for (int j=0; j<N; j++)
	std::cout << p[j] << " ";
	std::cout << std::endl;
      */
    }
    
    inline int operator[](int i) const
    { return p[i];}
    
    inline int & operator[](int i)
    { return p[i];}
    
    inline int size() const
    {return p.size();}
    
    inline permutation operator*(const permutation & b) const
    {
      /*
    print();
    std::cout << "*";
    b.print();
    std::cout << "\n";
      */
      if (N!=b.N)
	IndexError("Permutations have different dimensions");
      permutation res(N);
      for (int i=0; i<N; i++)
	res[i] = p[b[i]];
      return res;
    }

    inline bool operator==(const permutation & b) const
    {
      if (N!=b.N)
	return false;
      bool res=true;
      for (int i=0; i<N; i++)
	if (p[i] != b[i])
	  {
	    res = false;
	    break;
	  }
      return res;
    }
    
    inline bool operator!=(const permutation & b) const
    {
      return ! ((*this)==b);
    }
    
    void print() const
    {
      std::cout << "(";
      for (int i:p)
	std::cout << i << " ";
      std::cout <<")";
    }
    
  };

  // -------------------------------------------------------------

  template <class REAL>
  void finitize_point_group(std::vector<matrix3d<REAL> > & G, std::vector<permutation> P, REAL delta)
  {
    // find and appropriately place unity element
    int N = G.size();
    int i0;
    for (i0=0; i0<G.size(); i0++)
      {
	bool thatsit=true;
	for (int j=0; j<P[i0].N; j++)
	  if (P[i0][j]!=j)
	    {
	      thatsit=false;
	      break;
	    }
	if (thatsit) break;
      }
    if (i0!=0)
      {
	std::swap(G[0],G[i0]);
	std::swap(P[0],P[i0]);
      }

    // Construct multiplication table and element orders

    group_analyzer<permutation> A(P);
        
    // Analyze group operations

    std::vector<vector3d<REAL> > axis(N);
    std::vector<REAL> phi(N);
    std::vector<char> inv(N);
    std::vector<int> pow(N), dnm(N);

    int inversion = -1;

    for (int i=0; i<N; i++)
      {
	analyze_transform(axis[i],phi[i],*((bool*)&inv[i]),G[i]);
	if (A.order(i)==2 && inv[i] && phi[i] < pi/2)
	  inversion = i;
      }

    std::vector<std::vector<int> > same_axis;

    for (int i=1; i<N; i++)
      {
	if (i==inversion)
	  continue;
	bool found = false;
	for (int j=0; j<same_axis.size(); j++)
	  {
	    if ( norm(axis[i]+axis[same_axis[j][0]])<delta )
	      {
		axis[i] = -axis[i];
		phi[i]  = -phi[i];
	      }
	    if ( norm(axis[i]-axis[same_axis[j][0]])<delta ||
		 norm(axis[i]+axis[same_axis[j][0]])<delta)
	      {
		found=true;
		same_axis[j].push_back(i);
		break;
	      }
	  }
	if (!found)
	  same_axis.push_back({i});
      }

    int M = same_axis.size();
    
    // Correcting rotation angles

    phi[0] = REAL(0);
    for (int j=1; j<N; j++)
      if (j==inversion)
	phi[j] = REAL(0);
      else
	{
	  //std::cout << j << " before " << phi[j];
	  int k = round(phi[j]*A.order(j)/(2*pi));
	  phi[j] = REAL(pi)*2*k/A.order(j);
	  //std::cout << " after " << phi[j] << "\n";
	}
    
    // Correcting axes

    REAL eps = vector3d<REAL>::tol_equiv;
    std::vector<vector3d<REAL> > exact_axis(M);

    if (M>1)
      {

	Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic>  S(M,M);
	
	for (int i=0; i<M; i++)
	  for (int j=0; j<=i; j++)
	    if (i==j)
	      S(i,j)=1;
	    else
	      {
		int i1 = same_axis[i][0], j1 = same_axis[j][0];
		int k1 = A.multab(i1,j1);
				
		S(i,j) = S(j,i) = 
		  (std::cos(phi[i1]/2)*std::cos(phi[j1]/2) - 
		   std::cos(phi[k1]/2))/
		  (std::sin(phi[i1]/2)*std::sin(phi[j1]/2));
		
		if (S(i,j)*scal(axis[i1],axis[j1])<0)
		  S(i,j) = S(j,i) = -S(i,j);
		
		/*
		  std::cout << i1 << "(phi= " << phi[i1] << " n= " << axis[i1] << " r= " << bool(inv[i1]) << ")* " 
		  << j1 << "(phi= " << phi[j1] << " n= " << axis[j1] << " r= " << bool(inv[j1]) << ") -> " 
		  << k1 << "(phi= " << phi[k1] << " n= " << axis[k1] << " r= " << bool(inv[k1]) << ") S0= " 
		  << scal(axis[i1],axis[j1]) << " S1= " << S(i,j) << "\n";
		*/
		std::cout << i << ","  << j << " S0= " 
			  << scal(axis[i1],axis[j1]) << " S1= " << S(i,j) << "\n";
		
		//break;
	      }

	exact_axis[0] = {0,0,1};
	exact_axis[1] = {std::sqrt(1-S(0,1)*S(0,1)), 0, S(0,1)};

	for (int i=2; i<M; i++)
	  {
	    vector3d<REAL> n;
	    n.z() = S(0,i);
	    n.x() = (S(1,i) - S(0,1)*S(0,i))/std::sqrt(1-S(0,1)*S(0,1));
	    n.y() = 1 - n.x()*n.x() - n.z()*n.z();
	    if (n.y()<0)
	      n.y()=0;
	    n.y() = std::sqrt(n.y());
	    
	    int jy;
	    for (jy=2; jy<i; jy++)
	      if ( std::abs(exact_axis[jy].y()) > eps )
		break;
	    
	    if ( jy<i && std::abs(scal(n,exact_axis[jy])-S(i,jy))>eps)
	      n.y() *= -1;
	    
	    exact_axis[i] = n;
	  }

	// Finding the rotation
	
	std::vector<vector3d<REAL> > p0,p1;
	
	for (int i=0; i<M; i++)
	  for (int j:same_axis[i])
	    {
	      p0.push_back(exact_axis[i]);
	      p1.push_back(axis[j]);
	    }

	bool complanar = true;
	for (int i=2; i<M; i++)
	  if ( std::abs(det(exact_axis[0],exact_axis[1],exact_axis[i])) > eps )
	    {
	      complanar = false;
	      break;
	    }

	if (complanar)
	  {
	    p0.push_back(exact_axis[0] % exact_axis[1]);
	    p1.push_back(axis[same_axis[0][0]] % axis[same_axis[1][0]]);
	  }
	
	matrix3d<REAL> U;
	
	best_transform(U,p0,p1);

	for (int i=0; i<M; i++)
	  exact_axis[i] = U*exact_axis[i];

      }
    else
      {
	exact_axis[0] = 0;
	for (int i : same_axis[0])
	  exact_axis[0] += axis[i];
	exact_axis[0] /= norm(exact_axis[0]);
      }

    // Reconstruct the group
    G.clear();
    G.push_back(matrix3d<REAL>(1));
    if (inversion>=0)
      G.push_back(matrix3d<REAL>(-1));

    for (int i=0; i<M; i++)
      for (int j:same_axis[i])	
	G.push_back(RotMtrx(exact_axis[i],phi[j])*(inv[i] ? REAL(-1) : REAL(1)) );
    
    /*
    for (int i=0; i<M; i++)
      {
	std::cout << i << " ax = " << axis[same_axis[i][0]] << " exact= " << exact_axes[i] << "\n";
	for (int j=0; j<=i; j++)
	  std::cout << i << "," << j << " S0= " << scal(axis[same_axis[i][0]],axis[same_axis[j][0]]) 
		    << " S1= " <<  scal(exact_axes[i],exact_axes[j])  << "\n";
      }
    */
  }


  template<class REAL>
  bool vector_pair_match(const vector3d<REAL> & a1, const vector3d<REAL> & a2,
			 const vector3d<REAL> & b1, const vector3d<REAL> & b2,
			 REAL R = geometry<REAL,periodic_cell<REAL> >::tol_geom_default)
  {
    REAL aa1 = norm(a1), aa2 = norm(a2),
      bb1 = norm(b1), bb2 = norm(b2);

    if ( std::abs(aa1-bb1) > R || std::abs(aa2-bb2) > R )
      return false;

    if ( aa1 < R || aa2 < R)
      return true;

    REAL alp = std::acos(scal(a1,b1)/(aa1*bb1)), bet = std::acos(scal(a2,b2)/(aa2*bb2)),
      alp1 = std::acos((aa1*aa1+bb1*bb1-R*R)/(2*aa1*bb1)),
      alp2 = std::acos((aa2*aa2+bb2*bb2-R*R)/(2*aa2*bb2));

    if ( std::abs(alp-bet) > alp1 + alp2 )
      return false;
    
    return true;
  }

  template<class REAL>
  bool vector_triplet_match(const vector3d<REAL> & a1, const vector3d<REAL> & a2, const vector3d<REAL> & a3,
			    const vector3d<REAL> & b1, const vector3d<REAL> & b2, const vector3d<REAL> & b3,
			    REAL R = geometry<REAL,periodic_cell<REAL> >::tol_geom_default)
  {
    matrix3d<REAL> U;
    best_transform(U,{a1,a2,a3},{b1,b2,b3});
    return norm(U*a1-b1)<R && norm(U*a2-b2)<R && norm(U*a3-b3)<R;
  }

  enum{
    bravais_triclinic = 1,
    bravais_monoclinic = 2,
    bravais_monoclinic_bas = 3,
    bravais_orthorhombic_prim = 4,
    bravais_orthorhombic_base = 5,
    bravais_orthorhombic_body = 6,
    bravais_orthorhombic_face = 7,
    bravais_tetragonal_prim = 8,
    bravais_tetragonal_body = 9,
    bravais_hexagonal = 10,
    bravais_trigonal = 11,
    bravais_cubic_prim = 12,
    bravais_fcc = 13,
    bravais_bcc = 14
  };


  template<class REAL>
  int bravais_point_group(generated_group<matrix3d<REAL> > & G, 
			  periodic_cell<REAL> & cell,
			  REAL R = geometry<REAL,periodic_cell<REAL> >::tol_geom_default)
  {
    if (cell.DIM != 3)
      IndexError("bravais_point_group:: works only for 3d-periodic crystals");

    matrix3d<REAL> aa(0);

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
	aa(i,j) = scal(cell(i),cell(j));

    vector3d<REAL> leig = diagon3d(aa);
    REAL lmin = leig(0);
    if (leig(1) < lmin) lmin = leig(1);
    if (leig(2) < lmin) lmin = leig(2);

    REAL amax = norm(cell(0));
    if (norm(cell(1))>amax) amax = norm(cell(1));
    if (norm(cell(2))>amax) amax = norm(cell(2));

    amax += R;

    int n = int(amax/std::sqrt(lmin))+1;

    REAL eps = vector3d<REAL>::tol_equiv;
    std::vector<vector3d<REAL> > lattvecs;

    for (int i=-n; i<=n; i++)
      for (int j=-n; j<=n; j++)
	for (int k=-n; k<=n; k++)
	  {
	    vector3d<REAL> x = cell(0)*i + cell(1)*j + cell(2)*k;
	    if (norm(x) <= amax+eps)
	      lattvecs.push_back(x);
	  }

    std::vector<matrix3d<REAL> > Gapprox;
    std::set<int> ipoints;

    for (int i=0; i<lattvecs.size(); i++)
      for (int j=0; j<lattvecs.size(); j++)
	if (i!=j)
	  for (int k=0; k<lattvecs.size(); k++)
	    if (i!=k && j!=k)
	      {
		matrix3d<REAL> U;
		best_transform(U,{cell(0),cell(1),cell(2)},{lattvecs[i],lattvecs[j],lattvecs[k]});

		if ( norm(lattvecs[i]-U*cell(0))<R && 
		     norm(lattvecs[j]-U*cell(1))<R && 
		     norm(lattvecs[k]-U*cell(2))<R)
		  {
		    Gapprox.push_back(U);
		    ipoints.insert(i);
		    ipoints.insert(j);
		    ipoints.insert(k);
		  }
	      }


    std::vector<vector3d<REAL> > points;
    for (int i : ipoints)
      points.push_back(lattvecs[i]);

    std::vector<permutation> Gperm;

    for (const auto & g : Gapprox)
      {
	std::vector<int> p;
	for (int i=0; i<points.size(); i++)
	  {
	    vector3d<REAL> r = g*points[i];
	    for (int j=0; j<points.size(); j++)
	      if (norm(points[j]-r)<R)
		{
		  p.push_back(j);
		  break;
		}
	  }
	Gperm.push_back(permutation(p));
      }

    REAL angle_error = std::asin(R/amax);

    finitize_point_group(Gapprox,Gperm,angle_error);

    for (const auto & g : Gapprox)
      G.add(g);

    return 0;

  }

// ----------------------------------------------------------------------------------------

  template<class REAL>
  void find_point_symm(generated_group<matrix3d<REAL> > & G, 
		       const geometry<REAL, periodic_cell<REAL> > & geom,
		       REAL R = geometry<REAL,periodic_cell<REAL> >::tol_geom_default)
  {
    geometry<REAL, periodic_cell<REAL> > g(geom);

    // find geometric centre
    vector3d<REAL> cntr(0);

    for (int i=0; i<g.nat(); i++)
      cntr += g.coord(i);
    cntr /= g.nat();

    for (int i=0; i<g.nat(); i++)
      g.change(i,g.atom(i),g.coord(i)-cntr);

    g.sort([](const geometry<REAL> & gg, int ii)->REAL {return norm(gg.pos(ii));});

    g.write(std::cout);

    // define the possible "images" of atom to which it can transform
    std::vector<std::set<int> > images(g.nat());

    int i1=0, i2=0;

    for (int i=0; i<g.nat(); i++)
      {
	REAL r = norm(g.pos(i));
	while( r - norm(g.pos(i1)) > R) i1++;
	while( i2 < g.nat() && norm(g.pos(i2)) - r < R) i2++;
	
	//std::cout << "i1,i,i2= " << i1 << " " << i << " " <<  i2 << "\n";

	for (int j=i1; j<i2; j++)
	  if ( g.atom(j) == g.atom(i) )
	    images[i].insert(j);
      }

    /*
    for (int i=0; i<images.size(); i++)
      {
	std::cout << "images[" << i << "]= ";
	for (int j : images[i])
	  std::cout << j << " ";
	std::cout << "\n";
      }
    */

    // Define the shells of atoms which can be transformed to each other

    std::vector< std::set<int> > shells;

    for (int i=0; i<g.nat(); i++)
      {
	bool already = false;
	for (int j=0; j<shells.size(); j++)
	  if ( shells[j].count(i)>0 )
	    {
	      already = true;
	      break;
	    }

	//std::cout << "atom " << i << " already= " << already << "\n";

	if (already) continue;

	//std::cout << " here " << i << "\n";

	std::set<int> iset, buffer;
	iset = images[i];
	for (int j : images[i])
	  if ( images[j].count(i) )
	    {
	      std::set_intersection(iset.begin(), iset.end(), 
				    images[j].begin(), images[j].end(), 
				    std::inserter(buffer,buffer.begin()));
	      iset = buffer;
	    }
	shells.push_back(iset);
      }

    for (int i=0; i<shells.size(); i++)
      {
	std::cout << "shell[" << i << "]= ";
	for (int j : shells[i])
	  std::cout << j << " ";
	std::cout << "\n";
      }

    REAL angle_error = 0e0;
    geometry<REAL, periodic_cell<REAL> > g1(geom);
    std::vector<permutation> P;
    P.push_back(permutation(g.nat()));

    // Shells are formed, let's try different combinations of atoms to be transformed to each other

    for (int sh1=0; sh1<shells.size(); sh1++)
      for (int sh2=0; sh2<=sh1; sh2++)
	for (int i : shells[sh1])
	  for (int j : shells[sh2])
	    {
	      // check duplicate pair
	      if ( sh1==sh2 && i > j )
		continue;

	      // check that one of the points is too close to the centre
	      vector3d<REAL> r1 = g.pos(i), r2 = g.pos(j);
	      if ( norm(r1)<R || norm(r2)<R )
		continue;

	      // check collineality
	      REAL a1 = std::asin(R/norm(r1)), a2 = std::asin(R/norm(r2)),
			    alp = a1+a2, 
			    s = scal(r1,r2)/(norm(r1)*norm(r2));
	      
	      if (alp > angle_error) angle_error = alp;

	      if ( s > REAL(1) ) s = REAL(1);
	      if ( s < REAL(-1) ) s = REAL(-1);

	      REAL beta = std::acos(s);

	      //std::cout << i << "," << j << " r1= " << norm(r1) << " r2= " << norm(r2) << " a1= " << a1 
	      //<< " a2= " << a2 << " s= " << s << " bet= " << beta << "\n";

	      if ( beta < alp || beta > pi - alp )
		continue;
	      
	      for (int i1 : shells[sh1] )
		if (i1 <= i)
		  for (int j1 : shells[sh2] )
		    if (j1 <= j)
		      {
			
			REAL s1 = scal(g.pos(i1),g.pos(j1))/(norm(g.pos(i1))*norm(g.pos(j1)));
			
			if ( s1 > REAL(1) )  s1 = REAL(1);
			if ( s1 < REAL(-1) ) s1 = REAL(-1);
			
			REAL beta1 = std::acos(s1);
			
			//std::cout << i1 << "," << j1 <<  " s1= " << s1 << " bet1= " << beta1 << "\n";
			
			if ( std::abs(beta-beta1) < alp )
			  {
			    std::cout << i << "," << j << " -> " << i1 << "," << j1 << "\n";
			    vector3d<REAL> r11=g.pos(i1), r12 = g.pos(j1);
			    matrix3d<REAL> U;
			    best_transform(U,{r1,r2,r1%r2/sqrt(norm(r1)*norm(r2))},
					   {r11,r12,r11%r12/sqrt(norm(r11)*norm(r12))});

			    for (int k = 0; k<g.nat(); k++)
			      g1.coord(k) = U*g.coord(k);

			    std::vector<int> pp;
			    if (equiv_geoms(pp,g,g1,R))
			      if (std::find(P.begin(),P.end(),permutation(pp))==P.end())
				{
				  P.push_back(permutation(pp));
				  G.group.push_back(U);
				  permutation(pp).print();
				  std::cout << "\n";
				}

			    best_transform(U,{r1,r2,r1%r2/sqrt(norm(r1)*norm(r2))},
					   {r11,r12,-(r11%r12)/sqrt(norm(r11)*norm(r12))});

			    for (int k = 0; k<g.nat(); k++)
			      g1.coord(k) = U*g.coord(k);

			    if (equiv_geoms(pp,g,g1,R))
			      if (std::find(P.begin(),P.end(),permutation(pp))==P.end())
				{
				  P.push_back(permutation(pp));
				  G.group.push_back(U);
				  permutation(pp).print();
				  std::cout << "\n";
				}

			  }
		      }
	    }    
    
    //finitize_point_group(G.group,P,angle_error);

  }

  // ------------------------------------------------------------------------------------------
  template<class REAL>
  void find_cryst_symm(generated_group<rotrans<REAL,true> > & G, 
		       geometry<REAL,periodic_cell<REAL> > & geom,
		       REAL R = geometry<REAL,periodic_cell<REAL>>::tol_geom_default)
  {
    spgw_get_symmetry(G,geom,R);
  }

  template<class REAL>
  void find_cryst_symm(generators_pack<rotrans<REAL,true> > & G, 
		       geometry<REAL, periodic_cell<REAL> > & geom,
		       REAL R = geometry<REAL,periodic_cell<REAL>>::tol_geom_default)
  {
    generated_group<rotrans<REAL,true> > G1;
    spgw_get_symmetry(G1,geom,R);
    generator_form(G,G1); 
  }

  // ---------- find point subgroups stuff ----------------------

  template <class REAL, bool BOUND>
  bool is_pure_translation(const rotrans<REAL,BOUND> & A)
  {    
    return norm(A.R - matrix3d<REAL>(REAL(1))) < rotrans<REAL,BOUND>::rotation_tolerance && 
						 norm(A.T) > rotrans<REAL,BOUND>::translation_tolerance;
  }

  template <class REAL, bool BOUND>
  int find_or_add(std::vector<rotrans<REAL,BOUND> > & registry, const rotrans<REAL,BOUND> & A)
  {
    for (int i=0; i<registry.size(); i++)
      if ( A == registry[i] )
	return i;
    registry.push_back(A);
    //std::cout << "adding " << A << "\n";
    return registry.size()-1;
  }
  
  template <class REAL, bool BOUND>
  bool build_fingroup_by_registry(std::vector<int> & G, std::vector<rotrans<REAL,BOUND> > & registry)
  {
    int inew=0; 
    while (inew < G.size())
      {
	int inewest = G.size();
	  for (int ig1 = 0; ig1 < inewest; ig1++)
	    for (int ig2 = inew; ig2 < inewest; ig2++)
	      {
		rotrans<REAL,BOUND> h1 = registry[G[ig1]]*registry[G[ig2]];
		
		if ( is_pure_translation(h1) )
		  return false;

		int ih1 = find_or_add(registry,h1);
		if ( std::find(G.begin(),G.end(),ih1)==G.end() )
		  {
		    G.push_back(ih1);
		    //std::cout << ih1 << h1 << "\n";
		  }

		rotrans<REAL,BOUND> h2 = registry[G[ig2]]*registry[G[ig1]];
	
		if ( is_pure_translation(h2) )
		  return false;

		int ih2 = find_or_add(registry,h2);
		if ( std::find(G.begin(),G.end(),ih2)==G.end() )
		  {
		    G.push_back(ih2);
		    //std::cout << ih1 << h1 << "\n";
		  }
	      } 
	  inew = inewest;
      }
    return true;
  }

  /*! \brief Finds all point subgroups of crystalline symmetry group. 
    Can be used to list all high symmetry sites in the lattice.
    @param subs (OUT)    - std::vector containing point subgroups
    @param cntrs (OUT)   - std::vector containing the central points of the point groups
    @param G (IN)        - crystalline symmetry group in array form
   */
  template<class REAL>
  void find_point_subgroups(std::vector<generated_group<matrix3d<REAL> > > & subs, 
			    std::vector<vector3d<REAL> > &cntrs,
			    const generated_group<rotrans<REAL,false> > & G)
  {
    std::vector<rotrans<REAL,false> > registry(G.group);
    std::vector< std::vector<int> > isubs;

    // Find the elements whose abelian subgroup is point; put these subgroup into isubs
    for (int i=0; i<G.size(); i++)
      {
	std::vector<int> asub({i});
	if ( build_fingroup_by_registry(asub,registry) )
	  isubs.push_back(asub);
      }

    for (int i=0; i<isubs.size(); i++)
      {
	for (int j=0; j< isubs[i].size(); j++)
	  std::cout << isubs[i][j]<< " ";
	
	vector3d<REAL> c={0,0,0};
	for (int j=0; j< isubs[i].size(); j++)
	  c += registry[isubs[i][j]]*vector3d<REAL>(0,0,0);
	c = c/isubs[i].size();
	cntrs.push_back(c);
	std::cout << c << "\n";
      }
  }


  template<class REAL>
  void find_point_subgroups(std::vector<generated_group<matrix3d<REAL> > > & subs, 
			    std::vector<vector3d<REAL> > &cntrs,
			    const generated_group<rotrans<REAL,true> > & G)

  {
    generated_group<rotrans<REAL,false> > G1;
    G1.group.clear();
    for (const auto & x : G.group)
      G1.group.push_back(rotrans<REAL,false>(x.T,x.R));

    find_point_subgroups(subs,cntrs,G1);
  }


#ifdef PY_EXPORT

  template<class REAL>
  bool py_best_transform( matrix3d<REAL> & res, const bp::list &A, const bp::list &B)
  {
    std::vector<vector3d<REAL> > a,b;
    
    if (bp::len(A) != bp::len(B))
      IndexError("find_rotation:: different number of items int two lists");
    for (int i=0; i<bp::len(A); i++)
      {
	vector3d<REAL> r;
	if (bp::extract<vector3d<REAL> >(A[i]).check())
	  r = bp::extract<vector3d<REAL> >(A[i]);
	else if (bp::extract<bp::tuple>(A[i]).check())
	  r = vector3d<REAL>(bp::extract<bp::tuple>(A[i]));
	else if (bp::extract<bp::list>(A[i]).check())
	  r = vector3d<REAL>(bp::extract<bp::list>(A[i]));
	else
	  TypeError("find_rotation: invalid (not vector3) item in A list");
	a.push_back(r);

	if (bp::extract<vector3d<REAL> >(B[i]).check())
	  r = bp::extract<vector3d<REAL> >(B[i]);
	else if (bp::extract<bp::tuple>(B[i]).check())
	  r = vector3d<REAL>(bp::extract<bp::tuple>(B[i]));
	else if (bp::extract<bp::list>(B[i]).check())
	  r = vector3d<REAL>(bp::extract<bp::list>(B[i]));
	else
	  TypeError("find_rotation: invalid (not vector3) item in B list");
	b.push_back(r);
      }

    for (int i=0; i<a.size(); i++)
      std::cout << a[i] << " -> " << b[i] << "\n";

    return best_transform(res,a,b);

    
  }

  template<class REAL>
  bp::list py_analyze_transform(const matrix3d<REAL> & R)
  {
    vector3d<REAL> axis;
    REAL phi;
    bool inversion;
    analyze_transform(axis,phi,inversion,R);
    
    bp::list res;
    res.append(axis);
    res.append(phi);
    res.append(inversion);

    return res;
  }
    
  template<class REAL>
  void py_find_cryst_symm1(generated_group<rotrans<REAL,true> > & G, 
			   geometry<REAL,periodic_cell<REAL> > & geom,
			   REAL R = geometry<REAL,periodic_cell<REAL>>::tol_geom_default)
  {  find_cryst_symm(G,geom,R); }

  template<class REAL>
  void py_find_cryst_symm2(generators_pack<rotrans<REAL,true> > & G, 
			   geometry<REAL, periodic_cell<REAL> > & geom,
			   REAL R = geometry<REAL,periodic_cell<REAL>>::tol_geom_default)
  { find_cryst_symm(G,geom,R); }

  template<class REAL>
  void py_find_point_subgroups1(bp::list & subs, bp::list &cntrs,
				const generated_group<rotrans<REAL,true> > & G)
  {
    std::vector<generated_group<matrix3d<REAL> > >  vsubs;
    std::vector<vector3d<REAL> > vcntrs;
    find_point_subgroups(vsubs,vcntrs,G);
    for (int i=0; i<vsubs.size(); i++)
      {
	subs.append(vsubs[i]);
	cntrs.append(vcntrs[i]);
      }
  }

  template<class REAL>
  void py_find_point_subgroups2(bp::list & subs, bp::list &cntrs,
				const generated_group<rotrans<REAL,true> > & G)
  {
    std::vector<generated_group<matrix3d<REAL> > >  vsubs;
    std::vector<vector3d<REAL> > vcntrs;
    find_point_subgroups(vsubs,vcntrs,G);
    for (int i=0; i<vsubs.size(); i++)
      {
	subs.append(vsubs[i]);
	cntrs.append(vcntrs[i]);
      }
  }

    
#endif

};

#endif
