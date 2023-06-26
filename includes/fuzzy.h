#ifndef FUZZY
#define FUZZY
#include "asteroids.h"
#include "field.h"
#include "rules.h"
#include "spaceship.h"
#include "zone.h"

#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define AND 1
#define OR 2
#define BASIS 30

/**
 * @brief
 * Класс, отвечающий за реализацию нечёткого регулятора
 * @param all_move_rules вектор, содержащий указатели на все правила
 * @param basis среднеквадратичное отклонение, необходимое для нормального
 * распределения
 */
class Fuzzy_Controller {
  vector<Rule *> all_move_rules;
  vector<Rule *> all_prio_rules;
  vector<Rule *> all_obst_rules;
  int basis;

public:
  Fuzzy_Controller(int b) : basis(b){};
  int getBasis() { return basis; };
  vector<Rule *> getMoveRules() { return all_move_rules; };
  vector<Rule *> getPrioRules() { return all_prio_rules; };
  /** @brief Функция, добавляющая правила в вектор правил*/
  void rules_manager();
  void rules_prio_manager(Settings *);
  void rules_obst_manager(float *, int *, int *);
  double rules_processing(double e, double de);
  double rules_prio_processing(double e, double de);
  double membership_function(double x, double mu, double basis) {
    return exp(-pow(x - mu, 2) / (2 * pow(basis, 2)));
  }
  /**
   * @brief Функция, изменяющая коэффициент зоны при попадании в неё астероида
   */
  void calculate_asteroids(vector<Zone *> *, Space_Object, Spaceship *,
                           Field *);
  /**
   * @brief Функция, изменяющая коэффициент зоны в зависимости от удаленности от
   * зоны с Spaceship
   */
  vector<Zone *> calculate_distance(Field *, Spaceship *, Settings *);
  /**
   * @brief Функция, ищущая индекс зоны в векторе зон, расстояние до которой по
   * оси X минимальна
   */
  int find_optimal_x(vector<Zone *> *, Spaceship *);
  /**
   * @brief Функция, ищущая индекс зоны в векторе зон, расстояние до которой по
   * оси Y минимальна
   */
  int find_optimal_y(vector<Zone *> *, Spaceship *);
  /**
   * @brief Функция, ищущая индекс зоны в векторе зон, имеющей максимальный
   * коэффициент
   */
  int find_optimal_priority(vector<Zone *> *);
  /**
   * @brief Функция, передающая действия Spaceship
   */
  void rules_to_do(Spaceship *, Field *, vector<Asteroids *> *, double, double);
  /**
   * @brief Обработка случая, когда Asteroid и Spaceship оказались в одной зоне
   */
  // char path_check(Zone *, Space_Object, Space_Object, Field *);
  /**
   * @brief Обработка случая, когда Asteroid и Spaceship оказались в одной зоне
   */
  int return_zone_index(Space_Object, vector<Zone *> *);
  // double activation(vector<Rule *>);

  bool isSafeToMove(Spaceship *, Field *, vector<Asteroids *> *, char);
};

#endif