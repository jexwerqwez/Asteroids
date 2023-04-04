#include "../includes/fuzzy.h"
#define ZONE_SIZE 3
double pyth(int x, int y) {
  return sqrt(y * y + x * x);
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
  all_rules.push_back(new Rule(NM, AND, ZN, PB));
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
  int space_x = spaceship->getPos().getX(); // просмотр окружения корабля
  int space_y = spaceship->getPos().getY();
  int max_num = (field->getFieldHeight() > field->getFieldWidth())
                    ? ceil(field->getFieldHeight() / 3.0)
                    : ceil(field->getFieldWidth() / 3.0);
  float koef_diff = 1.0 / (float)(max_num + ZONE_SIZE);
  all_zones.push_back(
      new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0, 0,
               Space_Object(space_x - 1, space_y - 1))); // зона с кораблем
  int i = 0;
  all_zones.push_back(new Zone(ZONE_SIZE, ZONE_SIZE, 1 - koef_diff, space_x - (space_x - 1), space_y - (space_y - ZONE_SIZE),
                               Space_Object(space_x - 1, space_y - ZONE_SIZE)));
  for (i = 1; all_zones.at(i)->getPos().getY() > -1; i++) {
    all_zones.push_back(new Zone(
        ZONE_SIZE, ZONE_SIZE, all_zones.at(i)->getCoefficient() - koef_diff, 0, 0,
        Space_Object(all_zones.at(i)->getPos().getX(),
                     all_zones.at(i)->getPos().getY() - ZONE_SIZE)));
    all_zones.back()->setDistanceX(space_x - (all_zones.back()->getPos().getX()));
    all_zones.back()->setDistanceY(space_y - (all_zones.back()->getPos().getY()));
  }
  all_zones.push_back(
      new Zone(ZONE_SIZE, ZONE_SIZE, 1 - koef_diff, space_x - (space_x - 1), space_y - (space_y + ZONE_SIZE - 1),
               Space_Object(space_x - 1, space_y + ZONE_SIZE - 1)));
  for (i += 1;
       all_zones.at(i)->getPos().getY() < field->getFieldHeight() - ZONE_SIZE;
       i++) {
    all_zones.push_back(new Zone(
        ZONE_SIZE, ZONE_SIZE, all_zones.at(i)->getCoefficient() - koef_diff, 0,0,
        Space_Object(all_zones.at(i)->getPos().getX(),
                     all_zones.at(i)->getPos().getY() + ZONE_SIZE)));
    all_zones.back()->setDistanceX(space_x - (all_zones.back()->getPos().getX()));
    all_zones.back()->setDistanceY(space_y - (all_zones.back()->getPos().getY()));
  }
  for (i = 0; all_zones.at(i)->getPos().getX() < field->getFieldWidth() - ZONE_SIZE; i++) {
    all_zones.push_back(new Zone(ZONE_SIZE, ZONE_SIZE, all_zones.at(i)->getCoefficient() - koef_diff, 0,0,
    Space_Object(all_zones.at(i)->getPos().getX() + ZONE_SIZE, all_zones.at(i)->getPos().getY())));
    all_zones.back()->setDistanceX(space_x - (all_zones.back()->getPos().getX()));
    all_zones.back()->setDistanceY(space_y - (all_zones.back()->getPos().getY()));
  }
  for (i = 0; all_zones.at(i)->getPos().getX() > ZONE_SIZE; i++) {
    all_zones.push_back(new Zone(ZONE_SIZE, ZONE_SIZE, all_zones.at(i)->getCoefficient() - koef_diff, 0,0,
    Space_Object(all_zones.at(i)->getPos().getX() - ZONE_SIZE, all_zones.at(i)->getPos().getY())));
    all_zones.back()->setDistanceX(space_x - (all_zones.back()->getPos().getX()));
    all_zones.back()->setDistanceY(space_y - (all_zones.back()->getPos().getY()));
  }
  // for (int k = 0; k < all_zones.size(); k++) {
  //   move(all_zones.at(k)->getPos().getY(), all_zones.at(k)->getPos().getX());
  //   printw("%.3f", all_zones.at(k)->getCoefficient());
  // }
  return all_zones;
}

void Fuzzy_Controller::calculate_asteroids(vector<Zone *> zones,
                                           Space_Object offset) {
  for (auto &zone : zones) {
    if (offset == zone->getPos()) {
      zone->setCoefficient(zone->getCoefficient() / 2.0);
    }
  }
}


int Fuzzy_Controller::find_optimal_x(vector<Zone *> zones) {
  int min_x = std::numeric_limits<int>::max();
  int min_index = -1;
  for (int i = 0; i < zones.size(); i++) {
    auto& zone = zones[i];
    if (zone->getDistanceX() < min_x && zone->getDistanceX() != 0) {
      min_x = zone->getDistanceX();
      min_index = i;
    }
  }
  return min_index;
}

int Fuzzy_Controller::find_optimal_y(vector<Zone *> zones) {
  int min_y = std::numeric_limits<int>::max();
  int min_index = -1;
  for (int i = 0; i < zones.size(); i++) {
    auto& zone = zones[i];
    if (zone->getDistanceY() < min_y && zone->getDistanceY() != 0) {
      min_y = zone->getDistanceY();
      min_index = i;
    }
  }
  return min_index;
}

int Fuzzy_Controller::find_optimal_coef(vector<Zone *> zones, Spaceship* spaceship) {
  float max_coef = std::numeric_limits<float>::lowest();
  int max_index = -1;
  for (int i = 0; i < zones.size(); i++) {
    auto& zone = zones[i];
    if (zone->getCoefficient() > max_coef && zone->getPos().getX() > 5 && zone->getDistanceY() != 0) {
      max_coef = zone->getCoefficient();
      max_index = i;
    }
  }
  return max_index;
}

void Fuzzy_Controller::rules_to_do(vector<Zone *> zones, Spaceship* spaceship, Field field) {
  // int min_x = zones.at(find_optimal_x(zones))->getPos().getX();
  // int min_y = zones.at(find_optimal_y(zones))->getPos().getY();
  double max_coef = zones.at(find_optimal_coef(zones, spaceship))->getCoefficient();
  // move(21, 30);
  // printw("%d", min_x);
  int min_x = zones.at(find_optimal_coef(zones, spaceship))->getDistanceX();
  int min_y = zones.at(find_optimal_coef(zones, spaceship))->getDistanceY();
  if (min_x > 0 && min_y > 0) {
    spaceship->change_position('a', field);
    spaceship->change_position('w', field);
  }
  if (min_x > 0 && min_y < 0) {
    spaceship->change_position('a', field);
    spaceship->change_position('s', field);
  }
  if (min_x < 0 && min_y > 0) {
    spaceship->change_position('d', field);
    spaceship->change_position('w', field);
  }
  if (min_x < 0 && min_y > 0) {
    spaceship->change_position('d', field);
    spaceship->change_position('s', field);
  }
}