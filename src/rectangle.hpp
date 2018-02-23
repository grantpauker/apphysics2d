#ifndef H_RECTANGLE
#define H_RECTANGLE
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "shape.hpp"
#include "body_data.hpp"
#include "utils.hpp"
#include "vector.hpp"
#include "color.hpp"
//DO SET_SCALE
class Rectangle2D : public Shape2D
{
  public:
	Rectangle2D(b2World &world, bodyType type, VectorF2D pos, VectorF2D size, float density, float friction, float resitiution);
	sf::Drawable *getShape();			// UNCHANGABLE TYPE
	sf::RectangleShape *getRect_TEMP(); // UNCHANGABLE TYPE

	void updatePhysics();
	void setRestitution(float r);

	b2Body *getBody(); // UNCHANGABLE TYPE
	bool isCollisionWith(Rectangle2D collider);
	bool isCollision();

	int getPointCount();
	VectorF2D getPoint(unsigned int index)
	{
		return VectorF2D(rectangle.getPoint(index));
	}
	// void 	setTexture (const Texture *texture, bool resetRect=false)
	// void 	setTextureRect (const IntRect &rect)
	void setFillColor(Color2D color)
	{
		rectangle.setFillColor(color);
	}
	void setOutlineColor(Color2D color)
	{
		rectangle.setOutlineColor(color);
	}
	void setOutlineThickness(float thickness)
	{
		rectangle.setOutlineThickness(thickness);
	}
	// const Texture * 	getTexture () const
	// const IntRect & 	getTextureRect () const
	Color2D getFillColor()
	{
		return rectangle.getFillColor();
	}

	Color2D getOutlineColor()
	{
		return rectangle.getOutlineColor();
	}
	float getOutlineThickness()
	{
		return rectangle.getOutlineThickness();
	}
	// FloatRect 	getLocalBounds () const
	// FloatRect 	getGlobalBounds () const
	// void 	setPosition (float x, float y)
	// void 	setPosition (const Vector2f &position)
	// void 	setRotation (float angle)
	void setSize(float x, float y);
	void setOrigin(float x, float y)
	{
		rectangle.setOrigin(x, y);
	}

	VectorF2D getPosition()
	{
		b2Vec2 position = body->GetPosition();
		position *= SCALE;
		return VectorF2D(position.x, position.y);
	}
	// float 	getRotation () const
	VectorF2D getSize()
	{
		return size;
	}
	// const Vector2f & 	getOrigin () const
	// void 	move (float offsetX, float offsetY)
	// void 	move (const Vector2f &offset)
	// void 	rotate (float angle)
	// void 	scale (float factorX, float factorY)
	// void 	scale (const Vector2f &factor)
	// const Transform & 	getTransform () const
	// const Transform & 	getInverseTransform () const
	BodyData *body_data;

  protected:
	const float SCALE = 30.f;

  private:
	VectorF2D pos;
	VectorF2D size;
	sf::RectangleShape rectangle;

	b2Body *body;
	b2BodyDef body_def;
	b2PolygonShape shape;
	b2FixtureDef fix_def;
	b2Fixture *fixture;
};
#endif
