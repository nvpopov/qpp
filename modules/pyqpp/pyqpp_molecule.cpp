#include <pyqpp/pyqpp.hpp>
#include <data/molecule.hpp>
#include <symm/gen_cell.hpp>

template<class REAL, class CELL>
void py_molecule_export (py::module m, const char * pyname) {

  py::class_<qpp::molecule<REAL, CELL> >(m, pyname)
      .def_readwrite("name", & qpp::molecule<REAL,CELL>::name)
      .def_readwrite("cell", & qpp::molecule<REAL,CELL>::cell)
      .def_readwrite("geom", & qpp::molecule<REAL,CELL>::geom)
      .def("atom", & qpp::molecule<REAL,CELL>::atom)
      ;

  std::string sNameMM = fmt::format("{0}_{1}", "mm", pyname);
  py::class_<qpp::mm_molecule<REAL, CELL>,
      qpp::molecule<REAL, CELL> >(m, sNameMM.c_str())
      .def_readwrite("pot", & qpp::mm_molecule<REAL,CELL>::pot)
      ;
  std::string sNameQM = fmt::format("{0}_{1}", "qmmmm", pyname);
  py::class_<qpp::qmmm_molecule<REAL, CELL>,
      qpp::mm_molecule<REAL, CELL> >(m, sNameQM.c_str())
      .def_readwrite("basis", & qpp::qmmm_molecule<REAL,CELL>::basis)
      .def_readwrite("qmatoms", & qpp::qmmm_molecule<REAL,CELL>::qmatoms)
      .def_readwrite("clsatoms", & qpp::qmmm_molecule<REAL,CELL>::clsatoms)
      .def_readwrite("fixedatoms", & qpp::qmmm_molecule<REAL,CELL>::fixedatoms);

}

void pyqpp_molecule_export (pybind11::module m) {

  py_molecule_export<float, qpp::periodic_cell<float> >(m, "molecule_f");
  py_molecule_export<float, qpp::gen_cell<float,
      qpp::matrix3<float> > >(m, "molecule_pgf");
  py_molecule_export<float, qpp::gen_cell<float,
      qpp::rotrans<float, false> > >(m, "molecule_cgf");
  py_molecule_export<float, qpp::gen_cell<float,
      qpp::rotrans<float, true> > >(m, "molecule_fcgf");

#ifdef PYTHON_EXP_EXT
  py_molecule_export<double, qpp::periodic_cell<double> >(m, "molecule_d");
  py_molecule_export<double, qpp::gen_cell<double,
      qpp::matrix3<double> > >(m, "molecule_pgd");
  py_molecule_export<double, qpp::gen_cell<double,
      qpp::rotrans<double, false> > >(m, "molecule_cgd");
  py_molecule_export<double, qpp::gen_cell<double,
      qpp::rotrans<double, true> > >(m, "molecule_fcgd");
#endif

}
