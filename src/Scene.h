#pragma once
#include "glall.h"
#include "GxObject.h"
#include "Program.h"

class Scene
{
private:
  typedef std::vector<GxObject*> SCENE_OBJECTS;
  SCENE_OBJECTS objects;
  glm::mat4 view;
  glm::mat4 projection;
  Program prog;

public:
  Scene();
  ~Scene();

  void draw();
  void setViewport(int width, int height);
};

