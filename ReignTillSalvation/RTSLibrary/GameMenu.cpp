#include "GameMenu.h"
#include "GameRunning.h"
#include "LawMenu.h"


GameMenu::GameMenu(const Game & state, std::unique_ptr<Map> new_map,
	std::unique_ptr<sftools::Chronometer> time) :
	Game(state, std::move(new_map), std::move(time))
{
	time->pause();
}

void GameMenu::processInput(RTS* rts, sf::RenderWindow& window, sf::Event& event) {

	if (event.type == sf::Event::KeyReleased) {
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			rts->changeState(changeStateToGameRunning());
			break;
		}

	}
	else {
		menu->handleMouseEvent(rts, window, event);
	}

}

void GameMenu::render(sf::RenderWindow& window) {
	renderMenu(window);
}

void GameMenu::renderMenu(sf::RenderWindow& window) {
	menu->render(window);
}


std::unique_ptr<RTSState> GameMenu::changeStateToGameRunning() {

	return std::make_unique<GameRunning>(*this, std::move(map), std::move(time));

}

void GameMenu::changeState(RTS* rts) {

	rts->changeState(changeStateToGameRunning());


}

void GameMenu::init() {
	menu = std::make_unique<LawMenu>(map->getSelectedElement(), LAW_MENU_WIDTH, LAW_MENU_HEIGHT);
	time->pause();
}