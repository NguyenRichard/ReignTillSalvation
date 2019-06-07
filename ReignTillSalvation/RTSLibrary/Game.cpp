#include "Game.h"
#include "OtherFunctions.h"

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
	std::vector<std::unique_ptr<Element>>& elements = map.getElements();
	sf::Vector2f coord;
	sf::CircleShape* circle;
	float radius;
	std::vector<std::unique_ptr<Individual>>* subordinates;
	Strong* strong;
	for (const auto & leader : leaders) {
		coord = leader->getCoord();
		circle = leader->getState()->getSprite();
		radius = circle->getRadius();
		circle->setPosition(coord.x-radius,coord.y-radius);
		window.draw(*circle);
		strong = dynamic_cast<Strong*>(leader->getState());
		subordinates = &(strong->getSubordinates());
		for (const auto & subordinate : *subordinates) {
			coord = subordinate->getCoord();
			circle = subordinate->getState()->getSprite();
			radius = circle->getRadius();
			circle->setPosition(coord.x - radius, coord.y - radius);
			window.draw(*circle);
		}
	}
	std::vector<sf::Vector2f> element_coords;
	for (const auto & element : elements) {
		circle = element.get()->getSprite();
		radius = circle->getRadius();
		element_coords = element.get()->getCoords();
		float range = element.get()->getRangeUnmutable();
		for (const auto & element_coord : element_coords) {
			circle->setPosition(element_coord.x-radius,element_coord.y-radius);
			circle->setRadius(range);
			window.draw(*circle);
		}
	}
}

void::Game::init() {
	for (int i = 0; i < MAX_INDIVIDUALS; i++) {
		map.createIndividual(sf::Vector2f(randomint(WINDOW_WIDTH), randomint(WINDOW_HEIGHT)));
	}

	//parseXML();
}

void Game::update() {
	map.updateGroup();
	map.updatePositions();
}

void Game::parseXML() {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(XML_FILE_PATH.c_str());

	pugi::xpath_node_set elements = doc.select_nodes("/ElementsResource/Element");
	for (pugi::xpath_node_set::const_iterator it = elements.begin(); it != elements.end(); ++it)
	{
		pugi::xpath_node node = *it;
		std::string name = node.node().child("name").value();
		float range = std::stof(node.node().child("range").value());
		sf::Color color = stringToColor(node.node().child("color").value());
		std::string attractionMessage = node.node().child("attractionMessage").value();
		std::string repulsionMessage = node.node().child("repulsionMessage").value();
		map.createElement(name, range, color, attractionMessage, repulsionMessage);
	}
}


#pragma endregion RTSStateFunctions