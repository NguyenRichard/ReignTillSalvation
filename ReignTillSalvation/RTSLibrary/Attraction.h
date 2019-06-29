#pragma once

#include "Element.h"
#include "ObjectLogic.h"

class Attraction : public ObjectLogic
{
public:
	Attraction(Element element, int power) :
		element(element), power(power) {};
	~Attraction();

	void updateRejection();
	void updateAttraction();
	int getPower() const;
	Element getElement() const;
private:
	Element element;
	int power;
	int max_power;
};