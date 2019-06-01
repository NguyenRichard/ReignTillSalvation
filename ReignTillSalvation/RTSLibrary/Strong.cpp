#include "Strong.h"
#include "Weak.h"

Strong::Strong() {
	sprite.setFillColor(CIRCLE_S_COLOR);
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

void Strong::addSubordinate(std::unique_ptr<Individual> surbordinate) {
	subordinates.push_back(move(surbordinate));
}

std::vector<std::unique_ptr<Individual>>& Strong::getSubordinate() { return subordinates; }