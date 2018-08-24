#include <qppcad/ws_item.hpp>
#include <qppcad/app.hpp>
#include <data/color.hpp>
#include <qppcad/workspace.hpp>

using namespace qpp;

ws_item::ws_item(){
  vPosition = vector3<float>(0.0f, 0.0f, 0.0f);
  vScale    = vector3<float>(1.0f, 1.0f, 1.0f);
  vRotation = vector3<float>(0.0f, 0.0f, 0.0f);
  bSelected = false;
}

void ws_item::set_parent_workspace(workspace *_parent_ws){
  parent_ws = _parent_ws;
}

void ws_item::render(){
  app_state* astate = &(c_app::get_state());

  if (astate->_draw_pipeline != nullptr){
      if (bSelected && support_selection()){
          astate->_draw_pipeline->begin_render_aabb();
          if (parent_ws->cur_edit_type == ws_edit_type::EDIT_WS_ITEM)
            astate->_draw_pipeline->render_aabb(clr_fuchsia, aabb.min, aabb.max );
          else
            astate->_draw_pipeline->render_aabb_segmented(clr_olive, aabb.min, aabb.max );
          astate->_draw_pipeline->end_render_aabb();
        }
    }

}

void ws_item::update(){

}
