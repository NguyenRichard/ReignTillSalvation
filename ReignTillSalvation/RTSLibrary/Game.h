#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <pugixml.hpp>
#include <iostream> 

#include "RTSState.h"
#include "Map.h"
#include "MainMenu.h"

class Game : public RTSState{
public:
	Game(int width, int height);
	Game(const RTSState & state);
	Game(const Game & state, std::unique_ptr<Map>);
	void processInput(RTS*,sf::RenderWindow& window) override = 0;
	void render(sf::RenderWindow& window) override = 0;
	void update() override = 0;
	void init() override = 0;
	std::unique_ptr<Map>& getMap() { return map; }
	const std::string XML_FILE_PATH = "resources.xml";

protected:
	std::unique_ptr<Map> map;
};