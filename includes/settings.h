#ifndef SETTINGS
#define SETTINGS
#include "base.h"
struct Settings {
  unsigned height;
  unsigned width;
  int score;
  unsigned hithpoint;
  Settings(unsigned h = 10, unsigned w = 10, int s = 0, unsigned hp = 1)
      : height(h), width(w), score(s), hithpoint(hp){};
  int parser(Settings &set, string &filename);
};
#endif
