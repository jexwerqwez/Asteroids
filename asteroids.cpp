#include "asteroids.h"


Field::Field() {
    // printf("construct\n");
    height = width = 1; 
    field = new int*[height]; 
    for(int i = 0; i < 1; i++) {
        field[i] = new int[width];
    }
};

Field::Field(int h, int w) { 
    // printf("construct\n");
    height = h; 
    width = w; 
    field = new int*[height]; 
    for(int i = 0; i < height; i++) {
        field[i] = new int[width];
    }
};


char Spaceship::ship_direction(int signal) {
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
void Field::draw_field(char asteroid, char spaceship, char shot) {
    //printf("draw?\n");
    printw("----------------------------\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (field[i][j] == 1) {printw("%c", spaceship);
            } else if (field[i][j] == 2) {printw("%c", shot);
            } else {
                printw("%c", ' ');
            }
        }
        printw("\n");
    }
    printw("----------------------------\n");
}

void Field::init_field(int object, int x, int y) {
    // printf("initialization\n"); 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            field[i][j] = 0;
            field[x][y] = object;
        }
    }
}

// void Field::next_position(int **prev_matrix, int **next_matrix, int ship_status) {
//     for (int i = 0; i < getmaxx(stdscr); i++) {
//         for (int j = 0; j < getmaxy(stdscr); j++) {
//             next_matrix[i][j] = ship_status;
//         }
//     } 
// }