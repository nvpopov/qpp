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
#include <geom/lace3d.hpp>

namespace qpp {

  enum app_task_type {
    TASK_WORKSPACE_EDITOR,
    TASK_NODE_EDITOR,
    TASK_MENDELEY_TABLE
  };

  enum app_camera_proj_type {
    CAMERA_PROJ_ORTHO,
    CAMERA_PROJ_PERSP
  };

  class app_state {
  public:
    draw_style* _draw_style;
    shader_program* def_shader;
    shader_program* unit_line_shader;
    shader_program* bond_shader;
    workspace_manager* _workspace_manager;
    ui_manager* _ui_manager;

    app_task_type cur_task;
    app_camera_proj_type cur_proj;
    // sphere mesh with differnet resolutions
    std::vector<mesh*> _sph_meshes;
    mesh* cylinder_mesh;
    mesh* unit_line;
    mesh* trm;

    int FPS;

    vector3<float> camPos;
    vector3<float> camLookAt;
    vector3<float> gUpAxis;

    matrix4<float> mView;
    matrix4<float> mProjection;
    matrix4<float> mViewProjection;
    matrix3<float> mViewInvTr;

    int wWidth;
    int wHeight;
    vector2<float> vViewportXY;
    vector2<float> vViewportWidthHeight;

    bool bRotateCamera;
    bool bMoveCamera;
    double MouseX;
    double MouseY;
    double MouseOldX;
    double MouseOldY;
    GLFWcursor* stdCursor;
    GLFWcursor* hndCursor;

    float fMouseWhellCameraStep;
    float fMinCameraDist;

    float fDistCamera;
    vector3<float> vViewDispl;

    vector3<float> vLigthPos;
    vector3<float> vLightColor;
    vector3<float> vLightPosTr;

    bool bDrawAxis;

    void reset_camera(){
      camPos = vector3<float>(0.0, 0.0, 4.5);
      camLookAt = vector3<float>(0.0, 0.0, 0.0);
      gUpAxis = vector3<float>(0.0, 1.0, 0.0);
      vViewDispl = vector3<float>(0.0, 0.0, 0.0);

      fDistCamera = 10.0f;
      fMouseWhellCameraStep = 0.1f;
      fMinCameraDist = 4.0f;
    }

    void update_mouse_coord(const double _mcx, const double _mcy){
      MouseX = _mcx; MouseY = _mcy;}

    void update_camera_dist(const double _dist){
      if ((fDistCamera + _dist * fMouseWhellCameraStep) > fMinCameraDist)
        fDistCamera += _dist;
    }

    void update_camera_translation(const bool _bMoveCamera){
      bMoveCamera = _bMoveCamera;
    }

    void update_camera_rotation(bool _bRotateCamera){
      bRotateCamera = _bRotateCamera; }

    /// Update application state
    void update(){

      double xDt = MouseX - MouseOldX;
      double yDt = MouseY - MouseOldY;

      MouseOldX = MouseX;
      MouseOldY = MouseY;

      if (bMoveCamera){
          float fMoveX = yDt/100;
          float fMoveY = xDt/100;
          vector3<float> camDir = (camPos-vViewDispl).normalized();
          vector3<float> camRight_t = gUpAxis.cross(camDir);
          vViewDispl += -camRight_t * fMoveY + vector3<float>(0,  fMoveX, 0.0);
        }

      if (bRotateCamera){
          float fRotAngleX = yDt/100;
          float fRotAngleY = xDt/100;

          vector3<float> newpos;
          vector3<float> camDir = (camPos-vViewDispl).normalized();
          vector3<float> camRight = gUpAxis.cross(camDir);

          Eigen::Quaternionf qrx, qry, qr;
          qrx = Eigen::AngleAxisf(fRotAngleX, camRight);
          qry = Eigen::AngleAxisf(fRotAngleY, gUpAxis);
          qr = qrx*qry;

          newpos = qr.toRotationMatrix() * (camPos-vViewDispl);
          camPos = newpos;
          camPos += vViewDispl;
        }

      camPos = camPos.normalized() * fDistCamera;
      camLookAt = vViewDispl;

      mView = look_at<float>(camPos, camLookAt, gUpAxis);

      if (cur_proj == app_camera_proj_type::CAMERA_PROJ_PERSP)
        mProjection = perspective<float>(60,
                                         vViewportWidthHeight(0) /
                                         vViewportWidthHeight(1),
                                         0.1, 100.0);
      else{
          float a = vViewportWidthHeight(0);
          a /= vViewportWidthHeight(1);
          float r = (camPos-vViewDispl).norm();
          if (a > 1.0)
            mProjection = ortho<float>(-r*a, r*a, -r, r, -100, 100);
          else
            mProjection = ortho<float>(-r, r, -r/a, r/a, -100, 100);
        }

      mViewProjection = mProjection *  mView ;
      mViewInvTr = mat4_to_mat3<float>((mView.transpose()).inverse());
      vLightPosTr = mat4_to_mat3<float>(mView) * vLigthPos;
    }

    /// Initialize app state
    app_state(){
      FPS = 60;

      cur_task = app_task_type::TASK_WORKSPACE_EDITOR;
      cur_proj = app_camera_proj_type::CAMERA_PROJ_PERSP;

      bRotateCamera = false;
      bMoveCamera = false;
      bDrawAxis = false;

      reset_camera();

      vLigthPos = vector3<float>(0, 25.0, 25.0);
      vLightPosTr = vector3<float>(0, 0, 0);
      _workspace_manager = new workspace_manager();
      wWidth  = 600;
      wHeight = 600;

      _draw_style = new default_draw_style();
      //unit sphere
      _sph_meshes.push_back(mesh::generate_sphere_mesh(15, 15));
      cylinder_mesh = mesh::generate_cylinder_whole(15, 4);
      unit_line = mesh::generate_unit_line();
      //trm = new test_triangle_mesh();
      def_shader = gen_default_program();
      unit_line_shader = gen_unit_line_program();
      bond_shader = gen_bond_draw_program();
      _workspace_manager->init_default_workspace();
      _ui_manager = new ui_manager();

      stdCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
      hndCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
    }

  };
}

#endif
