#ifndef QPP_GEOM_ANIM
#define QPP_GEOM_ANIM

#include <vector>
#include <geom/lace3d.hpp>
#include <string>

namespace qpp {

  enum geom_anim_t {
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
    bool m_cell_is_animable{false};
    std::array<vector3<REAL>, 3> m_cell;
  };

  template<typename REAL>
  struct geom_anim_record_t {
      std::string m_anim_name;
      geom_anim_t m_anim_type{anim_generic};
      bool m_variable_cell_anim{false};
      std::vector<geom_anim_record_frame_t<REAL> > frames;
  };

} // namespace qpp

#endif
