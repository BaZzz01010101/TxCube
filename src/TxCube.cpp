#include "TxCube.h"

TxCube::TxCube(GLfloat size) : 
  GxObject()
{
  const GLfloat a = size * 0.5f;

  GLfloat vertexBufferData[24 * 3] =
  {
    // left face
    -a, -a, -a,
    -a, a, -a,
    -a, -a, a,
    -a, a, a,
    // right face
    a, -a, -a,
    a, a, -a,
    a, -a, a,
    a, a, a,
    // front face
    -a, -a, -a,
    a, -a, -a,
    -a, a, -a,
    a, a, -a,
    // back face
    -a, -a, a,
    a, -a, a,
    -a, a, a,
    a, a, a,
    // top face
    -a, a, -a,
    a, a, -a,
    -a, a, a,
    a, a, a,
    // bottom face
    -a, -a, -a,
    a, -a, -a,
    -a, -a, a,
    a, -a, a,
  };

  glGenBuffers(1, &vbo);
  assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  assert(!glGetError());
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
  assert(!glGetError());

  GLushort indexBufferData[24] =
  {
    // left
    0, 1, 2, 3,
    // right
    4, 6, 5, 7,
    // front
    8, 9, 10, 11,
    // back
    12, 14, 13, 15,
    // top
    16, 17, 18, 19,
    // bottom
    20, 22, 21, 23
  };

  glGenBuffers(1, &indexBuffer);
  assert(!glGetError());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  assert(!glGetError());
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBufferData), indexBufferData, GL_STATIC_DRAW);
  assert(!glGetError());
}


TxCube::~TxCube()
{
}

void TxCube::draw()
{
  glEnableVertexAttribArray(0);                                     assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                               assert(!glGetError());
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);     assert(!glGetError());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);               assert(!glGetError());

  for (int i = 0; i < 24 * sizeof(GLshort); i += 4 * sizeof(GLshort))
  {
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (void*)i);  
    assert(!glGetError());
  }

  glDisableVertexAttribArray(0);
  assert(!glGetError());
}
