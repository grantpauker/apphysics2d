#include "shape.h"
#include "rectangle.h"
#include "viewport.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

Rectangle2D::Rectangle2D(b2World &world, sf::Vector2f _pos, sf::Vector2f size, float density, float friction, float restitution)
{
	rectangle = sf::RectangleShape(sf::Vector2f(size.x, size.y));
	size = size;
	body_def.position = b2Vec2(pos.x, pos.y);
	body_def.type = b2_dynamicBody;
	body = world.CreateBody(&body_def);

	shape.SetAsBox((size.x / 2) / SCALE, (size.y / 2) / SCALE);
	fix_def.density = 1.f;
	fix_def.restitution = 1.f;
	fix_def.shape = &shape;
	body->CreateFixture(&fix_def);
}
void Rectangle2D::updatePhysics()
{
	rectangle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
	rectangle.setRotation(body->GetAngle() * 180 / b2_pi);
}
