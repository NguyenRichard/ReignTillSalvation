#include "Strong.h"
#include "Weak.h"
#include "OtherFunctions.h"

Strong::Strong() {
	sprite.setFillColor(sf::Color(randomint(255), randomint(255), randomint(255)));
	sprite.setRadius(CIRCLE_S_RADIUS);
}

Strong::Strong(const IndividualState & state) :
	subordinates() {}

std::unique_ptr<IndividualState> Strong::changeState() {
	return std::make_unique<Weak>(*this);
}

void Strong::action() {
	std::cout << "I am strong.\n";
}

void Strong::addSubordinate(std::unique_ptr<Individual> subordinate) {
	subordinate.get()->changeColor(sprite.getFillColor());
	subordinates.push_back(move(subordinate));
}

std::vector<std::unique_ptr<Individual>>& Strong::getSubordinate() { return subordinates; }

void Strong::updatePositionChaos() {
	srand(time(0));
	float degree = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 9)) + 1;
	// between 1 and 10

	degree = log10(degree); // between 0 and 1
	degree *= MAX_TURN;

	sf::Vector2f direction = -directionToward(old_coord);
	float theta = degree / 180 * PI;
	float cs = cos(theta);
	float sn = sin(theta);

	float new_x = coord.x * cs - coord.y * sn;
	float new_y = coord.x * sn + coord.y * cs;

	old_coord = coord;

	coord.x = new_x;
	coord.y = new_y;
}