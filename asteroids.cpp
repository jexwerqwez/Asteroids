#include "asteroids.h"

//////////// FIELD CLASS ////////////
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

void Field::init_field() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            field[i][j] = 0;
}

void Field::draw_board() {
    for(int i = 0; i < width; i++)
        printw("=");
    printw("\n");
}

void Field::draw_field(char asteroid, char spaceship, char shot) {
    printw("\n");
    draw_board();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (field[i][j] == 2) {printw("%c", spaceship);
            } else if (field[i][j] == 3) {printw("%c", shot);
            } else if (field[i][j] == 1) {printw("%c", asteroid);
            } else { printw("%c", ' '); }
        }
        printw("\n");
    }
    draw_board();
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
 * @param a матрица астероида (1/0)
 * @param a_x координата х астероида
 * @param a_y координата у астероида
 */

int Field::set_objects(struct spaceshippos sp, struct gunpos gp, struct asteroidpos ap) {
    int flag = 0;
    int counter = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (gp.gun_mode == 1) {
                field[gp.g_x][gp.g_y] = gp.g;
            }
            if(j == ap.a_y && i == ap.a_x) {  // если при отрисовке наткнулись на астероид
                i = set_asteroid(ap.a_x, ap.a_y, ap);
            }
            field[sp.s_x][sp.s_y] = sp.s;
            field[i][j] = 0;
        }
    }
    return gp.gun_mode;
}

int Field::set_asteroid(int start_x, int start_y, struct asteroidpos ap) {
    int x = start_x;
    int y = start_y;
    static int start = 0;
    if (start_y == 0)
        start++;
    for(int l = 0; l < height/3 && x < height; l++) {  // отрисовка астероида по х
        for(int k = start; k < width/3 && y < width; k++) {  // по у
            field[x][y++] = ap.asteroid[l][k];  // сначала заполним столбцами астероида
        }
        for(int n = 0; n < width && y < width; n++) { // дозаполнение
            field[x][y++] = 0;
        }
        y = start_y; // возвращение
        x = ( x > height - 2) ? height - 1 : x + 1; // прорисовка в пределах поля
    }
    return x;
}

//////////// GUN CLASS ////////////

int Gun::shot(int signal, int x, int y) {
    if (signal == 1) {
        return 0;
    }
    return 1;
}

//////////// GAME CLASS ////////////

void Game::run() {
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    timeout(740);
}

void Game::stop() {
    curs_set(1);
    nocbreak();
    endwin();
}

//////////// ASTEROID CLASS ////////////
int** Asteroid::construct_asteroid(int width, int height) {
    srand(time(NULL));
    int ast_width = width/3;
    int ast_height = height/3;
    int** ast = new int*[ast_height]; 
    for(int i = 0; i < ast_height; i++) {
        ast[i] = new int[ast_width];
    }
    // конструируем
    for(int i = 0; i < ast_height; i ++) {
        for(int j = 0; j < ast_width; j++) {
            ast[i][j] = rand() % 2;
        }
    }
    // заполняем пустоту
    for(int i = 0; i < ast_height - 1; i ++) {
        for(int j = 0; j < ast_width - 1; j++) {
            if (ast[i][j] != ast[i+1][j+1]) {
                ast[i+1][j+1] = 1;
                int fill_pos = rand() % 2;
                if (fill_pos == 1)
                    ast[i][j+1] = 1;
                else
                    ast[i+1][j] = 1;
            }
        }
    }
    return ast;
}
