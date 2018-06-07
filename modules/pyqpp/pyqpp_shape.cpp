#include <pyqpp/pyqpp.hpp>
#include <geom/shape.hpp>

#define v2d qpp::vector2d<REAL>
#define v3d qpp::vector3d<REAL>

template<class REAL>
void py_shape_export(py::module m, const char * pyname){
  py::class_<qpp::shape<REAL>,qpp::py_shape<REAL> > ashape(m, pyname);

    ashape.def(py::init<>())
    .def("within",    & qpp::shape<REAL>::within)
    .def("scale",     & qpp::shape<REAL>::scale)
    .def("move",      & qpp::shape<REAL>::move)
    .def("rotate",    & qpp::shape<REAL>::rotate)
    .def("volume",    & qpp::shape<REAL>::volume)
    .def("rmin",      & qpp::shape<REAL>::rmin)
    .def("rmax",      & qpp::shape<REAL>::rmax)
    .def("fmin",      & qpp::shape<REAL>::fmin)
    .def("fmax",      & qpp::shape<REAL>::fmax)
    .def("write",     & qpp::shape<REAL>::write)
      // TODO: bp::return_value_policy<bp::manage_new_object>() start
    .def("__or__",     & qpp::shape<REAL>::py_or)
    .def("__and__",    & qpp::shape<REAL>::py_and)
    .def("__sub__",    & qpp::shape<REAL>::py_sub)
    .def("__xor__",    & qpp::shape<REAL>::py_xor)
    .def("__invert__", & qpp::shape<REAL>::py_inv)
       // bp::return_value_policy<bp::manage_new_object>() end
    ;

    std::string boxShapeName = "box_"+std::string(pyname);
    py::class_<qpp::shape_box<REAL> >(m, boxShapeName.c_str(), ashape)
        .def(py::init<const v3d&,
             const v3d&,
             const v3d&,
             const v3d&,
             const STRING & >())
     //TODO bp::optional<const STRING &> >())
        .def(py::init<const v3d&,
             const v3d&,
             const v3d&,
             const STRING & >())
     //TODO const v3d&, bp::optional<const STRING &> >())
        .def(py::init<REAL, REAL, REAL,
             const STRING & >())
        ;
    std::string sphereShapeName = "sphere_"+std::string(pyname);
    py::class_<qpp::shape_sphere<REAL> >(m, sphereShapeName.c_str(), ashape)
      .def(py::init<REAL,
          const STRING & >()) //bp::optional<const STRING &> >())
      .def(py::init<REAL,
           const v3d&, const STRING &>())//bp::optional<const STRING &> >()
      ;
}

void pyqpp_shape_export(py::module m){

  //qpp::shape<float>::py_export(m, "abstract_shape_f");
  //qpp::shape<double>::py_export(m, "abstract_shape_d");

  py_shape_export<float>(m, "shape_f");
  py_shape_export<double>(m, "shape_d");

  /*
  def("shape_box_f", qpp::py_shape_box1<float>, return_value_policy<manage_new_object>());
  def("shape_box_f", qpp::py_shape_box2<float>, return_value_policy<manage_new_object>());
  def("shape_box_f", qpp::py_shape_box3<float>, return_value_policy<manage_new_object>());
  def("shape_box_d", qpp::py_shape_box1<double>, return_value_policy<manage_new_object>());
  def("shape_box_d", qpp::py_shape_box2<double>, return_value_policy<manage_new_object>());
  def("shape_box_d", qpp::py_shape_box3<double>, return_value_policy<manage_new_object>());
  */

  //qpp::shape_box<float>::py_export(m, "shape_box_f");
 // qpp::shape_box<double>::py_export(m, "shape_box_d");

/*
  qpp::shape_sphere<float>::py_export(m, "shape_sphere_f");
  qpp::shape_sphere<double>::py_export(m, "shape_sphere_d");
*/
}
#undef v3d
#undef v2d