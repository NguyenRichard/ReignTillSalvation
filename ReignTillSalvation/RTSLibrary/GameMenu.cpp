#include "GameMenu.h"
#include "GameRunning.h"
#include "LawMenu.h"


GameMenu::GameMenu(const Game & state, std::unique_ptr<Map> new_map) :
	Game(state, std::move(new_map))
{
}


void GameMenu::processInput(RTS* rts, sf::RenderWindow& window) {

	menu->handleMouseEvent(rts, window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		rts->changeState(changeStateToGameRunning());
	}
}

void GameMenu::render(sf::RenderWindow& window) {
	renderMenu(window);
}

void GameMenu::renderMenu(sf::RenderWindow& window) {
	menu->render(window);
}


std::unique_ptr<RTSState> GameMenu::changeStateToGameRunning() {

	return std::make_unique<GameRunning>(*this, std::move(map));

}

void GameMenu::changeState(RTS* rts) {

	rts->changeState(changeStateToGameRunning());


}

void GameMenu::init() {
	menu = std::make_unique<LawMenu>(map->getSelectedElement(), LAW_MENU_WIDTH, LAW_MENU_HEIGHT);
}