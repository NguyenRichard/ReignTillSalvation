#pragma once

#include "Danger.h"

class CircleDanger : public Danger
{
public:
	CircleDanger(std::unique_ptr<sftools::Chronometer>&, float, float, sf::Vector2f coord, float radius);
	CircleDanger(std::unique_ptr<sftools::Chronometer>&, float, float, sf::Vector2f coord);
	void affectZone(std::vector<std::unique_ptr<Individual>>&);
	sf::CircleShape &getShape() { return shape; };
private:
	sf::CircleShape shape;

	void updateOpacity(float opacity);
};