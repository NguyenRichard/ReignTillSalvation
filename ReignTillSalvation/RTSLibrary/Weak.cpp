#include "Strong.h"
#include "Weak.h"


std::unique_ptr<IndividualState> Weak::changeState() {
	return std::make_unique<Strong>(*this);
}

void Weak::action() {
	std::cout << "I am weak\n";
}