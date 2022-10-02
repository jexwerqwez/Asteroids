#include "asteroids.h"

bool Field::object_inside(Space_Object object) {
    return object.getX() >= 0 && object.getX() <= width &&
            object.getY() >= 0 && object.getY() <= height;
}

void Field::draw_field() {
    move(0,0);
    for(int i = 0; i < width; i++)
        printw("=");
    move(height, 0);
    for(int i = 0; i < width; i++)
        printw("=");  
}

Game::Game() {
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    clear();
    refresh();
    timeout(740);
}

void Game::menu() {
    WINDOW* wnd;
    int height = 21, width = 30;
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
                clear();
                play(height, width);
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
    }
}

void Game::play(int height, int width) {
    int quit = 0;
    int x = 5, y = height/2;
    int x_gun = x, y_gun = y;
    int gun_mode = 0;
    Space_Object shippos(x, y);
    char shipsprite = '>';
    Spaceship spaceship(shipsprite, shippos);

    vector<vector<char>> asteroid = {
        {'*', '*', '*'},
        {'*', '*', ' '},
        {'*', '*', '*'}
    };
    Space_Object astpos(10, 10);
    Asteroids *asts = new Asteroids(asteroid, astpos);
    
    Space_Object gunpos(x_gun,y_gun);
    char gunsprite = '-';
    Gun gun(gunsprite, gunpos);

    Field bord(height, width);
    Asteroids_Manager manage(bord);
    GunManager gmanage(bord);
    bord.draw_field();
    while (1) {
        int command;
        command = getch();
        spaceship.erase_spaceship(x, y);
        //manage.Update();
        if (gun_mode) {
            //gmanage.gunUpdate(gun_mode,spaceship);
        }
        switch (command) {
            case 'd': {
                x = ( x == width - 1 ) ? 0 : x + 1;
                spaceship.setX(x);
                break;
            }
            case 'a': {
                x = ( x == 0) ? 0 : x - 1;
                spaceship.setX(x);
                break;
            }
            case 'w': {
                y = ( y == 1) ? height - 1 : y - 1;
                spaceship.setY(y);
                break;
            }
            case 's': {
                y = ( y == height - 1 ) ? 1 : y + 1; 
                spaceship.setY(y);
                break;
            }
            case 'r': {
                gun_mode = 1;
                break;
            }
            case 'q': {
                raw();
                quit = 1;
                break;
            }
        }
        spaceship.draw_spaceship(x, y);
        refresh();
        //vector<Asteroids*> all_asts = manage.getAsters();
        if (quit){
            curs_set(1);
            nocbreak();
            endwin();
            break;
        }
    }
}