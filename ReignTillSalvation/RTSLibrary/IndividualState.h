#ifndef INDIVIDUALSTATE_H
#define INDIVIDUALSTATE_H
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Value.h"
#include "Element.h"


class Individual;

enum Dir { Down, DownLeft, Left, TopLeft, Top, TopRight, Right, DownRight };

class IndividualState : public ObjectLogic {
public:
	IndividualState() {};
	IndividualState(const IndividualState & state);
	virtual void action() = 0;
	virtual ~IndividualState() = default;
	virtual void updatePositionChaos(std::vector<std::unique_ptr<Element>>&) = 0;
	void applyCollision(const sf::Vector2f&, float);
	void applyCollisionElements(std::vector<std::unique_ptr<Element>>& elements);

	void setCoord(const sf::Vector2f& new_coord) { coord = new_coord; };
	sf::Vector2f& getCoord() { return coord; };
	sf::Vector2f& getOldCoord() { return old_coord; };
	float distanceToPoint(const sf::Vector2f&) const;
	float distanceToIndividual(const IndividualState& individual) const;
	sf::Vector2f directionToward(const sf::Vector2f&) const;
	void setOldCoord(const sf::Vector2f &coord) { old_coord = coord; };

	virtual void updateMyGroup(Individual*,std::vector<std::unique_ptr<Individual>>&, int) = 0;
	virtual void findGroup(Individual*,std::vector<std::unique_ptr<Individual>>&, int) = 0;
	virtual void findGroupNew(Individual*, std::vector<std::unique_ptr<Individual>>&, int) {};
	virtual int findSubPosition(const IndividualState&) = 0;
	virtual int myStrength() const = 0;

	void updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>>) override;

	bool operator <(const IndividualState&);

protected:
	void setSpriteDirection(float, sf::IntRect&);

	sf::Vector2f coord;
	sf::Vector2f old_coord;
};

#endif