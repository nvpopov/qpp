#ifndef _QPP_COMPUTE_DRIVER
#define _QPP_COMPUTE_DRIVER
#include <vector>
#include <tuple>

namespace qpp {

  template<typename REAL>
  class compute_driver{
  private:
    std::vector<std::tuple<int, std::string> > basisMap;
    std::vector<std::tuple<int, std::string> > ecpMap;
  public:
    bool can_perform_0d() = 0;
    bool can_perform_1d() = 0;
    bool can_perform_2d() = 0;
    bool can_perform_3d() = 0;
    bool can_perform_energy() = 0;
    bool can_perform_gradient() = 0;
  };

  template<typename REAL>
  class compute_driver_factory{

  };
}

#endif
