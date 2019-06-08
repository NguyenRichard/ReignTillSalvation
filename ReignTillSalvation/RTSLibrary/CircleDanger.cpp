#include "CircleDanger.h"

CircleDanger::CircleDanger(float setCountdownAppearance,
	float setDuration, sf::Vector2f coord, float radius) :
	Danger(setCountdownAppearance, setDuration)
{
	shape = sf::CircleShape(radius);

	shape.setOrigin(sf::Vector2f(radius, radius));
	shape.setPosition(coord);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape.setFillColor(color);
	shape.setOutlineThickness(2);
	color.a = 150.0f;
	shape.setOutlineColor(color);
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
	int nb_weak_dead = 0;
	for (int i = leaders.size() - 1; i >= 0; i--)
	{
		std::unique_ptr<Individual> &leader = leaders[i];
		if (distanceBetween(center, leader->getCoord()) < shape.getRadius()) {
			moveIndividuals(leaders, leader_of_death.getSubordinates(),
				i, leader_of_death.getSubordinates().size());
		}
		else
		{
			Strong* strong = dynamic_cast<Strong*>(leader->getState());
			for (int i = strong->getSubordinates().size() - 1; i >= 0; i--)
			{
				std::unique_ptr<Individual> &weak = strong->getSubordinates()[i];
				if (distanceBetween(center, weak->getCoord()) < shape.getRadius()) {
					moveIndividuals(strong->getSubordinates(), leader_of_death.getSubordinates(), i, 0);
					nb_weak_dead++;
				}
			}
		}
	}

	for (int i = leader_of_death.getSubordinates().size() - 1; i >= nb_weak_dead ;i--)
	{
		Strong* strong = dynamic_cast<Strong*>(leader_of_death.getSubordinates()[i]->getState());
		for (int i = strong->getSubordinates().size() - 1; i >= 0; i--)
		{
			std::unique_ptr<Individual> &weak = strong->getSubordinates()[i];
			if (distanceBetween(center, weak->getCoord()) > shape.getRadius()) {
				weak->findMyGroupNew(leaders, i);
			}
		}
	}
}