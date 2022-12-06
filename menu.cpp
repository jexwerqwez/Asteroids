#include "game.h"
#include "alphabet.h"
#define START 3
#define FINISH 3
#define SETTING 4
#define CELL_TYPE '*'

const char* start_set[START] = {"Play", "Settings", "Quit"};
const char* setting_set[SETTINGS] = {"Continue", "Difficulty", "Field", "Quit"};
const char* difficulty_set[START] = {"Easy", "Norm", "Hard"};
const char* finish_set[FINISH] = {"Replay", "Settings", "Quit"};
const char* field_set[START] = {"Height", "Width", "Back"};

int Menu::choices(Settings set, Field f, int mode) {
    unsigned choice = 0, gamemode = 0;
    int start = 0, settings = 0, quit = 0, hard = 1e5;
    int shift = 3, items = 3;
    const char** array;
    int height = f.getFieldHeight(), width = f.getFieldWidth();
    int newheight = f.getFieldHeight(), newwidth = f.getFieldWidth();
    Settings_Menu setts(f);
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
    //if (getch() == 10) {
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
                            setts.field_menu(set, &f);
                        } else {
                            quit = 1;
                        }
                    } else if (choice == 3) {
                        quit = 1;
                    }
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
                Game game(gamemode);
                game.play(f.getNewFieldHeight(), f.getNewFieldWidth(), set);
                break;
            }
            if (settings) {
                clear();
                setts.processing(set, &f);
                break;
            }
        }
    //}
    return 0;
}

void Start::processing(Settings set, Field* f) {
    clear();
    COLOR_PAIR(3);
    int height = (*f).getFieldHeight(), width = (*f).getFieldWidth();
    //print_info(f, height, width, "ASTEROIDS", 0);
    f->draw_field(0);
    print_asteroids(set, f);
    choices(set, *f, 1);
}

void Start::print_asteroids(Settings set, Field* f) {
    clear();
    f->draw_field(0);
    int x = f->getFieldWidth()/2-16;
    int y = 3;
    attrset(COLOR_PAIR(8));
    print_a(x,y,CELL_TYPE);x += 4;print_s(x,y, CELL_TYPE);x +=3;print_t(x, y, CELL_TYPE);
    x+=4;print_e(x, y, CELL_TYPE);x+=3;print_r(x, y, CELL_TYPE);x+=4;print_o(x, y, CELL_TYPE);
    x+=4;print_i(x, y, CELL_TYPE);x+=4;print_d(x, y, CELL_TYPE);x+=4;print_s(x, y, CELL_TYPE);
    attroff(COLOR_PAIR(9));
    attrset(A_BOLD);
    COLOR_PAIR(3);
}

void Settings_Menu::print_settings(Settings set, Field* f) {
    clear();
    f->draw_field(0);
    int x = f->getFieldWidth()/2-15;
    int y = 3;
    attrset(COLOR_PAIR(8));
    print_s(x,y, CELL_TYPE);x +=3;print_e(x, y, CELL_TYPE);x+=3;print_t(x, y, CELL_TYPE);
    x+=4;print_t(x, y, CELL_TYPE);x+=4;print_i(x, y, CELL_TYPE);x+=4;print_n(x, y, CELL_TYPE);
    x+=5;print_g(x, y, CELL_TYPE);x+=5;print_s(x, y, CELL_TYPE);
    attroff(COLOR_PAIR(9));
    attrset(A_BOLD);
    COLOR_PAIR(3);
}

void Settings_Menu::print_field(Settings set, Field* f) {
    clear();
    f->draw_field(0);
    int x = f->getFieldWidth()/2-8;
    int y = 3;
    attrset(COLOR_PAIR(8));
    print_f(x,y,CELL_TYPE);x += 3;print_i(x, y, CELL_TYPE);x+=4;print_e(x, y, CELL_TYPE);x+=3;
    print_l(x, y, CELL_TYPE);x+=4;print_d(x, y, CELL_TYPE);
    attroff(COLOR_PAIR(9));
    attrset(A_BOLD);
    COLOR_PAIR(3);
}

void Finish::print_blackhole(Settings set, Field* f) {
    clear();
    f->draw_field(1);
    int x = f->getFieldWidth()/2-17;
    int y = 3;
    attrset(COLOR_PAIR(8));
    print_b(x,y,CELL_TYPE);x += 4;print_l(x, y, CELL_TYPE);x+=4;print_a(x, y, CELL_TYPE);x+=4;print_c(x, y, CELL_TYPE);x+=4;
    print_k(x, y, CELL_TYPE);x+=5;print_h(x, y, CELL_TYPE);x+=4;print_o(x, y, CELL_TYPE);x+=4;print_l(x, y, CELL_TYPE);x+=4;print_e(x, y, CELL_TYPE);
    attroff(COLOR_PAIR(9));
    attrset(A_BOLD);
    COLOR_PAIR(3);
}

void Finish::print_gameover(Settings set, Field* f) {
    clear();
    f->draw_field(0);
    int x = f->getFieldWidth()/2-16;
    int y = 3;
    attrset(COLOR_PAIR(8));
    print_g(x, y, CELL_TYPE);x+=5;print_a(x,y,CELL_TYPE);x += 4; print_m(x,y,CELL_TYPE);x += 6;
    print_e(x, y, CELL_TYPE);x+=3; print_o(x, y, CELL_TYPE);x+=4;print_v(x, y, CELL_TYPE);x+=4;
    print_e(x, y, CELL_TYPE);x+=3;print_r(x, y, CELL_TYPE);
    attroff(COLOR_PAIR(9));
    attrset(A_BOLD);
    COLOR_PAIR(3);
}

void Finish::processing(Settings set, Field* f) {
    int height = (*f).getFieldHeight(), width = (*f).getFieldWidth();
    while(!(getch() == 10)) {
        attroff(A_BLINK);
        (game.getstatus() == 1) ? print_blackhole(set,f) : print_gameover(set,f);
        move(height/2, width/2-2);
        printw("SCORE: %d", game.getScore());
        attrset(A_BLINK | COLOR_PAIR((game.getstatus() == 1) ? 9 : 3));
        move(height/2+1, width/2-8);
        printw("Press ENTER to replay");
    }
    attrset(COLOR_PAIR(3));
    print_gameover(set,f);
    choices(set, *f, 3);
}

void Settings_Menu::processing(Settings set, Field* f) {
    int height = (*f).getFieldHeight(), width = (*f).getFieldWidth();
    f->draw_field(0);
    print_settings(set, f);
    int regime = choices(set, *f, 2);
    if (regime)
        clear();
}

int Settings_Menu::field_menu(Settings set, Field* f) {
    int ch;
    int newheight = (*f).getFieldHeight();
    int newwidth = (*f).getFieldWidth();
    int j = 0, flag = 1;
    unsigned choice = 0;
    clear();
    (*f).draw_field(0);
    print_field(set, f);
    keypad(stdscr, true);
    while(flag) {
        for(int i = 0; i < 3; i++) {
            if (i == choice)
                mvaddch((*f).getFieldHeight()/2+i, (*f).getFieldWidth()/2-3-2, '>');
            else
                mvaddch((*f).getFieldHeight()/2+i, (*f).getFieldWidth()/2-3-2, ' ');
            move((*f).getFieldHeight()/2+i, (*f).getFieldWidth()/2-3);
            printw("%s", field_set[i]);
            if (i == 0) printw(":\t%d", newheight);
            if (i == 1) printw(":\t%d", newwidth);
        }
        switch ( ch = getch() ) {
            case KEY_UP:
                if ( choice )
                    choice--; 
                    break;
            case KEY_DOWN:
                if ( choice != 2 )
                    choice++;
                break;
            case '=':
                move((*f).getFieldHeight()/2 + choice, (*f).getFieldWidth()/2-3);
                move((*f).getFieldHeight()/2 + choice, (*f).getFieldWidth()/2-3);
                printw("%s", field_set[j]);
                if (choice == 0) printw(":\t%d", newheight++);
                else if (choice == 1) printw(":\t%d", newwidth++);
                break;
            case '-':
                if(ch == KEY_DOWN || ch == KEY_UP) {(*f).setFieldHeight(newheight); (*f).setFieldWidth(newwidth); break;}
                move((*f).getFieldHeight()/2 + choice, (*f).getFieldWidth()/2-3);
                move((*f).getFieldHeight()/2 + choice, (*f).getFieldWidth()/2-3);
                printw("%s", field_set[j]);
                if (choice == 0) printw(":\t%d", newheight++);
                else if (choice == 1) printw(":\t%d", newwidth++);
                    break;
            case 10:
                if (choice == 2)
                    flag = 0;
                (*f).setFieldHeight(newheight); (*f).setFieldWidth(newwidth);
                break;
        }
    }
    (*f).setFieldHeight(newheight); (*f).setFieldWidth(newwidth);
    print_settings(set,f);
    return 0;
}
