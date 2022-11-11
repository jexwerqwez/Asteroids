#include "base.h"
#include "game.h"

int main (int argc, char* argv[]) {
    initscr();
    curs_set(0);
    noecho();
    refresh();
    cbreak();
    start_color();
    clear();
    init_pair(1, COLOR_WHITE, 0);
    init_pair(2, COLOR_BLUE, 0);
    wattrset(stdscr, COLOR_PAIR(1));
    Settings settings;
    string filename = argv[1];
    settings.parser(settings, filename);
    Field field(settings.height, settings.width);
    Start start(field, filename, settings);
    start.processing(field);
    return 0;
}
