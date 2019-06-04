#pragma once
#include <SFML\Graphics.hpp>
#include "Individual.h"
#include "Strong.h"
#include "Element.h"

#define GROUP_SUB_RANGE 30
#define GROUP_LEAD_RANGE 60

class Map
{
private:
	std::vector<std::unique_ptr<Individual>> leaders;
	std::vector<std::unique_ptr<Element>> elements;
public:
	Map() = default;
	void createIndividual(sf::Vector2f);
	void createElement(std::string, int);
	void addElementInMap(std::string, sf::Vector2f);
	void updatePositions();
	std::vector<std::unique_ptr<Individual>>& getLeaders() { return leaders; };
	std::vector<std::unique_ptr<Element>>& getElements() { return elements; };
	Individual* findLeader(const Individual& individual);
	int findSubPosition(const Individual&, Strong&);
	void updateGroup();
};

