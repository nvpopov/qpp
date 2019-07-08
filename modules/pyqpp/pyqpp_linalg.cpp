#include <pyqpp/pyqpp.hpp>
#include <symm/index.hpp>
#include <geom/lace3d.hpp>
#include <symm/transform.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

template<class VALTYPE>
void py_vector3_export (py::module m, const char * pyname) {

  py::class_<qpp::vector3<VALTYPE> >(m, pyname )
      .def(py::init<>())
      .def(py::init<VALTYPE, VALTYPE, VALTYPE>())
      .def(py::init<VALTYPE>())
      .def(py::init<const py::list&>())
      .def(py::init<const py::tuple&>())
      .def(py::init<const qpp::vector3<VALTYPE>&>())

      .def("__str__", &qpp::vector3<VALTYPE>::to_string_vec)
      .def("__repr__", &qpp::vector3<VALTYPE>::to_string_vec)

      .def("__add__", [](qpp::vector3<VALTYPE> &self, qpp::vector3<VALTYPE> &other)
        {return self.sum_proxy(other);})

      .def("__sub__", [](qpp::vector3<VALTYPE> &self, qpp::vector3<VALTYPE> &other)
        {return self.sub_proxy(other);})

      .def("__mul__", [](qpp::vector3<VALTYPE> &self, const VALTYPE ns)
        {return self.mul_proxy(ns);})

      .def("__rmul__", [](qpp::vector3<VALTYPE> &self, const VALTYPE ns)
        {return self.mul_proxy(ns);})

      .def("__div__",[](qpp::vector3<VALTYPE> &self, const VALTYPE ns)
        {return self.div_proxy(ns);} )

      .def("__truediv__",[](qpp::vector3<VALTYPE> &self, const VALTYPE ns)
        {return self.div_proxy(ns);} )

      .def("__cmp__", &qpp::vector3<VALTYPE>::equal_proxy)
      .def("__rcmp__", &qpp::vector3<VALTYPE>::nequal_proxy)
      .def("__getitem__", &qpp::vector3<VALTYPE>::py_getitem_v)
      .def("__setitem__", &qpp::vector3<VALTYPE>::py_setitem_v)
      .def("dot", &qpp::vector3<VALTYPE>::dot_product_proxy)

      .def("cross", &qpp::vector3<VALTYPE>::cross_product_proxy)

      .def("norm",  [](const qpp::vector3<VALTYPE> &vec){ return vec.norm();})
      .def("norm2",    &qpp::vector3<VALTYPE>::squaredNorm)

      .def("normalized",       &qpp::vector3<VALTYPE>::normalized_proxy)
      .def_static("identity", &qpp::vector3<VALTYPE>::identity_proxy)

      .def_property("x",  &qpp::vector3<VALTYPE>::py_getx, &qpp::vector3<VALTYPE>::py_setx)
      .def_property("y",  &qpp::vector3<VALTYPE>::py_gety, &qpp::vector3<VALTYPE>::py_sety)
      .def_property("z",  &qpp::vector3<VALTYPE>::py_getz, &qpp::vector3<VALTYPE>::py_setz)
      .def_readwrite_static("tol_equiv", &qpp::vector3<VALTYPE>::tol_equiv) ;

}

template<class VALTYPE>
void py_matrix3_export (py::module m, const char * pyname) {

  py::class_<qpp::matrix3<VALTYPE> >(m, pyname)
      .def(py::init<>())
      .def(py::init<VALTYPE>())
      .def(py::init<VALTYPE, VALTYPE, VALTYPE,
                    VALTYPE, VALTYPE, VALTYPE,
                    VALTYPE, VALTYPE, VALTYPE>())
      .def(py::init<const qpp::matrix3<VALTYPE>&>())
      .def(py::init<const qpp::vector3<VALTYPE>&,
           const qpp::vector3<VALTYPE>&,
           const qpp::vector3<VALTYPE>&>())

      .def("__str__", &qpp::matrix3<VALTYPE>::to_string_matr)
      .def("__repr__", &qpp::matrix3<VALTYPE>::to_string_matr)

      .def("__add__", [](qpp::matrix3<VALTYPE> &self, qpp::matrix3<VALTYPE> &other)
        {return self.sum_proxy(other);})

      .def("__sub__", [](qpp::matrix3<VALTYPE> &self, qpp::matrix3<VALTYPE> &other)
        {return self.sub_proxy(other);})

      .def("__mul__", [](qpp::matrix3<VALTYPE> &self, const VALTYPE ns)
        {return self.mul_proxy(ns);})

      .def("__mul__", [](qpp::matrix3<VALTYPE> &self, qpp::vector3<VALTYPE> &vec)
        {return self.mv_mul_proxy(vec);})

      .def("__mul__", [](qpp::matrix3<VALTYPE> &self, qpp::matrix3<VALTYPE> &mtr)
        {return self.mm_mul_proxy(mtr);})

      .def("__rmul__", [](qpp::matrix3<VALTYPE> &self, const VALTYPE ns)
        {return self.mul_proxy(ns);})

      .def("__div__",[](qpp::matrix3<VALTYPE> &self, const VALTYPE ns)
        {return self.div_proxy(ns);} )

      .def("__truediv__",[](qpp::matrix3<VALTYPE> &self, const VALTYPE ns)
        {return self.div_proxy(ns);} )

      .def("__cmp__", &qpp::matrix3<VALTYPE>::equal_proxy)
      .def("__rcmp__", &qpp::matrix3<VALTYPE>::nequal_proxy)
      .def_static("identity", &qpp::matrix3<VALTYPE>::identity_proxy)
      .def("inv", &qpp::matrix3<VALTYPE>::inverse_proxy)
      .def("tran", &qpp::matrix3<VALTYPE>::transpose_proxy)
      .def("norm",  [](const qpp::matrix3<VALTYPE> &vec){ return vec.norm();})
      .def("det", &qpp::matrix3<VALTYPE>::determinant)
      .def("norm2",    &qpp::matrix3<VALTYPE>::squaredNorm)
      .def("pow", &qpp::matrix3<VALTYPE>::pow_proxy)
      .def("__getitem__", &qpp::matrix3<VALTYPE>::py_getitemv)
      .def("__setitem__", &qpp::matrix3<VALTYPE>::py_setitemv)
      .def("__getitem__", &qpp::matrix3<VALTYPE>::py_getitem)
      .def("__setitem__", &qpp::matrix3<VALTYPE>::py_setitem)

      .def_property("xx", &qpp::matrix3<VALTYPE>::py_getxx,
                      &qpp::matrix3<VALTYPE>::py_setxx)
      .def_property("xy",  &qpp::matrix3<VALTYPE>::py_getxy,
                      &qpp::matrix3<VALTYPE>::py_setxy)
      .def_property("xz",  &qpp::matrix3<VALTYPE>::py_getxz,
                      &qpp::matrix3<VALTYPE>::py_setxz)
      .def_property("yx",  &qpp::matrix3<VALTYPE>::py_getyx,
                      &qpp::matrix3<VALTYPE>::py_setyx)
      .def_property("yy",  &qpp::matrix3<VALTYPE>::py_getyy,
                      &qpp::matrix3<VALTYPE>::py_setyy)
      .def_property("yz",  &qpp::matrix3<VALTYPE>::py_getyz,
                      &qpp::matrix3<VALTYPE>::py_setyz)
      .def_property("zx",  &qpp::matrix3<VALTYPE>::py_getzx,
                      &qpp::matrix3<VALTYPE>::py_setzx)
      .def_property("zy",  &qpp::matrix3<VALTYPE>::py_getzy,
                      &qpp::matrix3<VALTYPE>::py_setzy)
      .def_property("zz",  &qpp::matrix3<VALTYPE>::py_getzz,
                      &qpp::matrix3<VALTYPE>::py_setzz)
      .def_readwrite_static("tol_equiv",
                            &qpp::matrix3<VALTYPE>::tol_equiv);
  //      ;
  //  m.def("det",       qpp::py_detm<VALTYPE>);
  //  m.def("det",       qpp::py_detv<VALTYPE>);
  //  m.def("outer",     qpp::outer<VALTYPE>);
    m.def("solve3",    qpp::py_solve3m<VALTYPE>);
    m.def("solve3",    qpp::py_solve3v<VALTYPE>);
  //  m.def("invert3",   qpp::py_invert_mtr<VALTYPE>);
  //  m.def("pow",       qpp::py_pow_mtr<VALTYPE>);
}


template<class VALTYPE>
void py_eigen3_export (py::module m) {
    m.def("RotMtrx",   qpp::py_rotmtrx_v<VALTYPE>);
    m.def("RotMtrx",   qpp::py_rotmtrx_t<VALTYPE>);
    m.def("RotMtrx",   qpp::py_rotmtrx_l<VALTYPE>);
    m.def("Sigma",     qpp::py_sigma_v<VALTYPE>);
    m.def("Sigma",     qpp::py_sigma_t<VALTYPE>);
    m.def("Sigma",     qpp::py_sigma_l<VALTYPE>);
    m.def("diagon3",   qpp::py_diagon3dv<VALTYPE>);
    m.def("diagon3",   qpp::py_diagon3dm<VALTYPE>);
    m.def("diagon3",   qpp::py_diagon3dreal<VALTYPE>);
  //  m.def("solve_cubeq",   qpp::solve_cubeq<VALTYPE>);
}


template<class REAL, bool BOUND>
void py_rotrans_export (py::module m, const char * pyname) {
  if (BOUND)
    py::class_<qpp::rotrans<REAL,BOUND> >(m, pyname)
        //.def()
        .def(py::init<const qpp::rotrans<REAL,BOUND> >())
        .def(py::init<const qpp::vector3<REAL>,
             qpp::periodic_cell<REAL>* >())
        .def(py::init<const qpp::matrix3<REAL>,
             qpp::periodic_cell<REAL>*  >())
        .def(py::init<const qpp::vector3<REAL>,
             const qpp::matrix3<REAL>, qpp::periodic_cell<REAL>* >())
        .def("__mul__", &qpp::rotrans<REAL,BOUND>::py_mulr)
        .def("__mul__", &qpp::rotrans<REAL,BOUND>::py_mulv)
        //   .def(sn::str(sn::self))
        //   .def(sn::repr(sn::self))
        .def(py::self==py::self)
        .def(py::self!=py::self)
        //        .def_readwrite_static("unity",
        //                              & qpp::rotrans<REAL,BOUND>::unity)
        .def_readwrite("T", &qpp::rotrans<REAL,BOUND>::T)
        .def_readwrite("R", &qpp::rotrans<REAL,BOUND>::R)
        .def_readwrite_static("tol_trans",
                              &qpp::rotrans<REAL,BOUND>::tol_trans)
        .def_readwrite_static("tol_rot",
                              &qpp::rotrans<REAL,BOUND>::tol_rot)
        .def_readwrite("cell", &qpp::rotrans<REAL,BOUND>::cell,
                       py::return_value_policy::reference_internal)
        //return_value_policy<reference_existing_object>()))
        ;
  else
    py::class_<qpp::rotrans<REAL,BOUND> >(m, pyname)
        //    .def()
        .def(py::init<const qpp::rotrans<REAL,BOUND> >())
        .def(py::init<const qpp::vector3<REAL> >())
        .def(py::init<const qpp::matrix3<REAL> >())
        .def(py::init<const qpp::vector3<REAL>,
             const qpp::matrix3<REAL> >())
        .def("__mul__", &qpp::rotrans<REAL,BOUND>::py_mulr)
        .def("__mul__", &qpp::rotrans<REAL,BOUND>::py_mulv)
        //.def(sn::str(sn::self))
        //.def(sn::repr(sn::self))
        .def(py::self==py::self)
        .def(py::self!=py::self)
        .def("__ne__", &qpp::rotrans<REAL,BOUND>::operator!=)
        .def_readwrite_static("unity", &qpp::rotrans<REAL,BOUND>::unity)
        .def_readwrite("T", &qpp::rotrans<REAL,BOUND>::T)
        .def_readwrite("R", &qpp::rotrans<REAL,BOUND>::R)
        .def_readwrite_static("tol_trans",
                              &qpp::rotrans<REAL,BOUND>::tol_trans)
        .def_readwrite_static("tol_rot",
                              &qpp::rotrans<REAL,BOUND>::tol_rot);
  //  m.def("invert", qpp::py_invert_rt<REAL,BOUND>);
  //  m.def("pow",   qpp::py_pow_rt<REAL,BOUND>);
}

void pyqpp_linalg_export (py::module m) {

  py_vector3_export<float>(m, "vector3f");
#ifdef QPPCAD_PY_EXPORT
  py_vector3_export<int>(m, "vector3i");
#endif
  py_matrix3_export<float>(m, "matrix3f");
  py_eigen3_export<float>(m);
  py_rotrans_export<float,false>(m, "rotrans_f");
  py_rotrans_export<float,true>(m, "bound_rotrans_f");

#ifdef PYTHON_EXP_EXT
  py_vector3_export<double>(m, "vector3d");
  py_vector3_export<std::complex<float> >(m, "vector3c");
  py_vector3_export<std::complex<double> >(m, "vector3z");

  py_matrix3_export<double>(m, "matrix3d");
  py_matrix3_export<std::complex<float> >(m, "matrix3c");
  py_matrix3_export<std::complex<double> >(m, "matrix3z");

  py_eigen3_export<double>(m);
  py_rotrans_export<double,false>(m, "rotrans_d");
  py_rotrans_export<double,true>(m, "bound_rotrans_d");
#endif

  qpp::index::py_export( m, "index");
  qpp::iterator::py_export(m, "iterator");
  qpp::index_range::py_export(m, "index_range");

}
