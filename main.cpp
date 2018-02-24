#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <ctime>
#include <chrono>
#include <Box2D/Box2D.h>
#include <apphysics2d/apphysics2d.hpp>
using namespace std;

#define WIDTH 800
#define HEIGHT 800
#define NOW() std::chrono::high_resolution_clock::now()
#define START() std::chrono::high_resolution_clock::time_point start = NOW()
#define END() std::cout << "time: " << (float)std::chrono::duration_cast<std::chrono::microseconds>(NOW() - start).count() / 1000 << std::endl

const static float SCALE_TEMP = 30.f;

int main()
{
	srand(time(NULL));
	Viewport2D viewport(VectorU2D(WIDTH, HEIGHT), VectorF2D(0, 9.8), 60);

	Rectangle2D dog(viewport.world, dynamic2D, VectorF2D(300, 100), VectorF2D(20, 20), 1.f, 0, 0.4f);
	dog.setOrigin(dog.getSize().x / 2, dog.getSize().y / 2);
	dog.setVisualProperties(Color2D(255, 0, 0, 128), Color2D(255, 0, 0), 1);
	viewport.addPhysicsBody(&dog);

	Rectangle2D ground(viewport.world, static2D, VectorF2D(WIDTH / 2, HEIGHT), VectorF2D(WIDTH, 50), 1.f, 0.5f, 0.4f);
	ground.setOrigin(ground.getSize().x / 2, ground.getSize().y / 2);
	ground.setVisualProperties(Color2D(255, 0, 0, 128), Color2D(255, 0, 0), 1);
	viewport.addPhysicsBody(&ground);

	Rectangle2D wall_left(viewport.world, static2D, VectorF2D(0, HEIGHT / 2), VectorF2D(50, HEIGHT), 1.f, 0.5f, 0.4f);
	wall_left.setOrigin(wall_left.getSize().x / 2, wall_left.getSize().y / 2);
	wall_left.setVisualProperties(Color2D(255, 0, 0, 128), Color2D(255, 0, 0), 1);
	viewport.addPhysicsBody(&wall_left);

	Rectangle2D wall_right(viewport.world, static2D, VectorF2D(WIDTH, HEIGHT / 2), VectorF2D(50, HEIGHT), 1.f, 0.5f, 0.4f);
	wall_right.setOrigin(wall_right.getSize().x / 2, wall_right.getSize().y / 2);
	wall_right.setVisualProperties(Color2D(255, 0, 0, 128), Color2D(255, 0, 0), 1);
	viewport.addPhysicsBody(&wall_right);

	sf::Clock clock;

	while (viewport.window.isOpen())
	{
		sf::Time time = clock.getElapsedTime();
		float seconds = time.asSeconds();

		if (seconds > 0.9 && seconds < 1.1)
		{
			// dog.getBody()->SetLinearVelocity(b2Vec2(10.f, dog.getBody()->GetLinearVelocity().y));
			// dog.setSize(200, 200);
			dog.getBody()->ApplyForce(b2Vec2(100.f, 0.f), b2Vec2(0.f, 0.f), true);
			// cout << "hey\n";
		}
		// cout << dog.getOrigin().x << endl;
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
		viewport.draw(&ground);
		viewport.draw(&wall_left);
		viewport.draw(&wall_right);

		viewport.window.display();
		START();
		if (dog.isCollision())
		{
			cout << dog.getSize().x << endl;
			dog.setSize(dog.getSize().x+5.f,dog.getSize().y+1.f);
		}
		// END();
	}
	return EXIT_SUCCESS;
}