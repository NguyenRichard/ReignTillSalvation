#pragma once

#include <ctime>
#include <cstdlib>

#include "IndividualState.h"
#include "Individual.h"

#pragma region define
#define CIRCLE_S_RADIUS 10

#pragma endregion define

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

	float PI = 3.14159265358979323846f;
	int MAX_TURN = 30;
private:
	std::vector<std::unique_ptr<Individual>> subordinates;
	
	void insertSubordinate(const int&, std::unique_ptr<Individual>&);
};