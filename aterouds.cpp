#include <iostream>
#include <ncurses.h>
#include "asteroids.h"
using namespace std;

int main (void) {
    Game game;
    int quit = 0, signal = 0, gun_mode = 0;
    int x = 1, y = 5, x_gun = 0, y_gun = 0;
    int height = 10, width = 14;
    char spaceship = '>', asteroid = '@', shot = '-';
    Field previous(height, width);
    Field next(height, width);
    Spaceship s(x, y);
    Gun g(x_gun, y_gun);
    Asteroid ast(4, 4);
    int** aster = ast.construct_asteroid(width, height);
    game.run();
    next.init_field(2, s.getX(), s.getY(), gun_mode, 3, g.getX(), g.getY(), aster, 4, 4);
    previous.init_field(2, s.getX(), s.getY(), gun_mode, 3, g.getX(), g.getY(), aster, 4, 4);
    next.draw_field(asteroid, spaceship, shot);
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
                break;
            }
            case 'a': {
                y = ( y == 0) ? 0 : y - 1;
                s.setY(y);
                break;
            }
            case 'w': {
                x = ( x == 0) ? height - 1 : x - 1;
                s.setX(x);
                break;
            }
            case 's': {
                x = ( x == height - 1 ) ? 0 : x + 1; 
                s.setX(x);
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
        if (quit) {
            game.stop();
            break;
        }
        clear();
        if (gun_mode) {
            y_gun = (y_gun >= width - 1) ? gun_mode = 0 : y_gun + 1;
            g.setY(y_gun);
        }
        gun_mode = next.init_field(2, s.getX(), s.getY(), gun_mode, 3, g.getX(), g.getY(), aster, 4, 4);
        next.draw_field(asteroid, spaceship, shot);
    }
    return 0;
}
