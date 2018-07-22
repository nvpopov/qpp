#ifndef _QPP_ptable_H
#define _QPP_ptable_H

#include <iostream>
#include <geom/lace3d.hpp>
#include <data/types.hpp>


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
        double       aRadius; // A
        double       aMass;

        double       aCovRad_Slater;// A
        double       aCovRad_Bragg;// A
        double       aCovRad_Cordero;// A
        double       aCovRad_Pyykko;// A
        double       aCovRad_Pyykko_D;// A
        double       aCovRad_Pyykko_T;// A

        double       aVdWRadius;// A
        double       aVdWRadius_Alvarez;// A
        double       aIonicRadius;// A

        int          aNValenceElec;
        std::tuple<int,int,int> aColorJmol, aColorGV, aColorCPK;
        //(1,"s",2),(2,"s",3)
        std::vector<std::tuple<int,std::string,int> > aElecConf;

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

        static const double mass_by_number(const int number){
            ptable *table = ptable::get_instance();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aMass;
        }

        static const double ionic_rad_by_number(const int number){
            ptable *table = ptable::get_instance();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aIonicRadius;
        }

        static const double cov_rad_by_number(const int number){
            ptable *table = ptable::get_instance();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aCovRad_Slater;
        }

        static const double vdw_rad_by_number(const int number){
            ptable *table = ptable::get_instance();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aVdWRadius;
        }

        static const int nval_elec_by_number(const int number){
            ptable *table = ptable::get_instance();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aNValenceElec;
        }
    };
}
#endif
