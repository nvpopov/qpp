#ifndef _QPP_COMPUTE_INSTANCE
#define _QPP_COMPUTE_INSTANCE
#include <geom/geom.hpp>
#include <compute/compute_driver.hpp>

namespace qpp{

  template<typename REAL>
  class compute_instance {
  public:
    compute_instance(){

    }

    REAL energy(){
      return 0.0;
    }

    gradient(std::vector<qpp::vector3d<REAL> > &grad){

    }
  };

}

#endif
