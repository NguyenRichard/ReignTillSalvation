#pragma once
#include "Menu.h"
#include "Element.h"
#include "Game.h"


class LawMenu : public Menu{
public:
	LawMenu(Element*, Game*,int width, int height);
	void render(sf::RenderWindow& window) override;
	void handleMouseEventClick(sf::RenderWindow& window) override;
	void handleKeyEventAction(sf::RenderWindow& window) override;
private:
	Element* element;
	sf::RectangleShape background;
	Game* game;
};