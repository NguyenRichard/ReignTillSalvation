#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <pugixml.hpp>
#include "RTSState.h"
#include "Map.h"
#include "MainMenu.h"
#include <iostream> 

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
	const std::string XML_FILE_PATH = "resources.xml";
private:
	sf::Text text;
	sf::Font font;
	Map map;

	void parseXML();
};