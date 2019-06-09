#pragma once
#include "Menu.h"
#include "RTSState.h"

class GameOverMenu : public Menu, public RTSState {
public:
	GameOverMenu(int width, int height);
	GameOverMenu(const RTSState & state);
	void render(sf::RenderWindow& window) override;
	void init() override;
	void changeState(RTS* rts) override;

private:
	void handleMouseEventClick(RTS*, sf::RenderWindow& window, sf::Event&) override;
	void handleKeyEventAction(RTS*, sf::RenderWindow& window) override;
	void processInput(RTS*, sf::RenderWindow& window, sf::Event&) override;
	std::unique_ptr<RTSState> changeStateToMainMenu();
};
