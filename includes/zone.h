#ifndef ZONE
#define ZONE
#include "base.h"
#include "objects.h"
#include "rules.h"
#include "spaceship.h"
/**
 * @brief Класс зон поля
 * @param height высота зоны
 * @param width ширина зону
 * @param coefficient весовой коэффициент зоны: чем ближе к 1, тем он
 *оптимальнее
 **/
class Zone : public Space_Object {
  int height;
  int width;
  float coefficient;
  int priority;

protected:
  Space_Object position;

public:
  Zone(int h, int w, float coef, int p, Space_Object pos)
      : height(h), width(w), coefficient(coef), priority(p), position(pos){};
  /** @brief получение высоты зоны */
  int getHeight() { return height; }
  /** @brief получение ширины зоны */
  int getWidth() { return width; }
  /** @brief получение коэффициента зоны */
  float getCoefficient() { return coefficient; }
  /** @brief получение приоритета зоны */
  int getPriority() { return priority; }
  /** @brief установка коэффициента зоны */
  void setCoefficient(float c) { coefficient = c; }
  /** @brief установка приоритета зоны */
  void setPriority(int p) { priority = p; }
  /** @brief получение расстояния от Spaceship до зоны по оси X
   * @return возвращает значение > 0, если зона находится левее от
   * местоположения Spaceship и < 0, если правее
   */
  int getDistanceX(Spaceship *, Zone *);
  /** @brief получение расстояния от Spaceship до зоны по оси Y
   * @return возвращает значение > 0, если зона находится выше от местоположения
   * Spaceship и < 0, если ниже
   */
  int getDistanceY(Spaceship *, Zone *);
  /** @brief получение позиции зоны на поле */
  Space_Object getPos() { return position; };
  /** @brief проверка есть ли объект внутри зоны */
  bool inside_the_zone(Space_Object);
  /** @brief установка приоритета зоны по входным данным*/
  void priority_processing(Spaceship *, Zone *);
  /** @brief вычисление отклонения от зоны в терминах НР*/
  int rejection(int, Field *);
};
#endif