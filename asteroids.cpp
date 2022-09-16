#include "asteroids.h"

Field::Field() {
    height = width = 1; 
    field = new int*[height]; 
    for(int i = 0; i < 1; i++) {
        field[i] = new int[width];
    }
};

Field::Field(int h, int w) { 
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

void Field::draw_field(char asteroid, char spaceship, char shot) {
    printw("==============\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (field[i][j] == 2) {printw("%c", spaceship);
            } else if (field[i][j] == 3) {printw("%c", shot);
            } else if (field[i][j] == 1) {printw("%c", asteroid);
            } else { printw("%c", ' '); }
        }
        printw("\n");
    }
    printw("==============\n");
}
/**
 * @brief заполнение поля элементами
 * @param s значение космического корабля (2)
 * @param s_x координата х космического корабля
 * @param s_y координата у космического корабля
 * @param gm gun mode включена(1)/выключена(0)
 * @param g значение выстрела (3)
 * @param g_x координата х выстрела
 * @param g_y координата у выстрела
 * @param a матрица астероида
 * @param a_x координата х астероида
 * @param a_y координата у астероида
 */
int Field::init_field(int s, int s_x, int s_y, int gm, int g, int g_x, int g_y,
                        int** asteroid, int a_x, int a_y) {
    int k = 0;
    int l = 0;
    int flag = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            field[i][j] = 0;
            if (gm == 1)
                field[g_x][g_y] = g;
            field[s_x][s_y] = s;
            if (j == a_y && i == a_x) {
                for(l; l < height/3; l++) {
                    for(k; k < width/3; k++)
                        field[i][j++] = asteroid[l][k];
                j = a_y;
                i++;
                }
            }
        }
    }
    return gm;
}

int Gun::shot(int signal, int x, int y) {
    if (signal == 1) {
        return 0;
    }
    return 1;
}

void Field::compare_position(int **prev_matrix, int **next_matrix) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
        }
    } 
}

void Game::run() {
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    timeout(240);
}

void Game::stop() {
    curs_set(1);
    nocbreak();
    endwin();
}

int** Asteroid::construct_asteroid(int width, int height) {
    srand(time(NULL));
    int ast_width = width/3;
    int ast_height = height/3;
    int** ast = new int*[ast_height]; 
    for(int i = 0; i < ast_height; i++) {
        ast[i] = new int[ast_width];
    }
    for(int i = 0; i < ast_height; i ++) {
        for(int j = 0; j < ast_width; j++) {
            ast[i][j] = rand() % 2;
        }
    }
    return ast;
}