#include "CircleDanger.h"

CircleDanger::CircleDanger(float set_countdownAppearance,
	float set_duration, sf::Vector2f coord, float radius) :
	Danger(set_countdownAppearance, set_duration)
{
	shape = sf::CircleShape(radius);

	shape.setOrigin(sf::Vector2f(radius, radius));
	shape.setPosition(coord);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape.setFillColor(color);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Red);
}

void CircleDanger::updateOpacity(float opacity)
{
	sf::Color color = shape.getFillColor();
	color.a = opacity;
	shape.setFillColor(color);
}

void CircleDanger::affectZone(std::vector<std::unique_ptr<Individual>> &leaders)
{
	sf::Vector2f center = shape.getPosition();
	Strong leader_of_death = Strong();
	int i = 0;
	for (std::unique_ptr<Individual> &individual : leaders)
	{
		if (distanceBetween(center, individual->getCoord()) < shape.getRadius()) {
			moveIndividuals(leaders, leader_of_death.getSubordinates(),
				i, leader_of_death.getSubordinates().size());
		}
		i++;
	}

	for (std::unique_ptr<Individual> &individual : leader_of_death.getSubordinates())
	{
		Strong* leader = dynamic_cast<Strong*>(individual->getState());
		i = 0;
		for (std::unique_ptr<Individual> &weak : leader->getSubordinates())
		{
			if (distanceBetween(center, weak->getCoord()) > shape.getRadius()) {
				weak->findMyGroupNew(leaders, i);
			}
			i++;
		}
	}
}