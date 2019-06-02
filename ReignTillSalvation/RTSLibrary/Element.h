#pragma once

#include <SFML\Graphics.hpp>
#include <random>

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
	void addCoord(sf::Vector2f);
	void updateRejections();
	void updateAttractions();
	void deleteAttraction(Attraction*);
	std::string getName() const { return name; }
	std::vector<sf::Vector2f>& getCoords() { return coords;  }
	sf::CircleShape* getSprite() { return &sprite; }
	float& getRangeMutable() { return range; }
	float getRangeUnmutable() { return range; }
private:
	std::string name;
	std::vector<sf::Vector2f> coords;
	float range;
	std::vector<Attraction*> attractions;
	sf::CircleShape sprite;
};

int randomint(int const n);