#pragma once
#include "IndividualState.h"

class Individual {
public:
	Individual(std::unique_ptr<IndividualState> state) : state{ std::move(state) } {};
	void changeState();
	void action();
private:
	std::unique_ptr<IndividualState> state;

};