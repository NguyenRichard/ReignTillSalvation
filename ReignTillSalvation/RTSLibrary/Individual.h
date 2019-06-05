#pragma once
#include "IndividualState.h"
#include "Attraction.h"
#include "SFML/Graphics.hpp"
#include "Value.h"

class Individual {
public:
	Individual(std::unique_ptr<IndividualState>, sf::Vector2f);
	void changeState();
	void updatePosition();
	void action();
	IndividualState* getState() const { return state.get(); };
	void setCoord(const sf::Vector2f& new_coord) { state->setCoord(new_coord); };
	sf::Vector2f& getCoord() const { return state->getCoord(); };
	void changeColor(sf::Color color);
	float distanceToPoint(const sf::Vector2f &point) const { return state->distanceToPoint(point); };
	float distanceToIndividual(const Individual &individual) const;
	float distanceToIndividual(const IndividualState& const individual) const;
	void applyCollision(const sf::Vector2f&);
	sf::Vector2f directionToward(const sf::Vector2f &point) const 
		{ return state->directionToward(point); };

private:
	int ATTRACTION_DIVIDER = 1;
	std::unique_ptr<IndividualState> state;
	std::vector<std::unique_ptr<Attraction>> attractions;
	
	void updatePositionAttraction();
};