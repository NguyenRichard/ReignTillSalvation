#include "Map.h"

void Map::createIndividual(sf::Vector2f coord) {
	leaders.push_back(std::make_unique<Individual>(std::make_unique<Strong>(coord)));
}

void Map::updatePositions() {
	for (std::unique_ptr<Individual> &leader : leaders)
		leader.updatePosition();
}