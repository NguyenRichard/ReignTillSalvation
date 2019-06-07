#pragma once
#include <SFML\Graphics.hpp>
#include "Individual.h"
#include "Strong.h"
#include "Element.h"
#include "Value.h"
#include "Weak.h"
#include "OtherFunctions.h"
#include "Law.h"

class Map
{
private:
	std::vector<std::unique_ptr<Individual>> leaders;
	std::vector<std::unique_ptr<Element>> elements;
	std::vector<std::unique_ptr<Law>> laws;
public:
	Map() = default;
	void createIndividual(sf::Vector2f);
	void createElement(std::string, float);
	void createElement(std::string, float, sf::Color, std::string, std::string, std::string);
	void addElementInMap(std::string, sf::Vector2f);
	void updatePositions();
	std::vector<std::unique_ptr<Individual>>& getLeaders() { return leaders; };
	std::vector<std::unique_ptr<Element>>& getElements() { return elements; };
	std::vector<std::unique_ptr<Law>>& getLaws() { return laws; };

	void updateGroup();
	int individualsNumber();
};

