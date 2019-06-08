#include "Attraction.h"
#include "Element.h"

Element::Element(std::string name) :
	name(name), coords(), range(DEFAULT_RANGE), power(0.0f) {
	rangeShape = sf::CircleShape(range);
	rangeShape.setFillColor(FILL_COLOR);
	rangeShape.setOutlineThickness(2);
	sf::Color color = sf::Color(randomint(255), randomint(255), randomint(255));
	rangeShape.setOutlineColor(color);
	sprite = sf::RectangleShape(sf::Vector2f(ELEMENT_SPRITE_SIZE, ELEMENT_SPRITE_SIZE));
	sprite.setFillColor(color);
}

Element::Element(std::string name, float new_range) :
	Element(name) {
	range = new_range;
}

Element::Element(std::string name, float range, sf::Color color, std::string attractionMessage,
		std::string repulsionMessage, std::string cancelMessage) :
		name(name), coords(), range(range), power(0),
		attractionMessage(attractionMessage),
		repulsionMessage(repulsionMessage),
		cancelMessage(cancelMessage)
{
	rangeShape = sf::CircleShape(range);
	rangeShape.setFillColor(FILL_COLOR);
	rangeShape.setOutlineThickness(2);
	rangeShape.setOutlineColor(color);

	sprite = sf::RectangleShape(sf::Vector2f(ELEMENT_SPRITE_SIZE, ELEMENT_SPRITE_SIZE));
	sprite.setFillColor(color);

}

void Element::addCoord(sf::Vector2f coord) {
	coords.push_back(coord);
}

std::vector<sf::Vector2f> Element::getCoords() const {
	return coords;
}

void Element::render(sf::RenderWindow& window) {
	float sprite_width = sprite.getSize().x;
	float sprite_height = sprite.getSize().y;
	for (const auto & element_coord : coords) {
		rangeShape.setPosition(element_coord.x - range, element_coord.y - range);
		rangeShape.setRadius(range);
		sprite.setPosition(element_coord.x - sprite_width / 2, element_coord.y - sprite_height / 2);
		window.draw(sprite);
		window.draw(rangeShape);
	}
}


bool Element:: operator ==(const Element &element) {
	return name == element.getName();
}