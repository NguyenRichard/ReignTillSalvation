#include "GameRunning.h"
#include "GameMenu.h"
#include "GameOverMenu.h"


GameRunning::GameRunning(const Game & state, std::unique_ptr<Map> new_map,
		std::unique_ptr<sftools::Chronometer> new_time, std::unique_ptr<sf::Music> old_music) :
		Game(state, std::move(new_map), std::move(new_time), std::move(old_music))
{
	time->resume();
}

void GameRunning::processInput(RTS* rts, sf::RenderWindow& window, sf::Event& event) {

	if (event.type == sf::Event::KeyReleased) {
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			changeState(rts);
			break;
		}
	}
	if (event.type == sf::Event::MouseButtonReleased) {
		switch (event.mouseButton.button) {
		case sf::Mouse::Left:
			std::vector<sf::Vector2f>* coords;
			sf::Vector2i mousePixelPosition = sf::Mouse::getPosition(window);
			sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePixelPosition);
			for (auto & element : map->getElements()) {
				coords = &element->getCoords();
				for (const auto & coord : *coords) {
					if (distanceBetween(coord, mouseWorldPosition) < ELEMENT_SPRITE_SIZE*(ELEMENT_SPRITE_RATIO-0.5)) {
						map->setSelectedElement(element.get());
						rts->changeState(changeStateToGameMenu());
						rts->initState();
					}
				}
			}
			break;
		}
	}

}

void GameRunning::render(sf::RenderWindow& window) {
	renderGame(window);
	renderAnimation(window);
}

void GameRunning::changeState(RTS* rts) {
	rts->changeState(changeStateToMainMenu());
	rts->initState();
}

std::unique_ptr<RTSState> GameRunning::changeStateToMainMenu(){

	return std::make_unique<MainMenu>(*this);

}

std::unique_ptr<RTSState> GameRunning::changeStateToGameMenu() {
	return std::make_unique<GameMenu>(*this, std::move(map), std::move(time), std::move(music));
}

std::unique_ptr<RTSState> GameRunning::changeStateToGameOverMenu() {
	return std::make_unique<GameOverMenu>(*this);
}

void GameRunning::update(RTS* rts) {
	map->update(time);
	if (!music->getStatus() == music->Playing)
		music->play();
	if (map->getLeaders().size() == 0) {
		rts->changeState(changeStateToGameOverMenu());
		rts->initState();
	}
}

void GameRunning::init() {
	time->resume();
	parseXML();
	for (int i = 0; i < MAX_INDIVIDUALS; i++) {
		renderables.push_back(std::make_unique<Renderable>(map->createIndividual(sf::Vector2f(randomint(WINDOW_WIDTH), randomint(WINDOW_HEIGHT)))));
	}

	sf::Vector2f coord;
	for (int i = 0; i < MAX_ELEMENTS; i++) {
		coord = sf::Vector2f(randomint(WINDOW_WIDTH), randomint(WINDOW_HEIGHT));
		int count = 0;
		while (mustMoveElementCoord(coord)) {
			count++;
			if (count % 10 == 0)
				coord = sf::Vector2f(randomint(WINDOW_WIDTH), randomint(WINDOW_HEIGHT));
			if (count > 50) {
				return;
			}
		}
		map->addElementInMap(map->getElements()[randomint(map->getElements().size()-1)]->getName(), coord);
	}

	for (const auto &element : map->getElements())
	{
		renderables.push_back(Renderable(element, map->getTextureManager()));
	}
}

bool GameRunning::mustMoveElementCoord(sf::Vector2f &coord) {
	for (auto &element : map->getElements())
		for (auto &other_coord : element->getCoords())
			if (distanceBetween(coord, other_coord) < 2 * ELEMENT_SPRITE_SIZE * ELEMENT_SPRITE_RATIO) {
				float signX = (other_coord.x < 2 * ELEMENT_SPRITE_SIZE * ELEMENT_SPRITE_RATIO
					&& coord.x < other_coord.x) ? 1 : randomint(1);
				signX = (other_coord.x > WINDOW_WIDTH -  2 * ELEMENT_SPRITE_SIZE * ELEMENT_SPRITE_RATIO
					&& coord.x > other_coord.x) ? -1 : randomint(1);
				float signY = (other_coord.y < 2 * ELEMENT_SPRITE_SIZE * ELEMENT_SPRITE_RATIO
					&& coord.y < other_coord.y) ? -1 : randomint(1);
				signY = (other_coord.y > WINDOW_HEIGHT - 2 * ELEMENT_SPRITE_SIZE * ELEMENT_SPRITE_RATIO
					&& coord.y > other_coord.y) ? -1 : randomint(1);
				
				coord.x = other_coord.x;
				coord.y = other_coord.y;

				coord.x += signX * 2 * ELEMENT_SPRITE_SIZE * (ELEMENT_SPRITE_RATIO + 0.5) / sqrt(2);
				coord.y += signY * 2 * ELEMENT_SPRITE_SIZE * (ELEMENT_SPRITE_RATIO + 0.5) / sqrt(2);

				return true;
			}
	return false;
}

void GameRunning::parseXML() {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(XML_FILE_PATH.c_str());

	pugi::xpath_node_set elements = doc.select_nodes("/ElementsCollection/Element");
	for (auto &node : elements)
	{
		std::string name = node.node().attribute("name").value();
		float range = (float)atoi(node.node().attribute("range").value());
		sf::Color color = stringToColor(node.node().attribute("color").value());
		std::string attractionMessage = node.node().attribute("attractionMessage").value();
		std::string repulsionMessage = node.node().attribute("repulsionMessage").value();
		std::string cancelMessage = node.node().attribute("cancelMessage").value();
		map->createElement(name, range, color, attractionMessage, repulsionMessage, cancelMessage);
	}
}