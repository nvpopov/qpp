#ifndef _QPP_CAD_DRAW_STYLE_
#define _QPP_CAD_DRAW_STYLE_
#include <string>
#include <Eigen/Eigen>
#include <geom/lace3d.hpp>

namespace qpp {
  class draw_style{
  public:
    draw_style(){};
    virtual void load_style() = 0;
    virtual void unload_style() = 0;
    virtual void render() = 0;
    virtual void render_atom(const vector3<float> color,
                             const vector3<float> pos) = 0;
    virtual void render_bond() = 0;
    virtual void render_molecule() = 0;
    virtual void render_cell() = 0;
    virtual void render_vector() = 0;
    virtual void render_primitive() = 0;
  };

  class default_draw_style : public draw_style{
  public:
    default_draw_style();
    void load_style() override;
    void unload_style() override;
    void render() override;
    void render_atom(const vector3<float> color,
                     const vector3<float> pos) override;
    void render_bond() override;
    void render_molecule() override;
    void render_cell() override;
    void render_vector() override;
    void render_primitive() override;
  };
}
#endif
