#include "Shader.h"


Shader::Shader(GLenum type)
{
  this->type = type;
  id = 0;
  _isError = false;
}


Shader::~Shader()
{
  glDeleteShader(id);
}

void Shader::setErrMsg(const char * str)
{
  int len = strlen(str);
  errMsg.resize(len + 1);
  strncpy(&errMsg.front(), str, errMsg.size());
}

bool Shader::checkGlErrors()
{
  GLenum errCode = glGetError();

  if (errCode)
  {
    const GLubyte * errStr = gluErrorString(errCode);

    if (errStr)
      setErrMsg((const char*)errStr);
    else
      setErrMsg("Unknown error");
  }
  else
    setErrMsg("");

  _isError = errCode != 0;
  return _isError;
}

bool Shader::compileFromString(const char * source)
{
  GLint Result = GL_FALSE;

  if (!id)
  {
    checkGlErrors();
    id = glCreateShader(type);

    if (checkGlErrors())
       return false;
  }

  glShaderSource(id, 1, &source, NULL);

  if (checkGlErrors())
    return false;

  glCompileShader(id);

  if (checkGlErrors())
    return false;

  glGetShaderiv(id, GL_COMPILE_STATUS, &Result);

  if (checkGlErrors())
    return false;

  if (Result == GL_FALSE)
  {
    int length = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

    if (checkGlErrors())
      return false;

    errMsg.resize(length);
    glGetShaderInfoLog(id, length, NULL, &errMsg.front());

    checkGlErrors();

    _isError = true;
    return false;
  }

  _isError = false;
  return true;
}

bool Shader::compileFromFile(const char * filename)
{
  _isError = true;
  return false;
}
