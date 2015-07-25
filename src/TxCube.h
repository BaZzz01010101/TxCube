#pragma once
#include "glall.h"
#include "GxObject.h"
#include "Texture.h" 

class TxCube : public GxObject
{
private:
  Texture texture;
  GLuint vbo;
  GLuint uvBufferId;
  GLuint indexBufferId;

public:
  TxCube(GLfloat size);
  ~TxCube();

  void draw();
};

