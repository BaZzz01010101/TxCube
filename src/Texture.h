#pragma once
#include "glall.h"

class Texture
{
private:
public:
  GLuint id;

  Texture();
  ~Texture();

  bool loadFromFile(const char * fileName);
};

