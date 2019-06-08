#pragma once
#include <SFML\Graphics.hpp>
#include "Individual.h"
#include "Strong.h"
#include "Element.h"
#include "Value.h"
#include "Weak.h"
#include "OtherFunctions.h"
#include "Law.h"
#include "Danger.h"

class Map
{
private:
	std::vector<std::unique_ptr<Individual>> leaders;
	std::vector<std::unique_ptr<Element>> elements;
	std::vector<std::unique_ptr<Law>> laws;
	std::vector<std::unique_ptr<Danger>> dangers;
	Element* selected_element;
	void updateGroup();
	void updateLaws();
	void updatePositions();
	void updateDangers();

public:
	Map() = default;
	void createIndividual(sf::Vector2f);
	void createElement(std::string, float);
	void createElement(std::string, float, sf::Color, std::string, std::string, std::string);
	void createLaw(Element*, LawType);
	void addElementInMap(std::string, sf::Vector2f);
	std::vector<std::unique_ptr<Individual>>& getLeaders() { return leaders; };
	std::vector<std::unique_ptr<Element>>& getElements() { return elements; };
	std::vector<std::unique_ptr<Law>>& getLaws() { return laws; };
	void setSelectedElement(Element* element) { selected_element = element; };
	Element* getSelectedElement() { return selected_element; };

	void update();
	int individualsNumber();
};

