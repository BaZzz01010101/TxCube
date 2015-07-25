#pragma once
#include "glall.h"

class GxObject
{
protected:
public:
  glm::mat4 mat;

  GxObject();
  virtual ~GxObject();

  inline glm::vec4 getRight() { return mat[0]; }
  inline glm::vec4 getUp() { return mat[1]; }
  inline glm::vec4 getFront() { return mat[2]; }
  inline glm::vec4 getPos() { return mat[3]; }

  virtual void draw() = 0;
};

