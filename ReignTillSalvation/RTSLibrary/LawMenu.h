#pragma once
#include "Menu.h"
#include "Element.h"


class LawMenu : public Menu{
public:
	LawMenu(Element*,int width, int height);
	void render(sf::RenderWindow& window) override;
	void handleMouseEventClick(RTS*,sf::RenderWindow& window,sf::Event&) override;
	void handleKeyEventAction(RTS*,sf::RenderWindow& window) override;
	//NOTE: Only use if RTS has GameMenu as state.
private:
	Element* element;
	sf::RectangleShape background;
};