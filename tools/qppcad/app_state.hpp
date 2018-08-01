#ifndef _QPP_APP_STATE_H
#define _QPP_APP_STATE_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>
#include <qppcad/draw_style.hpp>
#include <qppcad/workspace.hpp>
#include <qppcad/mesh.hpp>
#include <qppcad/shader_program.hpp>
#include <qppcad/ui_manager.hpp>
#include <qppcad/gl_math.hpp>

namespace qpp {

  class app_state {
  public:
    draw_style* _draw_style;
    shader_program* def_shader;

    workspace_manager* _workspace_manager;
    ui_manager* _ui_manager;

    // sphere mesh with differnet resolutions
    std::vector<mesh*> _sph_meshes;
    mesh* trm;

    vector3<float> camPos;
    vector3<float> camLookAt;
    vector3<float> gUpAxis;

    matrix4<float> mView;
    matrix4<float> mProjection;
    matrix4<float> mViewProjection;

    int wWidth;
    int wHeight;

    bool bRotateCamera;
    double MouseX;
    double MouseY;
    double MouseOldX;
    double MouseOldY;

    float fMouseWhellCameraStep;
    float fMinCameraDist;
    float fRotAngleX, fRotAngleY;
    float fDistCamera;
    vector3<float> vViewDispl;


    void update_mouse_coord(const double _mcx, const double _mcy){
      MouseX = _mcx; MouseY = _mcy;}

    void update_camera_dist(const double _dist){
      if ((fDistCamera + _dist * fMouseWhellCameraStep) > fMinCameraDist)
        fDistCamera += _dist;
    }

    void update_camera_rotation(bool _bRotateCamera){
      bRotateCamera = _bRotateCamera; }

    void update(){


      mView = look_at<float>(camPos, camLookAt, gUpAxis);
      mProjection = perspective<float>(70, wWidth/wHeight, 0.1, 100.0);
      mViewProjection = mProjection *  mView ;
      //std::cout<<mViewProjection<<std::endl<<std::endl;

      double xDt = MouseX - MouseOldX;
      double yDt = MouseY - MouseOldY;

      MouseOldX = MouseX;
      MouseOldY = MouseY;

      if (bRotateCamera){
          fRotAngleX += yDt/100;
          fRotAngleY += xDt/100;
        }
      Eigen::Quaternion<float> q_rx;
      q_rx = Eigen::AngleAxisf(fRotAngleX, vector3<float>(1.0, 0.0, 0.0));

      Eigen::Quaternion<float> q_ry;
      q_ry = Eigen::AngleAxisf(fRotAngleY, vector3<float>(0.0, 1.0, 0.0));

      camLookAt = vViewDispl;
      vector3<float> newCamPos =
          q_ry.toRotationMatrix() *
          q_rx.toRotationMatrix() *
          vector3<float>(0.0, 0.0, fDistCamera);
      camPos = newCamPos + camLookAt;


    }

    app_state(){

      camPos = vector3<float>(0.0, 0.0, 4.5);
      camLookAt = vector3<float>(0.0, 0.0, -3.5);
      gUpAxis = vector3<float>(0.0, 1.0, 0.0);
      vViewDispl = vector3<float>(0.0, 0.0, 0.0);
      fRotAngleX = 0.0f;
      fRotAngleY = 0.0f;
      fDistCamera = 10.0f;
      fMouseWhellCameraStep = 0.1f;
      fMinCameraDist = 4.0f;

      _workspace_manager = new workspace_manager();
      wWidth  = 600;
      wHeight = 600;

      _draw_style = new default_draw_style();
      //unit sphere
      _sph_meshes.push_back(new sphere_mesh(1.0, 12, 12));
      trm = new test_triangle_mesh();
      def_shader = gen_default_program();

      _workspace_manager->init_default_workspace();
      _ui_manager = new ui_manager();
    }

  };
}

#endif
