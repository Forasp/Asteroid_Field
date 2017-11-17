#include "AsteroidGame.h"
#include "Message.h"
#include "Messenger.h"
#include "SFML/System/Sleep.hpp"

int main()
{
	// Create window instance
	sf::RenderWindow WindowInstance(sf::VideoMode(1024, 768), "Fallen Forever");

	WindowInstance.setFramerateLimit(60);

	// Set the window inactive so another thread can pick it up.
	WindowInstance.setActive(false);

	// Create an instance of the game here.
	std::unique_ptr<AsteroidGame> GameInstance = std::make_unique<AsteroidGame>(&WindowInstance);

	// Create an event holder here for our event polling.
	sf::Event WindowEvent;

	while (GameInstance->IsActive())
	{
		while (WindowInstance.pollEvent(WindowEvent))
		{
			switch (WindowEvent.type)
			{
				case sf::Event::Closed:
					GameInstance->EndGame();
					break;
				case sf::Event::KeyPressed:
					GameInstance->QueueMessage("KeyEvents", std::make_unique<Message>(MESSAGE_TYPE_INPUT, WindowEvent.key.code));
					break;
				case sf::Event::Resized:
					WindowInstance.setSize(sf::Vector2u(WindowEvent.size.width, WindowEvent.size.height));
					break;
				case sf::Event::MouseButtonPressed:
					if (WindowEvent.mouseButton.button == sf::Mouse::Left)
					{
						GameInstance->QueueMessage("MouseEvents",
													std::make_unique<Message>(MESSAGE_TYPE_MOUSE, 
																			  "LeftPressed", 
																			  std::pair<double, double>(WindowEvent.mouseButton.x, WindowEvent.mouseButton.y)));
					}
					break;
			}
		}

		sf::sleep(sf::milliseconds(100));
	}

	return 0;
}