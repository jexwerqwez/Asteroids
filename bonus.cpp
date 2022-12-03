#include "game.h"

void Bonus::draw_bonus(){
    mvaddch(position.getY(), position.getX(), getSprite());
}

void Bonus::erase_bonus() {
    mvaddch(position.getY(), position.getX(), ' ');
}

void Bonus::move_bonus(int offset) {
    position.setX(position.getX() - offset);
}

void drawBonuses(Bonus* b) {
    b -> draw_bonus();
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
        Space_Object bonuspos(field.getFieldWidth() - 2, 1 + rand() % field.getFieldHeight());
        bonuses.push_back(new Bonus(bonus, bonuspos));
   }
    for (int i = 0; i < bonuses.size(); i++)
        drawBonuses(bonuses[i]);
}

void Bonus::set_effect(Spaceship spaceship, Asteroids_Manager all_asts, Gun gun, Game game, char type, int gun_mode) {
    switch (type) {
        case '1': spaceship.setHeath(spaceship.getHealt()+1); // int extra_life;
            break;
        case '2': spaceship.setHeath(spaceship.getHealt()+6); // int invulnerability;
            break;
        case '3': gun.gun_manager(spaceship.getPos(), gun_mode, 1); // int burst_shot;
            break;
        case '4': game.setScore(game.getScore() * 2); // int score_multiplier;
            break;
        case '5': all_asts.setVelocity(1e6);// int asteroid_slowdown;
            break;
        case '6': all_asts.setVelocity(1e4);// int asteroid_acceleration;
            break;
        case '7': gun.gun_manager(spaceship.getPos(), 0, 0);// int gun_disabling;
            break;
        }
}
