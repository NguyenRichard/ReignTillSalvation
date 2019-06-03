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
	virtual std::unique_ptr<IndividualState> changeState() = 0;
	virtual void action() = 0;
	virtual ~IndividualState() = default;
	virtual void updatePosition() {};
	sf::CircleShape* getSprite() { return &sprite; };
	void changeColor(sf::Color color) { sprite.setFillColor(color); };
protected:
	sf::CircleShape sprite;


};

#endif