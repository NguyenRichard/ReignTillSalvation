#ifndef INDIVIDUALSTATE_H
#define INDIVIDUALSTATE_H
#pragma 

#include <memory>
#include <string>
#include <vector>
#include <iostream>

class IndividualState {
public:
	IndividualState(std::string name) : name(name) {};
	IndividualState(const IndividualState & state) : name(state.name) {};
	virtual std::unique_ptr<IndividualState> changeState() = 0;
	virtual void action() = 0;
	virtual ~IndividualState() = default;
protected:
	std::string name;


};

#endif