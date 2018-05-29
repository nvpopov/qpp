#include <pyqpp/pyqpp.hpp>
#include <symm/index.hpp>
#include <geom/lace3d.hpp>
#include <symm/transform.hpp>

template<class VALTYPE>
inline VALTYPE py_vec_scal(const qpp::vector3d<VALTYPE> & x,
                           const qpp::vector3d<VALTYPE> & y)
{ return qpp::scal(x,y); }

template<class VALTYPE>
inline typename qpp::numeric_type<VALTYPE>::norm py_vec_norm(
    const qpp::vector3d<VALTYPE> & x)
{ return x.norm(); }

template<class VALTYPE>
void py_vector3d_export(const char * pyname, py::module m){
  py::class_<qpp::vector3d<VALTYPE> >(m, pyname )
    .def(py::init<>())
    .def(py::init<VALTYPE,VALTYPE,VALTYPE>())
    .def(py::init<const py::list&>())
    .def(py::init<const py::tuple&>())
    .def(py::init<const qpp::vector3d<VALTYPE>&>())
    //.def(py::str(py::self))
    .def("__add__",     & qpp::vector3d<VALTYPE>::py_add)
    .def("__sub__",     & qpp::vector3d<VALTYPE>::py_sub)
    .def("__getitem__", & qpp::vector3d<VALTYPE>::py_getitem)
    .def("__setitem__", & qpp::vector3d<VALTYPE>::py_setitem)
    .def("__mul__",     & qpp::vector3d<VALTYPE>::py_mul)
    .def("__div__",     & qpp::vector3d<VALTYPE>::py_div)
    .def("__rmul__",    & qpp::vector3d<VALTYPE>::py_mul)
    .def("norm",        & qpp::vector3d<VALTYPE>::py_norm)
    .def("norm2",       & qpp::vector3d<VALTYPE>::py_norm2)
    .def_property("x",  & qpp::vector3d<VALTYPE>::py_getx, & qpp::vector3d<VALTYPE>::py_setx)
    .def_property("y",  & qpp::vector3d<VALTYPE>::py_gety, & qpp::vector3d<VALTYPE>::py_sety)
    .def_property("z",  & qpp::vector3d<VALTYPE>::py_getz, & qpp::vector3d<VALTYPE>::py_setz);
   // .def_readwrite("tol_equiv", &qpp::vector3d<VALTYPE>::tol_equiv) ;
    //.def("y",           & qpp::vector3d<VALTYPE>::y)
    //.def("z",           & qpp::vector3d<VALTYPE>::z)

  m.def("scal", py_vec_scal<VALTYPE>);
  //def("norm", py_vec_norm<VALTYPE>);
}
/*
template<class VALTYPE>
void py_matrix3d_export(const char * pyname){
  py::class_<qpp::matrix3d<VALTYPE> >(pyname)
    .def(init<>())
    .def(init<const qpp::matrix3d<VALTYPE>&>())
    .def(init<VALTYPE,VALTYPE,VALTYPE,VALTYPE,VALTYPE,VALTYPE,VALTYPE,VALTYPE,VALTYPE>())
    .def(init<VALTYPE>())
    .def(init<const qpp::vector3d<VALTYPE>&, const qpp::vector3d<VALTYPE>&, const qpp::vector3d<VALTYPE>&>())
    .def(init<const list&>())
    .def(init<const tuple&>())
    .def(sn::str(sn::self))
    .def(sn::repr(sn::self))
    .def(sn::self - sn::self)
    .def(sn::self + sn::self)
    .def(sn::self * sn::self)
    .def(sn::self == sn::self)
    .def(sn::self != sn::self)
    .def("__getitem__", & qpp::matrix3d<VALTYPE>::py_getitemv)
    .def("__setitem__", & qpp::matrix3d<VALTYPE>::py_setitemv)
    .def("__getitem__", & qpp::matrix3d<VALTYPE>::py_getitem)
    .def("__setitem__", & qpp::matrix3d<VALTYPE>::py_setitem)
    .def("__mul__",     & qpp::matrix3d<VALTYPE>::py_muln)
    .def("__div__",     & qpp::matrix3d<VALTYPE>::py_divn)
    .def("__rmul__",    & qpp::matrix3d<VALTYPE>::py_muln)
    .def("__mul__",     & qpp::matrix3d<VALTYPE>::py_mulv)
    .def("norm",        & qpp::matrix3d<VALTYPE>::norm)
    .def("norm2",       & qpp::matrix3d<VALTYPE>::norm2)
    .def("det",         & qpp::matrix3d<VALTYPE>::det)
    .def("T",           & qpp::matrix3d<VALTYPE>::T)
    .add_property("xx",  & qpp::matrix3d<VALTYPE>::py_getxx, & qpp::matrix3d<VALTYPE>::py_setxx)
    .add_property("xy",  & qpp::matrix3d<VALTYPE>::py_getxy, & qpp::matrix3d<VALTYPE>::py_setxy)
    .add_property("xz",  & qpp::matrix3d<VALTYPE>::py_getxz, & qpp::matrix3d<VALTYPE>::py_setxz)
    .add_property("yx",  & qpp::matrix3d<VALTYPE>::py_getyx, & qpp::matrix3d<VALTYPE>::py_setyx)
    .add_property("yy",  & qpp::matrix3d<VALTYPE>::py_getyy, & qpp::matrix3d<VALTYPE>::py_setyy)
    .add_property("yz",  & qpp::matrix3d<VALTYPE>::py_getyz, & qpp::matrix3d<VALTYPE>::py_setyz)
    .add_property("zx",  & qpp::matrix3d<VALTYPE>::py_getzx, & qpp::matrix3d<VALTYPE>::py_setzx)
    .add_property("zy",  & qpp::matrix3d<VALTYPE>::py_getzy, & qpp::matrix3d<VALTYPE>::py_setzy)
    .add_property("zz",  & qpp::matrix3d<VALTYPE>::py_getzz, & qpp::matrix3d<VALTYPE>::py_setzz)
    .def_readwrite("tol_equiv", & qpp::matrix3d<VALTYPE>::tol_equiv)
    ;
  py::def("det",       qpp::py_detm<VALTYPE>);
  py::def("det",       qpp::py_detv<VALTYPE>);
  py::def("outer",     qpp::outer<VALTYPE>);
  py::def("solve3",    qpp::py_solve3m<VALTYPE>);
  py::def("solve3",    qpp::py_solve3v<VALTYPE>);
  py::def("invert3",   qpp::py_invert_mtr<VALTYPE>);
  py::def("pow",       qpp::py_pow_mtr<VALTYPE>);
}

template<class VALTYPE>
void py_eigen3_export(){
  py::def("RotMtrx",   qpp::py_rotmtrx_v<VALTYPE>);
  py::def("RotMtrx",   qpp::py_rotmtrx_t<VALTYPE>);
  py::def("RotMtrx",   qpp::py_rotmtrx_l<VALTYPE>);
  py::def("Sigma",     qpp::py_sigma_v<VALTYPE>);
  py::def("Sigma",     qpp::py_sigma_t<VALTYPE>);
  py::def("Sigma",     qpp::py_sigma_l<VALTYPE>);
  py::def("diagon3",   qpp::py_diagon3dv<VALTYPE>);
  py::def("diagon3",   qpp::py_diagon3dm<VALTYPE>);
  py::def("diagon3",   qpp::py_diagon3dreal<VALTYPE>);
  py::def("solve_cubeq",   qpp::solve_cubeq<VALTYPE>);
}

template<class REAL, bool BOUND>
void py_rotrans_export(const char * pyname){
  if (BOUND)
    py::class_<qpp::rotrans<REAL,BOUND> >(pyname, init<>())
      .def(init<const qpp::rotrans<REAL,BOUND> >())
      .def(init<const qpp::vector3d<REAL>, qpp::periodic_cell<REAL>* >())
      .def(init<const qpp::matrix3d<REAL>, qpp::periodic_cell<REAL>*  >())
      .def(init<const qpp::vector3d<REAL>, const qpp::matrix3d<REAL>, qpp::periodic_cell<REAL>* >())
      .def("__mul__", & qpp::rotrans<REAL,BOUND>::py_mulr)
      .def("__mul__", & qpp::rotrans<REAL,BOUND>::py_mulv)
      .def(sn::str(sn::self))
      .def(sn::repr(sn::self))
      .def(sn::self==sn::self)
      .def(sn::self!=sn::self)
      .def_readwrite("unity", & qpp::rotrans<REAL,BOUND>::unity)
      .def_readwrite("T", & qpp::rotrans<REAL,BOUND>::T)
      .def_readwrite("R", & qpp::rotrans<REAL,BOUND>::R)
      .def_readwrite("tol_trans",& qpp::rotrans<REAL,BOUND>::translation_tolerance)
      .def_readwrite("tol_rot",& qpp::rotrans<REAL,BOUND>::rotation_tolerance)
      .add_property("cell", make_getter(& qpp::rotrans<REAL,BOUND>::cell, return_value_policy<reference_existing_object>()))
     ;
  else
    py::class_<qpp::rotrans<REAL,BOUND> >(pyname, init<>())
      .def(init<const qpp::rotrans<REAL,BOUND> >())
      .def(init<const qpp::vector3d<REAL> >())
      .def(init<const qpp::matrix3d<REAL> >())
      .def(init<const qpp::vector3d<REAL>, const qpp::matrix3d<REAL> >())
      .def("__mul__", & qpp::rotrans<REAL,BOUND>::py_mulr)
      .def("__mul__", & qpp::rotrans<REAL,BOUND>::py_mulv)
      .def(sn::str(sn::self))
      .def(sn::repr(sn::self))
      .def(sn::self==sn::self)
      //.def(sn::self!=sn::self)
      .def("__ne__", & qpp::rotrans<REAL,BOUND>::operator!=)
      .def_readwrite("unity", & qpp::rotrans<REAL,BOUND>::unity)
      .def_readwrite("T", & qpp::rotrans<REAL,BOUND>::T)
      .def_readwrite("R", & qpp::rotrans<REAL,BOUND>::R)
      .def_readwrite("tol_trans",& qpp::rotrans<REAL,BOUND>::translation_tolerance)
      .def_readwrite("tol_rot",& qpp::rotrans<REAL,BOUND>::rotation_tolerance)
      ;
  py::def("invert", qpp::py_invert_rt<REAL,BOUND>);
  py::def("pow",    qpp::py_pow_rt<REAL,BOUND>);
}*/

void pyqpp_linalg_export(py::module m){

  py_vector3d_export<float>("vector3f", m);
  py_vector3d_export<double>("vector3d", m);
  py_vector3d_export<std::complex<float> >("vector3c", m);
  py_vector3d_export<std::complex<double> >("vector3z", m);

  /*
  py_matrix3d_export<float>("matrix3f");
  py_matrix3d_export<double>("matrix3d");
  py_matrix3d_export<std::complex<float> >("matrix3c");
  py_matrix3d_export<std::complex<double> >("matrix3z");

  py_eigen3_export<float>();
  py_eigen3_export<double>();

  py_rotrans_export<float,false>("rotrans_f");
  py_rotrans_export<double,false>("rotrans_d");
  py_rotrans_export<float,true>("bound_rotrans_f");
  py_rotrans_export<double,true>("bound_rotrans_d");

  qpp::index::py_export("index");
  qpp::iterator::py_export("iterator");
  qpp::index_range::py_export("index_range");*/
}