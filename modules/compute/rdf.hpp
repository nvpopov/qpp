#ifndef QPP_RADIAL_DENSITY_FUNCTION
#define QPP_RADIAL_DENSITY_FUNCTION

#include <geom/lace3d.hpp>
#include <geom/geom.hpp>

namespace qpp {

  // N^2 complexity alogorithm, no saptial optimization
  template<typename REAL, typename CELL>
  void compute_rdf(geometry<REAL, CELL> &geom,
                   std::vector<std::vector<REAL> > &data,
                   REAL data_min = 0.1,
                   REAL data_max = 4.0,
                   size_t data_steps = 10,
                   REAL r_eps = 0.1) {

    data.resize(geom.nat());
    for (auto &per_atom_rec : data) per_atom_rec.resize(data_steps);

    auto zero_idx = index::D(geom.DIM).all(0);

    for (size_t i = 0; i < geom.nat(); i++) {

        auto pos_i = geom.pos(i);

        for (size_t s = 0; s < data_steps; s++)
          for (size_t q = 0; q < geom.nat(); q++) {
              for (iterator idx(index::D(geom.DIM).all(-1), index::D(geom.DIM).all(1));
                   !idx.end(); idx++ )
                if (i != q || idx != zero_idx) {

                  }
            }

      }

  }

} // namespace qpp

#endif
