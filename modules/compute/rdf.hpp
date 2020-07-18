#ifndef QPP_RADIAL_DENSITY_FUNCTION
#define QPP_RADIAL_DENSITY_FUNCTION

#include <geom/lace3d.hpp>
#include <geom/xgeom.hpp>

namespace qpp {

  // naive
  template<typename REAL, typename CELL>
  void compute_rdf_naive(xgeometry<REAL, CELL> &geom,
                         std::vector<std::vector<REAL> > &data,
                         REAL data_min = 0.1,
                         REAL data_max = 4.0,
                         size_t data_steps = 10,
                         REAL r_eps = 0.1) {

//    xgeometry<REAL, periodic_cell<REAL> > tmp_geom(3);
//    geom.clone(tmp_geom, false);

//    data.resize(geom.nat());
//    for (auto &per_atom_rec : data) per_atom_rec.resize(data_steps);

//    //compute min max of input geometry
//    if (geom.nat() == 0) return;
//    vector3<REAL> min_pos = geom.pos(0);
//    vector3<REAL> max_pos = geom.pos(0);

//    for (size_t i = 0; i < geom.nat(); i++) {

//        if (min_pos[0] > geom.pos(i)[0]) min_pos[0] = geom.pos(i)[0];
//        if (min_pos[1] > geom.pos(i)[1]) min_pos[1] = geom.pos(i)[1];
//        if (min_pos[2] > geom.pos(i)[2]) min_pos[2] = geom.pos(i)[2];

//        if (max_pos[0] < geom.pos(i)[0]) max_pos[0] = geom.pos(i)[0];
//        if (max_pos[1] < geom.pos(i)[1]) max_pos[1] = geom.pos(i)[1];
//        if (max_pos[2] < geom.pos(i)[2]) max_pos[2] = geom.pos(i)[2];

//      }

//    auto zero_idx = index::D(geom.get_DIM()).all(0);

//    for (size_t i = 0; i < geom.nat(); i++) {

//        auto pos_i = geom.pos(i);

//        for (size_t s = 0; s < data_steps; s++)
//          for (size_t q = 0; q < geom.nat(); q++) {
//              for (iterator idx(index::D(geom.DIM).all(-1), index::D(geom.DIM).all(1));
//                   !idx.end(); idx++ )
//                if (i != q || idx != zero_idx) {

//                  }
//            }

//      }

  }

} // namespace qpp

#endif
