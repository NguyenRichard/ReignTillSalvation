#include "IndividualState.h"


IndividualState::IndividualState(std::pair<sf::Texture, sf::Texture>* textures) : 
	textures(textures) {}

IndividualState::IndividualState(const IndividualState & state) : 
	coord(state.coord), 
	textures(state.textures) {}

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

bool IndividualState:: operator <(const IndividualState& individual) {
	return myStrength() < individual.myStrength();
}

void IndividualState::rotateSprite(float degree) {
	sprite.setRotation(degree);
}