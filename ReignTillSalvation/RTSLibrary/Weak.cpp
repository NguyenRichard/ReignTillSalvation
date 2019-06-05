#include "Strong.h"
#include "Weak.h"
#include "OtherFunctions.h"



Weak::Weak()
{
	sprite.setRadius(CIRCLE_W_RADIUS);
};

Weak::Weak(const IndividualState & state) : IndividualState(state) {
	sprite.setRadius(CIRCLE_W_RADIUS);
}

std::unique_ptr<IndividualState> Weak::changeState() {
	std::unique_ptr<IndividualState> weak = std::make_unique<Strong>(*this);
	weak->changeColor(sf::Color(randomint(255), randomint(255), randomint(255)));
	return move(weak);
}

void Weak::action() {
	std::cout << "I am weak\n";
}

void Weak::updatePositionChaos() {
	sf::Vector2f direction = directionToward(leader->getCoord());
	old_coord = coord;

	coord += sf::Vector2f(DISTANCE_RUN_SUBORDINATE * direction.x,
		DISTANCE_RUN_SUBORDINATE * direction.y);

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

void Weak::setLeader(Individual* individual) {
	leader = individual;
}