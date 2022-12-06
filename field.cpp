#include "field.h"

bool Field::object_inside(Space_Object object) {
  return object.getX() > 0 && object.getX() < width - 1 && object.getY() > 0 &&
         object.getY() < height - 1;
}

void Field::draw_field(int mode) {
  move(0, 0);
  short int bord_color = 0;
  short int field_color = 0;
  char cell_type = ' ';
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width + 1; j++) {
      if (mode == 0) {
        bord_color = 8;
        field_color = 3;
        cell_type = ' ';
      } else if (mode == 1) {
        bord_color = 8;
        field_color = 9;
        cell_type = '`';
      }
      if (i == 0 || j == 0 || i == height - 1 || j == width)
        mvaddch(i, j, cell_type | COLOR_PAIR(bord_color));
      else
        mvaddch(i, j, cell_type | COLOR_PAIR(field_color));
    }
  }
  move(height + 2, width / 2 - 5);
}

void Field::draw_circle(int d) {
  int middle_h = getFieldHeight() / 2;
  int middle_w = getFieldWidth() / 2;
}
