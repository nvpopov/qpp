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
                                           vector3<float>(50.0, 0.0, 0.0) );

          astate->_draw_style->render_line(vector3<float>(0.0,  1.0, 0.0),
                                           vector3<float>(0.0,  0.0, 0.0),
                                           vector3<float>(0.0, 50.0, 0.0) );

          astate->_draw_style->render_line(vector3<float>(0.0,  0.0, 1.0),
                                           vector3<float>(0.0,  0.0, 0.0),
                                           vector3<float>(0.0, 0.0, 50.0) );
        }
    }

  for (ws_item* _ws_item : ws_items){
      _ws_item->render();
    }
}

ws_atom_list::ws_atom_list(){
  bPeriodicA = false;
  bPeriodicB = false;
  bPeriodicC = false;
  cell = new periodic_cell<float>(
  {1.0, 0.0, 0.0},
  {0.0, 1.0, 0.0},
  {0.0, 0.0, 1.0});
  geom = new geometry<float, periodic_cell<float> >(3);
}

void ws_atom_list::render(){
  app_state* astate = &(c_app::get_state());
  if (astate->_draw_style != NULL){
      for (int i = 0; i < geom->nat(); i++){
          int ap_idx = ptable::number_by_symbol(geom->atom(i));
          //std::cout << ap_idx << std::endl;
          vector3<float> color =
              ptable::get_instance()->arecs[ap_idx-1].aColorJmol;
          astate->_draw_style->render_atom(color,
                                           geom->pos(i),
                                           ptable::get_instance()->arecs[ap_idx-1].aRadius*0.35);
        }
      //      astate->_draw_style->render_bond(vector3<float>(1.0, 1.0, 1.0),
      //                                       p1+offset,
      //                                       p3+offset,
      //                                       0.2);

      //      astate->_draw_style->render_bond(vector3<float>(1.0, 1.0, 1.0),
      //                                       p2+offset,
      //                                       p3+offset,
      //                                       0.2);
    }
}

void ws_atom_list::render_ui(){
  if (ImGui::TreeNode("Atoms")){
      for (int i = 0; i < geom->nat(); i++)
        if (ImGui::TreeNode(fmt::format("{}:{}", geom->atom(i), i).c_str())){
            float _x = geom->pos(i)[0];
            float _y = geom->pos(i)[1];
            float _z = geom->pos(i)[2];
            ImGui::InputFloat("x", &_x);
            ImGui::InputFloat("y", &_y);
            ImGui::InputFloat("z", &_z);
            geom->coord(i) = vector3<float>(_x, _y, _z);
            ImGui::TreePop();
          }
      ImGui::TreePop();
    }
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

  workspace* _ws = new workspace();
  _ws->ws_items.push_back(_wsl);
  ws.push_back(_ws);
  iCurrentWorkSpace = ws.size() - 1;
}

void workspace_manager::render_current_workspace(){
  //std::cout<<"render_current_workspace"<<std::endl;
  if (ws.size() > 0)
    if ((iCurrentWorkSpace >= 0) && (iCurrentWorkSpace < ws.size()))
      ws[iCurrentWorkSpace]->render();
}
