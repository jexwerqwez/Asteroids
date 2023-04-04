#ifndef ZONE
#define ZONE
#include "base.h"
#include "objects.h"
class Zone: public Space_Object {
  int height;
  int width;
  float coefficient;
  double distance_x;
  double distance_y;
protected:
  Space_Object position;
public:
  Zone(int h, int w, float coef, double dist_x, double dist_y, Space_Object pos) 
  : height(h), width(w), coefficient(coef), distance_x(dist_x), distance_y(dist_y), position(pos) {};
  int getHeight() {return height;}
  int getWidth() {return width;}
  float getCoefficient() {return coefficient;}
  void setCoefficient(float c) {coefficient = c;}
  double getDistanceX() {return distance_x;}
  double getDistanceY() {return distance_y;}
  void setDistanceX(double dx) {distance_x = dx;}
  void setDistanceY(double dy) {distance_y = dy;}
  Space_Object getPos() { return position; };
};
#endif