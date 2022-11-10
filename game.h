#ifndef GAME
#define GAME
#include "base.h"
#include "settings.h"
#include "field.h"
#include "spaceship.h"
#include "gun.h"
#include "asteroids.h"
class Game {
    int status;
    string filename;
    Settings settings;
    int score;
    public:
        Game(string file);
        friend Field;
        int getstatus() {return status;};
        void menu();
        void play(int, int);
        void gameover(int, int);
        void print_info(int, int, const char*);
        int getScore() {return score;};
        void setScore(int s) {score = s;};
        ~Game() {
            endwin();
        }
        void timer(int, int, int, int, int, int);
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
        void set_effect(Spaceship, Asteroids_Manager, Gun, Game, char, int);
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
#endif