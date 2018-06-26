#ifndef _QPP_CAD_H
#define _QPP_CAD_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
namespace qpp{
  class cad_app{
  private:
    static GLFWwindow* curWindow;
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window,
                             int key, int scancode, int action, int mods);
    static void begin_render();
    static void render();
    static void compose_ui();
    static void compose_ui_menu();
    static void end_render();
  public:
    static void run();
  };
}
#endif
