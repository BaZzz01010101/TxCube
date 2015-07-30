#include "Scene.h"
#include "TxCube.h"
#include "Shader.h"


Scene::Scene() :
  eye(0, 0, 5),
  at(0, 0, 0),
  view(glm::lookAt(eye, at, glm::vec3(0, 1, 0))),
  projection(glm::perspective(45.0f, 16.0f / 10.0f, 0.1f, 100.0f))
{
  objects.push_back(new TxCube(1.0f));
  objects.back()->mat = glm::translate(objects.back()->mat, glm::vec3(2, 0, 0));
  objects.push_back(new TxCube(2.0f));
  objects.back()->mat = glm::translate(objects.back()->mat, glm::vec3(-1, 0, 0));

  const char * vertShadeStr =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vertexPos;\n"
    "layout(location = 1) in vec2 vertexUV;\n"
    "layout(location = 2) in vec3 vertexNorm;\n"
    "uniform mat4 mvp;\n"
    "uniform mat4 mv;\n"
    "out vec3 pos;\n"
    "out vec2 uv;\n"
    "out vec3 norm;\n"
    "out float ltPower;\n"
    "const vec3 ltDir = normalize(vec3(5, 0, -3));\n"

    "void main()\n"
    "{\n"
    "  gl_Position = mvp * vec4(vertexPos, 1);\n"
    "  uv = vertexUV;\n"
    "  pos = vec3(mv * vec4(vertexPos, 1));\n"
    "  norm = normalize(vec3(mat3(mv) * vertexNorm));\n"
    "  ltPower = 0.1 + 0.9 * clamp(dot(ltDir, -norm), 0, 1);\n"
    "}\n";

  const char * fragShadeStr =
    "#version 330 core\n"
    "uniform sampler2D mytexture;\n"
    "uniform vec3 eye;\n"
    "in vec2 uv;\n"
    "in vec3 pos;\n"
    "in vec3 norm;\n"
    "in float ltPower;\n"
    "const vec3 ltDir = normalize(vec3(5, 0, -3));\n"
    "out vec3 color;\n"

    "float rand(vec2 co) {\n"
    "  return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);\n"
    "}\n"

    "void main()\n"
    "{\n"
    "  vec3 refl = reflect(normalize(pos - eye), norm);\n"
    "  float specPower = clamp(dot(refl, -ltDir), 0, 1);\n"
    "  color = texture(mytexture, uv).rgb;\n"
    "  const float blackLimit = 0.2;\n"
    "  if(color.r < blackLimit && color.g < blackLimit && color.b < blackLimit) {\n"
    "    float rndf = rand(uv);\n"
    "    color.x = rndf;\n"
    "    color.y = rndf;\n"
    "    color.z = rndf;\n"
    "  } \n"
    "    color = color * ltPower + pow(specPower, 16);\n"
    "}\n";

  Shader vertShade(GL_VERTEX_SHADER);
  Shader fragShade(GL_FRAGMENT_SHADER);

  vertShade.compileFromString(vertShadeStr);    assert(!vertShade.isError());
  fragShade.compileFromString(fragShadeStr);    assert(!fragShade.isError());
  prog.attachShader(vertShade);                 assert(!prog.isError());
  prog.attachShader(fragShade);                 assert(!prog.isError());
  prog.link();                                  assert(!prog.isError());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);         assert(!glGetError());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);         assert(!glGetError());
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

  ax += 0.0087f;
  ay += 0.0057f;
  az += 0.0037f;

  GLuint eyeId = glGetUniformLocation(prog.getId(), "eye");   assert(!glGetError());
  glUniform3fv(eyeId, 1, &eye[0]);                            assert(!glGetError());

  for (SCENE_OBJECTS::iterator it = objects.begin(); it != objects.end(); ++it)
  {
    GxObject * obj = *it;

    glm::mat4 m = glm::rotate(obj->mat, ax, glm::vec3(-1, 0, 0));
    m = glm::rotate(m, ay, glm::vec3(0, 1, 0));
    m = glm::rotate(m, az, glm::vec3(0, 0, 1));

    GLuint mvpId = glGetUniformLocation(prog.getId(), "mv");                assert(!glGetError());
    glUniformMatrix4fv(mvpId, 1, GL_FALSE, &(view * m)[0][0]);              assert(!glGetError());

    GLuint mvId = glGetUniformLocation(prog.getId(), "mvp");                assert(!glGetError());
    glUniformMatrix4fv(mvId, 1, GL_FALSE, &(projection * view * m)[0][0]);  assert(!glGetError());

    GLuint texId = glGetUniformLocation(prog.getId(), "mytexture");         assert(!glGetError());
    glUniform1i(texId, 0);                                                  assert(!glGetError());

    obj->draw();
  }
}

void Scene::setViewport(int width, int height)
{
  if (height)
    projection = glm::perspective(45.0f, float(width) / height, 0.1f, 100.0f);
  else
    projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
}
