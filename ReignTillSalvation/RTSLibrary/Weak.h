#pragma once
#include "IndividualState.h"

#pragma region define
#define CIRCLE_W_RADIUS 5

#pragma endregion define

class Weak : public IndividualState {
public:
	Weak();
	Weak(const IndividualState & state) {};
	std::unique_ptr<IndividualState> changeState() override;
	void action() override;
	void updatePositionChaos();
	float distanceToLeader() const { return distanceToIndividual(*leader->getState()); };
private:
	float ATTRACTION_TO_LEADER = 1;
	Individual* leader;
};