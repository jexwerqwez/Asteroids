#include "asteroids.h"

bool Field::object_inside(Space_Object object) {
    return object.getX() >= 0 && object.getX() <= width &&
            object.getY() >= 0 && object.getY() <= height;
}

void Field::draw_field() {
    move(0,0);
    for(int i = 0; i < height; i++) {
        printw("#\n");
    }
    move(0, 1);
    for(int i = 0; i < width; i++) {
        printw("#");
    }
    move(height-1, 1);
    for(int i = 0; i < width; i++) {
        printw("#");
    }
    for(int i = 1; i < height; i++) {
        move(i, width);
        printw("#");
    }
}

Game::Game() {
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    clear();
    refresh();
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
    Gun gun(gunsprite, gunpos);
    Field bord(height, width);
    Spaceship spaceship(shipsprite, shippos);
    Asteroids_Manager manage(bord);
    bord.draw_field();
    while (1) {
        int command;
        command = getch();
        spaceship.erase_spaceship(x, y);
        gun.erase_shot(x_gun-1, y_gun);
        manage.asts_manage();
        if (gun_mode) {
            gun.draw_shot(x_gun, y_gun);
            x_gun++;
        }
        switch (command) {
            case 'd': {
                if (bord.object_inside(shippos))
                    spaceship.moveHorizontal(1);
                else
                    spaceship.moveHorizontal(-1);
                break;
            }
            case 'a': {
                    spaceship.moveHorizontal(-1);
                break;
            }
            case 'w': {
                    spaceship.moveVertical(-1);
                break;
            }
            case 's': {
                    spaceship.moveVertical(1);
                break;
            }
            case 'r': {
                gun_mode = 1;
                x_gun = x;
                y_gun = y;
                break;
            }
            case 'q': {
                raw();
                quit = 1;
                break;
            }
        }
        spaceship.draw_spaceship(x, y);
        vector<Asteroids*> all_asts = manage.getAsters();
        //printw("%d", (spaceship.getPos()).getX());
        // for (int i = 0; i < all_asts.size(); i++) {
        //     for (int j = 0; j < asts->getWidth(); j++) {
        //         for(int k = 0; k < asts->getHeight(); k++) {
        //             Space_Object offset(j, k);
        //             if (all_asts.at(i)->getPos() == spaceship.getPos() + offset)
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