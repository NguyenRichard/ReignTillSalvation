#ifndef INDIVIDUALSTATE_H
#define INDIVIDUALSTATE_H
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"


class IndividualState {
public:
	IndividualState() = default;
	IndividualState(const IndividualState & state) : coord(state.coord) {};
	virtual std::unique_ptr<IndividualState> changeState() = 0;
	virtual void action() = 0;
	virtual ~IndividualState() = default;
	sf::CircleShape* getSprite() { return &sprite; };
	void changeColor(sf::Color color) { sprite.setFillColor(color); };
	virtual void updatePositionChaos() = 0;

	sf::Vector2f& getCoord() { return coord; };
	float distanceToPoint(const sf::Vector2f&) const;
	float distanceToIndividual(const IndividualState& individual) const;
	sf::Vector2f directionToward(const sf::Vector2f&) const;
	void setCoord(const sf::Vector2f &new_coord) { coord = new_coord; };
	void setOldCoord(const sf::Vector2f &coord) { old_coord = coord; };

protected:
	sf::CircleShape sprite;
	sf::Vector2f coord;
	sf::Vector2f old_coord;
};

#endif