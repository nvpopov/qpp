#include "gmsio.hpp"

#include <symm/gcell.hpp>
#include <io/fdstream.hpp>

#ifdef PY_EXPORT

#include <boost/python.hpp>
#include <boost/python/list.hpp>
namespace bp = boost::python;

namespace qpp{

  template<qpp_bastype BT, class FREAL>
  void py_read_gms_basis(int fd, qpp::atomic_basis<BT,FREAL> & bas)
  {
    boost::fdistream inp(fd);
    qpp::read_gms_basis(inp,bas);
  }

  // -------------------------------------------------------

  template<qpp_bastype BT, class FREAL>
  void py_write_gms_basis(int fd, qpp::atomic_basis<BT,FREAL> & bas)
  {
    boost::fdostream out(fd);
    qpp::write_gms_basis(out,bas);
  }

  // -------------------------------------------------------

  template<class REAL, class CELL>
  void py_write_gms_data(int fd, qpp::geometry<REAL, CELL> & geom, 
			 std::vector<qpp::atomic_basis<qpp::qbas_gauss,REAL> > & bas)
  { 
    boost::fdostream out(fd);
    qpp::write_gms_data(out,geom,bas);
  }

  template<class REAL, class CELL>
  void py_write_gms_data1(int fd, qpp::geometry<REAL, CELL> & geom, bp::list & bas)
  { 
    boost::fdostream out(fd);
    std::vector<qpp::atomic_basis<qpp::qbas_gauss,REAL> > bas1;
    for (int i=0; i<bp::len(bas); i++)
      if (bp::extract<qpp::atomic_basis<qpp::qbas_gauss,REAL> >(bas[i]).check() )
	bas1.push_back(bp::extract<qpp::atomic_basis<qpp::qbas_gauss,REAL> >(bas[i]));
      else
	qpp::TypeError("atomic_basis type items are expected in the list");
    qpp::write_gms_data(out,geom,bas1);
  }

  template<class REAL, class CELL >
  void py_write_gms_data2(int fd, qpp::qmmm_molecule<REAL,CELL,qpp::qbas_gauss,REAL> & mol)
  {
    boost::fdostream out(fd);
    qpp::write_gms_data(out,mol);
  }

  template<class REAL, class CELL = periodic_cell<REAL> >
  void py_write_gms_charges(int fd, xgeometry<REAL, CELL> & geom)
  {
    boost::fdostream out(fd);
    write_gms_charges(out,geom);
  }

  template<class REAL, class CELL = periodic_cell<REAL>, class FREAL = REAL >
  void py_write_gms_charges1(int fd, qmmm_molecule<REAL,CELL,qbas_gauss,FREAL> & mol)
  {
    boost::fdostream out(fd);
    write_gms_charges(out,mol);
  }

  // --------------------------------------------------------

  template<class FREAL>
  void py_read_gms_ecp(int fd, STRING & name, atomic_ecp<FREAL> & ecp)
  {
    boost::fdistream inp(fd);
    qpp::read_gms_ecp(inp,name,ecp);
  }

  template<class FREAL>
  void py_write_gms_ecp(int fd, STRING & name, atomic_ecp<FREAL> & ecp)
  {
    boost::fdostream out(fd);
    write_gms_ecp(out,name,ecp);
  }

  // --------------------------------------------------------

  template<class REAL>
  void py_export1()
  {
    def("read_gms_basis", py_read_gms_basis<qpp::qbas_gauss,REAL>);
    def("write_gms_basis",py_write_gms_basis<qpp::qbas_gauss,REAL>);
    def("read_gms_ecp",   py_read_gms_ecp<REAL>);
    def("write_gms_ecp",  py_write_gms_ecp<REAL>);
  }

  template<class REAL, class CELL>
  void py_export2()
  {
    def("write_gms_data", py_write_gms_data<REAL,CELL>);
    def("write_gms_data", py_write_gms_data1<REAL,CELL>);
    def("write_gms_data", py_write_gms_data2<REAL,CELL>);
    def("write_gms_charges", py_write_gms_charges<REAL,CELL>);
    def("write_gms_charges", py_write_gms_charges1<REAL,CELL>);
  }

  void qpp_export_gmsio()
  {
    py_export1<float>();
    py_export1<double>();
    py_export2<float, qpp::periodic_cell<float> >();
    py_export2<double, qpp::periodic_cell<double> >();
    py_export2<float, qpp::generalized_cell<float,  qpp::matrix3d<float> > >();
    py_export2<double, qpp::generalized_cell<double,  qpp::matrix3d<double> > >();
  }
  
};

#endif
