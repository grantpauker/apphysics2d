#ifndef H_RECTANGLE
#define H_RECTANGLE
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "shape.h"
#include "body_data.h"
#include "utils.h"

/*
TODO
 setOrigin
*/
class Rectangle2D : public Shape2D, public sf::RectangleShape
{
public:
	// void setFillColor(const sf::Color &color);
	// void setOutlineColor(const sf::Color &color);
	// void setOutlineThickness(float thickness);
	// void setTexture(const sf::Texture *texture, bool resetRect = false);
	// void setTextureRect(const sf::IntRect &rect);

	Rectangle2D(b2World &world, bodyType type, sf::Vector2f _pos, sf::Vector2f _size, float density, float friction, float resitiution);
	void updatePhysics();
	void setRestitution(float r);
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	b2Body *getBody();
	bool isCollisionWith(Rectangle2D collider);
	bool isCollision();

	BodyData *body_data;

protected:
	const float SCALE = 30.f;

private:
	sf::Vector2f pos;
	sf::Vector2f size;

	b2Body *body;	
	b2BodyDef body_def;
	b2PolygonShape shape;
	b2FixtureDef fix_def;

	using sf::RectangleShape::move;
	using sf::RectangleShape::rotate;
	using sf::RectangleShape::scale;
	using sf::RectangleShape::setPosition;
	using sf::RectangleShape::setRotation;
	using sf::RectangleShape::setScale;
	using sf::RectangleShape::setScale;
	using sf::RectangleShape::setSize;
};
#endif
