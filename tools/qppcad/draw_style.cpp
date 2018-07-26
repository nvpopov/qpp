#include <qppcad/draw_style.hpp>
#include <qppcad/app.hpp>

using namespace qpp;

default_draw_style::default_draw_style(){

}

void default_draw_style::load_style(){

}

void default_draw_style::unload_style(){

}

void default_draw_style::render(){

}

void default_draw_style::render_atom(const vector3<float> color,
                                     const vector3<float> po){
  app_state* astate = &(c_app::get_state());
  astate->def_shader->begin_shader_program();
 // std::cout<<"render_atom"<<std::endl;
 // astate->_sph_meshes[0]->render();
  astate->trm->render();
  astate->def_shader->end_shader_program();
}

void default_draw_style::render_bond(){

}

void default_draw_style::render_molecule(){

}

void default_draw_style::render_cell(){

}

void default_draw_style::render_vector(){

}

void default_draw_style::render_primitive(){

}
