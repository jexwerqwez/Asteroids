#include <iostream>
#include <ncurses.h>
#include "asteroids.h"
using namespace std;

int main (void) {
    int x = 0, y = 2;
    int x_gun = x, y_gun = y;
    int quit = 0, signal = 0, gun_signal = 0;
    Spaceship spaceship(x, y);
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    int width = getmaxy(stdscr);
    int height = getmaxx(stdscr);
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
                    x_gun = x + 1;
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
            move(y_gun, x_gun);
            switch (signal)
            {
            case (1):
                x_gun++;
                break;
            case (2):
                x_gun--;
                break;
            case (3):
                y_gun--;
                break;
            case (4):
                y_gun++;
                break;
            }
            if (x_gun == getmaxx(stdscr) || y_gun == getmaxy(stdscr) ||
                    x_gun == -1 || y_gun == -1)
                gun_signal = 0;
            printw("%c", spaceship.gun());
        }
        move(y,x);
        printw("%c", spaceship.draw_spaceship(signal));
    }
    curs_set(1);
    nocbreak();
    endwin();
    return 0;
}
