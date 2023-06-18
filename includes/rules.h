#ifndef RULES
#define RULES
#include "base.h"

/** @brief большое отклоненние вниз/вправо*/
#define NB -125
/** @brief среднее отклоненние вниз/вправо*/
#define NM -90
/** @brief маленькое отклоненние вниз/вправо*/
#define NS -55
/** @brief очень маленькое отклоненние вниз/вправо*/
#define ZN -20
/** @brief отклоненния нет*/
#define Z 0
/** @brief очень маленькое отклоненние вверх/влево*/
#define ZP 20
/** @brief маленькое отклоненние вверх/влево*/
#define PS 55
/** @brief среднее отклонение вверх/влево*/
#define PM 90
/** @brief большое отклоненние вверх/влево*/
#define PB 125
/** @brief класс правил
 * @param current_state текущее состояние приоритетной зоны
 * @param operation вид операции: И или ИЛИ
 * @param delta_state отклонение корабля от приоритетной зоны
 * @param previous_state предыдущее значение отклонения
 */
class Rule {
  float current_state;
  int operation;
  int delta_state;
  int previous_state;

public:
  Rule(int cur, int op, int del, int prev)
      : current_state(cur), operation(op), delta_state(del),
        previous_state(prev){};
  void setRules(int cur_st, int delta_st, int prev_st);
  int getCurr() { return current_state; };
  int getOper() { return operation; };
  int getDelta() { return delta_state; };
  int getPrev() { return previous_state; };
  std::string ruleToString(const Rule *rule) {
    std::ostringstream oss;
    oss << "Rule: Coef=" << rule->current_state << ", Oper=" << rule->operation
        << ", Dist=" << rule->delta_state << ", Prio=" << rule->previous_state;
    return oss.str();
  }
};
#endif