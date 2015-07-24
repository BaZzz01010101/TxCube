#pragma once
#include "glall.h"

class GxObject
{
protected:
public:
  mat4 mat;

  GxObject();
  ~GxObject();

  inline vec4 getRight() { return mat[0]; }
  inline vec4 getUp() { return mat[1]; }
  inline vec4 getFront() { return mat[2]; }
  inline vec4 getPos() { return mat[3]; }

  virtual void draw() = 0;
};

