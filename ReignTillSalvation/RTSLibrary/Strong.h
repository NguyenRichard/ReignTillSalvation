#pragma once

#include <ctime>
#include <cstdlib>

#include "IndividualState.h"
#include "Individual.h"
#include "OtherFunctions.h"
#include "Weak.h"


class Strong : public IndividualState {
public:
	Strong();
	Strong(const IndividualState & state);
	std::unique_ptr<IndividualState> changeState(Individual*);
	void action() override;
	void addSubordinate(std::unique_ptr<Individual>&);
	std::vector<std::unique_ptr<Individual>>& getSubordinates();
	void updatePositionChaos();
	void eraseSubordinate(int);
	void insertSubordinate(const int&, std::unique_ptr<Individual>&);
	bool stillInGroup(int);


	void updateMyGroup(Individual*,std::vector<std::unique_ptr<Individual>>&,int) override;
	void findGroup(Individual*,std::vector<std::unique_ptr<Individual>>& leaders, int my_position) override;

	int myStrength() const override { return subordinates.size(); };
	int findSubPosition(const IndividualState&);
	void makeSubordinate(Individual*, std::vector<std::unique_ptr<Individual>>&,Individual* new_leader, int);
	//new_leader must be a Strong.


private:
	std::vector<std::unique_ptr<Individual>> subordinates; //must be sorted 
};