#ifndef QPP_MOLECULE_H
#define QPP_MOLECULE_H

#if defined(PY_EXPORT) || defined(QPPCAD_PY_EXPORT)
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
//#include <pybind11/stl.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#pragma pop_macro("slots")
#endif

#include <classic/potentials.hpp>
#include <geom/geom.hpp>
#include <basis/basis.hpp>
#include <basis/ecp.hpp>

namespace qpp {

  typedef std::set<int> qselection;

  template<class REAL, class CELL>
  class molecule {

      std::vector<STRING_EX> atoms;
      std::vector<int> attypes;

    public:
      STRING_EX name;
      CELL * cell;
      geometry<REAL,CELL> * geom;

      //std::vector<qpp_atom<FREAL>*> atoms;

      //! \brief Gives the name of atomic type number t. For correct
      //! work of molecule::atom the type table of molecule::geom
      //! must be correctly built
      STRING_EX atom(int t) const {
        return geom->atom_of_type(t);
      }

      int type(const STRING_EX & at) const {
        return geom->type_of_atom(at);
      }

      int define_type(const STRING_EX & at) {
        geom -> define_type(at);
      }

  };

  template<class REAL, class CELL>
  class mm_molecule : public molecule<REAL,CELL> {

    public:

      int pot;
      //std::vector<classical_potential<REAL> > pot;

  };

  template<class REAL, class CELL = periodic_cell<REAL>,
           qpp_bastype BT = qbas_gauss, class FREAL = REAL>
  class qmmm_molecule : public mm_molecule<REAL,CELL> {

    public:
      qselection qmatoms,clsatoms,fixedatoms;
      std::vector<atomic_basis<BT,FREAL> > basis;
      std::vector<atomic_ecp<FREAL> > ecp;

  };

}

#endif
