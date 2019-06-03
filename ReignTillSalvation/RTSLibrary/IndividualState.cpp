#include "IndividualState.h"

sf::Vector2f IndividualState::directionToward(const sf::Vector2f &point) const {
	sf::Vector2f direction = sf::Vector2f(point.x - coord.x, point.y - coord.y);
	float length = std::hypot(direction.x, direction.y);
	if (length != 0)
		return direction / length;
	return direction;
}

float IndividualState::distanceTo(const sf::Vector2f &point) const {
	return sqrt(pow(point.x - coord.x, 2) + pow(point.y - coord.y, 2));
}