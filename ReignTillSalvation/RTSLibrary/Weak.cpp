#include "Strong.h"
#include "Weak.h"



Weak::Weak()
{
	sprite.setRadius(CIRCLE_W_RADIUS);
};

std::unique_ptr<IndividualState> Weak::changeState() {
	return std::make_unique<Strong>(*this);
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