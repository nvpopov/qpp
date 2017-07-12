#include "qppcpp.hpp"
#include <geom/shape.hpp>

template<class REAL>
void py_shape_export(const char * pyname)
{
  class_<qpp::py_shape<REAL>,boost::noncopyable>(pyname)
    .def("within",    pure_virtual( & qpp::shape<REAL>::within))
    .def("scale",     pure_virtual( & qpp::shape<REAL>::scale))
    .def("move",      pure_virtual( & qpp::shape<REAL>::move))    
    .def("rotate",    pure_virtual( & qpp::shape<REAL>::rotate))
    .def("volume",    pure_virtual( & qpp::shape<REAL>::volume))
    .def("rmin",      pure_virtual( & qpp::shape<REAL>::rmin))
    .def("rmax",      pure_virtual( & qpp::shape<REAL>::rmax))
    .def("fmin",      pure_virtual( & qpp::shape<REAL>::fmin))
    .def("fmax",      pure_virtual( & qpp::shape<REAL>::fmax))
    .def("write",     pure_virtual( & qpp::shape<REAL>::write))
    .def("__or__",     & qpp::shape<REAL>::py_or,  bp::return_value_policy<bp::manage_new_object>())
    .def("__and__",    & qpp::shape<REAL>::py_and, bp::return_value_policy<bp::manage_new_object>())
    .def("__sub__",    & qpp::shape<REAL>::py_sub, bp::return_value_policy<bp::manage_new_object>())
    .def("__xor__",    & qpp::shape<REAL>::py_xor, bp::return_value_policy<bp::manage_new_object>())
    .def("__invert__", & qpp::shape<REAL>::py_inv, bp::return_value_policy<bp::manage_new_object>())
    ;
}

void qpp_export6()
{
  
  qpp::shape<float>::py_export("abstract_shape_f");
  qpp::shape<double>::py_export("abstract_shape_d");
  
  py_shape_export<float>("shape_f");
  py_shape_export<double>("shape_d");

  /*
  def("shape_box_f", qpp::py_shape_box1<float>, return_value_policy<manage_new_object>());
  def("shape_box_f", qpp::py_shape_box2<float>, return_value_policy<manage_new_object>());
  def("shape_box_f", qpp::py_shape_box3<float>, return_value_policy<manage_new_object>());
  def("shape_box_d", qpp::py_shape_box1<double>, return_value_policy<manage_new_object>());
  def("shape_box_d", qpp::py_shape_box2<double>, return_value_policy<manage_new_object>());
  def("shape_box_d", qpp::py_shape_box3<double>, return_value_policy<manage_new_object>());
  */
  
  qpp::shape_box<float>::py_export("shape_box_f");
  qpp::shape_box<double>::py_export("shape_box_d");

  qpp::shape_sphere<float>::py_export("shape_sphere_f");
  qpp::shape_sphere<double>::py_export("shape_sphere_d");
  
}
