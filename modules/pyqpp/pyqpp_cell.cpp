#include <pyqpp/pyqpp.hpp>
#include <symm/cell.hpp>
#include <symm/gcell.hpp>
#include <symm/group_theory.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

template<class REAL>
void py_cell_export(py::module m, const char * pyname)
{
  py::class_<qpp::periodic_cell<REAL> >(m, pyname)
    .def(py::init<int>())
    .def(py::init<
         qpp::vector3d<REAL> ,
         qpp::vector3d<REAL>,
         qpp::vector3d<REAL> >(),
         py::arg("a"),
         py::arg("b")=qpp::vector3d<REAL>(0),
         py::arg("c")=qpp::vector3d<REAL>(0)
         )
    .def(py::init<qpp::periodic_cell<REAL> >())
    .def(py::init<REAL,REAL,REAL,REAL,REAL,REAL>())
    //.def(py::init<py::tuple, optional<py::tuple,py::tuple> >())
    //.def(py::init<list, optional<py::list,py::list> >())
    .def("__getitem__",   & qpp::periodic_cell<REAL>::py_getitem)
    .def("__getitem__",   & qpp::periodic_cell<REAL>::py_getitem2)
    .def("__setitem__",   & qpp::periodic_cell<REAL>::py_setitem)
    .def("__setitem__",   & qpp::periodic_cell<REAL>::py_setitem2)
    .def( "reduce",		  & qpp::periodic_cell<REAL>::reduce)
    .def( "within",		  & qpp::periodic_cell<REAL>::within)
    .def( "transform",	          & qpp::periodic_cell<REAL>::transform)
    .def( "begin",		  & qpp::periodic_cell<REAL>:: begin)
    .def( "end",		  & qpp::periodic_cell<REAL>::end)
    .def( "symmetrize",	          & qpp::periodic_cell<REAL>::symmetrize)
    .def( "frac2cart",	          & qpp::periodic_cell<REAL>::frac2cart)
    .def( "cart2frac",	          & qpp::periodic_cell<REAL>::cart2frac)
    .def( "reduce_cntr",	  & qpp::periodic_cell<REAL>::reduce_cntr)
    .def( "within_centered",      & qpp::periodic_cell<REAL>::within_centered)
    .def( "reduce_wz",	          & qpp::periodic_cell<REAL>::reduce_wz)
    .def( "within_wz",            & qpp::periodic_cell<REAL>::within_wz);
    //TODO: __str__ for cell
   /* .def("__str__", [](const qpp::periodic_cell<REAL> &c){
      return fmt::format("[{0}, {1}, {2}], d={3}", c.v[]);})*/

}

template <class REAL, class TRANSFORM, class ARRAY = std::vector<TRANSFORM> >
void py_generator_form(qpp::generalized_cell<REAL,TRANSFORM> & R, ARRAY & G)
{
  qpp::generator_form(R,G);
}

void pyqpp_cell_export(py::module m){

  py_cell_export<float>(m, "periodic_cell_f");
  py_cell_export<double>(m, "periodic_cell_d");

  qpp::generalized_cell<float,  qpp::matrix3d<float> >::py_export(
      m, "point_group_f");
  qpp::generalized_cell<double, qpp::matrix3d<double> >::py_export(
      m, "point_group_d");

  qpp::generalized_cell<float,  qpp::rotrans<float,false> >::py_export(
      m, "crystal_group_f");
  qpp::generalized_cell<double, qpp::rotrans<double,false> >::py_export(
      m, "crystal_group_d");

  qpp::generalized_cell<float,  qpp::rotrans<float,true> >::py_export(
      m, "finite_crystal_group_f");
  qpp::generalized_cell<double, qpp::rotrans<double,true> >::py_export(
      m, "finite_crystal_group_d");

  qpp::generated_group<qpp::matrix3d<float> >::py_export(
      m, "array_point_group_f");
  qpp::generated_group<qpp::matrix3d<double> >::py_export(
      m, "array_point_group_d");
  qpp::generated_group<qpp::rotrans<float,true> >::py_export(
      m, "array_fincryst_group_f");
  qpp::generated_group<qpp::rotrans<double,true> >::py_export(
      m, "array_fincryst_group_d");

  m.def("generator_form", py_generator_form<double, qpp::matrix3d<double>,
      qpp::generated_group<qpp::matrix3d<double> > >);
  m.def("generator_form", py_generator_form<float,  qpp::matrix3d<float>,
      qpp::generated_group<qpp::matrix3d<float> > > );
  m.def("generator_form", py_generator_form<double, qpp::rotrans<double,true>,
      qpp::generated_group<qpp::rotrans<double,true> > >);
  m.def("generator_form", py_generator_form<float,  qpp::rotrans<float,true>,
      qpp::generated_group<qpp::rotrans<float,true> > >);

}

