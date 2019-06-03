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