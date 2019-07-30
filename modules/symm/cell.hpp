#ifndef QPP_CELL_H
#define QPP_CELL_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
//#include <pybind11/stl.h>
#include <pybind11/iostream.h>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

#include <geom/lace3d.hpp>
#include <symm/index.hpp>
//#include <symm/transform.hpp>
#include <consts.hpp>
#include <stdexcept>
#include <cmath>

namespace qpp {

  /*
    The supercell concept generalization for the geometry class looks like:

  template< int DIM, class REAL>
  class CELL{
  public:

    vector3d<REAL> transform(const vector3d<REAL> & r, const index<DIM> & I) const;

    bool within(const vector3d<REAL> & r) const;

    vector3d<REAL> reduce(const vector3d<REAL> & r) const;

    // find high symmetry point within "radius" distance from given point "r"
    // makes sence for rotational symmetries
    vector3d<REAL> symmetrize(const vector3d<REAL> & r, REAL radius) const;

    // fractional to cartesian and vice versa transformation
    // makes sence only for periodic translational cells
    vector3d<REAL> frac2cart(const vector3d<REAL> & r) const;

    vector3d<REAL> cart2frac(const vector3d<REAL> & r) const;

  };

  Any class having these methods - can be used as a "supercell"
  for some geometry

  */

  /*! \brief Purely translational periodic cell with DIM=1,2,3 periodicity.
   * The value DIM=0 is also valid and means no periodicity
   */
  template<class REAL = double>
  struct periodic_cell {

      //! \brief The dimension of periodicity
      int DIM;

      vector3<REAL> *v;
      STRING_EX name;

      //! \brief Create periodic cell of dimension dim with zero
      //!  translation vectors
      periodic_cell (int dim = 0) {
        DIM = dim;
        if (DIM>0)
          v = new vector3<REAL>[DIM];
        else
          v = nullptr;
        for (int d=0; d<DIM; d++)
          v[d] = vector3<REAL>::Zero();
      }

      //! \brief Copy constructor for periodic cell
      periodic_cell (const periodic_cell<REAL> & cl) {
        DIM = cl.DIM;
        if (DIM>0)
          v = new vector3<REAL>[DIM];
        else
          v = nullptr;
        for(int i=0; i<DIM; i++)
          v[i] = cl.v[i];
      }

      ~periodic_cell() {
        delete [] v;
      }
      /*! \brief Creates periodic cell of DIM==3 with given lattice
     * constants and angles
        @param a,b,c - lattice constants
        @param alpha, beta, gamma - angles are in degrees!
    */
      periodic_cell (REAL a, REAL b, REAL c, REAL alpha, REAL beta, REAL gamma) {
        DIM = 3;
        v = new vector3<REAL>[DIM];
        alpha *= REAL(pi) / 180;
        beta  *= REAL(pi) / 180;
        gamma *= REAL(pi) / 180;
        v[0] = vector3<REAL>(a,REAL(0),REAL(0));
        v[1] = vector3<REAL>(b*std::cos(gamma), b*std::sin(gamma), REAL(0));
        REAL nx = std::cos(beta);
        REAL ny = (std::cos(alpha) - nx*std::cos(gamma))/std::sin(gamma);
        REAL nz = std::sqrt(1-nx*nx-ny*ny);
        v[2] = vector3<REAL>(nx,ny,nz)*c;
      }

      /*! \brief Creates periodic cell with given translation vectors
        @param a, b(optional), c(optional) - translation vectors.
        If only one provided, the resulting cell has
        DIM==1, if two provided, then DIM==2, and if all
        three provided, you get DIM==3 periodic cell
    */
      periodic_cell (vector3<REAL> a, vector3<REAL > b = 0, vector3<REAL> c = 0 ) {

        DIM = 1;
        if ( b != vector3<REAL>::Zero() )
          DIM = 2;
        if ( c != vector3<REAL>::Zero() )
          DIM = 3;

        v = new vector3<REAL>[DIM];

        if (DIM>0)
          v[0] = a;
        if (DIM>1)
          v[1] = b;
        if (DIM>2)
          v[2] = c;
      }

      index begin() const
      {return index::D(DIM).all(-1);}

      index end() const
      {return index::D(DIM).all(1); }

      vector3<REAL> cnt() const {

        vector3<REAL> ret_cnt{0};
        for (int d=0; d<DIM; d++)
          ret_cnt += v[d]*0.5;
        return ret_cnt;

      }

      vector3<REAL> transform(const vector3<REAL> & r, const index & I) const {

        vector3<REAL> r1 = r;
        for (int d=0; d<DIM; d++)
          r1 += v[d]*I(d);
        return r1;

      }

      /*! \brief Answers the question whether r belongs to the unit cell
      defined as parallelepiped with one vertex in
      the coordinate origin
      the others are pointed by lattice vectors
    */
      bool within(const vector3<REAL> & r) const {

        vector3<REAL> f = cart2frac(r);
        bool res = true;
        for (int d=0; d<DIM; d++)
          if (f(d)<REAL(0) || f(d) >= REAL(1)){
              res = false;
              break;
            }
        return res;

      }

      bool within_already_frac(const vector3<REAL> & r) const {

        bool res = true;
        for (int d=0; d<DIM; d++)
          if ( r(d)<REAL(0) || r(d) >= REAL(1) ){
              res = false;
              break;
            }
        return res;

      }

      bool within_epsilon_b(const vector3<REAL> & r, const REAL eps) const {

        vector3<REAL> f = cart2frac(r);
        bool res = true;
        for (int d=0; d<DIM; d++)
          if ( (f[d] < -eps) || (f[d] > 1 + eps)){
              res = false;
              break;
            }
        return res;

      }

      /*! \brief Brings the point r into the volume of unit cell by translations
       unit cell is defined as parallelepiped with one vertex in
       the coordinate origin
       the others are pointed by lattice vectors
    */
      vector3<REAL> reduce(const vector3<REAL> & r) const {

        vector3<REAL> f = cart2frac(r);
        for (int d=0; d<DIM; d++)
          f(d) -= floor(f(d));
        return frac2cart(f);

      }

      /*! \brief find high symmetry point within "radius" distance from given point "r"
      makes sence for rotational symmetries
    */
      vector3<REAL> symmetrize(const vector3<REAL> & r, REAL radius) const {
        return r;
      }

      /*! \brief fractional to cartesian  transformation
       makes sence only for periodic translational cells
       @param[in] r The fractional coordinates. In the case DIM==2 the third coordinate ( z=r(2) ) is
       orthogonal to both translation vectors
       @return Cartesian coordinates
    */
      vector3<REAL> frac2cart(const vector3<REAL> & r) const {

        vector3<REAL> res = vector3<REAL>::Zero();
        for (int i=0; i<DIM; i++)
          res += r(i)*v[i];

        if (DIM==2){
            vector3<REAL> n12 = v[0].cross(v[1]);
            n12 = n12.normalized();
            res += r(2)*n12;
          }

        return res;

      }

      /*! \brief cartesian to fractional transformation,
       works for DIM==3 and DIM==2
       @param[in] r  Fartesian coordinates
       @return Fractional coordinates. In the case DIM==2 the third
       coordinate ( z=f(2) ) is
       orthogonal to both translation vectors
    */
      vector3<REAL> cart2frac(const vector3<REAL> & r) const {

        vector3<REAL> v2;
        if (DIM==3)
          v2 = v[2];
        else if (DIM==2){
            v2 = v[0].cross(v[1]);
            v2 /= v2.norm();
          }

        matrix3<REAL> A;
        A.col(0) = v[0];
        A.col(1) = v[1];
        A.col(2) = v2;
        return solve3(A, r);

      }

      // -----------------------------------------------------------------------

      inline vector3<REAL> & operator()(int i){
        // fixme - not obvious convention

        return v[i];
      }

      inline vector3<REAL> operator()(int i) const
      { return v[i]; }

      inline periodic_cell<REAL> & operator=(const periodic_cell<REAL> & cl) {

        for(int i=0; i<DIM; i++)
          v[i] = cl.v[i];
        return *this;

      }

      /*! \brief Brings the point r into the volume of unit cell
       by translations
       unit cell is defined as parallelepiped CENTRED in the
       coordinate origin
    */
      inline vector3<REAL> reduce_cntr(const vector3<REAL> & r) const {

        vector3<REAL> f = cart2frac(r);
        for (int i=0; i<DIM; i++){
            f(i) -= int(f(i));
            if ( f(i) > REAL(1)/2 ) f(i)-=1;
          }

        return frac2cart(f);

      }

      /*! \brief Brings r into Wigner-Zeitz unit cell
      fixme - not implemented yet!
    */
      inline vector3<REAL> reduce_wz(vector3<REAL> r) const {
        return vector3<REAL>::Zero();
      }


      /*! \brief Answers the question whether r belongs to unit cell
     * centred at the coordinate origin
     */
      inline bool within_centered(vector3<REAL> r) const {

        vector3<REAL> f = cart2frac(r);
        bool res = true;
        for (int d=0; d<DIM; d++)
          if ( f(d)<-REAL(1)/2 || f(d) > REAL(1)/2 ){
              res = false;
              break;
            }
        return res;

      }

      /*! \brief Answers the question whether r belongs to Wigner-Zeitz
      * unit cell
      fixme - not implemented yet!
      */
      inline bool within_wz(vector3<REAL> r) const {
        return true;
      }

      virtual void write(std::basic_ostream<CHAR_EX,TRAITS> &os,
                         int offset=0) const {

        if (DIM == 0) return;
        for (int k=0; k<offset; k++) os << " ";
        os << "vectors";
        if (name != "")
          os << " " << name;
        os << "(" << DIM << "d){\n";

        for (int i=0; i<DIM; i++){
            for (int k=0; k<offset+2; k++) os << " ";
            //TODO Migrate to fmt
            //	  os << boost::format(" %11.6f %11.6f %11.6f\n")
            //	  % v[i](0) % v[i](1) % v[i](2);
          }

        for (int k=0; k<offset; k++) os << " ";
        os << "}\n";

      }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

      // --------------- PYTHON -------------------------------

      inline void py_setitem(int i, const vector3<REAL> & a){
        if (i<0)
          i += DIM;
        if (i<0 || i>=DIM)
          IndexError("cell: index out of range");
        v[i] = a;
      }

      inline vector3<REAL> py_getitem(int i) const{
        if (i<0)
          i += DIM;
        if (i<0 || i>=DIM)
          IndexError("cell: index out of range");
        return v[i];
      }

      inline void py_setitem2(py::tuple I, REAL a){
        int i= py::cast<int>(I[0]), j= py::cast<int>(I[1]);
        v[i](j) = a;
      }

      inline REAL py_getitem2(py::tuple I) const{
        int i= py::cast<int>(I[0]), j= py::cast<int>(I[1]);
        return v[i](j);
      }

      periodic_cell(py::tuple t1, py::tuple t2=py::tuple(),
                    py::tuple t3=py::tuple()){
        DIM = 1;
        if (py::len(t2)>0) DIM = 2;
        if (py::len(t3)>0) DIM = 3;

        v = new vector3<REAL>[DIM];

        if (DIM>0) v[0] = vector3<REAL>(t1);
        if (DIM>1) v[1] = vector3<REAL>(t2);
        if (DIM>2) v[2] = vector3<REAL>(t3);
      }

      periodic_cell(py::list t1, py::list t2=py::list(),
                    py::list t3=py::list()){
        DIM = 1;
        if (py::len(t2)>0) DIM = 2;
        if (py::len(t3)>0) DIM = 3;

        v = new vector3<REAL>[DIM];

        if (DIM>0) v[0] = vector3<REAL>(t1);
        if (DIM>1) v[1] = vector3<REAL>(t2);
        if (DIM>2) v[2] = vector3<REAL>(t3);
      }

#endif

  };

  // ------------------------------------------------------

  template<typename _CharT, class _Traits, class REAL>
  std::basic_ostream<_CharT, _Traits>&
  operator<< (std::basic_ostream<_CharT, _Traits>& __os, const periodic_cell<REAL> &cl) {

    std::basic_ostringstream<_CharT, _Traits> __s;
    __s.flags(__os.flags());
    __s.imbue(__os.getloc());
    __s.precision(__os.precision());
    __s  << "cell(" << cl(0);
    for (int d=1; d<cl.DIM; d++)
      __s << "," << cl(d);
    __s << ")";
    return __os << __s.str();

  }

}

#endif

