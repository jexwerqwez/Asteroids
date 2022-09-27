#include "asteroids.h"
using namespace std;

int main (void) {
    Game game;
    game.play();
    int height = 21, width = 20;
    int quit = 0;
    int x = 5, y = height/2;
    Space_Object shippos(x, y);
    Space_Object astpos(10, 10);
    char shipsprite = '>';
    vector<vector<char>> asteroid = {
        {'*', '*', '*'},
        {'*', '*', ' '},
        {'*', '*', '*'}
    };
    Asteroids *asts = new Asteroids(asteroid, astpos);
    Spaceship spaceship(shipsprite, shippos);
    Field bord(height, width);
    Asteroids_Manager manage(bord);
    bord.draw_field();
    //ViewModule drawship();
    while (1) {
        int command;
        command = getch();
        spaceship.erase_spaceship(x, y);
        manage.Update();
        switch (command) {
            case 'd': {
                x = ( x == width - 1 ) ? 0 : x + 1;
                spaceship.setX(x);
                break;
            }
            case 'a': {
                x = ( x == 0) ? 0 : x - 1;
                spaceship.setX(x);
                break;
            }
            case 'w': {
                y = ( y == 1) ? height - 1 : y - 1;
                spaceship.setY(y);
                break;
            }
            case 's': {
                y = ( y == height - 1 ) ? 1 : y + 1; 
                spaceship.setY(y);
                break;
            }
            // case 'r': {
            //     gun_mode = 1;
            //     x_gun = x;
            //     y_gun = y + 1;
            //     g.setX(x_gun);
            //     g.setY(y_gun);
            // }
            // case 'p': {
            //     refresh();
            //     if (getchar() == 'q') quit = 1;
            // }
            case 'q': {
                raw();
                quit = 1;
                break;
            }
        }
        spaceship.draw_spaceship(x, y);
        vector<Asteroids*> all_asts = manage.getAsters();
        if (quit){
            curs_set(1);
            nocbreak();
            endwin();
            break;
        }
    }
    return 0;
}
