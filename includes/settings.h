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
  std::vector<float> fuzzy_coef;
  std::vector<int> fuzzy_dist;
  std::vector<int> fuzzy_prio;

  Settings(unsigned h = 10, unsigned w = 10, int s = 0, unsigned hp = 1)
      : height(h), width(w), score(s), hithpoint(hp), fuzzy_coef({1}),
        fuzzy_dist({1}), fuzzy_prio({1}) {}

  int parser(Settings &set, std::string &filename);
  Zone_Settings getZoneSettings() {
    return {fuzzy_coef, fuzzy_dist, fuzzy_prio};
  };
  void outputZoneSettings(std::string filename);
};
#endif
