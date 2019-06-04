#pragma once
#include "IndividualState.h"

#pragma region define
#define CIRCLE_W_RADIUS 5

#pragma endregion define

class Weak : public IndividualState {
public:
	Weak();
	Weak(const IndividualState & state) : IndividualState(state) {};
	std::unique_ptr<IndividualState> changeState() override;
	void action() override;
	void updatePositionChaos();
	float distanceToLeader() const { return distanceToIndividual(*leader->getState()); };
	void setLeader(Individual* leader);
	const Individual* getLeader() const { return leader; };
private:
	float ATTRACTION_TO_LEADER = 1;
	Individual* leader;
};