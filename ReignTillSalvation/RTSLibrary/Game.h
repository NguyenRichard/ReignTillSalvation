#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Game {
public:
	void gameStart();
	void gameLoop();
	void gameEnd();
	void processInput();
	void renderFrame();
private:
	sf::RenderWindow window;

};