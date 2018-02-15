#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include <Box2D/Box2D.h>
#include "src/rectangle.h"
#include "src/viewport.h"
#include "src/shape.h"
#include "src/body_data.h"

using namespace std;

#define WIDTH 800
#define HEIGHT 800
const static float SCALE_TEMP = 30.f;
void CreateGround(b2World &world);

void CreateWalls(b2World &world);
class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact *contact)
	{

		void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void *bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData && bodyUserData2)
		{
			int id1 = static_cast<BodyData *>(contact->GetFixtureA()->GetBody()->GetUserData())->id;
			int id2 = static_cast<BodyData *>(contact->GetFixtureB()->GetBody()->GetUserData())->id;

			static_cast<BodyData *>(bodyUserData)->collisionStart(id2);
			static_cast<BodyData *>(bodyUserData2)->collisionStart(id1);
		}
		// if (bodyUserData)
		// {
		// 	int other_id = static_cast<BodyData *>(contact->GetFixtureA()->GetBody()->GetUserData())->id;
		// 	std::cout << "start_id: " << static_cast<BodyData *>(bodyUserData)->id << endl;
		// 	static_cast<BodyData *>(bodyUserData)->collisionStart(other_id);
		// }
	}

	void EndContact(b2Contact *contact)
	{
		void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void *bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData && bodyUserData2)
		{
			int id1 = static_cast<BodyData *>(contact->GetFixtureA()->GetBody()->GetUserData())->id;
			int id2 = static_cast<BodyData *>(contact->GetFixtureB()->GetBody()->GetUserData())->id;

			static_cast<BodyData *>(bodyUserData)->collisionEnd(id2);
			static_cast<BodyData *>(bodyUserData2)->collisionEnd(id1);
		}
		// if (bodyUserData)
		// {
		// 	int other_id = static_cast<BodyData *>(contact->GetFixtureA()->GetBody()->GetUserData())->id;
		// 	std::cout << "end_id: " << static_cast<BodyData *>(bodyUserData)->id << endl;
		// 	static_cast<BodyData *>(bodyUserData)->collisionEnd(other_id);
		// }
	}
};
int main()
{
	Viewport2D viewport(sf::Vector2f(WIDTH, HEIGHT), sf::Vector2f(0.f, 9.8f), 60);

	Rectangle2D dog(viewport.world, sf::Vector2f(10, 0), sf::Vector2f(20, 20), 0.f, 0.f, 0.f);
	dog.setOrigin(dog.getSize().x / 2, dog.getSize().y / 2);
	dog.setFillColor(sf::Color(255, 0, 0, 128));
	dog.setOutlineColor(sf::Color(255, 0, 0));
	dog.setOutlineThickness(1);

	Rectangle2D dog2(viewport.world, sf::Vector2f(100, 0), sf::Vector2f(100, 100), 0.f, 0.f, 0.f);
	dog2.setOrigin(dog2.getSize().x / 2, dog2.getSize().y / 2);
	dog2.setFillColor(sf::Color(0, 255, 0, 128));
	dog2.setOutlineColor(sf::Color(0, 255, 0));
	dog2.setOutlineThickness(1);

	Rectangle2D dog3(viewport.world, sf::Vector2f(500, 0), sf::Vector2f(20, 20), 0.f, 0.f, 0.f);
	dog3.setOrigin(dog3.getSize().x / 2, dog3.getSize().y / 2);
	dog3.setFillColor(sf::Color(0, 0, 255, 128));
	dog3.setOutlineColor(sf::Color(0, 0, 255));
	dog3.setOutlineThickness(1);

	viewport.addPhysicsBody(&dog);
	viewport.addPhysicsBody(&dog2);
	viewport.addPhysicsBody(&dog3);

	CreateGround(viewport.world);
	CreateWalls(viewport.world);
	sf::Clock clock;
	MyContactListener myContactListenerInstance;
	viewport.world.SetContactListener(&myContactListenerInstance);
	while (viewport.window.isOpen())
	{
		sf::Time time = clock.getElapsedTime();
		float seconds = time.asSeconds();
		// cout << seconds << endl;

		if (seconds > 2.9 && seconds < 3.1)
		{
			dog.getBody()->SetLinearVelocity(b2Vec2(10.f, dog.getBody()->GetLinearVelocity().y));
			// cout << "hey\n";
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
		viewport.window.draw(dog3);
		viewport.window.draw(dog);
		viewport.window.draw(dog2);

		viewport.window.display();
		if (dog.isCollision())
		{
			cout << "Collision\n";
		}
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

	BodyDef;
	BodyDef.position = b2Vec2(WIDTH / SCALE_TEMP, 0);
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
