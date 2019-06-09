#include "GameOverMenu.h"
#include "MainMenu.h"

#pragma region MenuFunctions
GameOverMenu::GameOverMenu(int width, int height) :
	Menu(),
	RTSState(width, height, std::make_unique<sf::Music>())
{
	music->openFromFile(MUSIC_GAME_OVER);
	music->setLoop(true);
	music->play();
}

void GameOverMenu::handleKeyEventAction(RTS* rts, sf::RenderWindow& window) {
	switch (selectedItemIndex) {
	case 0:
		changeState(rts);
		break;
	}
}

void GameOverMenu::handleMouseEventClick(RTS* rts, sf::RenderWindow& window, sf::Event& event) {
	if (event.key.code == sf::Mouse::Left) {
		switch (selectedItemIndex) {
		case 0: 
			changeState(rts);
			break;
		}
	}
}

#pragma endregion MenuFunctions

#pragma region RTSStateFunctions

GameOverMenu::GameOverMenu(const RTSState& state) :
	Menu(),
	RTSState(state.getWidth(), state.getHeight(), std::make_unique<sf::Music>())
{
	music->openFromFile(MUSIC_GAME_OVER);
	music->setLoop(true);
	music->play();
}

void GameOverMenu::changeState(RTS* rts) {
	rts->changeState(changeStateToMainMenu());
	rts->initState();
}

std::unique_ptr<RTSState> GameOverMenu::changeStateToMainMenu() {
	return std::make_unique<MainMenu>(*this);
}

void GameOverMenu::processInput(RTS* rts, sf::RenderWindow& window, sf::Event& event) {
	if (event.type == sf::Event::Closed) {
		window.close();
	}
	if (event.type == sf::Event::KeyReleased) {
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			rts->changeState(changeStateToMainMenu());
			break;
		}
	}
	Menu::handleMouseEvent(rts, window, event);
}

void GameOverMenu::init() {

	if (!font.loadFromFile("res/fonts/impact.ttf")) {
		std::cout << "Impossible to load font for menu";
		return;
	}

	std::vector<std::string> option_names;
	option_names.push_back("Main Menu");
	number_choice = option_names.size();

	options[0].setFont(font);
	//put selectedColor for a default option if you use handleKeyEvent.
	options[0].setFillColor(sf::Color::White);
	options[0].setString(option_names[0]);
	options[0].setCharacterSize(char_size);
	sf::FloatRect rect = options[0].getGlobalBounds();
	//SFML draw with the top-left corner as origin, so we have to center the position.
	options[0].setPosition(sf::Vector2f(width / 2 - rect.width / 2, (height / (number_choice + 1)) * 1 - rect.height / 2 + 200));
}

void GameOverMenu::render(sf::RenderWindow& window) {
	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("Game Over");
	gameOverText.setCharacterSize(char_size * 2);
	sf::FloatRect rect = gameOverText.getGlobalBounds();
	gameOverText.setPosition(sf::Vector2f(width / 2 - rect.width / 2, -rect.height / 2 + 300));
	window.draw(gameOverText);

	sf::Text gameOverSubText;
	gameOverSubText.setFont(font);
	gameOverSubText.setFillColor(sf::Color::Red);
	gameOverSubText.setString("You bad rula");
	gameOverSubText.setCharacterSize(char_size / 2);
	rect = gameOverSubText.getGlobalBounds();
	gameOverSubText.setPosition(sf::Vector2f(width / 2 - rect.width / 2, -rect.height / 2 + 450));
	window.draw(gameOverSubText);
	
	Menu::render(window);
}

#pragma endregion RTSStateFunctions
