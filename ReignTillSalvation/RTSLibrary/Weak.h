#pragma once
#include "Individual.h"
#include "IndividualState.h"


class Weak : public IndividualState {
public:
	Weak();
	Weak(const IndividualState & state);
	std::unique_ptr<IndividualState> changeState() override;
	void action() override;
	void updatePositionChaos();
	void setLeader(Individual* leader);
	const Individual* getLeader() const { return leader; };
	float distanceToLeader() const { return distanceToIndividual(*leader->getState()); };
private:
	Individual* leader;
};