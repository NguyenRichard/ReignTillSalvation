#include "Individual.h"

void Individual::changeState() {
	state = move(state->changeState());
}

void Individual::action() {
	state->action();
}
