#ifndef GAME
#define GAME
#include "base.h"
#include "settings.h"
#include "field.h"
#include "spaceship.h"
#include "gun.h"
#include "asteroids.h"
struct Time {
    unsigned int ms = 0, s = 0, m = 0, h = 0;
};

class Game {
    int status;
    string filename;
    Settings settings;
    Time time;
    int score;
    public:
        Game() {};
        friend Field;
        int getstatus() {return status;};
        void play(int, int, Time);
        int getScore() {return score;};
        void setScore(int s) {score = s;};
        Time getTime() {return time;};
        void setTime(Time t) {time.ms = t.ms; time.s = t.s; time.m = t.m; time.h = t.h;};
        ~Game() {
            endwin();
        }
        Time timer(Time, int, int);
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

class Menu {
    protected:
        Field field;
    public:
    Menu(Field f): field(f) {};
    virtual void processing(Field) = 0;
    void print_info(int, int, const char*);
    int choices(int, int, Time, Field, int);
};
class Start: virtual public Menu {
    string filename;
    Settings settings;
    public:
        Start(Field f, string n, Settings s): Menu(f), filename(n), settings(s) {};
        void processing(Field);
};
class Pause: virtual public Menu {
    public:
        Pause(Field f): Menu(f) {};
        void processing(Field);
};
class Settings_Menu: virtual public Menu {
    public:
        Settings_Menu(Field f): Menu(f) {};
        void setting_menu(Field);
        void processing(Field);
};
class Finish: virtual public Menu {
    string filename;
    Settings settings;
    public:
        Finish(Field f, string n, Settings s): Menu(f), filename(n), settings(s) {};
        void processing(Field);
};
#endif
