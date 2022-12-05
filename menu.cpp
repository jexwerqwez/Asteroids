#include "game.h"
#define START 3
#define FINISH 3
#define SETTING 4

const char* start_set[START] = {"Play", "Settings", "Quit"};
const char* setting_set[SETTINGS] = {"Continue", "Difficulty", "Field", "Quit"};
const char* difficulty_set[START] = {"Easy", "Norm", "Hard"};
const char* finish_set[FINISH] = {"Replay", "Settings", "Quit"};
const char* field_set[START] = {"Height", "Width", "Back"};

void Menu::print_info(Field* f, int height, int width, const char* str, int mode) {
    clear();
    attrset(A_BOLD | COLOR_PAIR((mode == 1) ? 9 : 3));
    field.draw_field(mode);
    move(height/2-3, width/2-5);
    for(int i = 0; i < strlen(str)+2; i++)
        addch('=');
    move(height/2-2, width/2-4);
    printw("%s", str);
    move(height/2-1, width/2-5);
    for(int i = 0; i < strlen(str)+2; i++)
        addch('=');
}

int Menu::choices(Settings set, Field f, int mode) {
    unsigned choice = 0, gamemode = 0;
    int start = 0, settings = 0, quit = 0, hard = 1e5;
    int shift = 3, items = 3;
    const char** array;
    int height = f.getFieldHeight(), width = f.getFieldWidth();
    int newheight = f.getFieldHeight(), newwidth = f.getFieldWidth();
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
                            int j = 0;
                            int ch;
                            move(height/2 + 2, width/2+2);
                            Settings_Menu setts(f);
                            setts.field_menu(set, f);
                            // while(ch = getch()) {
                            //     if (ch == KEY_DOWN || ch == KEY_UP)
                            //         break;
                            //     else {
                            //         switch (ch)
                            //         {
                            //         case 10:
                            //             (j == 1) ? j = 0 : j += 1;
                            //         case '=':
                            //             move(height/2 + 2, width/2+2);
                            //             printw(" ");
                            //             printw("%s%d", info_set[j], (j == 0) ? newheight++ : newwidth++);
                            //             break;
                            //         case '-':
                            //             move(height/2 + 2, width/2+2);
                            //             printw(" ");
                            //             printw("%s%d", info_set[j], (j == 0) ? newheight-- : newwidth--);
                            //             break;
                            //         }
                            //     }
                            // }
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
                height = newheight;
                width = newwidth;
                game.play(height, width, set);
                break;
            }
            if (settings && mode != 2) {
                clear();
                Settings_Menu setts(f);
                setts.processing(set, &f);
                break;
            }
        }
    //}
    return 0;
}

void Start::processing(Settings set, Field* f) {
    COLOR_PAIR(3);
    int height = (*f).getFieldHeight(), width = (*f).getFieldWidth();
    print_info(f, height, width, "ASTEROIDS", 0);
    choices(set, *f, 1);
}

void Finish::processing(Settings set, Field* f) {
    int height = (*f).getFieldHeight(), width = (*f).getFieldWidth();
    while(!(getch() == 10)) {
        attroff(A_BLINK);
        (game.getstatus() == 1) ? print_info(f, height, width, "BLACK HOLE!", 1) : print_info(f, height, width, "GAME OVER", 0);
        move(height/2, width/2-2);
        printw("SCORE: %d", game.getScore());
        attrset(A_BLINK | COLOR_PAIR((game.getstatus() == 1) ? 9 : 3));
        move(height/2+1, width/2-8);
        printw("Press ENTER to replay");
    }
    attrset(COLOR_PAIR(3));
    print_info(f, height, width, "GAME OVER", 0);
    choices(set, *f, 3);
}

void Settings_Menu::processing(Settings set, Field* f) {
    int height = (*f).getFieldHeight(), width = (*f).getFieldWidth();
    print_info(f, height, width, "SETTINGS", 0);
    int regime = choices(set, *f, 2);
    if (regime)
        clear();
}

void Settings_Menu::field_menu(Settings set, Field f) {
    int ch;
    int newheight = f.getFieldHeight();
    int newwidth = f.getFieldWidth();
    int j = 0;
    unsigned choice = 0;
    clear();
    f.draw_field(0);
    print_info(&f, f.getFieldHeight(), f.getFieldWidth(), "FIELD", 0);
    keypad(stdscr, true);
    while(1) {
        for(int i = 0; i < 3; i++) {
            if (i == choice)
                mvaddch(f.getFieldHeight()/2+i, f.getFieldWidth()/2-3-2, '>');
            else
                mvaddch(f.getFieldHeight()/2+i, f.getFieldWidth()/2-3-2, ' ');
            move(f.getFieldHeight()/2+i, f.getFieldWidth()/2-3);
            printw("%s", field_set[i]);
            if (i == 0) printw(":\t%d", f.getFieldHeight());
            if (i == 1) printw(":\t%d", f.getFieldWidth());
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
            case 10:
                if (choice == 0 || choice == 1) {
                    while(ch =getch()) {
                        if(ch == KEY_DOWN || ch == KEY_UP)
                            break;
                        switch (ch) {
                            case 10:
                                (j == 1) ? j = 0 : j += 1;
                            case '=':
                                move(f.getFieldHeight()/2 + choice, f.getFieldWidth()/2-3);
                                //printw(" ");
                                move(f.getFieldHeight()/2 + choice, f.getFieldWidth()/2-3);
                                printw("%s", field_set[j]);
                                printw(":\t%d", (j == 0) ? newheight++ : newwidth++);
                                break;
                            case '-':
                                move(f.getFieldHeight()/2 + choice, f.getFieldWidth()/2-3);
                                //printw(" ");
                                move(f.getFieldHeight()/2 + choice, f.getFieldWidth()/2-3);
                                printw("%s", field_set[j]);
                                printw(":\t%d", (j == 0) ? newheight-- : newwidth--);
                                break;
                            }
                    }

                }
                if (choice == 2)
                    processing(set, &f);
                break;
        }
    }
}

                            // while(ch = getch()) {
                            //     if (ch == KEY_DOWN || ch == KEY_UP)
                            //         break;
                            //     else {
                            //         switch (ch)
                            //         {
                            //         case 10:
                            //             (j == 1) ? j = 0 : j += 1;
                            //         case '=':
                            //             move(height/2 + 2, width/2+2);
                            //             printw(" ");
                            //             printw("%s%d", info_set[j], (j == 0) ? newheight++ : newwidth++);
                            //             break;
                            //         case '-':
                            //             move(height/2 + 2, width/2+2);
                            //             printw(" ");
                            //             printw("%s%d", info_set[j], (j == 0) ? newheight-- : newwidth--);
                            //             break;
                            //         }
                            //     }
                            // }
