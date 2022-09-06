#ifndef ASTEROIDS
#define ASTEROIDS

#include <iostream>
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
    int length;
    public:
        Field(int w, int l): width(w), length(l) {};
        void draw_field();
};

#endif