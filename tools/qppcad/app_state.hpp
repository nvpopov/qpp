#ifndef _QPP_APP_STATE_H
#define _QPP_APP_STATE_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include <imgui.h>
#include <mathf/math.hpp>
#include <qppcad/draw_style.hpp>
#include <qppcad/workspace.hpp>
#include <qppcad/mesh.hpp>
#include <qppcad/shader_program.hpp>
#include <qppcad/ui_manager.hpp>
#include <qppcad/gl_math.hpp>
#include <qppcad/camera.hpp>
#include <geom/lace3d.hpp>

namespace qpp {

  enum app_task_type {
    TASK_WORKSPACE_EDITOR,
    TASK_NODE_EDITOR,
    TASK_MENDELEY_TABLE
  };

  class app_state {
  public:
    draw_style* _draw_style;
    shader_program* def_shader;
    shader_program* unit_line_shader;
    shader_program* bond_shader;
    shader_program* shaderLineMesh;
    workspace_manager* _workspace_manager;
    ui_manager* _ui_manager;
    camera* _camera;

    double MouseX;
    double MouseY;
    double MouseOldX;
    double MouseOldY;

    app_task_type cur_task;
    // sphere mesh with differnet resolutions
    std::vector<mesh*> _sph_meshes;
    mesh* cylinder_mesh;
    mesh* unit_line;
    mesh* trm;
    mesh* gridXZ;

    int FPS;

    int wWidth;
    int wHeight;

    vector2<float> vViewportXY;
    vector2<float> vViewportWidthHeight;

    vector3<float> vLigthPos;
    vector3<float> vLightColor;
    vector3<float> vLightPosTr;

    bool bDrawAxis;

    void update_mouse_coord(const double _mcx, const double _mcy){
      MouseX = _mcx; MouseY = _mcy;}

    /// Update application state
    void update(){
      _camera->update_camera();
      vLightPosTr = mat4_to_mat3<float>(_camera->mView) * vLigthPos;
    }

    /// Initialize app state
    app_state(){

      FPS = 60;
      cur_task = app_task_type::TASK_WORKSPACE_EDITOR;
      bDrawAxis = true;

      vLigthPos = vector3<float>(0, 25.0, 25.0);
      vLightPosTr = vector3<float>(0, 0, 0);
      _workspace_manager = new workspace_manager();
      wWidth  = 600;
      wHeight = 600;

      _camera = new camera();
      _camera->reset_camera();

      _draw_style = new default_draw_style();

      //default meshes
      _sph_meshes.push_back(mesh::generate_sphere_mesh(15, 15));
      cylinder_mesh = mesh::generate_cylinder_whole(15, 4);
      unit_line = mesh::generate_unit_line();
      gridXZ = mesh::generate_xz_plane(20, 0.5, 20, 0.5);
      def_shader = gen_default_program();
      unit_line_shader = gen_unit_line_program();
      bond_shader = gen_bond_draw_program();
      shaderLineMesh = gen_line_mesh_program();
      _workspace_manager->init_default_workspace();
      _ui_manager = new ui_manager();
    }

  };
}

#endif
