#ifndef QPP_RADIAL_DENSITY_FUNCTION
#define QPP_RADIAL_DENSITY_FUNCTION

#include <geom/lace3d.hpp>
#include <geom/geom.hpp>

namespace qpp {

  template<typename REAL, typename CELL>
  void compute_rdf(geometry<REAL, CELL> &geom,
                   std::vector<REAL> &data,
                   REAL data_min = 0.1,
                   REAL data_max = 4.0,
                   size_t data_steps = 10) {

  }


} // namespace qpp

#endif
