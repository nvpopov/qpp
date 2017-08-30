#include "qppcpp.hpp"
#include <geom/builders.hpp>
#include <geom/ngbr.hpp>
#include <symm/gcell.hpp>

template<class REALDST, class CELLDST, class REALSRC, class CELLSRC>
void def_builders4()
{
  def("replicate",qpp::py_replicate1<REALDST,CELLDST, REALSRC,CELLSRC> );
  def("replicate",qpp::py_replicate2<REALDST,CELLDST, REALSRC,CELLSRC> );
  def("fill",qpp::py_fill1<REALDST,CELLDST, REALSRC,CELLSRC> );
  def("fill",qpp::py_fill2<REALDST,CELLDST, REALSRC,CELLSRC> );
  def("fill",qpp::py_fill3<REALDST,CELLDST, REALSRC,CELLSRC> );
}

template<class REALDST, class CELLDST, class REALSRC>
void def_builders3()
{
  def_builders4< REALDST, CELLDST, REALSRC, qpp::periodic_cell<REALSRC> >();
  def_builders4< REALDST, CELLDST, REALSRC, qpp::generalized_cell<REALSRC, qpp::matrix3d<REALSRC> > >();
  def_builders4< REALDST, CELLDST, REALSRC, qpp::generalized_cell<REALSRC, qpp::rotrans<REALSRC> > >();
}

template<class REALDST, class CELLDST>
void def_builders2()
{
  def_builders3< REALDST, CELLDST, float>();
  def_builders3< REALDST, CELLDST, double>();
}

template<class REALDST>
void def_builders1()
{
  def_builders2< REALDST, qpp::periodic_cell<REALDST> >();
  def_builders2< REALDST, qpp::generalized_cell<REALDST, qpp::matrix3d<REALDST> > >();
  def_builders2< REALDST, qpp::generalized_cell<REALDST, qpp::rotrans<REALDST> > >();
}

void qpp_export7()
{
  def("treat_crowd",qpp::treat_crowd<float,  qpp::periodic_cell<float> >);
  def("treat_crowd",qpp::treat_crowd<double, qpp::periodic_cell<double> >);
  def("treat_crowd",qpp::treat_crowd<float,  qpp::generalized_cell<float,  qpp::matrix3d<float> > >);
  def("treat_crowd",qpp::treat_crowd<double, qpp::generalized_cell<double, qpp::matrix3d<double> > >);
  def("treat_crowd",qpp::treat_crowd<float,  qpp::generalized_cell<float,  qpp::rotrans<float>  > >);
  def("treat_crowd",qpp::treat_crowd<double, qpp::generalized_cell<double, qpp::rotrans<double> > >);

  def_builders1<float>();
  def_builders1<double>();
}

  
