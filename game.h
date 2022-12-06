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
    int score;
    int hard;
    int main_velocity;
    public:
        Game(int h): hard(h) {};
        friend Field;
        int getstatus() {return status;};
        void setstatus(int s) {status = s;};
        void sethard(Asteroids_Manager*);
        void play(int, int, Settings);
        int getScore() {return score;};
        void setScore(int s) {score = s;};
        int getVelocity() {return main_velocity;};
        void setVelocity(int v) {main_velocity = v;};
        ~Game() {
            endwin();
        }
};
class Bonus: public Space_Object {
        char bonus;
    protected:
        Space_Object position;
    public:
        Bonus(char bsp, Space_Object pos): bonus(bsp), position(pos) {};
        void draw_bonus(int);
        void erase_bonus();
        // int getType() {return type;};
        // void setType(int t) {type = t;};
        void move_bonus(int);
        char getSprite() {return bonus;};
        void generate_bonus(Space_Object);
        int set_effect(Spaceship*, Asteroids_Manager*, Gun*, Game*, int, int);
        Space_Object getPos() {return position;};
};

class Bonus_Manager {
    Field field;
    vector <Bonus*> bonuses;
    public:
        friend Spaceship;
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
    virtual void processing(Settings, Field*) = 0;
    void print_info(Field*, int, int, const char*, int);
    int choices(Settings, Field, int);
};
class Start: virtual public Menu {
    string filename;
    Settings settings;
    public:
        Start(Field f, string n, Settings s): Menu(f), filename(n), settings(s) {};
        void processing(Settings, Field*);
        void print_asteroids(Settings, Field*);
};
class Pause: virtual public Menu {
    public:
        Pause(Field f): Menu(f) {};
        void processing(Settings, Field*);
};
class Settings_Menu: virtual public Menu {
    public:
        Settings_Menu(Field f): Menu(f) {};
        void setting_menu(Settings, Field);
        void print_settings(Settings, Field*);
        void print_field(Settings, Field*);
        int field_menu(Settings, Field*);
        void processing(Settings, Field*);
};
class Finish: virtual public Menu {
    string filename;
    Settings settings;
    Game game;
    public:
        Finish(Field f, string n, Settings s, Game g): Menu(f), filename(n), settings(s), game(g) {};
        void print_gameover(Settings, Field*);
        void print_blackhole(Settings, Field*);
        void processing(Settings, Field*);
};
#endif
