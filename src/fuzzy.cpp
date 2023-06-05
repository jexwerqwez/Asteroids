#include "../includes/fuzzy.h"

int Fuzzy_Controller::return_zone_index(Space_Object object,
                                        vector<Zone *> *zones) {
  for (long unsigned int i = 0; i < zones->size(); i++) {
    for (int j = 0; j < zones->at(i)->getWidth(); j++) {
      for (int k = 0; k < zones->at(i)->getHeight(); k++) {
        Space_Object zone_offset(j, k);
        if (object == zones->at(i)->getPos() + zone_offset)
          return i;
      }
    }
  }
  return 0;
}

void Rule::setRules(int cur_st, int delta_st, int prev_st) {
  current_state = cur_st;
  delta_state = delta_st;
  previous_state = prev_st;
}

// double activation(vector<Rule *>) {}

void Fuzzy_Controller::rules_manager() {
  all_move_rules.push_back(new Rule(Z, AND, Z, Z));
  all_move_rules.push_back(new Rule(PB, OR, PB, NB));
  all_move_rules.push_back(new Rule(NB, OR, NB, PB));
  all_move_rules.push_back(new Rule(NM, AND, ZN, PB)); /* если текущее
  отклонение среднее внизу и разница между положением корабля и зоной очень
  маленькое снизу, то кораблю необходимо дать крен вверх  */
  all_move_rules.push_back(new Rule(PM, AND, ZP, NB));
  all_move_rules.push_back(new Rule(ZN, AND, ZN, ZP));
  all_move_rules.push_back(new Rule(ZP, AND, ZP, ZN));

  all_move_rules.push_back(new Rule(NS, AND, PS, ZP));
  all_move_rules.push_back(new Rule(NS, AND, NS, PM));
  all_move_rules.push_back(new Rule(PS, AND, NS, ZN));
  all_move_rules.push_back(new Rule(PS, AND, PS, NM));

  all_move_rules.push_back(new Rule(PM, AND, PS, NB));
  all_move_rules.push_back(new Rule(PM, AND, PM, NB));
  all_move_rules.push_back(new Rule(PM, AND, NS, NM));
  all_move_rules.push_back(new Rule(PM, AND, ZN, NM));
  all_move_rules.push_back(new Rule(PM, AND, NM, NB));
  all_move_rules.push_back(new Rule(NM, AND, NS, PB));
  all_move_rules.push_back(new Rule(NM, AND, NM, PB));
  all_move_rules.push_back(new Rule(NM, AND, PM, PB));
  all_move_rules.push_back(new Rule(NM, AND, PS, PM));
  all_move_rules.push_back(new Rule(NM, AND, ZP, PM));
}

double Fuzzy_Controller::rules_processing(int e, int de) {
  double num = 0, den = 0;
  for (long unsigned int i = 0; i < all_move_rules.size(); i++) {
    double alpha = 0, mf_cur = 0, mf_delt = 0;
    mf_cur =
        membership_function(e, all_move_rules[i]->getCurr(), getBasis() - 10);
    mf_delt =
        membership_function(de, all_move_rules[i]->getDelta(), getBasis() - 10);
    alpha = (all_move_rules[i]->getOper() == 1) ? MIN(mf_cur, mf_delt)
                                                : MAX(mf_cur, mf_delt);
    num += (alpha * all_move_rules[i]->getPrev());
    den += alpha;
  }
  return num / den;
}

double Fuzzy_Controller::rules_prio_processing(int e, int de) {
  double di = 0, num = 0, den = 0, activated = 0, cur_max = -1;
  for (long unsigned int i = 0; i < all_prio_rules.size(); i++) {
    double alpha = 0, mf_cur = 0, mf_delt = 0, mf_prev;
    mf_cur = membership_function(e, all_prio_rules[i]->getCurr(),
                                 getBasis()); // фаззификация
    mf_delt =
        membership_function(de, all_prio_rules[i]->getDelta(), getBasis());
    mf_prev =
        membership_function(de, all_prio_rules[i]->getDelta(), getBasis());
    alpha = (all_prio_rules[i]->getOper() == 1)
                ? MIN(mf_cur, mf_delt)
                : MAX(mf_cur, mf_delt); // агрегирование подусловий
    di = (alpha * all_prio_rules[i]->getPrev()); // степень истинности правила
    activated = MIN(di, mf_prev); // min-активация подзаключений
    if (activated > cur_max) {
      cur_max = activated;
    }
    num += all_prio_rules[i]->getPrev() * cur_max;
    den += cur_max;
  }
  return num / den;
}

vector<Zone *> Fuzzy_Controller::calculate_distance(Field *field,
                                                    Spaceship *spaceship) {
  vector<Zone *> all_zones;
  int space_x = spaceship->getPos().getY(); // просмотр окружения корабля
  int space_y = spaceship->getPos().getY();
  all_zones.push_back(new Zone(
      ZONE_SIZE, ZONE_SIZE, 1, 0, 0,
      Space_Object(space_x - 1,
                   space_y - (int)(ZONE_SIZE / 2)))); // зона с кораблем

  int i = 0;
  all_zones.push_back(
      new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0, 0,
               Space_Object(space_x - 1, space_y - ZONE_SIZE -
                                             (int)(ZONE_SIZE / 2)))); // вверх
  // занесение зон в вектор
  for (i = 1; all_zones.at(i)->getPos().getY() > -1; i++) { // вверх
    all_zones.push_back(
        new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0, 0,
                 Space_Object(all_zones.at(i)->getPos().getX(),
                              all_zones.at(i)->getPos().getY() - ZONE_SIZE)));
  }
  for (i = i;
       all_zones.at(i)->getPos().getY() < field->getFieldHeight() - ZONE_SIZE;
       i++) { // вниз
    all_zones.push_back(
        new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0, 0,
                 Space_Object(all_zones.at(i)->getPos().getX(),
                              all_zones.at(i)->getPos().getY() + ZONE_SIZE)));
  }
  for (i = 0;
       all_zones.at(i)->getPos().getX() < field->getFieldWidth() - ZONE_SIZE;
       i++) {
    all_zones.push_back(
        new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0, 0,
                 Space_Object(all_zones.at(i)->getPos().getX() + ZONE_SIZE,
                              all_zones.at(i)->getPos().getY())));
  }
  for (i = 0; all_zones.at(i)->getPos().getX() > ZONE_SIZE; i++) {
    all_zones.push_back(
        new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0, 0,
                 Space_Object(all_zones.at(i)->getPos().getX() - ZONE_SIZE,
                              all_zones.at(i)->getPos().getY())));
  }
  return all_zones;
}

void Fuzzy_Controller::calculate_asteroids(vector<Zone *> *zones,
                                           Space_Object offset,
                                           Spaceship *spaceship, Field *field) {
  int max_num = (field->getFieldHeight() > field->getFieldWidth())
                    ? ceil(field->getFieldHeight() / (double)ZONE_SIZE)
                    : ceil(field->getFieldWidth() /
                           (double)ZONE_SIZE); // находим число зон
  float koef_diff =
      1.0 / (float)(max_num + ZONE_SIZE); // вычисление коэффициента
  for (auto &zone : *zones) { // наличие астероида в зоне
    if (zone->inside_the_zone(offset)) {
      zone->setCoefficient(zone->getCoefficient() - koef_diff * ZONE_SIZE);
      if (zone->inside_the_zone(spaceship->getPos())) {
        zone->setCoefficient(fuzzy_coef[4]);
      }
    }
    zone->priority_processing(spaceship, zone);
  }
}

int Fuzzy_Controller::find_optimal_x(vector<Zone *> *zones,
                                     Spaceship *spaceship) {
  int min_x = std::numeric_limits<int>::max();
  int min_index = -1;
  for (long unsigned int i = 0; i < zones->size(); i++) {
    auto &zone = (*zones)[i];
    if (zone->getDistanceX(spaceship, zone) < min_x) {
      min_x = zone->getDistanceX(spaceship, zone);
      min_index = i;
    }
  }
  return min_index;
}

int Fuzzy_Controller::find_optimal_y(vector<Zone *> *zones,
                                     Spaceship *spaceship) {
  int min_y = std::numeric_limits<int>::max();
  int min_index = -1;
  for (long unsigned int i = 0; i < zones->size(); i++) {
    auto &zone = (*zones)[i];
    if (zone->getDistanceY(spaceship, zone) < min_y) {
      min_y = zone->getDistanceY(spaceship, zone);
      min_index = i;
    }
  }
  return min_index;
}

int Fuzzy_Controller::find_optimal_priority(vector<Zone *> *zones) {
  double max_priority = std::numeric_limits<float>::lowest();
  int max_index = -1;
  for (long unsigned int i = 0; i < zones->size();
       i++) { // поиск зоны с максимальным коэффициентом
    auto &zone = (*zones)[i];
    if (abs(zone->getPriority()) > max_priority) {
      max_priority = abs(zone->getPriority());
      max_index = i;
    }
  }
  // move(zones->at(max_index)->getPos().getY(),
  //      zones->at(max_index)->getPos().getX());
  // printw("%lf", zones->at(max_index)->getPriority());
  return max_index;
}

void Fuzzy_Controller::rules_to_do(Spaceship *spaceship, Field *field,
                                   vector<Asteroids *> *all_asts, double z_x,
                                   double z_y) {
  int spaceship_x = spaceship->getPos().getX();
  int spaceship_y = spaceship->getPos().getY();
  bool findflag = false;
  if (z_y > 0) {
    for (auto &aster : *all_asts) {
      if (aster->getPos().getX() == spaceship_x &&
          (aster->getPos().getY() == spaceship_y + 1 ||
           aster->getPos().getY() == spaceship_y + 2)) {
        findflag = true;
      }
    }
    if (!findflag)
      spaceship->change_position('s', *field);
  } else if (z_y < 0) {
    for (auto &aster : *all_asts) {
      if (aster->getPos().getX() == spaceship_x &&
          (aster->getPos().getY() == spaceship_y - 2 ||
           aster->getPos().getY() == spaceship_y - 1 ||
           aster->getPos().getY() == spaceship_y - 3)) {
        findflag = true;
      }
    }
    if (!findflag)
      spaceship->change_position('w', *field);
  }
  findflag = false;
  if (z_x > 0 && spaceship->getPos().getX() < field->getFieldWidth() / 2) {
    for (auto &aster : *all_asts) {
      if ((aster->getPos().getX() == spaceship_x + 1 ||
           aster->getPos().getX() == spaceship_x + 2) &&
          aster->getPos().getY() == spaceship_y - 1) {
        findflag = true;
      }
    }
    if (!findflag)
      spaceship->change_position('d', *field);
  } else if (z_x < 0) {
    for (auto &aster : *all_asts) {
      if ((aster->getPos().getX() == spaceship_x - 2 ||
           aster->getPos().getX() == spaceship_x - 1 ||
           aster->getPos().getX() == spaceship_x - 3) &&
          aster->getPos().getY() == spaceship_y - 1) {
        findflag = true;
      }
    }
    if (!findflag)
      spaceship->change_position('a', *field);
  }
}

void Fuzzy_Controller::rules_prio_manager(float *fuzzy_coef, int *fuzzy_dist,
                                          int *fuzzy_prio) {
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[0], AND, fuzzy_dist[4], fuzzy_prio[0]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[0], AND, fuzzy_dist[3], fuzzy_prio[0]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[0], AND, fuzzy_dist[2], fuzzy_prio[0]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[0], AND, fuzzy_dist[1], fuzzy_prio[1]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[0], AND, fuzzy_dist[0], fuzzy_prio[1]));

  all_prio_rules.push_back(
      new Rule(fuzzy_coef[1], AND, fuzzy_dist[4], fuzzy_prio[0]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[1], AND, fuzzy_dist[3], fuzzy_prio[0]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[1], AND, fuzzy_dist[2], fuzzy_prio[1]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[1], AND, fuzzy_dist[1], fuzzy_prio[1]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[1], AND, fuzzy_dist[0], fuzzy_prio[2]));

  all_prio_rules.push_back(
      new Rule(fuzzy_coef[2], AND, fuzzy_dist[4], fuzzy_prio[2]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[2], AND, fuzzy_dist[3], fuzzy_prio[3]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[2], AND, fuzzy_dist[2], fuzzy_prio[3]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[2], AND, fuzzy_dist[1], fuzzy_prio[4]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[2], AND, fuzzy_dist[0], fuzzy_prio[4]));

  all_prio_rules.push_back(
      new Rule(fuzzy_coef[3], AND, fuzzy_dist[4], fuzzy_prio[3]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[3], AND, fuzzy_dist[3], fuzzy_prio[3]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[3], AND, fuzzy_dist[2], fuzzy_prio[4]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[3], AND, fuzzy_dist[1], fuzzy_prio[4]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[3], AND, fuzzy_dist[0], fuzzy_prio[4]));

  all_prio_rules.push_back(
      new Rule(fuzzy_coef[4], AND, fuzzy_dist[4], fuzzy_prio[4]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[4], AND, fuzzy_dist[3], fuzzy_prio[4]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[4], AND, fuzzy_dist[2], fuzzy_prio[4]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[4], AND, fuzzy_dist[1], fuzzy_prio[4]));
  all_prio_rules.push_back(
      new Rule(fuzzy_coef[4], AND, fuzzy_dist[0], fuzzy_prio[4]));
}