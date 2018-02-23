#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <ctime>
#include <chrono>

#include <Box2D/Box2D.h>
#include "src/rectangle.hpp"
#include "src/viewport.hpp"
#include "src/shape.hpp"
#include "src/body_data.hpp"
#include "src/collision_handler.hpp"
#include "src/utils.hpp"
#include "src/color.hpp"
#include "src/vector.hpp"

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
	Viewport2D viewport(VectorU2D(WIDTH, HEIGHT), VectorF2D(0, 9.8), 60);

	Rectangle2D dog(viewport.world, dynamic2D, VectorF2D(300, 100), VectorF2D(20, 20), 1.f, 0.5f, 0.1f);

	Rectangle2D ground(viewport.world, static2D, VectorF2D(WIDTH / 2, HEIGHT), VectorF2D(WIDTH, 50), 1.f, 0.5f, 0.9f);
	dog.getRect_TEMP()->setOrigin(dog.getSize().x / 2, dog.getSize().y / 2);
	dog.getRect_TEMP()->setFillColor(sf::Color(255, 0, 0, 128));
	dog.getRect_TEMP()->setOutlineColor(sf::Color(255, 0, 0));
	dog.getRect_TEMP()->setOutlineThickness(1);
	viewport.addPhysicsBody(&dog);

	ground.getRect_TEMP()->setOrigin(ground.getSize().x / 2, ground.getSize().y / 2);
	ground.getRect_TEMP()->setFillColor(sf::Color(255, 0, 0, 128));
	ground.getRect_TEMP()->setOutlineColor(sf::Color(255, 0, 0));
	ground.getRect_TEMP()->setOutlineThickness(1);
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
			// dog.getBody()->SetLinearVelocity(b2Vec2(10.f, dog.getBody()->GetLinearVelocity().y));
			// dog.setSize(200, 200);
			dog.getBody()->ApplyForce(b2Vec2(1090.f,0.f),b2Vec2(0.f,0.f), true);
			cout << "hey\n";
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
		viewport.draw(&dog);
		// cout << ground.getRect_TEMP().getSize().x << "	" << ground.getRect_TEMP().getSize().y << endl;
		// cout << ground.getRect_TEMP().getPosition().x << "	" << ground.getRect_TEMP().getPosition().y << endl;
		// cout << (int)ground.getRect_TEMP().getFillColor().r<<  endl;
		viewport.draw(&ground);

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
