#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <pugixml.hpp>
#include <iostream> 

#include "RTSState.h"
#include "Map.h"
#include "MainMenu.h"

enum GameState { Running, Paused, InMenu, MAX_NUMBER};

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
	void changeGameState();
	void changeGameState(GameState);
private:
	Map map;
	GameState state;
	void parseXML();
	std::unique_ptr<Menu> menu;
	void processGameInput(sf::RenderWindow& window);
	void renderGame(sf::RenderWindow& window);
	void renderMenu(sf::RenderWindow& window);
};