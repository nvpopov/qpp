#ifndef _QPP_WORKSPACE_H
#define _QPP_WORKSPACE_H

#include <geom/lace3d.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>
#include <geom/extents_observer.hpp>
#include <qppcad/camera.hpp>
#include <vector>
#include <iostream>
#include <geom/aux_rtree.hpp>

namespace qpp{

  class workspace;
  class ws_item;

  enum ws_periodic {
    ws_periodic_a,
    ws_periodic_b,
    ws_periodic_c
  };

  /// workspace manager
  class workspace_manager {
  public:
    int iCurrentWorkSpace;
    std::vector<workspace*> ws;

    workspace_manager(){ iCurrentWorkSpace = -1;}
    workspace* get_current_workspace();

    void init_default_workspace();
    void render_current_workspace();
  };

  /// workspace
  class workspace {
  public:
    std::vector<ws_item*> ws_items;
    std::string ws_name;
    camera* ws_cam;
    bool bFirstRender;

    workspace(std::string _ws_name = "default"){
      ws_name = _ws_name;
      bFirstRender = true;
      ws_cam = new camera();
      ws_cam->reset_camera();
    }

    void reset_camera();
    void set_best_view();
    void render();
  };

  class ws_item {
  public:
    std::string name;
    ws_item(){}
    virtual void vote_for_view_vectors(vector3<float> &vOutLookPos,
                                       vector3<float> &vOutLookAt) = 0;
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
    aux_rtree<float, periodic_cell<float> > *rtree;
    extents_observer<float, periodic_cell<float> > *ext_obs;

    ws_atom_list();

    void vote_for_view_vectors(vector3<float> &vOutLookPos,
                               vector3<float> &vOutLookAt) override ;
    void render() override;
    void render_ui() override;
    void rebuild_ngbt();
  };

}

#endif
