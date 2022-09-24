#ifndef ASTEROIDS
#define ASTEROIDS

#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <time.h>
using namespace std;

struct spaceshippos {
    int s, s_x, s_y;
};

struct gunpos {
    int gun_mode, g, g_x, g_y;
};

struct asteroidpos {
    int **asteroid;
    int a_x, a_y;
};

class Game {
    int status;
    public:
        int getstatus() {return status;};
        void run();
        void stop();
};

class Space_Object {
    int x;
    int y;
    float velocity;
    public:
        Space_Object(int x_ = 0, int y_ = 0, float vc = 0): x(x_), y(y_), velocity(vc) {};
        int getX() {return x;};
        int getY() {return y;};
        void setX(int xx) {x = xx;};
        void setY(int yy) {y = yy;};
};

class Spaceship: public Space_Object {
    public:
        Spaceship(int sx = 0, int sy = 0): Space_Object(sx, sy) {};
        char ship_direction(int signal);
};
 
class Gun: public Space_Object {
    public:
        Gun(int gx = 0, int gy = 0, float gv = 0): Space_Object(gx, gy, gv) {};
        int shot(int signal, int x, int y);
};

class Asteroid: public Space_Object {
    public:
        Asteroid(int ax = 0, int ay = 0, float av = 0): Space_Object(ax, ay, av) {};
        int** construct_asteroid(int width, int height);
        int move_asteroid(struct asteroidpos ap);
        int asteroid_status(int x, int y);
        int destruct_asteroid(int **asteroid, int width, int height);
};

class Field {
    int height, width;
    int **field;
    public:
        Field();
        Field(int h, int w);
        int init_field(struct spaceshippos sp, struct gunpos gp, struct asteroidpos ap);
        int set_asteroid(int start_x, int start_y, struct asteroidpos ap);
        void draw_field(char asteroid, char spaceship, char shot);
        void draw_board();
        ~Field() { for(int i = 0; i < height; i++) delete field[i]; delete[]field; };
};

class ViewModule {
    char asteroid;
    char spaceship;
    char shot;
    int** field;
    public:
        void draw_mode(Field **field, char asteroid, char spaceship, char shot);
        void draw_menu(Field **field);
};

#endif