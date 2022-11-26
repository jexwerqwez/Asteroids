#include "game.h"
#define START 3
#define FINISH 3
#define SETTING 4

const char* start_set[START] = {"Play", "Settings", "Quit"};
const char* setting_set[SETTINGS] = {"Continue", "Difficulty", "Field", "Quit"};
const char* difficulty_set[START] = {"Easy", "Norm", "Hard"};
const char* finish_set[FINISH] = {"Replay", "Settings", "Quit"};

void Menu::print_info(int height, int width, const char* str) {
    move(height/2-3, width/2-5);
    printw("###########");
    move(height/2-2, width/2-4);
    printw("%s", str);
    move(height/2-1, width/2-5);
    printw("###########");
}

int Menu::choices(int height, int width, Time time, Field f, int mode) {
    unsigned choice = 0, gamemode = 0;
    int start = 0, settings = 0, quit = 0, hard = 1e5;
    int shift = 3, items = 3;
    const char** array;
    keypad(stdscr, true);
        switch (mode)
        {
        case 1:
            array = start_set;
            break;
        case 2:
            array = setting_set;
            items = 4;
            break;
        case 3:
            array = (items == 4) ? setting_set : finish_set;
            break;
        case 4:
            array = (items == 4) ? finish_set : NULL;
            break;
        }
    while (1) {
        for(int i = 0; i < items; i++) {
            if (i == choice)
                mvaddch(height/2+i, width/2-shift-2, '>');
            else
                mvaddch(height/2+i, width/2-shift-2, ' ');
            move(height/2+i, width/2-shift);
            printw("%s", array[i]);
        }
        switch ( getch() ) {
            case KEY_UP:
                if ( choice )
                    choice--; 
                break;
            case KEY_DOWN:
                if ( choice != 3 )
                    choice++;
                break;
            case 10:
                if(choice == 0) {
                    start = 1;
                } else if (choice == 1) {
                    if (items == 4) {
                        (gamemode == 2) ? gamemode = 0 : gamemode += 1;
                        move(height/2 + 1, width/2+2);
                        printw(" ");
                        printw("\t%s", difficulty_set[gamemode]);
                    } else {
                        settings = 1;
                    }
                } else if (choice == 2) {
                    if (items == 4) {
                        move(height/2 + 2, width/2+2);
                        printw("\tKEKw");
                    } else {
                        quit = 1;
                    }
                } else if (choice == 3) {
                    quit = 1;
                }
                break;
        }
        switch (gamemode)
        {
        case 0:
            hard = 3e5;
            break;
        case 1:
            hard = 1e5;
            break;
        case 2:
            hard = 5e4;
            break;
        default:
            break;
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
            game.play(height, width, time, hard);
            break;
        }
        if (settings && mode != 2) {
            clear();
            Settings_Menu setts(f);
            setts.processing(f);
            break;
        }
    }
    return 0;
}

void Start::processing(Field f) {
    COLOR_PAIR(1);
    Time time;
    f.draw_field();
    int height = f.getFieldHeight()+2, width = f.getFieldWidth() + 1;
    print_info(height, width, "ASTEROIDS");
    choices(height, width, time, f, 1);
}

void Finish::processing(Field f) {
    Time time;
    int height = f.getFieldHeight() + 2, width = f.getFieldWidth() + 1;
    f.draw_field();
    print_info(height, width, "GAME OVER");
    choices(height, width, time, f, 3);
}

void Settings_Menu::processing(Field f) {
    Time time;
    int height = f.getFieldHeight() + 2, width = f.getFieldWidth() + 1;
    f.draw_field();
    print_info(height, width, "SETTINGS");
    int regime = choices(height, width, time, f, 2);
    if (regime)
        clear();
}