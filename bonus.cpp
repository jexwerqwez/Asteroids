#include "asteroids.h"

void Bonus::draw_bonus(){
    mvaddch(position.getY(), position.getX(), getSprite());
}

void Bonus::erase_bonus() {
    mvaddch(position.getY(), position.getX(), ' ');
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

void Bonus::generate_bonus(Space_Object pos) {
    position.setX(pos.getX());
    position.setY(pos.getY());
}
void Bonus_Manager::bonus_manager(Space_Object pos, int bonus_mode) {
        for (int i = 0; i < bonuses.size(); i++)
            eraseBonuses(bonuses[i]);
        int bonus_type = 1+rand()%11;
        char bonus = '0';
        switch (bonus_type) {
        case 1: bonus = '1';
            break;
        case 2: bonus = '2';
            break;
        case 3: bonus = '3';
            break;
        case 4: bonus = '4';
            break;
        case 5: bonus = '5';
            break;
        case 6: bonus = '6';
            break;
        case 7: bonus = '7';
            break;
        case 8: bonus = '8';
            break;
        case 9: bonus = '9';
            break;
        case 10: bonus = 'P';
            break;
        }
        if(rand()%100 == 6) {
            Space_Object bonuspos(rand()%field.getFieldWidth(), 1 + rand() % field.getFieldHeight());
            bonuses.push_back(new Bonus(bonus, bonuspos));
        }
        for (int i = 0; i < bonuses.size(); i++)
            drawBonuses(bonuses[i]);
}

void Bonus::set_effect(Spaceship spaceship, Asteroids_Manager all_asts, Gun gun, char type) {
    switch (type) {
        case '1': spaceship.setHeath(spaceship.getHealt()+1);
            break;
        case '2': spaceship.setHeath(spaceship.getHealt()+6);
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            break;
        case '9':
            break;
        case 'P':
            break;
        }
}

    // int extra_life;
    // int invulnerability;
    // int bullet_slowdown;
    // int bullet_acceleration;
    // int burst_shot;
    // int score_multiplier;
    // int asteroid_slowdown;
    // int asteroid_acceleration;
    // int asteroid_rain;
    // int gun_disabling;
