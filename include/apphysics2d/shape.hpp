#ifndef H_SHAPE
#define H_SHAPE
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
class Shape2D
{
  public:
	virtual void updatePhysics() = 0;
  virtual sf::Drawable* getShape() = 0;
};
#endif
