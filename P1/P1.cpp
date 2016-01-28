//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 


#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>
#include "CollidableBody.h"
#include "Ball.h"
#include "CollidableManager.h"
#include <ctime>

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	window.setPosition(sf::Vector2i(0, 0));
	window.setFramerateLimit(40);

	CollidableManager::getInstance();
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		CollidableManager::getInstance()->addObject(new CollidableBody(4));
	}

	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

		}

		window.clear();
		CollidableManager::getInstance()->updateObjects();
		int count = CollidableManager::getInstance()->getCount();
		for (int i = 0; i < count; i++)
		{
			/*if ((Event.type == sf::Event::MouseButtonPressed) && (Event.key.code == sf::Mouse::Left))
			{
			mBalls[i]->push(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
			}
			if ((Event.type == sf::Event::MouseButtonPressed) && (Event.key.code == sf::Mouse::Right))
			{
			mBalls[i]->pull(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
			}*/
			//mBalls[i]->pull(sf::Vector2f(window.getPosition().x + 400, window.getPosition().y + 300));
			//mBalls[i]->update();

			window.draw(CollidableManager::getInstance()->getDrawAt(i));
		}
		//Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame
	return EXIT_SUCCESS;
}