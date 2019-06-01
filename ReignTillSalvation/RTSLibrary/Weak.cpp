#include "Strong.h"
#include "Weak.h"



Weak::Weak()
{
	sprite.setFillColor(CIRCLE_W_COLOR);
	sprite.setRadius(CIRCLE_W_RADIUS);
};

std::unique_ptr<IndividualState> Weak::changeState() {
	return std::make_unique<Strong>(*this);
}

void Weak::action() {
	std::cout << "I am weak\n";
}