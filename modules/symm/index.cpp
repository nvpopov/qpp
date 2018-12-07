#include <symm/index.hpp>

namespace qpp {

  index atom_index(int at, const index & I) {
    index res = index::D(I.DIM+1);
    res(0) = at;
    for (int d=0; d<I.DIM; d++)
      res(d+1) = I(d);
    return res;
  }

  // -------------------------------------------------------------

  bool compare_atindex(const index & at1, const index & at2) {
    return at1(0) > at2(0);
  }

}
