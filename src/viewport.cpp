#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "apphysics2d/viewport.hpp"
#include "apphysics2d/shape.hpp"
#include "apphysics2d/collision_handler.hpp"
#include "apphysics2d/vector.hpp"

Viewport2D::Viewport2D(VectorU2D size, VectorF2D gravity, unsigned int fps, unsigned int bitsPerPixel)
	: window(sf::VideoMode(size.x, size.y, 32U), "AP Physics 2D"),
	  world{b2World(b2Vec2(gravity.x, gravity.y))}
{
	window.setFramerateLimit(fps);
	world.SetContactListener(&collision_handler);
}
void Viewport2D::addPhysicsBody(Shape2D *shape)
{
	physics_bodies.push_back(shape);
}
void Viewport2D::updatePhysicsBody()
{
	for (std::vector<Shape2D *>::iterator it = physics_bodies.begin(); it != physics_bodies.end(); ++it)
	{
		(*it)->updatePhysics();
	}
}

void Viewport2D::draw(Shape2D *shape)
{
	window.draw(*shape->getShape());
}
