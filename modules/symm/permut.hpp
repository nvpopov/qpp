#ifndef QPP_PERMUT_H
#define QPP_PERMUT_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

#include <vector>
#include <string>

namespace qpp {

  // ------------------------------------------------------
  class permutation {

      std::vector<int> p;

    public:

      int N;

      //static permutation unity;
      permutation(int _N) {
        N = _N;
        for (int i=0; i<N; i++)
          p.push_back(i);
      }

      permutation(const permutation & b) {
        //std::cout << "copy constructor\n";
        N = b.N;
        for (int i : b.p)
          p.push_back(i);
      }

      permutation(const std::vector<int> & li) {
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

      inline permutation operator*(const permutation & b) const {
        if (N != b.N) IndexError("Permutations have different dimensions");
        permutation res(N);
        for (int i=0; i<N; i++) res[i] = b[p[i]];
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

      STRING_EX to_string() const {
        STRING_EX res="(";
        for (int i:p) res = res + " " + std::to_string(i);
        res = res + ")";
        return res;
      }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

      permutation(const py::list &li){
        N = py::len(li);
        for (auto j : li)
          p.push_back(py::cast<int>(j));

      }

      int py_get(int i) const{
        if (i<0) i+= size();
        if (i<0 || i>=size())
          IndexError("permutation: index out of range");
        return p[i];
      }

      void py_set(int i, int pi){
        if (i<0) i+= size();
        if (i<0 || i>=size())
          IndexError("permutation: index out of range");
        p[i]=pi;
      }

      static void py_export(py::module m){
        py::class_<permutation>(m,"permutation")
            .def(py::init<int>())
            .def(py::init<const permutation &>())
            .def(py::init<const py::list &>())
            .def("__mul__", [] (const permutation & p1, const permutation & p2) -> permutation {return p1*p2;} )
            .def("__str__", & permutation::to_string )
            .def("__repr__", & permutation::to_string )
            .def("__len__", & permutation::size )
            .def("__getitem__", &permutation::py_get)
            .def("__setitem__", &permutation::py_set)
            .def(py::self==py::self)
            .def(py::self!=py::self)
            ;
      }

#endif

  };

};

#endif
