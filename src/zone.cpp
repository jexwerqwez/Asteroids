#include "../includes/zone.h"

int Zone::rejection(int input, Field *field, char side) {
  int ret = Z;
  int value = 0;
  if (side == 'X') {
    value = field->getFieldWidth();
  } else if (side == 'Y') {
    value = field->getFieldHeight();
  }
  if (abs(input) >= value - 3) {
    ret = (input > 0) ? PB : NB;
  } else if (abs(input) > ZONE_SIZE * 4 && abs(input) < value - 3) {
    ret = (input > 0) ? PM : NM;
  } else if (abs(input) > ZONE_SIZE * 2 && abs(input) <= ZONE_SIZE * 4) {
    ret = (input > 0) ? PS : NS;
  } else if (abs(input) > ZONE_SIZE && abs(input) <= 2 * ZONE_SIZE) {
    ret = (input > 0) ? ZP : ZN;
  } else if (abs(input) <= ZONE_SIZE) {
    ret = Z;
  }
  return ret;
}

double pyth(int x, int y) { return sqrt(y * y + x * x); }

int Zone::getDistanceX(Spaceship *spaceship, Zone *zone) {
  return (spaceship->getPos().getX() - zone->getPos().getX());
}

int Zone::getDistanceY(Spaceship *spaceship, Zone *zone) {
  return (spaceship->getPos().getY() - zone->getPos().getY());
}

bool Zone::inside_the_zone(Space_Object object) {
  return object.getX() > this->getPos().getX() &&
         (object.getX() < this->getPos().getX() + getWidth()) &&
         object.getY() > this->getPos().getY() &&
         (object.getY() < this->getPos().getY() + getHeight());
}

// void Zone::set_all_cell(Zone* zone, float coef) {
//   for (int i = 0; i < zone->getHeight(); i++) {
//     for (int j = 0; j < zone->getWidth(); j++) {
//       zone.
//     }
//   }
// }

void Zone::priority_processing(Spaceship *spaceship, Zone *zone) {
  float dist_y = abs(zone->getDistanceY(spaceship, zone));
  float dist_x = abs(zone->getDistanceX(spaceship, zone));
  double distance = pyth(dist_x, dist_y); // рассчитали гипотенузу
  // устанавливаем константы расстояний
  const double vsd_dist = 0;
  const double sd_dist =
      pyth(zone->getSettings()->fuzzy_dist[3] * zone->getWidth(),
           zone->getSettings()->fuzzy_dist[3] * zone->getHeight());
  const double md_dist =
      pyth(zone->getSettings()->fuzzy_dist[2] * zone->getWidth(),
           zone->getSettings()->fuzzy_dist[2] * zone->getHeight());
  const double ld_dist =
      pyth(zone->getSettings()->fuzzy_dist[1] * zone->getWidth(),
           zone->getSettings()->fuzzy_dist[1] * zone->getHeight());
  const double vld_dist =
      pyth(zone->getSettings()->fuzzy_dist[0] * zone->getWidth(),
           zone->getSettings()->fuzzy_dist[0] * zone->getHeight());
  if (zone->getCoefficient() >=
      zone->getSettings()->fuzzy_coef[0]) { // очень большой коэффициент
    if (distance >= vsd_dist && distance < sd_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[4]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[0]);
    } else if (distance >= sd_dist && distance < md_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[3]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[0]);
    } else if (distance >= md_dist && distance < ld_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[2]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[0]);
    } else if (distance >= ld_dist && distance < vld_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[1]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[1]);
    } else {
      zone->setDistance(zone->getSettings()->fuzzy_dist[0]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[1]);
    }
  } else if (zone->getCoefficient() >= zone->getSettings()->fuzzy_coef[1] &&
             zone->getCoefficient() <
                 zone->getSettings()->fuzzy_coef[0]) { // большой коэффициент
    if (distance >= vsd_dist && distance < sd_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[4]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[0]);
    } else if (distance >= sd_dist && distance < md_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[3]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[0]);
    } else if (distance >= md_dist && distance < ld_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[2]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[1]);
    } else if (distance >= ld_dist && distance < vld_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[1]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[1]);
    } else {
      zone->setDistance(zone->getSettings()->fuzzy_dist[0]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[2]);
    }
  } else if (zone->getCoefficient() >= zone->getSettings()->fuzzy_coef[2] &&
             zone->getCoefficient() < zone->getSettings()->fuzzy_coef[1]) {
    if (distance >= vsd_dist && distance < sd_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[4]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[2]);
    } else if (distance >= sd_dist && distance < md_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[3]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[3]);
    } else if (distance >= md_dist && distance < ld_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[2]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[3]);
    } else if (distance >= ld_dist && distance < vld_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[1]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[4]);
    } else {
      zone->setDistance(zone->getSettings()->fuzzy_dist[0]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[4]);
    }
  } else if (zone->getCoefficient() >= zone->getSettings()->fuzzy_coef[3] &&
             zone->getCoefficient() < zone->getSettings()->fuzzy_coef[2]) {
    if (distance >= vsd_dist && distance < sd_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[4]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[3]);
    } else if (distance >= sd_dist && distance < md_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[3]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[3]);
    } else if (distance >= md_dist && distance < ld_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[2]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[4]);
    } else if (distance >= ld_dist && distance < vld_dist) {
      zone->setDistance(zone->getSettings()->fuzzy_dist[1]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[4]);
    } else {
      zone->setDistance(zone->getSettings()->fuzzy_dist[0]);
      zone->setPriority(zone->getSettings()->fuzzy_prio[4]);
    }
  } else if (zone->getCoefficient() >= zone->getSettings()->fuzzy_coef[4] &&
             zone->getCoefficient() < zone->getSettings()->fuzzy_coef[3]) {
    zone->setPriority(zone->getSettings()->fuzzy_prio[4]);
  }
  if (zone->getPos().getY() < 0 || zone->getPos().getX() < 0)
    zone->setPriority(zone->getSettings()->fuzzy_prio[4]);
  // for (int i = 0; i < all_zones.size(); i++) {
  //   move(all_zones.at(i)->getPos().getY(), all_zones.at(i)->getPos().getX());
  //   printw("%d", all_zones.at(i)->getDistance());
  // }
}