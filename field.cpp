#include "asteroids.h"

bool Field::object_inside(Space_Object object) {
    return object.getX() >= 0 && object.getX() <= width &&
            object.getY() >= 0 && object.getY() <= height;
}

void Field::draw_field() {
    move(0,0);
    for(int i = 0; i < height; i++) {
        printw("#\n");
    }
    move(0, 1);
    for(int i = 0; i < width; i++) {
        printw("#");
    }
    move(height-1, 1);
    for(int i = 0; i < width; i++) {
        printw("#");
    }
    for(int i = 1; i < height; i++) {
        move(i, width);
        printw("#");
    }
}
