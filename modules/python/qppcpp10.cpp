/*
#include "qppcpp.hpp"
#include <data/molecule.hpp>
#include <symm/gcell.hpp>

template<class REAL, class CELL>
void py_molecule_export(const char * pyname)
{
  class_<qpp::molecule<REAL,CELL> >(pyname)
    .def_readwrite("name", & qpp::molecule<REAL,CELL>::name)
    .def_readwrite("cell", & qpp::molecule<REAL,CELL>::cell)
    .def_readwrite("geom", & qpp::molecule<REAL,CELL>::geom)
    .def("atom", & qpp::molecule<REAL,CELL>::atom)
    ;
  class_<qpp::mm_molecule<REAL,CELL>, bases<qpp::molecule<REAL,CELL> > >(pyname)
    .def_readwrite("pot", & qpp::mm_molecule<REAL,CELL>::pot)
    ;
  class_<qpp::qmmm_molecule<REAL,CELL>, bases<qpp::mm_molecule<REAL,CELL> > >(pyname)
    .def_readwrite("basis", & qpp::qmmm_molecule<REAL,CELL>::basis)
    .def_readwrite("qmatoms", & qpp::qmmm_molecule<REAL,CELL>::qmatoms)
    .def_readwrite("clsatoms", & qpp::qmmm_molecule<REAL,CELL>::clsatoms)
    .def_readwrite("fixedatoms", & qpp::qmmm_molecule<REAL,CELL>::fixedatoms)
    ;
}


void qpp_export10()
{
  py_molecule_export<float, qpp::periodic_cell<float> >("molecule_f");
  py_molecule_export<double, qpp::periodic_cell<double> >("molecule_d");
  py_molecule_export<float, qpp::generalized_cell<float,  qpp::matrix3d<float> > >("molecule_pgf");
  py_molecule_export<double, qpp::generalized_cell<double, qpp::matrix3d<double> > >("molecule_pgd");
  py_molecule_export<float, qpp::generalized_cell<float,  qpp::rotrans<float,false> > >("molecule_cgf");
  py_molecule_export<double, qpp::generalized_cell<double, qpp::rotrans<double,false> > >("molecule_cgd");
  py_molecule_export<float, qpp::generalized_cell<float,  qpp::rotrans<float,true> > >("molecule_fcgf");
  py_molecule_export<double, qpp::generalized_cell<double, qpp::rotrans<double,true> > >("molecule_fcgd");
}

*/
