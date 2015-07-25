#include "Texture.h"


Texture::Texture()
{
  id = 0;
}

Texture::~Texture()
{
  if (id)
    glDeleteTextures(1, &id);
}

bool Texture::loadFromFile(const char * fileName)
{
  if (id)
    glDeleteTextures(1, &id);

  id = SOIL_load_OGL_texture(fileName, 0, 0, SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

  return id != 0;
}