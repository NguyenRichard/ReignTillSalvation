#include "Attraction.h"
#include "Element.h"

void Element::updateRejections() {
	for (Attraction* attraction : attractions)
		attraction->updateRejection();
}

void Element::updateAttractions() {
	for (Attraction* attraction : attractions)
		attraction->updateAttraction();
}

void Element::deleteAttraction(Attraction *attraction) {
	for (std::vector<Attraction*>::iterator it = attractions.begin(); it < attractions.end(); it++)
		if (*it == attraction) {
			attractions.erase(it);
			break;
		}
}