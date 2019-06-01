#pragma once
#include <SFML\Graphics.hpp>
#include "Individual.h"
#include "Element.h"

class Map
{
private:
	std::vector<std::unique_ptr<Individual>> leaders;
	std::vector<std::unique_ptr<Element>> elements;
public:
	Map() = default;
	void createIndividual(sf::Vector2f);
	void updatePositions();
	std::vector<std::unique_ptr<Individual>>& getLeaders() { return leaders; };
};

