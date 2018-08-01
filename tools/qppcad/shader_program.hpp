#ifndef _QPP_SHADER_PROGRAM_H
#define _QPP_SHADER_PROGRAM_H
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>

namespace qpp {
  class shader_program{
  private:
    GLuint programID;
  public:
    GLint uiUnfColor;
    GLint uiUnfTrans;
    GLint uiUnfModelViewProj;
    GLint uiUnfViewProj;

    bool bUnfColor;
    bool bUnfTrans;
    bool bUnfModelMat;
    bool bUnfViewMat;
    bool bUnfModelViewMat;
    bool bUnfViewProjMat;
    bool bUnfModelViewProjMat;

    std::string programName;

    shader_program();

    shader_program(const std::string _programName,
                   const std::string &_vs_text,
                   const std::string &_fs_text,
                   bool _bUColor = false,
                   bool _bUTrans = false,
                   bool _bUViewProjMat = true,
                   bool _bUModelViewProjMat = false);

    void begin_shader_program();
    void end_shader_program();
  };

  shader_program* gen_default_program();
}
#endif


