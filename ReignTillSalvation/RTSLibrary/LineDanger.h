#pragma once

#include "Danger.h"
#include <math.h>

class LineDanger : Danger
{
public:
	LineDanger(float, float, sf::Vector2f coord, sf::Vector2f direction, float width);
	void affectZone(std::vector<std::unique_ptr<Individual>>&);
	sf::RectangleShape &getShape() { return shape; };
private:
	sf::RectangleShape shape;

	void updateOpacity(float opacity);
};