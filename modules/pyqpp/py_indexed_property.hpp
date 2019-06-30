#ifndef QPP_PIP_H
#define QPP_PIP_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
namespace py = pybind11;
#pragma pop_macro("slots")

namespace qpp {

  // ----------------------------------------------

  template<class OWNER, class ELEM, class IDX,
           ELEM (OWNER::*GET)(IDX), void (OWNER::*SET)(IDX, const ELEM &)>
  struct py_indexed_property{

      typedef py_indexed_property<OWNER,ELEM,IDX,GET,SET> SELF;

      OWNER * owner;

      py_indexed_property(){  owner = nullptr;}
      py_indexed_property(OWNER * _owner){ owner = _owner;}
      void bind(OWNER * _owner){owner = _owner;}

      inline ELEM getitem(IDX i)
      { return ((*owner).*GET)(i); }

      inline void setitem(IDX i, const ELEM & e)
      { ((*owner).*SET)(i,e); }

      static void py_export(py::module m, const char * pyname){
        py::module prop = m.def_submodule("props", "props");
        py::class_<SELF>(prop, pyname)
            .def(py::init<>())
            .def(py::init<OWNER*>())
            .def("__getitem__", & SELF::getitem)
            .def("__setitem__", & SELF::setitem)
            ;
      }

  };

  // ---------------------------------------------

  template<class OWNER, class ELEM, class ELEM2, class IDX,
           ELEM (OWNER::*GET)(IDX), void (OWNER::*SET)(IDX, const ELEM &),
           ELEM2 (OWNER::*GET2)(IDX,IDX), void (OWNER::*SET2)(IDX,IDX,const ELEM2 &)>
  struct py_2indexed_property {
      OWNER * owner;
      typedef py_2indexed_property<OWNER,ELEM,ELEM2,IDX,GET,SET,GET2,SET2> SELF2;

      void bind(OWNER * _owner){owner = _owner;}

      inline ELEM getitem(IDX i)
      { return ((*owner).*GET)(i); }

      inline void setitem(IDX i, const ELEM & e)
      { ((*owner).*SET)(i,e); }

      inline ELEM2 getitem2(py::tuple I){
        IDX i = py::cast<IDX>(I[0]);
        IDX j = py::cast<IDX>(I[1]);
        return ((*owner).*GET2)(i,j);
      }

      inline void setitem2(py::tuple I, const ELEM2 & e){
        IDX i=py::cast<IDX>(I[0]), j=py::cast<IDX>(I[1]);
        ((*owner).*SET2)(i,j,e);
      }

      static void py_2export(py::module m, const char * pyname, bool only2 = false)
      {
        if (only2){
            py::module prop = m.def_submodule("props", "props");
            py::class_<SELF2>(prop, pyname)
                .def(py::init<>())
                .def(py::init<OWNER*>())
                .def("__getitem__", & SELF2::getitem2)
                .def("__setitem__", & SELF2::setitem2);
          }
        else{
            py::module prop = m.def_submodule("props", "props");
            py::class_<SELF2>(prop, pyname)
                .def(py::init<>())
                .def(py::init<OWNER*>())
                .def("__getitem__", & SELF2::getitem)
                .def("__setitem__", & SELF2::setitem)
                .def("__getitem__", & SELF2::getitem2)
                .def("__setitem__", & SELF2::setitem2);
          }
      }

      py_2indexed_property(){ owner = nullptr;}
      py_2indexed_property(OWNER * _owner){
        owner = _owner;
      }

  };

} // namespace qpp

#endif

#endif
