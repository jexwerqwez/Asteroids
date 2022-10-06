#include "asteroids.h"

void Gun::draw_shot(int x_off, int y_off) {
    mvaddch(y_off+position.getY(), x_off+position.getX(), getSprite());
}

void Gun::erase_shot(int x_prev, int y_prev) {
    mvaddch(y_prev+position.getY(), x_prev+position.getX(), ' ');
}
