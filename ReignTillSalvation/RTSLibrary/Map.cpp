#include "Map.h"
#include "Strong.h"

void Map::createIndividual(sf::Vector2f coord) {
	leaders.push_back(std::make_unique<Individual>(std::make_unique<Strong>(),coord));
}

void Map::createElement(std::string name, int range) {
	elements.push_back(std::make_unique<Element>(name, range));
}

void Map::addElementInMap(std::string name, sf::Vector2f coord) {
	for (const auto & element : elements) {
		if (name.compare(element.get()->getName()) == 0) {
			element.get()->addCoord(coord);
			return;
		}
	}
	createElement(name,DEFAULT_RANGE);
	elements.back()->addCoord(coord);
}

void Map::updatePositions() {
	//for (std::unique_ptr<Individual> &leader : leaders)
		//leader.updatePosition();
}