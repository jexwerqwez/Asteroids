#include "asteroids.h"

void Asteroids::draw_asteroid(int x_off) {
    for(int i = 0; i < asteroid.size(); i++) {
        for(int j = 0; j < asteroid[i].size(); j++)
            mvaddch(position.getY() + i, position.getX() + j + x_off, asteroid[i][j]);
    }
}

void Asteroids::erase_asteroid(int x_prev) {
    for(int i = 0; i < asteroid.size(); i++) {
        for(int j = 0; j < asteroid[i].size(); j++)
            mvaddch(position.getY() + i, position.getX() + j + x_prev, ' ');
    }
}

void Asteroids::move_ast(int offset) {
    position.setX(position.getX() - offset);
}

void drawAsts(Asteroids* ast, int x) {
    ast -> draw_asteroid(x);
}

void eraseAsts(Asteroids* ast, int x) {
    ast -> erase_asteroid(x);
}

void moveAstsLeft(Asteroids_Manager* ast_manage, Asteroids* aster, int i) {
    int x = 20;
    if(aster->getX() >= 0)
        aster->move_ast(aster->getWidth());
    else
        aster->move_ast(i);
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
    Space_Object ast_pos(0, 3);
    asters.push_back(new Asteroids(asteroid, ast_pos));
    for(int i = 0; i < asters.size(); i++)
        drawAsts(asters[i], i);
}

void Spaceship::draw_spaceship(int x_off, int y_off) {
    mvaddch(y_off+position.getY(), x_off+position.getX(), getSprite());
}

void Spaceship::erase_spaceship(int x_prev, int y_prev) {
    mvaddch(y_prev+position.getY(), x_prev+position.getX(), ' ');
}

bool Field::object_inside(Space_Object object) {
    return object.getX() >= 0 && object.getX() <= width &&
            object.getY() >= 0 && object.getY() <= height;
}

void Field::draw_field() {
    move(0,0);
    for(int i = 0; i < width; i++)
        printw("=");
    move(height, 0);
    for(int i = 0; i < width; i++)
        printw("=");  
}

Game::Game() {
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    clear();
    refresh();
    timeout(740);
}

void Game::play() {

}