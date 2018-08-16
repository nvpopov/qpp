#ifndef _QPP_CAD_DRAW_PIPELINE_
#define _QPP_CAD_DRAW_PIPELINE_
#include <string>
#include <Eigen/Eigen>
#include <geom/lace3d.hpp>

namespace qpp {

  class draw_pipeline{
  public:
    draw_pipeline();
    void load_pipeline();
    void unload_pipeline();
    void render();

    void begin_atom_render();
    void render_atom(const vector3<float> color,
                     const vector3<float> pos,
                     const float radius);
    void end_atom_render();

    void render_bond(const vector3<float> color,
                     const vector3<float> vBondStart,
                     const vector3<float> vBondEnd,
                     const float fBondRadius);
    void render_molecule();
    void render_cell();
    void render_vector();
    void render_primitive();
    void render_line(const vector3<float> color,
                     const vector3<float> vStart,
                     const vector3<float> vEnd);
  };

}
#endif
