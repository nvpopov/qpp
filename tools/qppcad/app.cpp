#include <qppcad/app.hpp>

void
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

void qpp::c_app::error_callback(int error, const char* description){
  std::string s1(description);
  qpp::c_app::log(s1);
}

void qpp::c_app::key_callback(GLFWwindow* window,
                              int key, int scancode, int action, int mods){
  qpp::c_app::log(fmt::format("Key pressed  {}, scancode = {}", key, scancode));

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void qpp::c_app::run(){

  glfwSetErrorCallback(qpp::c_app::error_callback);

  if (!glfwInit()){
      qpp::c_app::log("Failed to initialize GLFW3");
      exit(EXIT_FAILURE);
    }

  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  qpp::c_app::curWindow = glfwCreateWindow(800,
                                           600,
                                           "qpp::cad", NULL, NULL);

  if (!qpp::c_app::curWindow){
      glfwTerminate();
      qpp::c_app::log("Failed to initialize window");
      exit(EXIT_FAILURE);
    }

  glfwMakeContextCurrent(qpp::c_app::curWindow);
  glfwSwapInterval(1);
  if (gl3wInit()) {
      qpp::c_app::log("Failed  to initialize OpenGL");
    }

  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.Fonts->AddFontDefault();
  io.Fonts->Build();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark();

  glEnable              ( GL_DEBUG_OUTPUT );
  glDebugMessageCallback( MessageCallback, 0 );
  ImGui_ImplGlfw_InitForOpenGL(qpp::c_app::curWindow, true);
  ImGui_ImplOpenGL3_Init();

  glfwSetScrollCallback(qpp::c_app::curWindow, qpp::c_app::mouse_scroll_callback);
  glfwSetKeyCallback(qpp::c_app::curWindow, qpp::c_app::key_callback);
  glfwSetWindowSizeCallback(qpp::c_app::curWindow,
                            qpp::c_app::resize_window_callback);
  glfwSetMouseButtonCallback(qpp::c_app::curWindow,
                             qpp::c_app::mouse_button_callback);
  glfwSetCursorPosCallback(qpp::c_app::curWindow,
                           qpp::c_app::mouse_callback);

  qpp::c_app::log("qpp::cad initialized succesfully!");
  app_state* astate = &(c_app::get_state());

  while (!glfwWindowShouldClose(qpp::c_app::curWindow)){

      qpp::c_app::get_state().update();
      qpp::c_app::begin_render();
      qpp::c_app::render();
      qpp::c_app::end_render();

      glfwPollEvents();
    }

  glfwDestroyWindow(qpp::c_app::curWindow);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

void qpp::c_app::begin_render(){


  glfwMakeContextCurrent(qpp::c_app::curWindow);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  qpp::c_app::get_state()._ui_manager->render_ui();

  float ratio;
  int width, height;
  glfwGetFramebufferSize(qpp::c_app::curWindow, &width, &height);

  ratio = width / (float) height;
  glViewport(0, 0, width, height);


  glDepthFunc(GL_LESS);

  glClearColor(0.4, 0.4, 0.4, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void qpp::c_app::end_render(){
  glfwSwapBuffers(qpp::c_app::curWindow);
}

void qpp::c_app::render(){
  app_state* astate = &(c_app::get_state());
  astate->_workspace_manager->render_current_workspace();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void qpp::c_app::resize_window_callback(GLFWwindow *window,
                                        int _width, int _height){
  qpp::c_app::get_state().wWidth = _width;
  qpp::c_app::get_state().wHeight = _height;
}

void qpp::c_app::mouse_scroll_callback(GLFWwindow *window,
                                       double xoffset, double yoffset){
  app_state* astate =  &(c_app::get_state());
  astate->update_camera_dist(-yoffset);
}

void qpp::c_app::mouse_callback(GLFWwindow *window, double x, double y){
  std::cout<<x<<" "<<y<<std::endl;
  qpp::c_app::get_state().update_mouse_coord(x, y);
}

void qpp::c_app::mouse_button_callback(GLFWwindow *window,
                                       int button,
                                       int action,
                                       int mods){
  bool _bUpdateCameraRotation = false;
  _bUpdateCameraRotation =
      (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS);

   qpp::c_app::get_state().update_camera_rotation(_bUpdateCameraRotation);
}

void qpp::c_app::log(const std::string logText){

  std::time_t t = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
  std::string ts( ctime( &t) );
  std::cout << fmt::format("[{}] {}",
                           ts.substr( 0, ts.length() -1  ), logText) << std::endl;
}

GLFWwindow* qpp::c_app::curWindow;
qpp::app_state* qpp::c_app::a_state;
