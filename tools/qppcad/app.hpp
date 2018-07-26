#ifndef _QPP_CAD_H
#define _QPP_CAD_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <qppcad/app_state.hpp>
#include <qppcad/gl_math.hpp>
#include <chrono>
#include <ctime>

namespace qpp{
  class c_app{

  private:
    static app_state* a_state;
    static GLFWwindow* curWindow;

    static void error_callback(int error, const char* description);

    static void key_callback(GLFWwindow* window,
                             int key,
                             int scancode,
                             int action,
                             int mods);

    static void resize_window_callback(GLFWwindow* window,
                                       int _width,
                                       int _height);
    static void begin_render();
    static void render();
    static void compose_ui();
    static void compose_ui_menu();
    static void compose_io_object_inspector();
    static void end_render();


  public:
    static void log(const std::string logText);
    static void run();
    static app_state & get_state(){
      if (c_app::a_state == NULL)
        c_app::a_state = new qpp::app_state();
      return *a_state;
    }
  };
}
#endif