#ifndef ZONE
#define ZONE
#include "base.h"
class Zone {
  int height;
  int width;
  float coefficient;
public:
  Zone(int h, int w, float coef) : height(h), width(w), coefficient(coef) {};
  int getHeight() {return height;}
  int getWidth() {return width;}
  float getCoefficient() {return coefficient;}
};
#endif