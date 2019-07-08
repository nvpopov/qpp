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
#include <data/generic_array.hpp>

using namespace qpp;

void pyqpp_opaque_types_export(py::module m) {

  generic_array_t<vector3<float>, float>::py_export(m, "array_vector3f");

#ifdef PYTHON_EXP_EXT

  generic_array_t<vector3<double>, double>::py_export(m, "array_vector3d");

#endif

}
