#include "RTS.h"

RTS::RTS(std::unique_ptr<RTSState> new_state) : 
	state{ std::move(new_state) }
{
	state->init();
}

void RTS::changeState() {
	state = move(state->changeState());
	state->init();
}

void RTS::render(sf::RenderWindow& window) {
	state->render(window);
}

void RTS::processInput(sf::RenderWindow& window) {
	state->processInput(window);
	if (state->haveToChangeState()) {
		changeState();
	}
}