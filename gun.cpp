#include "asteroids.h"

void Shot::draw_shot() {
    mvaddch(position.getY(), position.getX(), getSprite());
}

void Shot::erase_shot() {
    mvaddch(position.getY(), position.getX(), ' ');
}

void Shot::moveShot(int x) {
    position.setX(position.getX() + x);
}

void drawShots(Shot* sh) {
    sh -> draw_shot();
}

void eraseShots(Shot* sh) {
    sh -> erase_shot();
}

void moveShotsRigth(Gun* gun, Shot* shot, int a) {
    if ((gun->getField()).object_inside(shot->getPos()))
        shot->moveShot(1);
    else
        gun->destruct_shot(a);
}

void Gun::destruct_shot(int i) {
    delete shots.at(i);
    shots.erase(shots.begin() + i);
}

void Shot::makeShot(Space_Object pos) {
    position.setX(pos.getX());
    position.setY(pos.getY());
}
void Gun::gun_manager(Space_Object pos, int signal) {
        for (int i = 0; i < shots.size(); i++)
            eraseShots(shots[i]);
        for (int i = 0; i < shots.size(); i++)
            moveShotsRigth(this, shots[i], i);
        timeout(240);
        char shot = {'-'};
        Space_Object shotpos(pos.getX(), pos.getY());
        if(signal)
            shots.push_back(new Shot(shot, shotpos));
        for (int i = 0; i < shots.size(); i++)
            drawShots(shots[i]);
}
