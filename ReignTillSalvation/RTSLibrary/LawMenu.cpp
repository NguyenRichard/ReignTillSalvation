#include "LawMenu.h"
#include "Value.h"
#include "Strong.h"
#include "GameMenu.h"

LawMenu::LawMenu(Element* element, int width, int height) :
	element(element)
{

	if (!font.loadFromFile(FONT_PATH)) {
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
	/*
	options[0].setPosition(sf::Vector2f((WINDOW_WIDTH) / 2 - rect.width / 2,
		(WINDOW_HEIGHT - height) / 2 + (height / (number_choice + 1)) * 1 - rect.height));
		*/
	int width2 = rect.width;
	int height2 = rect.height + 150;

	for (int i = 1; i < option_names.size(); i++) {
		options[i].setFont(font);
		options[i].setFillColor(nselectedColor);
		options[i].setString(option_names[i]);
		options[i].setCharacterSize(char_size/2);
		rect = options[i].getGlobalBounds();
		/*
		options[i].setPosition(sf::Vector2f((WINDOW_WIDTH) / 2 - rect.width / 2,
			(WINDOW_HEIGHT - height) / 2 + (height / (number_choice + 1)) * (i + 1) - rect.height));
			*/
		width2 = std::max(width2, (int) rect.width);
		height2 += rect.height + 50;
	}

	width2 += 100;

	for (int i = 0; i < option_names.size(); i++) {
		rect = options[i].getGlobalBounds();
		options[i].setOrigin(sf::Vector2f(0, - rect.height / 2));
		options[i].setPosition(sf::Vector2f((WINDOW_WIDTH) / 2 - rect.width / 2,
			(WINDOW_HEIGHT - height2) / 2 + (height2 / (number_choice + 1)) * (i + 1) - rect.height));
	}

	sf::Color color = sf::Color::Black;
	color.a = 220.0f;
	background.setFillColor(color);
	background.setSize(sf::Vector2f(width2, height2));
	background.setPosition(sf::Vector2f((WINDOW_WIDTH - width2) / 2, (WINDOW_HEIGHT - height2)/2 - 10.0f));

}

void LawMenu::render(sf::RenderWindow& window) {
	window.draw(background);
	Menu::render(window);

}

void LawMenu::handleMouseEventClick(RTS* rts,sf::RenderWindow& window, sf::Event& event) {
	GameMenu* game = dynamic_cast<GameMenu*>(rts->getState());
	if (event.key.code == sf::Mouse::Left && game != NULL) {
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
		Strong* strong;
		switch (selectedItemIndex) {
		case 0:
			game->createLaw(element, Attraction);
			game->changeState(rts);
			break;
		case 1:
			game->createLaw(element, Repulsion);
			game->changeState(rts);
			break;
		case 2:
			game->createLaw(element, Cancel);
			game->changeState(rts);
			break;
		case 3:
			game->changeState(rts);
			break;
		}
	}
}