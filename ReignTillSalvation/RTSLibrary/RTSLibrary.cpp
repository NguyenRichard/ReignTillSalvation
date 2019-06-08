#include "RTSLibrary.h"
// RTSLibrary.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

int RTSmain()
{

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ReignTillSalvation");

	ViewManager view(window);

	RTS rts{ std::make_unique<MainMenu>(window.getSize().x,window.getSize().y) };
	window.setVerticalSyncEnabled(true);

	sf::Clock globalClock;

	sf::Clock deltaClock;

	float offset;
	sf::Time time = sf::Time::Time();
	while (window.isOpen()) {
		offset = time.asSeconds();
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::Resized) {
				view.set_View(window);
			}
			rts.processInput(window, event);
		}

		window.clear();

		sf::Time duration = globalClock.getElapsedTime();
		rts.update();
		rts.render(window);
		window.display();
		offset = time.asSeconds() - offset;
	//	Sleep(MS_PER_UPDATE - 1000 * offset);
	}


	return EXIT_SUCCESS;


}
