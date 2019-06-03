#include "Attraction.h"

Attraction::~Attraction() {
	element.deleteAttraction(this);
}

void Attraction::updateAttraction() {
	if (power < max_power)
		power++;
}

void Attraction::updateRejection() {
	if (power > -max_power)
		power--;
}

int Attraction::getPower() const {
	return power;
}

Element Attraction::getElement() const {
	return element;
}