#ifndef ASTEROIDS
#define ASTEROIDS

#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <time.h>
#include <vector>
using namespace std;


template<class T>
class Space_Object {
    T x;
    T y;
    public:
        Space_Object(int x_ = 0, int y_ = 0): x(x_), y(y_) {};
        int getX() {return x;};
        int getY() {return y;};
        void setX(int xx) {x = xx;};
        void setY(int yy) {y = yy;};
        int operator==(Space_Object<T> pos) {
            return this->x == pos.getX() && this->y == pos.getY()
        }
        Space_Object<T> operator+(Space_Object<T> pos) {
            return Space_Object<T>(this->x + pos.getX(), this->y + pos.getY());
        }
        Space_Object<T> operator-(Space_Object<T> pos) {
            return Space_Object<T>(this->x - pos.getX(), this->y - pos.getY());
        }
        Space_Object<int> getPos() {return pos;};
};

template<class T>
class Spaceship: public Space_Object<T> {
        char spaceship;
    protected:
        Space_Object<int> position;
    public:
        Spaceship(char ssp, T sx = 0, T sy = 0): Space_Object<T>(sx, sy), spaceship(ssp) {};
};

template<class T>
class Gun: public Space_Object<T> {
        char gun;
    protected:
        Space_Object<int> position;
    public:
        Gun(char gsp, T gx = 0, T gy = 0): Space_Object<T>(gx, gy), gun(gsp) {};
        int shot(int signal, T x, T y);
};

template<class T>
class Asteroids: public Space_Object<T> {
        vector<vector<char>> asteroid;
    protected:
        Space_Object<int> position;
    public:
        Asteroids(int ax = 0, int ay = 0, float av = 0): Space_Object(ax, ay, av) {};
        int** construct_asteroid(int width, int height);
        int move_asteroid(struct asteroidpos ap);
        int asteroid_status(int x, int y);
        int destruct_asteroid(int **asteroid, int width, int height);
};

// class Asteroid_Manager {
//     vector <Asteroid*> asters;
// };

class Field {
    int height, width;
    int **field;
    public:
        Field();
        Field(int h, int w);
        void init_field();
        int set_objects(struct spaceshippos sp, struct gunpos gp, struct asteroidpos ap);
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

class ViewModule {
    public:
        virtual void draw() = 0;
        virtual void erase() = 0;
};

class Game {
    int status;
    public:
        int getstatus() {return status;};
        void run();
        void stop();
};

#endif