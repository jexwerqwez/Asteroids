#include "asteroids.h"

void Asteroids::draw_asteroid() {
    for(int i = 0; i < asteroid.size(); i++) {
        for(int j = 0; j < asteroid[i].size(); j++)
            mvaddch(position.getY() + i, position.getX() + j, asteroid[i][j]);
    }
}
void Asteroids::erase_asteroid() {
    for(int i = 0; i < asteroid.size(); i++) {
        for(int j = 0; j < asteroid[i].size(); j++)
            mvaddch(position.getY() + i, position.getX() + j, ' ');
    }
}
void Asteroids::move_ast(int offset) {
    position.setX(position.getX() - offset);
}

void drawAsts(Asteroids* ast) {
    ast -> draw_asteroid();
}
void eraseAsts(Asteroids* ast) {
    ast -> erase_asteroid();
}
void moveAstsLeft(Asteroids_Manager* ast_manage, Asteroids* aster, int a) {
    if(aster->getX() < (ast_manage->getField()).getFieldWidth() && aster->getX() >= 0 && 
        aster->getY() >= -5 && aster->getY() < (ast_manage->getField()).getFieldHeight())
        aster->move_ast(1);
    else
        ast_manage->destruct_asteroid(a);
}

void Asteroids_Manager::asts_manage() {
    for(int i = 0; i < asters.size(); i++)
        eraseAsts(asters[i]);
    for(int i = 0; i < asters.size(); i++)
        moveAstsLeft(this, asters[i], i);
    vector<vector<char>> asteroid = {
        {'*', ' '},
        {'*', '*'},
    };
    Space_Object ast_pos(field.getFieldWidth() - 2, 1 + rand() % (field.getFieldHeight()-asteroid.size()-1));
    asters.push_back(new Asteroids(asteroid, ast_pos));
    for(int i = 0; i < asters.size(); i++)
        drawAsts(asters[i]);
}

void Asteroids_Manager::destruct_asteroid(int i) {
    delete asters.at(i);
    asters.erase(asters.begin() + i);
}

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

void Gun::draw_shot(int x_off, int y_off) {
    mvaddch(y_off+position.getY(), x_off+position.getX(), getSprite());
}

void Gun::erase_shot(int x_prev, int y_prev) {
    mvaddch(y_prev+position.getY(), x_prev+position.getX(), ' ');
}
