#ifndef QPP_GEOM_ANIM
#define QPP_GEOM_ANIM

#include <vector>
#include <geom/lace3d.hpp>
#include <string>

namespace qpp {

  enum geom_anim_type {
    geom_anim_generic,
    geom_anim_geo_opt,
    geom_anim_md,
    geom_anim_vib
  };

  template<typename REAL>
  struct geom_anim_record_t {
      std::string anim_name;
      geom_anim_type m_anim_type{geom_anim_generic};
      std::vector< std::vector<vector3<REAL> > > frame_data;
  };
}

#endif
