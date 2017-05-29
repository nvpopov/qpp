#define PY_EXPORT

#include "qppcpp.hpp"
#include <symm/cell.hpp>
#include <symm/gcell.hpp>

template<class REAL>
void py_cell_export(const char * pyname)
{
  class_<qpp::periodic_cell<REAL> >(pyname, init<int>())
    .def(init<qpp::vector3d<REAL> , optional<qpp::vector3d<REAL>, qpp::vector3d<REAL> > >())
    .def(init<qpp::periodic_cell<REAL> >())
    .def(init<REAL,REAL,REAL,REAL,REAL,REAL>())
    .def(init<tuple, optional<tuple,tuple> >())
    .def(init<list, optional<list,list> >())
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
    .def( "within_wz",            & qpp::periodic_cell<REAL>::within_wz)      
    .def(sn::str(sn::self))
    ;
}


void qpp_export2()
{

  py_cell_export<float>("periodic_cell_f");
  py_cell_export<double>("periodic_cell_d");

  qpp::generalized_cell<float,  qpp::matrix3d<float> >::py_export("point_group_f");
  qpp::generalized_cell<double, qpp::matrix3d<double> >::py_export("point_group_d");

  qpp::generalized_cell<float,  qpp::rotrans<float,false> >::py_export("crystal_group_f");
  qpp::generalized_cell<double, qpp::rotrans<double,false> >::py_export("crystal_group_d");

  qpp::generalized_cell<float,  qpp::rotrans<float,true> >::py_export("finite_crystal_group_f");
  qpp::generalized_cell<double, qpp::rotrans<double,true> >::py_export("finite_crystal_group_d");

  qpp::generated_group<qpp::matrix3d<float> >::py_export("array_point_group_f");
  qpp::generated_group<qpp::matrix3d<double> >::py_export("array_point_group_d");
  qpp::generated_group<qpp::rotrans<float,true> >::py_export("array_fincryst_group_f");
  qpp::generated_group<qpp::rotrans<double,true> >::py_export("array_fincryst_group_d");

}

