#pragma once

#include <SFML\Graphics.hpp>
#include "Value.h"
#include "OtherFunctions.h"
#include "ObjectLogic.h"

class Attraction;


class Element : public ObjectLogic
{
public:
	Element(std::string name);
	Element(std::string name, float range);
	Element(std::string name, float range, sf::Color color,
		std::string attractionMessage, std::string repulsionMessage, std::string cancelMessage,sf::Texture*);
	void addCoord(sf::Vector2f);
	std::string getName() const { return name; };
	std::vector<sf::Vector2f>& getCoords() { return coords; };
	sf::CircleShape* getRangeShape() { return &rangeShape; };
	sf::Sprite* getSprite() { return &sprite; };
	float& getRangeMutable() { return range; };
	float getRangeUnmutable() { return range; };
	std::vector<sf::Vector2f> getCoords() const;
	float getPower() const { return power; };
	void changePower(const float &offset) { power += offset; };
	std::string getAttractionMessage() { return attractionMessage; };
	std::string getRepulsionMessage() { return repulsionMessage; };
	std::string getCancelMessage() { return cancelMessage; };
	//void render(sf::RenderWindow& window);
	//void changeSprite();
	void updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>>&);

	bool operator ==(const Element&);

private:
	std::string name;
	std::vector<sf::Vector2f> coords;
	float range;
	sf::CircleShape rangeShape;
	sf::Sprite sprite;
	sf::Texture* texture;
	std::string attractionMessage;
	std::string repulsionMessage;
	std::string cancelMessage;
	float power;
};
