#pragma once
#include "Menu.h"

class MainMenu : public Menu {
private:
	void handleMouseEventClick(sf::RenderWindow& window) override;
	void handleKeyEventAction(sf::RenderWindow& window) override;
public:
	MainMenu(float width, float height);
};
