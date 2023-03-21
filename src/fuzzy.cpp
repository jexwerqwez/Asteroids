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

vector<Zone*> Fuzzy_Controller::optimal_position(Field* field, Asteroids_Manager* manager, Spaceship* spaceship) {
  vector<Zone*> all_zones;
  int space_x = spaceship->getPos().getX(); // просмотр окружения корабля
  int space_y = spaceship->getPos().getY();
  int max_num = (field->getFieldHeight() > field->getFieldWidth()) ? 
                ceil(field->getFieldHeight() / 3.0) : ceil(field->getFieldWidth() / 3.0);
  float koef_diff = 1.0/(float)max_num;
  all_zones.push_back(new Zone(space_y, space_x + 1, 1)); // зона с кораблем
  int i = 0;
  all_zones.push_back(new Zone(space_y - 2, space_x, 1 - koef_diff));
  for (i = 1; all_zones.at(i)->getHeight() > 3; i++) {
    all_zones.push_back(new Zone(all_zones.at(i)->getHeight() - 3, 
    all_zones.at(i)->getWidth(), all_zones.at(i)->getCoefficient() - koef_diff));
  }
  all_zones.push_back(new Zone(space_y + 2, space_x, 1 - koef_diff));
  for (i += 1; all_zones.at(i)->getHeight() < field->getFieldHeight() - 3; i++) {
    all_zones.push_back(new Zone(all_zones.at(i)->getHeight() + 3, all_zones.at(i)->getWidth(), all_zones.at(i)->getCoefficient() - koef_diff));
  }
  for (i = 0; all_zones.at(i)->getWidth() < field->getFieldWidth() - 3; i++) {
    all_zones.push_back(new Zone(all_zones.at(i)->getHeight(), all_zones.at(i)->getWidth() + 3, all_zones.at(i)->getCoefficient() - koef_diff));
  }
  for (i = 0; all_zones.at(i)->getWidth() > 3; i++) {
    all_zones.push_back(new Zone(all_zones.at(i)->getHeight(), all_zones.at(i)->getWidth() - 3, all_zones.at(i)->getCoefficient() - koef_diff));
  }
  // for (int k = 0; k < all_zones.size(); k++) {
  //   move(all_zones.at(k)->getHeight(), all_zones.at(k)->getWidth());
  //   printw("%.3f" ,all_zones.at(k)->getCoefficient());
  // }
  return all_zones;
}
