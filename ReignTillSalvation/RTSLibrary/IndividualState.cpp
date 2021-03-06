#include "IndividualState.h"


IndividualState::IndividualState() : anim(sf::Vector2i(0, Right)) {};

IndividualState::IndividualState(std::pair<sf::Texture, sf::Texture>* textures) : 
	textures(textures),
	anim(sf::Vector2i(0,Right))
{}

IndividualState::IndividualState(const IndividualState & state) : 
	coord(state.coord), 
	textures(state.textures),
	anim(state.anim) {}

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


void IndividualState::applyCollision(const sf::Vector2f& compare_coord, float min) {

	float dist = distanceToPoint(compare_coord);
	if (dist < min) {
		sf::Vector2f direction = directionToward(compare_coord);
		float direction_x = coord.x - (min - dist)*direction.x;
		float direction_y = coord.y - (min - dist)*direction.y;
		coord = sf::Vector2f(direction_x, direction_y);

		sf::Vector2f new_coord = coord;
		if (compare_coord.x < 0)
			new_coord.x = 0;
		if (compare_coord.y < 0)
			new_coord.y = 0;

		float outside_mvt_x = compare_coord.x - WINDOW_WIDTH;
		float outside_mvt_y = compare_coord.y - WINDOW_HEIGHT;

		if (outside_mvt_x > 0)
			new_coord.x -= outside_mvt_x;
		if (outside_mvt_y > 0)
			new_coord.y -= outside_mvt_y;

		coord = new_coord;
	}
}

void IndividualState::applyCollisionElements(std::vector<std::unique_ptr<Element>>& elements) {
	for (const auto & element : elements) {
		for (auto coord : element->getCoords()) {
			applyCollision(coord, DIST_TO_ELEMENTS);
		}
	}

}
