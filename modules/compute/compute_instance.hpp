#ifndef _QPP_COMPUTE_INSTANCE
#define _QPP_COMPUTE_INSTANCE
#include <geom/geom.hpp>

namespace qpp{

  template<typename REAL, typename CELL>
  class compute_instance {
  public:
    qpp::geometry<REAL, CELL> geom;
    virtual compute_instance() = 0;
  };

}

#endif
