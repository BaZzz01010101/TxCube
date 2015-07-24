#include "glall.h"
#include "Scene.h"

Scene * scene = NULL;

void OnWindowSize(GLFWwindow * win, int width, int height)
{
  glViewport(0, 0, width, height);
  scene->setViewport(width, height);
}

int main()
{
  int retVal = -1;

  if (glfwInit())
  {
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    //glfwWindowHint(GLFW_SAMPLES, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int initWinWidth = 640;
    const int initWinHeight = 480;
    GLFWwindow * win = glfwCreateWindow(initWinWidth, initWinHeight, "TxCube", NULL, NULL);

    if (win)
    {
      glfwMakeContextCurrent(win);
      glfwSetWindowSizeCallback(win, OnWindowSize);
      glewExperimental = GL_TRUE;

      if (glewInit() == GLEW_OK)
      {
        // workaround GLEW problem with GL_INVALID_ENUM rising just after glewInit
        glGetError();

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);       assert(!glGetError());
        glBindVertexArray(VertexArrayID);           assert(!glGetError());
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  assert(!glGetError());
        glEnable(GL_CULL_FACE);                     assert(!glGetError());
        glCullFace(GL_FRONT);                       assert(!glGetError());

        scene = new Scene();
        scene->setViewport(initWinWidth, initWinHeight);

        while (!glfwWindowShouldClose(win))
        {
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
          assert(!glGetError());

          scene->draw();

          glfwSwapBuffers(win);
          glfwPollEvents();
        }

        retVal = 0;
        delete scene;
      }

    }

    glfwTerminate();
  }

  return retVal;
}
