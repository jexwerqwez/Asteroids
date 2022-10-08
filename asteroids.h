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
};

class Spaceship: public Space_Object{
        char spaceship;
    protected:
        Space_Object position;
    public:
        friend class ViewModule;
        Spaceship(char ssp, Space_Object pos): spaceship(ssp), position(pos) {};
        void draw_spaceship();
        void erase_spaceship();
        char getSprite() {return spaceship;};
        void moveHorizontal(int);
        void moveVertical(int);
        Space_Object getPos() {return position;};
};

class Shot: public Space_Object {
        char shot;
    protected:
        Space_Object position;
    public:
        Shot(char shsp, Space_Object pos): shot(shsp), position(pos) {};
        void draw_shot();
        void erase_shot();
        void moveShot(int);
        void makeShot(Space_Object);
        char getSprite() {return shot;};
        Space_Object getPos() {return position;};
};

class Asteroids: public Space_Object {
        vector<vector<char>> asteroid;
    protected:
        Space_Object position;
    public:
        friend class ViewModule;
        Asteroids(vector<vector<char>> a, Space_Object pos): asteroid(a), position(pos) {};
        Asteroids(Asteroids &ast): asteroid(ast.asteroid), position(0,0) {};
        int getWidth() {return asteroid.at(0).size();};
        int getHeight() {return asteroid.size();};
        void draw_asteroid();
        void erase_asteroid();
        void move_ast(int);
        Space_Object getPos() {return position;};
};


class Field {
    int height;
    int width;
    public:
        Field(int h, int w): height(h), width(w) {};
        int getFieldWidth() {return width;};
        int getFieldHeight() {return height;};
        bool object_inside(Space_Object object);
        void draw_field();
};

class ViewModule {
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
        void destruct_asteroid(int i);
        void asts_manage();
        Field getField() {return field;};
};

class Gun {
    Field field;
    vector <Shot*> shots;
    Spaceship* spaceship;
    public:
        Gun(Field f): field(f) {};
        vector<Shot*> getShots() {return shots;};
        Field getField() {return field;};
        void destruct_shot(int i);
        void gun_manager(Space_Object, int);
};

class Game {
    int status;
    public:
        Game();
        friend Field;
        int getstatus() {return status;};
        void menu();
        void play(int, int);
        void gameover(int, int);
        ~Game() {
            endwin();
        }
};

#endif