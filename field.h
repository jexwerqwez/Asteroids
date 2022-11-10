#ifndef FIELD
#define FIELD
#include "base.h"
#include "objects.h"
class Field {
    int height;
    int width;
    public:
        Field(int h, int w): height(h), width(w) {};
        int getFieldWidth() {return width;};
        int getFieldHeight() {return height;};
        bool object_inside(Space_Object object);
        void draw_field();
};
#endif