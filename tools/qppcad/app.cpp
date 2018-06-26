#include <qppcad/app.hpp>

static const GLfloat g_vertex_buffer_data[] = {
  -1.0f, -1.0f, 0.0f,
  1.0f, -1.0f, 0.0f,
  0.0f,  1.0f, 0.0f,
};

GLuint vertexbuffer;

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
  if (gl3wInit()) {
      fprintf(stderr, "failed to initialize OpenGL\n");
    }

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
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

  while (!glfwWindowShouldClose(qpp::cad_app::curWindow)){

      qpp::cad_app::begin_render();
      qpp::cad_app::render();
      qpp::cad_app::end_render();

    }

  glfwDestroyWindow(qpp::cad_app::curWindow);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

void qpp::cad_app::begin_render(){

  glfwPollEvents();
  glfwMakeContextCurrent(qpp::cad_app::curWindow);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  qpp::cad_app::compose_ui();

  float ratio;
  int width, height;
  glfwGetFramebufferSize(qpp::cad_app::curWindow, &width, &height);

  ratio = width / (float) height;
  glViewport(0, 0, width, height);

  glClearColor(0.8, 0.8, 0.8, 0.8);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void qpp::cad_app::end_render(){

  glfwSwapBuffers(qpp::cad_app::curWindow);

}

void qpp::cad_app::render(){
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void qpp::cad_app::compose_ui(){
  qpp::cad_app::compose_ui_menu();
}

void qpp::cad_app::compose_ui_menu(){
  if (ImGui::BeginMainMenuBar()){
      if (ImGui::BeginMenu("File")){
          ImGui::MenuItem("New");
          ImGui::MenuItem("Open");
          ImGui::MenuItem("Save");
          ImGui::MenuItem("Save as");
          ImGui::MenuItem("Exit");
          ImGui::EndMenu();
        }


      if (ImGui::BeginMenu("Edit")){
          ImGui::MenuItem("Undo");
          ImGui::MenuItem("Redo");
          ImGui::EndMenu();
        }

      if (ImGui::BeginMenu("Tools")){
          ImGui::MenuItem("Tool1");
          ImGui::MenuItem("Tool2");
          ImGui::EndMenu();
        }

      if (ImGui::BeginMenu("Help")){
          ImGui::MenuItem("Help1");
          ImGui::MenuItem("Help2");
          ImGui::EndMenu();
        }

      ImGui::EndMainMenuBar();

    }
}

GLFWwindow* qpp::cad_app::curWindow;
