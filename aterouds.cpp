#include <iostream>
#include <ncurses.h>
#include "asteroids.h"
using namespace std;

int main (void) {
    srand(time(NULL));
    Game game;
    int quit = 0, signal = 0, gun_mode = 0;
    int x = 1, y = 5, x_gun = 0, y_gun = 0;
    int height = 10, width = 20;
    int x_ast = rand() % height, y_ast = width - 1;
    char spaceship = '>', asteroid = '@', shot = '-';
    Field f(height, width);
    Spaceship s(x, y);
    Gun g(x_gun, y_gun, 0.8);
    int size = 2;
    Asteroid *ast = new Asteroid[size];
    // Asteroid ast(0, 0, 0.8);
    // int** aster = ast.construct_asteroid(width, height);
    for (int i = 0; i < size; i++) {
        
    }
    spaceshippos sp = {2, s.getX(), s.getY()};
    gunpos gp = {gun_mode, 3, g.getX(), g.getY()};
    asteroidpos ap = {aster[], x_ast, y_ast};
    game.run();
    f.init_field();
    f.draw_field(asteroid, spaceship, shot);
    while (1) {
        int command;
        command = getch();
        switch (command) {
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
            case 'p': {
                refresh();
                if (getchar() == 'q') quit = 1;
            }
            case 'q': {
                raw();
                quit = 1;
                break;
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
        printw("%d;%d\n", sp.s_x, sp.s_y);
        sp = {2, s.getX(), s.getY()};
        gp = {gun_mode, 3, g.getX(), g.getY()};
        y_ast = (y_ast < 0) ? y_ast = 0: y_ast;
        ap = {aster, x_ast, y_ast--};
        gun_mode = f.set_objects(sp, gp, ap);
        f.draw_field(asteroid, spaceship, shot);
    }
    return 0;
}
