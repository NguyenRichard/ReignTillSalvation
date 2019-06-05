#include <SFML/Graphics.hpp>
#include "SFMLOrthogonalLayer.hpp"

void init() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	tmx::Map map;
	map.load("C:/Users/cypri/Desktop/tmxlite/SFMLExample/assets/demo.tmx");

	MapLayer layerZero(map, 0);
	MapLayer layerOne(map, 1);
	MapLayer layerTwo(map, 2);

	sf::Clock globalClock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time duration = globalClock.getElapsedTime();
		layerZero.update(duration);

		window.clear(sf::Color::Black);
		window.draw(layerZero);
		window.draw(layerOne);
		window.draw(layerTwo);
		window.display();
	}
}
