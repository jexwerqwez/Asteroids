#ifndef OBJECTS
#define OBJECTS
#include "base.h"
class Space_Object {
  int x;
  int y;

public:
  Space_Object(int x_ = 0, int y_ = 0) : x(x_), y(y_){};
  int getX() { return x; };
  int getY() { return y; };
  void setX(int xx) { x = xx; };
  void setY(int yy) { y = yy; };
  int operator==(Space_Object pos) {
    return this->x == pos.getX() && this->y == pos.getY();
  }
  int operator!=(Space_Object pos) {
    return this->x != pos.getX() && this->y != pos.getY();
  }
  Space_Object operator+(Space_Object pos) {
    return Space_Object(this->x + pos.getX(), this->y + pos.getY());
  }
  Space_Object operator-(Space_Object pos) {
    return Space_Object(this->x - pos.getX(), this->y - pos.getY());
  }
  bool compare_pos(Space_Object object2, int offset) {
    return this->x >= object2.getX() - offset &&
           this->x <= object2.getX() + offset &&
           this->y >= object2.getY() - offset &&
           this->y <= object2.getY() + offset;
  }
};
#endif
