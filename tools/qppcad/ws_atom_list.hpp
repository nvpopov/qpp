#ifndef QPP_WS_ATOM_LIST_H
#define QPP_WS_ATOM_LIST_H

#include <geom/lace3d.hpp>
#include <geom/geom.hpp>
#include <geom/xgeom.hpp>
#include <geom/ngbr.hpp>
#include <geom/extents_observer.hpp>
#include <qppcad/camera.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <geom/tws_tree.hpp>
#include <qppcad/ws_item.hpp>

namespace qpp{

  class ws_atom_list : public ws_item {
    public:
      int iDim;
      bool bNeedToRebuildNBT;
      periodic_cell<float> *cell;
      xgeometry<float, periodic_cell<float> > *geom;
      bonding_table<float> *bt;
      neighbours_table<float> *nt;
      tws_tree<float, periodic_cell<float> > *tws_tr;
      extents_observer<float, periodic_cell<float> > *ext_obs;

      ws_atom_list();

      void vote_for_view_vectors(vector3<float> &vOutLookPos,
                                 vector3<float> &vOutLookAt) override ;
      void render() override;
      void render_ui() override;
      void mouse_click(ray<float> *ray) override;

      void rebuild_ngbt();

      ~ws_atom_list() override {

      }

  };

}

#endif
