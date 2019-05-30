#include "Strong.h"
#include "Weak.h"


std::unique_ptr<IndividualState> Strong::changeState() {
	return std::make_unique<Weak>(*this);
}

void Strong::action() {
	std::cout << "I am strong.\n";
}

void Strong::addSubordinate(std::unique_ptr<Individual> surbordinate) {
	subordinates.push_back(move(surbordinate));
}