#include <qppcad/shader_program.hpp>
#include <qppcad/app.hpp>

qpp::shader_program::shader_program(){

}

qpp::shader_program::shader_program(const std::string _programName,
                                    const std::string &_vs_text,
                                    const std::string &_fs_text,
                                    bool _bUniformColor,
                                    bool _bUniformTrVec){

  programName = _programName;
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  programID = glCreateProgram();

  GLint proc_res = GL_FALSE;
  GLint vs_proc_res = GL_FALSE;
  GLint fs_proc_res = GL_FALSE;

  int infoLogLength = 0;

  const char *_vs_text_c = _vs_text.c_str();
  const char *_fs_text_c = _fs_text.c_str();

  glShaderSource(vertexShaderID, 1, &_vs_text_c, NULL);
  glCompileShader(vertexShaderID);
  glShaderSource(fragmentShaderID, 1, &_fs_text_c, NULL);
  glCompileShader(fragmentShaderID);

  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vs_proc_res);
  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &fs_proc_res);

  c_app::log(fmt::format("Program[{}] vs_sh_stat = {}, fs_sh_stat = {}",
                         programName, vs_proc_res, fs_proc_res));
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glBindAttribLocation(programID, 0, "in_Position");

  glLinkProgram(programID);

  glGetProgramiv(programID, GL_LINK_STATUS, &proc_res);
  glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

  c_app::log("Shader program["+programName+"] compilation status:" +
             std::to_string(proc_res));

  if (infoLogLength > 0){
      c_app::log("Shader/Program compilation/linking failed:");
      std::vector<char> ProgramErrorMessage(infoLogLength+1);
      glGetProgramInfoLog(programID, infoLogLength, NULL, &ProgramErrorMessage[0]);
      std::string str(ProgramErrorMessage.begin(), ProgramErrorMessage.end());
      c_app::log(str);
    }


  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

  bUniformColor = _bUniformColor;
  bUniformTrVec = _bUniformTrVec;

  if(bUniformColor) uiUniformColor = glGetUniformLocation(programID, "uColor");
  if(bUniformTrVec) uiUniformTrVec = glGetUniformLocation(programID, "uTrVec");

}

void qpp::shader_program::begin_shader_program(){
  glUseProgram(programID);
}

void qpp::shader_program::end_shader_program(){
  glUseProgram(0);
}

qpp::shader_program* qpp::gen_default_program(){
  std::string vs =
      "#version 330\n"
      "in vec3 in_Position;\n"
      "out vec4 ex_Color;\n"
      "\n"
      "void main(void)\n"
      "{\n"
      "       gl_Position = vec4(in_Position, 1.0);\n"
      "       ex_Color = vec4(0.0, 1.0, 1.0, 1.0);\n"
      "}";

  std::string fs =
      "#version 330\n"
      "in  vec4 ex_Color;\n"
      "out vec4 out_Color;\n"
      "void main(void)\n"
      "{\n"
      "        out_Color = vec4(ex_Color);\n"
      "}\n";

  return new qpp::shader_program(std::string("default_program"), vs, fs);
}
