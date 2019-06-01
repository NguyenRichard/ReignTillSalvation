#pragma once
#include "IndividualState.h"
#include "SFML/Graphics.hpp"

class Individual {
public:
	Individual(std::unique_ptr<IndividualState> state, sf::Vector2f coord) :
		state{ std::move(state) },
		coord(coord)
	{};
	virtual ~Individual() = default;
	void changeState();
	void updatePosition();
	void action();
	IndividualState* getState() { return state.get(); };
	sf::Vector2f getCoord() { return coord; };
private:
	std::unique_ptr<IndividualState> state;
	sf::Vector2f coord;

};