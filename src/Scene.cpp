#include "Scene.h"
#include "TxCube.h"
#include "Shader.h"


Scene::Scene() :
  view(glm::lookAt(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0))),
  projection(glm::perspective(45.0f, 16.0f / 10.0f, 0.1f, 100.0f))
{
  objects.push_back(new TxCube(1.0f));
  objects.back()->mat = glm::translate(objects.back()->mat, vec3(2, 0, 0));
  objects.push_back(new TxCube(2.0f));
  objects.back()->mat = glm::translate(objects.back()->mat, vec3(-1, 0, 0));

  const char * vertShadeStr =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
    "uniform mat4 mvp;\n"
    "void main()\n"
    "{\n"
    "  vec4 v = vec4(vertexPosition_modelspace, 1);\n"
    "  gl_Position = mvp * v;\n"
    "}\n";

  const char * fragShadeStr =
    "#version 330 core\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "  color = vec3(1, 0, 0);\n"
    "}\n";

  Shader vertShade(GL_VERTEX_SHADER);
  Shader fragShade(GL_FRAGMENT_SHADER);

  vertShade.compileFromString(vertShadeStr);    assert(!vertShade.isError());
  fragShade.compileFromString(fragShadeStr);    assert(!fragShade.isError());
  prog.attachShader(vertShade);                 assert(!prog.isError());
  prog.attachShader(fragShade);                 assert(!prog.isError());
  prog.link();                                  assert(!prog.isError());
}

Scene::~Scene()
{
  for (SCENE_OBJECTS::iterator it = objects.begin(); it != objects.end(); ++it)
    delete *it;
}

void Scene::draw()
{
  prog.use();
  assert(!prog.isError());

  static float ax = 0;
  static float ay = 0;
  static float az = 0;

  ax += 0.057f;
  ay += 0.037f;
  az += 0.017f;

  for (SCENE_OBJECTS::iterator it = objects.begin(); it != objects.end(); ++it)
  {
    GxObject * obj = *it;

    mat4 m = glm::rotate(obj->mat, ax, vec3(-1, 0, 0));
    m = glm::rotate(m, ay, vec3(0, 1, 0));
    m = glm::rotate(m, az, vec3(0, 0, 1));

    GLuint matID = glGetUniformLocation(prog.getId(), "mvp");                 assert(!glGetError());
    glUniformMatrix4fv(matID, 1, GL_FALSE, &(projection * view * m)[0][0]);   assert(!glGetError());

    obj->draw();
  }
}

void Scene::setViewport(int width, int height)
{
  projection = glm::perspective(45.0f, float(width) / height, 0.1f, 100.0f);
}
