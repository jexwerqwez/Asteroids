#include "game.h"

void Bonus::draw_bonus(int effect){
    mvaddch(position.getY(), position.getX(), getSprite()| COLOR_PAIR(effect));
}

void Bonus::erase_bonus() {
    mvaddch(position.getY(), position.getX(), ' ');
}

void Bonus::move_bonus(int offset) {
    position.setX(position.getX() - offset);
}

void drawBonuses(Bonus* b, int effect) {
    b -> draw_bonus(effect);
}

void eraseBonuses(Bonus* b) {
    b -> erase_bonus();
}

void Bonus_Manager::destruct_bonus(int i) {
    delete bonuses.at(i);
    bonuses.erase(bonuses.begin() + i);
}

void moveBonusLeft(Bonus_Manager* bonuses, Bonus* bonus, int a) {
    if ((bonuses->getField()).object_inside(bonus->getPos()))
        bonus->move_bonus(1);
    else
        bonuses->destruct_bonus(a);
}

void Bonus::generate_bonus(Space_Object pos) {
    position.setX(pos.getX());
    position.setY(pos.getY());
}
void Bonus_Manager::bonus_manager(Space_Object pos, int bonus_mode) {
    for (int i = 0; i < bonuses.size(); i++)
        eraseBonuses(bonuses[i]);
    for (int i = 0; i < bonuses.size(); i++)
        moveBonusLeft(this, bonuses[i], i);
    int bonus_type = 1+rand()%11;
    char bonus = '0';
   if(rand()%100 == 6) {
        Space_Object bonuspos(field.getFieldWidth() - 2, 1 + rand() % (field.getFieldHeight()-1));
        bonuses.push_back(new Bonus(bonus, bonuspos));
    }
    for (int i = 0; i < bonuses.size(); i++)
        drawBonuses(bonuses[i], rand()%8);
}

int Bonus::set_effect(Spaceship* spaceship, Asteroids_Manager* all_asts, Gun* gun, Game* game, int type, int gun_mode) {
    switch (type) {
        case 0: spaceship->setHeath(spaceship->getHealt()+1); // extra_life;
            break;
        case 1: spaceship->setHeath(spaceship->getHealt()-1); // spaceship acceleration
            break;
        case 2: gun->gun_manager(spaceship->getPos(), gun_mode, 1); // int burst_shot;
            break;
        case 3: game->setScore(game->getScore() * 2); // int score_multiplier;
            break;
        case 4: all_asts->setVelocity(all_asts->getVelocity()+100);// int asteroid_slowdown;
            break;
        case 5: all_asts->setVelocity(all_asts->getVelocity()-100);// int asteroid_acceleration;
            break;
        case 6: gun->gun_manager(spaceship->getPos(), 0, 0);// int gun_disabling;
            break;
        case 7: spaceship->setHeath(spaceship->getHealt()-100000);
            break;
        }
    return type;
}
