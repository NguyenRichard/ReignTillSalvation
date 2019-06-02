#include "Game.h"
#include "MainMenu.h"
#include <iostream> 

#pragma region GameFunctions

Game::Game(int width, int height) : 
	RTSState(width, height) {}

#pragma endregion GameFunctions

#pragma region RTSStateFunctions

Game::Game(const RTSState& state) : 
	RTSState(state.getWidth(),state.getHeight()) {}

std::unique_ptr<RTSState> Game::changeState() {
	return std::make_unique<MainMenu>(*this);
}

void Game::processInput(sf::RenderWindow& window) {

}

void Game::render(sf::RenderWindow& window) {
	std::vector<std::unique_ptr<Individual>>& leaders = map.getLeaders();
	sf::Vector2f coord;
	sf::CircleShape* circle;
	for (const auto & leader : leaders) {
		coord = leader.get()->getCoord();
		circle = leader.get()->getState()->getSprite();
		circle->setPosition(coord);
		window.draw(*circle);
	}
}

void::Game::init() {

	if (!font.loadFromFile("res/fonts/impact.ttf")) {
		std::cout << "Impossible to load font for menu";
		return;
	}

	text.setFont(font);
	//Useful if you use handleKeyEvent() for default color.
	text.setFillColor(sf::Color::Red);
	text.setString("IN GAME");
	text.setCharacterSize(100);
	sf::FloatRect rect = text.getGlobalBounds();
	//SFML draw with the top-left corner as origin, so we have to center the position.
	text.setPosition(sf::Vector2f(width / 2 - rect.width / 2, height / 2 - rect.height / 2));

}


#pragma endregion RTSStateFunctions