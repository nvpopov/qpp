#ifndef QPP_WORKSPACE_ITEM_H
#define QPP_WORKSPACE_ITEM_H

#include <geom/lace3d.hpp>
#include <geom/aabb.hpp>
#include <geom/ray.hpp>
#include <vector>
#include <iostream>


namespace qpp{

  class ws_item {
    public:
      std::string name;
      aabb_3d<float> aabb;
      vector3<float> pos;
      ws_item();
      virtual void vote_for_view_vectors(vector3<float> &vOutLookPos,
                                         vector3<float> &vOutLookAt) = 0;
      virtual void render() = 0;
      virtual void render_ui() = 0;
      virtual void mouse_click(ray<float> *ray) = 0;
      virtual ~ws_item(){ }
  };

}

#endif
