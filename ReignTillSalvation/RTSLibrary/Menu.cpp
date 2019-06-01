#include "Menu.h"

Menu::Menu() {

	//default
	selectedColor = SELECTED_COLOR;
	nselectedColor = NOT_SELECTED_COLOR;
	char_size = CHAR_SIZE;
	selectedItemIndex = 0;

}

void Menu::render(sf::RenderWindow& window) {
	for (int i = 0; i < number_choice; i++) {
		window.draw(options[i]);
	}
}

void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		options[selectedItemIndex].setFillColor(nselectedColor);
		selectedItemIndex--;
		options[selectedItemIndex].setFillColor(selectedColor);
	}
}

void Menu::MoveDown() {
	if (selectedItemIndex + 1 < number_choice) {
		options[selectedItemIndex].setFillColor(nselectedColor);
		selectedItemIndex++;
		options[selectedItemIndex].setFillColor(selectedColor);
	}
}

void Menu::handleKeyEvent(sf::RenderWindow& window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		MoveUp();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		MoveDown();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		handleKeyEventAction(window);
	}
}


void Menu::handleMouseEventPositionSelect(sf::RenderWindow& window) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	for (int i = 0; i < number_choice; i++) {
		if (option_bounds[i].contains(mousePosition.x, mousePosition.y)) {
			if (selectedItemIndex == i) {
				return;
			}
			options[i].setFillColor(selectedColor);
			selectedItemIndex = i;
			return;
		}
	}
	options[selectedItemIndex].setFillColor(nselectedColor);
	selectedItemIndex = MAX_NUMBER_OF_ITEMS;
}

void Menu::handleMouseEvent(sf::RenderWindow& window) {
	handleMouseEventPositionSelect(window);
	handleMouseEventClick(window);
}