#include "asteroids.h"

Game::Game() {
    initscr();
    curs_set(0);
    noecho();
    clear();
    refresh();
    cbreak();
    timeout(440);
}

void Game::menu() {
    WINDOW* wnd;
    int height = 20 + 2, width = 30 + 1;
    int start = 0;
    Field f(height, width);
    f.draw_field();
    move(height/2-1, width/2-5);
    printw("###########");
    move(height/2, width/2-4);
    printw("ASTEROIDS");
    move(height/2+1, width/2-5);
    printw("###########");
    move(height/2+2, width/2-7);
    printw("Press p to start");
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
    Space_Object gunpos(x_gun,y_gun);
    char shipsprite = '>';
    char gunsprite = {'-'};
    vector<vector<char>> asteroid = {
        {'*', ' ',},
        {'*', '*',},
    };
    Asteroids *asts = new Asteroids(asteroid, astpos);
    // Gun *shots = new Gun(gunsprite, gunpos);
    Gun gun(gunsprite, gunpos);
    Field bord(height, width);
    Spaceship spaceship(shipsprite, shippos);
    Asteroids_Manager manage(bord);
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
                gun_mode = 1;
                gun.makeShot(spaceship.getPos());
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
        if (gun_mode) {
            gun.erase_shot();
            gun.moveShot(1);
            gun.draw_shot();
        }
        spaceship.draw_spaceship();
        printw("%d", spaceship.getPos().getX());
        // vector<Asteroids*> all_asts = manage.getAsters();
        // for (int i = 0; i < all_asts.size(); i++) {
        //     for (int j = 0; j < asts->getWidth(); j++) {
        //         for(int k = 0; k < asts->getHeight(); k++) {
        //             Space_Object offset(j, k);
        //             if (all_asts.at(i)->getPos()+ offset == gun.getPos()) {
        //                 manage.destruct_asteroid(i);
        //                 gun.erase_shot();
        //                 gun.makeShot(spaceship.getPos());
        //                 gun_mode = 0;
        //             }
        //             if (all_asts.at(i)->getPos()+ offset == spaceship.getPos())
        //                 quit = 1;
        //         }
        //     }
        // }
        refresh();
        if (quit){
            curs_set(1);
            nocbreak();
            endwin();
            break;
        }
    }
}
