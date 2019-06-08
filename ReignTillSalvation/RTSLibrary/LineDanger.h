#pragma once

#include "Danger.h"
#include <math.h>

class LineDanger : public Danger
{
public:
	LineDanger(float, float, sf::Vector2f coord, sf::Vector2f direction, float width);
	LineDanger(float, float, sf::Vector2f coord);
	void affectZone(std::vector<std::unique_ptr<Individual>>&);
	sf::RectangleShape &getShape() { return shape; };
private:
	sf::RectangleShape shape;

	void updateOpacity(float opacity);
	bool isInTheZone(std::unique_ptr<Individual> &individual);
};