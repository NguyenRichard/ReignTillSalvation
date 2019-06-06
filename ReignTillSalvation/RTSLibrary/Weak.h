#pragma once
#include "Individual.h"
#include "IndividualState.h"


class Weak : public IndividualState {
public:
	Weak();
	Weak(const IndividualState & state);
	std::unique_ptr<IndividualState> changeState();
	void action() override;
	void updatePositionChaos();
	void setLeader(Individual* leader);
	const Individual* getLeader() const { return leader; };
	float distanceToLeader() const { return distanceToIndividual(*leader->getState()); };

	void updateMyGroup(Individual*,std::vector<std::unique_ptr<Individual>>&,int) override;
	void findGroup(Individual*,std::vector<std::unique_ptr<Individual>>& leaders, int my_position) override;
	int myStrength() const override { return -1; };
	int findSubPosition(const IndividualState&) override { return -1; };
	void makeSubordinate(std::vector<std::unique_ptr<Individual>>&,std::unique_ptr<Individual>&,int);

private:
	Individual* leader;
};