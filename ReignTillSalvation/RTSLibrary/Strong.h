#pragma once

#include <ctime>
#include <cstdlib>

#include "IndividualState.h"
#include "Individual.h"
#include "Value.h"


class Strong : public IndividualState {
public:
	Strong();
	Strong(const IndividualState & state);
	std::unique_ptr<IndividualState> changeState() override;
	void action() override;
	void addSubordinate(std::unique_ptr<Individual>&);
	std::vector<std::unique_ptr<Individual>>& getSubordinates();
	void updatePositionChaos();
	void eraseSubordinate(int);
	void insertSubordinate(const int&, std::unique_ptr<Individual>&);
	int findSubPosition(const Individual&);
	bool stillInGroup(int);

	float PI = 3.14159265358979323846f;
	int MAX_TURN = 30;
private:
	std::vector<std::unique_ptr<Individual>> subordinates;
};