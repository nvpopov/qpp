#include <qppcad/app.hpp>


void qpp::cad_app::error_callback(int error, const char* description){
  std::cout << description << std::endl;
}

void qpp::cad_app::key_callback(GLFWwindow* window,
                                int key, int scancode, int action, int mods){
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void qpp::cad_app::run(){

  glfwSetErrorCallback(qpp::cad_app::error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  qpp::cad_app::curWindow = glfwCreateWindow(640, 480, "qpp::cad", NULL, NULL);

  if (!qpp::cad_app::curWindow){
      glfwTerminate();
      exit(EXIT_FAILURE);
    }

  glfwMakeContextCurrent(qpp::cad_app::curWindow);
  glfwSwapInterval(1);
  gl3wInit();


  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.Fonts->AddFontDefault();
  io.Fonts->Build();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(qpp::cad_app::curWindow, true);
  ImGui_ImplOpenGL3_Init();
  glfwSetKeyCallback(qpp::cad_app::curWindow, qpp::cad_app::key_callback);

  //glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(qpp::cad_app::curWindow)){

      qpp::cad_app::begin_render();
      qpp::cad_app::render();
      qpp::cad_app::render_ui();
      qpp::cad_app::end_render();

    }

  glfwDestroyWindow(qpp::cad_app::curWindow);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

void qpp::cad_app::app_cycle(){


}

void qpp::cad_app::begin_render(){

  float ratio;
  int width, height;
  glfwGetFramebufferSize(qpp::cad_app::curWindow, &width, &height);

  ratio = width / (float) height;
  glViewport(0, 0, width, height);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void qpp::cad_app::end_render(){
  ImGui::Render();
  glfwSwapBuffers(qpp::cad_app::curWindow);
  glfwPollEvents();
}

void qpp::cad_app::render(){

}

void qpp::cad_app::render_ui(){
  ImGui::Begin("Another Window");
  ImGui::Text("retsts");
  ImGui::End();

}

GLFWwindow* qpp::cad_app::curWindow;
