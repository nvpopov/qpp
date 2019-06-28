#ifndef QPP_POINT_GROUPS_H
#define QPP_POINT_GROUPS_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

#include <geom/lace3d.hpp>
#include <symm/groups.hpp>
#include <symm/group_theory.hpp>
#include <symm/gen_cell.hpp>
#include <symm/shoenflis.hpp>
#include <symm/permut.hpp>
#include <io/geomio.hpp>
#include <cmath>

namespace qpp{

  // -----------------------------------------------------------------------

  template<class REAL, class CELL>
  bool equiv_geoms (std::vector<int> & ord,
                    const geometry<REAL,CELL> & g1,
                    const geometry<REAL,CELL> & g2,
                    REAL R = geometry<REAL,CELL>::tol_geom_default) {

    if (g1.nat() != g2.nat() )
      return false;

    int N = g1.nat();

    // fixme - inefficient for large molecules, N^2 scaling
    ord.clear();

    for (int i = 0; i < N; i++){
        bool found = false;
        for (int j = 0; j < N; j++)
          if ((g1.pos(i) - g2.pos(j)).squaredNorm() < R * R &&
              g1.atom(i) == g2.atom(j) &&
              std::find(ord.begin(), ord.end(),j) == ord.end() ){
              found = true;
              ord.push_back(j);
              break;
            }
        if (!found)
          return false;
      }

    return true;
  }

  // -----------------------------------------------------------------------

  template<class REAL, class CELL>
  bool equiv_geoms (const geometry<REAL,CELL> & g1,
                    const geometry<REAL,CELL> & g2,
                    REAL R = geometry<REAL,CELL>::tol_geom_default) {
    std::vector<int> ord;
    return equiv_geoms(ord,g1,g2,R);
  }

  // -----------------------------------------------------------------------

  template<class REAL>
  bool best_transform (matrix3<REAL> & res,
                       const std::vector<vector3<REAL> > &a,
                       const std::vector<vector3<REAL> > &b) {
    REAL eps = vector3<REAL>::tol_equiv;

    matrix3<REAL> C = matrix3<REAL>::Zero();
    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
        for (int k=0; k<a.size(); k++)
          C(i,j) += a[k](j)*b[k](i);

    matrix3<typename numeric_type<REAL>::complex> dv,
        SS( matrix3<typename numeric_type<REAL>::complex>::Zero());
    matrix3<REAL> D = C*C.transpose(), S(matrix3<REAL>::Zero());
    vector3<typename numeric_type<REAL>::complex> de;

    diagon3d(de,dv,D);

    for (int i=0; i<3; i++)
      if (std::abs(de(i))<eps)
        return false;

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
        for (int k=0; k<3; k++)
          SS(i,j) += std::conj(dv(i,k))*dv(j,k)/std::sqrt(de(k).real());

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
        S(i,j) = SS(i,j).real();

    res = S*C;
    return true;
  }

  // -----------------------------------------------------------------------

  template<class REAL>
  void best_axes(matrix3<REAL> & axes, vector3<REAL> & lambda,
                 const geometry<REAL, periodic_cell<REAL> > & g) {
    matrix3<REAL> S = matrix3<REAL>::Zero();

    for (int i=0; i<g.size(); i++)
      for (int j=0; j<3; j++)
        for (int k=0; k<3; k++)
          S(j,k) += g.pos(i)(j)*g.pos(i)(k);

    std::cout << "S= " << S << "\n";

    diagon3d(lambda,axes,S);
  }

  /*
  template<class REAL>
  void rotate_pair (matrix3<REAL> & R,
                    const vector3<REAL> & a1, const vector3<REAL> & a2,
                    const vector3<REAL> & b1, const vector3<REAL> & b2) {

    vector3<REAL> a3 = a1.cross(a2), b3 = b1.cross(b2);
    a3 *= std::sqrt(a1.norm()*a2.norm())/(a3.norm());
    b3 *= std::sqrt(b1.norm()*b2.norm())/(b3.norm());

    best_transform(R,{a1,a2,a3},{b1,b2,b3});

  }
  */

  // -----------------------------------------------------------------------
  /*
  template<class REAL>
  bool vector_pair_match(const vector3<REAL> & a1, const vector3<REAL> & a2,
                         const vector3<REAL> & b1, const vector3<REAL> & b2,
                         REAL R = geometry<REAL,periodic_cell<REAL>
                         >::tol_geom_default){
    REAL aa1 = a1.norm(), aa2 = a2.norm(),
        bb1 = b1.norm(), bb2 = b2.norm();

    if ( std::abs(aa1-bb1) > R || std::abs(aa2-bb2) > R )
      return false;

    if ( aa1 < R || aa2 < R)
      return true;

    REAL alp = std::acos(a1.dot(b1)/(aa1*bb1)), bet = std::acos(a2.dot(b2)
                                                                /(aa2*bb2)),
        alp1 = std::acos((aa1*aa1+bb1*bb1-R*R)/(2*aa1*bb1)),
        alp2 = std::acos((aa2*aa2+bb2*bb2-R*R)/(2*aa2*bb2));

    if ( std::abs(alp-bet) > alp1 + alp2 )
      return false;

    return true;
  }
  */
  // -----------------------------------------------------------------------
  /*
  template<class REAL>
  bool vector_triplet_match(const vector3<REAL> & a1,
                            const vector3<REAL> & a2,
                            const vector3<REAL> & a3,
                            const vector3<REAL> & b1,
                            const vector3<REAL> & b2,
                            const vector3<REAL> & b3,
                            REAL R = geometry<REAL,periodic_cell<REAL> >::tol_geom_default){
    matrix3<REAL> U;
    best_transform(U,{a1,a2,a3},{b1,b2,b3});
    return (U*a1-b1).norm() < R && (U*a2-b2).norm() < R && (U*a3-b3).norm() <R;
  }
  */
  // -----------------------------------------------------------------------

  template<class REAL>
  void analyze_transform (vector3<REAL> & axis, REAL & phi, bool & inversion,
                          const matrix3<REAL> & R) {

    REAL eps = matrix3<REAL>::tol_equiv;

    matrix3<REAL> R1 = R;
    inversion = R.determinant() < 0;
    if (inversion)
      R1 *= -1;

    matrix3<REAL> A = 0.5*(R1 - R1.transpose());
    REAL trace = R1(0,0) + R1(1,1) + R1(2,2);
    REAL cos = 0.5*(trace - 1);
    if (cos < REAL(-1)) cos = REAL(-1);
    if (cos > REAL(1))  cos = REAL(1);

    phi = std::acos(cos);

    axis(0) = -A(1,2);
    axis(1) =  A(0,2);
    axis(2) = -A(0,1);

    REAL nn = axis.norm();
    if (nn > eps)
      axis /= nn;
    else if (phi < eps)
      axis = {0,0,1};
    else
      {
        R1 += matrix3<REAL>::Identity();
        axis = R1.row(0);
        if (axis.norm() < R1.row(1).norm() )
          axis = R1.row(1);
        if (axis.norm() < R1.row(2).norm() )
          axis = R1.row(2);
        axis /= axis.norm();
      }

  }

  // -----------------------------------------------------------------------

  template<class REAL>
  void unitarize(matrix3<REAL> & U) {
    /*
    matrix3<REAL> S = U*U.transpose(), ss;
    vector3<REAL> sig;

    diagon3d(sig,ss,S);
    S=matrix3<REAL>(0);

    for(int i=0; i<3; i++)
      for (int j=0; j<3; j++)
  for (int k=0; k<3; k++)
    S(i,k) += ss(j,i)*ss(j,k)/std::sqrt(sig(j));

    U = S*U;
    */
    matrix3<REAL> S = U*U.transpose();
    U = S.pow(-0.5)*U;
  }

  // -----------------------------------------------------------------------

  template<class REAL>
  int pg_approx_find(const array_group<matrix3<REAL> > & G,
                     const matrix3<REAL> & M, REAL angle_error) {
    REAL norm_error = std::sqrt(8e0)*std::sin(0.5*angle_error);

    int i0;
    REAL err = infty;

    for (int i=0; i<G.size(); i++)
      if ( (G[i] - M).norm() < err ) {
          err = (G[i] - M).norm();
          i0 = i;
        }

    return (err > norm_error) ? -1 : i0;
  }

  // -------------------------------------------------------------

  template<class REAL>
  void pg_approx_multab(std::vector<std::vector<int> > & multab,
                        const array_group<matrix3<REAL> > & G,
                        REAL angle_error) {
    for (int i=0; i<G.size(); i++)
      for (int j=0; j<G.size(); j++)
        if (multab[i][j] == -1)
          multab[i][j] = pg_approx_find(G, matrix3<REAL>(G[i]*G[j]), angle_error);
  }

  // -------------------------------------------------------------

  template<class REAL>
  int pg_max_order(const array_group<matrix3<REAL> > & G,
                   REAL angle_error = 8*matrix3<REAL>::tol_equiv) {
    matrix3<REAL> E = matrix3<REAL>::Identity();
    matrix3<REAL> I = -E;
    int i0 = pg_approx_find(G,E,angle_error);
    int i1 = pg_approx_find(G,I,angle_error);

    REAL phi_min = 2 * REAL(pi);
    for (int i=0; i<G.size(); i++)
      if (i!=i0 && i!=i1) {
          vector3<REAL> ax;
          REAL phi;
          bool inv;
          analyze_transform(ax,phi,inv,G[i]);
          if (inv) phi = REAL(pi) - phi;
          if ( phi > angle_error && phi < phi_min)
            phi_min = phi;
        }

    int n = int(2*REAL(pi)/phi_min + 0.5);
    if (2 * REAL(pi) / n < angle_error)
      ValueError("pg_max_order : the principle axis roation angle is smaller than angle_error");
    return n;
  }


  // -------------------------------------------------------------------------------

  template <class REAL>
  void complete_point_group(array_group<matrix3<REAL> > & G,
                            std::vector<permutation> & P) {
    for (int i=0; i<P.size(); i++)
      for (int j=0; j<=i; j++){
          permutation p = P[i]*P[j];
          auto idx = std::find(P.begin(),P.end(),p);
          if (idx==P.end()){
              P.push_back(p);
              G.add(G[i]*G[j]);
            }
        }

  }

  // -------------------------------------------------------------------------------

  template<class REAL>
  void fix4_point_group(array_group<matrix3<REAL> > & G, const static_table<int> & M){
    int N = G.size();
    static_table<matrix3<REAL> > F(N,N);

    //std::cout << "fix4: alive 1\n";

    for (int i=0; i<N; i++)
      for (int j=0; j<N; j++){
          F(i,j) = G[i]*G[j] - G[M(i,j)];
          //std::cout << "Fij " << i << " " << j << " " << F(i,j) << "\n";
        }

    std::vector<matrix3<REAL> > Ginv(N);

    for (int j=0; j<N; j++){
        Ginv[j] = G[j].inverse();
        //std::cout << j << " inv " << Ginv[j] << "\n";
      }

    //std::cout << "fix4: alive 2\n";

    std::vector<matrix3<REAL> > Di(N);
    for (int i=0; i<N; i++){

        //std::cout << "Di " << i << "\n";

        matrix3<REAL> D(REAL(0));
        for (int j=0; j<N; j++)
          D += Ginv[j]*F(j,i) + F(i,j)*Ginv[j];
        D /= 2*N;
        Di[i] = D;

        //std::cout << i << " Di " << Di[i] << "\n";

      }

    //std::cout << "fix4: alive 3\n";

    for (int i=0; i<N; i++){

        //std::cout << "unitarize " << i << "\n";

        G[i] = G[i] - Di[i];

        //std::cout << "new Gi " << i << " " << G[i] << "\n";

        unitarize(G[i]);

        //std::cout << "unitarized "  << G[i] << "\n";
      }
    //std::cout << "fix4: alive 4\n";
  }

  // -------------------------------------------------------------------------------

  template<class REAL>
  void reconstruct_point_group(array_group<matrix3<REAL> > & G, const static_table<int> & M){

    int maxit = 100;
    int N = G.size();
    int it = 0;
    REAL eps = matrix3<REAL>::tol_equiv*N;
    REAL err;

    //std::cout << "Befor cycle\n";

    while (true) {

        /*
      std::cout << "multab:\n";
      for (int i=0; i<N; i++){
  std::cout << i << "[";
  for (int j=0; j<N; j++)
    std::cout << M(i,j)<< ",";
  std::cout << "]\n";
      }
      */

        err = REAL(0);
        for (int i=0; i<N; i++)
          for (int j=0; j<N; j++){

              //std::cout << "Sij calc " << i << " " << j << "\n";

              matrix3<REAL> F = G[i]*G[j]-G[M(i,j)];
              REAL s(0);
              for (int k=0; k<3; k++)
                for (int l=0; l<3; l++)
                  s += F(k,l)*F(k,l);
              err += s;
            }
        err = std::sqrt(err);

        std::cout << "fix_point_group: iteration = " << it << " error = " << err << "\n";

        if (err < eps) break;
        fix4_point_group(G,M);

        if (++it > maxit) OverflowError("Too many iterations in fix_point_group");

        //break;
      }

  }

  // -------------------------------------------------------------------------------

  template<class REAL>
  STRING_EX point_group_symbol(const array_group<matrix3<REAL> > & G)
  {
    group_analyzer<matrix3<REAL>, array_group<matrix3<REAL> > > A(G);

    // Define the maximum order
    int maxord=1;
    for (int i=0; i<G.size(); i++){
      if (A.order(i)>maxord)
  maxord=A.order(i);
    }
    std::vector<STRING_EX> cand_groups = shnfl<REAL>::groups_by_order(maxord);

    for (int i=cand_groups.size()-1; i>=0; i--)
      {
  //std::cout << cand_groups[i] << " " << shnfl<REAL>::group(cand_groups[i]).size() << "\n";
  if (shnfl<REAL>::group(cand_groups[i]).size() != G.size() )
    cand_groups.erase(cand_groups.begin()+i);
      }

    REAL fpeps = matrix3<REAL>::tol_equiv*G.size();

    typename shnfl<REAL>::fingerprint FG(G,fpeps);
    bool found = false;
    STRING_EX res = "";

    for (const STRING_EX &s:cand_groups)
      if ( typename shnfl<REAL>::fingerprint(shnfl<REAL>::group(s),fpeps)
     .compare(FG, fpeps) )
  {
    found = true;
    res = s;
    break;
  }
    return res;
  }

  // -------------------------------------------------------------------------------

  template<class REAL>
  void find_point_symm(array_group<matrix3<REAL> > & G,
                       const geometry<REAL, periodic_cell<REAL> > & geom,
                       vector3<REAL> &new_centre,
                       REAL R = geometry<REAL,periodic_cell<REAL> >::tol_geom_default) {
    if (geom.nat() == 0)
      return;

    if (geom.nat() == 1) {
        G = shnfl<REAL>::Oh();
        G.name = "SO3";
        return;
      }

    // make a copy of geometry
    geometry<REAL, periodic_cell<REAL> > g(geom);

    // find geometric centre
    vector3<REAL> cntr(0);

    // subtract the coordinates of centre
    for (int i = 0; i < g.nat(); i++)
      cntr += g.coord(i);
    cntr /= g.nat();

    new_centre = cntr;

    for (int i = 0; i < g.nat(); i++)
      g.change(i, g.atom(i), g.coord(i) - cntr);

    // Check if molecule is linear or planar

    bool linear = true, planar = true;
    vector3<REAL> lmb, naxis, nplane;
    matrix3<REAL> axes;

    best_axes(axes,lmb,g);

    std::cout << "lmb= " << lmb << " axes= " << axes << "\n";

    naxis = axes.col(2);
    std::cout << " linaxis = " <<  naxis << "\n";

    for (int i=0; i<g.nat(); i++) {
        vector3<REAL> r = g.pos(i);

        std::cout << "i= " << i << " r= " << r << " r*n= " << naxis.dot(r)
                  << " r-n(r*n) = " << r - naxis*naxis.dot(r) << "\n";

        if ( (r - naxis*naxis.dot(r)).norm() > R ) {
            linear = false;
            break;
          }
      }

    nplane = axes.col(0);

    std::cout << " planaxis = " <<  nplane << "\n";

    for (int i=0; i<g.nat(); i++) {
        vector3<REAL> r = g.pos(i);
        if ( nplane.dot(r) > R ) {
            planar = false;
            break;
          }
      }

    if (linear) {

        matrix3<REAL> U = axes;
        matrix3<REAL> U2 = RotMtrx(nplane,REAL(pi));
        geometry<REAL, periodic_cell<REAL> > g1(g);
        for (int i=0; i<g.size(); i++)
          g1.coord(i) = U2*g.coord(i);

        bool dnh = equiv_geoms(g,g1,R);

        if (dnh){
            G = shnfl<REAL>::Dnh(4);
            G.name = "D_inf_h";

            std::cout << "linear molecule with Dh\n";
          }
        else{
            G = shnfl<REAL>::Cnv(4);
            G.name = "C_inf_v";

            std::cout << "linear molecule with Cv\n";
          }

        for (int j=0; j < G.size(); j++)
          G[j] = U*G[j]*U.transpose();
        return;
      }

    if (planar){
        // add two reference points on both sides of the symmetry plane
        REAL h = std::sqrt(lmb[2]/g.nat());
        g.add("refpoint",  nplane*h);
        g.add("refpoint", -nplane*h);

        std::cout << "Planar molecule\n";
      }

    // sort atoms in reverse order by the distance from centre
    g.sort(
          [](const geometry<REAL> & gg, int ii)->REAL
    {return -gg.pos(ii).norm();}
    );

    //std::cout << g.pos(0).norm() << " " << g.pos(g.nat()-1).norm() << "\n";

    write_xyz(std::cout,g);
    std::cout << "centre: " << cntr << "\n";

    // estimate maximum angle error during the fit
    REAL angle_error = 2*std::asin(R/(g.pos(0).norm())), theta;

    // find the pair of non-collinear atoms with largest distances to centre
    int i,j;
    vector3<REAL> ri, rj;

    bool found = false;

    for (j=1; j<g.nat() && g.pos(j).norm()>R; j++)
      for (i=0; i<j; i++){

          ri = g.pos(i);
          rj = g.pos(j);

          REAL cos_t = (g.pos(i).dot(g.pos(j))) /
                       (g.pos(i).norm() * g.pos(j).norm());
          if ( cos_t < REAL(-1) )
            cos_t = -REAL(1);
          if (cos_t > REAL(1) )
            cos_t = REAL(1);

          theta = std::acos(cos_t);

          if ( theta > angle_error && theta < REAL(pi) - angle_error ){
              found = true;
              goto FOUND;
            }
        }
FOUND:
    if (!found)
      return;

    // form the lists of possible images for i-th and j-th atoms
    std::vector<int> img_i, img_j;
    REAL Ri = ri.norm(), Rj = rj.norm();

    for (int k = 0; k<g.nat(); k++){
        REAL Rk = g.pos(k).norm();
        if ( Ri+R > Rk && Rk > Ri-R && g.atom(i)==g.atom(k) )
          img_i.push_back(k);
        if ( Rj+R > Rk && Rk > Rj-R && g.atom(j)==g.atom(k) )
          img_j.push_back(k);

        if ( Rk <= Ri-R && Rk <= Rj-R )
          break;
      }

    /*
    std::cout << "img1= ";
    for (auto k:img_i) std::cout << " "<< k;
    std::cout << "\n";
    std::cout << "img2= ";
    for (auto k:img_j) std::cout << " "<< k;
    std::cout << "\n";
    */

    // initialize permutations array to have the group in atom permutations form
    // for further 'finitiztion'

    geometry<REAL, periodic_cell<REAL> > g1(g);
    std::vector<permutation> P;
    P.push_back(permutation(g.nat()));

    //P[0].print();

    // try all possible transormations turning i -> i1, j -> j1,
    // where i1 belongs to img_i and j1 belongs to img_j

    for (int i1 : img_i)
      for (int j1 : img_j){
          vector3<REAL> ri1 = g.pos(i1), rj1 = g.pos(j1);

          REAL cos_t1 = (ri1.dot(rj1))/(ri1.norm()*rj1.norm());
          if ( cos_t1 < -REAL(1) )
            cos_t1 = -REAL(1);
          if (cos_t1 > REAL(1) )
            cos_t1 = REAL(1);

          REAL theta1 = std::acos(cos_t1);
          if ( std::abs(theta - theta1) >= angle_error  )
            continue;

          matrix3<REAL> U;
          best_transform(U, {ri, rj, ri.cross(rj)/sqrt(Ri * Rj)},
          {ri1, rj1, ri1.cross(rj1)/sqrt(ri1.norm() * rj1.norm())});

          for (int k = 0; k < g.nat(); k++)
            g1.coord(k) = U * g.coord(k);

          std::vector<int> pp;
          if (equiv_geoms(pp,g,g1,R))
            if (std::find(P.begin(),P.end(),permutation(pp)) == P.end())
              {
                P.push_back(permutation(pp));
                G.add(U);

                /*
    std::cout << permutation(pp).to_string();
                std::cout << "\n";
    */
              }

          best_transform(U,{ri,rj,ri.cross(rj)/sqrt(Ri*Rj)},
          {ri1,rj1,-(ri1.cross(rj1))/sqrt(ri1.norm()*rj1.norm())});

          for (int k = 0; k<g.nat(); k++)
            g1.coord(k) = U*g.coord(k);

          if (equiv_geoms(pp,g,g1,R))
            if (std::find(P.begin(),P.end(),permutation(pp))==P.end())
              {
                P.push_back(permutation(pp));
                G.add(U);

                /*
    std::cout << permutation(pp).to_string();
                std::cout << "\n";
    */
              }
        }

    // Construct possibly missing elements
    complete_point_group(G, P);

    // Construct multiplication table
    group_analyzer<permutation> AP(P);

    // Correct point group according to the multiplication table

    reconstruct_point_group(G,AP.multab);

    STRING_EX Gname = point_group_symbol(G);

    std::cout << " group= " << Gname << " found= " << found << "\n";

    G.name = Gname;

  }


  //----------------------------------------------------

  template<class REAL>
  struct point_group_axes{

      vector3<REAL> center;
      bool inversion;

      int naxes, nplanes;
      std::vector<vector3<REAL> > axes, planes;
      std::vector<int> orders;
      std::vector<Bool> rotoinversion;

      point_group_axes(){}

      point_group_axes(const point_group_axes & A):
        center(A.center), inversion(A.inversion), naxes(A.naxes), nplanes(A.nplanes),
        axes(A.axes), planes(A.planes), orders(A.orders), rotoinversion(A.rotoinversion)
      {}

      point_group_axes(const array_group< matrix3<REAL> > & G){
        inversion = false;
        REAL eps = matrix3<REAL>::tol_equiv;
        REAL epscos = std::sqrt(eps);
        std::vector<std::vector<int> > same_ax;

        int N = G.size();
        std::vector<REAL> phi(N);
        std::vector<vector3<REAL> > n(N);
        std::vector<Bool> inv(N);

        for (int i = 0; i<G.size(); i++)
          analyze_transform(n[i], phi[i], inv[i],G[i]);

        for (int i = 0; i<G.size(); i++){
            if (phi[i] < epscos){
                if (inv[i])
                  inversion = true;
                continue;
              }

            bool found = false;
            for (int j=0; j < axes.size(); j++)
              if ( ((n[i]-axes[j]).norm() < eps) || ((n[i]+axes[j]).norm() < eps) ) {
                  found = true;
                  same_ax[j].push_back(i);
                }
            if (!found ) {
                axes.push_back(n[i]);
                same_ax.push_back({i});
              }
          }

        /*
      std::cout << axes.size() << " " << same_ax.size() << "\n";
      for (int i=0; i<axes.size(); i++){
  std::cout << i << axes[i];
  for (int j=0; j<same_ax[i].size(); j++)
    std::cout << same_ax[i][j] << " ";
  std::cout << "\n";
      }
      */

        // find and separate mirror planes
        for (int i=axes.size()-1; i>=0; i--){
            bool pln = false;
            for (int j : same_ax[i])
              if ( REAL(pi) - phi[j] < epscos && inv[j]  ) {
                  pln = true;
                  break;
                }
            if (pln) {
                planes.push_back(axes[i]);
                for (int j = same_ax[i].size()-1; j>=0; j--)
                  if (inv[same_ax[i][j]])
                    same_ax[i].erase(same_ax[i].begin()+j);
              }
            if (same_ax[i].size()==0){
                same_ax.erase(same_ax.begin()+i);
                axes.erase(axes.begin()+i);
              }
          }

        nplanes = planes.size();
        naxes = axes.size();
        rotoinversion.resize(naxes);
        orders.resize(naxes);

        for (int i=0; i<axes.size(); i++){

            std::sort(same_ax[i].begin(), same_ax[i].end(),
                      [&phi,&inv] (int i1, int i2) -> bool
            { return (inv[i1]? REAL(pi)-phi[i1]:phi[i1]) < (inv[i2]? REAL(pi)-phi[i2]:phi[i2]); }
            );
            /*
  std::cout << "axes " << i << "\n";
  for (int j=0; j<same_ax[i].size(); j++)
    std::cout << same_ax[i][j] << " ";
  std::cout << "\n";
  */
            int j = same_ax[i][0];
            rotoinversion[i] = inv[j];

            orders[i] = int( 2*REAL(pi)/( inv[j]? REAL(pi)-phi[j] : phi[j] ) + 0.5 );
          }
      }

  };

  // ----------------------------------------------------------------------------------------

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  template<class REAL>
  bool py_best_transform( matrix3<REAL> & res,
                          const py::list &A, const py::list &B){
    std::vector<vector3<REAL> > a,b;

    if (py::len(A) != py::len(B))
      IndexError("find_rotation:: different number of items int two lists");

    //TODO: There are grows potential type casting error: convert to/from
    // vector3 and python types via py::cast
    for (int i=0; i<py::len(A); i++){
        vector3<REAL> r;
        if (py::isinstance<vector3<REAL> >(A[i]))
          r = py::cast<vector3<REAL> >(A[i]);
        /*else if (py::isinstance<py::tuple>(A[i]))
          r = vector3<REAL>(py::cast<py::tuple>(A[i]));
        else if (py::isinstance<py::list>(A[i]))
          r = vector3<REAL>(py::cast<py::list>(A[i]));*/
        else
          TypeError("find_rotation: invalid (not vector3) item in A list");
        a.push_back(r);

        if (py::isinstance<vector3<REAL> >(B[i]))
          r = py::cast<vector3<REAL> >(B[i]);
        /*else if (py::isinstance<py::tuple>(B[i]))
          r = vector3<REAL>(py::cast<py::tuple>(B[i]));
        else if (py::isinstance<py::list>(B[i]))
          r = vector3<REAL>(py::cast<py::list>(B[i]));*/
        else
          TypeError("find_rotation: invalid (not vector3) item in B list");
        b.push_back(r);
      }

    for (int i=0; i<a.size(); i++)
      std::cout << a[i] << " -> " << b[i] << "\n";

    return best_transform(res,a,b);

  }

  template<class REAL>
  py::list py_analyze_transform(const matrix3<REAL> & R){
    vector3<REAL> axis;
    REAL phi;
    bool inversion;
    analyze_transform(axis,phi,inversion,R);

    py::list res;
    res.append(axis);
    res.append(phi);
    res.append(inversion);

    return res;
  }

  template<class REAL>
  void py_reconstruct_point_group(array_group<matrix3<REAL> > & G, const py::list & M){
    int N = G.size();
    static_table<int> multab(N,N);
    if (py::len(M)!=N)
      IndexError("Wrong multiplication table size in fix_point_group");
    for (int i=0; i<N; i++){
        if (!py::isinstance<py::list>(M[i]))
          TypeError("Bad multiplication table in fix_point_group");
        py::list L = py::cast<py::list>(M[i]);
        if (py::len(L)!=N)
          IndexError("Wrong multiplication table size in fix_point_group 1");
        for (int j=0; j<N; j++){
            /*
  if (!py::isinstance<int>(L[j]))
    TypeError("Bad multiplication table in fix_point_group 1");
  */
            multab(i,j) = py::cast<int>(L[j]);
          }

      }

    reconstruct_point_group(G,multab);
  }


#endif

};

#endif
