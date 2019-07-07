#pragma once

#include <ctime>
#include <cstdlib>

#include "IndividualState.h"
#include "Individual.h"
#include "OtherFunctions.h"
#include "Weak.h"


class Strong : public IndividualState {
public:
	Strong() = default;
	Strong(const IndividualState & state);
	void action() override;
	std::vector<std::unique_ptr<Individual>>& getSubordinates();
	void updatePositionChaos(std::vector<std::unique_ptr<Element>>&) override;
	void eraseSubordinate(int);
	bool stillInGroup(int);
	std::unique_ptr<IndividualState> changeState(Individual*);

	void updateMyGroup(Individual*,std::vector<std::unique_ptr<Individual>>&,int) override;
	void findGroup(Individual*,std::vector<std::unique_ptr<Individual>>& leaders, int my_position) override;

	int myStrength() const override { return subordinates.size(); };
	int findSubPosition(const IndividualState&);
	void makeSubordinate(Individual*, std::vector<std::unique_ptr<Individual>>&,Individual* new_leader, int);
	//new_leader must be a Strong.

	void updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>>) override;

private:


	std::vector<std::unique_ptr<Individual>> subordinates; //must be sorted 
};