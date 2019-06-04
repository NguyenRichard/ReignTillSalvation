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

	coord += sf::Vector2f(ATTRACTION_TO_LEADER * direction.x,
		ATTRACTION_TO_LEADER * direction.y);
}

void Weak::setLeader(Individual* individual) {
	leader = individual;
}