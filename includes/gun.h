#ifndef GUN
#define GUN
#include "base.h"
#include "field.h"
#include "objects.h"
#include "spaceship.h"
class Shot : public Space_Object {
  char shot;

protected:
  Space_Object position;

public:
  Shot(char shsp, Space_Object pos) : shot(shsp), position(pos){};
  void draw_shot();
  void erase_shot();
  void moveShot(int);
  void makeShot(Space_Object);
  char getSprite() { return shot; };
  Space_Object getPos() { return position; };
};
class Gun {
  Field field;
  vector<Shot *> shots;
  Spaceship *spaceship;

public:
  Gun(Field f) : field(f){};
  vector<Shot *> getShots() { return shots; };
  Field getField() { return field; };
  void destruct_shot(int);
  int gun_manager(Space_Object, int, int);
};
#endif
