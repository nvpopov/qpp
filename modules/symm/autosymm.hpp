#ifndef QPP_AUTOSYMM_H
#define QPP_AUTOSYMM_H

#include <geom/geom.hpp>
#include <geom/ngbr.hpp>
#include <symm/cell.hpp>
#include <symm/gcell.hpp>
#include <symm/transform.hpp>
#include <symm/group_theory.hpp>
//#include <symm/spgw.hpp>
#include <data/compiler_fallback.hpp>
#include <Eigen/Dense>
#include <algorithm>
#include <iomanip>

#ifdef PY_EXPORT
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#endif

namespace qpp{

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

  template<class REAL, class CELL>
  bool equiv_geoms (const geometry<REAL,CELL> & g1,
                    const geometry<REAL,CELL> & g2,
                    REAL R = geometry<REAL,CELL>::tol_geom_default) {
    std::vector<int> ord;
    return equiv_geoms(ord,g1,g2,R);
  }

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

    for (int i=0; i<geom.nat(); i++){
        int found = 0;

        //std::cout << "atom " << i;

        for (int j=0; j<ngbr.n(i); j++){
            index J = ngbr(i,j);
            //std::cout << " " << J;

            if ( geom.atom(i) == geom.atom(J) &&
                 J != index::D(symm.DIM).atom(J(0))){
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

  template<class REAL>
  bool best_transform (matrix3<REAL> & res,
                       const std::vector<vector3<REAL> > &a,
                       const std::vector<vector3<REAL> > &b) {
    REAL eps = tol_equiv;

    matrix3<REAL> C = matrix3<REAL>::Zero();
    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
        for (int k=0; k<a.size(); k++)
          C(i,j) += a[k](j)*b[k](i);

    //std::cout << "C matrix= " << C << "\n";

    matrix3<typename numeric_type<REAL>::complex> dv,
        SS( matrix3<typename numeric_type<REAL>::complex>::Zero());
    matrix3<REAL> D = C*C.transpose(), S(matrix3<REAL>::Zero());
    vector3<typename numeric_type<REAL>::complex> de;

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
  void rotate_pair (matrix3<REAL> & R,
                    const vector3<REAL> & a1, const vector3<REAL> & a2,
                    const vector3<REAL> & b1, const vector3<REAL> & b2) {

    vector3<REAL> a3 = a1.cross(a2), b3 = b1.cross(b2);
    a3 *= std::sqrt(a1.norm()*a2.norm())/(a3.norm());
    b3 *= std::sqrt(b1.norm()*b2.norm())/(b3.norm());

    best_transform(R,{a1,a2,a3},{b1,b2,b3});

  }

  template<class REAL>
  void analyze_transform (vector3<REAL> & axis, REAL & phi, bool & inversion,
                          const matrix3<REAL> & R) {

    REAL eps = tol_equiv;
    vector3<typename numeric_type<REAL>::complex> e, nax;
    matrix3<typename numeric_type<REAL>::complex> n;
    typename numeric_type<REAL>::complex I(0,1);

    inversion = R.determinant() < 0;
    matrix3<REAL> R1 = matrix3<REAL>::Zero();
    if (inversion) R1 = matrix3<REAL>::Identity()*-1*R;
    else matrix3<REAL>::Identity()*R;

    int i1=0,i2=0;
    for (int i=0; i<3; i++){
        if ( e[i].imag() < e[i1].imag() )
          i1 = i;
        if ( e[i].imag() > e[i2].imag() )
          i2 = i;
      }

    int i0 = 3 - i1 - i2;

    // std::cout << " i0, i1, i2= " << i0 << " " << i1 << " " << i2 << " eigvals= " << e << "\n";

    if (i1==i2){
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

    nax = n.row(i0);

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

    matrix3<REAL> _m1 = RotMtrx<REAL>(axis,phi);
    matrix3<REAL> _m2 = RotMtrx<REAL>(-axis,phi);

    if ( (R1-_m1).norm() > (R1-_m2).norm() )
      axis *= -REAL(1);
  }



  // ------------------------------------------------------
  class permutation{

      std::vector<int> p;

    public:

      int N;

      //static permutation unity;

      permutation(int _N){
        N = _N;
        for (int i=0; i<N; i++)
          p.push_back(i);
      }

      permutation(const permutation & b){
        //std::cout << "copy constructor\n";
        N = b.N;
        for (int i : b.p)
          p.push_back(i);
      }

      permutation(const std::vector<int> & li){
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

      inline permutation operator*(const permutation & b) const{
        /*
    print();
    std::cout << "*";
    b.print();
    std::cout << "\n";
      */
        if (N != b.N) IndexError("Permutations have different dimensions");
        permutation res(N);
        for (int i=0; i<N; i++) res[i] = p[b[i]];
        return res;
      }

      inline bool operator== (const permutation & b) const {

        if (N!=b.N) return false;
        bool res=true;
        for (int i=0; i<N; i++)
          if (p[i] != b[i]) {
              res = false;
              break;
            }
        return res;

      }

      inline bool operator!= (const permutation & b) const {
        return ! ((*this) == b);
      }

      int order () {
        int n=1;
        permutation P = (*this)*(*this);
        while (*this != P) n++;
        return n;
      }

      void print () const {
        std::cout << "(";
        for (int i:p) std::cout << i << " ";
        std::cout <<")";
      }

  };

  // -------------------------------------------------------------

  template <class REAL>
  struct linear3d_subspace {

      int dim;
      vector3<REAL> pt, n;

      linear3d_subspace (int __dim, const vector3<REAL> & __pt,
                         const vector3<REAL> & __n = vector3<REAL>(0)) {
        dim = __dim;
        pt = __pt;
        n = __n.normalized();
      }

      bool within (const vector3<REAL> & x) const {
        if (dim == -1) return false;
        else if (dim == 0)
          return (pt - x).norm() < tol_equiv;
        else if (dim == 1) {
            vector3<REAL> y = x - pt;
            y = y - n*(y.dot(n));
            return y.norm() < tol_equiv;
          }
        else if (dim == 2){
            vector3<REAL>  y = x - pt;
            return std::abs(y.dot(n)) < tol_equiv;
          }
        else if (dim == 3)
          return true;
      }

      bool operator== (const linear3d_subspace<REAL> & L ) const {
        if (L.dim != dim)
          return false;
        if (dim == 0)
          return (pt-L.pt).norm() < tol_equiv;
        else if ( dim == 1 or dim == 2)
          return ((n-L.n).norm() < tol_equiv ) and within(L.pt);
        else if (dim == -1 or dim == 3)
          return true;
      }

      bool operator!= (const linear3d_subspace<REAL> & L ) const {
        return !(*this == L);
      }

      linear3d_subspace<REAL> operator& (const linear3d_subspace<REAL> & L) const {

        int d1,d2;
        vector3<REAL> p1,p2,n1,n2;

        if ( dim > L.dim ){
            d1 = dim; d2 = L.dim;
            p1 = pt;  p2 = L.pt;
            n1 = n;   n2 = L.n;
          }
        else{
            d1 = L.dim; d2 = dim;
            p1 = L.pt;  p2 = pt;
            n1 = L.n;   n2 = n;
          }

        if (d1 == 3)
          return linear3d_subspace<REAL>(d2,p2,n2);

        if (d2 == -1)
          return linear3d_subspace<REAL>(-1,vector3<REAL>(0,0,0));

        if  (d2 == 0){
            if ( linear3d_subspace(d1,p1,n1).within(p2) )
              return linear3d_subspace<REAL>(0,p2);
            else
              return linear3d_subspace<REAL>(-1,vector3<REAL>(0,0,0));
          }

        if ( d1 == 1 and d2 == 1) {
            if ((n1-n2).norm() < tol_equiv or (n1+n2).norm() < tol_equiv) {
                if (linear3d_subspace<REAL>(d1,p1,n1).within(p2))
                  return *this;
                else
                  return linear3d_subspace<REAL>(-1,vector3<REAL>(0,0,0));
              }
            else if (std::abs((p2-p1).dot(n1.cross(n2))) < tol_equiv) {
                REAL s = n1.dot(n2);
                REAL x1 = ((n1 - s*n2).dot(p2-p1))/(1-s*s);
                return linear3d_subspace<REAL>(0,p1+x1*n1);
              }
            else
              return linear3d_subspace<REAL>(-1,vector3<REAL>(0,0,0));
          }

        if (d1 == 2 and d2 == 1) {
            if (std::abs(n1.dot(n2)) < tol_equiv){
                if (std::abs(n1.dot(p2-p1)) < tol_equiv)
                  return linear3d_subspace<REAL>(1,p2,n2);
                else
                  return linear3d_subspace<REAL>(-1,vector3<REAL>(0,0,0));
              }
            else
              return  linear3d_subspace(0,p2+n2*n1.dot(p1-p2)/n1.dot(n2));
          }

        if (d1 == 2 and d2 == 2) {
            if ((n1-n2).norm() < tol_equiv or (n1+n2).norm() < tol_equiv){
                if (std::abs(n1.dot(p1-p2)) < tol_equiv)
                  return *this;
                else
                  return linear3d_subspace<REAL>(-1,vector3<REAL>(0,0,0));
              }
            else {
                REAL s = n1.dot(n2);
                vector3<REAL> nn = n1.cross(n2);
                REAL x1 = (p1.dot(n1)-s*p2.dot(n2))/(1-s*s);
                REAL x2 = (p2.dot(n2)-s*p1.dot(n1))/(1-s*s);
                return linear3d_subspace<REAL>(1,x1*n1+x2*n2,nn);
              }
          }
      }

  };

  // -------------------------------------------------------------

  template<class CMPLX>
  vector3<typename numeric_type<CMPLX>::real> vecreal(
      const vector3<CMPLX> & v){
    return vector3<typename numeric_type<CMPLX>::real>(v(0).real(),
                                                       v(1).real(), v(2).real() );
  }

  // -------------------------------------------------------------

  template<class REAL>
  std::optional<linear3d_subspace<REAL> > invariant_subspace(const rotrans<REAL,false> & R){
    matrix3<typename numeric_type<REAL>::complex> n;
    vector3<typename numeric_type<REAL>::complex> lmb;
    diagon3d(lmb,n,R.R);

    vector3<typename numeric_type<REAL>::complex>
        T(R.T[0],R.T[1],R.T[2]),
        t(n.row(0).dot(T), n.row(1).dot(T), n.row(2).dot(T)),
        x(0,0,0);

    int d = 0, ni[3];

    for (int i=0; i<3; i++)
      if (abs(lmb[i]-REAL(1)) < tol_equiv) {
          if (abs(t[i]) < tol_equiv) {
              ni[d] = i;
              d++;
            }
          else return std::optional<linear3d_subspace<REAL> >({ -1, vector3<REAL>(0,0,0) });
        }
      else
        x[i] = t[i]/(REAL(1)-lmb[i]);

    vector3<typename numeric_type<REAL>::complex> c =
        x[0]*n.row(0)+x[1]*n.row(1)+x[2]*n.row(2);
    vector3<REAL> rc = vecreal(c);

    if (d==0)
      return std::optional<linear3d_subspace<REAL> >({ 0, rc});
    else if (d==1)
      return std::optional<linear3d_subspace<REAL> >({ 1, rc,
                                     vecreal<typename numeric_type<REAL>::complex>(n.row(ni[0])) });
    else if (d==2)
      return std::optional<linear3d_subspace<REAL> >({ 2, rc,
                                     vecreal<typename numeric_type<REAL>::complex>(
                                       n.row(ni[0]).cross(n.row(ni[1]))) });
    else if (d==3)
      return std::optional<linear3d_subspace<REAL> >({ 3, rc});

    return std::nullopt;
  }


  // -------------------------------------------------------------

  template <class REAL>
  void add_subspace(std::vector<linear3d_subspace<REAL> > & subspaces,
                    std::vector<std::vector<rotrans<REAL,false> > > &elements,
                    const linear3d_subspace<REAL> &s,
                    const std::vector<rotrans<REAL,false> > &g){
    int i=0;
    while (i<subspaces.size() && subspaces[i] != s) i++;

    //std::cout << "i= " << i << "\n";

    if (i<subspaces.size())
      for (const auto & gg : g){
          if ( std::find(elements[i].begin(),elements[i].end(),gg) ==
               elements[i].end() )
            elements[i].push_back(gg);
        }
    else if (s.dim > -1){
        subspaces.push_back(s);
        elements.push_back(g);
      }
  }

  // -------------------------------------------------------------

  template <class REAL>
  void finitize_point_group(std::vector<matrix3<REAL> > & G,
                            std::vector<permutation> P, REAL delta){
    // find and appropriately place unity element
    int N = G.size();
    int i0;
    for (i0=0; i0<G.size(); i0++) {
        bool thatsit=true;
        for (int j=0; j<P[i0].N; j++)
          if (P[i0][j]!=j){
              thatsit=false;
              break;
            }
        if (thatsit) break;
      }
    if (i0!=0){
        std::swap(G[0],G[i0]);
        std::swap(P[0],P[i0]);
      }

    // Construct multiplication table and element orders

    group_analyzer<permutation> A(P);

    // Analyze group operations

    std::vector<vector3<REAL> > axis(N);
    std::vector<REAL> phi(N);
    std::vector<char> inv(N);
    std::vector<int> pow(N), dnm(N);

    int inversion = -1;

    for (int i=0; i<N; i++) {
        analyze_transform(axis[i],phi[i],*((bool*)&inv[i]),G[i]);
        if (A.order(i)==2 && inv[i] && phi[i] < pi/2)
          inversion = i;
      }

    std::vector<std::vector<int> > same_axis;

    for (int i=1; i<N; i++) {
        if (i==inversion) continue;
        bool found = false;
        for (int j=0; j<same_axis.size(); j++) {
            if ( (axis[i]+axis[same_axis[j][0]]).norm() < delta ) {
                axis[i] = -axis[i];
                phi[i]  = -phi[i];
              }
            if ( (axis[i]-axis[same_axis[j][0]]).norm() < delta ||
                 (axis[i]+axis[same_axis[j][0]]).norm() < delta) {
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
      if (j==inversion) phi[j] = REAL(0);
      else {
          //std::cout << j << " before " << phi[j];
          int k = round(phi[j]*A.order(j)/(2*pi));
          phi[j] = REAL(pi)*2*k/A.order(j);
          //std::cout << " after " << phi[j] << "\n";
        }

    // Correcting axes

    REAL eps = tol_equiv;
    std::vector<vector3<REAL> > exact_axis(M);

    if (M>1) {

        Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic>  S(M,M);

        for (int i=0; i<M; i++)
          for (int j=0; j<=i; j++)
            if (i==j) S(i,j)=1;
            else {
                int i1 = same_axis[i][0], j1 = same_axis[j][0];
                int k1 = A.multab(i1,j1);

                S(i,j) = S(j,i) =
                    (std::cos(phi[i1]/2)*std::cos(phi[j1]/2) -
                     std::cos(phi[k1]/2))/
                    (std::sin(phi[i1]/2)*std::sin(phi[j1]/2));

                if (S(i,j)*(axis[i1].dot(axis[j1]))<0)
                  S(i,j) = S(j,i) = -S(i,j);

                /*
                  std::cout << i1 << "(phi= " << phi[i1] << " n= " << axis[i1] << " r= " << bool(inv[i1]) << ")* "
                  << j1 << "(phi= " << phi[j1] << " n= " << axis[j1] << " r= " << bool(inv[j1]) << ") -> "
                  << k1 << "(phi= " << phi[k1] << " n= " << axis[k1] << " r= " << bool(inv[k1]) << ") S0= "
                  << scal(axis[i1],axis[j1]) << " S1= " << S(i,j) << "\n";

                std::cout << i << ","  << j << " S0= "
                          << scal(axis[i1],axis[j1]) << " S1= " << S(i,j) << "\n";
                */
                //break;
              }

        exact_axis[0] = {0,0,1};
        exact_axis[1] = {std::sqrt(1-S(0,1)*S(0,1)), 0, S(0,1)};

        for (int i=2; i<M; i++){
            vector3<REAL> n;
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

            if ( jy<i && std::abs((n.dot(exact_axis[jy]))-S(i,jy))>eps)
              n.y() *= -1;

            exact_axis[i] = n;
          }

        // Finding the rotation

        std::vector<vector3<REAL> > p0,p1;

        for (int i=0; i<M; i++)
          for (int j:same_axis[i]) {
              p0.push_back(exact_axis[i]);
              p1.push_back(axis[j]);
            }

        bool complanar = true;
        for (int i=2; i<M; i++)
          if (std::abs(matrix3<REAL>(exact_axis[0], exact_axis[1], exact_axis[i]).determinant()) > eps ){
              complanar = false;
              break;
            }

        if (complanar) {
            p0.push_back(exact_axis[0].cross(exact_axis[1]));
            p1.push_back(axis[same_axis[0][0]].cross(axis[same_axis[1][0]]));
          }

        matrix3<REAL> U;
        best_transform(U,p0,p1);
        for (int i=0; i<M; i++)
          exact_axis[i] = U*exact_axis[i];

      }
    else {
        exact_axis[0] = vector3<REAL>::Zero();
        for (int i : same_axis[0]) exact_axis[0] += axis[i];
        exact_axis[0] /= (exact_axis[0]).norm();
      }

    // Reconstruct the group
    G.clear();
    G.push_back(gen_matrix<REAL>(1));
    if (inversion>=0) G.push_back(gen_matrix<REAL>(-1));

    for (int i=0; i<M; i++)
      for (int j:same_axis[i]) {
          if (inv[i]) G.push_back(RotMtrx(exact_axis[i],phi[j])*gen_matrix<REAL>(-1));
          else G.push_back(RotMtrx(exact_axis[i],phi[j])*gen_matrix<REAL>(1));
        }


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

  template<class REAL>
  bool vector_triplet_match(const vector3<REAL> & a1,
                            const vector3<REAL> & a2,
                            const vector3<REAL> & a3,
                            const vector3<REAL> & b1,
                            const vector3<REAL> & b2,
                            const vector3<REAL> & b3,
                            REAL R = geometry<REAL,periodic_cell<REAL>
                            >::tol_geom_default){
    matrix3<REAL> U;
    best_transform(U,{a1,a2,a3},{b1,b2,b3});
    return (U*a1-b1).norm() < R && (U*a2-b2).norm() < R && (U*a3-b3).norm() <R;
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


  /*! \brief Find all point symmetry operations of 3 lattice vectors
   *  comprising a periodic cell
    @param[out] G the resulting point symmetry group in array form
    @param[in] cell the periodic cell
    @param[in] R tolerance radius
   */
  template<class REAL>
  int bravais_point_group(generated_group<matrix3<REAL> > & G,
                          periodic_cell<REAL> & cell,
                          REAL R = geometry<REAL,periodic_cell<REAL>
                          >::tol_geom_default){
    if (cell.DIM != 3)
      IndexError("bravais_point_group:: works only for 3d-periodic crystals");

    matrix3<REAL> aa(matrix3<REAL>::Zero());

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
        aa(i,j) = cell(i).dot(cell(j));

    vector3<REAL> leig = diagon3d(aa);
    REAL lmin = leig(0);
    if (leig(1) < lmin) lmin = leig(1);
    if (leig(2) < lmin) lmin = leig(2);

    REAL amax = cell(0).norm();
    if (cell(1).norm() > amax) amax = cell(1).norm();
    if (cell(2).norm() > amax) amax = cell(2).norm();

    amax += R;

    int n = int(amax/std::sqrt(lmin))+1;

    REAL eps = tol_equiv;
    std::vector<vector3<REAL> > lattvecs;

    for (int i=-n; i<=n; i++)
      for (int j=-n; j<=n; j++)
        for (int k=-n; k<=n; k++){
            vector3<REAL> x = cell(0)*i + cell(1)*j + cell(2)*k;
            if (x.norm() <= amax+eps)
              lattvecs.push_back(x);
          }

    std::vector<matrix3<REAL> > Gapprox;
    std::set<int> ipoints;

    for (int i=0; i<lattvecs.size(); i++)
      for (int j=0; j<lattvecs.size(); j++)
        if (i!=j)
          for (int k=0; k<lattvecs.size(); k++)
            if (i!=k && j!=k){
                matrix3<REAL> U;
                best_transform(U,{cell(0),cell(1),cell(2)},
                {lattvecs[i],lattvecs[j],lattvecs[k]});

                if ( (lattvecs[i]-U*cell(0)).norm() < R &&
                     (lattvecs[j]-U*cell(1)).norm() < R &&
                     (lattvecs[k]-U*cell(2)).norm() < R){
                    Gapprox.push_back(U);
                    ipoints.insert(i);
                    ipoints.insert(j);
                    ipoints.insert(k);
                  }
              }


    std::vector<vector3<REAL> > points;
    for (int i : ipoints)
      points.push_back(lattvecs[i]);

    std::vector<permutation> Gperm;

    for (const auto & g : Gapprox) {
        std::vector<int> p;
        for (int i=0; i<points.size(); i++) {
            vector3<REAL> r = g*points[i];
            for (int j=0; j<points.size(); j++)
              if ((points[j]-r).norm()<R) {
                  p.push_back(j);
                  break;
                }
          }
        Gperm.push_back(permutation(p));
      }

    REAL angle_error = std::asin(R/amax);

    //    finitize_point_group(Gapprox,Gperm,angle_error);

    for (const auto & g : Gapprox)
      G.add(g);

    return 0;

  }

  // ----------------------------------------------------------------------------------------

  template<class REAL>
  void find_point_symm(generated_group<matrix3<REAL> > & G,
                       const geometry<REAL, periodic_cell<REAL> > & geom,
                       REAL R = geometry<REAL,periodic_cell<REAL> >
                       ::tol_geom_default){
    if (geom.nat()<2)
      return;

    // make a copy of geometry
    geometry<REAL, periodic_cell<REAL> > g(geom);

    // find geometric centre
    vector3<REAL> cntr(0);

    for (int i=0; i<g.nat(); i++)
      cntr += g.coord(i);
    cntr /= g.nat();

    for (int i=0; i<g.nat(); i++)
      g.change(i,g.atom(i),g.coord(i)-cntr);

    // sort atoms in reverse order by the distance from centre
    g.sort(
          [](const geometry<REAL> & gg, int ii)->REAL
    {return gg.pos(ii).norm();}
    );

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

          if ( theta > angle_error && theta < pi - angle_error ){
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

    // initialize permutations array to have the group in atom permutations form
    // for further 'finitiztion'

    geometry<REAL, periodic_cell<REAL> > g1(g);
    std::vector<permutation> P;
    P.push_back(permutation(g.nat()));

    P[0].print();

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
            if (std::find(P.begin(),P.end(),permutation(pp)) == P.end()){
                P.push_back(permutation(pp));
                G.group.push_back(U);
                permutation(pp).print();
                std::cout << "\n";
              }

          best_transform(U,{ri,rj,ri.cross(rj)/sqrt(Ri*Rj)},
          {ri1,rj1,-(ri1.cross(rj1))/sqrt(ri1.norm()*rj1.norm())});

          for (int k = 0; k<g.nat(); k++)
            g1.coord(k) = U*g.coord(k);

          if (equiv_geoms(pp,g,g1,R))
            if (std::find(P.begin(),P.end(),permutation(pp))==P.end()){
                P.push_back(permutation(pp));
                G.group.push_back(U);
                permutation(pp).print();
                std::cout << "\n";
              }
        }

    //   finitize_point_group(G.group,P,angle_error);
  }

  // ----------------------------------------------------------------------------------------

  template<class REAL>
  void find_point_symm_old(generated_group<matrix3<REAL> > & G,
                           const geometry<REAL, periodic_cell<REAL> > & geom,
                           REAL R = geometry<REAL,periodic_cell<REAL> >
                           ::tol_geom_default){
    geometry<REAL, periodic_cell<REAL> > g(geom);

    // find geometric centre
    vector3<REAL> cntr(0);

    for (int i=0; i<g.nat(); i++)
      cntr += g.coord(i);
    cntr /= g.nat();

    for (int i=0; i<g.nat(); i++)
      g.change(i,g.atom(i),g.coord(i)-cntr);

    g.sort(
          [](const geometry<REAL> & gg, int ii)->REAL {return norm(gg.pos(ii));}
    );

    //g.write(std::cout);

    // define the possible "images" of atom to which it can transform
    std::vector<std::set<int> > images(g.nat());

    int i1=0, i2=0;

    for (int i=0; i<g.nat(); i++){
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

    for (int i=0; i<g.nat(); i++){
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
          if ( images[j].count(i) ){
              std::set_intersection(iset.begin(), iset.end(),
                                    images[j].begin(), images[j].end(),
                                    std::inserter(buffer,buffer.begin()));
              iset = buffer;
            }
        shells.push_back(iset);
      }

    /*
    for (int i=0; i<shells.size(); i++)
      {
        std::cout << "shell[" << i << "]= ";
        for (int j : shells[i])
          std::cout << j << " ";
        std::cout << "\n";
      }
    */

    REAL angle_error = 0e0;
    geometry<REAL, periodic_cell<REAL> > g1(geom);
    std::vector<permutation> P;
    P.push_back(permutation(g.nat()));

    // Shells are formed, let's try different combinations of atoms to be transformed to each other

    for (int sh1=0; sh1<shells.size(); sh1++)
      for (int sh2=0; sh2<=sh1; sh2++)
        for (int i : shells[sh1])
          for (int j : shells[sh2]){
              // check duplicate pair
              if ( sh1==sh2 && i > j )
                continue;

              // check that one of the points is too close to the centre
              vector3<REAL> r1 = g.pos(i), r2 = g.pos(j);
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
                  for (int j1 : shells[sh2] ){
                      //   if (j1 <= j)

                      REAL s1 = scal(g.pos(i1),g.pos(j1))/
                                (norm(g.pos(i1))*norm(g.pos(j1)));

                      if ( s1 > REAL(1) )  s1 = REAL(1);
                      if ( s1 < REAL(-1) ) s1 = REAL(-1);

                      REAL beta1 = std::acos(s1);

                      //std::cout << i1 << "," << j1 <<  " s1= " << s1 << " bet1= " << beta1 << "\n";

                      if ( std::abs(beta-beta1) < alp ){
                          std::cout << i << "," << j << " -> " << i1 << "," << j1 << "\n";
                          vector3<REAL> r11=g.pos(i1), r12 = g.pos(j1);
                          matrix3<REAL> U;
                          best_transform(U,{r1,r2,r1%r2/sqrt(norm(r1)*norm(r2))},
                          {r11,r12,r11%r12/sqrt(norm(r11)*norm(r12))});

                          for (int k = 0; k<g.nat(); k++)
                            g1.coord(k) = U*g.coord(k);

                          std::vector<int> pp;
                          if (equiv_geoms(pp,g,g1,R))
                            if (std::find(P.begin(),P.end(),permutation(pp))
                                ==P.end()){
                                P.push_back(permutation(pp));
                                G.group.push_back(U);
                                permutation(pp).print();
                                std::cout << "\n";
                              }

                          best_transform(U,{r1,r2,r1%r2/
                                            sqrt(norm(r1)*norm(r2))},
                          {r11,r12,-(r11%r12)/sqrt(norm(r11)*norm(r12))});

                          for (int k = 0; k<g.nat(); k++)
                            g1.coord(k) = U*g.coord(k);

                          if (equiv_geoms(pp,g,g1,R))
                            if (std::find(P.begin(),P.end(),permutation(pp))
                                ==P.end()){
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
        perm[i].print();
        std::cout << "\n";
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
  void find_cryst_symm(generated_group<rotrans<REAL,true> > & G,
                       geometry<REAL,periodic_cell<REAL> > & geom,
                       REAL R = geometry<REAL,periodic_cell<REAL> >
                       ::tol_geom_default){
    //spgw_get_symmetry(G,geom,R);

    generated_group<matrix3<REAL> > B;
    bravais_point_group(B,geom.cell,R);
    G.group.clear();
    G.group.push_back(rotrans<REAL,true>(gen_matrix<REAL>(1),&geom.cell));

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
            G.add(S);
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
  void find_cryst_symm(generators_pack<rotrans<REAL,true> > & G,
                       geometry<REAL, periodic_cell<REAL> > & geom,
                       REAL R = geometry<REAL,periodic_cell<REAL>>::tol_geom_default){
    generated_group<rotrans<REAL,true> > G1;
    find_cryst_symm(G1,geom,R);
    generator_form(G,G1);
  }

  /*! \brief Finds all point subgroups of crystalline symmetry group.
    Can be used to list all high symmetry sites in the lattice.
    @param subs (OUT)    - std::vector containing point subgroups
    @param cntrs (OUT)   - std::vector containing the central points of the point groups
    @param G (IN)        - crystalline symmetry group in array form
   */
  template<class REAL>
  void find_point_subgroups(std::vector<generated_group<matrix3<REAL> > > & subs,
                            std::vector<vector3<REAL> > &cntrs,
                            std::vector<int> & dims,
                            const generated_group<rotrans<REAL,false> > & G){

    std::vector<linear3d_subspace<REAL> > subspaces;
    std::vector<std::vector<rotrans<REAL,false> > > elements;

    //std::cout << "find_point_subs:\n";

    for (const auto & g : G.group){
        auto s = invariant_subspace(g);
        //std::cout << "g= " << g << " s= " << "(" << s.dim << "," << s.pt << "," << s.n << ")\n";
        add_subspace(subspaces,elements, *s,{g});
      }

    //debug
    std::setprecision(4);
    std::cout << std::fixed;
    for (int i=0; i<subspaces.size(); i++)
      std::cout << i << " d= " << subspaces[i].dim << " pt= " << subspaces[i].pt << " n= " << subspaces[i].n
                << " ng= " << elements[i].size() << "\n";


    for (int i=0; i<subspaces.size(); i++)
      if ( subspaces[i].dim == 0)
        for (int j=0; j<subspaces.size(); j++)
          if (subspaces[j].within(subspaces[i].pt))
            for (const auto & gg : elements[j])
              if ( std::find(elements[i].begin(),elements[i].end(),gg)
                   == elements[i].end())
                elements[i].push_back(gg);

    //debug

    std::cout << "\n\n";
    for (int i=0; i<subspaces.size(); i++)
      std::cout << i << "d= " << subspaces[i].dim << " pt= "
                << subspaces[i].pt << " n= " << subspaces[i].n
                << " ng= " << elements[i].size() << "\n";

    /*
    for (int i=0; i<subspaces.size(); i++)
      {
        std::cout << "d= " << subspaces[i].dim << " pt= " << subspaces[i].pt << " n= " << subspaces[i].n;
        for (int j=0; j<elements[i].size(); j++)
          std::cout << elements[i][j];
        std::cout << "\n";
      }
    */

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

    for (int d=0; d<3; d++)
      for (int i=0; i<subspaces.size(); i++)
        if (subspaces[i].dim==d){
            cntrs.push_back(subspaces[i].pt);
            dims.push_back(d);
            subs.push_back(generated_group<matrix3<REAL> >());
            int n=subs.size()-1;
            for (int j=0; j<elements[i].size(); j++)
              subs[n].add(elements[i][j].R);
          }
  }


  template<class REAL>
  void find_point_subgroups(std::vector<generated_group<matrix3<REAL> > >
                            & subs,
                            std::vector<vector3<REAL> > &cntrs,
                            std::vector<int> & dims,
                            const generated_group<rotrans<REAL,true> > & G)
  {
    generated_group<rotrans<REAL,false> > G1;
    G1.group.clear();
    for (const auto & x : G.group)
      G1.group.push_back(rotrans<REAL,false>(x.T,x.R));

    find_point_subgroups(subs,cntrs,dims,G1);
  }


#ifdef PY_EXPORT

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
  void py_find_cryst_symm1(generated_group<rotrans<REAL,true> > & G,
                           geometry<REAL,periodic_cell<REAL> > & geom,
                           REAL R = geometry<REAL,periodic_cell<REAL>>
                           ::tol_geom_default)
  {  find_cryst_symm(G,geom,R); }

  template<class REAL>
  void py_find_cryst_symm2(generators_pack<rotrans<REAL,true> > & G,
                           geometry<REAL, periodic_cell<REAL> > & geom,
                           REAL R = geometry<REAL,periodic_cell<REAL>>
                           ::tol_geom_default)
  { find_cryst_symm(G,geom,R); }

  template<class REAL, bool BOUND>
  void py_find_point_subgroups1(py::list & subs, py::list &cntrs,
                                const generated_group<rotrans<REAL,BOUND> >
                                & G){
    std::vector<generated_group<matrix3<REAL> > >  vsubs;
    std::vector<vector3<REAL> > vcntrs;
    std::vector<int> vdims;
    find_point_subgroups(vsubs,vcntrs,vdims,G);
    for (int i = 0; i < vsubs.size(); i++){
        subs.append(vsubs[i]);
        cntrs.append(vcntrs[i]);
      }
  }

  template<class REAL, bool BOUND>
  void py_find_point_subgroups2(py::list & subs,
                                py::list &cntrs,
                                py::list & dims,
                                const generated_group<rotrans<REAL,BOUND> >
                                & G){
    std::vector<generated_group<matrix3<REAL> > >  vsubs;
    std::vector<vector3<REAL> > vcntrs;
    std::vector<int> vdims;
    find_point_subgroups(vsubs,vcntrs,vdims,G);
    for (int i=0; i<vsubs.size(); i++){
        subs.append(vsubs[i]);
        cntrs.append(vcntrs[i]);
        dims.append(vdims[i]);
      }
  }

  /*
  template<class REAL>
  void py_find_point_subgroups2(bp::list & subs, bp::list &cntrs,
                                const generated_group<rotrans<REAL,true> > & G)
  {
    std::vector<generated_group<matrix3d<REAL> > >  vsubs;
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
