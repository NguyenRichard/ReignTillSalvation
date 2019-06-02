#pragma once
#include "IndividualState.h"
#include "Individual.h"

#pragma region define
#define CIRCLE_S_RADIUS 10
#define CIRCLE_S_COLOR sf::Color::Red

#pragma endregion define

class Strong : public IndividualState {
public:
	Strong();
	Strong(const IndividualState & state);
	std::unique_ptr<IndividualState> changeState() override;
	void action() override;
	void addSubordinate(std::unique_ptr<Individual>);
	std::vector<std::unique_ptr<Individual>>& getSubordinate();
	void updatePosition() override {};
private:
	std::vector<std::unique_ptr<Individual>> subordinates; //
};