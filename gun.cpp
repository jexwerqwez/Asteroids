#include "asteroids.h"

void Gun::draw_shot() {
    mvaddch(position.getY(), position.getX(), getSprite());
}

void Gun::erase_shot() {
    mvaddch(position.getY(), position.getX(), ' ');
}

void Gun::moveShot(int x) {
    position.setX(position.getX() + x);
}

void Gun::makeShot(Space_Object pos) {
    position.setX(pos.getX());
    position.setY(pos.getY());
}