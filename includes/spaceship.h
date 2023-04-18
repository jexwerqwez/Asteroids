#ifndef SPACESHIP
#define SPACESHIP
#include "base.h"
#include "field.h"
#include "objects.h"
class Spaceship : public Space_Object {
  int health;
  char spaceship;
  int heel_x;
  int heel_y;

protected:
  Space_Object position;

public:
  Spaceship(int h, char ssp, int hex, int hey, Space_Object pos)
      : health(h), spaceship(ssp), heel_x(hex), heel_y(hey), position(pos){};
  void draw_spaceship(int);
  void erase_spaceship();
  int getHealt() { return health; };
  void setHeath(int h) { health = h; };
  char getSprite() { return spaceship; };
  void moveHorizontal(int);
  void moveVertical(int);
  int getHeelX() { return heel_x; };
  int getHeelY() { return heel_y; };
  void setHeelX(int hx) { heel_x = hx; };
  void setHeelY(int hy) { heel_y = hy; };
  Space_Object change_position(int, Field);
  Space_Object getPos() { return position; };
};
#endif
