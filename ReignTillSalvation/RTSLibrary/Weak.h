#pragma once
#include "IndividualState.h"
#include "Value.h"


class Weak : public IndividualState {
public:
	Weak();
	Weak(const IndividualState & state);
	std::unique_ptr<IndividualState> changeState() override;
	void action() override;
	void updatePositionChaos();
	void setLeader(Individual* leader);
	const Individual* getLeader() const { return leader; };
private:
	float ATTRACTION_TO_LEADER = 1;
	Individual* leader;

	float distanceToLeader() const { return distanceToIndividual(*leader->getState()); };
};