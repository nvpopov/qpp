#include <pyqpp/pyqpp.hpp>
#include <io/gmsio.hpp>
#include <symm/gen_cell.hpp>
#include <io/fdstream.hpp>

template<qpp::qpp_bastype BT, class FREAL>
void py_read_gms_basis (int fd, qpp::atomic_basis<BT,FREAL> & bas) {

  boost::fdistream inp(fd);
  qpp::read_gms_basis(inp,bas);

}

// -------------------------------------------------------

template<qpp::qpp_bastype BT, class FREAL>
void py_write_gms_basis (int fd, qpp::atomic_basis<BT,FREAL> & bas) {

  boost::fdostream out(fd);
  qpp::write_gms_basis(out,bas);

}

// -------------------------------------------------------

template<class REAL, class CELL>
void py_write_gms_data (int fd, qpp::geometry<REAL, CELL> & geom,
                        std::vector<
                        qpp::atomic_basis<qpp::qbas_gauss,REAL> > & bas) {

  boost::fdostream out(fd);
  qpp::write_gms_data(out,geom,bas);

}

template<class REAL, class CELL>
void py_write_gms_data1 (int fd, qpp::geometry<REAL, CELL> & geom,
                         py::list & bas) {

  boost::fdostream out(fd);
  std::vector<qpp::atomic_basis<qpp::qbas_gauss,REAL> > bas1;
  for (int i=0; i<py::len(bas); i++)
    //TODO: Probably py::isinstance didn`t work on non-python types
    if (py::isinstance<qpp::atomic_basis<qpp::qbas_gauss,REAL> >(bas[i]))
      //TODO: As same as py::instance py::cast can goes to wrong results
      bas1.push_back(
            py::cast<qpp::atomic_basis<qpp::qbas_gauss,REAL> >(bas[i])
            );
    else
      qpp::TypeError("atomic_basis type items are expected in the list");
  qpp::write_gms_data(out,geom,bas1);

}

template<class REAL, class CELL >
void py_write_gms_data2 (int fd,
                         qpp::qmmm_molecule<REAL,
                         CELL,qpp::qbas_gauss,REAL> & mol) {

  boost::fdostream out(fd);
  qpp::write_gms_data(out,mol);

}

template<class REAL, class CELL = qpp::periodic_cell<REAL> >
void py_write_gms_charges (int fd, qpp::xgeometry<REAL, CELL> & geom) {

  boost::fdostream out(fd);
  qpp::write_gms_charges(out,geom);

}

template<class REAL, class CELL = qpp::periodic_cell<REAL>, class FREAL = REAL>
void py_write_gms_charges1 (int fd,
                            qpp::qmmm_molecule<REAL,CELL,
                            qpp::qbas_gauss,FREAL> & mol) {

  boost::fdostream out(fd);
  qpp::write_gms_charges(out,mol);

}

// --------------------------------------------------------

template<class FREAL>
void py_read_gms_ecp (int fd, STRING_EX & name, qpp::atomic_ecp<FREAL> & ecp) {

  boost::fdistream inp(fd);
  qpp::read_gms_ecp(inp,name,ecp);

}

template<class FREAL>
void py_write_gms_ecp (int fd, STRING_EX & name, qpp::atomic_ecp<FREAL> & ecp) {

  boost::fdostream out(fd);
  qpp::write_gms_ecp(out,name,ecp);

}

// --------------------------------------------------------

template<class REAL>
void py_gmsio_export1 (py::module m) {

  m.def("read_gms_basis", py_read_gms_basis<qpp::qbas_gauss,REAL>);
  m.def("write_gms_basis",py_write_gms_basis<qpp::qbas_gauss,REAL>);
  m.def("read_gms_ecp",   py_read_gms_ecp<REAL>);
  m.def("write_gms_ecp",  py_write_gms_ecp<REAL>);

}

template<class REAL, class CELL>
void py_gmsio_export2 (py::module m) {

  m.def("write_gms_data", py_write_gms_data<REAL,CELL>);
  m.def("write_gms_data", py_write_gms_data1<REAL,CELL>);
  m.def("write_gms_data", py_write_gms_data2<REAL,CELL>);
  m.def("write_gms_charges", py_write_gms_charges<REAL,CELL>);
  m.def("write_gms_charges", py_write_gms_charges1<REAL,CELL>);

}


void pyqpp_gmsio_export (pybind11::module m) {

  py::module io = m.def_submodule("io");
  py_gmsio_export1<float>(io);
  py_gmsio_export2<float, qpp::periodic_cell<float> >(io);
  py_gmsio_export2<float,
      qpp::gen_cell<float,  qpp::matrix3<float> > >(io);

#ifdef PYTHON_EXP_EXT
  py_gmsio_export1<double>(io);
  py_gmsio_export2<double, qpp::periodic_cell<double> >(io);
  py_gmsio_export2<double,
      qpp::gen_cell<double,  qpp::matrix3<double> > >(io);
#endif

}
