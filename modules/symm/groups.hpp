#ifndef QPP_SYMM_H
#define QPP_SYMM_H
#include <data/types.hpp>
#include <symm/index.hpp>
#include <vector>

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

namespace qpp {

  /*!\brief The genform_group class implements
    Positionary Generator Form (PGF) for arbitrary finite group.
  */
  template <class TRANSFORM>
  class genform_group {
    public:

      std::vector<TRANSFORM> generators;
      index _begin, _end;
      int DIM;
      STRING_EX name;

      genform_group(int dim = 0,
                    const STRING_EX & _name = "") {
        DIM=dim;
        generators.resize(DIM);
        _begin = index::D(DIM);
        _end   = index::D(DIM);
        name = _name;
      }

      genform_group(const std::vector<TRANSFORM> & g,
                    const index & __begin,
                    const index & __end,
                    const STRING_EX & _name = "") {
        DIM = g.size();
        generators.resize(DIM);
        int d=0;
        for (const TRANSFORM & t : g)
          generators[d++]=t;
        _begin = __begin;
        _end   = __end;
        name = _name;
      }

      genform_group(const std::vector<TRANSFORM> & g, const STRING_EX & _name = "") {
        DIM = g.size();
        generators.resize(DIM);

        int d=0;
        for (const TRANSFORM & t : g)
          generators[d++]=t;

        _begin = index::D(DIM);
        _end   = index::D(DIM);
        name = _name;
      }

      genform_group(const genform_group<TRANSFORM> & G) :
        DIM(G.DIM), generators(G.generators), _begin(G._begin), _end(G._end), name(G.name)
      {}

      int get_dim(){return DIM;}

      void set_dim(int D){
        DIM = D;
        generators.resize(DIM);

        _begin = index::D(DIM);
        _end   = index::D(DIM);
      }

      TRANSFORM operator()(const index & n) const {
        if (DIM==0)
          return TRANSFORM::unity;

        //TRANSFORM A = pow(generators[0],n(0));
        TRANSFORM A = generators[0].pow(n(0));
        for (int d = 1; d<DIM; d++){
            //A = A*pow(generators[d],n(d));
            TRANSFORM Anp = A * generators[d].pow(n(d));
            A = Anp;
          }
        return A;
      }

      template <class ARRAY>
      void generate(ARRAY & group) {
        for (iterator n(_begin, _end); !n.end(); n++)
          group.push_back((*this)(n));
      }

      void auto_order(int d) {
        _begin(d) = 0;
        const TRANSFORM & g = generators[d];
        TRANSFORM a = g;
        int n=1;
        while (a != TRANSFORM::unity){
            a = a*g;
            n++;
          }
        _end(d) = n-1;
      }

      void auto_orders() {
        for (int d=0; d<DIM; d++)
          auto_order(d);
      }

      inline index begin() const
      { return _begin;}

      inline index end() const
      { return _end;}

  };

  // ------------------------------------------------------------------------
  /*
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  template<class TRANSFORM> class array_group;

  template <class TRANSFORM>
  int py_group_len(const array_group<TRANSFORM> & G)
  {
    return G.size();
  }

#endif
  */
  // ------------------------------------------------------------------------

  template<class TRANSFORM>
  class array_group {
    public:

      static int default_lim_size;
      int lim_size;
      STRING_EX name;

      std::vector<TRANSFORM> group;

      int index(const TRANSFORM & g) {
        int i;
        bool result=false;
        for (i = 0; i < group.size(); i++)
          if ( group[i] == g ){
              result = true;
              break;
            }
        return result? i : -1;
      }

      array_group(const STRING_EX & _name="",
                  TRANSFORM E = TRANSFORM::unity) {
        name = _name;
        group.push_back(E);
        lim_size = default_lim_size;
      }

      array_group(const array_group<TRANSFORM> & G):
        group(G.group), lim_size(G.lim_size), name(G.name)
      {}

      inline TRANSFORM & operator[](int i)
      { return group[i]; }

      inline TRANSFORM operator[](int i) const
      { return group[i]; }

      inline int size() const
      { return group.size(); }

      void add(const TRANSFORM & g) {
        if ( index(g) >= 0 )
          return;
        group.push_back(g);
      }

      void erase(int i){
        group.erase(group.begin()+i);
      }

      void generate(const TRANSFORM & g){
        if ( index(g) >= 0 )
          return;
        int inew = size();
        group.push_back(g);

        while (inew < size()){
            //std::cout << size() << "\n";

            int inewest = size();
            for (int ig1 = 0; ig1 < inewest; ig1++)
              for (int ig2 = inew; ig2 < inewest; ig2++) {
                  //std::cout << "ig1= " << ig1 << " ig2= " << ig2 << "\n";

                  TRANSFORM h1 = group[ig1]*group[ig2];

                  //std::cout << "h1= " << h1 << "\n";

                  if (index(h1)==-1)
                    group.push_back(h1);
                  TRANSFORM h2 = group[ig2]*group[ig1];

                  //std::cout << "h2= " << h2 << "\n";
                  //if (!(h2 == h1) && index(h2)==-1)
                  if ((h2 != h1) && index(h2) == -1)
                    group.push_back(h2);

                  if (size() > lim_size)
                    OverflowError("array_group size exceeded the size limit\nWhat you can do:\n 1) "
                                  "Set larger lim_size value;\n 2) Check if the group is indeed"
                                  " finite;\n");
                }
            //std::cout << inew << " " << inewest << "\n";

            inew = inewest;
          }
      }

      virtual void write(std::basic_ostream<CHAR_EX,TRAITS> &os,
                         int offset=0) const {
        // fixme
      }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

      inline TRANSFORM py_getitem(int i){
        if (i<0)
          i += size();
        if (i<0 || i>=size())
          IndexError("cell: index out of range");
        return group[i];
      }

      inline void py_setitem(int i, const TRANSFORM & t){
        if (i<0)
          i += size();
        if (i<0 || i>=size())
          IndexError("cell: index out of range");
        group[i] = t;
      }

      static void py_export(py::module m, const char * pyname){
        py::class_<array_group<TRANSFORM>, std::shared_ptr<array_group<TRANSFORM> > >(m, pyname)
            .def(py::init<const STRING_EX &, TRANSFORM>(),
                 py::arg("_name") = "",
                 py::arg("E") = TRANSFORM::unity )
            .def(py::init<const array_group<TRANSFORM> &>())
            .def("index",  & array_group<TRANSFORM>::index )
            .def("add",    & array_group<TRANSFORM>::add )
            .def("generate", & array_group<TRANSFORM>::generate )
            .def("erase",  & array_group<TRANSFORM>::erase )
            .def("__getitem__",  & array_group<TRANSFORM>::py_getitem)
            .def("__setitem__",  & array_group<TRANSFORM>::py_setitem)
            .def("__len__", & array_group<TRANSFORM>::size)
            .def_readwrite("name", & array_group<TRANSFORM>::name)
            .def_readwrite("lim_size", & array_group<TRANSFORM>::lim_size)
            .def_readwrite_static("default_lim_size", & array_group<TRANSFORM>::default_lim_size)
            ;
        // bp::def("len", py_group_len<TRANSFORM>);
      }

#endif

  };

  template<class TRANSFORM>
  int array_group<TRANSFORM>::default_lim_size = 1024;

}

#endif
