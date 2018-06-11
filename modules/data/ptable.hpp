#ifndef _QPP_ptable_H
#define _QPP_ptable_H

#include <iostream>
#include <data/types.hpp>
#include <geom/lace3d.hpp>

#ifdef PY_EXPORT
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pyqpp/py_indexed_property.hpp>
namespace py = pybind11;
#endif

namespace qpp {
  const int PTABLE_ELEM_N = 100;
  const int PTABLE_INT_NONE = -1;
  const double PTABLE_FLOAT_NONE = -1.0;
  const STRING PTABLE_NONE = "None";

  struct ptable_atom_ionic_radii{
    double charge;
    double radii;
  };

  struct ptable_atom_record{
    unsigned int aNumber;
    STRING       aName;
    STRING       aSymbol;
    double       aRadius;
    double       aMass;

    double       aCovRad_Slater;
    double       aCovRad_Bragg;
    double       aCovRad_Cordero;
    double       aCovRad_Pyykko;
    double       aCovRad_Pyykko_D;
    double       aCovRad_Pyykko_T;

    double       aVdWRad;
    double       aVdWRad_Alvarez;
    double       aIonicRadius;

  };

  class ptable{
  private:
    static ptable *instance;
    std::array<ptable_atom_record, PTABLE_ELEM_N> arecs;

    static ptable* get_instance(){
      if(!instance){
          instance = new ptable();
          instance->init_default();
        }
      return instance;
    }

    void init_default();

  public:

    ptable(){};

    static STRING symbol_by_number(const int number){
      ptable *table = ptable::get_instance();
      if ((number >= 1) && (number < PTABLE_ELEM_N))
        return table->arecs[number-1].aSymbol;
      return PTABLE_NONE;
    }

    static STRING name_by_number(const int number){
      ptable *table = ptable::get_instance();
      if ((number >= 1) && (number < PTABLE_ELEM_N))
        return table->arecs[number-1].aName;
      return PTABLE_NONE;
    }

    static const int number_by_name(const STRING& name){
      ptable *table = ptable::get_instance();
      for(int i = 0; i < PTABLE_ELEM_N; i++)
        if(table->arecs[i].aName == name)
          return i+1;
      return PTABLE_INT_NONE;
    }

    static const int number_by_symbol(const STRING& symbol){
      ptable *table = ptable::get_instance();
      for(int i = 0; i < PTABLE_ELEM_N; i++)
        if(table->arecs[i].aSymbol == symbol)
          return i+1;
      return PTABLE_INT_NONE;
    }
  };
}
#endif
