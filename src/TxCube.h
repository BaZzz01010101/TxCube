#pragma once
#include "glall.h"
#include "GxObject.h"

class TxCube : public GxObject
{
private:
  GLuint vbo;
  GLuint indexBuffer;

public:
  TxCube(GLfloat size);
  ~TxCube();

  void draw();
};

