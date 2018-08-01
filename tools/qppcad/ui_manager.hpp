#ifndef _QPP_UI_MANAGER_H
#define _QPP_UI_MANAGER_H
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace qpp{
  class ui_manager{
  public:
    ui_manager();
    void render_ui();
    void render_main_menu();
    void render_object_inspector();
  };
}
#endif
