#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "src/rectangle.h"
#include "src/viewport.h"
#include "src/shape.h"

using namespace std;

#define WIDTH 800
#define HEIGHT 800
const static float SCALE_TEMP = 30.f;
void CreateGround(b2World &world);

void updateThing(Shape2D *shape)
{
	shape->updatePhysics();
}
int main()
{
	Viewport2D viewport(sf::Vector2f(WIDTH, HEIGHT), sf::Vector2f(0.f, 9.8f), 60);

	Rectangle2D dog(viewport.world, sf::Vector2f(0, 0), sf::Vector2f(20, 20), 0.f, 0.f, 0.f);

	dog.rectangle.setOrigin(dog.size.x / 2, dog.size.y / 2);
	dog.rectangle.setFillColor(sf::Color(255, 0, 0, 128));
	dog.rectangle.setOutlineColor(sf::Color(255, 0, 0));
	dog.rectangle.setOutlineThickness(1);
	viewport.addPhysicsBody(&dog);
	CreateGround(viewport.world);

	while (viewport.window.isOpen())
	{
		sf::Event event;

		while (viewport.window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				viewport.window.close();
				break;
			case sf::Event::KeyPressed:
				//Ctrl-W or Ctrl-Q
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
					 sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) &&
					(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
				{
					viewport.window.close();
				}
				break;
			default:
				break;
			}
		}
		(viewport.world).Step(1 / 60.f, 8, 3);

		viewport.window.clear(sf::Color::White);

		viewport.updatePhysicsBody();
		viewport.window.draw(dog.rectangle);
		viewport.window.display();
	}
	return EXIT_SUCCESS;
}

void CreateGround(b2World &world)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(0, (HEIGHT) / SCALE_TEMP);
	BodyDef.type = b2_staticBody;
	b2Body *Body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox(WIDTH / SCALE_TEMP, 1);
	b2FixtureDef fix_def;
	fix_def.density = 0.f;
	fix_def.friction = 0.7f;
	fix_def.shape = &Shape;
	Body->CreateFixture(&fix_def);
}
