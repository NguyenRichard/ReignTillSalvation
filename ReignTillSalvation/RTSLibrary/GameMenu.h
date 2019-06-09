#pragma once
#include "Game.h"

class GameMenu : public Game {
public:
	GameMenu(int width, int height) : Game(width, height) {};
	GameMenu(const RTSState & state) : Game(state) {};
	GameMenu(const Game & state, std::unique_ptr<Map>, std::unique_ptr<sftools::Chronometer>);
	void processInput(RTS*, sf::RenderWindow&, sf::Event&) override;
	void render(sf::RenderWindow& window) override;
	void update() override;
	void init() override;
	void changeState(RTS* rts) override;
private:
	void renderMenu(sf::RenderWindow& window);
	std::unique_ptr<RTSState> changeStateToGameRunning();
	std::unique_ptr<Menu> menu;

};


