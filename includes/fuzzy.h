#ifndef FUZZY
#define FUZZY
#include "base.h"

#define NB -125
#define NM -90
#define NS -55
#define ZN -20
#define Z 0
#define ZP 20
#define PS 55
#define PM 90
#define PB 125
#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define AND 1
#define OR 2

class Rule {
  int current_state;
  int operation;
  int delta_state;
  int previous_state;
public:
  Rule(int cur, int op, int del, int prev) : 
  current_state(cur), operation(op), delta_state(del), previous_state(prev) {};
  void setRules(int cur_st, int delta_st, int prev_st);
  int getCurr() {return current_state;};
  int getOper() {return operation;};
  int getDelta() {return delta_state;};
  int getPrev() {return previous_state;};
};

class Fuzzy_Controller {
  vector<Rule*> all_rules;
  int basis;
public:
  Fuzzy_Controller(int b) : basis(b) {};
  int getBasis() {return basis;};
  vector<Rule*> getRules() {return all_rules;};
  void rules_manager();
  double rules_processing(int e, int de);
  double membership_function(int x, int mu, int basis) {
      return exp(-pow(x - mu, 2) / (2 * pow(basis, 2)));
  }
};

#endif