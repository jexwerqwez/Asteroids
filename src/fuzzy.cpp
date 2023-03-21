#include "../includes/fuzzy.h"

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
        alpha = (all_rules[i]->getOper() == 1) ? MIN(mf_cur, mf_delt) : MAX(mf_cur, mf_delt);
        num += (alpha * all_rules[i]->getPrev());
        den += alpha;
    }
    return num / den;
}

vector<Zone*> Fuzzy_Controller::optimal_position(Field* field, Spaceship* spaceship) {
  vector<Zone*> all_zones;
  int space_x = spaceship->getPos().getX(); // просмотр окружения корабля
  int space_y = spaceship->getPos().getY();
  int zone_h = 3;
  int zone_w = 3;
  int max_num = (field->getFieldHeight() > field->getFieldWidth()) ? 
                ceil(field->getFieldHeight() / 3.0) : ceil(field->getFieldWidth() / 3.0);
  float koef_diff = 1.0/(float)max_num;
  all_zones.push_back(new Zone(space_y, space_x + 1, zone_h, zone_w, 1)); // зона с кораблем
  int i = 0;
  all_zones.push_back(new Zone(space_y - 2, space_x, zone_h, zone_w, 1 - koef_diff));
  for (i = 1; all_zones.at(i)->getY() > 3; i++) {
    all_zones.push_back(new Zone(all_zones.at(i)->getY() - 3, 
    all_zones.at(i)->getX(), zone_h, zone_w, all_zones.at(i)->getCoefficient() - koef_diff));
  }
  all_zones.push_back(new Zone(space_y + 2, space_x, zone_h, zone_w, 1 - koef_diff));
  for (i += 1; all_zones.at(i)->getY() < field->getFieldHeight() - 3; i++) {
    all_zones.push_back(new Zone(all_zones.at(i)->getY() + 3, all_zones.at(i)->getX(), zone_h, zone_w, all_zones.at(i)->getCoefficient() - koef_diff));
  }
  for (i = 0; all_zones.at(i)->getX() < field->getFieldWidth() - 3; i++) {
    all_zones.push_back(new Zone(all_zones.at(i)->getY(), all_zones.at(i)->getX() + 3, zone_h, zone_w, all_zones.at(i)->getCoefficient() - koef_diff));
  }
  for (i = 0; all_zones.at(i)->getX() > 3; i++) {
    all_zones.push_back(new Zone(all_zones.at(i)->getY(), all_zones.at(i)->getX() - 3, zone_h, zone_w, all_zones.at(i)->getCoefficient() - koef_diff));
  }
  // for (int k = 0; k < all_zones.size(); k++) {
  //   move(all_zones.at(k)->getHeight(), all_zones.at(k)->getWidth());
  //   printw("%.3f" ,all_zones.at(k)->getCoefficient());
  // }
  return all_zones;
}

vector<Zone*> Fuzzy_Controller::calculate_optimal(vector<Zone*> all_zones, Field* field,
                                    vector<Asteroids*> all_asts, Space_Object* offset) {
  int max_num = (field->getFieldHeight() > field->getFieldWidth()) ? 
                field->getFieldHeight() : field->getFieldWidth();
  float koef_diff = 1.0/(float)max_num;                                                                 
  for (long unsigned int q = 0; q < all_zones.size(); q++) {
    int zone_x = all_zones.at(q)->getX();
    int zone_y = all_zones.at(q)->getY();
//     for (int i = all_zones.at(q)->getY(); i > 0; i--) {
//       for (int j = 0; j < all_zones.at(q)->getX(); j++) {
// //         if (all_asts.at(i)->getPos().getX() + offset->getX() == zone_x &&
// //             all_asts.at(i)->getPos().getY() + offset->getY() == zone_y)
//           all_zones.at(i)->setCoefficient(all_zones.at(i)->getCoefficient() - koef_diff);
//       }
    // }
  }
  return all_zones;
}