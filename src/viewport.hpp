#ifndef H_VIEWPORT
#define H_VIEWPORT
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "shape.hpp"
#include "collision_handler.hpp"
#include "vector.hpp"

class Viewport2D
{
  public:
	const float SCALE = 30.f;

	sf::RenderWindow window;
	b2World world;
	std::vector<Shape2D *> physics_bodies;
	Viewport2D(VectorU2D size, VectorF2D gravity, unsigned int fps = 60U, unsigned int bitsPerPixel = 32U);
	void addPhysicsBody(Shape2D *shape);
	void updatePhysicsBody();
	void draw(Shape2D *shape);

  private:
	CollisionHandler2D collision_handler;
};
#endif
