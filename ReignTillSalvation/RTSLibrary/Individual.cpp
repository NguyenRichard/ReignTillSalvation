#include "Individual.h"

void Individual::changeState() {
	state = move(state->changeState());
}

void Individual::action() {
	state->action();
}

void Individual::changeColor(sf::Color color) {
	state->changeColor(color);
}