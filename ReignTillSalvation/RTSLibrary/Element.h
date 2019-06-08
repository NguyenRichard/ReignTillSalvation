#pragma once

#include <SFML\Graphics.hpp>
#include "Value.h"
#include "OtherFunctions.h"

class Attraction;


class Element
{
public:
	Element(std::string name);
	Element(std::string name, float range);
	Element(std::string name, float range, sf::Color color,
		std::string attractionMessage, std::string repulsionMessage, std::string cancelMessage);
	void addCoord(sf::Vector2f);
	std::string getName() const { return name; };
	std::vector<sf::Vector2f>& getCoords() { return coords; };
	sf::CircleShape* getRangeShape() { return &rangeShape; };
	sf::RectangleShape* getSprite() { return &sprite; };
	float& getRangeMutable() { return range; };
	float getRangeUnmutable() { return range; };
	std::vector<sf::Vector2f> getCoords() const;
	float getPower() const { return power; };
	void changePower(const float &offset) { power += offset; };
	std::string getAttractionMessage() { return attractionMessage; };
	std::string getRepulsionMessage() { return repulsionMessage; };
	std::string getCancelMessage() { return cancelMessage; };
	void render(sf::RenderWindow& window);

	bool operator ==(const Element&);

private:
	std::string name;
	std::vector<sf::Vector2f> coords;
	float range;
	sf::CircleShape rangeShape;
	sf::RectangleShape sprite;
	std::string attractionMessage;
	std::string repulsionMessage;
	std::string cancelMessage;
	float power;
};
