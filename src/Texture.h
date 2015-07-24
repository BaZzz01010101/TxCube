#pragma once
#include "glall.h"

class Texture
{
private:
  GLuint textureId;
public:
  Texture(const char * fileName);
  ~Texture();
};

