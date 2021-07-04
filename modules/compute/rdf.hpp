#ifndef QPP_RADIAL_DISTRIBUTION_FUNCTION
#define QPP_RADIAL_DISTRIBUTION_FUNCTION

#include <geom/lace3d.hpp>
#include <geom/xgeom.hpp>

namespace qpp {

// naive
template<typename REAL, typename CELL>
void compute_rdf_naive(xgeometry<REAL, CELL> &geom,
                       Eigen::Matrix<REAL, Eigen::Dynamic, Eigen::Dynamic> &data,
                       REAL data_min = 0.1,
                       REAL data_max = 4.0,
                       size_t data_steps = 10,
                       REAL r_eps = 0.1) {
//  data.resize(1, data_steps); //rows, cols
//  REAL dstep = (data_max - data_min) / data_steps;
//  auto DIM = geom.get_DIM();
//  int nimg{1}; // required number of imaginary cells
//  if (DIM > 0) {
//    std::vector<REAL> cell_lens;
//    cell_lens.resize(DIM);
//    for (int i = 0; i < DIM; i++)
//      cell_lens[i] = geom.get_cell_vector(i).norm();
//    auto min_cell_len = *std::min_element(cell_lens.begin(), cell_lens.end());
//  // if (data_max > min_cell_len)
//  //    nimg = std::roung(data)
}

} // namespace qpp

#endif
