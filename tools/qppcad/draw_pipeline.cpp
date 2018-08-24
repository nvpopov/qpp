#include <qppcad/draw_pipeline.hpp>
#include <qppcad/app.hpp>

using namespace qpp;

draw_pipeline::draw_pipeline(){

}

void draw_pipeline::load_pipeline(){

}

void draw_pipeline::unload_pipeline(){

}

void draw_pipeline::render(){

}

void draw_pipeline::begin_atom_render(){
  app_state* astate = &(c_app::get_state());
  astate->def_shader->begin_shader_program();
}

void draw_pipeline::render_atom(const vector3<float> color,
                                const vector3<float> pos,
                                const float radius){

  app_state* astate = &(c_app::get_state());
  // std::cout<<"render_atom"<<std::endl;

  astate->def_shader->set_u(sp_u_name::vTranslate, (GLfloat*)(pos.data()));
  astate->def_shader->set_u(sp_u_name::fScale, (GLfloat*)(&radius));
  astate->def_shader->set_u(sp_u_name::vColor, (GLfloat*)(color.data()));

  matrix4<float> mModelViewInvTr = (
                                     astate->_camera->mView*matrix4<float>::Identity()).inverse().transpose();
  // our Model matrix equals unity matrix, so just pass matrix from app state
  astate->def_shader->set_u(sp_u_name::mModelViewProj,
                            astate->_camera->mViewProjection.data());
  astate->def_shader->set_u(sp_u_name::mModelView, astate->_camera->mView.data());
  astate->def_shader->set_u(sp_u_name::mModelViewInvTr,
                            mModelViewInvTr.data());

  astate->_sph_meshes[0]->render();
  // astate->trm->render();

}

void draw_pipeline::end_atom_render(){
  app_state* astate = &(c_app::get_state());
  astate->def_shader->end_shader_program();
}

void draw_pipeline::begin_render_bond(){
  app_state* astate = &(c_app::get_state());
  astate->bond_shader->begin_shader_program();
}

void draw_pipeline::render_bond(const vector3<float> color,
                                const vector3<float> vBondStart,
                                const vector3<float> vBondEnd,
                                const float fBondRadius){
  app_state* astate = &(c_app::get_state());

  vector3<float> vBondEndNew = (vBondEnd - vBondStart)*(-0.498f) + vBondEnd;

  matrix4<float> mModelTr = matrix4<float>::Identity();
  mModelTr.block<3,1>(0,3) = vBondStart;
  mModelTr.block<3,1>(0,2) = vBondEndNew - vBondStart;

  vector3<float> vAxisNorm = mModelTr.block<3,1>(0,2).normalized();
  mModelTr.block<3,1>(0,0) = vAxisNorm.unitOrthogonal() * fBondRadius;
  mModelTr.block<3,1>(0,1) = vAxisNorm.cross(mModelTr.block<3,1>(0,0));
  mModelTr.block<3,1>(0,3) = vBondStart;

  matrix4<float> mModel = mModelTr  /** rotM * mModelSc */;
  matrix4<float> mModelViewInvTr =
      (astate->_camera->mView * mModelTr).inverse().transpose(); /* * rotM*/;

  matrix4<float> mModelView = astate->_camera->mView * mModel;
  matrix4<float> mModelViewProjection = astate->_camera->mViewProjection * mModel;

  astate->bond_shader->set_u(sp_u_name::mModelViewProj,
                             mModelViewProjection.data());
  astate->bond_shader->set_u(sp_u_name::mModelView, mModelView.data());
  astate->bond_shader->set_u(sp_u_name::vColor, (GLfloat*)(color.data()));
  astate->bond_shader->set_u(sp_u_name::mModelViewInvTr,
                             mModelViewInvTr.data());

  astate->cylinder_mesh->render();

}

void draw_pipeline::end_render_bond(){
  app_state* astate = &(c_app::get_state());
  astate->bond_shader->end_shader_program();
}

void draw_pipeline::render_molecule(){

}

void draw_pipeline::render_cell(){

}

void draw_pipeline::render_vector(){

}

void draw_pipeline::render_primitive(){

}

void draw_pipeline::begin_render_aabb(){
  begin_render_line();
}

void draw_pipeline::render_aabb(const vector3<float> vColor,
                                const vector3<float> vBoxMin,
                                const vector3<float> vBoxMax){

  vector3<float> vBoxSize = vBoxMax - vBoxMin;

  /// 1
  render_line(
        vColor,
        vBoxMin,
        vector3<float>(vBoxMin[0], vBoxMin[1], vBoxMin[2]+vBoxSize[2]));

  /// 2
  render_line(
        vColor,
        vBoxMin,
        vector3<float>(vBoxMin[0], vBoxMin[1]+vBoxSize[1], vBoxMin[2] ));

  /// 3
  render_line(
        vColor,
        vBoxMin,
        vector3<float>(vBoxSize[0]+vBoxMin[0], vBoxMin[1], vBoxMin[2]));

  /// 4 +x +y
  render_line(
        vColor,
        vector3<float>(vBoxMin[0]+vBoxSize[0], vBoxMin[1], vBoxMin[2]),
      vector3<float>(vBoxMin[0]+vBoxSize[0], vBoxMin[1]+vBoxSize[1], vBoxMin[2]));

  ///5 +x +z
  render_line(
        vColor,
        vector3<float>(vBoxMin[0]+vBoxSize[0], vBoxMin[1], vBoxMin[2]),
      vector3<float>(vBoxMin[0]+vBoxSize[0], vBoxMin[1], vBoxMin[2]+vBoxSize[2]));

  /// 6 +y +x
  render_line(
        vColor,
        vector3<float>(vBoxMin[0], vBoxMin[1]+vBoxSize[1], vBoxMin[2]),
      vector3<float>(vBoxMin[0]+vBoxSize[0], vBoxMin[1]+vBoxSize[1], vBoxMin[2]));

  /// 7 +y +z
  render_line(
        vColor,
        vector3<float>(vBoxMin[0], vBoxMin[1]+vBoxSize[1], vBoxMin[2]),
      vector3<float>(vBoxMin[0], vBoxMin[1]+vBoxSize[1], vBoxMin[2]+vBoxSize[2]));

  /// 8  +z +x
  render_line(
        vColor,
        vector3<float>(vBoxMin[0], vBoxMin[1], vBoxMin[2]+vBoxSize[2]),
      vector3<float>(vBoxMin[0]+vBoxSize[1], vBoxMin[1], vBoxMin[2]+vBoxSize[2]));

  /// 9 +z +y
  render_line(
        vColor,
        vector3<float>(vBoxMin[0], vBoxMin[1], vBoxMin[2]+vBoxSize[2]),
      vector3<float>(vBoxMin[0], vBoxMin[1]+vBoxSize[1], vBoxMin[2]+vBoxSize[2]));

  /// 10
  render_line(
        vColor,
        vBoxMax,
        vector3<float>(vBoxMax[0], vBoxMax[1], vBoxMax[2]-vBoxSize[2]));

  /// 11
  render_line(
        vColor,
        vBoxMax,
        vector3<float>(vBoxMax[0], vBoxMax[1]-vBoxSize[1], vBoxMax[2]));
  /// 12
  render_line(
        vColor,
        vBoxMax,
        vector3<float>(vBoxMax[0]-vBoxSize[0], vBoxMax[1], vBoxMax[2]));
}

void draw_pipeline::end_render_aabb(){
  end_render_line();
}

void draw_pipeline::begin_render_line(){
  app_state* astate = &(c_app::get_state());
  astate->unit_line_shader->begin_shader_program();
}

void draw_pipeline::render_line(const vector3<float> color,
                                const vector3<float> vStart,
                                const vector3<float> vEnd){
  app_state* astate = &(c_app::get_state());


  astate->unit_line_shader->set_u(sp_u_name::vColor,
                                  (GLfloat*)color.data());
  astate->unit_line_shader->set_u(sp_u_name::vLineStart,
                                  (GLfloat*)vStart.data());
  astate->unit_line_shader->set_u(sp_u_name::vLineEnd,
                                  (GLfloat*)vEnd.data());
  astate->unit_line_shader->set_u(sp_u_name::mModelViewProj,
                                  astate->_camera->mViewProjection.data());
  astate->unit_line_shader->set_u(sp_u_name::mModelView,
                                  astate->_camera->mView.data());
  astate->unit_line->render();

}

void draw_pipeline::end_render_line(){
  app_state* astate = &(c_app::get_state());
  astate->unit_line_shader->end_shader_program();

}
