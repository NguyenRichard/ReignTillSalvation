#pragma once
#include "Game.h"

class GameMenu : public Game {
public:
	GameMenu(int width, int height, std::unique_ptr<sf::Music> music) : Game(width, height, std::move(music)) {};
	GameMenu(const RTSState & state, std::unique_ptr<sf::Music> old_music) : Game(state, std::move(old_music)) {};
	GameMenu(const Game & state, std::unique_ptr<Map>, std::unique_ptr<sftools::Chronometer>,
		std::unique_ptr<sf::Music> old_music);
	void processInput(RTS*, sf::RenderWindow&, sf::Event&) override;
	void render(sf::RenderWindow& window) override;
	void update(RTS* rts) override;
	void init() override;
	void changeState(RTS* rts) override;
	void createLaw(Element*, LawType);
private:
	void renderMenu(sf::RenderWindow& window);
	std::unique_ptr<RTSState> changeStateToGameRunning();
	std::unique_ptr<Menu> menu;

};


