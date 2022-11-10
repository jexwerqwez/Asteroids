#ifndef SETTINGS
#define SETTINGS
#include "base.h"
struct Settings {
    unsigned height;
    unsigned width;
    Settings(unsigned h = 10, unsigned w = 10): height(h), width(w) {};
    int parser(Settings &set, string &filename);
};
#endif