#include <qppcad/shader_program.hpp>

qpp::shader_program::shader_program(){

}

qpp::shader_program::shader_program(const std::string &_vs_text,
                                    const std::string &_fs_text){
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  programID = glCreateProgram();

  GLint proc_res = GL_FALSE;
  int infoLogLength = 0;

  const char *_vs_text_c = _vs_text.c_str();
  const char *_fs_text_c = _fs_text.c_str();

  glShaderSource(vertexShaderID, 1, &_vs_text_c, NULL);
  glCompileShader(vertexShaderID);
  glShaderSource(fragmentShaderID, 1, &_fs_text_c, NULL);
  glCompileShader(fragmentShaderID);
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  glLinkProgram(programID);

  glGetProgramiv(programID, GL_LINK_STATUS, &proc_res);
  glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
  //TODO: log this

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);

}

qpp::shader_program* qpp::gen_default_program(){
  std::string vs =" #version 140"
      "in  vec3 in_Position;"
      "in  vec3 in_Color;"
      "out vec3 ex_Color;"
      ""
      "void main(void)"
      "{"
      "       gl_Position = vec4(in_Position, 1.0);"
      "       ex_Color = in_Color;"
      "}";

  std::string ps =
     " #version 140"
      "precision highp float;"
      "in  vec3 ex_Color;"
      "out vec4 out_Color;"
      "void main(void)"
      "{"
      "        out_Color = vec4(ex_Color,1.0);"
      "}";

  return new qpp::shader_program(vs, ps);
}
