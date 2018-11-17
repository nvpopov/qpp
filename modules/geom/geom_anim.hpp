#ifndef QPP_GEOM_ANIM
#define QPP_GEOM_ANIM

#include <vector>
#include <geom/lace3d.hpp>
#include <string>

namespace qpp {

  enum geom_anim_type {
    anim_static,
    anim_generic,
    anim_geo_opt,
    anim_md,
    anim_vib
  };

  template<typename REAL>
  struct geom_anim_record_frame_t {
    std::vector<vector3<REAL> > atom_pos;
    std::vector<vector3<REAL> > atom_color;
  };

  template<typename REAL>
  struct geom_anim_record_t {
      std::string m_anim_name;
      geom_anim_type m_anim_type{anim_generic};
      std::vector<geom_anim_record_frame_t<REAL> > frame_data;
  };
}

#endif
