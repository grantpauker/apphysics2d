#ifndef H_RECTANGLE
#define H_RECTANGLE
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "shape.h"

class Rectangle2D : public Shape2D
{
  public:
	const float SCALE = 30.f;

	sf::RectangleShape rectangle;
	sf::Vector2f pos;
	sf::Vector2f size;

	b2Body *body;
	b2BodyDef body_def;
	b2PolygonShape shape;
	b2FixtureDef fix_def;

	Rectangle2D(b2World &world, sf::Vector2f _pos, sf::Vector2f _size, float density, float friction, float resitiution);
	void updatePhysics();
};
#endif
