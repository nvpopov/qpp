#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/iostream.h>
#pragma pop_macro("slots")

namespace py = pybind11;

#include <pyqpp/pyqpp.hpp>
#include <geom/lace3d.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

using namespace qpp;

template<typename TYPE>
void pyqpp_export_opaque_array(py::module m, const char * pyname) {

  py::class_<std::vector<TYPE> > py_opaque_vector(m, pyname);
  py_opaque_vector.def("__len__", [](std::vector<TYPE> &src){ return src.size();});
  py_opaque_vector.def("__getitem__", [](std::vector<TYPE> &selg, size_t i) {
    if (i >= selg.size()) throw py::index_error();
    return selg[i];
  }, py::return_value_policy::copy);

}


void pyqpp_opaque_types_export(py::module m) {

  pyqpp_export_opaque_array<vector3<float> >(m, "array_vector3f");

#ifdef PYTHON_EXP_EXT

  pyqpp_export_opaque_array<vector3<double> >(m, "array_vector3d");

#endif

}
