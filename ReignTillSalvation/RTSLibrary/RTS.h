#pragma once
#include "RTSState.h"
#include "SFML/Graphics.hpp"

class RTS {
private:
	std::unique_ptr<RTSState> state;
public:
	RTS(std::unique_ptr<RTSState> new_state);
	void changeState(std::unique_ptr<RTSState>);
	void changeStateAuto();
	void initState() { state->init(); };
	void render(sf::RenderWindow& window);
	void update();
	void processInput(sf::RenderWindow& window);
	RTSState* getState() { return state.get(); };

};