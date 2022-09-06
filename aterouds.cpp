#include <iostream>
#include <ncurses.h>
#include "asteroids.h"
using namespace std;

int main (void) {
    int x = 0;
    int y = 2;
    int x_gun = x;
    int y_gun = y;
    int quit = 0;
    int signal = 0;
    int gun_signal = 0;
    Spaceship s(x, y);
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    timeout(40);
    while (1) {
        int command;
        command = getch();
        switch (command) {
            case 'q': {
                raw();
                quit = 1;
                break;
            }
            case 'd': {
                x++;
                signal = 1;
                break;
            }
            case 'a': {
                x--;
                signal = 2;
                break;
            }
            case 'w': {
                y--;
                signal = 3;
                break;
            }
            case 's': {
                y++;
                signal = 4;
                break;
            }
            case 'r': {
                gun_signal = 1;
                if (signal == 1) {
                    x_gun = x+1;
                    y_gun = y;
                } else if (signal == 2) {
                    x_gun = x-1;
                    y_gun = y;
                } else if (signal == 3) {
                    x_gun = x;
                    y_gun = y-1;
                } else if (signal == 4) {
                    x_gun = x;
                    y_gun = y+1;
                }
                break;
            }
        }
        if (quit) break;
        clear();
        if (gun_signal == 1) {
            while(y_gun != y+3) {
                move(y_gun, x_gun);
                timeout(700);
                printw("%c", s.gun());
                y_gun++;
            }
        }
        move(y,x);
        printw("%c", s.draw_spaceship(signal));
    }
    curs_set(1);
    nocbreak();
    endwin();
    return 0;
}


char Spaceship::draw_spaceship(int signal) {
    if (signal == 1) {
        return '>';
    } else if (signal == 2) {
        return '<';
    } else if (signal == 3) {
        return '^';
    } else if (signal == 4) {
        return 'v';
    } else {
        return '>';
    }
}

