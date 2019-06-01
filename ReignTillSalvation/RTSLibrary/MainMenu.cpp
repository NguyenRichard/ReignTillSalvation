#include "MainMenu.h"
#include <iostream> 
#include "Game.h"

#pragma region MenuFunctions
MainMenu::MainMenu(int width, int height) :
	Menu(), 
	RTSState(width,height) {}

void MainMenu::handleKeyEventAction(sf::RenderWindow& window) {
	switch (selectedItemIndex) {
	case 0: //Play option
		changeState();
		break;
	case 2: //Exit option
		window.close();
		break;
	}
}

void MainMenu::handleMouseEventClick(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		switch (selectedItemIndex) {
		case 0: //Play option
			state = true;
			break;
		case 2: //Exit option
			window.close();
			break;
		}
	}
}

#pragma endregion MenuFunctions

#pragma region RTSStateFunctions

MainMenu::MainMenu(const RTSState& state) : 
	Menu(), 
	RTSState(state.getWidth(), state.getHeight()) {

}

std::unique_ptr<RTSState> MainMenu::changeState() {
	return std::make_unique<Game>(*this);
}

void MainMenu::processInput(sf::RenderWindow& window) {
	Menu::handleMouseEvent(window);
}

void MainMenu::init() {

	if (!font.loadFromFile("res/fonts/impact.ttf")) {
		std::cout << "Impossible to load font for menu";
		return;
	}

	std::vector<std::string> option_names;
	option_names.push_back("Play");
	option_names.push_back("Options");
	option_names.push_back("Exit");
	number_choice = option_names.size();

	options[0].setFont(font);
	//put selectedColor for a default option if you use handleKeyEvent.
	options[0].setFillColor(nselectedColor);
	options[0].setString(option_names[0]);
	options[0].setCharacterSize(char_size);
	sf::FloatRect rect = options[0].getGlobalBounds();
	//SFML draw with the top-left corner as origin, so we have to center the position.
	options[0].setPosition(sf::Vector2f(width / 2 - rect.width / 2, (height / (number_choice + 1)) * 1 - rect.height / 2));

	for (int i = 1; i < option_names.size(); i++) {
		options[i].setFont(font);
		options[i].setFillColor(nselectedColor);
		options[i].setString(option_names[i]);
		options[i].setCharacterSize(char_size);
		options[i].setPosition(sf::Vector2f(width / 2 - rect.width / 2, (height / (number_choice + 1)) * (i + 1) - rect.height / 2));
	}
}

void MainMenu::render(sf::RenderWindow& window) {
	Menu::render(window);
}

#pragma endregion RTSStateFunctions