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

void Fuzzy_Controller::rules_manager() {
  all_rules.push_back(new Rule(Z, AND, Z, Z));
  all_rules.push_back(new Rule(PB, OR, PB, NB));
  all_rules.push_back(new Rule(NB, OR, NB, PB));
  all_rules.push_back(new Rule(NM, AND, ZN, PB)); /* если текущее отклонение
  среднее внизу и разница между положением корабля и зоной очень маленькое
  снизу, то кораблю необходимо дать крен вверх  */
  all_rules.push_back(new Rule(PM, AND, ZP, NB));
  all_rules.push_back(new Rule(ZN, AND, ZN, ZP));
  all_rules.push_back(new Rule(ZP, AND, ZP, ZN));

  all_rules.push_back(new Rule(NS, AND, PS, ZP));
  all_rules.push_back(new Rule(NS, AND, NS, PM));
  all_rules.push_back(new Rule(PS, AND, NS, ZN));
  all_rules.push_back(new Rule(PS, AND, PS, NM));
}

double Fuzzy_Controller::rules_processing(int e, int de) {
  double num = 0, den = 0;
  for (long unsigned int i = 0; i < all_rules.size(); i++) {
    double alpha = 0, mf_cur = 0, mf_delt = 0;
    mf_cur = membership_function(e, all_rules[i]->getCurr(), getBasis());
    mf_delt = membership_function(de, all_rules[i]->getDelta(), getBasis());
    alpha = (all_rules[i]->getOper() == 1) ? MIN(mf_cur, mf_delt)
                                           : MAX(mf_cur, mf_delt);
    num += (alpha * all_rules[i]->getPrev());
    den += alpha;
  }
  return num / den;
}

vector<Zone *> Fuzzy_Controller::calculate_distance(Field *field,
                                                    Spaceship *spaceship) {
  vector<Zone *> all_zones;
  int space_x = spaceship->getPos().getY(); // просмотр окружения корабля
  int space_y = spaceship->getPos().getY();
  all_zones.push_back(new Zone(
      ZONE_SIZE, ZONE_SIZE, 1, 0,
      Space_Object(space_x - 1,
                   space_y - (int)(ZONE_SIZE / 2)))); // зона с кораблем
  int i = 0;
  all_zones.push_back(
      new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0,
               Space_Object(space_x - 1, space_y - ZONE_SIZE -
                                             (int)(ZONE_SIZE / 2)))); // вверх
  // занесение зон в вектор
  for (i = 1; all_zones.at(i)->getPos().getY() > -1; i++) { // вверх
    all_zones.push_back(
        new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0,
                 Space_Object(all_zones.at(i)->getPos().getX(),
                              all_zones.at(i)->getPos().getY() - ZONE_SIZE)));
  }
  for (i = i;
       all_zones.at(i)->getPos().getY() < field->getFieldHeight() - ZONE_SIZE;
       i++) { // вниз
    all_zones.push_back(
        new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0,
                 Space_Object(all_zones.at(i)->getPos().getX(),
                              all_zones.at(i)->getPos().getY() + ZONE_SIZE)));
  }
  for (i = 0;
       all_zones.at(i)->getPos().getX() < field->getFieldWidth() - ZONE_SIZE;
       i++) {
    all_zones.push_back(
        new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0,
                 Space_Object(all_zones.at(i)->getPos().getX() + ZONE_SIZE,
                              all_zones.at(i)->getPos().getY())));
  }
  for (i = 0; all_zones.at(i)->getPos().getX() > ZONE_SIZE; i++) {
    all_zones.push_back(
        new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0,
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
      zone->setCoefficient(zone->getCoefficient() - koef_diff * 2);
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
  float max_priority = std::numeric_limits<float>::lowest();
  int max_index = -1;
  for (long unsigned int i = 0; i < zones->size();
       i++) { // поиск зоны с максимальным коэффициентом
    auto &zone = (*zones)[i];
    if (abs(zone->getPriority()) > max_priority) {
      max_priority = abs(zone->getPriority());
      max_index = i;
    }
  }
  move(zones->at(max_index)->getPos().getY(),
       zones->at(max_index)->getPos().getX());
  printw("%d", zones->at(max_index)->getPriority());
  return max_index;
}

void Fuzzy_Controller::rules_to_do(Spaceship *spaceship, Field *field,
                                   double z_x, double z_y) {
  // int no_effect = 6;
  int small_effect = 12;
  int medium_effect = 34;
  int big_effect = 60;
  if (z_y > 0) {
    if (z_y > big_effect) {
      spaceship->change_position('s', *field);
      spaceship->change_position('s', *field);
      spaceship->change_position('s', *field);
    } else if (z_y > medium_effect) {
      spaceship->change_position('s', *field);
      spaceship->change_position('s', *field);
    } else if (z_y > small_effect) {
      spaceship->change_position('s', *field);
    }
  } else if (z_y < 0) {
    if (abs(z_y) > big_effect) {
      spaceship->change_position('w', *field);
      spaceship->change_position('w', *field);
      spaceship->change_position('w', *field);
    } else if (abs(z_y) > medium_effect) {
      spaceship->change_position('w', *field);
      spaceship->change_position('w', *field);
    } else if (abs(z_y) > small_effect) {
      spaceship->change_position('w', *field);
    }
  }
  if (z_x > 0 && spaceship->getPos().getX() < field->getFieldWidth() / 2) {
    spaceship->change_position('d', *field);
  } else if (z_x < 0) {
    spaceship->change_position('a', *field);
  }
}
