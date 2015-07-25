#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <X11/Xlib.h>
#include <unistd.h>
#endif

#include <vector>
#include <limits.h>
#include <stdint.h>
#include <string.h>

namespace Crosy
{
  std::string getExePath();
  uint64_t getPerformanceCounter();
  uint64_t getPerformanceFrequency();
  uint64_t getSystemTime();
  void sleep(unsigned int timeMs);
}