#include "LawMenu.h"
#include "Value.h"
#include "Strong.h"

LawMenu::LawMenu(Element* element, Game* game, int width, int height) :
	element(element),
	game(game)
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

	background.setFillColor(LAW_MENU_BACKGROUND_COLOR);
	background.setSize(sf::Vector2f(width, height));
	background.setPosition(sf::Vector2f((WINDOW_WIDTH - width) / 2, (WINDOW_HEIGHT - height)/2));

}

void LawMenu::render(sf::RenderWindow& window) {
	window.draw(background);
	Menu::render(window);

}

void LawMenu::handleMouseEventClick(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Map* map = game->getMap();
		Strong* strong;
		switch (selectedItemIndex){
		case 0:
			map->getLaws().push_back(std::make_unique<Law>(element, attraction));
			for (auto & leader : map->getLeaders()) {
				strong = dynamic_cast<Strong*>(leader->getState());
				leader->addElement(element);
				for (auto & subordinate : strong->getSubordinates()) {
					subordinate->addElement(element);
				}
			}
			game->changeGameState(Running);
			break;
		case 1:
			map->getLaws().push_back(std::make_unique<Law>(element, repulsion));
			for (auto & leader : map->getLeaders()) {
				strong = dynamic_cast<Strong*>(leader->getState());
				leader->addElement(element);
				for (auto & subordinate : strong->getSubordinates()) {
					subordinate->addElement(element);
				}
			}
			game->changeGameState(Running);
			break;
		case 2:
			map->getLaws().push_back(std::make_unique<Law>(element, repulsion));
			for (auto & leader : map->getLeaders()) {
				strong = dynamic_cast<Strong*>(leader->getState());
				leader->addElement(element);
				for (auto & subordinate : strong->getSubordinates()) {
					subordinate->addElement(element);
				}
			}
			game->changeGameState(Running);
			break;
		case 3:
			game->changeGameState(Running);
			break;
		}
	}
}

void LawMenu::handleKeyEventAction(sf::RenderWindow& window) {
	Map* map = game->getMap();
	Strong* strong;
	switch (selectedItemIndex) {
	case 0:
		//	map->getLaws()->push_back(std::make_unique<Law>(element, attraction));
		for (auto & leader : map->getLeaders()) {
			strong = dynamic_cast<Strong*>(leader->getState());
			leader->addElement(element);
			for (auto & subordinate : strong->getSubordinates()) {
				subordinate->addElement(element);
			}
		}
		break;
	case 1:
		//		map->getLaws()->push_back(std::make_unique<Law>(element, repulsion));
		for (auto & leader : map->getLeaders()) {
			strong = dynamic_cast<Strong*>(leader->getState());
			leader->addElement(element);
			for (auto & subordinate : strong->getSubordinates()) {
				subordinate->addElement(element);
			}
		}
		break;
	case 2:
		//	map->getLaws()->push_back(std::make_unique<Law>(element, repulsion));
		for (auto & leader : map->getLeaders()) {
			strong = dynamic_cast<Strong*>(leader->getState());
			leader->addElement(element);
			for (auto & subordinate : strong->getSubordinates()) {
				subordinate->addElement(element);
			}
		}
		break;
	case 3:
		game->changeGameState(Running);
		break;
	}
}