#include "game.h"

struct timeval tv1, tv2, dtv;
struct timezone tz;
void time_start() {
    gettimeofday(&tv1, &tz);
}
long time_stop() {
    gettimeofday(&tv2, &tz);
    dtv.tv_sec = tv2.tv_sec - tv1.tv_sec;
    dtv.tv_usec = tv2.tv_usec - tv1.tv_usec;
    if(dtv.tv_usec < 0) {
        dtv.tv_sec--;
        dtv.tv_usec+=1000000;
    }
    return (dtv.tv_sec*1000+dtv.tv_usec/1000);
}

void Game::play(int height, int width, Time time, int hard) {
    int quit = 0;
    int command = 0;
    int x = 5, y = height/2;
    int x_gun = x, y_gun = y;
    int gun_mode = 0;
    Space_Object astpos(10, 10);
    Space_Object shippos(x, y);
    Space_Object shotpos(x_gun,y_gun);
    Space_Object bonuspos(0, 0);
    char bonussprite = '0';
    Bonus bonus(bonussprite, bonuspos);
    char shipsprite = '>';
    char shotsprite = {'-'};
    vector<vector<char>> asteroid = {
        {'*', ' ',},
        {'*', '*',},
    };
    Asteroids *asts = new Asteroids(asteroid, astpos, 1+rand()%2);
    Bonus *bonuses = new Bonus(bonussprite, bonuspos);
    Shot shot(shotsprite, shotpos);
    Field bord(height, width);
    Spaceship spaceship(1, shipsprite, shippos);
    Asteroids_Manager manage(bord, 1e5);
    Bonus_Manager bonus_manage(bord);
    Gun gun(bord);
    bord.draw_field();
    timeout(3);
    clock_t t0 = clock();
    while (1) {
        score = 0;
        raw();
        command = getch();
        spaceship.erase_spaceship();
        manage.asts_manage();
        spaceship.change_position(command, bord);
        bonus_manage.bonus_manager(bonuspos, 1);
        switch(command) {
            case 'r': {
                gun_mode = (gun_mode == 1) ? 0: 1;
                break;
            }
        }
        gun_mode = gun.gun_manager(spaceship.getPos(), gun_mode, 0);
        spaceship.draw_spaceship();
        vector<Asteroids*> all_asts = manage.getAsters();
        vector<Shot*> all_shots = gun.getShots();
        vector<Bonus*> all_bonuses = bonus_manage.getBonuses();
        for (int i = 0; i < all_asts.size(); i++) {
            for (int j = 0; j < asts->getWidth(); j++) {
                for(int k = 0; k < asts->getHeight(); k++) {
                    Space_Object offset(j, k);
                    if (all_asts.at(i)->getPos()+ offset == spaceship.getPos())
                        spaceship.setHeath(spaceship.getHealt()-1);
                    for (int l = 0; l < all_shots.size(); l++) {
                        if (all_asts.at(i)->getPos() + offset == all_shots.at(l)->getPos()) {
                            all_asts.at(i)->setHeath(all_asts.at(i)->getHealt()-1);
                            all_shots.at(l)->erase_shot();
                            setScore(getScore()+1);
                            gun.destruct_shot(l);
                            if(all_asts.at(i)->getHealt() == 0) {
                                all_asts.at(i)->erase_asteroid();
                                manage.destruct_asteroid(i);
                                setScore(getScore()+3);
                            }
                        }
                    }
                    for (int m = 0; m < all_bonuses.size(); m++) {
                        if (all_bonuses.at(m)->getPos() == spaceship.getPos()) {
                            all_bonuses.at(m)->set_effect(spaceship, manage, gun, *this, all_bonuses.at(m)->getSprite(), gun_mode);
                            all_bonuses.at(m)->erase_bonus();
                            bonus_manage.destruct_bonus(m);
                        }
                    }
                }
            }
        }
        usleep(hard);
        if(spaceship.getHealt() == 0)
            quit = 1;
        move(height, width/2-10);
        clock_t t1 = clock();
        printw("SCORE: %d\tHEALT: %d", getScore(), spaceship.getHealt());
        move(height+1, width/2-10);
        printw("time: %lf", (double)(t1-t0) / CLOCKS_PER_SEC);
        gun_mode = 0;
        refresh();
        if (quit) {
            Finish finish(bord, filename, settings);
            finish.processing(bord);
            break;
        }
    }
}
