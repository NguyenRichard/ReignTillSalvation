#pragma once

#include <SFML\Graphics.hpp>

class Attraction;

class Element
{
public:
	Element(std::string name, std::vector<sf::Vector2f> coords, float range) :
		name(name), coords(coords), range(range) {
		sprite = sf::CircleShape(range);
		sprite.setFillColor(sf::Color(255, 255, 255, 0));
		sprite.setOutlineThickness(2);
		sprite.setOutlineColor(sf::Color(255, 255, 255, 255));
	};
	virtual ~Element() = default;
	void updateRejections();
	void updateAttractions();
	void deleteAttraction(Attraction*);
private:
	std::string name;
	std::vector<sf::Vector2f> coords;
	float range;
	std::vector<Attraction*> attractions;
	sf::CircleShape sprite;
};