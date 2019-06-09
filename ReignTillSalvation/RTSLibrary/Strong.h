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
	Strong(std::pair<sf::Texture, sf::Texture>*);
	Strong(const IndividualState & state);
	void action() override;
	std::vector<std::unique_ptr<Individual>>& getSubordinates();
	void updatePositionChaos() override;
	void eraseSubordinate(int);
	bool stillInGroup(int);
	std::unique_ptr<IndividualState> changeState(Individual*);
	void render(sf::RenderWindow&) override;
	void render_and_update(sf::RenderWindow&) override;
	void incrementAnim() override;
	void setSpriteDirection(float rotation);


	void updateMyGroup(Individual*,std::vector<std::unique_ptr<Individual>>&,int) override;
	void findGroup(Individual*,std::vector<std::unique_ptr<Individual>>& leaders, int my_position) override;

	int myStrength() const override { return subordinates.size(); };
	int findSubPosition(const IndividualState&);
	void makeSubordinate(Individual*, std::vector<std::unique_ptr<Individual>>&,Individual* new_leader, int);
	//new_leader must be a Strong.


private:
	std::vector<std::unique_ptr<Individual>> subordinates; //must be sorted 
};