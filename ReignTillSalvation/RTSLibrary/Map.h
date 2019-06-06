#pragma once
#include <SFML\Graphics.hpp>
#include "Individual.h"
#include "Strong.h"
#include "Element.h"
#include "Value.h"


class Map
{
private:
	std::vector<std::unique_ptr<Individual>> leaders;
	std::vector<std::unique_ptr<Element>> elements;
public:
	Map() = default;
	void createIndividual(sf::Vector2f);
	void createElement(std::string, int);
	void createElement(std::string, float, sf::Color, std::string, std::string);
	void addElementInMap(std::string, sf::Vector2f);
	void updatePositions();
	std::vector<std::unique_ptr<Individual>>& getLeaders() { return leaders; };
	std::vector<std::unique_ptr<Element>>& getElements() { return elements; };
	void findGroup(std::unique_ptr<Individual>&, int);
	void findStrongerLeader(std::unique_ptr<Individual>&, int);
	void makeLeader(std::unique_ptr<Individual>&);
	void makeSubordinate(std::unique_ptr<Individual>&, int, std::unique_ptr<Individual>&);
	void updateGroup();
	void eraseLeader(int);
};

