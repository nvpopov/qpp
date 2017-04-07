#define PY_EXPORT

#include <python/qppython.hpp>
#include <symm/index.hpp>
#include <geom/lace3d.hpp>
#include <symm/cell.hpp>
#include <symm/gcell.hpp>
#include <symm/transform.hpp>
#include <geom/geom.hpp>
#include <geom/ngbr.hpp>
#include <geom/shape.hpp>
#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/return_internal_reference.hpp>

using namespace boost::python;
namespace sn = boost::python::self_ns;

namespace qpp{

  void IndexError(const char * msg)
  {
    PyErr_SetString(PyExc_IndexError, msg);
    throw_error_already_set();
  }

  void TypeError(const char * msg)
  {
    PyErr_SetString(PyExc_TypeError, msg);
    throw_error_already_set();
  }

  void KeyError(const char * msg)
  {
    PyErr_SetString(PyExc_KeyError, msg);
    throw_error_already_set();
  }

  void StopIter()
  {
    PyErr_SetString(PyExc_StopIteration, "");
    throw_error_already_set();
  }

};

template<class VALTYPE>
inline VALTYPE py_scal(const qpp::vector3d<VALTYPE> & x, const qpp::vector3d<VALTYPE> & y)
{ return qpp::scal(x,y); }

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
    .def(sn::self - sn::self)
    .def(sn::self == sn::self)
    .def(sn::self != sn::self)
    .def(sn::self % sn::self)	
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
  def("scal", py_scal<VALTYPE>);
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
  def("RotMtrx",   qpp::py_rotmtrx_v<VALTYPE>);
  def("RotMtrx",   qpp::py_rotmtrx_t<VALTYPE>);
  def("RotMtrx",   qpp::py_rotmtrx_l<VALTYPE>);
  def("Sigma",     qpp::py_sigma_v<VALTYPE>);
  def("Sigma",     qpp::py_sigma_t<VALTYPE>);
  def("Sigma",     qpp::py_sigma_l<VALTYPE>);
  def("solve3",    qpp::py_solve3m<VALTYPE>);
  def("solve3",    qpp::py_solve3v<VALTYPE>);
  def("invert3",   qpp::py_invert_mtr<VALTYPE>);
  def("pow",       qpp::py_pow_mtr<VALTYPE>);
  def("diagon3",   qpp::diagon3d<VALTYPE>);
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
      ;
  def("invert", qpp::py_invert_rt<REAL,BOUND>);
  def("pow",    qpp::py_pow_rt<REAL,BOUND>);
}

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


template<class REAL,class CELL>
void py_geom_export(const char * pyname)
{
  qpp::geometry<REAL,CELL>::py_props();
  class_<qpp::geometry<REAL,CELL> >(pyname, init<int, optional<const STRING&> >() )
    .def(init<CELL&, optional<const STRING&> >())
    .def("add_observer",    & qpp::geometry<REAL,CELL>::add_observer )
    .def("remove_observer", & qpp::geometry<REAL,CELL>::remove_observer )
    .def("add",     & qpp::geometry<REAL,CELL>::py_add1)
    .def("add",     & qpp::geometry<REAL,CELL>::py_add2)
    .def("add",     & qpp::geometry<REAL,CELL>::py_add3)
    .def("erase",   & qpp::geometry<REAL,CELL>::py_erase)
    .def("insert",  & qpp::geometry<REAL,CELL>::py_insert1)
    .def("insert",  & qpp::geometry<REAL,CELL>::py_insert2)
    .def("insert",  & qpp::geometry<REAL,CELL>::py_insert3)
    .def("clear",   & qpp::geometry<REAL,CELL>::clear)    
    .def("pos",     & qpp::geometry<REAL,CELL>::py_pos1)    
    .def("pos",     & qpp::geometry<REAL,CELL>::py_pos2)    
    .def("pos",     & qpp::geometry<REAL,CELL>::py_pos3)    
    .def("r",       & qpp::geometry<REAL,CELL>::py_pos1)    
    .def("r",       & qpp::geometry<REAL,CELL>::py_pos2)    
    .def("r",       & qpp::geometry<REAL,CELL>::py_pos3)    
    .def("nat",              & qpp::geometry<REAL,CELL>::nat)
    .def("__getitem__",      & qpp::geometry<REAL,CELL>::py_getitem)
    .def("__setitem__",      & qpp::geometry<REAL,CELL>::py_setitem)
    .add_property("cell",   
		  make_getter(& qpp::geometry<REAL,CELL>::cell, return_value_policy<reference_existing_object>()), 
		  & qpp::geometry<REAL,CELL>::py_setcell)
    .def_readonly("dim",     & qpp::geometry<REAL,CELL>::DIM)
    .def_readwrite("atom",   & qpp::geometry<REAL,CELL>::py_atoms)
    .def_readwrite("coord",  & qpp::geometry<REAL,CELL>::py_coords)
    .def_readwrite("shadow", & qpp::geometry<REAL,CELL>::py_shadow)
    .def_readwrite("x",      & qpp::geometry<REAL,CELL>::py_x)
    .def_readwrite("y",      & qpp::geometry<REAL,CELL>::py_y)
    .def_readwrite("z",      & qpp::geometry<REAL,CELL>::py_z)

    .def("type",         & qpp::geometry<REAL,CELL>::type_table)
    .def("atom_of_type", & qpp::geometry<REAL,CELL>::atom_of_type)
    .def("type",         & qpp::geometry<REAL,CELL>::py_typeofatom)
    .def("n_types",      & qpp::geometry<REAL,CELL>::n_atom_types)
    
    .def_readwrite("auto_update_types", & qpp::geometry<REAL,CELL>::auto_update_types, 
		   "bool auto_update_types: Whether to update atomic type table after any atom manipulations")
    .def_readwrite("frac", & qpp::geometry<REAL,CELL>::frac, 
		   "bool frac: Whether to undestand the atomic coordinates as fractional")
    .def_readwrite("auto_symmetrize", & qpp::geometry<REAL,CELL>::auto_symmetrize,
		   "bool auto_symmetrize: How to treat atoms added near \'high symmetry points\'.\nIf auto_symmetrize==true, put the new atom in high symmetry point instead of given coordinates, when the distance\n between atom and its image less then symmetrization radius (symmrad)")
    .def_readwrite("default_symmrad", & qpp::geometry<REAL,CELL>::default_symmetrize_radius,
		   "real default_symmrad: symmetrization radius for all atoms")
    .def_readwrite("symmrad", & qpp::geometry<REAL,CELL>::py_symmrad,
		   "Usage: symmrad[at] with string at. Symmetrization radius for atom at")
    .def("symmrad_to_dict", & qpp::geometry<REAL,CELL>::py_symmrad2dict,
	 "Outputs the symmrad values in dictionary form")
    ;
}

template<class REAL>
void py_observer_export(const char * pyname)
{
  class_<qpp::py_geometry_observer<REAL>,boost::noncopyable>(pyname)
    .def("added",    pure_virtual(& qpp::py_geometry_observer<REAL>::added))
    .def("inserted", pure_virtual(& qpp::py_geometry_observer<REAL>::inserted))
    .def("changed",  pure_virtual(& qpp::py_geometry_observer<REAL>::changed))
    .def("erased",   pure_virtual(& qpp::py_geometry_observer<REAL>::erased))
    .def("shaded",   pure_virtual(& qpp::py_geometry_observer<REAL>::shaded))
    ;
}

template<class REAL>
void py_shape_export(const char * pyname)
{
  class_<qpp::py_shape<REAL>,boost::noncopyable>(pyname)
    .def("within",    pure_virtual( & qpp::py_shape<REAL>::within))
    .def("scale",     pure_virtual( & qpp::py_shape<REAL>::scale))
    .def("move",      pure_virtual( & qpp::py_shape<REAL>::move))    
    .def("rotate",    pure_virtual( & qpp::py_shape<REAL>::rotate))
    .def("volume",    pure_virtual( & qpp::py_shape<REAL>::volume))
    .def("rmin",      pure_virtual( & qpp::py_shape<REAL>::rmin))
    .def("rmax",      pure_virtual( & qpp::py_shape<REAL>::rmax))
    .def("fmin",      pure_virtual( & qpp::py_shape<REAL>::fmin))
    .def("fmax",      pure_virtual( & qpp::py_shape<REAL>::fmax))
    .def("write",     pure_virtual( & qpp::py_shape<REAL>::write))
    ;

}

BOOST_PYTHON_MODULE(qpp_cpp)
{
  
  qpp::index::py_export("index");
  qpp::iterator::py_export("iterator");
  qpp::index_range::py_export("index_range");

  py_vector3d_export<float>("vector3f");
  py_vector3d_export<double>("vector3d");
  py_vector3d_export<std::complex<float> >("vector3c");
  py_vector3d_export<std::complex<double> >("vector3z");

  py_matrix3d_export<float>("matrix3f");
  py_matrix3d_export<double>("matrix3d");

  py_rotrans_export<float,false>("rotrans_f");
  py_rotrans_export<double,false>("rotrans_d");
  py_rotrans_export<float,true>("bound_rotrans_f");
  py_rotrans_export<double,true>("bound_rotrans_d");

  py_cell_export<float>("periodic_cell_f");
  py_cell_export<double>("periodic_cell_d");

  qpp::generalized_cell<float,  qpp::matrix3d<float> >::py_export("point_group_f");
  qpp::generalized_cell<double, qpp::matrix3d<double> >::py_export("point_group_d");

  qpp::generalized_cell<float,  qpp::rotrans<float,false> >::py_export("crystal_group_f");
  qpp::generalized_cell<double, qpp::rotrans<double,false> >::py_export("crystal_group_d");

  qpp::generalized_cell<float,  qpp::rotrans<float,true> >::py_export("finite_crystal_group_f");
  qpp::generalized_cell<double, qpp::rotrans<double,true> >::py_export("finite_crystal_group_d");

  py_geom_export<float,qpp::periodic_cell<float> >("geometry_f");
  py_geom_export<double,qpp::periodic_cell<double> >("geometry_d");

  py_geom_export<float, qpp::generalized_cell<float,  qpp::matrix3d<float>  > >("geometry_pgf");
  py_geom_export<double,qpp::generalized_cell<double, qpp::matrix3d<double> > >("geometry_pgd");
  py_geom_export<float, qpp::generalized_cell<float,  qpp::rotrans<float>   > >("geometry_cgf");
  py_geom_export<double,qpp::generalized_cell<double, qpp::rotrans<double>  > >("geometry_cgd");
  
  enum_<qpp::before_after>("geom_change_state")
    .value("before", qpp::before)
    .value("after",  qpp::after)
    ;
  
  py_observer_export<float>("gobserver_f");
  py_observer_export<double>("gobserver_d");

  qpp::bonding_table<float>::py_export("bonding_table_f");
  qpp::bonding_table<double>::py_export("bonding_table_d");

  qpp::neighbours_table<float, qpp::periodic_cell<float> >::py_export("ngbr_table_f");
  qpp::neighbours_table<double, qpp::periodic_cell<double> >::py_export("ngbr_table_d");
  /*
  qpp::shape<float>::py_export("abstract_shape_f");
  qpp::shape<double>::py_export("abstract_shape_d");
  
  py_shape_export<float>("shape_f");
  py_shape_export<double>("shape_d");

  def("shape_box_f", qpp::py_shape_box1<float>, return_value_policy<manage_new_object>());
  def("shape_box_f", qpp::py_shape_box2<float>, return_value_policy<manage_new_object>());
  def("shape_box_f", qpp::py_shape_box3<float>, return_value_policy<manage_new_object>());

  def("shape_box_d", qpp::py_shape_box1<double>, return_value_policy<manage_new_object>());
  def("shape_box_d", qpp::py_shape_box2<double>, return_value_policy<manage_new_object>());
  def("shape_box_d", qpp::py_shape_box3<double>, return_value_policy<manage_new_object>());

  qpp::shape_box<float>::py_export("shape_box_f");
  qpp::shape_box<double>::py_export("shape_box_d");
  */
  
}
