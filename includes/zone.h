#ifndef ZONE
#define ZONE
#include "base.h"
class Zone {
  int y;
  int x;
  int height;
  int width;
  float coefficient;
public:
  Zone(int y_, int x_, int h, int w, float coef) : y(y_), x(x_), height(h), width(w), coefficient(coef) {};
  int getY() {return y;}
  int getX() {return x;}
  float getCoefficient() {return coefficient;}
  void setCoefficient(float c) {coefficient = c;}
};
#endif