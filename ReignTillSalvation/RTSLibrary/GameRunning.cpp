#include "GameRunning.h"
#include "GameMenu.h"


GameRunning::GameRunning(const Game & state, std::unique_ptr<Map> new_map, std::unique_ptr<sftools::Chronometer> new_time) :
	Game(state, std::move(new_map), std::move(new_time))
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
					if (distanceBetween(coord, mouseWorldPosition) < ELEMENT_SPRITE_SIZE) {
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
	if (time->getElapsedTime().asMilliseconds() - last_render.asMilliseconds() > MS_PER_RENDER) {
		window.clear();
		renderGame(window);
		last_render = time->getElapsedTime();
	}
}

void GameRunning::changeState(RTS* rts) {
	rts->changeState(changeStateToMainMenu());
	rts->initState();
}

std::unique_ptr<RTSState> GameRunning::changeStateToMainMenu(){

	return std::make_unique<MainMenu>(*this);

}

std::unique_ptr<RTSState> GameRunning::changeStateToGameMenu() {
	return std::make_unique<GameMenu>(*this, std::move(map), std::move(time));
}

void GameRunning::processGameInput(RTS* rts,sf::RenderWindow& window) {
	std::vector<sf::Vector2f>* coords;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePixelPosition = sf::Mouse::getPosition(window);
		sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePixelPosition);
		for (auto & element : map->getElements()) {
			coords = &element->getCoords();
			for (const auto & coord : *coords) {
				if (distanceBetween(coord, mouseWorldPosition) < ELEMENT_SPRITE_SIZE) {
					map->setSelectedElement(element.get());
					rts->changeState(changeStateToGameMenu()); 
					rts->initState();
				}
			}
		}
	}

}

void GameRunning::renderGame(sf::RenderWindow& window) {
	std::vector<std::unique_ptr<Individual>>& leaders = map->getLeaders();
	std::vector<std::unique_ptr<Element>>& elements = map->getElements();
	std::vector<std::unique_ptr<Danger>>& dangers = map->getDangers();
	std::vector<std::unique_ptr<Law>>& laws = map->getLaws();

	for (const auto & leader : leaders) {
		leader->render(window);
	}

	for (const auto & element : elements) {
		element->render(window);
	}

	sf::Shape* danger_shape;
	for (const auto &danger : dangers) {
		danger_shape = &danger->getShape();
		window.draw(*danger_shape);
	}

	for (const auto & law : laws) {
		law->render(window);
	}
}

void GameRunning::update() {
	if (time->getElapsedTime().asMilliseconds() - last_update.asMilliseconds() > MS_PER_RENDER) {
		std::cout << time->getElapsedTime().asMilliseconds() << "\n";
		map->update(time);
		last_update = time->getElapsedTime();
	}
}

void::GameRunning::init() {
	time->resume();
	parseXML();
	for (int i = 0; i < MAX_INDIVIDUALS; i++) {
		map->createIndividual(sf::Vector2f(randomint(WINDOW_WIDTH), randomint(WINDOW_HEIGHT)));
	}
	for (int i = 0; i < MAX_ELEMENTS; i++) {
		map->addElementInMap(map->getElements()[randomint(map->getElements().size()-1)]->getName(),
			sf::Vector2f(randomint(WINDOW_WIDTH), randomint(WINDOW_HEIGHT)));
	}
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