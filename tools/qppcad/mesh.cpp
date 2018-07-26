#include <qppcad/mesh.hpp>

using namespace qpp;

sphere_mesh::sphere_mesh(const float radius,
                         const unsigned int num_azimut,
                         const unsigned int num_polar){

  //  if (vio != 0) glDeleteBuffers(1, &(this->vio));
  //  if (vbo != 0) glDeleteBuffers(1, &(this->vbo));

  std::vector<float> vertexData;
  std::vector<int> indicesData;

  unsigned int total_segs = num_azimut * num_polar;

  float azimut_step = (2.0f * float(qpp::pi)) / float(num_azimut);
  float polar_step = float(qpp::pi) / float(num_polar);

  float r = 1.0f;
  num_vertices = 0;

  for (unsigned int m = 0; m < num_azimut; m++)
    for (unsigned int n = 0; n < num_polar; n++){
        float phi = azimut_step * m;
        float theta = polar_step * n;

        float x = r * sin(theta) * cos(phi);
        float y = r * sin(theta) * sin(phi);
        float z = r * cos(theta);

        vertexData.push_back(x);
        vertexData.push_back(y);
        vertexData.push_back(z);

        indicesData.push_back(num_vertices % total_segs);
        indicesData.push_back((num_vertices + num_azimut) % total_segs);
        indicesData.push_back((num_vertices + num_azimut + 1) %
                              total_segs);
        indicesData.push_back((num_vertices + 1) % total_segs);

        num_vertices++;
      }

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,
               vertexData.size()*sizeof(float),
               &vertexData[0],GL_STATIC_DRAW);


  glGenBuffers(1, &vio);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               indicesData.size()*sizeof(int),
               &indicesData[0], GL_STATIC_DRAW);

}

void sphere_mesh::render(){

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        num_vertices*3*sizeof(GL_FLOAT),
                        BUFFER_OFFSET(0));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio);
  glDrawElements(GL_QUADS, num_vertices*4, GL_UNSIGNED_INT, NULL);
  glDisableVertexAttribArray(0);

}

test_triangle_mesh::test_triangle_mesh(){

  static const GLfloat g_vertex_buffer_data[] = {
    -0.8f, -0.8f, 0.0f,
     0.8f, -0.8f, 0.0f,
     0.0f,  0.8f, 0.0f,
  };

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat),
               &g_vertex_buffer_data[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

void test_triangle_mesh::render(){

  glBindVertexArray(vao);

  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);

}
