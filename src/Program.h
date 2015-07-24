#pragma once
#include "glall.h"
#include "Shader.h"

class Program
{
private:
  GLint id;
  bool _isError;
  std::vector<char> errMsg;
  void setErrMsg(const char * str);
  bool checkGlErrors();

public:
  Program();
  ~Program();

  inline GLint getId() const { return id; }
  inline bool isError() const { return _isError; }
  inline char * getLastError() { return &errMsg.front(); }
  bool attachShader(const Shader & shader);
  bool link();
  bool use();
};
