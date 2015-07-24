#include "Texture.h"


Texture::Texture(const char * fileName)
{
  textureId = SOIL_load_OGL_texture(fileName, 0, 0, SOIL_FLAG_POWER_OF_TWO);
}


Texture::~Texture()
{
}
