#ifndef FIELD
#define FIELD
#include "base.h"
#include "objects.h"
class Field {
  int height;
  int width;
  int newheight = height;
  int newwidth = width;

 public:
  Field(int h, int w) : height(h), width(w){};
  int getFieldWidth() { return width; };
  void setFieldWidth(int w) { newwidth = w; };
  int getNewFieldWidth() { return newwidth; };
  int getFieldHeight() { return height; };
  void setFieldHeight(int h) { newheight = h; };
  int getNewFieldHeight() { return newheight; };
  bool object_inside(Space_Object object);
  void draw_field(int mode);
};
#endif
