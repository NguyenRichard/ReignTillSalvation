#pragma once
#include "Individual.h"
#include "IndividualState.h"
#include "OtherFunctions.h"
#include "Strong.h"


class Weak : public IndividualState {
public:
	Weak();
	Weak(const IndividualState & state);
	void action() override;
	void updatePositionChaos() override;
	void setLeader(Individual* leader);
	const Individual* getLeader() const { return leader; };
	float distanceToLeader() const { return distanceToIndividual(*leader->getState()); };
	std::unique_ptr<IndividualState> changeState();
	void render(sf::RenderWindow&) override;
	void render_and_update(sf::RenderWindow&) override;

	void updateMyGroup(Individual*,std::vector<std::unique_ptr<Individual>>&,int) override;
	void findGroup(Individual*,std::vector<std::unique_ptr<Individual>>& leaders, int my_position) override;
	void findGroupNew(Individual*, std::vector<std::unique_ptr<Individual>>& leaders, int my_position) override;
	int myStrength() const override { return -1; };
	int findSubPosition(const IndividualState&) override { return -1; };
	void makeSubordinate(Individual*,std::vector<std::unique_ptr<Individual>>& new_leader,std::unique_ptr<Individual>&,int);
	void incrementAnim() override;
	void setSpriteDirection(float rotation);
	//new_leader must be a Strong.

private:
	Individual* leader; //must be a Strong.
};
