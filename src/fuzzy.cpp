#include "../includes/fuzzy.h"
#define ZONE_SIZE 5

double pyth(int x, int y) { return sqrt(y * y + x * x); }

int Zone::getDistanceX(Spaceship *spaceship, Zone *zone) {
  return (spaceship->getPos().getX() - zone->getPos().getX());
}

int Zone::getDistanceY(Spaceship *spaceship, Zone *zone) {
  return (spaceship->getPos().getY() - zone->getPos().getY());
}

bool Zone::inside_the_zone(Space_Object object) {
  return object.getX() > (*this).getPos().getX() &&
         (object.getX() < (*this).getPos().getX() + getWidth() ||
          object.getX() < (*this).getPos().getX() - getWidth()) &&
         object.getY() > (*this).getPos().getY() &&
         (object.getY() < (*this).getPos().getY() + getHeight() ||
          object.getY() < (*this).getPos().getY() - getHeight());
}

int Fuzzy_Controller::return_zone_index(Space_Object *object,
                                        vector<Zone *> *zones) {
  for (int i = 0; i < (*zones).size(); i++) {
    if (*object == (*zones)[i]->getPos()) {
      return i;
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
  int space_x = spaceship->getPos().getY(); // просмотр окружения корабля
  int space_y = spaceship->getPos().getY();
  int max_num = (field->getFieldHeight() > field->getFieldWidth())
                    ? ceil(field->getFieldHeight() / (double)ZONE_SIZE)
                    : ceil(field->getFieldWidth() /
                           (double)ZONE_SIZE); // находим число зон
  float koef_diff =
      1.0 / (float)(max_num + ZONE_SIZE); // вычисление коэффициента
  all_zones.push_back(
      new Zone(ZONE_SIZE, ZONE_SIZE, 1,
               Space_Object(space_x - 1, space_y - 1))); // зона с кораблем
  int i = 0;
  // занесение зон в вектор
  all_zones.push_back(
      new Zone(ZONE_SIZE, ZONE_SIZE, 1 - koef_diff,
               Space_Object(space_x - 1, space_y - ZONE_SIZE - 1)));
  for (i = 1; all_zones.at(i)->getPos().getY() > -1; i++) {
    all_zones.push_back(new Zone(
        ZONE_SIZE, ZONE_SIZE, all_zones.at(i)->getCoefficient() - koef_diff,
        Space_Object(all_zones.at(i)->getPos().getX(),
                     all_zones.at(i)->getPos().getY() - ZONE_SIZE)));
  }
  all_zones.push_back(
      new Zone(ZONE_SIZE, ZONE_SIZE, 1 - koef_diff,
               Space_Object(space_x - 1, space_y + ZONE_SIZE - 1)));
  for (i += 1;
       all_zones.at(i)->getPos().getY() < field->getFieldHeight() - ZONE_SIZE;
       i++) {
    all_zones.push_back(new Zone(
        ZONE_SIZE, ZONE_SIZE, all_zones.at(i)->getCoefficient() - koef_diff,
        Space_Object(all_zones.at(i)->getPos().getX(),
                     all_zones.at(i)->getPos().getY() + ZONE_SIZE)));
  }
  for (i = 0;
       all_zones.at(i)->getPos().getX() < field->getFieldWidth() - ZONE_SIZE;
       i++) {
    all_zones.push_back(new Zone(
        ZONE_SIZE, ZONE_SIZE, all_zones.at(i)->getCoefficient() - koef_diff,
        Space_Object(all_zones.at(i)->getPos().getX() + ZONE_SIZE,
                     all_zones.at(i)->getPos().getY())));
  }
  for (i = 0; all_zones.at(i)->getPos().getX() > ZONE_SIZE; i++) {
    all_zones.push_back(new Zone(
        ZONE_SIZE, ZONE_SIZE, all_zones.at(i)->getCoefficient() - koef_diff,
        Space_Object(all_zones.at(i)->getPos().getX() - ZONE_SIZE,
                     all_zones.at(i)->getPos().getY())));
  }
  return all_zones;
}

void Fuzzy_Controller::calculate_asteroids(vector<Zone *> *zones,
                                           Space_Object offset,
                                           Spaceship *spaceship, Field *field) {
  for (auto &zone : *zones) { // наличие астероида в зоне
    if (zone->inside_the_zone(offset)) {
      zone->setCoefficient(zone->getCoefficient() / 2.0);
      if (zone->inside_the_zone(spaceship->getPos()))
        asteroid_and_spaceship_in_zone(zone, spaceship, &offset, field);
    }
  }
}

int Fuzzy_Controller::find_optimal_x(vector<Zone *> *zones,
                                     Spaceship *spaceship) {
  int min_x = std::numeric_limits<int>::max();
  int min_index = -1;
  for (int i = 0; i < (*zones).size(); i++) {
    auto &zone = (*zones)[i];
    if (zone->getDistanceX(spaceship, zone) < min_x &&
        zone->getDistanceX(spaceship, zone) != 0) {
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
  for (int i = 0; i < (*zones).size(); i++) {
    auto &zone = (*zones)[i];
    if (zone->getDistanceY(spaceship, zone) < min_y &&
        zone->getDistanceY(spaceship, zone) != 0) {
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
  for (int i = 5; i < (*zones).size();
       i++) { // поиск зоны с максимальным коэффициентом
    auto &zone = (*zones)[i];
    if (zone->getCoefficient() > max_coef &&
        zone->getDistanceY(spaceship, zone) != 0) {
      max_coef = zone->getCoefficient();
      max_index = i;
    }
  }
  return max_index;
}

void Fuzzy_Controller::rules_to_do(vector<Zone *> *zones, Spaceship *spaceship,
                                   Field *field) {
  int ind = find_optimal_coef(zones, spaceship);
  // int min_x = zones.at(find_optimal_x(zones))->getPos().getX();
  // int min_y = zones.at(find_optimal_y(zones))->getPos().getY();
  // move(zones.at(ind)->getPos().getY(), zones.at(ind)->getPos().getX());
  // printw("%.2f", zones.at(ind)->getCoefficient());
  int min_x = zones->at(ind)->getDistanceX(spaceship, (*zones).at(ind));
  int min_y = zones->at(ind)->getDistanceY(spaceship, (*zones).at(ind));
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
}

void Fuzzy_Controller::asteroid_and_spaceship_in_zone(Zone *zone,
                                                      Spaceship *spaceship,
                                                      Space_Object* ast_point,
                                                      Field *field) {
  // for (int i = 0; i < zone->getWidth(); i++) {
  //   for (int j = 0; j < zone->getHeight(); j++) {
      int ast_pos_x = ast_point->getX();
      int ship_pos_x = spaceship->getPos().getX();
      int ast_pos_y = ast_point->getY();
      int ship_pos_y = spaceship->getPos().getY();
      if (ast_pos_x > ship_pos_x)
        spaceship->change_position('a', *field);
      if (ast_pos_x < ship_pos_x)
        spaceship->change_position('d', *field);
      if (ast_pos_y > ship_pos_y)
        spaceship->change_position('w', *field);
      if (ast_pos_y < ship_pos_y)
        spaceship->change_position('s', *field);
    }
//   }
// }
