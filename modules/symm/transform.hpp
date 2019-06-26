#ifndef QPP_TRANSFORM_H
#define QPP_TRANSFORM_H

#include <geom/lace3d.hpp>
#include <symm/cell.hpp>
//#include <geom/cell.hpp>
#include <consts.hpp>
#include <vector>

namespace qpp{

  /*! \brief rotrans is the general rotational and translational symmetry operation turning the vector r into R*r+T, where R is rotation (and probably reflection) matrix and T is a translation vector. Thus, rotrans class implements all possible operations of space groups.
    @param REAL either float or double depending of what precision is necessary
    @param BOUND boolean parameter specifying if the rotrans should be "bound" to certain periodic cell. The need for "bound rotrans" is the following: a symmetry group consisting of rotrans operations is, generally speaking, infinite. "Bound rotrans" makes it finite by reducing the symmetry operation result (a vector, a point) to 3d-periodic cell with given translation vectors. Such periodic cell must be the same for all ""bound rotranses" comprising the group.
   */
  template<class REAL, bool BOUND = false>
  struct rotrans {
      typedef periodic_cell<REAL>  BOUNDARY;

      //!\brief the threshhold to consider two translation vectors equal
      static REAL tol_trans;

      //!\brief the threshhold to consider two rotation matricies equal
      static REAL tol_rot;

      static rotrans<REAL,BOUND> unity;

      //!\brief the translation vector
      vector3<REAL> T;

      //!\brief the rotation matrix
      matrix3<REAL> R;

      //!\brief the periodic cell to which the bound rotrans is bound
      //! (should be NULL if BOUND==false)
      BOUNDARY * cell{nullptr};

      //!\brief empty constructor creates unity operation
      rotrans(){
        T = vector3<REAL>(0);
        R = matrix3<REAL>::unity;
        cell = nullptr;
      }

      //!\brief copy constructor
      rotrans(const rotrans<REAL,BOUND> & a) {
        T = a.T;
        R = a.R;
        if (BOUND)
          cell = a.cell;
        else
          cell = nullptr;
      }

      //!\brief creates translation operation with _T vector
      rotrans(const vector3<REAL> &_T, BOUNDARY * _cell = nullptr) {
        T=_T;
        R = matrix3<REAL>::unity;
        if (BOUND)
          cell = _cell;
        else
          cell = nullptr;
      }

      //!\brief creates rotation operation with _R matrix
      rotrans(const matrix3<REAL> & _R, BOUNDARY * _cell = nullptr) {
        T = vector3<REAL>(0);
        R = _R;
        if (BOUND)
          cell = _cell;
        else
          cell = nullptr;
      }

      //!\brief creates rotation-translation operation with vector _T and matrix _R
      rotrans(const vector3<REAL> &_T, const matrix3<REAL> &_R,
              BOUNDARY * _cell = nullptr){
        T = _T;
        R = _R;
        if (BOUND)
          cell = _cell;
        else
          cell = nullptr;
      }

      //!\brief Multiplication of two rotrans operations
      inline rotrans<REAL,BOUND> operator*(const rotrans<REAL,BOUND> & b) const {
        vector3<REAL> t = T + R*b.T;
        if (BOUND) {
            vector3<REAL> f =  cell -> cart2frac(t);
            for (int d=0; d<cell->DIM; d++) {
                f(d) -= floor(f(d));
                if (std::abs(f(d)-REAL(1)) < tol_trans)
                  f(d)=REAL(0);
              }
            t = cell -> frac2cart(f);
          }
        return rotrans<REAL,BOUND>(t, R*b.R,cell);
      }

      /*!\brief Comparison of two rotrans operations. They are considered equal
      if their translations differ by less than tol_trans and their
      rotation matricies differ by less than tol_rot.
    */
      inline bool operator==(const rotrans<REAL, BOUND> & b) const {
        if (!BOUND) {
            return (T - b.T).norm()<= tol_trans &&
                (R - b.R).norm() <= tol_rot;
          }
        else {
            if ( (R - b.R).norm() > tol_rot) return false;
            vector3<REAL> f =  cell -> cart2frac(T - b.T);

            //debug
            //std::cout << "rotrans::== f= " << f;

            for (int d=0; d<cell->DIM; d++) f(d) -= floor(f(d)+.5);
            f = cell->frac2cart(f);

            //std::cout << " t= " << f << "\n";

            return (f).norm() <= tol_trans;
          }
      }


      //!\brief Inequality operator. Simply !(a==b).
      inline bool operator!=(const rotrans<REAL, BOUND> & b) const {
        return !(*this == b);
      }

      //!\brief Rotrans times vector multiplication means that rotrans
      //!  acts on this vector
      inline vector3<REAL> operator*(const vector3<REAL> & v) const {
        vector3<REAL> res = T+R*v;
        if (BOUND)
          res = cell -> reduce(res);
        return res;
      }

      inline rotrans<REAL, BOUND> pow(REAL fn) const {
        int n = floor(fn);
        // fixme - inefficient
        rotrans<REAL,BOUND> A = rotrans<REAL,BOUND>::unity;
        rotrans<REAL,BOUND> C = *this;
        A.cell = C.cell;
        if (n>0){
            while (n-- > 0)
              A = (C)*A;
          }
        else if (n<0){
            rotrans<REAL,BOUND>  B = C.inverse();
            while (n++ < 0)
              A = (B)*A;
          }
        return A;
      }

      inline rotrans<REAL, BOUND> inverse() const {
        matrix3<REAL> A = ((*this).R).inverse();
        vector3<REAL> t = - A*(*this).T;
        return rotrans<REAL,BOUND>(t, A, (*this).cell);
      }

      //!\ Rotrans oputput in qpp format
      virtual void write(std::basic_ostream<CHAR_EX,TRAITS> &os, int offset=0) const{
        for (int k=0; k<offset; k++) os << " ";
        if (BOUND)
          os << "bound_rotrans(";
        else
          os << "rotrans(";
        os << T << "," << R << ")";
      }


#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

      inline vector3<REAL> py_mulv(const vector3<REAL> & v) const
      {return (*this)*v; }
      inline rotrans<REAL,BOUND> py_mulr(const rotrans<REAL,BOUND> & b) const {return (*this)*b; }

#endif

  };

  template<typename _CharT, class _Traits, class VALTYPE, bool BOUND>
  std::basic_ostream<_CharT, _Traits>&
  operator<<(std::basic_ostream<_CharT, _Traits>& __os,
             const rotrans<VALTYPE,BOUND> & r){
    r.write(__os);
    return __os;
  }


  template<class REAL, bool BOUND>
  REAL rotrans<REAL,BOUND>::tol_trans = vector3<REAL>::tol_equiv;

  template<class REAL, bool BOUND>
  REAL rotrans<REAL,BOUND>::tol_rot = matrix3<REAL>::tol_equiv;

  template<class REAL, bool BOUND>
  rotrans<REAL,BOUND>
  rotrans<REAL,BOUND>::unity(vector3<REAL>::Zero(), matrix3<REAL>::unity);

  //!\brief Inverse of rotrans R, P=R^(-1). Means R*P==1.
  //  template<class REAL, bool BOUND>
  //  rotrans<REAL,BOUND> invert(const rotrans<REAL,BOUND> & R){
  //    matrix3<REAL> A = (R.R).inverse();
  //    vector3<REAL> t = - A*R.T;
  //    return rotrans<REAL,BOUND>(t, A, R.cell);
  //  }

  //!\brief Power n of rotrans R
  //template<class REAL, bool BOUND>


  // ----------------------------------------------------------------
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  //  template<class REAL,bool BOUND>
  //  inline rotrans<REAL,BOUND> py_invert_rt(const rotrans<REAL,BOUND> & R) {
  //    return invert(R);}

  //  template<class REAL,bool BOUND>
  //  inline rotrans<REAL,BOUND> py_pow_rt(const rotrans<REAL,BOUND> & R, int n) {
  //    return pow(R,n);}

#endif



  // ----------------------------------------------------------------
  /*
  template<class REAL>
  struct translation
  {
    //typedef typename BOUNDARY::real real;
    static REAL tol_trans;

    static translation<REAL> unity;

    vector3<REAL> T;

    translation()
    { T = 0e0; }

    translation( const translation<REAL> & a)
    {
      T = a.T;
    }

    translation(const vector3<REAL> & t)
    {
      T = t;
    }

    inline translation<REAL> operator*(const translation<REAL> & b) const
    {
      vector3<REAL> res = T+b.T;
      return translation<REAL>(res);
    }

    inline bool operator==(const translation<REAL> & b) const
    {
      return norm(T - b.T) <= tol_trans;
    }

    inline bool operator!=(const translation<REAL> & b) const
    {
      return norm(T - b.T) > tol_trans;
    }

    inline vector3<REAL> operator*(const vector3<REAL> & v) const
    {
      vector3<REAL> res = T+v;
      return res;
    }

    inline operator vector3<REAL>() const
    {
      return T;
    }

  };

  template<class REAL>
  REAL translation<REAL>::tol_trans = 1e-10;

  template<class REAL>
  translation<REAL>  translation<REAL>::unity(vector3<REAL>(0e0));

  template<class REAL>
  translation<REAL> invert(const translation<REAL> & R)
  {
    return translation<REAL>(-R.T);
  }

  template<class REAL>
  translation<REAL> pow(const translation<REAL> & R, int n)
  {
    return translation<REAL>(R.T*n);
  }
  */

}

#endif
