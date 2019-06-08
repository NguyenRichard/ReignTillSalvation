#pragma once
#include "Game.h"

class GameRunning : public Game {
public:
	GameRunning(int width, int height) : Game(width, height) {};
	GameRunning(const RTSState & state) : Game(state) {};
	GameRunning(const Game & state, std::unique_ptr<Map>);
	void processInput(RTS*, sf::RenderWindow& window) override;
	void render(sf::RenderWindow& window) override;
	void update() override;
	void init() override;
	void changeState(RTS* rts) override;

private:
	std::unique_ptr<RTSState> changeStateToMainMenu();
	std::unique_ptr<RTSState> changeStateToGameMenu();
	void processGameInput(RTS*,sf::RenderWindow& window);
	void renderGame(sf::RenderWindow& window);
	void parseXML();
};