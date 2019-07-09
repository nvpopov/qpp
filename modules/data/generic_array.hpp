#ifndef QPP_DATA_GENERIC_ARRAY_H
#define QPP_DATA_GENERIC_ARRAY_H

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
#include <variant>
#include <numeric>
#include <map>
#include <data/types.hpp>

namespace qpp {

    template<typename STORED_TYPE, typename SCALAR_TYPE>
    class generic_array_t : public std::vector<STORED_TYPE> {

        public:

            generic_array_t<STORED_TYPE, SCALAR_TYPE> opaque_vector_mul_el(const SCALAR_TYPE ns) {

              generic_array_t<STORED_TYPE, SCALAR_TYPE> ret;
              ret.reserve(this->size());
              for (size_t i = 0; i < this->size(); i++) ret.push_back(this->at(i) * ns);
              return ret;

            }

            generic_array_t<STORED_TYPE, SCALAR_TYPE> opaque_vector_add(
                    generic_array_t<STORED_TYPE, SCALAR_TYPE> &ns) {

              generic_array_t<STORED_TYPE, SCALAR_TYPE> ret;
              if (this->size() == ns.size()) {
                  ret.reserve(this->size());
                  for (size_t i = 0; i < this->size(); i++)
                    ret.push_back(this->at(i) + ns.at(i));
                }
              return ret;

            }

            STRING_EX to_string_vec() const {

              STRING_EX ret = "[";

              for (size_t i = 0; i < this->size() - 1; i++)
                ret += fmt::format("{},", this->at(i));

              if (!this->empty())
                ret += fmt::format("{}", this->back());

              ret += "]";
              return ret;

            }

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)

            static void py_export(py::module m, const char * pyname) {

                py::class_<generic_array_t<STORED_TYPE, SCALAR_TYPE > > py_opaque_vector(m, pyname);
                py_opaque_vector.def("__len__",
                                     [](generic_array_t<STORED_TYPE, SCALAR_TYPE> &src)
                                     { return src.size();});
                py_opaque_vector.def("__getitem__",
                                     [](generic_array_t<STORED_TYPE, SCALAR_TYPE> &sel, size_t i){
                                      if (i >= sel.size()) throw py::index_error();
                                      return sel[i];
                                    }, py::return_value_policy::copy);
                py_opaque_vector.def("__mul__",
                                     [](generic_array_t<STORED_TYPE, SCALAR_TYPE> &self,
                                     const SCALAR_TYPE ns)
                                     {return self.opaque_vector_mul_el(ns);});
                py_opaque_vector.def("__rmul__",
                                     [](generic_array_t<STORED_TYPE, SCALAR_TYPE> &self,
                                     const SCALAR_TYPE ns)
                                     {return self.opaque_vector_mul_el(ns);});
                py_opaque_vector.def("__add__",
                                     [](generic_array_t<STORED_TYPE, SCALAR_TYPE> &self,
                                     generic_array_t<STORED_TYPE, SCALAR_TYPE> &ns)
                                     {return self.opaque_vector_add(ns);});
                py_opaque_vector.def("__str__",
                                     &generic_array_t<STORED_TYPE, SCALAR_TYPE>::to_string_vec);
                py_opaque_vector.def("__repr__",
                                     &generic_array_t<STORED_TYPE, SCALAR_TYPE>::to_string_vec);

            }

#endif

    };

} // namespace qpp

#endif
