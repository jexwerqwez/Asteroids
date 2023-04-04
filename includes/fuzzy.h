#ifndef FUZZY
#define FUZZY
#include "zone.h"
#include "field.h"
#include "spaceship.h"
#include "asteroids.h"


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
/**
 * @brief
 * Класс, отвечающий за реализацию нечёткого регулятора
 * @param all_rules вектор, содержащий указатели на все правила
 * @param basis среднеквадратичное отклонение, необходимое для нормального распределения
*/
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
  /**
   * @brief Функция, изменяющая коэффициент зоны при попадании в неё астероида
  */
  void calculate_asteroids(vector<Zone*>*, Space_Object, Spaceship*, Field*);
  /**
   * @brief Функция, изменяющая коэффициент зоны в зависимости от удаленности от зоны с Spaceship
  */
  vector<Zone*> calculate_distance(Field*, Spaceship*);
  /**
   * @brief Функция, ищущая индекс зоны в векторе зон, расстояние до которой по оси X минимальна
  */
  int find_optimal_x(vector<Zone *>*, Spaceship*);
  /**
   * @brief Функция, ищущая индекс зоны в векторе зон, расстояние до которой по оси Y минимальна
  */
  int find_optimal_y(vector<Zone *>*, Spaceship*);
  /**
   * @brief Функция, ищущая индекс зоны в векторе зон, имеющей максимальный коэффициент
  */
  int find_optimal_coef(vector<Zone *>*, Spaceship*);
  /**
   * @brief Функция, передающая действия Spaceship
  */
  void rules_to_do(vector<Zone *>*, Spaceship*, Field*);
  /**
   * @brief Обработка случая, когда Asteroid и Spaceship оказались в одной зоне
  */
  void asteroid_and_spaceship_in_zone(Zone *, Spaceship*, Space_Object*, Field*);
  /**
   * @brief Обработка случая, когда Asteroid и Spaceship оказались в одной зоне
  */
  int return_zone_index(Space_Object*, vector<Zone *>*);
};

#endif