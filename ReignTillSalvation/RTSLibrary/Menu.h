#pragma once
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream> 
#include "RTS.h"

#define MAX_NUMBER_OF_ITEMS 5
#define SELECTED_COLOR sf::Color::Blue
#define NOT_SELECTED_COLOR sf::Color::White
#define CHAR_SIZE 60

class Menu {
protected:
	int selectedItemIndex;
	sf::Color selectedColor;
	sf::Color nselectedColor;
	sf::Font font;
	int char_size;
	int number_choice;
	sf::Text options[MAX_NUMBER_OF_ITEMS];
public:
	Menu();
	virtual void render(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void handleKeyEvent(RTS*, sf::RenderWindow& window,sf::Event&);
	virtual void handleKeyEventAction(RTS*,sf::RenderWindow& window) = 0; //put default option when using.
	void handleMouseEventPositionSelect(sf::RenderWindow& window);
	virtual void handleMouseEventClick(RTS*,sf::RenderWindow& window, sf::Event&) = 0;
	void handleMouseEvent(RTS*,sf::RenderWindow& window, sf::Event&);

};