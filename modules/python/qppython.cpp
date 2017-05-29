#define PY_EXPORT

#include <python/qppcpp.hpp>
#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/return_internal_reference.hpp>

using namespace boost::python;
namespace sn = boost::python::self_ns;


namespace qpp{

  void IndexError(const char * msg)
  {
    PyErr_SetString(PyExc_IndexError, msg);
    throw_error_already_set();
  }

  void TypeError(const char * msg)
  {
    PyErr_SetString(PyExc_TypeError, msg);
    throw_error_already_set();
  }

  void KeyError(const char * msg)
  {
    PyErr_SetString(PyExc_KeyError, msg);
    throw_error_already_set();
  }

  void StopIter()
  {
    PyErr_SetString(PyExc_StopIteration, "");
    throw_error_already_set();
  }

};

BOOST_PYTHON_MODULE(qpp_cpp)
{  
  qpp_export1();
  qpp_export2();
  qpp_export3();
  qpp_export4();
  qpp_export5();
  qpp_export6();
  
}
