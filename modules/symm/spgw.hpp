#ifndef SPGW_HPP
#define SPGW_HPP
#include <string>
#include "geom/geom.hpp"

extern "C"
{
    #include "spglib.h"
}

template<class VALTYPE, class CELL>
void get_spgdata_from_geom(qpp::geometry<VALTYPE,CELL> &inGeom,
                           VALTYPE _lattice[3][3], VALTYPE _positions[][3], int *_types){
    int num_atoms = inGeom.size();
    for(int i=0; i<num_atoms; i++){
        _positions[i][0] = inGeom.coord(i).x();
        _positions[i][1] = inGeom.coord(i).y();
        _positions[i][2] = inGeom.coord(i).z();
        _types[i]=inGeom.type_table(i);
    }

    for(int i=0; i<3; i++){
        _lattice[i][0] = inGeom.cell->v[i].x();
        _lattice[i][1] = inGeom.cell->v[i].y();
        _lattice[i][2] = inGeom.cell->v[i].z();
    }

}

template<class VALTYPE, class CELL>
int spgw_standartize_cell(qpp::geometry<VALTYPE,CELL> &inGeom,qpp::geometry<VALTYPE,CELL> &outGeom, float symprec = 1e-5){

    int num_atoms = inGeom.size();
    auto latticev = new VALTYPE[3][3]();
    auto position = new VALTYPE[num_atoms][3]();
    auto types = new int[num_atoms]();
    get_spgdata_from_geom(inGeom,latticev,position,types);

    int to_primitive = 1;
    int no_idealize = 0;
    int num_primitive_atom = spg_standardize_cell(latticev, position, types,
                                                  to_primitive, no_idealize, num_atoms, symprec);

    //Get standartized cell back to user
    for(int i=0; i<3; i++){
         outGeom.cell->v[i].x() = latticev[i][0];
         outGeom.cell->v[i].y() = latticev[i][1];
         outGeom.cell->v[i].z() = latticev[i][2];
    }

    for(int i=0; i<num_atoms; i++){
        outGeom.add(inGeom.atom_of_type(types[i]),position[i][0],position[i][1],position[i][2]);
    }

    return num_primitive_atom;
}

template<class VALTYPE, class CELL>
std::string spgw_get_international(qpp::geometry<VALTYPE,CELL> &inGeom, float symprec = 1e-7){

    int num_atoms = inGeom.size();
    auto latticev = new VALTYPE[3][3]();
    auto position = new VALTYPE[num_atoms][3]();
    auto types = new int[num_atoms]();
    get_spgdata_from_geom(inGeom,latticev,position,types);
    char symbol[21];

    int num_spg = spg_get_international(symbol, latticev, position, types, num_atoms, symprec);
    return std::string(symbol);
}

template<class VALTYPE, class CELL>
std::string spgw_get_schoenflies(qpp::geometry<VALTYPE,CELL> &inGeom, float symprec = 1e-7){

    int num_atoms = inGeom.size();
    auto latticev = new VALTYPE[3][3]();
    auto position = new VALTYPE[num_atoms][3]();
    auto types = new int[num_atoms]();
    get_spgdata_from_geom(inGeom,latticev,position,types);
    char symbol[21];

    int num_spg = spg_get_schoenflies(symbol, latticev, position, types, num_atoms, symprec);
    return std::string(symbol);
}


#endif // SPGW_HPP
