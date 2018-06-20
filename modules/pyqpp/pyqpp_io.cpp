#include <pyqpp/pyqpp.hpp>

#include <io/geomio.hpp>
#include <symm/gcell.hpp>
#include <io/fdstream.hpp>
#include <io/vasp_io.hpp>

#ifdef PY_EXPORT

//vasp io start
template<class REAL, class CELL>
void py_read_vasp_poscar(int fd, qpp::geometry<REAL,CELL> & geom){
  boost::fdistream inp(fd);
  read_vasp_poscar(inp,geom);
}

//vasp io end
template<class REAL, class CELL>
void py_read_xyz(int fd, qpp::geometry<REAL,CELL> & geom){
  boost::fdistream inp(fd);
  read_xyz(inp,geom);
}

template<class REAL, class CELL>
void py_read_xyzq(int fd, qpp::xgeometry<REAL,CELL> & geom){
  boost::fdistream inp(fd);
  read_xyzq(inp,geom);
}

template< class REAL, class CELL >
void py_write_xyz(int fd, const qpp::geometry<REAL,CELL> & geom){
  boost::fdostream out(fd);
  write_xyz(out,geom);
}

template< class REAL, class CELL >
void py_write_xyzq(int fd, const qpp::xgeometry<REAL,CELL> & geom){
  boost::fdostream out(fd);
  write_xyzq(out,geom);
}

template< class REAL, class CELL >
void py_export_ioxyz(py::module m){
  m.def("read_xyz",  &py_read_xyzq<REAL,CELL>);
  m.def("read_xyzq", &py_read_xyzq<REAL,CELL>);
  m.def("write_xyz", &py_write_xyz<REAL,CELL>);
  m.def("write_xyzq",&py_write_xyzq<REAL,CELL>);
}

template< class REAL, class CELL >
void py_export_vasp_io(py::module m){
  m.def("read_vasp_poscar", &py_read_vasp_poscar<REAL,CELL>);
}

void pyqpp_io_export(py::module m){


  py_export_ioxyz<float,qpp::periodic_cell<float> >(m);
  py_export_ioxyz<double,qpp::periodic_cell<double> >(m);
  py_export_vasp_io<float,qpp::periodic_cell<float> >(m);
  py_export_vasp_io<double,qpp::periodic_cell<double> >(m);

  /*
    py_export_ioxyz<float, qpp::generalized_cell<float,
        qpp::matrix3d<float>  > >(m);

    py_export_ioxyz<double,
        qpp::generalized_cell<double, qpp::matrix3d<double> > >(m);

    py_export_ioxyz<float,
        qpp::generalized_cell<float,  qpp::rotrans<float>   > >(m);

    py_export_ioxyz<double,
        qpp::generalized_cell<double, qpp::rotrans<double>  > >(m);
*/
}



#endif
