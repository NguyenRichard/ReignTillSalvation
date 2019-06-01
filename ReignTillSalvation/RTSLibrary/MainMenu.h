#pragma once
#include "Menu.h"
#include "RTSState.h"

class MainMenu : public Menu, public RTSState {
private:
	void handleMouseEventClick(sf::RenderWindow& window) override;
	void handleKeyEventAction(sf::RenderWindow& window) override;
	void processInput(sf::RenderWindow& window) override;
public:
	MainMenu(int width, int height);
	MainMenu(const RTSState & state);
	std::unique_ptr<RTSState> changeState() override;
	void render(sf::RenderWindow& window) override;
	void init() override;
};
