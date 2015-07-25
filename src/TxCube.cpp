#include "TxCube.h"
#define USE_STRIPES

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

  glGenBuffers(1, &vbo);                                                                      assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                                                         assert(!glGetError());
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);  assert(!glGetError());

#ifdef USE_STRIPES
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
#else
  GLushort indexBufferData[36] =
  {
    // left
    0, 1, 2,
    2,1,3,
    // right
    4, 6, 5,
    5,6,7,
    // front
    8, 9, 10,
    10,9,11,
    // back
    12, 14, 13,
    13,14,15,
    // top
    16, 17, 18,
    18,17,19,
    // bottom
    20, 22, 21,
    21,22,23
  };
#endif
  glGenBuffers(1, &indexBufferId);                                                                  assert(!glGetError());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);                                             assert(!glGetError());
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBufferData), indexBufferData, GL_STATIC_DRAW);  assert(!glGetError());

  GLfloat uvBufferData[24 * 2] =
  {
    // left face
    0, 0,
    0.333f, 0,
    0, 0.5f,
    0.333f, 0.5f,
    // right face
    0, 0.5f,
    0.333f, 0.5f,
    0, 1,
    0.333f, 1,

    // front face
    0.333f, 0,
    0.666f, 0,
    0.333f, 0.5f,
    0.666f, 0.5f,
    // back face
    0.333f, 0.5f,
    0.666f, 0.5f,
    0.333f, 1,
    0.666f, 1,

    // top face
    0.666f, 0,
    1, 0,
    0.666f, 0.5f,
    1, 0.5f,
    // bottom face
    0.666f, 0.5,
    1, 0.5,
    0.666f, 1,
    1, 1,
  };

  glGenBuffers(1, &uvBufferId);                                                       assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);                                          assert(!glGetError());
  glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData, GL_STATIC_DRAW);  assert(!glGetError());

  texture.loadFromFile((Crosy::getExePath() + "/textures/rubik.DDS").c_str());
  assert(texture.id);
}


TxCube::~TxCube()
{
}

void TxCube::draw()
{
  glEnableVertexAttribArray(0);                                     assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, vbo);                               assert(!glGetError());
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);     assert(!glGetError());

  glEnableVertexAttribArray(1);                                     assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);                        assert(!glGetError());
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);     assert(!glGetError());

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);             assert(!glGetError());
//  for (int n = 0; n < 100000; n++)
  {
#ifdef USE_STRIPES
    for (GLshort * ptr = 0; ptr < (GLshort *)0 + 24; ptr += 4)
    {
      glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (void*)ptr);
      assert(!glGetError());
    }
//    glDrawElements(GL_TRIANGLE_STRIP, 24, GL_UNSIGNED_SHORT, (void*)0);
#else
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)0);
#endif
  }
  glDisableVertexAttribArray(0);    assert(!glGetError());
  glDisableVertexAttribArray(1);    assert(!glGetError());
}
