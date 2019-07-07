#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <pugixml.hpp>
#include <iostream> 

#include "RTSState.h"
#include "Map.h"
#include "MainMenu.h"
#include "Renderable.h"

class Game : public RTSState{
public:
	Game(int width, int height, std::unique_ptr<sf::Music> music);
	Game(const RTSState & state, std::unique_ptr<sf::Music> old_music);
	Game(const Game & state, std::unique_ptr<Map>, std::unique_ptr<sftools::Chronometer>, std::unique_ptr<sf::Music> old_music);
	void processInput(RTS*,sf::RenderWindow& window,sf::Event&) override = 0;
	void render(sf::RenderWindow& window) override = 0;
	void update(RTS* rts) override = 0;
	void init() override = 0;
	std::unique_ptr<Map>& getMap() { return map; }
	std::unique_ptr<sftools::Chronometer> &getTime() { return time; }
	const std::string XML_FILE_PATH = "resources.xml";
	void renderGame(sf::RenderWindow& window);
	void renderAnimation(sf::RenderWindow& window);

protected:
	std::unique_ptr<Map> map;
	std::unique_ptr<sftools::Chronometer> time;
	sf::Time last_anim_update;
	std::vector<std::unique_ptr<Renderable>> renderables;
};