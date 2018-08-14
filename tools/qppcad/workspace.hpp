#ifndef _QPP_WORKSPACE_H
#define _QPP_WORKSPACE_H

#include <geom/lace3d.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>
#include <vector>
#include <iostream>

namespace qpp{

  class workspace;
  class ws_item;

  enum ws_periodic {
    ws_periodic_a,
    ws_periodic_b,
    ws_periodic_c
  };

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
    std::string name;
    ws_item(){}
    virtual void render() = 0;
    virtual void render_ui() = 0;
  };

  class ws_atom_list : public ws_item {
  public:
    int iDim;
    bool bNeedToRebuildNBT;
    periodic_cell<float> *cell;
    xgeometry<float, periodic_cell<float> > *geom;
    bonding_table<float> *bt;
    neighbours_table<float> *nt;
    ws_atom_list();
    void render() override;
    void render_ui() override;
    void rebuild_ngbt();
  };

}

#endif
