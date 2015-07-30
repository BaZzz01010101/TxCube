#include "TxCube.h"
#define USE_STRIPES

TxCube::TxCube(GLfloat size) :
  GxObject()
{
  texture.loadFromFile((Crosy::getExePath() + "/textures/rubik.DDS").c_str());
  assert(texture.id);

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

  glGenBuffers(1, &vertexBufferId);                                                               assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);                                                  assert(!glGetError());
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);      assert(!glGetError());

  GLfloat uvBufferData[24 * 2] =
  {
    // left face
    0.0f,       0.0f,
    1.0f / 3,   0.0f,
    0.0f,       0.5f,
    1.0f / 3,   0.5f,
    // right face
    0.0f,       0.5f,
    1.0f / 3,   0.5f,
    0.0f,       1.0f,
    1.0f / 3,   1.0f,

    // front face
    1.0f / 3,   0.0f,
    2.0f / 3,   0.0f,
    1.0f / 3,   0.5f,
    2.0f / 3,   0.5f,
    // back face
    1.0f / 3,   0.5f,
    2.0f / 3,   0.5f,
    1.0f / 3,   1.0f,
    2.0f / 3,   1.0f,

    // top face
    2.0f / 3,   0.0f,
    1.0f,       0.0f,
    2.0f / 3,   0.5f,
    1.0f,       0.5f,
    // bottom face
    2.0f / 3,   0.5f,
    1.0f,       0.5f,
    2.0f / 3,   1.0f,
    1.0f,       1.0f,
  };

  glGenBuffers(1, &uvBufferId);                                                       assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);                                          assert(!glGetError());
  glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData, GL_STATIC_DRAW);  assert(!glGetError());

  GLfloat normalBufferData[24 * 3] = 
  {
    // left face
    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,
    // right face
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    // front face
    0, 0, -1,
    0, 0, -1,
    0, 0, -1,
    0, 0, -1,
    // back face
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    // top face
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    // bottom face
    0, -1, 0,
    0, -1, 0,
    0, -1, 0,
    0, -1, 0,
  };

  //for (int i = 0; i < 24 * 3; i += 4 * 3)
  //{
  //  GLfloat * pf = vertexBufferData + i;
  //  glm::vec3 v0(*pf++, *pf++, *pf++);
  //  glm::vec3 v1(*pf++, *pf++, *pf++);
  //  glm::vec3 v2(*pf++, *pf++, *pf++);
  //  glm::vec3 norm = glm::normalize(glm::cross(v1 - v0, v2 - v0));

  //  pf = normalBufferData + i;

  //  for (int i = 0; i < 4; i++)
  //  {
  //    *pf++ = norm[0];
  //    *pf++ = norm[1];
  //    *pf++ = norm[2];
  //  }
  //}

  glGenBuffers(1, &normalBufferId);                                                           assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);                                              assert(!glGetError());
  glBufferData(GL_ARRAY_BUFFER, sizeof(normalBufferData), normalBufferData, GL_STATIC_DRAW);  assert(!glGetError());

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
    2, 1, 3,
    // right
    4, 6, 5,
    5, 6, 7,
    // front
    8, 9, 10,
    10, 9, 11,
    // back
    12, 14, 13,
    13, 14, 15,
    // top
    16, 17, 18,
    18, 17, 19,
    // bottom
    20, 22, 21,
    21, 22, 23
  };
#endif
  glGenBuffers(1, &indexBufferId);                                                                  assert(!glGetError());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);                                             assert(!glGetError());
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBufferData), indexBufferData, GL_STATIC_DRAW);  assert(!glGetError());
}


TxCube::~TxCube()
{
}

void TxCube::draw()
{
  glEnableVertexAttribArray(0);                                     assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);                    assert(!glGetError());
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);     assert(!glGetError());

  glEnableVertexAttribArray(1);                                     assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);                        assert(!glGetError());
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);     assert(!glGetError());

  glEnableVertexAttribArray(2);                                     assert(!glGetError());
  glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);                    assert(!glGetError());
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);     assert(!glGetError());

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
  glDisableVertexAttribArray(2);    assert(!glGetError());
}
