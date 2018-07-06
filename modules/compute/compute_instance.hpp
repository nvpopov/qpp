#ifndef _QPP_COMPUTE_INSTANCE
#define _QPP_COMPUTE_INSTANCE
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <compute/compute_driver.hpp>

namespace qpp{

  template<typename REAL>
  class compute_instance {
  private:
    compute_driver<REAL>* driver;
    //xgeometry<REAL,3>* geom;
  public:

//    compute_instance(compute_driver* _driver, xgeometry<3>* _geom){
//      driver = _driver;
//      geom = _geom;
//    }

    REAL energy(){
      return 0.0;
    }

    void gradient(std::vector<qpp::vector3<REAL> > &grad){

    }

    void geometry_optimize(){

    }
  };

}

#endif
