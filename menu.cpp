#include "game.h"


void Menu::print_info(int height, int width, const char* str) {
    move(height/2-3, width/2-5);
    printw("###########");
    move(height/2-2, width/2-4);
    printw("%s", str);
    move(height/2-1, width/2-5);
    printw("###########");
    move(height/2, width/2-7);
    printw("Press q to quit");
}

void Start::processing(Field f) {
    init_pair(1, COLOR_WHITE, 0);
    start_color();
    settings.parser(settings, filename);
    int height = settings.height+2, width = settings.width + 1;
    int start = 0;
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
            Game game;
            game.play(height, width);
            break;
        }
    }
}

void Finish::processing(Field f) {
    int height = settings.height+2, width = settings.width + 1;
    f.draw_field();
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
            Game game;
            game.play(height, width);
            break;
        }
    }
}