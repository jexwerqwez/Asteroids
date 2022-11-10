#ifndef ASTEROIDS
#define ASTEROIDS

#include "base.h"
#include "objects.h"
#include "field.h"
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
    double velocity;
    public:
        Asteroids_Manager(Field f, double v): field(f), velocity(v) {};
        vector<Asteroids*> getAsters() {return asters;};
        int getVelocity() {return velocity;};
        void setVelocity(int v) {velocity = v;};
        void destruct_asteroid(int);
        void asts_manage();
        Field getField() {return field;};
};
#endif
