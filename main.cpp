#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <ctime>
#include <chrono>

#include <Box2D/Box2D.h>
#include "src/rectangle.h"
#include "src/viewport.h"
#include "src/shape.h"
#include "src/body_data.h"
#include "src/collision_handler.h"
#include "src/utils.h"

using namespace std;

#define WIDTH 800
#define private punbl
#define HEIGHT 800
#define NOW() std::chrono::high_resolution_clock::now()
#define START() std::chrono::high_resolution_clock::time_point start = NOW()
#define END() std::cout << "time: " << (float)std::chrono::duration_cast<std::chrono::microseconds>(NOW() - start).count() / 1000 << std::endl

const static float SCALE_TEMP = 30.f;
// void CreateGround(b2World &world);
void CreateWalls(b2World &world);

int main()
{
	srand(time(NULL));
	Viewport2D viewport(sf::Vector2f(WIDTH, HEIGHT), sf::Vector2f(0.f, 9.8f), 60);

	Rectangle2D dog(viewport.world, dynamic2D, sf::Vector2f(300, 100), sf::Vector2f(20, 20), 1.f, 0.5f, 0.9f);

	Rectangle2D ground(viewport.world, static2D, sf::Vector2f(WIDTH/2, HEIGHT), sf::Vector2f(WIDTH, 50), 1.f, 0.5f, 0.9f);

	dog.setOrigin(dog.getSize().x / 2, dog.getSize().y / 2);
	dog.setFillColor(sf::Color(255, 0, 0, 128));
	dog.setOutlineColor(sf::Color(255, 0, 0));
	dog.setOutlineThickness(1);
	viewport.addPhysicsBody(&dog);

	ground.setOrigin(ground.getSize().x / 2, ground.getSize().y / 2);
	ground.setFillColor(sf::Color(255, 0, 0, 128));
	ground.setOutlineColor(sf::Color(255, 0, 0));
	ground.setOutlineThickness(1);
	viewport.addPhysicsBody(&ground);

	CreateWalls(viewport.world);
	sf::Clock clock;

	while (viewport.window.isOpen())
	{
		sf::Time time = clock.getElapsedTime();
		float seconds = time.asSeconds();
		// cout << seconds << endl;

		if (seconds > 1.9 && seconds < 2.1)
		{
			dog.getBody()->SetLinearVelocity(b2Vec2(10.f, dog.getBody()->GetLinearVelocity().y));
		}

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
		viewport.world.Step(1 / 60.f, 8, 3);

		viewport.window.clear(sf::Color::White);
		viewport.updatePhysicsBody();
		viewport.window.draw(dog);
		viewport.window.draw(ground);

		viewport.window.display();
		// START();
		// // if (dog.isCollision())
		// // {
		// // 	cout << "Collision\n";
		// // }
		// END();
	}
	return EXIT_SUCCESS;
}

void CreateWalls(b2World &world)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(WIDTH / SCALE_TEMP, 0);
	BodyDef.type = b2_staticBody;
	b2Body *Body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox(1, HEIGHT / SCALE_TEMP);
	b2FixtureDef fix_def;
	fix_def.density = 0.f;
	fix_def.friction = 0.7f;
	fix_def.shape = &Shape;
	Body->CreateFixture(&fix_def);

	BodyDef.position = b2Vec2(0, 0);
	BodyDef.type = b2_staticBody;
	Body = world.CreateBody(&BodyDef);

	Shape;
	Shape.SetAsBox(1, HEIGHT / SCALE_TEMP);
	fix_def;
	fix_def.density = 0.f;
	fix_def.friction = 0.7f;
	fix_def.shape = &Shape;
	Body->CreateFixture(&fix_def);
}
