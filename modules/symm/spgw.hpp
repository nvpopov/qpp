#ifndef SPGW_HPP
#define SPGW_HPP
#include <string>
#include "geom/geom.hpp"
#include "symm/symm.hpp"
#include "symm/transform.hpp"

extern "C"
{
    #include "spglib.h"
}

namespace qpp{

  template<class VALTYPE, class CELL>
  void get_spgdata_from_geom(const qpp::geometry<VALTYPE,CELL> &inGeom,
           double _lattice[3][3], double _positions[][3], int *_types){
    int num_atoms = inGeom.size();
    for(int i=0; i<num_atoms; i++){
      vector3<VALTYPE> r = inGeom.coord(i);
      if (!inGeom.frac)
  r = inGeom.cell.cart2frac(r);
  /*
  {
    matrix3d<VALTYPE> f2c,c2f;
    for (int j=0; j<3; j++)
      for (int k=0; k<3; k++)
        f2c(j,k) = inGeom.cell(j)(k);
    c2f = invert(f2c);
    r = c2f*r;
  }
  */
      _positions[i][0] = r.x();
      _positions[i][1] = r.y();
      _positions[i][2] = r.z();
      _types[i]=inGeom.type_table(i);
    }

    for(int i=0; i<3; i++){
      _lattice[i][0] = inGeom.cell.v[i].x();
      _lattice[i][1] = inGeom.cell.v[i].y();
      _lattice[i][2] = inGeom.cell.v[i].z();
    }

  }

  template<class VALTYPE, class CELL>
  int spgw_standartize_cell(geometry<VALTYPE,CELL> &inGeom,geometry<VALTYPE,CELL>
                            &outGeom, float symprec = 1e-5)
  {

    int num_atoms = inGeom.size();
    auto latticev = new VALTYPE[3][3]();
    auto position = new VALTYPE[num_atoms][3]();
    auto types = new int[num_atoms]();
    get_spgdata_from_geom(inGeom,latticev,position,types);

    int to_primitive = 1;
    int no_idealize = 0;
    int num_primitive_atom = spg_standardize_cell(latticev, position, types,
                                                  to_primitive, no_idealize,
                                                  num_atoms, symprec);

    //Get standartized cell back to user
    for(int i=0; i<3; i++){
      outGeom.cell.v[i].x() = latticev[i][0];
      outGeom.cell.v[i].y() = latticev[i][1];
      outGeom.cell.v[i].z() = latticev[i][2];
    }

    for(int i=0; i<num_atoms; i++){
      outGeom.add(inGeom.atom_of_type(types[i]),
                  position[i][0], position[i][1], position[i][2]);
    }

    return num_primitive_atom;
  }

  template<class REAL, class CELL>
  void spgw_get_symmetry(generated_group<rotrans<REAL,true> > & G,
       geometry<REAL,CELL> & geom,
       REAL R = geometry<REAL,CELL>::tol_geom_default) {
    int nat = geom.size();
    auto lattice = new double[3][3]();
    auto position = new double[nat][3]();
    auto types = new int[nat]();

    get_spgdata_from_geom(geom,lattice,position,types);

    int max_size = nat*48, nsymm;
    double translation[max_size][3];
    int rotation[max_size][3][3];

    //std::cout << "before get symmetry\n";

    nsymm = spg_get_symmetry(rotation, translation, max_size, lattice, position, types, nat, R);
    matrix3<REAL> f2c,c2f;

    //std::cout << "after get symmetry\n";

    G.group.clear();

    for (int i=0; i<3; i++)
      for (int j=0; j<3; j++)
        f2c(i,j) = geom.cell(i)(j);

    c2f = f2c.inverse();

    for (int i=0; i<nsymm; i++)
      {
  //std::cout << "i= " << i << "\n";

      matrix3<REAL> rot;
      vector3<REAL> transl = {translation[i][0],translation[i][1],translation[i][2]};
      for (int j=0; j<3; j++)
  for (int k=0; k<3; k++)
    rot(j,k) = rotation[i][j][k];
      rot = f2c*rot*c2f;
      G.group.push_back(rotrans<REAL,true>(f2c*transl,rot,&geom.cell));
      }

    /*
  std::cout << "Leaving get_symmetry\n";
  for (int i=0; i<G.group.size(); i++)
  std:: cout << G.group[i] << "\n";
    */

  }

  template<class VALTYPE, class CELL>
  std::string spgw_get_international(geometry<VALTYPE,CELL> &inGeom,
                                     float symprec = 1e-7){

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
  std::string spgw_get_schoenflies(geometry<VALTYPE,CELL> &inGeom, float symprec = 1e-7){

    int num_atoms = inGeom.size();
    auto latticev = new VALTYPE[3][3]();
    auto position = new VALTYPE[num_atoms][3]();
    auto types = new int[num_atoms]();
    get_spgdata_from_geom(inGeom,latticev,position,types);
    char symbol[21];

    int num_spg = spg_get_schoenflies(symbol, latticev, position, types, num_atoms, symprec);
    return std::string(symbol);
  }

}

#endif // SPGW_HPP
