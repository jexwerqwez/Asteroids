#ifndef ASTEROIDS
#define ASTEROIDS

#include <iostream>
#include <ncurses.h>

using namespace std;

class Spaceship {
    int x;  // координаты на плоскости
    int y;
    public:
        Spaceship(int _x, int _y): x(_x), y(_y) {};  // конструктор
        int getx() {return x;};
        int gety() {return y;};
        char draw_spaceship(int signal); // отрисовка корабля
        char gun() {return '@';};
};

class Asteroid {
    int x;
    int y;
    int speed;
    public:
        Asteroid(int _x, int _y, int s): x(_x), y(_y), speed(s) {};
        void draw_asteroid();
};

class Field {
    int width;
    int height;
    public:
        Field(int w, int l): width(w), height(l) {};
        int getwidth() {return width;};
        int getheight() {return height;};
        void draw_field(int width, int height, int **matrix, char ship, 
                        int ship_signal, char gun, char gun_signal);
        void init_field(int **matrix, int object);
};

#endif