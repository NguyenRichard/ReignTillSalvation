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

void Individual::changeColor(const sf::Color& color) {
	state->changeColor(color);
}

void Individual::updatePositionAttraction() {
	for (Element* &element: elements)
		for (sf::Vector2f coord : element->getCoords())
			if (distanceToPoint(coord) < element->getRangeUnmutable()) {
				sf::Vector2f direction = directionToward(coord);

				int power = element->getPower();
				if (liked && liked == element)
					power += NATURAL_ATTRACTION;
				if (disliked && disliked == element)
					power -= NATURAL_ATTRACTION;

				if (power > MAX_POWER)
					power = MAX_POWER;
				if (power < -MAX_POWER)
					power = -MAX_POWER;

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

void Individual::applyCollision(const sf::Vector2f& coord) {

	float dist = this->distanceToPoint(coord);
	if (dist < DIST_BETWEEN_INDIVIDUAL) {
		sf::Vector2f direction = this->directionToward(coord);
		sf::Vector2f my_coord = this->getCoord();
		float direction_x = my_coord.x - (DIST_BETWEEN_INDIVIDUAL - dist)*direction.x;
		float direction_y = my_coord.y - (DIST_BETWEEN_INDIVIDUAL - dist)*direction.y;
		this->setCoord(sf::Vector2f(direction_x, direction_y));

		sf::Vector2f new_coord = getCoord();
		if (coord.x < 0)
			new_coord.x = 0;
		if (coord.y < 0)
			new_coord.y = 0;

		float outside_mvt_x = coord.x - WINDOW_WIDTH;
		float outside_mvt_y = coord.y - WINDOW_HEIGHT;

		if (outside_mvt_x > 0)
			new_coord.x -= outside_mvt_x;
		if (outside_mvt_y > 0)
			new_coord.y -= outside_mvt_y;

		setCoord(new_coord);
	}
}

void Individual::updateMyGroup(std::vector<std::unique_ptr<Individual>>& leaders, int my_position) {
	state->updateMyGroup(this,leaders, my_position);

	/*individual->changeState();
	individual->changeColor(new_leader->getRangeShape()->getFillColor());
	new_position = new_leader->findSubPosition(*individual);
	weak = dynamic_cast<Weak*>(individual->getState());
	weak->setLeader(leader.get());*/
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

void Individual::deleteElement(Element* &element) {
	for (int i = 0; i <= elements.size(); i++) {
		if (element == elements[i]) {
			elements.erase(elements.begin() + i);
			return;
		}
	}
}

void Individual::setLiked(Element* &el_liked) {
	liked = el_liked;
}

void Individual::setDisliked(Element* &el_disliked) {
	disliked = el_disliked;
}

void Individual::addElement(Element* &element) {
	elements.push_back(element);
}