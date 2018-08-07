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
                                     const vector3<float> pos,
                                     const float radius){

  app_state* astate = &(c_app::get_state());
  astate->def_shader->begin_shader_program();
  // std::cout<<"render_atom"<<std::endl;
  astate->def_shader->set_u(sp_u_name::vTranslate, (GLfloat*)(pos.data()));
  astate->def_shader->set_u(sp_u_name::fScale, (GLfloat*)(&radius));
  astate->def_shader->set_u(sp_u_name::vColor, (GLfloat*)(color.data()));

  // our Model matrix equals unity matrix, so just pass matrix from app state
  astate->def_shader->set_u(sp_u_name::mModelViewProj,
                            astate->mViewProjection.data());
  astate->def_shader->set_u(sp_u_name::mModelView, astate->mView.data());

  astate->_sph_meshes[0]->render();
  // astate->trm->render();
  astate->def_shader->end_shader_program();
}

void default_draw_style::render_bond(const vector3<float> color,
                                     const vector3<float> vBondStart,
                                     const vector3<float> vBondEnd,
                                     const float fBondRadius){
  app_state* astate = &(c_app::get_state());
  astate->bond_shader->begin_shader_program();

  vector3<float> pos = (vBondStart + vBondEnd) * 0.5;
  vector3<float> pos_d = (vBondEnd - vBondStart);
  vector3<float> pos_n = pos_d.normalized();
  vector3<float> bond_c_n = pos.normalized();
  matrix4<float> rotM = align_vectors4(pos_n, vector3<float>(0.0, 0.0, 1.0));

  matrix4<float> mModelTr = matrix4<float>::Identity();
  pos += -0.5*pos_n * pos_d.norm();
  mModelTr(0,3) = pos(0);
  mModelTr(1,3) = pos(1);
  mModelTr(2,3) = pos(2);

  matrix4<float> mModelSc = matrix4<float>::Identity();
  mModelSc(0,0) = fBondRadius;
  mModelSc(1,1) = fBondRadius;
  mModelSc(2,2) = pos_d.norm();
  //std::cout << "posnorm = " << pos_d.norm() << std::endl;

  matrix4<float> mModel = mModelTr  * rotM * mModelSc ;

  matrix4<float> mModelView = astate->mView * mModel;
  matrix4<float> mModelViewProjection = astate->mViewProjection * mModel;

  astate->bond_shader->set_u(sp_u_name::mModelViewProj,
                                  mModelViewProjection.data());
  astate->bond_shader->set_u(sp_u_name::mModelView, mModelView.data());
  astate->bond_shader->set_u(sp_u_name::vColor, (GLfloat*)(color.data()));

  astate->cylinder_mesh->render();
  astate->bond_shader->end_shader_program();
}

void default_draw_style::render_molecule(){

}

void default_draw_style::render_cell(){

}

void default_draw_style::render_vector(){

}

void default_draw_style::render_primitive(){

}

void default_draw_style::render_line(const vector3<float> color,
                                     const vector3<float> vStart,
                                     const vector3<float> vEnd){
  app_state* astate = &(c_app::get_state());
  astate->unit_line_shader->begin_shader_program();

  astate->unit_line_shader->set_u(sp_u_name::vColor,
                                  (GLfloat*)color.data());
  astate->unit_line_shader->set_u(sp_u_name::vLineStart,
                                  (GLfloat*)vStart.data());
  astate->unit_line_shader->set_u(sp_u_name::vLineEnd,
                                  (GLfloat*)vEnd.data());
  astate->unit_line_shader->set_u(sp_u_name::mModelViewProj,
                            astate->mViewProjection.data());
  astate->unit_line_shader->set_u(sp_u_name::mModelView, astate->mView.data());
  astate->unit_line->render();
  astate->unit_line_shader->end_shader_program();
}
