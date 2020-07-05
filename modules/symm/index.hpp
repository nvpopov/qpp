#ifndef QPP_INDEX_H
#define QPP_INDEX_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif


#include <ostream>
#include <sstream>
#include <initializer_list>
#include <stdexcept>
#include <geom/lace3d.hpp>
#include <data/errors.hpp>
#include <io/strfun.hpp>

namespace qpp {

/// \brief index is a general purpose complex index, having DIM integer components
class index {

  int *idx;
  bool del;

public:

  //! The index dimension - number of components
  int DIM;

  //! Typecast operator to int type returns the 0th component of the index
  inline operator int () const {return idx[0];}

  //! The d-th component of the index
  inline int operator () (int d) const {return idx[d];}

  //! The d-th component of the index
  inline int& operator () (int d) {return idx[d];}

  //! Typecast from integer: the 0th component of index is set to i, the rest is set to 0
  inline index& operator= (int i) {

    idx[0] = i;
    for (int d=1; d<DIM; d++)
      idx[d] = 0;
    return *this;

  }

  //! Assigment operator
  inline index& operator= (const index & I) {

    if (DIM != I.DIM){
      if (del)
        delete [] idx;
      DIM = I.DIM;
      idx = new int[DIM];
      del = true;
    }

    for (int d=0; d<DIM; d++)
      idx[d] = I(d);
    return *this;

  }

  //! The same as assigment operator in the form of explicitly called method
  inline void set (const index & I) {
    *this = I;
  }

  //! Componentwise addition of two indicies
  inline index operator+(const index & I) const {

    index res = D(DIM);
    for (int d=0; d<DIM; d++)
      res(d) = idx[d] + I(d);
    return res;

  }

  //! Componentwise subtraction of two indicies
  inline index operator-(const index & I) const {

    index res = D(DIM);
    for (int d=0; d<DIM; d++)
      res(d) = idx[d] - I(d);
    return res;

  }

  //! Index I is added to this index componentwise
  inline index& operator+= (const index & I) {

    for (int d=0; d<DIM; d++)
      idx[d] = idx[d] + I(d);
    return *this;

  }

  //! Index I is subtracted from this index componentwise
  inline index& operator-= (const index & I){

    for (int d=0; d<DIM; d++)
      idx[d] = idx[d] - I(d);
    return *this;

  }

  /*! \brief Using std::initializer_list to set the components of this index. Example:
      qpp::index I({1,2,3,4,5});
      std::cout << I << std::endl; // (1,2,3,4,5)
      I.set({5,4,3,2,1});
      std::cout << I << std::endl; // (5,4,3,2,1)
      I.set({1,2,3}); // IndexError: Wrong number of index components
     */
  inline void set (const std::initializer_list<int> &li) {

    if (li.size() != DIM) IndexError("Wrong number of index components");
    int d=0;
    for (int i : li)
      idx[d++] = i;
  }

  /*
    index(int dim)
    {
      DIM = dim;
      idx = new int[DIM];
      del = true;
    }
    */

  index () {

    DIM = 0;
    idx = nullptr;
    del = false;

  }

  /*
    index(int i)
    {
      DIM=1;
      idx = new int;
      del = true;
      *idx = i;
    }
    */

  index (const index & I) {

    DIM = I.DIM;
    idx = new int[DIM];
    for (int d=0; d<DIM; d++)
      idx[d] = I(d);
    del = true;

  }

  index (const index & I, int d1, int d2 = -1) {

    if (d2==-1) d2 = I.DIM-1;
    DIM = d2-d1+1;
    idx = & I.idx[d1];
    del = false;

  }

  index (const std::initializer_list<int> &li) {

    DIM = li.size();
    idx = new int[DIM];
    set(li);
    del = true;

  }

  ~index () {

    if (del)
      delete [] idx;

  }

  inline index sub (int d1, int d2 = -1) const {

    return index(*this,d1,d2);
  }

  inline bool operator== (const index &I) const {

    bool res = DIM == I.DIM;
    if (res)
      for (int d=0; d<DIM; d++)
        if (idx[d]!=I(d)){
          res = false;
          break;
        }
    return res;
  }


  inline bool operator!= (const index &I) const {
    return ! ((*this) == I);
  }

  struct factory {

    int DIM;

    factory (int dim) {DIM=dim;}

    index all (int a) {

      index t;
      t.DIM = DIM;
      t.del = true;
      t.idx = new int[DIM];

      for (int d=0; d<DIM; d++)
        t(d) = a;
      return t;

    }

    index atom (int a) {

      index t = all(0);
      t(0)=a;
      return t;

    }

    operator index () {return all(0);}

  };

  static factory D(int dim) {

    return factory(dim);
  }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  // --------------- PYTHON -------------------------------

  int py_getitem(int d) const{

    return idx[d];
  }

  void py_setitem(int d, int v){

    idx[d] = v;
  }

  inline index sub1(int d1){

    return sub(d1);
  }

  index(const py::list &l){

    // Assuming that type checks have been performed inside python code
    DIM = py::len(l);
    idx = new int[DIM];
    for (int d=0; d<DIM; d++)
      idx[d] =py::cast<int>(l[d]);
    del = true;
  }

  index(const py::tuple &l){

    // Assuming that type checks have been performed inside python code
    DIM = py::len(l);
    idx = new int[DIM];
    for (int d=0; d<DIM; d++)
      idx[d] = py::cast<int>(l[d]);
    del = true;
  }

  std::string print(){
    std::string _tmp = "{";

    _tmp = "idx(" + t2s(idx[0]);

    for (int d=1; d<DIM; d++)
      _tmp += "," + t2s(idx[d]);
    _tmp += ")";

    return _tmp;

  }

  index py_add(const index &I2) const
  { return (*this)+I2; }

  index py_sub(const index &I2) const
  { return (*this)-I2; }

  static void py_export( py::module m, const char * pyname){

    py::class_<index >(m, pyname)
        .def(py::init<>())
        .def(py::init<py::list&>())
        .def(py::init<py::tuple&>())
        .def(py::init<index const&>())
        //TODO: last parameter is optional
        .def(py::init<index const&, int, int >())
        //.def(py::init<int>())
        .def("__getitem__",&index::py_getitem)
        .def("__setitem__",&index::py_setitem)
        .def("sub",  &index::sub)
        .def("sub",  &index::sub1)
        //	.def(py::str(py::self))
        //	.def(py::repr(py::self))
        .def(py::self + py::self)
        .def(py::self - py::self)
        //.def("__add__", & index::py_add )
        //.def("__sub__", & index::py_sub )
        .def(py::self == py::self)
        .def(py::self!= py::self)
        .def("__str__", &index::print)
        .def("__repr__", &index::print)
        ;
  }

#endif

};

// ------------------------------------------------------

template<typename _CharT, class _Traits>
std::basic_ostream<_CharT, _Traits>&
operator<<(std::basic_ostream<_CharT,
                              _Traits>& __os,
           const index &I){

  std::basic_ostringstream<_CharT, _Traits> __s;
  __s.flags(__os.flags());
  __s.imbue(__os.getloc());
  __s.precision(__os.precision());

  if (I.DIM > 0){

    __s  << "(" << I(0);
    for (int d=1; d<I.DIM; d++)
      __s << "," << I(d);
    __s << ")";
  }
  else

    __s << "(0)";
  return __os << __s.str();
}

index atom_index(int at, const index & I);

// -------------------------------------------------------------

bool compare_atindex(const index & at1,
                     const index & at2);

// ------------------- iterator class --------------------
// Iterator allows you run through all (or some) atoms of this cell
// and of surrounding cells

class iterator : public index {

protected:
  index a, b;
  bool _end;
  // a - from
  // b - to

  //using index::idx;

  inline void inc(){

    if (DIM==0){

      _end = true;
      return;
    }

    int d = 0;

    while (++(*this)(d) > b(d)){

      (*this)(d)=a(d);
      if (++d >= DIM) {

        _end = true;
        break;
      }
    }
  }

public:

  iterator(const index & _a, const index & _b) :
                                               index(_a), a(_a), b(_b){

    _end = false;
  }

  inline void reset(){

    _end = false;
    set(a);
  }

  iterator & operator++(int){

    inc();
    return *this;
  }

  inline bool end(){return _end;}

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  // --------------- PYTHON -------------------------------

  index py_next(){

    if (end())
      StopIter();
    index res = *this;
    inc();
    return res;
  }

  static void py_export(py::module m, const char * pyname){

    py::class_<iterator>(m, pyname)
        .def(py::init<const index&, const index&>())
        .def(py::init<py::list,py::list>())
        .def(py::init<py::tuple,py::tuple>())
        .def("next", & iterator::py_next)
        .def("__next__", & iterator::py_next)
        ;
  }

#endif

};

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

class index_range{

  index a,b;

public:
  index_range(const index & _a,
              const index & _b) :
                                 a(_a), b(_b) {}

  index_range(const py::list & l1,
              const py::list & l2) :
                                    a(l1), b(l2){}

  index_range(const py::tuple & l1,
              const py::tuple & l2) :
                                     a(l1), b(l2) {}

  iterator  __iter__()
  { return iterator(a,b); }

  static void py_export(py::module m,
                        const char * pyname){
    py::class_<index_range>(m, pyname)
        .def(py::init<const index&, const index&>())
        .def(py::init<const py::list&, const py::list&>())
        .def(py::init<const py::tuple&, const py::tuple&>())
        .def("__iter__", & index_range::__iter__)
        ;
  }

};

#endif

}

#endif
