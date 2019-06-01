#pragma once
#include "IndividualState.h"

#pragma region define
#define CIRCLE_W_RADIUS 40
#define CIRCLE_W_COLOR sf::Color::Green

#pragma endregion define

class Weak : public IndividualState {
public:
	Weak();
	Weak(const IndividualState & state) {};
	std::unique_ptr<IndividualState> changeState() override;
	void action() override;
	void updatePosition() override {};
};