#pragma once

#include <SFML\Graphics.hpp>

#include "OtherFunctions.h"

class Attraction;

#pragma region define
#define DEFAULT_RANGE 30
#define FILL_COLOR sf::Color(255,255,255,0)
#define OUTLINE_COLOR sf::Color(255,255,255,255)

#pragma endregion define


class Element
{
public:
	Element(std::string name);
	Element(std::string name, float range);
	Element(std::string name, float range, sf::Color color,
		std::string attractionMessage, std::string repulsionMessage, std::string cancelMessage);
	void addCoord(sf::Vector2f);
	std::string getName() const { return name; }
	std::vector<sf::Vector2f>& getCoords() { return coords;  }
	sf::CircleShape* getRangeShape() { return &rangeShape; }
	float& getRangeMutable() { return range; }
	float getRangeUnmutable() { return range; }
	std::vector<sf::Vector2f> getCoords() const;
	float getPower() const { return power; };
	void changePower(const float &offset) { power += offset; };
	std::string getAttractionMessage() { return attractionMessage; };
	std::string getRepulsionMessage() { return repulsionMessage; };
	std::string getCancelMessage() { return cancelMessage; };

	bool operator ==(const Element&);

private:
	std::string name;
	std::vector<sf::Vector2f> coords;
	float range;
	sf::CircleShape rangeShape;
	std::string attractionMessage;
	std::string repulsionMessage;
	std::string cancelMessage;
	float power;
};
