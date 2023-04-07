#include "../includes/zone.h"

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