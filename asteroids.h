#ifndef ASTEROIDS
#define ASTEROIDS

#include <iostream>
#include <ncurses.h>

using namespace std;

class Game {
    int status;
    public:
        int getstatus() {return status;};
        void run();
        void stop();
};

// class Space_Object {
//     int x;
//     int y;
//     public:
//         Space_Object(int x_ = 0, int y_ = 0): x(x_), y(y_) {};
//         int getX() {return x;};
//         int getY() {return y;};
// };

class Spaceship {
    int x;
    int y;
    public:
        Spaceship(int x_ = 0, int y_ = 0): x(x_), y(y_) {};
        int getX() {return x;};
        int getY() {return y;};
        void setX(int xx) {x = xx;};
        void setY(int yy) {y = yy;};
        char ship_direction(int signal);
};

class Gun {
    int gun_x;
    int gun_y;
    public:
    Gun(int gx = 0, int gy = 0): gun_x(gx), gun_y(gy) {};
    int getX() {return gun_x;};
    int getY() {return gun_y;};
    void setX(int gxx) {gun_x = gxx;};
    void setY(int gyy) {gun_y = gyy;};
    int shot(int signal, int x, int y);
};
// class Asteroid: public Space_Object {
//     int** size;
//     int velocity;
//     public:
//         void construct_asteroid(int x, int y, int **size);
//         int asteroid_status(int x, int y);
//         int destroy_asteroid();
// };

class Field {
    int height, width;
    int **field;
    public:
        Field();
        Field(int h, int w);
        void init_field(int s, int s_x, int s_y, int gm, int g, int g_x, int g_y);
        void next_position(int **prev_matrix, int **next_matrix);
        void draw_field(char asteroid, char spaceship, char shot);
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