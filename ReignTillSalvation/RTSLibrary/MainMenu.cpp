#include "MainMenu.h"


MainMenu::MainMenu(float width, float height) :
	Menu(width,height){

	if (!font.loadFromFile("res/fonts/impact.ttf")) {

	}
	std::vector<std::string> option_names;
	option_names.push_back("Play");
	option_names.push_back("Options");
	option_names.push_back("Exit");
	number_choice = option_names.size();

	options[0].setFont(font);
	//Useful if you use handleKeyEvent() for default color.
	options[0].setFillColor(selectedColor);
	options[0].setString(option_names[0]);
	options[0].setCharacterSize(char_size);
	sf::FloatRect rect = options[0].getGlobalBounds();
	//SFML draw with the top-left corner as origin, so we have to center the position.
	options[0].setPosition(sf::Vector2f(width / 2 - rect.width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1 - rect.height / 2));
	option_bounds[0] = options[0].getGlobalBounds();

	for (int i = 1; i < option_names.size(); i++) {
		options[i].setFont(font);
		options[i].setFillColor(nselectedColor);
		options[i].setString(option_names[i]);
		options[i].setCharacterSize(char_size);
		options[i].setPosition(sf::Vector2f(width / 2 - rect.width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1) - rect.height / 2));
		option_bounds[i] = options[i].getGlobalBounds();
	}

}

void MainMenu::handleKeyEventAction(sf::RenderWindow& window) {
	switch (selectedItemIndex) {
	case 2:
		window.close();
		break;
	}
}

void MainMenu::handleMouseEventClick(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		switch (selectedItemIndex) {
		case 2:
			window.close();
			break;
		}
	}
}