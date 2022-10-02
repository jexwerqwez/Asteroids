#include "asteroids.h"

void Asteroids::draw_asteroid(int x_off) {
    for(int i = 0; i < asteroid.size(); i++) {
        for(int j = 0; j < asteroid[i].size(); j++)
            mvaddch(position.getY() + i, position.getX() + j, asteroid[i][j]);
    }
}

void Asteroids::erase_asteroid(int x_prev) {
    for(int i = 0; i < asteroid.size(); i++) {
        for(int j = 0; j < asteroid[i].size(); j++)
            mvaddch(position.getY() + i, position.getX() + j, ' ');
    }
}

void Asteroids::move_ast(int offset) {
    position.setX(position.getX() + offset);
}

void drawAsts(Asteroids* ast, int x) {
    ast -> draw_asteroid(x);
}

void eraseAsts(Asteroids* ast, int x) {
    ast -> erase_asteroid(x);
}

void moveAstsLeft(Asteroids_Manager* ast_manage, Asteroids* aster, int i) {
    if(aster->getX() >= 0)
        aster->move_ast(aster->getWidth());
    else
        aster->erase_asteroid(i);
}

void Asteroids_Manager::Update() {
    for(int i = 0; i < asters.size(); i++)
        eraseAsts(asters[i], i);
    for(int i = 0; i < asters.size(); i++)
        moveAstsLeft(this, asters.at(i), i);
    vector<vector<char>> asteroid = {
        {'*', '*', ' '},
        {'*', '*', '*'},
        {'*', '*', '*'}
    };
    Space_Object ast_pos(rand() % field.getFieldHeight(), 0);
    asters.push_back(new Asteroids(asteroid, ast_pos));
    for(int i = 0; i < asters.size(); i++)
        drawAsts(asters[i], i);
}

void Asteroids_Manager::destruct_asteroid(int i) {
    delete asters.at(i);
    asters.erase(asters.begin() + i);
}

void Spaceship::draw_spaceship(int x_off, int y_off) {
    mvaddch(y_off+position.getY(), x_off+position.getX(), getSprite());
}

void Spaceship::erase_spaceship(int x_prev, int y_prev) {
    mvaddch(y_prev+position.getY(), x_prev+position.getX(), ' ');
}

void Gun::shot(int offset) {
    position.setX(position.getY()+offset);
}

void Gun::draw_shot() {
    mvaddch(position.getY(), position.getX(), getSprite());
}

void Gun::erase_shot() {
    mvaddch(position.getY(), position.getX(), ' ');
}

void GunManager::gunTouch(int i) {
    delete active_shots.at(i);
    active_shots.erase(active_shots.begin() + i);
}

void drawShot(Gun* shots) {
    shots->draw_shot();
}

void clearShot(Gun* shots) {
    shots->erase_shot();
}

void Shooting(GunManager* gun_manager, Gun* gun, int i) {
    gun->shot(i);
}

void GunManager::gunUpdate(int signal, Spaceship sp) {
    for(int i = 0; active_shots.size(); i++)
        clearShot(active_shots[i]);
    for(int i = 0; i < active_shots.size(); i++)
        Shooting(this, active_shots.at(i), i);
    char gun = {'-'};
    Space_Object gunpos(sp.getX(), sp.getY());
    active_shots.push_back(new Gun(gun, gunpos));
    if (signal) {
        for(int i = 0; active_shots.size(); i++)
            drawShot(active_shots[i]);
    }
}
