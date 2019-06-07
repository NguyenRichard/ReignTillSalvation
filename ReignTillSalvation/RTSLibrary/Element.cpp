#include "Attraction.h"
#include "Element.h"

Element::Element(std::string name) :
	name(name), coords(), range(DEFAULT_RANGE), power(0.0f) {
	sprite = sf::CircleShape(range);
	sprite.setFillColor(FILL_COLOR);
	sprite.setOutlineThickness(2);
	sprite.setOutlineColor(sf::Color(randomint(255),randomint(255),randomint(255)));
}

Element::Element(std::string name, float new_range) :
	Element(name) {
	range = new_range;
}

Element::Element(std::string name, float range, sf::Color color, std::string attractionMessage,
		std::string repulsionMessage) : name(name), coords(), range(range), power(0),
		attractionMessage(attractionMessage), repulsionMessage(repulsionMessage) {
	sprite = sf::CircleShape(range);
	sprite.setFillColor(FILL_COLOR);
	sprite.setOutlineThickness(2);
	sprite.setOutlineColor(color);
}

void Element::addCoord(sf::Vector2f coord) {
	coords.push_back(coord);
}

std::vector<sf::Vector2f> Element::getCoords() const {
	return coords;
}

bool Element:: operator ==(const Element &element) {
	return name == element.getName();
}