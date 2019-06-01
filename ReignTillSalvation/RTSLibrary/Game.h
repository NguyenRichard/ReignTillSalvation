#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "RTSState.h"

class Game : public RTSState{
public:
	Game(int width, int height);
	Game(const RTSState & state);
	void processInput(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
	std::unique_ptr<RTSState> changeState() override;
	void init() override;
private:
	sf::Text text;
	sf::Font font;

};