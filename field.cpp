#include "field.h"

bool Field::object_inside(Space_Object object) {
    return object.getX() > 0 && object.getX() < width-1 &&
            object.getY() > 0 && object.getY() < height-1;
}

void Field::draw_field() {
    move(0,0);
    for(int i = 0; i < height; i++) {
        addch(' ' | COLOR_PAIR(8));
        addch('\n');
        //printw("#\n");
    }
    move(0, 1);
    for(int i = 0; i < width; i++) {
        addch(' ' | COLOR_PAIR(8));
    }
    move(height-1, 1);
    for(int i = 0; i < width; i++) {
        addch(' ' | COLOR_PAIR(8));
    }
    for(int i = 1; i < height; i++) {
        move(i, width);
        addch(' ' | COLOR_PAIR(8));
    }
    move(height+2, width/2-5);
}
