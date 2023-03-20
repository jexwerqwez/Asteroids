#include "../includes/alphabet.h"
#include "../includes/game.h"
#define ITEMS 4
#define TITLEPOS 5
#define CELL_TYPE '*'
#define TOP_H 55
#define TOP_W 210
#define BOT_H 20
#define BOT_W 40

const char* start_set[ITEMS] = {"Play", "Settings", "Rules", "Quit"};
const char* setting_set[ITEMS] = {"Play", "Mode", "Field", "Quit"};
const char* difficulty_set[ITEMS] = {"Easy", "Norm", "Hard", "Fuzz"};
const char* finish_set[ITEMS] = {"Replay", "Settings", "Rules", "Quit"};
const char* field_set[ITEMS] = {"Height", "Width", "Back"};
const char* mode_set[2] = {"On", "Off"};
void print_asteroids(Field* f);
void print_background(Field*);

int Menu::choices(Settings set, Field f, int mode) {
  unsigned choice = 0, gamemode = 0;
  int start = 0, settings = 0, quit = 0;
  int shift = 3, finflag = 4;
  const char** array;
  int height = f.getFieldHeight(), width = f.getFieldWidth();
  Settings_Menu setts(f);
  keypad(stdscr, true);
  switch (mode) {
    case 1:
      array = start_set;
      break;
    case 2:
      array = setting_set;
      break;
    case 3:
      array = (finflag == 3) ? setting_set : finish_set;
      break;
    case 4:
      array = (finflag == 3) ? finish_set : NULL;
      break;
    case 5:
      while (1) {
        clear();
        setts.print_rules(&f);
      }
      break;
  }
  while (1) {
    for (unsigned int i = 0; i < 4; i++) {
      if (i == choice)
        mvaddch(height / 2 + i, width / 2 - shift - 2, '>');
      else
        mvaddch(height / 2 + i, width / 2 - shift - 2, ' ');
      move(height / 2 + i, width / 2 - shift);
      printw("%s", array[i]);
    }
    if (mode == 2) {
      move(height / 2 + 1, width / 2 + 9);
      printw("%s", difficulty_set[gamemode]);
    }
    switch (getch()) {
      case KEY_UP:
        if (choice) choice--;
        break;
      case KEY_DOWN:
        if (choice != 3) choice++;
        break;
      case 10:
        if (choice == 0) {
          start = 1;
        } else if (choice == 1) {
          if (mode == 2) {
            (gamemode == 3) ? gamemode = 0 : gamemode += 1;
          } else {
            settings = 1;
          }
        } else if (choice == 2) {
          if (mode == 2) {
            move(height / 2 + 2, width / 2 + 2);
            setts.field_menu(&f);
          } else {
            setts.rules_processing(&f);
            print_asteroids(&f);
          }
        } else if (choice == 3) {
          quit = 1;
        }
        break;
    }
    if (quit) {
      curs_set(1);
      nocbreak();
      endwin();
      break;
    } else if (start) {
      clear();
      Game game(gamemode);
      game.play(f.getNewFieldHeight(), f.getNewFieldWidth(), set);
      break;
    } else if (settings) {
      clear();
      setts.processing(set, &f);
      break;
    }
  }
  return 0;
}

int Start::processing(Settings set, Field* f) {
  clear();
  COLOR_PAIR(3);
//  int height = f->getFieldHeight(), width = f->getFieldWidth();
  f->draw_field(0);
  print_asteroids(f);
  print_background(f);
  choices(set, *f, 1);
  return 0;
}

void print_asteroids(Field* f) {
  clear();
  f->draw_field(0);
  int x = f->getFieldWidth() / 2 - 16;
  int y = TITLEPOS;
  attrset(COLOR_PAIR(8));
  print_a(x, y, CELL_TYPE);
  x += 4;
  print_s(x, y, CELL_TYPE);
  x += 3;
  print_t(x, y, CELL_TYPE);
  x += 4;
  print_e(x, y, CELL_TYPE);
  x += 3;
  print_r(x, y, CELL_TYPE);
  x += 4;
  print_o(x, y, CELL_TYPE);
  x += 4;
  print_i(x, y, CELL_TYPE);
  x += 4;
  print_d(x, y, CELL_TYPE);
  x += 4;
  print_s(x, y, CELL_TYPE);
  print_background(f);
  attroff(COLOR_PAIR(9));
  attrset(A_BOLD);
  COLOR_PAIR(3);
}

void Settings_Menu::print_settings(Field* f) {
  clear();
  f->draw_field(0);
  int x = f->getFieldWidth() / 2 - 15;
  int y = TITLEPOS;
  attrset(COLOR_PAIR(8));
  print_s(x, y, CELL_TYPE);
  x += 3;
  print_e(x, y, CELL_TYPE);
  x += 3;
  print_t(x, y, CELL_TYPE);
  x += 4;
  print_t(x, y, CELL_TYPE);
  x += 4;
  print_i(x, y, CELL_TYPE);
  x += 4;
  print_n(x, y, CELL_TYPE);
  x += 5;
  print_g(x, y, CELL_TYPE);
  x += 5;
  print_s(x, y, CELL_TYPE);
  print_background(f);
  attroff(COLOR_PAIR(9));
  attrset(A_BOLD);
  COLOR_PAIR(3);
}

void Settings_Menu::print_field(Field* f) {
  int x = f->getFieldWidth() / 2 - 8;
  int y = TITLEPOS;
  attrset(COLOR_PAIR(8));
  print_f(x, y, CELL_TYPE);
  x += 3;
  print_i(x, y, CELL_TYPE);
  x += 4;
  print_e(x, y, CELL_TYPE);
  x += 3;
  print_l(x, y, CELL_TYPE);
  x += 4;
  print_d(x, y, CELL_TYPE);
  print_background(f);
  attroff(COLOR_PAIR(9));
  attrset(A_BOLD);
  COLOR_PAIR(3);
}

void Finish::print_blackhole(Field* f) {
  clear();
  f->draw_field(1);
  int x = f->getFieldWidth() / 2 - 17;
  int y = TITLEPOS;
  attrset(COLOR_PAIR(8));
  print_b(x, y, CELL_TYPE);
  x += 4;
  print_l(x, y, CELL_TYPE);
  x += 4;
  print_a(x, y, CELL_TYPE);
  x += 4;
  print_c(x, y, CELL_TYPE);
  x += 4;
  print_k(x, y, CELL_TYPE);
  x += 5;
  print_h(x, y, CELL_TYPE);
  x += 4;
  print_o(x, y, CELL_TYPE);
  x += 4;
  print_l(x, y, CELL_TYPE);
  x += 4;
  print_e(x, y, CELL_TYPE);
  attroff(COLOR_PAIR(9));
  attrset(A_BOLD);
  COLOR_PAIR(3);
}

void Finish::print_gameover(Field* f) {
  clear();
  f->draw_field(0);
  int x = f->getFieldWidth() / 2 - 16;
  int y = TITLEPOS;
  attrset(COLOR_PAIR(8));
  print_g(x, y, CELL_TYPE);
  x += 5;
  print_a(x, y, CELL_TYPE);
  x += 4;
  print_m(x, y, CELL_TYPE);
  x += 6;
  print_e(x, y, CELL_TYPE);
  x += 3;
  print_o(x, y, CELL_TYPE);
  x += 4;
  print_v(x, y, CELL_TYPE);
  x += 4;
  print_e(x, y, CELL_TYPE);
  x += 3;
  print_r(x, y, CELL_TYPE);
  print_background(f);
  attroff(COLOR_PAIR(9));
  attrset(A_BOLD);
  COLOR_PAIR(3);
}

void Settings_Menu::print_rules(Field* f) {
  clear();
  f->draw_field(0);
  int x = f->getFieldWidth() / 2 - 8;
  int y = TITLEPOS;
  attrset(COLOR_PAIR(8));
  print_r(x, y, CELL_TYPE);
  x += 4;
  print_u(x, y, CELL_TYPE);
  x += 4;
  print_l(x, y, CELL_TYPE);
  x += 4;
  print_e(x, y, CELL_TYPE);
  x += 3;
  print_s(x, y, CELL_TYPE);
  print_background(f);
  attroff(COLOR_PAIR(9));
  attrset(A_BOLD);
  COLOR_PAIR(3);
}

int Finish::processing(Settings set, Field* f) {
  int height = f->getFieldHeight(), width = f->getFieldWidth();
  while (!(getch() == 10)) {
    attroff(A_BLINK);
    (game.getstatus() == 1) ? print_blackhole(f) : print_gameover(f);
    move(height / 2, width / 2 - 2);
    printw("SCORE: %d", game.getScore());
    attrset(A_BLINK | COLOR_PAIR((game.getstatus() == 1) ? 9 : 3));
    move(height / 2 + 1, width / 2 - 8);
    printw("Press ENTER to replay");
  }
  attrset(COLOR_PAIR(3));
  print_gameover(f);
  choices(set, *f, 3);
  return 0;
}

int Settings_Menu::rules_processing(Field* f) {
  int ch = 0;
  int flag = 1;
  clear();
  f->draw_field(0);
  print_rules(f);
  move(f->getFieldHeight() / 2, f->getFieldWidth() / 2 - 10);
  attrset(A_UNDERLINE | A_BOLD);
  printw("CONTROL");
  attroff(A_UNDERLINE);
  move(f->getFieldHeight() / 2 + 1, f->getFieldWidth() / 2 - 10);
  printw("WASD - spaceship control");
  move(f->getFieldHeight() / 2 + 2, f->getFieldWidth() / 2 - 10);
  printw("R - gunshot");
  move(f->getFieldHeight() / 2 + 3, f->getFieldWidth() / 2 - 10);
  printw("Enter - select");
  keypad(stdscr, true);
  while (flag) {
    attrset(A_BLINK | COLOR_PAIR(3));
    move(f->getFieldHeight() / 2 - 1, f->getFieldWidth() / 2 - 10);
    printw("Press ENTER to go back");
    ch = getch();
    if (ch == 10) flag = 0;
  }
  print_rules(f);
  return 0;
}

int Settings_Menu::processing(Settings set, Field* f) {
  clear();
  f->draw_field(0);
  print_settings(f);
  choices(set, *f, 2);
  return 0;
}

int Settings_Menu::field_menu(Field* f) {
  int ch;
  int newheight = f->getFieldHeight();
  int newwidth = f->getFieldWidth();
  int j = 0, flag = 1;
  unsigned choice = 0;
  clear();
  f->draw_field(0);
  print_field(f);
  keypad(stdscr, true);
  while (flag) {
    attroff(A_BOLD);
    mvaddstr(f->getFieldHeight() - 4, f->getFieldWidth() / 2 - 12,
             "Press '+/=' to increase");
    mvaddstr(f->getFieldHeight() - 3, f->getFieldWidth() / 2 - 12,
             "Press '-/_' to decrease");
    attrset(A_BOLD);
    for (unsigned int i = 0; i < 3; i++) {
      if (i == choice)
        mvaddch(f->getFieldHeight() / 2 + i, f->getFieldWidth() / 2 - 3 - 2,
                '>');
      else
        mvaddch(f->getFieldHeight() / 2 + i, f->getFieldWidth() / 2 - 3 - 2,
                ' ');
      move(f->getFieldHeight() / 2 + i, f->getFieldWidth() / 2 - 3);
      printw("%s", field_set[i]);
      if (i == 0) printw(":\t%d", newheight);
      if (i == 1) printw(":\t%d", newwidth);
    }
    switch (ch = getch()) {
      case KEY_UP:
        if (choice) choice--;
        break;
      case KEY_DOWN:
        if (choice != 2) choice++;
        break;
      case '=':
        move(f->getFieldHeight() / 2 + choice, f->getFieldWidth() / 2 - 3);
        move(f->getFieldHeight() / 2 + choice, f->getFieldWidth() / 2 - 3);
        printw("%s", field_set[j]);
        if (choice == 0)
          printw(":\t%d", (newheight < TOP_H) ? newheight++ : newheight);
        else if (choice == 1)
          printw(":\t%d", (newwidth < TOP_W) ? newwidth++ : newwidth);
        break;
      case '-':
        if (ch == KEY_DOWN || ch == KEY_UP) {
          f->setFieldHeight(newheight);
          f->setFieldWidth(newwidth);
          break;
        }
        move(f->getFieldHeight() / 2 + choice, f->getFieldWidth() / 2 - 3);
        move(f->getFieldHeight() / 2 + choice, f->getFieldWidth() / 2 - 3);
        printw("%s", field_set[j]);
        if (choice == 0)
          printw(":\t%d", (newheight > BOT_H) ? newheight-- : newheight);
        else if (choice == 1)
          printw(":\t%d", (newwidth < BOT_W) ? newwidth-- : newwidth);
        break;
      case 10:
        if (choice == 2) flag = 0;
        f->setFieldHeight(newheight);
        f->setFieldWidth(newwidth);
        break;
    }
  }
  f->setFieldHeight(newheight);
  f->setFieldWidth(newwidth);
  print_settings(f);
  return 0;
}

void print_background(Field* f) {
  int y = f->getFieldHeight() - 7;
  int x = f->getFieldWidth() - 3;
  attrset(COLOR_PAIR(8));
  print_r(x, y, CELL_TYPE);
  print_l(x, y + 1, CELL_TYPE);
  print_b(x - 2, y + 1, CELL_TYPE);
  print_s(x - 4, y + 2, CELL_TYPE);
  x = 1;
  print_s(x, y, CELL_TYPE);
  print_t(x + 2, y + 1, CELL_TYPE);
  print_s(x + 1, y + 2, CELL_TYPE);
  print_s(x + 4, y + 2, CELL_TYPE);
  print_l(x + 5, y + 2, CELL_TYPE);
  x = f->getFieldWidth() - 4;
  y = 1;
  print_g(x, y + 1, CELL_TYPE);
  print_i(x + 1, y - 1, CELL_TYPE);
  print_i(x, y - 1, CELL_TYPE);
  print_b(x - 2, y, CELL_TYPE);
  print_e(x - 4, y - 1, CELL_TYPE);
  attroff(COLOR_PAIR(9));
  attrset(A_BOLD);
  COLOR_PAIR(3);
}
