#ifndef ASTEROIDS
#define ASTEROIDS

#include "base.h"
#include "field.h"
#include "objects.h"
class Asteroids : public Space_Object {
  vector<vector<char>> asteroid;
 protected:
  Space_Object position;
private:
  int health;
 public:
  Asteroids(vector<vector<char>> a, Space_Object pos, int h = 1)
      : asteroid(a), position(pos), health(h){};
  Asteroids(Asteroids &ast, Space_Object &pos) : asteroid(ast.asteroid), position(pos){};
  int getWidth() { return asteroid.at(0).size(); };
  int getHeight() { return asteroid.size(); };
  int getHealt() { return health; };
  void setHeath(int h) { health = h; };
  void draw_asteroid(int);
  void erase_asteroid();
  void move_ast(int);
  Space_Object getPos() { return position; };
};
class Asteroids_Manager {
  Field field;
  vector<Asteroids *> asters;
  double velocity;

 public:
  Asteroids_Manager(Field f, double v) : field(f), velocity(v){};
  vector<Asteroids *> getAsters() { return asters; };
  int getVelocity() { return velocity; };
  void setVelocity(int v) { velocity = v; };
  void destruct_asteroid(int);
  void asts_manage(int);
  Field getField() { return field; };
};
#endif
