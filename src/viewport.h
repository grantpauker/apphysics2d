#ifndef H_VIEWPORT
#define H_VIEWPORT
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "shape.h"
#include "collision_handler.h"

class Viewport2D
{
  public:
	const float SCALE = 30.f;

	sf::RenderWindow window;
	b2World world;
	std::vector<Shape2D *> physics_bodies;
	Viewport2D(sf::Vector2f size, sf::Vector2f gravity, unsigned int fps = 60U, unsigned int bitsPerPixel = 32U);
	void addPhysicsBody(Shape2D *shape);
	void updatePhysicsBody();

  private:
	CollisionHandler2D collision_handler;
};
#endif
