#pragma once
#include <SFML\Graphics.hpp>
#include "Attraction.h"

class Element
{
public:
	Element(std::string name, std::vector<sf::Vector2f> coords, float range) :
		name(name), coords(coords), range(range) {};

	void updateRejections();
	void updateAttractions();
	void deleteAttraction(Attraction*);
private:
	std::string name;
	std::vector<sf::Vector2f> coords;
	float range;
	std::vector<Attraction*> attractions;
};

