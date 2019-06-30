#include "Individual.h"

Individual::Individual(std::unique_ptr<IndividualState> new_state, sf::Vector2f coord) :
	state (std::move(new_state))
{
	state->setCoord(coord);
}

Individual::Individual(std::unique_ptr<IndividualState> new_state, sf::Vector2f coord,
		Element* liked, Element* disliked) :
	state(std::move(new_state)), liked(liked), disliked(disliked)
{
	state->setCoord(coord);
}

void Individual::changeState(std::unique_ptr<IndividualState> new_state) {
	state = std::move(new_state);
}

void Individual::action() {
	state->action();
}


void Individual::updatePositionAttraction() {
	bool likedHasBeenApplied = false;
	bool dislikedHasBeenApplied = false;
	sf::Vector2f my_coord = getCoord();

	for (Element* element: elements)
		for (sf::Vector2f coord : element->getCoords())
			if (distanceToPoint(coord) < element->getRangeUnmutable()) {
				sf::Vector2f direction = directionToward(coord);

				int power = element->getPower();
				if (liked && liked == element) {
					power += NATURAL_ATTRACTION;
					likedHasBeenApplied = true;
				}
				if (disliked && disliked == element) {
					power -= NATURAL_ATTRACTION;
					dislikedHasBeenApplied = true;
				}

				if (power > MAX_POWER)
					power = MAX_POWER;
				if (power < -MAX_POWER)
					power = -MAX_POWER;

				my_coord += sf::Vector2f(power * direction.x / ATTRACTION_DIVIDER,
					power * direction.y / ATTRACTION_DIVIDER);
			}

	if (liked && !likedHasBeenApplied)
			for (sf::Vector2f coord : liked->getCoords())
				if (distanceToPoint(coord) < liked->getRangeUnmutable()) {
					sf::Vector2f direction = directionToward(coord);
					my_coord += sf::Vector2f(NATURAL_ATTRACTION * direction.x / ATTRACTION_DIVIDER,
						NATURAL_ATTRACTION * direction.y / ATTRACTION_DIVIDER);
				}

	if (disliked && !dislikedHasBeenApplied)
		for (sf::Vector2f coord : disliked->getCoords())
			if (distanceToPoint(coord) < disliked->getRangeUnmutable()) {
				sf::Vector2f direction = directionToward(coord);
				my_coord += sf::Vector2f(-NATURAL_ATTRACTION * direction.x / ATTRACTION_DIVIDER,
					-NATURAL_ATTRACTION * direction.y / ATTRACTION_DIVIDER);
			}

	if (my_coord.x < 0)
		my_coord.x = 0;
	if (my_coord.y < 0)
		my_coord.y = 0;

	float outside_mvt_x = my_coord.x - WINDOW_WIDTH;
	float outside_mvt_y = my_coord.y - WINDOW_HEIGHT;

	if (outside_mvt_x > 0)
		my_coord.x -= outside_mvt_x;
	if (outside_mvt_y > 0)
		my_coord.y -= outside_mvt_y;

	setCoord(my_coord);
}

void Individual::updatePosition(std::vector<std::unique_ptr<Element>>& map_elements) {
	updatePositionAttraction();
	state->updatePositionChaos(map_elements);
}

float Individual::distanceToIndividual(const Individual & individual) const {
	return state->distanceToIndividual(*individual.state.get());
}


float Individual::distanceToIndividual(const IndividualState& individual) const {
	return state->distanceToIndividual(individual);
}
void Individual::updateMyGroup(std::vector<std::unique_ptr<Individual>>& leaders, int my_position) {
	state->updateMyGroup(this,leaders, my_position);
}

void Individual::findMyGroup(std::vector<std::unique_ptr<Individual>>& leaders, int my_position) {
	state->findGroup(this,leaders, my_position);
}

void Individual::findMyGroupNew(std::vector<std::unique_ptr<Individual>>& leaders, int my_position) {
	state->findGroupNew(this, leaders, my_position);
}

int Individual::findSubPosition(const Individual& individual) {
	return state->findSubPosition(*individual.state);
}

bool Individual:: operator <(const Individual& individual) {
	return state < individual.state;
}


void moveIndividuals(std::vector<std::unique_ptr<Individual>>& vect1, 
	std::vector<std::unique_ptr<Individual>>& vect2, int pos1, int pos2) {
	vect2.insert(vect2.begin()+pos2,std::move(vect1[pos1]));
	vect1.erase(vect1.begin() + pos1);
}

void Individual::deleteElement(Element* element) {
	for (int i = elements.size()-1; i >= 0; i--) {
		if (element == elements[i]) {
			elements.erase(elements.begin() + i);
			return;
		}
	}
}

void Individual::setLiked(Element* el_liked) {
	liked = el_liked;
}

void Individual::setDisliked(Element* el_disliked) {
	disliked = el_disliked;
}

void Individual::addElement(Element* element) {
	elements.push_back(element);
}

