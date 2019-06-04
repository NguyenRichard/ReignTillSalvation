#include "IndividualState.h"


sf::Vector2f IndividualState::directionToward(const sf::Vector2f &point) const {
	sf::Vector2f direction = sf::Vector2f(point.x - coord.x, point.y - coord.y);
	float length = std::hypot(direction.x, direction.y);
	if (length != 0)
		return direction / length;
	return direction;
}


float IndividualState::distanceToPoint(const sf::Vector2f &point) const {
	return std::hypot((point.x - coord.x),(point.y - coord.y));
}


float IndividualState::distanceToIndividual(const IndividualState& individual) const {
	return std::hypot((individual.coord.x - coord.x), (individual.coord.y - coord.y));
}