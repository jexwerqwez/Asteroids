#include "asteroids.h"

Game::Game(string file) {
    filename = file;
    initscr();
    curs_set(0);
    noecho();
    clear();
    refresh();
    cbreak();
    timeout(140);
}

void Game::menu() {
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
    int x = 5, y = height/2;
    int x_gun = x, y_gun = y;
    int gun_mode = 0;
    Space_Object astpos(10, 10);
    Space_Object shippos(x, y);
    Space_Object shotpos(x_gun,y_gun);
    char shipsprite = '>';
    char shotsprite = {'-'};
    vector<vector<char>> asteroid = {
        {'*', ' ',},
        {'*', '*',},
    };
    Asteroids *asts = new Asteroids(asteroid, astpos);
    // Gun *shots = new Gun(gunsprite, gunpos);
    Shot shot(shotsprite, shotpos);
    Field bord(height, width);
    Spaceship spaceship(shipsprite, shippos);
    Asteroids_Manager manage(bord);
    Gun gun(bord);
    bord.draw_field();
    while (1) {
        int command;
        command = getch();
        spaceship.erase_spaceship();
        manage.asts_manage();
        switch (command) {
            case 'd': {
                if (bord.object_inside(spaceship.getPos()) && (spaceship.getPos().getX() < width - 2))
                    spaceship.moveHorizontal(1);
                break;
            }
            case 'a': {
                if (bord.object_inside(spaceship.getPos()) && (spaceship.getPos().getX() > 1))
                    spaceship.moveHorizontal(-1);
                break;
            }
            case 'w': {
                if (bord.object_inside(spaceship.getPos()) && (spaceship.getPos().getY() > 1))
                    spaceship.moveVertical(-1);
                break;
            }
            case 's': {
                if (bord.object_inside(spaceship.getPos()) && (spaceship.getPos().getY() < height - 2))
                    spaceship.moveVertical(1);
                break;
            }
            case 'r': {
                gun_mode = (gun_mode == 1) ? 0: 1;
                break;
            }
            case 'q': {
                raw();
                quit = 1;
                break;
            }
            default: {
                break;
            }
        }
        gun.gun_manager(spaceship.getPos(), gun_mode);
        spaceship.draw_spaceship();
        vector<Asteroids*> all_asts = manage.getAsters();
        vector<Shot*> all_shots = gun.getShots();
        for (int i = 0; i < all_asts.size(); i++) {
            for (int j = 0; j < asts->getWidth(); j++) {
                for(int k = 0; k < asts->getHeight(); k++) {
                    Space_Object offset(j, k);
                    if (all_asts.at(i)->getPos()+ offset == spaceship.getPos())
                        quit = 1;
                    for (int l = 0; l < all_shots.size(); l++) {
                        if (all_asts.at(i)->getPos() + offset == all_shots.at(l)->getPos()) {
                            manage.destruct_asteroid(i);
                            gun.destruct_shot(l);
                        }
                    }
                }
            }
        }
        refresh();
        if (quit){
            gameover(height, width);
            break;
        }
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
            break;
        }
        if (start) {
            clear();
            play(height, width);
            break;
        }
    }
}

void Game::print_info(int height, int width, char* str) {
    move(height/2-3, width/2-5);
    printw("###########");
    move(height/2-2, width/2-4);
    printw("%s", str);
    move(height/2-1, width/2-5);
    printw("###########");
    move(height/2, width/2-7);
    printw("Press q to quit");
}