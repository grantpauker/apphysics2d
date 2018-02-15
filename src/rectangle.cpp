#include "shape.h"
#include "rectangle.h"
#include "viewport.h"
#include "body_data.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

Rectangle2D::Rectangle2D(b2World &world, sf::Vector2f pos, sf::Vector2f size, float density, float friction, float restitution)
	: pos(pos),
	  size(size),
	  sf::RectangleShape(sf::Vector2f(size.x, size.y))
{
	// rectangle = sf::RectangleShape(sf::Vector2f(size.x, size.y));
	body_def.type = b2_dynamicBody;
	body_def.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	body = world.CreateBody(&body_def);
	body_data = new BodyData;
	body_data->body_type = RECTANGLE;
	body->SetUserData((void *)body_data);
	shape.SetAsBox((size.x / 2) / SCALE, (size.y / 2) / SCALE);
	fix_def.density = density;
	fix_def.friction = friction;
	fix_def.restitution = restitution;
	fix_def.shape = &shape;
	body->CreateFixture(&fix_def);
}
void Rectangle2D::setRestitution(float r)
{
	// fix_def.restitution = r;
	// body->CreateFixture(&fix_def);
	body->SetTransform(b2Vec2(0.f, 0.f), 0.f);
}
void Rectangle2D::updatePhysics()
{
	setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
	setRotation(body->GetAngle() * 180 / b2_pi);
}
sf::Vector2f Rectangle2D::getSize()
{
	return size;
}
sf::Vector2f Rectangle2D::getPosition()
{
	b2Vec2 position = body->GetPosition();
	position *= SCALE;
	return sf::Vector2f(position.x, position.y);
}
b2Body *Rectangle2D::getBody()
{
	return body;
}
bool Rectangle2D::isCollisionWith(Rectangle2D collider)
{
	return std::find(body_data->collisions.begin(), body_data->collisions.end(), collider.body_data->id) != body_data->collisions.end();
}
bool Rectangle2D::isCollision()
{
	return !(body_data->collisions.empty());
}
// void Rectangle2D::setFillColor(const sf::Color &color)
// {
// 	rectangle.setFillColor(color);
// }
// void Rectangle2D::setOutlineColor(const sf::Color &color)
// {
// 	rectangle.setOutlineColor(color);
// }
// void Rectangle2D::setOutlineThickness(float thickness)
// {
// 	rectangle.setOutlineThickness(thickness);
// }
// void Rectangle2D::setTexture(const sf::Texture *texture, bool resetRect = false)
// {
// 	rectangle.setTexture(texture, resetRect);
// }
// void Rectangle2D::setTextureRect(const sf::IntRect &rect)
// {
// 	rectangle.setTextureRect(rect);
// }
