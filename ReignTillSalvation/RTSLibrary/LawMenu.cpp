#include "LawMenu.h"
#include "Value.h"
#include "Strong.h"
#include "GameMenu.h"

LawMenu::LawMenu(Element* element, int width, int height) :
	element(element)
{

	if (!font.loadFromFile("res/fonts/impact.ttf")) {
		std::cout << "Impossible to load font for menu";
		return;
	}
	
	std::vector<std::string> option_names;
	option_names.push_back(element->getAttractionMessage());
	option_names.push_back(element->getRepulsionMessage());
	option_names.push_back(element->getCancelMessage());
	option_names.push_back("Exit");
	number_choice = option_names.size();

	options[0].setFont(font);
	//put selectedColor for a default option if you use handleKeyEvent.
	options[0].setFillColor(nselectedColor);
	options[0].setString(option_names[0]);
	options[0].setCharacterSize(char_size/2);
	sf::FloatRect rect = options[0].getGlobalBounds();
	//SFML draw with the top-left corner as origin, so we have to center the position.
	options[0].setPosition(sf::Vector2f((WINDOW_WIDTH) / 2 - rect.width/2, (WINDOW_HEIGHT - height) / 2+(height / (number_choice + 1)) * 1 - rect.height));

	for (int i = 1; i < option_names.size(); i++) {
		options[i].setFont(font);
		options[i].setFillColor(nselectedColor);
		options[i].setString(option_names[i]);
		options[i].setCharacterSize(char_size/2);
		rect = options[i].getGlobalBounds();
		options[i].setPosition(sf::Vector2f((WINDOW_WIDTH) / 2 - rect.width/2, (WINDOW_HEIGHT - height) / 2+(height / (number_choice + 1)) * (i + 1) - rect.height));
	}

	background.setFillColor(element->getSprite()->getFillColor());
	background.setSize(sf::Vector2f(width, height));
	background.setPosition(sf::Vector2f((WINDOW_WIDTH - width) / 2, (WINDOW_HEIGHT - height)/2));

}

void LawMenu::render(sf::RenderWindow& window) {
	window.draw(background);
	Menu::render(window);

}

void LawMenu::handleMouseEventClick(RTS* rts,sf::RenderWindow& window) {
	GameMenu* game = dynamic_cast<GameMenu*>(rts->getState());
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && game != NULL) {
		std::unique_ptr<Map>& map = game->getMap();
		Strong* strong;
		switch (selectedItemIndex){
		case 0:
			map->createLaw(element, Attraction);
			game->changeState(rts);
			break;
		case 1:
			map->createLaw(element,Repulsion);
			game->changeState(rts);
			break;
		case 2:
			map->createLaw(element, Cancel);
			game->changeState(rts);
			break;
		case 3:
			game->changeState(rts);
			break;
		}
	}
}

void LawMenu::handleKeyEventAction(RTS* rts,sf::RenderWindow& window) {
	GameMenu* game = dynamic_cast<GameMenu*>(rts->getState());
	if (game != NULL) {
		std::unique_ptr<Map>& map = game->getMap();
		Strong* strong;
		switch (selectedItemIndex) {
		case 0:
			map->createLaw(element, Attraction);
			game->changeState(rts);
			break;
		case 1:
			map->createLaw(element, Repulsion);
			game->changeState(rts);
			break;
		case 2:
			map->createLaw(element, Cancel);
			game->changeState(rts);
			break;
		case 3:
			game->changeState(rts);
			break;
		}
	}
}