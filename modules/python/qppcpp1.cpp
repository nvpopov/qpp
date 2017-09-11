#include "qppcpp.hpp"
#include <python/qppython.hpp>
#include <symm/index.hpp>
#include <geom/lace3d.hpp>
#include <symm/transform.hpp>

template<class VALTYPE>
inline VALTYPE py_vec_scal(const qpp::vector3d<VALTYPE> & x, const qpp::vector3d<VALTYPE> & y)
{ return qpp::scal(x,y); }

template<class VALTYPE>
inline typename qpp::numeric_type<VALTYPE>::norm py_vec_norm(const qpp::vector3d<VALTYPE> & x)
{ return x.norm(); }

template<class VALTYPE>
void py_vector3d_export(const char * pyname)
{
  class_<qpp::vector3d<VALTYPE> >(pyname)
    .def(init<>())
    .def(init<VALTYPE,VALTYPE,VALTYPE>())
    .def(init<const list&>())
    .def(init<const tuple&>())
    .def(init<const qpp::vector3d<VALTYPE>&>())
    .def(sn::str(sn::self))
    .def(sn::repr(sn::self))
    .def(sn::self == sn::self)
    .def(sn::self != sn::self)
    .def(sn::self % sn::self)	
    .def("__add__",     & qpp::vector3d<VALTYPE>::py_add)
    .def("__sub__",     & qpp::vector3d<VALTYPE>::py_sub)
    .def("__getitem__", & qpp::vector3d<VALTYPE>::py_getitem)
    .def("__setitem__", & qpp::vector3d<VALTYPE>::py_setitem)
    .def("__mul__",     & qpp::vector3d<VALTYPE>::py_mul)
    .def("__div__",     & qpp::vector3d<VALTYPE>::py_div)
    .def("__rmul__",    & qpp::vector3d<VALTYPE>::py_mul)
    .def("norm",        & qpp::vector3d<VALTYPE>::py_norm)
    .def("norm2",       & qpp::vector3d<VALTYPE>::py_norm2)
    .add_property("x",  & qpp::vector3d<VALTYPE>::py_getx, & qpp::vector3d<VALTYPE>::py_setx)
    .add_property("y",  & qpp::vector3d<VALTYPE>::py_gety, & qpp::vector3d<VALTYPE>::py_sety)
    .add_property("z",  & qpp::vector3d<VALTYPE>::py_getz, & qpp::vector3d<VALTYPE>::py_setz)
    .def_readwrite("tol_equiv", & qpp::vector3d<VALTYPE>::tol_equiv)
    //.def("y",           & qpp::vector3d<VALTYPE>::y)
    //.def("z",           & qpp::vector3d<VALTYPE>::z)
    ;
  def("scal", py_vec_scal<VALTYPE>);
  //def("norm", py_vec_norm<VALTYPE>);
}

template<class VALTYPE>
void py_matrix3d_export(const char * pyname)
{
  class_<qpp::matrix3d<VALTYPE> >(pyname)
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
  def("det",       qpp::py_detm<VALTYPE>);
  def("det",       qpp::py_detv<VALTYPE>);
  def("outer",     qpp::outer<VALTYPE>);
  def("solve3",    qpp::py_solve3m<VALTYPE>);
  def("solve3",    qpp::py_solve3v<VALTYPE>);
  def("invert3",   qpp::py_invert_mtr<VALTYPE>);
  def("pow",       qpp::py_pow_mtr<VALTYPE>);
}

template<class VALTYPE>
void py_eigen3_export()
{
  def("RotMtrx",   qpp::py_rotmtrx_v<VALTYPE>);
  def("RotMtrx",   qpp::py_rotmtrx_t<VALTYPE>);
  def("RotMtrx",   qpp::py_rotmtrx_l<VALTYPE>);
  def("Sigma",     qpp::py_sigma_v<VALTYPE>);
  def("Sigma",     qpp::py_sigma_t<VALTYPE>);
  def("Sigma",     qpp::py_sigma_l<VALTYPE>);
  def("diagon3",   qpp::py_diagon3dv<VALTYPE>);
  def("diagon3",   qpp::py_diagon3dm<VALTYPE>);
  def("diagon3",   qpp::py_diagon3dreal<VALTYPE>);
  def("solve_cubeq",   qpp::solve_cubeq<VALTYPE>);
}

template<class REAL, bool BOUND>
void py_rotrans_export(const char * pyname)
{
  if (BOUND)
    class_<qpp::rotrans<REAL,BOUND> >(pyname, init<>())
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
      .add_property("cell", make_getter(& qpp::rotrans<REAL,BOUND>::cell, return_value_policy<reference_existing_object>()))
     ;
  else
    class_<qpp::rotrans<REAL,BOUND> >(pyname, init<>())
      .def(init<const qpp::rotrans<REAL,BOUND> >())
      .def(init<const qpp::vector3d<REAL> >())
      .def(init<const qpp::matrix3d<REAL> >())
      .def(init<const qpp::vector3d<REAL>, const qpp::matrix3d<REAL> >())
      .def("__mul__", & qpp::rotrans<REAL,BOUND>::py_mulr)
      .def("__mul__", & qpp::rotrans<REAL,BOUND>::py_mulv)
      .def(sn::str(sn::self))
      .def(sn::repr(sn::self))
      .def(sn::self==sn::self)
      .def(sn::self!=sn::self)
      .def_readwrite("unity", & qpp::rotrans<REAL,BOUND>::unity)
      .def_readwrite("T", & qpp::rotrans<REAL,BOUND>::T)
      .def_readwrite("R", & qpp::rotrans<REAL,BOUND>::R)
      ;
  def("invert", qpp::py_invert_rt<REAL,BOUND>);
  def("pow",    qpp::py_pow_rt<REAL,BOUND>);
}

void qpp_export1()
{

  py_vector3d_export<float>("vector3f");
  py_vector3d_export<double>("vector3d");
  py_vector3d_export<std::complex<float> >("vector3c");
  py_vector3d_export<std::complex<double> >("vector3z");
  
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
  qpp::index_range::py_export("index_range");
}
