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
        char gun(int x, int y) {return '@';};
};

class Asteroid {
    int x;
    int y;
    int speed;
    public:
        Asteroid(int _x, int _y, int s): x(_x), y(_y), speed(s) {};
        void draw_asteroid();
};

class Field {
    int width;
    int length;
    public:
        Field(int w, int l): width(w), length(l) {};
        void draw_field();
};

int main (void) {
    int x = 0;
    int y = 2;
    int quit = 0;
    int signal = 0;
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
                signal = 1;
                break;
            }
            case 'a': {
                x--;
                signal = 2;
                break;
            }
            case 'w': {
                y++;
                signal = 3;
                break;
            }
            case 's': {
                y--;
                signal = 4;
                break;
            }
            case 'r': {
                if (signal == 1)
                    s.gun(x+1, y);
                else if (signal == 2)
                    s.gun(x-1, y);
                else if (signal == 3)
                    s.gun(x, y+1);
                else if (signal == 4)
                    s.gun(x, y-1);
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