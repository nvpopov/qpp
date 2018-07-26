#ifndef _QPP_WORKSPACE_H
#define _QPP_WORKSPACE_H

#include <geom/lace3d.hpp>
#include <vector>
#include <iostream>

namespace qpp{

  class workspace;
  class ws_item;

  class workspace_manager {
  public:
    int iCurrentWorkSpace;
    std::vector<workspace*> ws;

    workspace_manager(){ iCurrentWorkSpace = -1;}
    void init_default_workspace();
    void render_current_workspace();
  };

  class workspace {
  public:
    std::vector<ws_item*> ws_items;
    std::string ws_name;
    workspace(std::string _ws_name = "default"){ ws_name = _ws_name;}
    void render();
  };

  class ws_item {
  public:
    vector3<float> pos;
    ws_item(){ pos = vector3<float>::Zero();}
    virtual void render() = 0;
  };

  class ws_atom_list : public ws_item {
  public:
    ws_atom_list(){}
    void render() override;
  };

}

#endif
