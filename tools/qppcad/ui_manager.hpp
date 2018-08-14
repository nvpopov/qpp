#ifndef _QPP_UI_MANAGER_H
#define _QPP_UI_MANAGER_H
#pragma GCC diagnostic ignored "-Wformat-security"
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <io/strfun.hpp>
#include <cstdlib>

namespace qpp{
  class ui_manager{
  public:
    int iWorkPanelHeight;
    int iWorkPanelYOffset;
    int iObjInspWidth;
    ui_manager();
    void render_ui();
    void render_main_menu();
    void render_work_panel();
    void render_task_panel();
    void render_ws_tabs();
    void render_object_inspector();
    void render_mtable_big();
  };
}
#endif
