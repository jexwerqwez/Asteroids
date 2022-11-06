#include "asteroids.h"

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

Game::Game(string file) {
    filename = file;
    initscr();
    curs_set(0);
    noecho();
    clear();
    refresh();
    cbreak();
}

void Game::menu() {
    start_color();
    settings.parser(settings, filename);
    int height = settings.height+2, width = settings.width + 1;
    int start = 0;
    Field f(height, width);
    f.draw_field();
    print_info(height, width, "ASTEROIDS");
    int quit = 0;
    while (1) {
        int command = getch();
        switch (command)
        {
            case 'p': {
                start = 1;
                break;
            }
            case 'q': {
                raw();
                quit = 1;
                break;
            }
        }
        if (quit){
            curs_set(1);
            nocbreak();
            endwin();
            break;
        }
        if (start) {
            clear();
            play(height, width);
            break;
        }
    }
}

void Game::play(int height, int width) {
    int quit = 0;
    int command = 0;
    int x = 5, y = height/2;
    int x_gun = x, y_gun = y;
    int gun_mode = 0;
    time_start();
    int s = 0, m = 0, h = 0, ms = 0;
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
    int score = 0;
    Spaceship spaceship(1, shipsprite, shippos);
    Asteroids_Manager manage(bord);
    Bonus_Manager bonus_manage(bord);
    Gun gun(bord);
    bord.draw_field();
    timeout(1);
    while (1) {
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
            case 'q': {
                raw();
                quit = 1;
                break;
            }
        }
        gun_mode = gun.gun_manager(spaceship.getPos(), gun_mode);
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
                            score += 1;
                            gun.destruct_shot(l);
                            if(all_asts.at(i)->getHealt() == 0) {
                                all_asts.at(i)->erase_asteroid();
                                manage.destruct_asteroid(i);
                                score += 3;
                            }
                        }
                    }
                    for (int m = 0; m < all_bonuses.size(); m++) {
                        if (all_bonuses.at(m)->getPos() == spaceship.getPos()) {
                            all_bonuses.at(m)->set_effect(spaceship, manage, gun, all_bonuses.at(m)->getSprite());
                            all_bonuses.at(m)->erase_bonus();
                            bonus_manage.destruct_bonus(m);
                        }
                    }
                }
            }
        }
        if(spaceship.getHealt() == 0)
            quit = 1;
        move(height, width/2-10);
        printw("SCORE: %d\tHEALT: %d", score, spaceship.getHealt());
        gun_mode = 0;
        refresh();
        if (quit){
            gameover(height, width);
            break;
        }
        timer(ms, s, m, h, height, width);
    }
}

void Game::gameover(int height, int width) {
    Field bord(height, width);
    bord.draw_field();
    print_info(height, width, "GAME OVER");
    move(height/2+1, width/2-8);
    printw("Press p to replay");
    int quit = 0;
    int start = 0;
    while (1) {
        int command = getch();
        switch (command) {
            case 'p': {
                start = 1;
                break;
            }
            case 'q': {
                raw();
                quit = 1;
                break;
            }
        }
        if (quit){
            curs_set(1);
            nocbreak();
            break;
        }
        if (start) {
            clear();
            play(height, width);
            break;
        }
    }
}

void Game::print_info(int height, int width, const char* str) {
    move(height/2-3, width/2-5);
    printw("###########");
    move(height/2-2, width/2-4);
    printw("%s", str);
    move(height/2-1, width/2-5);
    printw("###########");
    move(height/2, width/2-7);
    printw("Press q to quit");
}

void Game::timer(int ms, int s, int m, int h, int height, int width) {
    ms = time_stop();
    if (ms > 999) {
        s += 1;
        ms = 0;
        time_start();
    }
    if (s > 59) {
        m += 1;
        s = 0;
    }
    if (m > 59) {
        h += 1;
        m = 0;
    }
    move(height + 1, width/2-10);
    refresh();
    printw("%d:%02d:%02d.%03d", h, m, s, ms);
}