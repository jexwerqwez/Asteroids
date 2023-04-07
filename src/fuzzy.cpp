#include "../includes/fuzzy.h"
#define ZONE_SIZE 6

double pyth(int x, int y) { return sqrt(y * y + x * x); }

int Fuzzy_Controller::return_zone_index(Space_Object object,
                                        vector<Zone *> *zones) {
  for (int i = 0; i < zones->size(); i++) {
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
  all_rules.push_back(new Rule(VLC, AND, VSD, VLP));
  all_rules.push_back(new Rule(VLC, AND, SD, VLP));
  all_rules.push_back(new Rule(VLC, AND, MD, MP));
  all_rules.push_back(new Rule(VLC, AND, LD, SP));
  all_rules.push_back(new Rule(VLC, AND, VLD, VSP));

  all_rules.push_back(new Rule(VLC, AND, VSD, VLP));
  all_rules.push_back(new Rule(VLC, AND, SD, LP));
  all_rules.push_back(new Rule(VLC, AND, MD, MP));
  all_rules.push_back(new Rule(VLC, AND, LD, SP));
  all_rules.push_back(new Rule(VLC, AND, VLD, VSP));

  all_rules.push_back(new Rule(VLC, AND, VSD, LP));
  all_rules.push_back(new Rule(VLC, AND, SD, MP));
  all_rules.push_back(new Rule(VLC, AND, MD, MP));
  all_rules.push_back(new Rule(VLC, AND, LD, SP));
  all_rules.push_back(new Rule(VLC, AND, VLD, VSP));

  all_rules.push_back(new Rule(VLC, AND, VSD, SP));
  all_rules.push_back(new Rule(VLC, AND, SD, SP));
  all_rules.push_back(new Rule(VLC, AND, MD, VSP));
  all_rules.push_back(new Rule(VLC, AND, LD, VSP));
  all_rules.push_back(new Rule(VLC, AND, VLD, VSP));

  all_rules.push_back(new Rule(VLC, AND, VSD, SP));
  all_rules.push_back(new Rule(VLC, AND, SD, VSP));
  all_rules.push_back(new Rule(VLC, AND, MD, VSP));
  all_rules.push_back(new Rule(VLC, AND, LD, VSP));
  all_rules.push_back(new Rule(VLC, AND, VLD, VSP));
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
  // занесение зон в вектор
  all_zones.push_back(
      new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0,
               Space_Object(space_x - 1, space_y - ZONE_SIZE -
                                             (int)(ZONE_SIZE / 2)))); // вверх
  for (i = 1; all_zones.at(i)->getPos().getY() > -1; i++) {
    all_zones.push_back(
        new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0,
                 Space_Object(all_zones.at(i)->getPos().getX(),
                              all_zones.at(i)->getPos().getY() - ZONE_SIZE)));
  }
  all_zones.push_back(
      new Zone(ZONE_SIZE, ZONE_SIZE, 1, 0,
               Space_Object(space_x - 1, space_y + ZONE_SIZE -
                                             (int)(ZONE_SIZE / 2)))); // вниз
  for (i += 1;
       all_zones.at(i)->getPos().getY() < field->getFieldHeight() - ZONE_SIZE;
       i++) {
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
      zone->setCoefficient(zone->getCoefficient() - koef_diff);
    }
  }
}

int Fuzzy_Controller::find_optimal_x(vector<Zone *> *zones,
                                     Spaceship *spaceship) {
  int min_x = std::numeric_limits<int>::max();
  int min_index = -1;
  for (int i = 0; i < zones->size(); i++) {
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
  for (int i = 0; i < zones->size(); i++) {
    auto &zone = (*zones)[i];
    if (zone->getDistanceY(spaceship, zone) < min_y) {
      min_y = zone->getDistanceY(spaceship, zone);
      min_index = i;
    }
  }
  return min_index;
}

int Fuzzy_Controller::find_optimal_coef(vector<Zone *> *zones,
                                        Spaceship *spaceship) {
  float max_coef = std::numeric_limits<float>::lowest();
  int max_index = -1;
  for (int i = 0; i < zones->size();
       i++) { // поиск зоны с максимальным коэффициентом
    auto &zone = (*zones)[i];
    if (zone->getCoefficient() > max_coef) {
      max_coef = zone->getCoefficient();
      max_index = i;
    }
  }
  return max_index;
}

void Fuzzy_Controller::rules_to_do(vector<Zone *> *zones, Spaceship *spaceship,
                                   Field *field) {
  int ind = find_optimal_coef(zones, spaceship);
  int min_x = zones->at(ind)->getDistanceX(spaceship, zones->at(ind));
  int min_y = zones->at(ind)->getDistanceY(spaceship, zones->at(ind));
  while (spaceship->getPos() != zones->at(ind)->getPos()) {
    if (min_x > 0)
      spaceship->change_position('a', *field);
    if (min_y > 0)
      spaceship->change_position('w', *field);
    if (min_y < 0)
      spaceship->change_position('s', *field);
    if (min_x < 0)
      spaceship->change_position('d', *field);
  }
  // move(zones->at(ind)->getPos().getY(), zones->at(ind)->getPos().getX());
  // printw("%f", zones->at(ind)->getCoefficient());
}

char Fuzzy_Controller::path_check(Zone *zone, Space_Object spaceship,
                                  Space_Object ast_point, Field *field) {
  if (spaceship.getX() - 1 == ast_point.getX() &&
      spaceship.getX() + 1 != ast_point.getX())
    return 'd';
  if (spaceship.getX() + 1 == ast_point.getX() &&
      spaceship.getX() - 1 != ast_point.getX())
    return 'a';
  if (spaceship.getY() - 1 == ast_point.getY() &&
      spaceship.getY() + 1 != ast_point.getY())
    return 's';
  if (spaceship.getY() + 1 == ast_point.getY() &&
      spaceship.getY() - 1 != ast_point.getY())
    return 'w';
  return '0';
}