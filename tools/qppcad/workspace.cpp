#include <qppcad/workspace.hpp>
#include <qppcad/app.hpp>
using namespace qpp;

void workspace::render(){
  for (ws_item* _ws_item : ws_items){
        _ws_item->render();
    }
}

void ws_atom_list::render(){
  app_state* astate = &(c_app::get_state());
  if (astate->_draw_style != NULL){
      astate->_draw_style->render_atom(vector3<float>(1.0, 1.0, 1.0),
                                       vector3<float>(0.0, 0.0, 0.0));
    }
}

void workspace_manager::init_default_workspace(){
  ws_atom_list* _wsl = new ws_atom_list();
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
