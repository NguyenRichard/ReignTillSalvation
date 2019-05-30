#pragma once
#include "IndividualState.h"
#include "Individual.h"

class Strong : public IndividualState {
public:
	Strong(std::string name) : IndividualState(name) {};
	Strong(const IndividualState & state) : IndividualState(state) {};
	std::unique_ptr<IndividualState> changeState() override;
	void action() override;
	void addSubordinate(std::unique_ptr<Individual>);
private:
	std::vector<std::unique_ptr<Individual>> subordinates; //
};