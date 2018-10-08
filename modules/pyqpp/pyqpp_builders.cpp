#include <pyqpp/pyqpp.hpp>
#include <geom/builders.hpp>
#include <geom/ngbr.hpp>
#include <symm/gcell.hpp>


template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
void def_builders4(py::module m){
  m.def("replicate",qpp::py_replicate1<REALDST,CELLDST, REALSRC,CELLSRC> );
  m.def("replicate",qpp::py_replicate2<REALDST,CELLDST, REALSRC,CELLSRC> );
  m.def("fill",qpp::py_fill1<REALDST,CELLDST, REALSRC,CELLSRC> );
  m.def("fill",qpp::py_fill2<REALDST,CELLDST, REALSRC,CELLSRC> );
  m.def("fill",qpp::py_fill3<REALDST,CELLDST, REALSRC,CELLSRC> );
}

template<class REALDST, class CELLDST, class REALSRC>
void def_builders3(py::module m){
  def_builders4< REALDST, CELLDST, REALSRC, qpp::periodic_cell<REALSRC> >(m);
  def_builders4< REALDST, CELLDST, REALSRC,
      qpp::generalized_cell<REALSRC,
      qpp::matrix3<REALSRC> > >(m);
  def_builders4< REALDST, CELLDST, REALSRC,
      qpp::generalized_cell<REALSRC,
      qpp::rotrans<REALSRC> > >(m);
}

template<class REALDST, class CELLDST>
void def_builders2(py::module m){
  def_builders3< REALDST, CELLDST, float>(m);
  def_builders3< REALDST, CELLDST, double>(m);
}

template<class REALDST>
void def_builders1(py::module m){
  def_builders2< REALDST, qpp::periodic_cell<REALDST> >(m);
  def_builders2< REALDST, qpp::generalized_cell<REALDST,
      qpp::matrix3<REALDST> > >(m);
  def_builders2< REALDST, qpp::generalized_cell<REALDST,
      qpp::rotrans<REALDST> > >(m);
}

void pyqpp_builders_export (py::module m) {

  m.def("treat_crowd", qpp::treat_crowd<float,  qpp::periodic_cell<float> >);
  m.def("treat_crowd", qpp::treat_crowd<float,
                       qpp::generalized_cell<float,
                       qpp::matrix3<float> > >);
  m.def("treat_crowd", qpp::treat_crowd<float,
                       qpp::generalized_cell<float,
                       qpp::rotrans<float>  > >);
  def_builders1<float>(m);

#ifdef PYTHON_EXP_EXT
  m.def("treat_crowd", qpp::treat_crowd<double, qpp::periodic_cell<double> >);
  m.def("treat_crowd", qpp::treat_crowd<double,
                       qpp::generalized_cell<double,
                       qpp::matrix3<double> > >);
  m.def("treat_crowd", qpp::treat_crowd<double,
                       qpp::generalized_cell<double,
                       qpp::rotrans<double> > >);
  def_builders1<double>(m);
#endif

}
