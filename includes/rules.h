#ifndef RULES
#define RULES
#include "base.h"
/** @brief очень большой коэффициент (0.9 - 1.0)*/
#define VLC 0.9
/** @brief большой коэффициент (0.7 - 0.9)*/
#define LC 0.7
/** @brief средний коэффициент (0.5 - 0.7)*/
#define MC 0.5
/** @brief маленький коэффициент (0.3 - 0.5)*/
#define SC 0.3
/** @brief очень маленький коэффициент (0.0 - 0.3)*/
#define VSC 0

/** @brief очень большое расстояние (более 5 зон по Х и У)*/
#define VLD 4
/** @brief большое расстояние (4 - 5 зон по Х и У)*/
#define LD 3
/** @brief среднее расстоние (3 - 4 зоны по Х и У)*/
#define MD 2
/** @brief маленькое расстояние (2 - 3 зоны по Х и У)*/
#define SD 1
/** @brief очень маленькое расстояние (до 2х зон по Х и У)*/
#define VSD 0

/** @brief очень большой приоритет (100 - 125) */
#define VLP 125
/** @brief большой приоритет (75 - 100)*/
#define LP 100
/** @brief средний приоритет (50 - 75)*/
#define MP 75
/** @brief маленький приоритет (25 - 50)*/
#define SP 50
/** @brief очень маленький приоритет (0 - 25)*/
#define VSP 25

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
  int current_state;
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
};
#endif