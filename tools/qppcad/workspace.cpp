#include <qppcad/workspace.hpp>
#include <qppcad/app.hpp>
#include <data/ptable.hpp>
#include <io/geomio.hpp>
#include <mathf/math.hpp>

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

//  std::cout << "set bv " << _vLookAt << std::endl << _vLookPos << std::endl
//            << "end bv " << std::endl;
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
  rtree = new aux_rtree<float>(*geom);
  rtree->bAutoBonding = true;
}

void ws_atom_list::vote_for_view_vectors(vector3<float> &vOutLookPos,
                                         vector3<float> &vOutLookAt){
  vOutLookAt += (ext_obs->max_pos + ext_obs->min_pos) / 2.0;
  vector3<float> vSize = ext_obs->max_pos - ext_obs->min_pos;
 // std::cout << vSize << std::endl;
  float fSize = vSize.norm();

  vOutLookPos  +=
      ext_obs->max_pos.normalized() * clamp<float>(fSize, 10.0, 100.0);
  //std::cout << vSize << std::endl << vOutLookAt << std::endl << std::endl;
}

void ws_atom_list::render(){

  app_state* astate = &(c_app::get_state());

  if (astate->_draw_pipeline != NULL){

      if (astate->bDebugDrawRTree){
          astate->_draw_pipeline->begin_render_aabb();
          rtree->apply_visitor(
                [astate](rtree_node<float> *inNode){
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
          float fDrawRad = 0.4;
          vector3<float> color(0.0, 0.0, 1.0);

          if(ap_idx != -1){
              fDrawRad = ptable::get_instance()->arecs[ap_idx-1].aRadius * 0.25;
              color = ptable::get_instance()->arecs[ap_idx-1].aColorJmol;
            }

          astate->_draw_pipeline->render_atom(color,
                                              geom->pos(i), fDrawRad
                                              );
        }
      astate->_draw_pipeline->end_atom_render();
      // atom render end

      // bond render
      astate->_draw_pipeline->begin_render_bond();
      int totB = 0;
            for (int i = 0; i < geom->nat(); i++)
              for (int j = 0; j < rtree->n(i); j++){
                  //std::cout<< i << "  " << nt->table(i, j) <<std::endl;
                  int ap_idx = ptable::number_by_symbol(geom->atom(i));
                  vector3<float> color(0.0, 0.0, 1.0);

                  if(ap_idx != -1){
                      color = ptable::get_instance()->arecs[ap_idx-1].aColorJmol;
                    }
                  astate->_draw_pipeline->render_bond(color,
                                                      geom->pos(i),
                                                      geom->pos(rtree->table_atm(i,j)),
                                                      0.08);
                  totB += 1;
                }
//      std::cout << "Tot bond" << totB << std::endl;
      astate->_draw_pipeline->end_render_bond();
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
  std::ifstream si2("../examples/io/ref_data/dna.xyz");
  _wsl->rtree->bAutoBonding = false;
  read_xyz(si2, *(_wsl->geom));
  _wsl->rtree->find_all_neighbours();


  ws_atom_list* _wsl2 = new ws_atom_list();
  std::ifstream nt2("../examples/io/ref_data/nanotube.xyz");
  _wsl2->name = "nanotube";
  _wsl2->rtree->bAutoBonding = false;
  read_xyz(nt2, *(_wsl2->geom));
  _wsl2->rtree->find_all_neighbours();

   ws_atom_list* _wsl3 = new ws_atom_list();
  std::ifstream nt3("../examples/io/ref_data/cdse_nanocrystal.xyz");
  _wsl3->name = "cdse";
  _wsl3->rtree->bAutoBonding = false;
  read_xyz(nt3, *(_wsl3->geom));
  _wsl3->rtree->find_all_neighbours();

  workspace* _ws = new workspace();
  _ws->ws_name = "default1";

  workspace* _ws2 = new workspace();
  _ws2->ws_name = "nanotube";

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
