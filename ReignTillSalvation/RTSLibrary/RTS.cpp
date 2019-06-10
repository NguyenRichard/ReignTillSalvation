#include "RTS.h"

RTS::RTS(std::unique_ptr<RTSState> new_state) : 
	state{ std::move(new_state) }
{
	state->init();
}

void RTS::changeState(std::unique_ptr<RTSState> new_state) {
	state = move(new_state);
}

void RTS::render(sf::RenderWindow& window) {
	state->render(window);
}

void RTS::update() {
	state->update(this);
}

void RTS::processInput(sf::RenderWindow& window,sf::Event& event) {
	state->processInput(this,window,event);
}

void RTS::changeStateAuto() {
	state->changeState(this);
}