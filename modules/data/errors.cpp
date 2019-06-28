#include "errors.hpp"

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

#include <stdexcept>

namespace qpp{

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

  void PyIndexError(const char * msg)
  {
    PyErr_SetString(PyExc_IndexError, msg);
    throw  py::error_already_set();
  }

  void PyTypeError(const char * msg)
  {
    PyErr_SetString(PyExc_TypeError, msg);
    throw  py::error_already_set();
  }

  void PyKeyError(const char * msg)
  {
    PyErr_SetString(PyExc_KeyError, msg);
    throw  py::error_already_set();
  }

  void PyValueError(const char * msg)
  {
    PyErr_SetString(PyExc_ValueError, msg);
    throw  py::error_already_set();
  }

  void PyOverflowError(const char * msg)
  {
    PyErr_SetString(PyExc_OverflowError, msg);
    throw  py::error_already_set();
  }

  void PySyntaxError(const char * msg)
  {
    PyErr_SetString(PyExc_SyntaxError, msg);
    throw  py::error_already_set();
  }

  void StopIter()
  {
    PyErr_SetString(PyExc_StopIteration, "");
    throw  py::error_already_set();
  }

#endif

  void IndexError(const char * msg) {
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
    PyIndexError(msg);
#else
    throw std::out_of_range(msg);
#endif
  }

  void TypeError(const char * msg) {
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
    PyTypeError(msg);
#else
    throw std::invalid_argument(msg);
#endif
  }

  void KeyError(const char * msg) {
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
    PyKeyError(msg);
#else
    throw std::range_error(msg);
#endif
  }

  void ValueError(const char * msg) {
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
    PyValueError(msg);
#else
    throw std::domain_error(msg);
#endif
  }

  void OverflowError(const char * msg)
  {
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
    PyOverflowError(msg);
#else
    throw std::overflow_error(msg);
#endif
  }

  void SyntaxError(const char * msg)
  {
#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
    PySyntaxError(msg);
#else
    throw std::runtime_error(msg);
#endif
  }

}
