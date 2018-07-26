#ifndef _QPP_MESH_H
#define _QPP_MESH_H
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <io/strfun.hpp>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace qpp{


  class mesh{
  public:
    GLuint vio;
    GLuint vbo;
    GLuint vao;
    mesh(){}

    virtual void render() = 0;
  };

  //unit sphere mesh
  class sphere_mesh : public mesh{
  public:
    unsigned int num_vertices;
    sphere_mesh(const float radius = 1.0f,
                const unsigned int num_azimut = 12,
                const unsigned int num_polar = 12);
    void render() override;
  };

  class test_triangle_mesh : public mesh{
  public:
    unsigned int num_vertices;
    test_triangle_mesh();
    void render() override;
  };
}
#endif
