#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "RTSState.h"
#include "Map.h"

class Game : public RTSState{
public:
	Game(int width, int height);
	Game(const RTSState & state);
	void processInput(sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
	void update() override;
	std::unique_ptr<RTSState> changeState() override;
	void init() override;
	Map* getMap() { return &map; }
private:
	sf::Text text;
	sf::Font font;
	Map map;

};