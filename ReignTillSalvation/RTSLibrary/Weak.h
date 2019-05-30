#pragma once
#include "IndividualState.h"

class Weak : public IndividualState {
public:
	Weak(const IndividualState & state) : IndividualState(state) {};
	std::unique_ptr<IndividualState> changeState() override;
	void action() override;
};