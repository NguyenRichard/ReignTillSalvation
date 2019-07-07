#pragma once
#include "Game.h"

class GameRunning : public Game {
public:
	GameRunning(int width, int height, std::unique_ptr<sf::Music> music) : Game(width, height, std::move(music)) {};
	GameRunning(const RTSState & state, std::unique_ptr<sf::Music> old_music) : Game(state, std::move(old_music)) {};
	GameRunning(const Game & state, std::unique_ptr<Map>, std::unique_ptr<sftools::Chronometer>,
		std::unique_ptr<sf::Music> old_music);
	void processInput(RTS*, sf::RenderWindow& window, sf::Event&) override;
	void render(sf::RenderWindow& window) override;
	void update(RTS* rts) override;
	void init() override;
	void changeState(RTS* rts) override;

private:
	sf::Time last_update;
	sf::Time last_render;
	std::unique_ptr<RTSState> changeStateToMainMenu();
	std::unique_ptr<RTSState> changeStateToGameMenu();
	std::unique_ptr<RTSState> changeStateToGameOverMenu();
	void parseXML();
	bool mustMoveElementCoord(sf::Vector2f &coord);
	std::vector<std::unique_ptr<Renderable>> renderables;
};