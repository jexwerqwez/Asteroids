#include "asteroids.h"

void Spaceship::moveHorizontal(int x) {
    position.setX(position.getX() + x);
}

void Spaceship::moveVertical(int y) {
    position.setY(position.getY() + y);
}

void Spaceship::draw_spaceship(int x_off, int y_off) {
    mvaddch(y_off+position.getY(), x_off+position.getX(), getSprite());
}

void Spaceship::erase_spaceship(int x_prev, int y_prev) {
    mvaddch(y_prev+position.getY(), x_prev+position.getX(), ' ');
}