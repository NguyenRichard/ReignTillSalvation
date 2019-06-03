#include "Individual.h"

void Individual::changeState() {
	state = move(state->changeState());
}

void Individual::action() {
	state->action();
}

void Individual::changeColor(sf::Color color) {
	state->changeColor(color);
}

void Individual::updatePositionAttraction() {
	for (std::unique_ptr<Attraction> &attraction : attractions)
		for (sf::Vector2f coord : attraction->getElement().getCoords())
			if (distanceTo(coord) < attraction->getElement().getRangeUnmutable()) {
				sf::Vector2f direction = directionToward(coord);
				int power = attraction->getPower();
				coord += sf::Vector2f(power * direction.x / ATTRACTION_DIVIDER,
					power * direction.y / ATTRACTION_DIVIDER);
			}
}

void Individual::updatePosition() {
	updatePositionAttraction();
	state->updatePositionChaos();
}