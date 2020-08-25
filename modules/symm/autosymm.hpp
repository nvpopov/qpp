#ifndef QPP_AUTOSYMM_H
#define QPP_AUTOSYMM_H

#include <geom/shape.hpp>
#include <symm/cell.hpp>
#include <symm/gen_cell.hpp>
#include <symm/transform.hpp>
#include <symm/group_theory.hpp>
#include <symm/point_groups.hpp>
#include <symm/permut.hpp>
#include <symm/subspace.hpp>
#include <Eigen/Dense>
#include <algorithm>
#include <iomanip>
#include <optional>

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif


namespace qpp {

  template<class REAL, class CELL>
  bool has_symmetry (geometry<REAL,CELL> & geom, CELL & symm,
                     REAL R = geometry<REAL,CELL>::tol_geom_default) {

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

    for (int i=0; i<geom.nat(); i++) {
      int found = 0;

      //std::cout << "atom " << i;

      for (int j=0; j<ngbr.n(i); j++) {
	index J = ngbr(i,j);
	//std::cout << " " << J;

	if ( geom.atom(i) == geom.atom(J) &&
	     J != index::D(symm.DIM).atom(J(0))) {
	  found++;
	  //std::cout << "EQ";
	}
	if (found == Ng-1)
	  break;
      }

      //std::cout << "\nnfound= " << found << "\n";

      if ( found != Ng-1){
	res = false;
	//break;
      }
    }

    geom.cell = cell;
    geom.DIM = cell.DIM;
    return res;
  }

  // -------------------------------------------------------------
  /*
    template <class REAL>
    void add_subspace(std::vector<subspace3<REAL> > & subspaces,
    std::vector<std::vector<rotrans<REAL,false> > > &elements,
    const subspace3<REAL> &s,
    const std::vector<rotrans<REAL,false> > &g){
    int i=0;
    while (i<subspaces.size() && subspaces[i] != s) i++;


    if (i<subspaces.size())
    for (const auto & gg : g){
    if ( std::find(elements[i].begin(),elements[i].end(),gg) ==
    elements[i].end() )
    elements[i].push_back(gg);

    std::cout << "adding element to " << i <<
    " sub= (" << s.dim << s.point << s.axis  << ") g= " << gg << "\n";

    }
    else if (s.dim > -1){
    subspaces.push_back(s);
    elements.push_back(g);

    std::cout << "adding subspace (" << s.dim << s.point << s.axis  << ") g= ";
    for (const auto & gg : g)   std::cout << gg;
    std::cout << "\n";
    }
    }
  */
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


  /*! \brief Find all point symmetry operations of 3 lattice vectors
   *  comprising a periodic cell
   @param[out] G the resulting point symmetry group in array form
   @param[in] cell the periodic cell
   @param[in] R tolerance radius
  */
  template<class REAL>
  void bravais_point_group(array_group<matrix3<REAL> > & G,
                           const periodic_cell<REAL> & cell,
                           REAL R = geometry<REAL,periodic_cell<REAL> >::tol_geom){
    if (cell.DIM != 3)
      IndexError("bravais_point_group:: works only for 3d-periodic lattice");

    REAL amax = cell(0).norm();
    if (cell(1).norm() > amax) amax = cell(1).norm();
    if (cell(2).norm() > amax) amax = cell(2).norm();

    geometry<REAL> points(0);
    shape_sphere<REAL> S(amax+R);

    vector3<REAL> fmax = S.fmax(cell);
    int fx = int(fmax(0))+1,
      fy = int(fmax(1))+1,
      fz = int(fmax(2))+1;
    for (iterator I({-fx,-fy,-fz}, {fx,fy,fz}); !I.end(); I++){
      vector3<REAL> r = cell.transform({0.,0.,0.},I);
      if (S.within(r))
	points.add(std::string("point"), r);
    }

    vector3<REAL> new_centre;
    find_point_symm(G, points, new_centre, R);
  }

  // ------------------------------------------------------------------------------------------

  template<class REAL>
  void find_translations(std::vector<vector3<REAL> > & transl,
                         std::vector<permutation> & perm,
                         geometry<REAL,periodic_cell<REAL> > & g1,
                         geometry<REAL,periodic_cell<REAL> > & g2,
                         const periodic_cell<REAL> &cell,
                         REAL R = geometry<REAL,periodic_cell<REAL> >
                         ::tol_geom_default){
    transl.clear();
    g1.build_types();
    g2.build_types();
    if (g1.nat() != g2.nat() || g1.n_types() != g2.n_types())
      return;
    int nt = g1.n_types();
    std::vector<std::vector<int> > t1(nt),t2(nt);
    for (int i=0; i<g1.nat(); i++){
      t1[g1.type(i)].push_back(i);
      int t = g1.type(g2.atom(i));
      if (t==-1) return;
      t2[t].push_back(i);
    }

    // debug
    /*
      std::cout << "find_translations\n";
      for (int t=0; t<t1.size(); t++)
      {
      std::cout << "(" << g1.atom_of_type(t);
      for (int i=0; i<t1[t].size(); i++) std::cout << "," << t1[t][i];
      std::cout << ")";
      }
      std::cout << "\n";
      for (int t=0; t<t2.size(); t++)
      {
      std::cout << "(" << g1.atom_of_type(t);
      for (int i=0; i<t2[t].size(); i++) std::cout << "," << t2[t][i];
      std::cout << ")";
      }
      std::cout << "\n";
    */

    if (! std::equal(t1.begin(), t1.end(), t2.begin()))
      return;

    //reduce to uc
    for (int i=0; i<g1.nat(); i++){
      if (g1.frac)
	for (int j=0; j<3; j++)
	  g1.coord(i)(j) -= floor(g1.coord(i)(j));
      else
	g1.coord(i) = cell.reduce(g1.coord(i));

      if (g2.frac)
	for (int j=0; j<3; j++)
	  g2.coord(i)(j) -= floor(g2.coord(i)(j));
      else
	g2.coord(i) = cell.reduce(g2.coord(i));
    }

    int t=0;
    for (int i=0; i<t1.size(); i++)
      if (t1[t].size()>t1[i].size())
        t=i;

    //std::cout << "t= " << t << "\n";

    for (int i=0; i<t1[t].size(); i++){
      vector3<REAL> v = g2.pos(t2[t][i]) - g1.pos(t1[t][0]), vs=v;
      if (g1.frac) vs = cell.cart2frac(v);

      geometry<REAL,periodic_cell<REAL> > g(g1);
      for (int j=0; j<g.nat(); j++)
	g.coord(j) += vs;


      //std::cout << i << " v= " << v << "\n";


      bool is_transl = true;
      permutation P(g.nat());

      for (int j=0; j<g.nat(); j++){
	bool found = false;
	for (iterator J({-1,-1,-1},{1,1,1}); !J.end(); J++)
	  for (int k=0; k<g.nat(); k++)
	    if ((g2.pos(k) - g.pos(j,J)).norm() < 2*R && g2.atom(k)==g.atom(j)){
	      //std::cout << j << g.coord(j);

	      found = true;
	      if (g.frac){
		g.coord(j)(0) += J(0);
		g.coord(j)(1) += J(1);
		g.coord(j)(2) += J(2);
	      }
	      else
		g.coord(j) += cell(0)*J(0)+cell(1)*J(1)+cell(2)*J(2);

	      P[j] = k;
	      //std::cout << g.coord(j) << "\n";

	      goto FOUND;
	    }
      FOUND:
	if (!found){
	  is_transl = false;
	  break;
	}
      }
      if (is_transl){
	vector3<REAL> dv = vector3<REAL>::Zero();
	for (int j=0; j < g.nat(); j++)
	  dv += g2.pos(j) - g.pos(j);
	dv /= g.nat();
	transl.push_back(v+dv);
	perm.push_back(P);
      }
    }

    //debug
    /*
      std::cout << "alive after all!\n";
      for (int i=0; i<transl.size(); i++)
      {
      std::cout << i << transl[i];
      std::cout << perm[i].to_string() << "\n";
      }
    */

  }

  /*! \brief Find the translation that turns 3D-periodic geometry g1 into g2
    @param[out] t the translation vectors
    @param[in] g1 initial geometry
    @param[in] g2 final geometry
    @param[in] cell the periodic cell of DIM==3
    @param[in] R the tolerance radius
  */
  template<class REAL>
  void find_translations(std::vector<vector3<REAL> > & transl,
                         geometry<REAL,periodic_cell<REAL> > & g1,
                         geometry<REAL,periodic_cell<REAL> > & g2,
                         const periodic_cell<REAL> &cell,
                         REAL R = geometry<REAL,periodic_cell<REAL> >
                         ::tol_geom_default){
    std::vector<permutation> perm;
    find_translations(transl,perm,g1,g2,cell,R);
  }

  /*! \brief Find the crystalline symmetry group
    @param[out] G - the crystalline group of bound rotranslational
    operations in array form.
    Bound rotranslational operations are used to make the group finite
    @param[in] geom - the geometry of unit cell together with lattice vectors,
    which should be
    stored in geom.cell object. This geometry must be 3D - periodic
    @param[in] R( - the tolerance radius. Symmetry operation is considered
    valid, if the displacement of atom due to
    this operation is less than R
  */
  template<class REAL>
  void find_cryst_symm(array_group<rotrans<REAL,true> > & G,
                       geometry<REAL,periodic_cell<REAL> > & geom,
                       REAL R = geometry<REAL,periodic_cell<REAL> >
                       ::tol_geom_default){
    //spgw_get_symmetry(G,geom,R);

    array_group<matrix3<REAL> > B;
    bravais_point_group(B,geom.cell,R);
    G.group.clear();
    G.group.push_back(rotrans<REAL,true>(matrix3<REAL>::unity, &geom.cell));

    for (int i = 0; i < B.size(); i++){
      geometry<REAL,periodic_cell<REAL> > geom1(geom);
      for (int j = 0; j < geom1.nat(); j++)
	if (geom1.frac)
	  geom1.coord(j) = geom1.cell.cart2frac(B[i]*geom1.pos(j));
	else
	  geom1.coord(j) = B[i]*geom1.coord(j);

      std::vector<vector3<REAL> > T;
      std::vector<permutation> P;

      //debug
      //std::cout << "matrix " << B[i] << "\n";

      find_translations(T, P, geom1, geom, geom.cell, R);
      for (int j=0; j < T.size(); j++){
	//std::cout << i << " " << j << "\n";
	//int n = P[j].order();
	rotrans<REAL,true> S(T[j],B[i], & geom.cell);
	//G.group.push_back(S);

	//debug
	//int ng_was = G.size();

	G.generate(S);

	/*
	  std::cout << "new rotranses:\n";
	  for (int ii =ng_was; ii<G.size(); ii++)
	  std::cout << ii << G[ii] << "\n";
	*/
      }
    }

  }

  /*! \brief Find the crystalline symmetry group
    @param G(OUT) - the crystalline group of bound rotranslational operations in positionary generator form.
    Bound rotranslational operations are used to make the group finite
    @param geom(IN) - the geometry of unit cell together with lattice vectors, which should be
    stored in geom.cell object. This geometry must be 3D - periodic
    @param R(IN) - the tolerance radius. Symmetry operation is considered valid, if the displacement of atom due to
    this operation is less than R
  */
  template<class REAL>
  void find_cryst_symm(genform_group<rotrans<REAL,true> > & G,
                       geometry<REAL, periodic_cell<REAL> > & geom,
                       REAL R = geometry<REAL,periodic_cell<REAL>>::tol_geom_default){
    array_group<rotrans<REAL,true> > G1;
    find_cryst_symm(G1,geom,R);
    generator_form(G,G1);
  }

  // ----------------------------------------------------------------------------

  template <class REAL, bool BOUND>
  std::vector< rotrans<REAL,false> > rotrans_circle(const rotrans<REAL,BOUND> & r)
  {
    rotrans<REAL,false> F(r.T,r.R),
      G = F;
    std::vector< rotrans<REAL,false> > circle={G};
    while ( (G.R - matrix3<REAL>::Identity()).norm() > rotrans<REAL,false>::tol_rot )
      {
	G = G*F;
	circle.push_back(G);
      }
    return circle;
  }

  template <class REAL>
  std::vector< index > inspect_rotrans(const rotrans<REAL,true> & r, REAL eps)
  {
    std::vector<index> I = {index({1,0,0}), index({0,1,0}), index({0,0,1}), index({0,0,0})};
    matrix<REAL>  trns(3,4), cntr(3,4);
    for (int i=0; i<4; i++)
      {
	auto cicrle = rotrans_circle(rotrans_shift(r,I[i]));
	vector3<REAL> c(0);
	for (const auto & g : cicrle)
	  c += g.T;
	c = c/cicrle.size();
	cntr.col(i) = c;
	trns.col(i) = cicrle.back().T;
      }
    for (int i=0; i<3; i++){
      trns.col(i) -= trns.col(3);
      cntr.col(i) -= cntr.col(3);
    }
    std::vector<int> indep, dep;
    matrix<REAL> ns;
    nullspace(indep, dep, ns, trns, eps);
    int d = ns.cols();
    if (indep.back()==3) return {};
    std::vector<index> ret;
    index idx({0,0,0});
    for (int j=0; j<3; j++)
      if ( std::abs(ns.col(d-1)(j) - round(ns.col(d-1)(j)) ) < eps )
	idx(j) = - round(ns.col(d-1)(j));
      else
	return {};
    ret.push_back(idx);
    for (int i=0; i<d-1; i++)
      {
	bool succ = true;
	for (int j=0; j<3; j++)
	  if ( std::abs(ns.col(i)(j) - round(ns.col(i)(j)) ) < eps )
	    idx(j) = - round(ns.col(i)(j));
	  else
	    succ = false;
	if (succ)
	  ret.push_back(idx);
      }
    return ret;
  }


  template <class REAL>
  std::vector<index> rotrans_grid( const rotrans<REAL,true> & r, const std::vector<index> & idx)
  {

  }

  // ----------------------------------------------------------------------------

  template<class REAL, class TRANSF = int>
  struct highsymmsite{

    subspace3<REAL> S;
    std::vector<TRANSF> group;
    //bool maximal;
    std::vector<int> next;

    highsymmsite(const subspace3<REAL> & s, const std::vector<TRANSF> & g):
      S(s), group(g) {}
    
  };

  template<class T>
  bool belongs_to(const T & t, const std::vector<T> G)
  {
    return std::find(G.begin(),G.end(),t) != G.end();
  }
  
  template <class T>
  bool is_subset(const std::vector<T> G1, const std::vector<T> G){
    for (const T & i : G1)
      if ( ! belongs_set(i,G) )
	return false;
    return true;
  }

  template<class T>
  void merge_to_set( std::vector<T> & A, const std::vector<T> & B){
    for (const T & b:B)
      if (!belongs_to(b,A))
	A.push_back(b);
  }
  
  template<class TRANSF>
  void complete_group(std::vector<TRANSF> & S){
    std::vector<TRANSF> N = S;
    while (N.size()>0)
      {
	std::vector<TRANSF> NN;
	for (auto *c : { &S, &N } )
	  for (const auto & i : *c)
	    for (const auto & j : N)
	      {
		TRANSF k = i*j;
		if ( !belongs_to(k,S) && !belongs_to(k,N) && !belongs_to(k,NN))
		  NN.push_back(k);
		k = j*i;
		if ( !belongs_to(k,S) && !belongs_to(k,N) && !belongs_to(k,NN))
		  NN.push_back(k);
	      }
	for (const auto &i : N)
	  S.push_back(i);
	N = NN;
      }
  }

  template<class REAL>
  void fps_merge( std::vector<highsymmsite<REAL, rotrans<REAL,true> > > & H,
		  int to, const std::vector<int> & from){
    for (int i:from)
      {
	H[i].next.push_back(to);
	merge_to_set(H[to].group,H[i].group);
      }
  }

  template<class REAL>
  void fps_add( std::vector<highsymmsite<REAL, rotrans<REAL,true> > > & H,
		const subspace3<REAL> & s, int i1, int i2){
    std::vector< rotrans<REAL,true> > g(H[i1].group);
    merge_to_set(g,H[i2].group);
    H.push_back( highsymmsite<REAL, rotrans<REAL,true> >(s,g) );
    H[i1].next.push_back(H.size()-1);
    H[i2].next.push_back(H.size()-1);      
  }
  
  /*! \brief Finds all point subgroups of crystalline symmetry group.
    Can be used to list all high symmetry sites in the lattice.
    @param groups (OUT)    - std::vector containing point subgroups
    @param subspaces (OUT) - std::vector containing the central points of the point groups
    @param G (IN)          - crystalline symmetry group in array form
  */
  template<class REAL, bool BOUND>
  void find_point_subgroups(std::vector<array_group<matrix3<REAL> > > & groups,
			    std::vector<subspace3<REAL> > & subspaces,
			    const array_group<rotrans<REAL,BOUND> > & G)
  {
    
  }

  /*
  //double the UC
  periodic_cell<REAL> cell8(*G[0].cell);
  for (int i=0; i<3; i++)
  cell8(i) *= 2;
    
  array_group<rotrans<REAL,true> > G8("",rotrans<REAL,true>(matrix3<REAL>::unity, & cell8));

  //array_group<rotrans<REAL,true> > G8(G);

  int N = G.size();
    
  for (iterator j({0,0,0},{1,1,1}); !j.end(); j++)
  for (int i=0; i < N; i++)
  {
  std::cout << i << j << std::endl;
  G8.add(rotrans<REAL,true>(G[0].cell->transform(G[i].T,j),G[i].R, & cell8));
  }
      
  std::cout << "size= " << G8.size() << "\n";
  //group_analyzer<rotrans<REAL,true>, array_group<rotrans<REAL,true> > > A(G8);
  //group_analyzer<rotrans<REAL,true>, array_group<rotrans<REAL,true> > > B(G);
  //auto C = double_group(double_group(double_group(B)));

  /*
  for (int i=0; i<G8.size(); i++)
  for (int j=0; j<G8.size(); j++)
  if (A.multab(i,j)!=C.multab(i,j))
  std::cout << i << " " << j << " " << A.multab(i,j) << " " << C.multab(i,j) << std::endl;
    

  // Form all possible invariant subspaces of abelian subgroups
  // Combine (multiply) subgroups with coinciding subspaces
  std::vector<highsymmsite<REAL, rotrans<REAL,true> > > H;
  for (int i=0; i < G8.size(); i++)
  {
  auto s = invariant_subspace(G8[i]);
  if (s.dim == -1)
  continue;
  bool found = false;
  for (int j=0; j<H.size(); j++)
  if ( H[j].S == s )
  {
  if (!belongs_to(G8[i],H[j].group))
  H[j].group.push_back(G8[i]);
  found = true;
  break;
  }
  if (!found)
  H.push_back(highsymmsite<REAL, rotrans<REAL,true> >(s,{G8[i]}));
  }
  //for (int i=0; i<H.size(); i++)
  //  complete_group(H[i].group);

  int inew = 0;

  while (inew < H.size())
  {
  int inewest = H.size();
  for (int ig1 = 0; ig1 < inewest; ig1++)
  for (int ig2 = inew; ig2 < inewest; ig2++)
  if (ig1!=ig2)
  {
  subspace3<REAL> s = H[ig1].S & H[ig2].S;

  bool found = false;
	      
  if (s == H[ig1].S)
  {
  fps_merge(H,ig1,{ig2});
  found = true;
  }
  if (s == H[ig2].S)
  {
  fps_merge(H,ig2,{ig1});
  found = true;
  }

  for (int i=0; i<H.size(); i++)
  if (i!=ig1 && i!=ig2 && s == H[i].S)
  {
  merge_to_set(H[i].group,H[ig1].group);
  merge_to_set(H[i].group,H[ig2].group);
  }
	      
	      
  }
  inew = inewest;
  }

  for (int i=0; i<H.size(); i++)
  //if (H[i].next.size()==0)
  {
  /*
  std::cout << "{";
  for (const auto & j:H[i].group)
  std::cout << j << ","; 
  std::cout << "} "
  std::cout << i << " dim= " << H[i].S.dim << " " << G[0].cell->reduce(H[i].S.point)
  << " " << H[i].S.axis << H[i].next.size();
  for (int j:H[i].next)
  std::cout << " " << j ;
  std::cout << "\n";
  }
  //G = G8;
  }
  */
  /*
    template<class REAL>
    void find_point_subgroups(std::vector<array_group<matrix3<REAL> > > & groups,
    std::vector<vector3<REAL> > &cntrs,
    std::vector<int> & dims,
    const array_group<rotrans<REAL,false> > & G){}
  */

  /*
    template<class REAL>
    void find_point_subgroups1(std::vector<array_group<matrix3<REAL> > > & groups,
    std::vector<subspace3<REAL> > & subspaces,
    const array_group<rotrans<REAL,false> > & G){
    
    //std::vector<subspace3<REAL> > subspaces;
    std::vector<std::vector<rotrans<REAL,false> > > elements;

    //std::cout << "find_point_subs:\n";

    for (const auto & g : G.group){
    auto s = invariant_subspace(g);
    //std::cout << "g= " << g << " s= " << "(" << s.dim << "," << s.pt << "," << s.n << ")\n";
    add_subspace(subspaces,elements, s,{g});
    }

    //debug
    std::setprecision(4);
    std::cout << std::fixed;
    for (int i=0; i<subspaces.size(); i++)
    std::cout << i << " d= " << subspaces[i].dim << " pt= " << subspaces[i].point << " n= " << subspaces[i].axis
    << " ng= " << elements[i].size() << "\n";


    for (int i=0; i<subspaces.size(); i++)
    if ( subspaces[i].dim == 0)
    for (int j=0; j<subspaces.size(); j++)
    if (subspaces[j].within(subspaces[i].point))
    for (const auto & gg : elements[j])
    if ( std::find(elements[i].begin(),elements[i].end(),gg)
    == elements[i].end())
    elements[i].push_back(gg);

    //debug

    std::cout << "\n\n";
    for (int i=0; i<subspaces.size(); i++)
    std::cout << i << "d= " << subspaces[i].dim << " pt= "
    << subspaces[i].point << " n= " << subspaces[i].axis
    << " ng= " << elements[i].size() << "\n";

    /*
    for (int i=0; i<subspaces.size(); i++)
    {
    std::cout << "d= " << subspaces[i].dim << " pt= " << subspaces[i].pt << " n= " << subspaces[i].n;
    for (int j=0; j<elements[i].size(); j++)
    std::cout << elements[i][j];
    std::cout << "\n";
    }
    

    int nnew = 0, n = subspaces.size();
    bool contin = true;
    while (contin){
    int nnewnew = subspaces.size();
    for (int i=nnew; i<nnewnew; i++)
    if (subspaces[i].dim > 0)
    for (int j=0; j<n; j++)
    if (subspaces[j].dim > 0){
    add_subspace(subspaces,elements,
    subspaces[i] & subspaces[j], elements[i]);
    add_subspace(subspaces,elements,
    subspaces[i] & subspaces[j], elements[j]);
    }
    contin = nnewnew < subspaces.size();
    nnew = nnewnew;
    }

    /*
    std::vector<int> idx;
    for (int i=0; i<subspaces.size(); i++) idx.push_back(i);

    std::sort(idx.begin(), idx.end(),
    [&subspaces](int i, int j) -> bool
    { return subspaces[i].dim < subspaces[j].dim; }
    );
    reorder(subspaces,idx);
    reorder(elements, idx);
    
    for (int i=0; i<subspaces.size(); i++){
    groups.push_back(array_group<matrix3<REAL> >());
    for (int j=0; j<elements[i].size(); j++)
    groups[i].generate(elements[i][j].R);
    }

    /*
    for (int d=0; d<3; d++)
    for (int i=0; i<subspaces.size(); i++)
    if (subspaces[i].dim==d){
    cntrs.push_back(subspaces[i].point);
    dims.push_back(d);
    subs.push_back(array_group<matrix3<REAL> >());
    int n=subs.size()-1;
    for (int j=0; j<elements[i].size(); j++)
    groups[n].generate(elements[i][j].R);
    }
    
    }
  */
  /*
    template<class REAL>
    void find_point_subgroups(std::vector<array_group<matrix3<REAL> > > & groups,
    std::vector<subspace3<REAL> > & subspaces,
    const array_group<rotrans<REAL,true> > & G)
    {
    array_group<rotrans<REAL,false> > G1;
    G1.group.clear();
    for (const auto & x : G.group)
    G1.group.push_back(rotrans<REAL,false>(x.T,x.R));

    find_point_subgroups(groups,subspaces,G1);
    }
  */

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  template<class REAL>
  void py_find_cryst_symm1(array_group<rotrans<REAL,true> > & G,
                           geometry<REAL,periodic_cell<REAL> > & geom,
                           REAL R = geometry<REAL,periodic_cell<REAL>>
                           ::tol_geom_default)
  {  find_cryst_symm(G,geom,R); }

  template<class REAL>
  void py_find_cryst_symm2(genform_group<rotrans<REAL,true> > & G,
                           geometry<REAL, periodic_cell<REAL> > & geom,
                           REAL R = geometry<REAL,periodic_cell<REAL>>
                           ::tol_geom_default)
  { find_cryst_symm(G,geom,R); }

  template<class REAL>
  void py_find_point_subgroups(py::list & groups, py::list &subspaces,
			       const array_group<rotrans<REAL,true> >
			       & G){
    std::vector<array_group<matrix3<REAL> > >  vgroups;
    std::vector<subspace3<REAL> > vsubspaces;
    find_point_subgroups(vgroups,vsubspaces,G);
    for (int i = 0; i < vgroups.size(); i++){
      groups.append(vgroups[i]);
      subspaces.append(vsubspaces[i]);
    }
  }

  /*
    template<class REAL, bool BOUND>
    void py_find_point_subgroups2(py::list & subs,
    py::list &cntrs,
    py::list & dims,
    const array_group<rotrans<REAL,BOUND> >
    & G){
    std::vector<array_group<matrix3<REAL> > >  vsubs;
    std::vector<vector3<REAL> > vcntrs;
    std::vector<int> vdims;
    find_point_subgroups(vsubs,vcntrs,vdims,G);
    for (int i=0; i<vsubs.size(); i++){
    subs.append(vsubs[i]);
    cntrs.append(vcntrs[i]);
    dims.append(vdims[i]);
    }
    }
  */

  /*
    template<class REAL>
    void py_find_point_subgroups2(bp::list & subs, bp::list &cntrs,
    const array_group<rotrans<REAL,true> > & G)
    {
    std::vector<array_group<matrix3d<REAL> > >  vsubs;
    std::vector<vector3<REAL> > vcntrs;
    find_point_subgroups(vsubs,vcntrs,G);
    for (int i=0; i<vsubs.size(); i++)
    {
    subs.append(vsubs[i]);
    cntrs.append(vcntrs[i]);
    }
    }
  */

  template<class REAL>
  py::list py_find_translations( geometry<REAL,periodic_cell<REAL> > & g1,
                                 geometry<REAL,periodic_cell<REAL> > & g2,
                                 const periodic_cell<REAL> &cell,
                                 REAL R ){
    std::vector<vector3<REAL> > t;
    find_translations(t,g1,g2,cell,R);
    py::list res;
    for (const auto & tt : t)
      res.append(tt);
    return res;
  }


#endif

}

#endif
