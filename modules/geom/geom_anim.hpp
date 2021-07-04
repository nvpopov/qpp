#ifndef QPP_GEOM_ANIM
#define QPP_GEOM_ANIM

#include <vector>
#include <geom/lace3d.hpp>
#include <string>

namespace qpp {

enum class geom_anim_e {
  anim_static,
  anim_generic,
  anim_geo_opt,
  anim_md,
  anim_vib
};

template<typename REAL>
struct geom_anim_record_frame_t {
  std::vector<vector3<REAL>> atom_pos;
  std::vector<vector3<REAL>> atom_colors;
  std::vector<std::string> atom_types;
  int tot_nat{-1}; // if > 0, anim has nonconst nat
  bool m_cell_is_animable{false};
  std::array<vector3<REAL>, 3> m_cell;
};

template<typename REAL>
struct geom_anim_record_t {
  std::string m_anim_name;
  geom_anim_e m_anim_type{geom_anim_e::anim_generic};
  bool m_variable_cell_anim{false};
  std::vector<geom_anim_record_frame_t<REAL>> frames;
  bool has_nonconstant_num_at() {
    return std::any_of(frames.begin(), frames.end(), [](auto &frame){return frame.tot_nat != -1;});
  }
};

} // namespace qpp

#endif
