#include "Individual.h"
#include "Value.h"

Individual::Individual(std::unique_ptr<IndividualState> new_state, sf::Vector2f coord) :
	state (std::move(new_state))
{
	state->setCoord(coord);
}

void Individual::changeState() {
	state = std::move(state->changeState());
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
			if (distanceToPoint(coord) < attraction->getElement().getRangeUnmutable()) {
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



float Individual::distanceToIndividual(const Individual & individual) const {
	return state->distanceToIndividual(*individual.state.get());
}


float Individual::distanceToIndividual(const IndividualState& individual) const {
	return state->distanceToIndividual(individual);
}

void Individual::applyCollision(const Individual& individual) {

	float dist = this->distanceToIndividual(individual);
	if (dist < CIRCLE_S_RADIUS) {
		sf::Vector2f direction = this->directionToward(individual.getCoord());
		sf::Vector2f my_coord = this->getCoord();
		float direction_x = my_coord.x - (CIRCLE_S_RADIUS - dist)*direction.x;
		float direction_y = my_coord.y - (CIRCLE_S_RADIUS - dist)*direction.y;
		this->setCoord(sf::Vector2f(direction_x, direction_y));
	}
}