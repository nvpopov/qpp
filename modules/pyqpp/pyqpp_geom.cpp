#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
//#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#pragma pop_macro("slots")
namespace py = pybind11;

#include <pyqpp/pyqpp.hpp>
#include <geom/geom.hpp>
#include <symm/gen_cell.hpp>

using namespace qpp;

template<class REAL,class CELL>
void py_geom_export(py::module m, const char * pyname) {

  qpp::geometry<REAL,CELL>::py_props(m, pyname);
  py::class_<qpp::geometry<REAL,CELL>,
             std::shared_ptr<qpp::geometry<REAL,CELL>> >(m, pyname, py::dynamic_attr())
      .def(py::init<int,   const STRING_EX&>(),
           py::arg("dim"), py::arg("__name") = "")
      .def(py::init<CELL&, const STRING_EX&>(),
           py::arg("CELL"), py::arg("__name") = "")
      .def("add_observer",    & qpp::geometry<REAL,CELL>::add_observer )
      .def("remove_observer", & qpp::geometry<REAL,CELL>::remove_observer )
      .def("build_types",     & qpp::geometry<REAL,CELL>::build_type_table)
      .def("add",        &qpp::geometry<REAL,CELL>::py_add1)
      .def("add",        &qpp::geometry<REAL,CELL>::py_add2)
      .def("add",        &qpp::geometry<REAL,CELL>::py_add3)
      .def("erase",      &qpp::geometry<REAL,CELL>::py_erase)
      .def("insert",     &qpp::geometry<REAL,CELL>::py_insert1)
      .def("insert",     &qpp::geometry<REAL,CELL>::py_insert2)
      .def("insert",     &qpp::geometry<REAL,CELL>::py_insert3)
      .def("clear",      &qpp::geometry<REAL,CELL>::clear)
      .def("sort",       &qpp::geometry<REAL,CELL>::sort)
      .def("pos",        &qpp::geometry<REAL,CELL>::py_pos1)
      .def("pos",        &qpp::geometry<REAL,CELL>::py_pos2)
      .def("pos",        &qpp::geometry<REAL,CELL>::py_pos3)
      .def("r",          &qpp::geometry<REAL,CELL>::py_pos1)
      .def("r",          &qpp::geometry<REAL,CELL>::py_pos2)
      .def("r",          &qpp::geometry<REAL,CELL>::py_pos3)
      .def("nat",        &qpp::geometry<REAL,CELL>::nat)
      .def("__len__",    &qpp::geometry<REAL,CELL>::nat)
      .def("__getitem__",&qpp::geometry<REAL,CELL>::py_getitem)
      .def("__setitem__",&qpp::geometry<REAL,CELL>::py_setitem)
      //.add_property("cell",
      //make_getter(& qpp::geometry<REAL,CELL>::cell, return_value_policy<reference_existing_object>()),
      //make_getter(& qpp::geometry<REAL,CELL>::cell, return_self<>()),
      //& qpp::geometry<REAL,CELL>::py_setcell)
      .def_readwrite("name",   &qpp::geometry<REAL,CELL>::name)
      .def_readwrite("cell",   &qpp::geometry<REAL,CELL>::cell)
      .def_readonly( "dim",    &qpp::geometry<REAL,CELL>::DIM)
      .def_readwrite("atom",   &qpp::geometry<REAL,CELL>::py_atoms)
      .def_readwrite("coord",  &qpp::geometry<REAL,CELL>::py_coords)
      .def_readwrite("shadow", &qpp::geometry<REAL,CELL>::py_shadow)
      .def_readwrite("x",      &qpp::geometry<REAL,CELL>::py_x)
      .def_readwrite("y",      &qpp::geometry<REAL,CELL>::py_y)
      .def_readwrite("z",      &qpp::geometry<REAL,CELL>::py_z)

      .def("type",         &qpp::geometry<REAL,CELL>::type_table)
      .def("atom_of_type", &qpp::geometry<REAL,CELL>::atom_of_type)
      .def("type",         &qpp::geometry<REAL,CELL>::py_typeofatom)
      .def("n_types",      &qpp::geometry<REAL,CELL>::n_atom_types)

      .def_readwrite("auto_update_types",
                     &qpp::geometry<REAL,CELL>::auto_update_types,
                     "bool auto_update_types: Whether to update atomic type "
                     "table after any atom manipulations")

      .def_readwrite("frac",
                     &qpp::geometry<REAL,CELL>::frac,
                     "bool frac: Whether to undestand the atomic"
                     " coordinates as fractional")

      .def_readwrite("auto_symmetrize",
                     &qpp::geometry<REAL,CELL>::auto_symmetrize,
                     "bool auto_symmetrize: How to treat atoms added near \
                     'high symmetry points\'.\nIf auto_symmetrize==true,"
                     " put the new atom in high symmetry point instead of "
                     "given coordinates, when the distance\n between atom and "
                     "its image less then symmetrization radius (symmrad)")

      .def_readwrite("default_symmrad",
                     &qpp::geometry<REAL,CELL>::default_symmetrize_radius,
                     "real default_symmrad: symmetrization "
                     "radius for all atoms")

      .def_readwrite("symmrad",
                     &qpp::geometry<REAL,CELL>::py_symmrad,
                     "Usage: symmrad[at] with string at. "
                     "Symmetrization radius for atom at")

      .def("symmrad_to_dict",
           &qpp::geometry<REAL,CELL>::py_symmrad2dict,
           "Outputs the symmrad values in dictionary form")
      .def_readwrite("tol_geom",
                     &qpp::geometry<REAL,CELL>::tol_geom,
                     "real tol_geom. "
                     "The distance at which atoms are considered "
                     "to be at the same point")
      ;
}


template<class REAL>
void py_observer_export(py::module m, const char * pyname) {
  py::class_<qpp::geometry_observer<REAL>,
      qpp::py_geometry_observer<REAL> >(m, pyname)
      .def(py::init<>())
      .def("added",    &qpp::geometry_observer<REAL>::added)
      .def("inserted", &qpp::geometry_observer<REAL>::inserted)
      .def("changed",  &qpp::geometry_observer<REAL>::changed)
      .def("erased",   &qpp::geometry_observer<REAL>::erased)
      .def("shaded",   &qpp::geometry_observer<REAL>::shaded)
      ;
}

void pyqpp_geom_export(py::module m) {

  py_geom_export<float,qpp::periodic_cell<float> >(m, "geometry_f");
  py_geom_export<float, qpp::gen_cell<
      float, qpp::matrix3<float>  > >(m, "geometry_pgf");
  py_geom_export<float, qpp::gen_cell<
      float, qpp::rotrans<float>   > >(m, "geometry_cgf");
  py_observer_export<float>(m, "gobserver_f");

#ifdef PYTHON_EXP_EXT
  py_geom_export<double,qpp::periodic_cell<double> >(m, "geometry_d");
  py_geom_export<double,qpp::gen_cell<
      double, qpp::matrix3<double> > >(m, "geometry_pgd");
  py_geom_export<double,qpp::gen_cell<
      double,qpp::rotrans<double>  > >(m, "geometry_cgd");
  py_observer_export<double>(m, "gobserver_d");
#endif

  py::enum_<qpp::before_after>(m, "geom_change_state")
      .value("before", qpp::before)
      .value("after",  qpp::after)
      ;

}
