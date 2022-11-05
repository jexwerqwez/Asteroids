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

Space_Object Spaceship::change_position(int command, Field field) {
        switch (command) {
            case 'd': {
                if (field.object_inside(getPos()) && (getPos().getX() < field.getFieldWidth() - 2))
                    moveHorizontal(1);
                return getPos();
            }
            case 'a': {
                if (field.object_inside(getPos()) && (getPos().getX() > 1))
                    moveHorizontal(-1);
                return getPos();
            }
            case 'w': {
                if (field.object_inside(getPos()) && (getPos().getY() > 1))
                    moveVertical(-1);
                return getPos();
            }
            case 's': {
                if (field.object_inside(getPos()) && (getPos().getY() < field.getFieldHeight()- 2))
                    moveVertical(1);
                return getPos();
            }
        }
    //usleep(1);
    return getPos();
}