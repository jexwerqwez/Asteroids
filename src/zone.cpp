#include "../includes/zone.h"

int Zone::rejection(int input, Field *field) {
  int ret = Z;
  if (abs(input) >= field->getFieldHeight() - 3) {
    ret = (input > 0) ? PB : NB;
  } else if (abs(input) >= field->getFieldHeight() / 2) {
    ret = (input > 0) ? PM : NM;
  } else if (abs(input) > ZONE_SIZE) {
    ret = (input > 0) ? PS : NS;
  } else if (abs(input) <= ZONE_SIZE) {
    ret = (input > 0) ? ZP : ZN;
  } else {
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

void Zone::priority_processing(Spaceship *spaceship, Zone *zone) {
  float dist_y = abs(zone->getDistanceY(spaceship, zone));
  float dist_x = abs(zone->getDistanceX(spaceship, zone));
  double distance = pyth(dist_x, dist_y);
  double vsd_dist = pyth(VSD * zone->getWidth(), VSD * zone->getHeight());
  double sd_dist = pyth(SD * zone->getWidth(), VSD * zone->getHeight());
  double md_dist = pyth(MD * zone->getWidth(), VSD * zone->getHeight());
  double ld_dist = pyth(LD * zone->getWidth(), SD * zone->getHeight());
  double vld_dist = pyth(VLD * zone->getWidth(), SD * zone->getHeight());
  if (zone->getCoefficient() >= VLC) { // очень большой коэффициент
    if (distance >= vsd_dist && distance < sd_dist) {
      zone->setPriority(VLP);
    } else if (distance >= sd_dist && distance < md_dist) {
      zone->setPriority(VLP);
    } else if (distance >= md_dist && distance < ld_dist) {
      zone->setPriority(MP);
    } else if (distance >= ld_dist && distance < vld_dist) {
      zone->setPriority(SP);
    } else {
      zone->setPriority(VSP);
    }
  } else if (zone->getCoefficient() >= LC &&
             zone->getCoefficient() < VLC) { // большой коэффициент
    if (distance >= vsd_dist && distance < sd_dist) {
      zone->setPriority(VLP);
    } else if (distance >= sd_dist && distance < md_dist) {
      zone->setPriority(LP);
    } else if (distance >= md_dist && distance < ld_dist) {
      zone->setPriority(MP);
    } else if (distance >= ld_dist && distance < vld_dist) {
      zone->setPriority(SP);
    } else {
      zone->setPriority(VSP);
    }
  } else if (zone->getCoefficient() >= MC && zone->getCoefficient() < LC) {
    if (distance >= vsd_dist && distance < sd_dist) {
      zone->setPriority(LP);
    } else if (distance >= sd_dist && distance < md_dist) {
      zone->setPriority(MP);
    } else if (distance >= md_dist && distance < ld_dist) {
      zone->setPriority(MP);
    } else if (distance >= ld_dist && distance < vld_dist) {
      zone->setPriority(SP);
    } else {
      zone->setPriority(VSP);
    }
  } else if (zone->getCoefficient() >= SC && zone->getCoefficient() < MC) {
    if (distance >= vsd_dist && distance < sd_dist) {
      zone->setPriority(MP);
    } else if (distance >= sd_dist && distance < md_dist) {
      zone->setPriority(SP);
    } else if (distance >= md_dist && distance < ld_dist) {
      zone->setPriority(SP);
    } else if (distance >= ld_dist && distance < vld_dist) {
      zone->setPriority(VSP);
    } else {
      zone->setPriority(VSP);
    }
  } else if (zone->getCoefficient() >= VSC && zone->getCoefficient() < SC) {
    if (distance >= vsd_dist && distance < sd_dist) {
      zone->setPriority(SP);
    } else if (distance >= sd_dist && distance < md_dist) {
      zone->setPriority(VSP);
    } else if (distance >= md_dist && distance < ld_dist) {
      zone->setPriority(VSP);
    } else if (distance >= ld_dist && distance < vld_dist) {
      zone->setPriority(VSP);
    } else {
      zone->setPriority(VSP);
    }
  }
}