#include "base.h"
#include "game.h"

int main (int argc, char* argv[]) {
    initscr();
    curs_set(0);
    noecho();
    clear();
    refresh();
    cbreak();
    Settings setts;
    string filename = argv[1];
    Field field(setts.height, setts.width);
    Start start(field, filename, setts);
    start.processing(field);
    field.draw_field();
    return 0;
}
