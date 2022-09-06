#include "asteroids.h"

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
/**
 * @brief вывод поля
 * @param width ширина поля
 * @param height высота поля 
 * @param matrix матрица ..
 * @param ship значок корабля
*/
void Field::draw_field(int width, int height, int **matrix, char ship, 
                        int ship_signal, char gun, char gun_signal) {
    Spaceship s(0, 0);

    for (int i = 0; i < getmaxx(stdscr); i++) {
        for (int j = 0; j < getmaxy(stdscr); j++) {
            if (matrix[i][j] == 1) {printw("%c", s.draw_spaceship(ship_signal));
            } else if (matrix[i][j] == 2) {printw("%c", s.gun());
            } else {
                printw("%c", ' ');
            }
        }
        if (i != getmaxx(stdscr) - 1) printw("\n");
    } 
}

void Field::init_field(int **matrix, int object) {
    for (int i = 0; i < getmaxx(stdscr); i++) {
        for (int j = 0; j < getmaxy(stdscr); j++) {
            matrix[i][j] = object != 0;
        }
    }
}

void Field::next_position(int **matrix) {
    
}