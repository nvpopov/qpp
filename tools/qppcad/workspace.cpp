#include <qppcad/workspace.hpp>
#include <qppcad/app.hpp>
#include <data/ptable.hpp>

using namespace qpp;

void workspace::render(){
  app_state* astate = &(c_app::get_state());
  if (astate->_draw_style != NULL){

      if (astate->bDrawAxis){
          astate->_draw_style->render_line(vector3<float>(1.0,  0.0, 0.0),
                                           vector3<float>(0.0,  0.0, 0.0),
                                           vector3<float>(1.0, 0.0, 0.0) );

          astate->_draw_style->render_line(vector3<float>(0.0,  1.0, 0.0),
                                           vector3<float>(0.0,  0.0, 0.0),
                                           vector3<float>(0.0, 1.0, 0.0) );

          astate->_draw_style->render_line(vector3<float>(0.0,  0.0, 1.0),
                                           vector3<float>(0.0,  0.0, 0.0),
                                           vector3<float>(0.0, 0.0, 1.0) );
        }
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

  geom = new geometry<float, periodic_cell<float> >(iDim);

}

void ws_atom_list::render(){

  app_state* astate = &(c_app::get_state());
  if (astate->_draw_style != NULL){
      for (int i = 0; i < geom->nat(); i++){
          int ap_idx = ptable::number_by_symbol(geom->atom(i));
          vector3<float> color =
              ptable::get_instance()->arecs[ap_idx-1].aColorJmol;
          astate->_draw_style->render_atom(color,
                                           geom->pos(i),
                                           ptable::get_instance()->
                                           arecs[ap_idx-1].aRadius * 0.35);
        }


      for (int i = 0; i < geom->nat(); i++)
        for (int j = 0; j < nt->n(i); j++){
            //std::cout<< i << "  " << nt->table(i, j) <<std::endl;
            astate->_draw_style->render_bond(vector3<float>(1.0, 1.0, 1.0),
                                             geom->pos(i),
                                             geom->pos(nt->table(i, j)),
                                             0.08);
          }
    }
}

void ws_atom_list::render_ui(){
  ImGui::Button("Rebond");
  ImGui::SameLine();
  ImGui::Button("Delete");
  static bool bVisible;
  ImGui::SameLine();
  ImGui::Checkbox("Show" , &bVisible);

  int _dim = iDim;
  ImGui::Text("Geom. dim:"); ImGui::SameLine();
  ImGui::SliderInt("", &_dim, 0, 3);
  iDim = _dim;

  if (ImGui::TreeNode("Atoms")){
      for (int i = 0; i < geom->nat(); i++)
        if (ImGui::TreeNode(fmt::format("{}:{}", geom->atom(i), i).c_str())){
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
  bt->default_distance = 0.01;
  bt->set_pair("C", "C", 1.8);
  //nt->build_disttable();
  geom->build_types();
  nt->build();
  bNeedToRebuildNBT = false;
}

void workspace_manager::init_default_workspace(){
  ws_atom_list* _wsl = new ws_atom_list();
  _wsl->name = "geometry1";
  _wsl->geom->add("N",          1.75524,       -0.03055,       -0.15305);
  _wsl->geom->add("C",          0.46128,        0.62257,        0.10589);
  _wsl->geom->add("C",         -0.74491,       -0.32028,       -0.01207);
  _wsl->geom->add("O",         -1.89675,        0.44072,        0.26071);
  _wsl->geom->add("H",          1.76784,       -0.40647,       -1.07847);
  _wsl->geom->add("H",          1.89801,       -0.77424,        0.49847);
  _wsl->geom->add("H",         0.36238,        1.46995,       -0.60184);
  _wsl->geom->add("H",         0.50565,        1.07184,        1.11828);
  _wsl->geom->add("H",        -0.66487,       -1.16329 ,       0.70383);
  _wsl->geom->add("H",         -0.80945,       -0.76139,       -1.02735);
  _wsl->geom->add("H",         -2.63443,       -0.14886 ,       0.18560);
   _wsl->bt = new bonding_table<float>();
   _wsl->bt->default_distance = 0.01;
   _wsl->bt->set_pair("C", "C", 1.8);
   _wsl->bt->set_pair("H", "C", 1.8);
   _wsl->bt->set_pair("O", "C", 1.8);
   _wsl->bt->set_pair("H", "O", 1.8);
   _wsl->bt->set_pair("N", "C", 1.8);
   _wsl->bt->set_pair("N", "H", 1.8);
   _wsl->nt = new neighbours_table<float>(*_wsl->geom, *_wsl->bt);
  _wsl->rebuild_ngbt();

  workspace* _ws = new workspace();
  _ws->ws_name = "default1";

  workspace* _ws2 = new workspace();
  _ws2->ws_name = "default2";

  workspace* _ws3 = new workspace();
  _ws3->ws_name = "default3";

  _ws->ws_items.push_back(_wsl);
  ws.push_back(_ws2);
  ws.push_back(_ws3);
  ws.push_back(_ws);
  iCurrentWorkSpace = ws.size() - 1;
}

void workspace_manager::render_current_workspace(){
  //std::cout<<"render_current_workspace"<<std::endl;
  if (ws.size() > 0)
    if ((iCurrentWorkSpace >= 0) && (iCurrentWorkSpace < ws.size()))
      ws[iCurrentWorkSpace]->render();
}
