#include <iostream>
#include <ncurses.h>
using namespace std;

class Spaceship {
    int x;  // координаты на плоскости
    int y;
    public:
        Spaceship(int _x, int _y): x(_x), y(_y) {};  // конструктор
        int getx() {return x;};
        int gety() {return y;};
        char draw_spaceship(int signal); // отрисовка корабля
};

class Asteroid {
    int x;
    int y;
    public:
        Asteroid(int _x, int _y): x(_x), y(_y) {};
};

int main (void) {
    int x = 0;
    int y = 2;
    int quit = 0;
    Spaceship s(x, y);
    initscr();
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
                printw("%c", s.draw_spaceship(1));
                break;
            }
            case 'a': {
                x--;
                printw("%c", s.draw_spaceship(2));
                break;
            }
            case 'w': {
                y++;
                printw("%c", s.draw_spaceship(3));
                break;
            }
            case 's': {
                y--;
                printw("%c", s.draw_spaceship(4));
                break;
            }
        }
        if (quit) break;
    }
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
    } else {
        return 'v';
    }
}