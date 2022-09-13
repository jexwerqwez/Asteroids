#include <iostream>
#include <ncurses.h>
#include "asteroids.h"
using namespace std;

int main (void) {
    int quit = 0, signal = 0, gun_mode = 0;
    int x = 1, y = 5, x_gun = 0, y_gun = 0;
    int height = 10, width = 14;
    Field f(height, width);
    Spaceship s(x, y);
    Gun g(x_gun, y_gun);
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    timeout(40);
    f.init_field(1, s.getX(), s.getY(), gun_mode, 2, g.getX(), g.getY());
    f.draw_field('*', '>', '-');
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
                y = ( y == width - 1 ) ? 0 : y + 1;
                s.setY(y);
                signal = 1;
                break;
            }
            case 'a': {
                y = ( y == 0) ? width - 1 : y - 1;
                s.setY(y);
                // signal = 2;
                break;
            }
            case 'w': {
                x = ( x == 0) ? height - 1 : x - 1;
                s.setX(x);
                // signal = 3;
                break;
            }
            case 's': {
                x = ( x == height - 1 ) ? 0 : x + 1; 
                s.setX(x);
                // signal = 4;
                break;
            }
            case 'r': {
                gun_mode = 1;
                x_gun = x;
                y_gun = y + 1;
                g.setX(x_gun);
                g.setY(y_gun);
            }
        }
        if (quit) break;
        clear();
        if (gun_mode) {
            y_gun = (y_gun >= width - 1) ? gun_mode = 0 : y_gun + 1;
            g.setY(y_gun);
        }
        f.init_field(1, s.getX(), s.getY(), gun_mode, 2, g.getX(), g.getY());
        f.draw_field('*', '>', '-');
        printw("g(%d;%d)", g.getX(), g.getY());
    }
    curs_set(1);
    nocbreak();
    endwin();
    return 0;
}
