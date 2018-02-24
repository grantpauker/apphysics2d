#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <ctime>
#include <cmath>
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

	Rectangle2D dog(viewport.world, dynamic2D, VectorF2D(300, 100), VectorF2D(100, 100), 1.f, 0, 0.4f);
	dog.setOrigin(VectorF2D(dog.getSize().x / 2, dog.getSize().y / 2));
	dog.setVisualProperties(Color2D(255, 0, 0, 128), Color2D(255, 0, 0), 1);
	viewport.addPhysicsBody(&dog);

	Rectangle2D ground(viewport.world, static2D, VectorF2D(WIDTH / 2, HEIGHT), VectorF2D(WIDTH, 50), 1.f, 0.5f, 0.4f);
	ground.setOrigin(VectorF2D(ground.getSize().x / 2, ground.getSize().y / 2));
	ground.setVisualProperties(Color2D(255, 0, 0, 128), Color2D(255, 0, 0), 1);
	viewport.addPhysicsBody(&ground);

	Rectangle2D wall_left(viewport.world, static2D, VectorF2D(0, HEIGHT / 2), VectorF2D(50, HEIGHT), 1.f, 0.5f, 0.4f);
	wall_left.setOrigin(VectorF2D(wall_left.getSize().x / 2, wall_left.getSize().y / 2));
	wall_left.setVisualProperties(Color2D(255, 0, 0, 128), Color2D(255, 0, 0), 1);
	viewport.addPhysicsBody(&wall_left);

	Rectangle2D wall_right(viewport.world, static2D, VectorF2D(WIDTH, HEIGHT / 2), VectorF2D(50, HEIGHT), 1.f, 0.5f, 0.4f);
	wall_right.setOrigin(VectorF2D(wall_right.getSize().x / 2, wall_right.getSize().y / 2));
	wall_right.setVisualProperties(Color2D(255, 0, 0, 128), Color2D(255, 0, 0), 1);
	viewport.addPhysicsBody(&wall_right);

	sf::Clock clock;
	float start_time = 0;
	int frame_count = 0;

	while (viewport.window.isOpen())
	{
		start_time = clock.getElapsedTime().asSeconds();

		if (frame_count == 60)
		{
			cout << "start: " << dog.getTransform().pos.x << endl;
			dog.addTransform(VectorF2D(WIDTH / 2 / 30, 0), 0);
		}
		// cout << dog.getOrigin().x << endl;
		sf::Event event;
		while (viewport.window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Resized:
				viewport.window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				break;
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
		// if (dog.isCollision())
		// {
		// 	cout << dog.getSize().x << endl;
		// 	dog.setSize(dog.getSize().x + 5.f, dog.getSize().y + 1.f);
		// }
		frame_count++;
		cout << "end: " << dog.getTransform().pos.x << endl;
	}
	return EXIT_SUCCESS;
}