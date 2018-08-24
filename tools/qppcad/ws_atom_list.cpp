#include <qppcad/ws_atom_list.hpp>
#include <qppcad/app.hpp>
#include <io/geomio.hpp>

using namespace qpp;

ws_atom_list::ws_atom_list(){

  bNeedToRebuildNBT = true;
  iDim = 0;
  cell = new periodic_cell<float>(
  {20.0, 0.0, 0.0},
  {0.0, 20.0, 0.0},
  {0.0, 0.0, 20.0});

  geom = new xgeometry<float, periodic_cell<float> >(*cell,
  {"atom", "number", "charge", "x", "y", "z", "show", "sel"},

  {type_string, type_int, type_real, type_real, type_real, type_real,
   type_bool, type_bool}, "rg1");

  ext_obs = new extents_observer<float>(*geom);
  tws_tr = new tws_tree<float>(*geom);
  tws_tr->bAutoBonding = true;

  pos = vector3<float>(0.0, 0.0, 0.0);
}

void ws_atom_list::vote_for_view_vectors(vector3<float> &vOutLookPos,
                                         vector3<float> &vOutLookAt){
  if(geom->nat() > 2){
      vOutLookAt += (ext_obs->aabb.max + ext_obs->aabb.min) / 2.0;
      vector3<float> vSize = ext_obs->aabb.max - ext_obs->aabb.min;
      float fSize = vSize.norm();

      vOutLookPos  +=
          ext_obs->aabb.max.normalized() * clamp<float>(fSize, 10.0, 100.0);
    }
  else vOutLookPos += vector3<float>(0.0, 0.0, -5.0);

}

void ws_atom_list::update(){
  aabb = ext_obs->aabb;
}

void ws_atom_list::render(){
  ws_item::render();
  app_state* astate = &(c_app::get_state());

  if (astate->_draw_pipeline != nullptr){

      if (astate->bDebugDrawRTree){
          astate->_draw_pipeline->begin_render_aabb();
          tws_tr->apply_visitor(
                [astate](tws_node<float> *inNode, int deepLevel){
                  astate->_draw_pipeline->render_aabb(clr_maroon,
                                                     inNode->bb.min,
                                                     inNode->bb.max);
          });

          astate->_draw_pipeline->end_render_aabb();
        }

      // atom render start
      astate->_draw_pipeline->begin_atom_render();
      for (int i = 0; i < geom->nat(); i++){
          int ap_idx = ptable::number_by_symbol(geom->atom(i));
          float fDrawRad = 0.4f;
          vector3<float> color(0.0, 0.0, 1.0);

          if(ap_idx != -1){
              //TODO: radius scale factor
              fDrawRad = ptable::get_inst()->arecs[ap_idx-1].aRadius
                         * astate->fAtomRadiusScaleFactor;
              color = ptable::get_inst()->arecs[ap_idx-1].aColorGV;
            }

          if(geom->xfield<bool>("sel", i)) color =
              vector3<float>(0.43f, 0.55f, 0.12f);

          astate->_draw_pipeline->render_atom(color, geom->pos(i), fDrawRad);
        }
      astate->_draw_pipeline->end_atom_render();
      // atom render end

      // bond render
      astate->_draw_pipeline->begin_render_bond();
      int totB = 0;

      for (int i = 0; i < geom->nat(); i++)
        for (int j = 0; j < tws_tr->n(i); j++){
            int ap_idx = ptable::number_by_symbol(geom->atom(i));
            vector3<float> color(0.0, 0.0, 1.0);

            if(ap_idx != -1){
                color = ptable::get_inst()->arecs[ap_idx-1].aColorGV;
              }



            astate->_draw_pipeline->render_bond(color, geom->pos(i),
                                                geom->pos(tws_tr->table_atm(i,j)),
                                                astate->fBondScaleFactor);
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

void ws_atom_list::mouse_click(ray<float> *ray){
  if (ray){
      std::vector<tws_query_data<float>* > res;
      tws_tr->query_ray(ray, &res);
      std::cout << "res_size = " << res.size() << std::endl;

      std::sort(res.begin(), res.end(), tws_query_data_sort_by_dist<float>);

      if (res.size() > 0){
          std::cout << res[0]->atm << std::endl;
          geom->xfield<bool>("sel", res[0]->atm ) =
              !(geom->xfield<bool>("sel", res[0]->atm ));
        }
    }
}

bool ws_atom_list::support_translation(){
  return true;
}

bool ws_atom_list::support_rotation(){
  return false;
}

bool ws_atom_list::support_scaling(){
  return  false;
}

bool ws_atom_list::support_content_editing(){
  return true;
}

void ws_atom_list::shift(const vector3<float> vShift){
  tws_tr->bAutoBonding = false;
  tws_tr->bAutoBuild   = false;

  for (int i = 0; i < geom->nat(); i++)
    geom->coord(i) = vShift + geom->pos(i) ;

  ext_obs->aabb.min = vShift + ext_obs->aabb.min;
  ext_obs->aabb.max = vShift + ext_obs->aabb.max;

  tws_tr->bAutoBonding = true;
  tws_tr->bAutoBuild   = true;
}

void ws_atom_list::load_from_file(qc_file_format eFileFormat,
                                  std::string sFileName,
                                  bool bAutoCenter){
  //clean geom and tws-tree
  tws_tr->bAutoBonding = false;
  tws_tr->bAutoBuild   = false;
  tws_tr->clear_ntable();
  tws_tr->clear_tree();
  ext_obs->bFirstData = true;
  std::ifstream fQCData(sFileName);

  switch (eFileFormat) {
    case qc_file_format::format_standart_xyz:

      name = extract_base_name(sFileName);
      read_xyz(fQCData, *(geom));
      break;

    default: c_app::log("File format not implemented");

    }

  if(bAutoCenter){
      vector3<float> vCenter(0.0, 0.0, 0.0);
      for (int i = 0; i < geom->nat(); i++)
        vCenter += geom->pos(i);
      vCenter *= (1.0f / geom->nat());
      for (int i = 0; i < geom->nat(); i++)
        geom->coord(i) = -vCenter + geom->pos(i) ;

      ext_obs->aabb.min = -vCenter + ext_obs->aabb.min;
      ext_obs->aabb.max = -vCenter + ext_obs->aabb.max;


    }

  tws_tr->manual_build();
  tws_tr->find_all_neighbours();
  tws_tr->bAutoBonding = true;
  tws_tr->bAutoBuild   = true;

}

void ws_atom_list::rebuild_ngbt(){

  bNeedToRebuildNBT = false;
}
