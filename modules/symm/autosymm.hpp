#ifndef QPP_AUTOSYMM_H
#define QPP_AUTOSYMM_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

#include <geom/geom.hpp>
#include <geom/ngbr.hpp>
#include <geom/shape.hpp>
#include <symm/cell.hpp>
#include <symm/gen_cell.hpp>
#include <symm/transform.hpp>
#include <symm/group_theory.hpp>
#include <symm/point_groups.hpp>
#include <symm/permut.hpp>
#include <Eigen/Dense>
#include <algorithm>
#include <iomanip>
#include <optional>

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

        if ( found != Ng-1) {
            res = false;
            //break;
          }
      }

    geom.cell = cell;
    geom.DIM = cell.DIM;
    return res;
  }

  // -------------------------------------------------------------

  template <class REAL>
  struct subspace_of3d {

      int dim;
      vector3<REAL> point, axis;

      subspace_of3d(int __dim, const vector3<REAL> & __pt,
                    const vector3<REAL> & __n = vector3<REAL>(0)) {
        dim = __dim;
        point = __pt;
        axis = __n.normalized();
      }

      subspace_of3d(const subspace_of3d<REAL> & L) {
        dim = L.dim;
        point = L.point;
        axis = L.axis;
      }

      subspace_of3d & operator=(const subspace_of3d<REAL> & L){
        dim = L.dim;
        point = L.point;
        axis = L.axis;
        return *this;
      }

      bool within (const vector3<REAL> & x) const {

        REAL tol_equiv = vector3<REAL>::tol_equiv;
        if (dim == -1) return false;
        else if (dim == 0)
          return (point - x).norm() < tol_equiv;
        else if (dim == 1) {
            vector3<REAL> y = x - point;
            y = y - axis*(y.dot(axis));
            return y.norm() < tol_equiv;
          }
        else if (dim == 2) {
            vector3<REAL>  y = x - point;
            return std::abs(y.dot(axis)) < tol_equiv;
          }
        else if (dim == 3)
          return true;
        return false;

      }

      bool operator== (const subspace_of3d<REAL> & L ) const {

        if (L.dim != dim)
          return false;
        if (dim == 0)
          return (point-L.point).norm() < vector3<REAL>::tol_equiv;
        else if ( dim == 1 || dim == 2)
          return ((axis-L.axis).norm() < vector3<REAL>::tol_equiv ) && within(L.point);
        else if (dim == -1 || dim == 3)
          return true;

        return false;

      }

      bool operator!= (const subspace_of3d<REAL> & L ) const {
        return !(*this == L);
      }

      subspace_of3d<REAL> operator& (const subspace_of3d<REAL> & L) const {

        int d1,d2;
        vector3<REAL> p1,p2,n1,n2;

        if ( dim > L.dim ) {
            d1 = dim; d2 = L.dim;
            p1 = point;  p2 = L.point;
            n1 = axis;   n2 = L.axis;
          }
        else {
            d1 = L.dim; d2 = dim;
            p1 = L.point;  p2 = point;
            n1 = L.axis;   n2 = axis;
          }

        if (d1 == 3) return subspace_of3d<REAL>(d2,p2,n2);

        if (d2 == -1) return subspace_of3d<REAL>(-1,vector3<REAL>(0,0,0));

        if (d2 == 0) {
            if ( subspace_of3d(d1,p1,n1).within(p2) )
              return subspace_of3d<REAL>(0,p2);
            else
              return subspace_of3d<REAL>(-1,vector3<REAL>(0,0,0));
          }

        if ( d1 == 1 && d2 == 1) {
            if ((n1-n2).norm() < vector3<REAL>::tol_equiv ||
                (n1+n2).norm() <  vector3<REAL>::tol_equiv) {
                if (subspace_of3d<REAL>(d1,p1,n1).within(p2))
                  return *this;
                else
                  return subspace_of3d<REAL>(-1,vector3<REAL>(0,0,0));
              }
            else if (std::abs((p2-p1).dot(n1.cross(n2))) <  vector3<REAL>::tol_equiv) {
                REAL s = n1.dot(n2);
                REAL x1 = ((n1 - s*n2).dot(p2-p1))/(1-s*s);
                return subspace_of3d<REAL>(0,p1+x1*n1);
              }
            else
              return subspace_of3d<REAL>(-1,vector3<REAL>(0,0,0));
          }

        if (d1 == 2 && d2 == 1) {
            if (std::abs(n1.dot(n2)) < vector3<REAL>::tol_equiv){
                if (std::abs(n1.dot(p2-p1)) < vector3<REAL>::tol_equiv)
                  return subspace_of3d<REAL>(1,p2,n2);
                else
                  return subspace_of3d<REAL>(-1,vector3<REAL>(0,0,0));
              }
            else
              return  subspace_of3d(0,p2+n2*n1.dot(p1-p2)/n1.dot(n2));
          }

        if (d1 == 2 && d2 == 2) {

            if ((n1-n2).norm() < vector3<REAL>::tol_equiv ||
                (n1+n2).norm() < vector3<REAL>::tol_equiv) {

                if (std::abs(n1.dot(p1-p2)) <  vector3<REAL>::tol_equiv)
                  return *this;
                else
                  return subspace_of3d<REAL>(-1,vector3<REAL>(0,0,0));

              } else {

                REAL s = n1.dot(n2);
                vector3<REAL> nn = n1.cross(n2);
                REAL x1 = (p1.dot(n1)-s*p2.dot(n2))/(1-s*s);
                REAL x2 = (p2.dot(n2)-s*p1.dot(n1))/(1-s*s);
                return subspace_of3d<REAL>(1,x1*n1+x2*n2,nn);

              }

          }

      }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

      static void py_export(py::module m, const char * pyname){
        py::class_<subspace_of3d<REAL> >(m, pyname)
            .def(py::init<int, const vector3<REAL> &, const vector3<REAL> &>(),
                 py::arg("dim"), py::arg("point"), py::arg("axis") = vector3<REAL>(0))
            .def("within", & subspace_of3d<REAL>::within)
            .def_readwrite("dim", & subspace_of3d<REAL>::dim)
            .def_readwrite("point", & subspace_of3d<REAL>::point)
            .def_readwrite("axis", & subspace_of3d<REAL>::axis)
            .def(py::self==py::self)
            .def(py::self!=py::self)
            .def("__and__", [](const subspace_of3d<REAL> &self, const subspace_of3d<REAL> & other)
        {return self & other; })
            ;
      }

#endif

  };

  // -------------------------------------------------------------

  template<class CMPLX>
  vector3<typename numeric_type<CMPLX>::real> vecreal(const vector3<CMPLX> & v){
    return vector3<typename numeric_type<CMPLX>::real>(v(0).real(), v(1).real(), v(2).real() );
  }

  // -------------------------------------------------------------

  template<class REAL>
  subspace_of3d<REAL> invariant_subspace(const rotrans<REAL,false> & R) {
    vector3<REAL> axis, point;
    REAL phi;
    bool inv;
    int dim;
    REAL eps = vector3<REAL>::tol_equiv;

    REAL epscos = std::sqrt(eps);

    analyze_transform(axis, phi, inv, R.R);

    if (!inv) {
        if (phi < epscos) {
            // Unity matrix
            if ( R.T.norm() < eps ) {
                dim = 3;
                point = {0,0,0};
                //std::cout << "  ---- invariant_subspace ----- unity matrix - d3\n";
              }
            else {
                dim = -1;
                point = {0,0,0};
                //std::cout << "  ---- invariant_subspace ----- unity matrix - d-1\n";
              }
          }
        else if (std::abs(axis.dot(R.T)) < eps) {
            // Rotation case
            dim = 1;
            point = R.T - RotMtrx(axis,-phi)*R.T;
            point /= 2e0*(1 - std::cos(phi));
            //std::cout << "  ---- invariant_subspace ----- rotation\n";
          }
        else {
            // Chiral axis case
            dim = -1;
            point = {0,0,0};
            //std::cout << "  ---- invariant_subspace ----- chiral axis\n";
          }
      }
    else {
        if ( phi < epscos ) {
            // Pure inversion case
            dim = 0;
            point = 0.5*R.T;
            //std::cout << "  ---- invariant_subspace ----- inversion\n";
          }
        else if ( std::abs(phi - REAL(pi)) < epscos) {
            if ( (R.T - axis*axis.dot(R.T)).norm() < eps ) {
                // Mirror plane case
                dim = 2;
                point = 0.5*R.T;
                //std::cout << "  ---- invariant_subspace ----- mirror plane\n";
              }
            else {
                // Glide plane case
                dim = -1;
                point = {0,0,0};
                //std::cout << "  ---- invariant_subspace ----- glide plane\n";
              }
          }
        else {
            // Rotoinversion case
            dim = 0;
            vector3<REAL> Tpar = axis*axis.dot(R.T),
                Tperp = R.T - Tpar;
            point = 0.5*Tpar + 0.5*(Tperp + RotMtrx(axis,-phi)*Tperp)/(1+std::cos(phi) );
            //std::cout << "  ---- invariant_subspace ----- rotoinversion\n";
          }
      }

    return subspace_of3d(dim, point, axis);

  }

  // -------------------------------------------------------------

  template<class REAL>
  std::optional<subspace_of3d<REAL> > invariant_subspace1(const rotrans<REAL,false> & R) {

    matrix3<typename numeric_type<REAL>::complex> n;
    vector3<typename numeric_type<REAL>::complex> lmb;
    diagon3d(lmb,n,R.R);

    vector3<typename numeric_type<REAL>::complex>
        T(R.T[0],R.T[1],R.T[2]),
        t(n.row(0).dot(T), n.row(1).dot(T), n.row(2).dot(T)),
        x(0,0,0);

    int d = 0, ni[3];

    for (int i=0; i<3; i++)
      if (abs(lmb[i]-REAL(1)) < vector3<REAL>::tol_equiv) {
          if (abs(t[i]) < vector3<REAL>::tol_equiv) {
              ni[d] = i;
              d++;
            }
          else return std::optional<subspace_of3d<REAL> >({ -1, vector3<REAL>(0,0,0) });
        }
      else
        x[i] = t[i]/(REAL(1)-lmb[i]);

    vector3<typename numeric_type<REAL>::complex> c =
        x[0]*n.row(0)+x[1]*n.row(1)+x[2]*n.row(2);
    vector3<REAL> rc = vecreal(c);

    if (d==0)
      return std::optional<subspace_of3d<REAL> >({ 0, rc});
    else if (d==1)
      return std::optional<subspace_of3d<REAL> >({ 1, rc,
                                                   vecreal<typename numeric_type<REAL>::complex>(
                                                   n.row(ni[0]))
                                                 });
    else if (d==2)
      return std::optional<subspace_of3d<REAL> >({ 2, rc,
                                                   vecreal<typename numeric_type<REAL>::complex>(
                                                   n.row(ni[0]).cross(n.row(ni[1]))) });
    else if (d==3)
      return std::optional<subspace_of3d<REAL> >({ 3, rc});

    return std::nullopt;

  }


  // -------------------------------------------------------------

  template <class REAL>
  void add_subspace(std::vector<subspace_of3d<REAL> > & subspaces,
                    std::vector<std::vector<rotrans<REAL,false> > > &elements,
                    const subspace_of3d<REAL> &s,
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

    std::cout << "t= " << t << "\n";

    for (int i=0; i<t1[t].size(); i++){
        vector3<REAL> v = g2.pos(t2[t][i]) - g1.pos(t1[t][0]), vs=v;
        if (g1.frac) vs = cell.cart2frac(v);

        geometry<REAL,periodic_cell<REAL> > g(g1);
        for (int j=0; j<g.nat(); j++)
          g.coord(j) += vs;


        std::cout << i << " v= " << v << "\n";


        bool is_transl = true;
        permutation P(g.nat());

        for (int j=0; j<g.nat(); j++) {
            bool found = false;
            for (iterator J({-1,-1,-1},{1,1,1}); !J.end(); J++)
              for (int k=0; k<g.nat(); k++)
                if ((g2.pos(k) - g.pos(j,J)).norm() < 2*R && g2.atom(k)==g.atom(j)) {
                    //std::cout << j << g.coord(j);

                    found = true;
                    if (g.frac) {
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
            if (!found) {
                is_transl = false;
                break;
              }
          }
        if (is_transl) {
            vector3<REAL> dv = vector3<REAL>::Zero();
            for (int j=0; j < g.nat(); j++)
              dv += g2.pos(j) - g.pos(j);
            dv /= g.nat();
            transl.push_back(v+dv);
            perm.push_back(P);
          }
      }

    //debug

    std::cout << "alive after all!\n";
    for (int i=0; i<transl.size(); i++)
      {
        std::cout << i << transl[i];
        std::cout << perm[i].to_string() << "\n";
      }

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
                         ::tol_geom_default) {

    std::vector<permutation> perm;
    find_translations(transl,perm,g1,g2,cell,R);

  }

  /*! \brief Find the crystalline symmetry group
    @param[out] G - the crystalline group of bound rotranslational operations in array form.
    Bound rotranslational operations are used to make the group finite
    @param[in] geom - the geometry of unit cell together with lattice vectors, which should be
    stored in geom.cell object. This geometry must be 3D - periodic
    @param[in] R( - the tolerance radius. Symmetry operation is considered valid, if the
    displacement of atom due to this operation is less than R
   */
  template<class REAL>
  void find_cryst_symm(array_group<rotrans<REAL,true> > & G,
                       geometry<REAL,periodic_cell<REAL> > & geom,
                       REAL R = geometry<REAL,periodic_cell<REAL> >
                       ::tol_geom_default) {
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
                       REAL R = geometry<REAL,periodic_cell<REAL>>::tol_geom_default) {

    array_group<rotrans<REAL,true> > G1;
    find_cryst_symm(G1,geom,R);
    generator_form(G,G1);

  }

  /*! \brief Finds all point subgroups of crystalline symmetry group.
    Can be used to list all high symmetry sites in the lattice.
    @param subs (OUT)    - std::vector containing point subgroups
    @param cntrs (OUT)   - std::vector containing the central points of the point groups
    @param G (IN)        - crystalline symmetry group in array form
   */

  /*
  template<class REAL>
  void find_point_subgroups(std::vector<array_group<matrix3<REAL> > > & subs,
                            std::vector<vector3<REAL> > &cntrs,
                            std::vector<int> & dims,
                            const array_group<rotrans<REAL,false> > & G){}
  */

  template<class REAL>
  void find_point_subgroups(std::vector<array_group<matrix3<REAL> > > & groups,
                            std::vector<subspace_of3d<REAL> > & subspaces,
                            const array_group<rotrans<REAL,false> > & G) {

    //std::vector<subspace_of3d<REAL> > subspaces;
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
      std::cout << i <<
                   " d= " << subspaces[i].dim <<
                   " pt= " << subspaces[i].point <<
                   " n= " << subspaces[i].axis <<
                   " ng= " << elements[i].size() << "\n";

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
    */

    int nnew = 0, n = subspaces.size();
    bool contin = true;
    while (contin) {

        int nnewnew = subspaces.size();
        for (int i=nnew; i<nnewnew; i++)
          if (subspaces[i].dim > 0)
            for (int j=0; j<n; j++)
              if (subspaces[j].dim > 0) {
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
    */
    for (int i=0; i<subspaces.size(); i++) {

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
    */
  }


  template<class REAL>
  void find_point_subgroups(std::vector<array_group<matrix3<REAL> > > & groups,
                            std::vector<subspace_of3d<REAL> > & subspaces,
                            const array_group<rotrans<REAL,true> > & G) {

    array_group<rotrans<REAL,false> > G1;
    G1.group.clear();
    for (const auto & x : G.group)
      G1.group.push_back(rotrans<REAL,false>(x.T,x.R));

    find_point_subgroups(groups,subspaces,G1);

  }


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

  template<class REAL, bool BOUND>
  void py_find_point_subgroups1(py::list & groups, py::list &subspaces,
                                const array_group<rotrans<REAL,BOUND> >
                                & G){
    std::vector<array_group<matrix3<REAL> > >  vgroups;
    std::vector<subspace_of3d<REAL> > vsubspaces;
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

} // namespace qpp

#endif
