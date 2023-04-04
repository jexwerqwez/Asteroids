#ifndef ZONE
#define ZONE
#include "base.h"
#include "objects.h"
#include "spaceship.h"

/**
 * @brief Класс зон поля
 * @param height высота зоны
 * @param width ширина зону
 * @param coefficient весовой коэффициент зоны: чем ближе к 1, тем он оптимальнее
**/
class Zone: public Space_Object {
  int height;
  int width;
  float coefficient;
protected:
  Space_Object position;
public:
  Zone(int h, int w, float coef, Space_Object pos) 
  : height(h), width(w), coefficient(coef), position(pos) {};
  /** @brief получение высоты зоны */
  int getHeight() {return height;}
  /** @brief получение ширины зоны */
  int getWidth() {return width;}
  /** @brief получение коэффициента зоны */
  float getCoefficient() {return coefficient;}
  /** @brief установка коэффициента зоны */
  void setCoefficient(float c) {coefficient = c;}
  /** @brief получение расстояния от Spaceship до зоны по оси X 
   * @return возвращает значение > 0, если зона находится левее от местоположения Spaceship
   * и < 0, если правее
  */
  int getDistanceX(Spaceship*, Zone*);
  /** @brief получение расстояния от Spaceship до зоны по оси Y 
   * @return возвращает значение > 0, если зона находится выше от местоположения Spaceship
   * и < 0, если ниже
  */
  int getDistanceY(Spaceship*, Zone*);
  /** @brief получение позиции зоны на поле */
  Space_Object getPos() { return position; };
  /** @brief проверка есть ли объект внутри зоны */
  bool inside_the_zone(Space_Object);
};
#endif