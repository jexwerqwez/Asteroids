#include "asteroids.h"

void Spaceship::moveHorizontal(int x) {
    position.setX(position.getX() + x);
}

void Spaceship::moveVertical(int y) {
    position.setY(position.getY() + y);
}

void Spaceship::draw_spaceship() {
    mvaddch(position.getY(), position.getX(), getSprite());
}

void Spaceship::erase_spaceship() {
    mvaddch(position.getY(), position.getX(), ' ');
}