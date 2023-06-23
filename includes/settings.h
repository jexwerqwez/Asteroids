#ifndef SETTINGS
#define SETTINGS
#include "base.h"

struct Zone_Settings {
  std::vector<float> fuzzy_coef;
  std::vector<int> fuzzy_dist;
  std::vector<int> fuzzy_prio;
};

struct Settings {
  unsigned height;
  unsigned width;
  int score;
  unsigned hithpoint;
  float *fuzzy_coef;
  int *fuzzy_dist;
  int *fuzzy_prio;

  Settings(unsigned h = 10, unsigned w = 10, int s = 0, unsigned hp = 1)
      : height(h), width(w), score(s), hithpoint(hp) {
    fuzzy_coef = new float[1]{1.0f};
    fuzzy_dist = new int[1]{1};
    fuzzy_prio = new int[1]{1};
  }

  int parser(std::string &filename);
  float *getFuzzyCoef() { return fuzzy_coef; }
  int *getFuzzyDist() { return fuzzy_dist; }
  int *getFuzzyPrio() { return fuzzy_prio; }
  // Zone_Settings getZoneSettings() {
  //   return {fuzzy_coef, fuzzy_dist, fuzzy_prio};
  // };
  void outputZoneSettings(std::string filename);
};
#endif
