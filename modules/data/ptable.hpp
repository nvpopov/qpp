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
        vector3<float> aColorJmol, aColorGV, aColorCPK;
        //(1,"s",2),(2,"s",3)
        std::vector<std::tuple<int,std::string,int> > aElecConf;

    };

    class ptable{
    public:

        static ptable *instance;

        std::map<std::string, int> cache_atom_idx;
        std::array<ptable_atom_record, PTABLE_ELEM_N> arecs;

        static ptable* get_inst(){
            if(!instance){
                    instance = new ptable();
                    instance->init_default();
                }
            return instance;
        }

        void init_default();
        void assembly_ptable_0();
        void assembly_ptable_1();
        void assembly_ptable_2();
        void assembly_ptable_3();
        void assembly_ptable_4();
        void assembly_ptable_5();
        void assembly_ptable_6();
        void assembly_ptable_7();
        void assembly_ptable_8();
        void assembly_ptable_9();

        void init_cache_atom_idx();

        ptable(){}

        static STRING symbol_by_number(const int number){
            ptable *table = ptable::get_inst();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aSymbol;
            return PTABLE_NONE;
        }

        static STRING name_by_number(const int number){
            ptable *table = ptable::get_inst();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aName;
            return PTABLE_NONE;
        }

        static const int number_by_name(const STRING& name){
            ptable *table = ptable::get_inst();
            for(int i = 0; i < PTABLE_ELEM_N; i++)
                if(table->arecs[i].aName == name)
                    return i+1;
            return PTABLE_INT_NONE;
        }

        static const int number_by_symbol(const STRING& symbol){
            ptable *table = ptable::get_inst();
            if ( table->cache_atom_idx.find(symbol) ==
                 table->cache_atom_idx.end() ) {
              return PTABLE_INT_NONE;
            } else {
              return table->cache_atom_idx[symbol];
            }
            return PTABLE_INT_NONE;
        }

        static const double mass_by_number(const int number){
            ptable *table = ptable::get_inst();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aMass;
        }

        static const double ionic_rad_by_number(const int number){
            ptable *table = ptable::get_inst();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aIonicRadius;
            else return 1.0f;
        }

        static const double cov_rad_by_number(const int number){
            ptable *table = ptable::get_inst();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aCovRad_Slater;
            else return 1.0f;
        }

        static const double vdw_rad_by_number(const int number){
            ptable *table = ptable::get_inst();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aVdWRadius;
            else return 1.0f;
        }

        static const int nval_elec_by_number(const int number){
            ptable *table = ptable::get_inst();
            if ((number >= 1) && (number < PTABLE_ELEM_N))
                return table->arecs[number-1].aNValenceElec;
            else return 1.0f;
        }
    };
}
#endif
