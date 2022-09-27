#ifndef ASTEROIDS
#define ASTEROIDS

#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <time.h>
#include <vector>
using namespace std;

class Space_Object {
    int x;
    int y;
    public:
        Space_Object(int x_ = 0, int y_ = 0): x(x_), y(y_) {};
        int getX() {return x;};
        int getY() {return y;};
        void setX(int xx) {x = xx;};
        void setY(int yy) {y = yy;};
        int operator==(Space_Object pos) {
            return this->x == pos.getX() && this->y == pos.getY();
        }
        Space_Object operator+(Space_Object pos) {
            return Space_Object(this->x + pos.getX(), this->y + pos.getY());
        }
        Space_Object operator-(Space_Object pos) {
            return Space_Object(this->x - pos.getX(), this->y - pos.getY());
        }
        Space_Object getPos(Space_Object pos) {return pos;};
};

class Spaceship: public Space_Object{
        char spaceship;
    protected:
        Space_Object position;
    public:
        friend class ViewModule;
        Spaceship(char ssp, Space_Object pos): spaceship(ssp), Space_Object() {};
        void draw_spaceship(int, int);
        void erase_spaceship(int, int);
        char getSprite() {return spaceship;};
};

// class Gun: public Space_Object {
//         char gun;
//     protected:
//         Space_Object position;
//     public:
//         Gun(char gsp, T gx = 0, T gy = 0): Space_Object(gx, gy), gun(gsp) {};
//         int shot(int signal, T x, T y);
// };

class Asteroids: public Space_Object {
        vector<vector<char>> asteroid;
    protected:
        Space_Object position;
    public:
        friend class ViewModule;
        Asteroids(vector<vector<char>> a, Space_Object pos): asteroid(a), Space_Object() {};
        int getWidth() {return asteroid.at(0).size();};
        int getHeight() {return asteroid.size();};
        void draw_asteroid(int);
        void erase_asteroid(int);
        void move_ast(int);
        // int move_asteroid(struct asteroidpos ap);
        // int asteroid_status(int x, int y);
        // int destruct_asteroid(int **asteroid, int width, int height);
};


class Field {
    int height;
    int width;
    public:
        Field(int h, int w): height(h), width(w) {};
        int getFieldWidth() {return width;};
        int getFieldHeight() {return height;};
        bool object_inside(Space_Object object);
        // void init_field();
        // int set_objects(struct spaceshippos sp, struct gunpos gp, struct asteroidpos ap);
        // int set_asteroid(int start_x, int start_y, struct asteroidpos ap);
        void draw_field();
        // void draw_board();
        // ~Field() { for(int i = 0; i < height; i++) delete field[i]; delete[]field; };
};

class ViewModule {
        // Asteroids ast;
        Spaceship sp;
    public:
        void draw_asteroid();
        void erase_asteroid();
        void draw_spaceship();
        void erase_spaceshi();
        void draw_gun();
        void draw_field();
        void draw_menu(Field **field);
};

class Asteroids_Manager {
    Field field;
    vector <Asteroids*> asters;
    public:
        Asteroids_Manager(Field f): field(f) {};
        vector<Asteroids*> getAsters() {return asters;};
        void Update();
};

class Game {
    int status;
    public:
        Game();
        int getstatus() {return status;};
        void play();
        void stop();
};

#endif