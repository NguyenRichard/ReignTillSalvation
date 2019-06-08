#include "GameRunning.h"
#include "GameMenu.h"


GameRunning::GameRunning(const Game & state, std::unique_ptr<Map> new_map) :
	Game(state,std::move(new_map))
{
}


void GameRunning::processInput(RTS* rts, sf::RenderWindow& window) {

	processGameInput(rts,window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		changeState(rts);
	}
}

void GameRunning::render(sf::RenderWindow& window) {
	renderGame(window);
}

void GameRunning::changeState(RTS* rts) {
	rts->changeState(changeStateToMainMenu());
	rts->initState();
}

std::unique_ptr<RTSState> GameRunning::changeStateToMainMenu(){

	return std::make_unique<MainMenu>(*this);

}

std::unique_ptr<RTSState> GameRunning::changeStateToGameMenu() {
	return std::make_unique<GameMenu>(*this,std::move(map));
}

void GameRunning::processGameInput(RTS* rts,sf::RenderWindow& window) {
	std::vector<sf::Vector2f>* coords;
	sf::Event event;

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
	sf::Vector2f coord;
	sf::CircleShape* circle;
	float radius;
	std::vector<std::unique_ptr<Individual>>* subordinates;
	Strong* strong;
	for (const auto & leader : leaders) {
		coord = leader->getCoord();
		circle = leader->getState()->getRangeShape();
		radius = circle->getRadius();
		circle->setPosition(coord.x - radius, coord.y - radius);
		window.draw(*circle);
		strong = dynamic_cast<Strong*>(leader->getState());
		subordinates = &(strong->getSubordinates());
		for (const auto & subordinate : *subordinates) {
			coord = subordinate->getCoord();
			circle = subordinate->getState()->getRangeShape();
			radius = circle->getRadius();
			circle->setPosition(coord.x - radius, coord.y - radius);
			window.draw(*circle);
		}
	}
	std::vector<sf::Vector2f> element_coords;
	sf::RectangleShape* elem_sprite;
	sf::CircleShape* elem_range_sprite;
	float sprite_width;
	float sprite_height;
	float range;
	for (const auto & element : elements) {
		elem_sprite = element.get()->getSprite();
		elem_range_sprite = element.get()->getRangeShape();
		radius = elem_range_sprite->getRadius();
		element_coords = element.get()->getCoords();
		range = element.get()->getRangeUnmutable();
		sprite_width = elem_sprite->getSize().x;
		sprite_height = elem_sprite->getSize().y;
		for (const auto & element_coord : element_coords) {
			elem_range_sprite->setPosition(element_coord.x - radius, element_coord.y - radius);
			elem_range_sprite->setRadius(range);
			elem_sprite->setPosition(element_coord.x - sprite_width / 2, element_coord.y - sprite_height / 2);
			window.draw(*elem_sprite);
			window.draw(*elem_range_sprite);
		}
	}

	sf::Shape* danger_shape;
	for (const auto &danger : dangers) {
		danger_shape = &danger->getShape();
		window.draw(*danger_shape);
	}
}

void GameRunning::update() {
	map->update();
}

void::GameRunning::init() {
	parseXML();
	for (int i = 0; i < MAX_INDIVIDUALS; i++) {
		map->createIndividual(sf::Vector2f(randomint(WINDOW_WIDTH), randomint(WINDOW_HEIGHT)));
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