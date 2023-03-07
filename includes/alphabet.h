#ifndef ALPHABET
#define ALPHABET
#include "base.h"

void print_a(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
//  char two_cells[3] = {cell_type, cell_type};
  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(three_cells);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 1, x + 2);
  addstr(one_cell);
  move(y + 2, x);
  addstr(one_cell);
  move(y + 2, x + 2);
  addstr(one_cell);
  move(y + 3, x);
  addstr(three_cells);
  move(y + 4, x);
  addstr(one_cell);
  move(y + 4, x + 2);
  addstr(one_cell);
}

void print_b(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
//  char two_cells[3] = {cell_type, cell_type};
  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(three_cells);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 1, x + 2);
  addstr(one_cell);
  move(y + 2, x);
  addstr(three_cells);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 3, x + 2);
  addstr(one_cell);
  move(y + 4, x);
  addstr(three_cells);
}

void print_c(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
//  char two_cells[3] = {cell_type, cell_type};
  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(three_cells);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 2, x);
  addstr(one_cell);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 4, x);
  addstr(three_cells);
}

void print_h(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
//  char two_cells[3] = {cell_type, cell_type};
  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(one_cell);
  move(y, x + 2);
  addstr(one_cell);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 1, x + 2);
  addstr(one_cell);
  move(y + 2, x);
  addstr(three_cells);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 3, x + 2);
  addstr(one_cell);
  move(y + 4, x);
  addstr(one_cell);
  move(y + 4, x + 2);
  addstr(one_cell);
}

void print_s(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
  char two_cells[3] = {cell_type, cell_type};
//  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(two_cells);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 2, x);
  addstr(two_cells);
  move(y + 3, x);
  move(y + 3, x + 1);
  addstr(one_cell);
  move(y + 4, x);
  addstr(two_cells);
}

void print_t(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
//  char two_cells[3] = {cell_type, cell_type};
  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(three_cells);
  move(y + 1, x);
  move(y + 1, x + 1);
  addstr(one_cell);
  move(y + 2, x);
  move(y + 2, x + 1);
  addstr(one_cell);
  move(y + 3, x);
  move(y + 3, x + 1);
  addstr(one_cell);
  move(y + 4, x);
  move(y + 4, x + 1);
  addstr(one_cell);
}

void print_e(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
  char two_cells[3] = {cell_type, cell_type};
//  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(two_cells);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 2, x);
  addstr(two_cells);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 4, x);
  addstr(two_cells);
}

void print_r(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
  char two_cells[3] = {cell_type, cell_type};
  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(three_cells);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 1, x + 2);
  addstr(one_cell);
  move(y + 2, x);
  addstr(three_cells);
  move(y + 3, x);
  addstr(two_cells);
  move(y + 4, x);
  addstr(one_cell);
  move(y + 4, x + 2);
  addstr(one_cell);
}

void print_o(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
//  char two_cells[3] = {cell_type, cell_type};
  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(three_cells);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 1, x + 2);
  addstr(one_cell);
  move(y + 2, x);
  addstr(one_cell);
  move(y + 2, x + 2);
  addstr(one_cell);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 3, x + 2);
  addstr(one_cell);
  move(y + 4, x);
  addstr(three_cells);
}

void print_i(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
//  char two_cells[3] = {cell_type, cell_type};
  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(three_cells);
  move(y + 1, x);
  move(y + 1, x + 1);
  addstr(one_cell);
  move(y + 2, x);
  move(y + 2, x + 1);
  addstr(one_cell);
  move(y + 3, x);
  move(y + 3, x + 1);
  addstr(one_cell);
  move(y + 4, x);
  addstr(three_cells);
}

void print_d(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
  char two_cells[3] = {cell_type, cell_type};
//  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(two_cells);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 1, x + 2);
  addstr(one_cell);
  move(y + 2, x);
  addstr(one_cell);
  move(y + 2, x + 2);
  addstr(one_cell);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 3, x + 2);
  addstr(one_cell);
  move(y + 4, x);
  addstr(two_cells);
}

void print_n(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
  char two_cells[3] = {cell_type, cell_type};
//  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(one_cell);
  move(y, x + 3);
  addstr(one_cell);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 1, x + 3);
  addstr(one_cell);
  move(y + 2, x);
  addstr(two_cells);
  move(y + 2, x + 3);
  addstr(one_cell);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 3, x + 2);
  addstr(two_cells);
  move(y + 4, x);
  addstr(one_cell);
  move(y + 4, x + 3);
  addstr(one_cell);
}

void print_g(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
  char two_cells[3] = {cell_type, cell_type};
//  char three_cells[4] = {cell_type, cell_type, cell_type};
  char four_cells[5] = {cell_type, cell_type, cell_type, cell_type};
  move(y, x);
  addstr(four_cells);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 2, x);
  addstr(one_cell);
  move(y + 2, x + 2);
  addstr(two_cells);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 3, x + 3);
  addstr(one_cell);
  move(y + 4, x);
  addstr(four_cells);
}

void print_f(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
  char two_cells[3] = {cell_type, cell_type};
//  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(two_cells);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 2, x);
  addstr(two_cells);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 4, x);
  addstr(one_cell);
}

void print_k(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
  char two_cells[3] = {cell_type, cell_type};
//  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(one_cell);
  move(y, x + 3);
  addstr(one_cell);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 1, x + 2);
  addstr(one_cell);
  move(y + 2, x);
  addstr(two_cells);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 3, x + 2);
  addstr(one_cell);
  move(y + 4, x);
  addstr(one_cell);
  move(y + 4, x + 3);
  addstr(one_cell);
}

void print_l(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
//  char two_cells[3] = {cell_type, cell_type};
  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(one_cell);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 2, x);
  addstr(one_cell);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 4, x);
  addstr(three_cells);
}

void print_m(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
  char two_cells[3] = {cell_type, cell_type};
//  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(one_cell);
  move(y, x + 4);
  addstr(one_cell);
  move(y + 1, x);
  addstr(two_cells);
  move(y + 1, x + 3);
  addstr(two_cells);
  move(y + 2, x);
  addstr(one_cell);
  move(y + 2, x + 2);
  addstr(one_cell);
  move(y + 2, x + 4);
  addstr(one_cell);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 3, x + 4);
  addstr(one_cell);
  move(y + 4, x);
  addstr(one_cell);
  move(y + 4, x + 4);
  addstr(one_cell);
}

void print_v(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
//  char two_cells[3] = {cell_type, cell_type};
//  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(one_cell);
  move(y, x + 2);
  addstr(one_cell);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 1, x + 2);
  addstr(one_cell);
  move(y + 2, x);
  addstr(one_cell);
  move(y + 2, x + 2);
  addstr(one_cell);
  move(y + 3, x);
  addstr(one_cell);
  move(y + 3, x + 2);
  addstr(one_cell);
  move(y + 4, x);
  move(y + 4, x + 1);
  addstr(one_cell);
}

void print_u(int x, int y, char cell_type) {
  char one_cell[2] = {cell_type};
//  char two_cells[3] = {cell_type, cell_type};
  char three_cells[4] = {cell_type, cell_type, cell_type};
  move(y, x);
  addstr(one_cell);
  move(y, x + 2);
  addstr(one_cell);
  move(y + 1, x);
  addstr(one_cell);
  move(y + 1, x + 2);
  addstr(one_cell);
  move(y + 2, x);
  addstr(one_cell);
  move(y + 2, x + 2);
  addstr(one_cell);
  move(y + 3, x);
  addstr(one_cell);

  move(y + 3, x + 2);
  addstr(one_cell);
  move(y + 4, x);
  addstr(three_cells);
}

#endif
