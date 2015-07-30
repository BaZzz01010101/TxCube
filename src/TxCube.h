#pragma once
#include "glall.h"
#include "GxObject.h"

class TxCube : public GxObject
{
private:
  GLuint vertexBufferId;
  GLuint uvBufferId;
  GLuint normalBufferId;
  GLuint indexBufferId;

public:
  TxCube(GLfloat size);
  ~TxCube();

  void draw();
};

