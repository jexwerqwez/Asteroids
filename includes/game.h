#ifndef GAME
#define GAME
#include "asteroids.h"
#include "base.h"
#include "field.h"
#include "gun.h"
#include "settings.h"
#include "spaceship.h"
#include "zone.h"
class Game {
  int status;
  string filename;
  int score;
  int hard;
  int main_velocity;

public:
  Game(int h) : hard(h){};
  friend Field;
  int getstatus() { return status; };
  void setstatus(int s) { status = s; };
  int sethard(Asteroids_Manager *);
  void play(int, int, Settings *);
  int getScore() { return score; };
  void setScore(int s) { score = s; };
  int getVelocity() { return main_velocity; };
  void setVelocity(int v) { main_velocity = v; };
  void create_file(Field *, vector<Zone *> *, int, auto, int, int, Spaceship *,
                   double, double, Settings *);
  ~Game() { endwin(); }
};
class Bonus : public Space_Object {
  char bonus;

protected:
  Space_Object position;

public:
  Bonus(char bsp, Space_Object pos) : bonus(bsp), position(pos){};
  void draw_bonus(int);
  void erase_bonus();
  // int getType() {return type;};
  // void setType(int t) {type = t;};
  void move_bonus(int);
  char getSprite() { return bonus; };
  void generate_bonus(Space_Object);
  int set_effect(Spaceship *, Asteroids_Manager *, Gun *, Game *, int);
  Space_Object getPos() { return position; };
};

class Bonus_Manager {
  Field field;
  vector<Bonus *> bonuses;

public:
  friend Spaceship;
  Bonus_Manager(Field f) : field(f){};
  vector<Bonus *> getBonuses() { return bonuses; };
  Field getField() { return field; };
  void destruct_bonus(int);
  void bonus_manager();
};

class Menu {
protected:
  Field field;

public:
  Menu(Field f) : field(f){};
  virtual int processing(Field *) = 0;
  void print_info(Field *, int, int, const char *, int);
  int choices(Settings *, Field, int);
};

class Start : virtual public Menu {
  string filename;
  Settings *settings;

public:
  Start(Field f, string n, Settings *s) : Menu(f), filename(n), settings(s){};
  int processing(Field *);
};

class Settings_Menu : virtual public Menu {
  Settings *settings;

public:
  Settings_Menu(Field f, Settings *s) : Menu(f), settings(s){};
  void setting_menu(Field);
  void print_settings(Field *);
  void print_field(Field *);
  int field_menu(Field *);
  void print_rules(Field *);
  int processing(Field *);
  int rules_processing(Field *);
};
class Finish : virtual public Menu {
  string filename;
  Settings *settings;
  Game game;

public:
  Finish(Field f, string n, Settings *s, Game g)
      : Menu(f), filename(n), settings(s), game(g){};
  void print_gameover(Field *);
  void print_blackhole(Field *);
  int processing(Field *);
};
#endif
