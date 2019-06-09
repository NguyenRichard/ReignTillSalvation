#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>
#include <pugixml.hpp>
#include <iostream> 

#include "RTSState.h"
#include "Map.h"
#include "MainMenu.h"

class Game : public RTSState{
public:
	Game(int width, int height);
	Game(const RTSState & state);
	Game(const Game & state, std::unique_ptr<Map>, std::unique_ptr<sftools::Chronometer>);
	void processInput(RTS*,sf::RenderWindow& window,sf::Event&) override = 0;
	void render(sf::RenderWindow& window) override = 0;
	void update(RTS* rts) override = 0;
	void init() override = 0;
	std::unique_ptr<Map>& getMap() { return map; }
	std::unique_ptr<sftools::Chronometer> &getTime() { return time; }
	const std::string XML_FILE_PATH = "resources.xml";
	const std::string MAIN_MUSIC_PATH = "../ReignTillSalvation/res/musics/main_music.flac";
	void renderGame(sf::RenderWindow& window);

protected:
	std::unique_ptr<Map> map;
	std::unique_ptr<sftools::Chronometer> time;
	sf::Time last_render;
	sf::Music music;
};