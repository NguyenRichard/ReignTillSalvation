#include "Individual.h"

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

				if (coord.x < 0)
					coord.x = 0;
				if (coord.y < 0)
					coord.y = 0;

				float outside_mvt_x = coord.x - WINDOW_WIDTH;
				float outside_mvt_y = coord.y - WINDOW_HEIGHT;

				if (outside_mvt_x > 0)
					coord.x -= outside_mvt_x;
				if (outside_mvt_y > 0)
					coord.y -= outside_mvt_y;
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