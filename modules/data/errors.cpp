#include "errors.hpp"
#include <stdexcept>

#ifdef PY_EXPORT
#include <boost/python.hpp>
using namespace boost::python;

#endif

namespace qpp{

#ifdef PY_EXPORT

  void PyIndexError(const char * msg)
  {
    PyErr_SetString(PyExc_IndexError, msg);
    throw_error_already_set();
  }

  void PyTypeError(const char * msg)
  {
    PyErr_SetString(PyExc_TypeError, msg);
    throw_error_already_set();
  }

  void PyKeyError(const char * msg)
  {
    PyErr_SetString(PyExc_KeyError, msg);
    throw_error_already_set();
  }

  void PyValueError(const char * msg)
  {
    PyErr_SetString(PyExc_ValueError, msg);
    throw_error_already_set();
  }

  void PySyntaxError(const char * msg)
  {
    PyErr_SetString(PyExc_SyntaxError, msg);
    throw_error_already_set();
  }

  void StopIter()
  {
    PyErr_SetString(PyExc_StopIteration, "");
    throw_error_already_set();
  }

#endif

  void IndexError(const char * msg)
  {
#ifdef PY_EXPORT
    PyIndexError(msg);
#else
    throw std::out_of_range(msg);
#endif
  }

  void TypeError(const char * msg)
  {
#ifdef PY_EXPORT
    PyTypeError(msg);
#else
    throw std::invalid_argument(msg);
#endif
  }

  void KeyError(const char * msg)
  {
#ifdef PY_EXPORT
    PyKeyError(msg);
#else
    throw std::range_error(msg);
#endif
  }

  void ValueError(const char * msg)
  {
#ifdef PY_EXPORT
    PyValueError(msg);
#else
    throw std::domain_error(msg);
#endif
  }

  void SyntaxError(const char * msg)
  {
#ifdef PY_EXPORT
    PySyntaxError(msg);
#else
    throw std::runtime_error(msg);
#endif
  }

}
