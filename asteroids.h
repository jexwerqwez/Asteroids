#ifndef ASTEROIDS
#define ASTEROIDS

#include <iostream>
#include <ncursesw/ncurses.h>
#include <ctime>
#include <sys/time.h>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
using namespace std;

struct Settings {
    unsigned height;
    unsigned width;
    Settings(unsigned h = 10, unsigned w = 10): height(h), width(w) {};
    int parser(Settings &set, string &filename);
};


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
// class Bonus: public Space_Object {
//     char extra_life;
//     char invulnerability;
//     char bullet_slowdown;
//     char bullet_acceleration;
//     char burst_shot;
//     char score_multiplier;
//     char asteroid_slowdown;
//     char asteroid_acceleration;
//     char asteroid_rain;
//     char gun_disabling;
// };
class Spaceship: public Space_Object{
        int health;
        char spaceship;
    protected:
        Space_Object position;
    public:
        Spaceship(int h, char ssp, Space_Object pos): health(h), spaceship(ssp), position(pos) {};
        void draw_spaceship();
        void erase_spaceship();
        int getHealt() {return health;};
        void setHeath(int h) {health = h;};
        char getSprite() {return spaceship;};
        void moveHorizontal(int);
        void moveVertical(int);
        Space_Object change_position(int, Field);
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
        int health;
    protected:
        Space_Object position;
    public:
        Asteroids(vector<vector<char>> a, Space_Object pos, int h = 1): asteroid(a), position(pos), health(h) {};
        Asteroids(Asteroids &ast): asteroid(ast.asteroid), position(0,0) {};
        int getWidth() {return asteroid.at(0).size();};
        int getHeight() {return asteroid.size();};
        int getHealt() {return health;};
        void setHeath(int h) {health = h;};
        void draw_asteroid(int);
        void erase_asteroid();
        void move_ast(int);
        Space_Object getPos() {return position;};
};

class Asteroids_Manager {
    Field field;
    vector <Asteroids*> asters;
    public:
        Asteroids_Manager(Field f): field(f) {};
        vector<Asteroids*> getAsters() {return asters;};
        void destruct_asteroid(int);
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
        void destruct_shot(int);
        int gun_manager(Space_Object, int);
};

class Bonus: public Space_Object {
        char bonus;
    protected:
        Space_Object position;
    public:
        Bonus(char bsp, Space_Object pos): bonus(bsp), position(pos) {};
        void draw_bonus();
        void erase_bonus();
        char getSprite() {return bonus;};
        void generate_bonus(Space_Object);
        void set_effect(Spaceship, Asteroids_Manager, Gun, char);
        Space_Object getPos() {return position;};
};

class Bonus_Manager {
    Field field;
    vector <Bonus*> bonuses;
    public:
        Bonus_Manager(Field f): field(f) {};
        vector<Bonus*> getBonuses() {return bonuses;};
        Field getField() {return field;};
        void destruct_bonus(int);
        void bonus_manager(Space_Object, int);
};

class Game {
    int status;
    string filename;
    Settings settings;
    public:
        Game(string file);
        friend Field;
        int getstatus() {return status;};
        void menu();
        void play(int, int);
        void gameover(int, int);
        void print_info(int, int, const char*);
        ~Game() {
            endwin();
        }
        void timer(int, int, int, int, int, int);
};

#endif
