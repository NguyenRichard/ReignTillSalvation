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
	float rotation = 180.0f / PI * direction.y / direction.x;
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
		if (isInTheZone(individual)) {
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
			if (isInTheZone(weak)) {
				weak->findMyGroupNew(leaders, i);
			}
			i++;
		}
	}
}

bool LineDanger::isInTheZone(std::unique_ptr<Individual> &individual)
{
	sf::Vector2f coord = individual->getCoord();
	sf::Vector2f origin = shape.getPosition();

	float rotationLine = shape.getRotation() * PI / 180.0f;
	sf::Vector2f directionLine = sf::Vector2f(cos(rotationLine), sin(rotationLine));
	
	sf::Vector2f vectorBetween = coord - origin;
	sf::Vector2f directionBetween = sf::Vector2f();
	directionBetween.x = vectorBetween.x / magnitude(vectorBetween);
	directionBetween.y = vectorBetween.y / magnitude(vectorBetween);

	float rotationBetween = acos(directionBetween.x);
	if (directionBetween.y < 0)
		rotationBetween = -rotationBetween;

	// angle between the line and the vector from the origin to the individual
	float rotationRelative = rotationLine - rotationBetween;

	float distancePointToLine = magnitude(vectorBetween) * sin(rotationBetween);
	return distancePointToLine < shape.getSize().x;
}