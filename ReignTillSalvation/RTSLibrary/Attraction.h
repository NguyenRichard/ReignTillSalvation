#pragma once

#include "Element.h"

class Attraction
{
public:
	Attraction(Element element, int power) :
		element(element), power(power) {};
	~Attraction();

	void updateRejection();
	void updateAttraction();
private:
	Element element;
	int power;
	int max_power;
};