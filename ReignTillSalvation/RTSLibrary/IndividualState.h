#ifndef INDIVIDUALSTATE_H
#define INDIVIDUALSTATE_H
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Value.h"

class Individual;

class IndividualState {
public:
	IndividualState() = default;
	IndividualState(const IndividualState & state) : coord(state.coord) {};
	virtual void action() = 0;
	virtual ~IndividualState() = default;
	sf::CircleShape* getSprite() { return &sprite; };
	void changeColor(const sf::Color& color) { sprite.setFillColor(color); };
	virtual void updatePositionChaos() = 0;
	virtual void render(sf::RenderWindow&) = 0;

	void setCoord(const sf::Vector2f& new_coord) { coord = new_coord; };
	sf::Vector2f& getCoord() { return coord; };
	float distanceToPoint(const sf::Vector2f&) const;
	float distanceToIndividual(const IndividualState& individual) const;
	sf::Vector2f directionToward(const sf::Vector2f&) const;
	void setOldCoord(const sf::Vector2f &coord) { old_coord = coord; };

	virtual void updateMyGroup(Individual*,std::vector<std::unique_ptr<Individual>>&, int) = 0;
	virtual void findGroup(Individual*,std::vector<std::unique_ptr<Individual>>&, int) = 0;
	virtual void findGroupNew(Individual*, std::vector<std::unique_ptr<Individual>>&, int) {};
	virtual int findSubPosition(const IndividualState&) = 0;
	virtual int myStrength() const = 0;

	bool operator <(const IndividualState&);

protected:
	sf::CircleShape sprite;
	sf::Vector2f coord;
	sf::Vector2f old_coord;
};

#endif