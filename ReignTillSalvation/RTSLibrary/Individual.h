#pragma once
#include "IndividualState.h"
#include "Attraction.h"
#include "SFML/Graphics.hpp"

class Individual {
public:
	Individual(std::unique_ptr<IndividualState> state, sf::Vector2f coord) :
		state{ std::move(state) }
	{};
	void changeState();
	void updatePosition();
	void action();
	IndividualState* getState() const { return state.get(); };
	sf::Vector2f& getCoord() const { return state->getCoord(); };
	void changeColor(sf::Color color);
	float distanceToPoint(const sf::Vector2f &point) const { return state->distanceToPoint(point); };
	float distanceToIndividual(const Individual &individual) const;
	float distanceToIndividual(const IndividualState& const individual) const;
	sf::Vector2f directionToward(const sf::Vector2f &point) const 
		{ return state->directionToward(point); };

private:
	int ATTRACTION_DIVIDER = 1;
	std::unique_ptr<IndividualState> state;
	std::vector<std::unique_ptr<Attraction>> attractions;
	
	void updatePositionAttraction();
};