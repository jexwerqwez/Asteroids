#include "../includes/base.h"
#include "../includes/game.h"

int main(int argc, char *argv[]) {
  initscr();
  curs_set(0);
  noecho();
  start_color();
  clear();
  init_pair(10, COLOR_WHITE, COLOR_RED);
  init_pair(9, COLOR_WHITE, COLOR_BLUE);
  init_pair(8, COLOR_WHITE, COLOR_WHITE); // bord
  init_pair(7, COLOR_YELLOW, 0);
  init_pair(6, COLOR_MAGENTA, 0);
  init_pair(5, COLOR_GREEN, 0);
  init_pair(3, COLOR_WHITE, 0); // text, shot
  init_pair(2, COLOR_BLUE, 0);  // meteor 1
  init_pair(4, COLOR_RED, 0);   // spaceship
  init_pair(1, COLOR_CYAN, 0);  // meteor 2
  wattrset(stdscr, COLOR_PAIR(3) | A_BOLD);
  refresh();
  Settings settings;
  string filename;
  if (argc < 2)
    filename = "settings";
  else
    filename = argv[1];
  settings.parser(settings, filename);
  Field field(settings.height, settings.width);
  Start start(field, filename, settings);
  start.processing(settings, &field);
  curs_set(1);
  nocbreak();
  endwin();
  return 0;
}
