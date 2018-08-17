#include <qppcad/workspace.hpp>
#include <qppcad/app.hpp>
#include <data/ptable.hpp>
#include <io/geomio.hpp>

using namespace qpp;

void workspace::reset_camera(){
  ws_cam->reset_camera();
  set_best_view();
}

void workspace::set_best_view(){
  vector3<float> _vLookAt = vector3<float>(0.0, 0.0, 0.0);
  vector3<float> _vLookPos = vector3<float>(0.0, 0.0, 0.0);

  for (ws_item* _ws_item : ws_items)
    _ws_item->vote_for_view_vectors(_vLookPos, _vLookAt);

  _vLookAt  /= ws_items.size();
  _vLookPos /= ws_items.size();

  ws_cam->vLookAt = _vLookAt;
  ws_cam->vViewPoint = _vLookPos;

}

void workspace::render(){
  if (bFirstRender) {
      set_best_view();
      bFirstRender = false;
    }

  app_state* astate = &(c_app::get_state());
  if (astate->_draw_pipeline != NULL){


      ///// Draw grid /////
      if (astate->bDrawGrid){
          astate->shaderLineMesh->begin_shader_program();
          vector3<float> color(0.75, 0.75, 0.75);
          astate->shaderLineMesh->set_u(sp_u_name::mModelViewProj,
                                        astate->_camera->mViewProjection.data());
          astate->shaderLineMesh->set_u(sp_u_name::mModelView,
                                        astate->_camera->mView.data());
          astate->shaderLineMesh->set_u(sp_u_name::vColor,
                                        (GLfloat*)color.data());

          for (int dx = -4; dx <= 4; dx++)
            for (int dz = -4; dz <= 4; dz++){
                vector3<float> vTr(dx * (20 * 0.5), dz * (20 * 0.5), 0 );
                astate->shaderLineMesh->set_u(sp_u_name::vTranslate,
                                              (GLfloat*)vTr.data());
                astate->gridXZ->render();

              }
          astate->shaderLineMesh->end_shader_program();
        }
      ///// Draw grid /////

      ///// Draw axis /////
      if (astate->bDrawAxis){
          vector3<float> vScrTW = astate->_camera->unproject(-0.95, -0.90);
          float fAxisLen = 0.07 *astate->_camera->fStoredDist;
          if (astate->_camera->cur_proj ==
              app_camera_proj_type::CAMERA_PROJ_PERSP)
            fAxisLen = 0.015;

          astate->_draw_pipeline->begin_render_line();
          astate->_draw_pipeline->
              render_line(vector3<float>(1.0, 0.0, 0.0),
                          vector3<float>(0.0, 0.0, 0.0) + vScrTW,
                          vector3<float>(fAxisLen, 0.0, 0.0) + vScrTW);

          astate->_draw_pipeline->
              render_line(vector3<float>(0.0, 1.0, 0.0),
                          vector3<float>(0.0, 0.0, 0.0) + vScrTW,
                          vector3<float>(0.0, fAxisLen, 0.0) + vScrTW);

          astate->_draw_pipeline->
              render_line(vector3<float>(0.0, 0.0, 1.0),
                          vector3<float>(0.0, 0.0, 0.0) + vScrTW,
                          vector3<float>(0.0, 0.0, fAxisLen) + vScrTW);
          astate->_draw_pipeline->end_render_line();

        }
      ///// Draw axis end /////
    }

  for (ws_item* _ws_item : ws_items){
      _ws_item->render();
    }
}

ws_atom_list::ws_atom_list(){

  bNeedToRebuildNBT = true;
  iDim = 0;
  cell = new periodic_cell<float>(
  {20.0, 0.0, 0.0},
  {0.0, 20.0, 0.0},
  {0.0, 0.0, 20.0});

  geom = new xgeometry<float, periodic_cell<float> >(*cell,
  {"atom",
   "number",
   "charge",
   "x",
   "y",
   "z",
   "show"},

  {type_string,
   type_int,
   type_real,
   type_real,
   type_real,
   type_real,
   type_bool}, "rg1");

  ext_obs = new extents_observer<float>(*geom);
  rtree = new aux_rtree<float, periodic_cell<float>, vector3<float> >(*geom);
}

void ws_atom_list::vote_for_view_vectors(vector3<float> &vOutLookPos,
                                         vector3<float> &vOutLookAt){
  vOutLookAt += (ext_obs->max_pos + ext_obs->min_pos) / 2.0;
  vOutLookPos  += vOutLookAt +
      vector3<float>( 1.5*(ext_obs->max_pos(0) - ext_obs->min_pos(0)),
                      1.5*(ext_obs->max_pos(1) - ext_obs->min_pos(1)), 0);
}

void ws_atom_list::render(){

  app_state* astate = &(c_app::get_state());

  if (astate->_draw_pipeline != NULL){

      if (astate->bDebugDrawRTree){
          astate->_draw_pipeline->begin_render_aabb();
          rtree->apply_visitor(
                [astate](rtree_node<float, vector3<float>, 3> *inNode){
            vector3<float> vAABBMin(inNode->rect.rect_min[0],
                inNode->rect.rect_min[1],
                inNode->rect.rect_min[2]);

            vector3<float> vAABBMax(inNode->rect.rect_max[0],
                inNode->rect.rect_max[1],
                inNode->rect.rect_max[2]);

            astate->_draw_pipeline->render_aabb(vector3<float>(1.0, 1.0, 1.0),
                                                vAABBMin, vAABBMax);

          });
          astate->_draw_pipeline->end_render_aabb();
        }

      // atom render start
      astate->_draw_pipeline->begin_atom_render();
      for (int i = 0; i < geom->nat(); i++){
          int ap_idx = ptable::number_by_symbol(geom->atom(i));
          vector3<float> color =
              ptable::get_instance()->arecs[ap_idx-1].aColorJmol;
          astate->_draw_pipeline->render_atom(color,
                                              geom->pos(i),
                                              ptable::get_instance()->
                                              arecs[ap_idx-1].aRadius * 0.35);
        }
      astate->_draw_pipeline->end_atom_render();
      // atom render end

      // bond render
      //      for (int i = 0; i < geom->nat(); i++)
      //        for (int j = 0; j < nt->n(i); j++){
      //            //std::cout<< i << "  " << nt->table(i, j) <<std::endl;
      //            astate->_draw_pipeline->render_bond(vector3<float>(1.0, 1.0, 1.0),
      //                                                geom->pos(i),
      //                                                geom->pos(nt->table(i, j)),
      //                                                0.08);
      //          }
      // bond render end
    }
}

void ws_atom_list::render_ui(){
  ImGui::Separator();
  ImGui::Button("Rebond");
  ImGui::SameLine();
  ImGui::Button("Delete");
  static bool bVisible;
  ImGui::SameLine();
  ImGui::Checkbox("Show" , &bVisible);
  ImGui::Separator();
  int _dim = iDim;
  ImGui::Text("Geom. dim:"); ImGui::SameLine();
  ImGui::SliderInt("", &_dim, 0, 3);
  iDim = _dim;

  if (ImGui::TreeNode("Atoms")){
      for (int i = 0; i < geom->nat(); i++)
        if (ImGui::TreeNode(fmt::format("{}:{}", geom->atom(i), i).c_str())){
            //            ImGui::SameLine();
            //            ImGui::Button("eeeee");
            //  ImGui::Columns(2);
            //            float _x = geom->pos(i)[0];
            //            float _y = geom->pos(i)[1];
            //            float _z = geom->pos(i)[2];

            float vec3f[3] = { geom->pos(i)[0], geom->pos(i)[1], geom->pos(i)[2]};

            //            ImGui::Text("X");
            //            ImGui::Text("Y");
            //            ImGui::Text("Z");
            //ImGui::Se
            ImGui::Text("Pos.:");
            ImGui::SameLine();
            ImGui::PushID("flt3");
            ImGui::InputFloat3("", vec3f);
            ImGui::PopID();


            geom->coord(i) = vector3<float>(vec3f[0], vec3f[1], vec3f[2]);
            //   ImGui::Columns(1);
            ImGui::TreePop();
          }
      ImGui::TreePop();
    }
}

void ws_atom_list::rebuild_ngbt(){

  bNeedToRebuildNBT = false;
}

workspace *workspace_manager::get_current_workspace(){
  if ((iCurrentWorkSpace <= 0) && (iCurrentWorkSpace > ws.size())) return NULL;
  return ws[iCurrentWorkSpace];
}

void workspace_manager::init_default_workspace(){
  ws_atom_list* _wsl = new ws_atom_list();
  _wsl->name = "geometry1";
  std::ifstream si2("../examples/io/ref_data/slab.xyz");
  read_xyz(si2, *(_wsl->geom));
  //_wsl->make_camera_view();
  //  for(int i = 0; i < 30; i++)
  //   for(int j = 0; j < 30; j++){
  //   _wsl->geom->add("N",          1.75524 + j * 4,     -0.03055 +j* 4,       -0.15305 + i);
  //   _wsl->geom->add("C",          0.46128 + j * 4,        0.62257 +j* 4,        0.10589 + i);
  //   _wsl->geom->add("C",         -0.74491 + j * 4,       -0.32028 +j* 4,       -0.01207 + i);
  //   _wsl->geom->add("O",         -1.89675 + j * 4,        0.44072 +j* 4,        0.26071 + i);
  //   _wsl->geom->add("H",          1.76784 + j * 4,       -0.40647 +j* 4,       -1.07847 + i* 4);
  //   _wsl->geom->add("H",          1.89801 + j * 4,       -0.77424 +j* 4,        0.49847 + i);
  //   _wsl->geom->add("H",          0.36238 + j * 4,        1.46995 +j* 4,       -0.60184 + i);
  //   _wsl->geom->add("H",          0.50565 + j * 4,        1.07184 +j,        1.11828 + i* 4);
  //   _wsl->geom->add("H",         -0.66487 + j * 4,       -1.16329  +j,       0.70383 + i);
  //   _wsl->geom->add("H",         -0.80945 + j * 4 ,       -0.76139 +j,       -1.02735 + i* 4);
  //   _wsl->geom->add("H",         -2.63443 + j * 4,       -0.14886  +j,       0.18560 + i* 4);
  //}

  //  _wsl->bt = new bonding_table<float>();
  //  _wsl->bt->default_distance = 0.01;
  //  _wsl->bt->set_pair("C", "C", 1.8);
  //  _wsl->bt->set_pair("H", "C", 1.8);
  //  _wsl->bt->set_pair("O", "C", 1.8);
  //  _wsl->bt->set_pair("H", "O", 1.8);
  //  _wsl->bt->set_pair("N", "C", 1.8);
  //  _wsl->bt->set_pair("N", "H", 1.8);
  //  _wsl->nt = new neighbours_table<float>(*_wsl->geom, *_wsl->bt);
  //  _wsl->rebuild_ngbt();
  ws_atom_list* _wsl2 = new ws_atom_list();
  ws_atom_list* _wsl3 = new ws_atom_list();

  _wsl2->geom->add("Ca",          2,       2,       -0.15305);
  _wsl2->geom->add("F",          0.46128,        2,        0.10589);
  _wsl2->geom->add("F",         -0.74491,       -0.32028,       -0.01207);

  _wsl3->geom->add("Ba",          1,       2,       -0.15305);
  _wsl3->geom->add("Zn",          2,        2,        0.10589);
  _wsl3->geom->add("O",         -0.74491,       -1.32028,       -0.01207);

  workspace* _ws = new workspace();
  _ws->ws_name = "default1";

  workspace* _ws2 = new workspace();
  _ws2->ws_name = "default2";

  workspace* _ws3 = new workspace();
  _ws3->ws_name = "default3";

  _ws->ws_items.push_back(_wsl);
  _ws2->ws_items.push_back(_wsl2);
  _ws3->ws_items.push_back(_wsl3);

  ws.push_back(_ws2);
  ws.push_back(_ws3);
  ws.push_back(_ws);
  iCurrentWorkSpace = ws.size() - 1;
}

void workspace_manager::render_current_workspace(){
  //std::cout<<"render_current_workspace"<<std::endl;
  if (ws.size() > 0)
    if ((iCurrentWorkSpace >= 0) && (iCurrentWorkSpace < ws.size())){
        c_app::get_state()._camera = ws[iCurrentWorkSpace]->ws_cam;
        ws[iCurrentWorkSpace]->render();
      }
}
