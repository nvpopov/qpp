#include "geomio.hpp"
#include <symm/gcell.hpp>
#include <io/fdstream.hpp>

#ifdef PY_EXPORT

namespace qpp{

  /*
  template<class REAL, class CELL>
  void py_read_xyz(const STRING & filename, geometry<REAL,CELL> & geom)
  {
    IFSTREAM inp(filename);
    read_xyz(inp,geom);
    inp.close();
  }

  template<class REAL, class CELL>
  void py_read_xyzq(const STRING & filename, xgeometry<REAL,CELL> & geom)
  {
    IFSTREAM inp(filename);
    read_xyzq(inp,geom);
    inp.close();
  }

  template< class REAL, class CELL >
  void py_write_xyz(const STRING & filename, const qpp::geometry<REAL,CELL> & geom)
  {
    OFSTREAM out(filename);
    std::cout << "write_xyz call\n";
    write_xyz(out,geom);
    out.close();
  }

  template< class REAL, class CELL >
  void py_write_xyzq(const STRING & filename, const qpp::xgeometry<REAL,CELL> & geom)
  {
    OFSTREAM out(filename);
    write_xyzq(out,geom);
    out.close();
  }
  */
  
  template<class REAL, class CELL>
  void py_read_xyz(int fd, geometry<REAL,CELL> & geom)
  {
    boost::fdistream inp(fd);
    read_xyz(inp,geom);
  }

  template<class REAL, class CELL>
  void py_read_xyzq(int fd, xgeometry<REAL,CELL> & geom)
  {
    boost::fdistream inp(fd);
    read_xyzq(inp,geom);
  }

  template< class REAL, class CELL >
  void py_write_xyz(int fd, const qpp::geometry<REAL,CELL> & geom)
  {
    boost::fdostream out(fd);
    write_xyz(out,geom);
  }

  template< class REAL, class CELL >
  void py_write_xyzq(int fd, const qpp::xgeometry<REAL,CELL> & geom)
  {
    boost::fdostream out(fd);
    write_xyzq(out,geom);
  }
  
  template< class REAL, class CELL >
  void py_export_ioxyz()
  {
    def("read_xyz",py_read_xyzq<REAL,CELL>);
    def("read_xyzq",py_read_xyzq<REAL,CELL>);
    def("write_xyz",py_write_xyz<REAL,CELL>);
    def("write_xyzq",py_write_xyzq<REAL,CELL>);
  }

  void qpp_export_ioxyz()
  {
    py_export_ioxyz<float,periodic_cell<float> >();
    py_export_ioxyz<double,periodic_cell<double> >();
    /*
    py_export_ioxyz<float, qpp::generalized_cell<float,  qpp::matrix3d<float>  > >();
    py_export_ioxyz<double,qpp::generalized_cell<double, qpp::matrix3d<double> > >();
    py_export_ioxyz<float, qpp::generalized_cell<float,  qpp::rotrans<float>   > >();
    py_export_ioxyz<double,qpp::generalized_cell<double, qpp::rotrans<double>  > >();
    */
  }
  
};

#endif
