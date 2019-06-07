#include "LineDanger.h"

LineDanger::LineDanger(float set_countdownAppearance, float set_duration,
		sf::Vector2f coord, sf::Vector2f direction, float width) :
	Danger(set_countdownAppearance, set_duration)
{
	float length = (float)2 * sqrt(pow(WINDOW_HEIGHT, 2) + pow(WINDOW_WIDTH, 2));
	shape = sf::RectangleShape(sf::Vector2f(width, length));

	shape.setOrigin(sf::Vector2f(width / 2, length / 2));

	shape.setPosition(coord);

	direction.x = direction.x / sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	direction.y = direction.y / sqrt(pow(direction.x, 2) + pow(direction.y,2));
	float rotation = 180.0f / PI * direction.x / direction.y;
	shape.setRotation(rotation);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape.setFillColor(color);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Red);
}

void LineDanger::updateOpacity(float opacity)
{
	sf::Color color = shape.getFillColor();
	color.a = opacity;
	shape.setFillColor(color);
}

void LineDanger::affectZone(std::vector<std::unique_ptr<Individual>> &leaders)
{
	sf::Vector2f center = shape.getPosition();
	Strong leader_of_death = Strong();
	int i = 0;
	for (std::unique_ptr<Individual> &individual : leaders)
	{
		if (distanceBetween(center, individual->getCoord()) < shape.getRadius) {
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
			if (distanceBetween(center, weak->getCoord()) > shape.getRadius) {
				weak->findMyGroupNew(leaders, i);
			}
			i++;
		}
	}
}