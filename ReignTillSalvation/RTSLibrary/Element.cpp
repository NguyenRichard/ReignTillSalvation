#include "Attraction.h"
#include "Element.h"
#include "OtherFunctions.h"



Element::Element(std::string name) :
	name(name), coords(), range(DEFAULT_RANGE) {
	sprite = sf::CircleShape(range);
	sprite.setFillColor(FILL_COLOR);
	sprite.setOutlineThickness(2);
	sprite.setOutlineColor(sf::Color(randomint(255),randomint(255),randomint(255)));
}

Element::Element(std::string name, float new_range) :
	Element(name) {
	range = new_range;
}


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

void Element::addCoord(sf::Vector2f coord) {
	coords.push_back(coord);
}

std::vector<sf::Vector2f> Element::getCoords() const {
	return coords;
}