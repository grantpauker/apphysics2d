#include "viewport.h"
#include "shape.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

Viewport2D::Viewport2D(sf::Vector2f size, sf::Vector2f gravity, unsigned int fps, unsigned int bitsPerPixel)
	: window(sf::VideoMode(size.x, size.y, 32U), "AP Physics 2D"),
	  world{b2World(b2Vec2(gravity.x, gravity.y))}
{
	window.setFramerateLimit(fps);
}
void Viewport2D::addPhysicsBody(Shape2D *shape)
{
	body_list.push_back(shape);
}
void Viewport2D::updatePhysicsBody()
{
	for (std::vector<Shape2D *>::iterator it = body_list.begin(); it != body_list.end(); ++it)
	{
		(*it)->updatePhysics();
	}
}
