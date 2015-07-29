#pragma once
#include "glall.h"
#include "GxObject.h"
#include "Texture.h" 

class TxCube : public GxObject
{
private:
  Texture texture;
  GLuint vertexBufferId;
  GLuint uvBufferId;
  GLuint normalBufferId;
  GLuint indexBufferId;

public:
  TxCube(GLfloat size);
  ~TxCube();

  void draw();
};

