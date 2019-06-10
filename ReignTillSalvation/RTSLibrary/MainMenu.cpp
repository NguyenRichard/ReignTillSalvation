#include "MainMenu.h"
#include "GameRunning.h"

#pragma region MenuFunctions
MainMenu::MainMenu(int width, int height) :
	Menu(), 
	RTSState(width,height, std::make_unique<sf::Music>())
{
	music->openFromFile(MAIN_MUSIC_PATH);
	music->setLoop(true);
	music->play();
}

void MainMenu::handleKeyEventAction(RTS* rts,sf::RenderWindow& window) {
	switch (selectedItemIndex) {
	case 0: //Play option
		changeState(rts);
		break;
	case 2: //Exit option
		window.close();
		break;
	}
}

void MainMenu::handleMouseEventClick(RTS* rts,sf::RenderWindow& window,sf::Event& event) {
	if (event.key.code == sf::Mouse::Left) {
		switch (selectedItemIndex) {
		case 0: //Play option
			changeState(rts);
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
		RTSState(state.getWidth(), state.getHeight(), std::make_unique<sf::Music>()) {
	music->openFromFile(MAIN_MUSIC_PATH);
	music->setLoop(true);
	music->play();
}

void MainMenu::changeState(RTS* rts) {
	rts->changeState(changeStateToGameRunning());
	rts->initState();
}

std::unique_ptr<RTSState> MainMenu::changeStateToGameRunning() {

	return std::make_unique<GameRunning>(*this, std::move(music));

}
void MainMenu::processInput(RTS* rts,sf::RenderWindow& window, sf::Event& event) {
	if (event.type == sf::Event::Closed) {
		window.close();
	}
	if (event.type == sf::Event::KeyReleased) {
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			rts->changeState(changeStateToGameRunning());
			break;
		}

	}
	Menu::handleMouseEvent(rts, window, event);
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
	options[0].setOrigin(sf::Vector2f(rect.width / 2, rect.height / 2));
	options[0].setPosition(sf::Vector2f(width / 2, (height / (number_choice + 1)) * 1 + 250));

	for (int i = 1; i < option_names.size(); i++) {
		options[i].setFont(font);
		options[i].setFillColor(nselectedColor);
		options[i].setString(option_names[i]);
		options[i].setCharacterSize(char_size);
		rect = options[i].getGlobalBounds();
		options[i].setOrigin(sf::Vector2f(rect.width / 2, rect.height / 2));
		options[i].setPosition(sf::Vector2f(width / 2, (height / (number_choice + 1)) * (0.6f * i + 1) + 250));
	}
}

void MainMenu::render(sf::RenderWindow& window) {
	sf::Text title;
	title.setString("Reign till Salvation");
	title.setFont(font);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(char_size * 2.5f);
	sf::FloatRect rect = title.getGlobalBounds();
	title.setOrigin(sf::Vector2f(rect.width / 2, rect.height / 2));
	title.setPosition(sf::Vector2f(width / 2, height / 2 -300));
	Menu::render(window);
	window.draw(title);
}

#pragma endregion RTSStateFunctions
