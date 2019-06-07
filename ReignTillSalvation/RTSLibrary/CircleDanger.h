#pragma once

#include "Danger.h"

class CircleDanger : Danger
{
public:
	CircleDanger(float, float, sf::Vector2f coord, float radius);
	void affectZone(std::vector<std::unique_ptr<Individual>>&);
	sf::CircleShape &getShape() { return shape; };
private:
	sf::CircleShape shape;

	void updateOpacity(float opacity);
};