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
        int gun(int signal);
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
        // int getwidth() {return width;};
        // int getheight() {return height;};
        // void setwidth(int w) { width = w; };
        // void setheight(int h) { height = h; };
        void init_field(int object, int x, int y);
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