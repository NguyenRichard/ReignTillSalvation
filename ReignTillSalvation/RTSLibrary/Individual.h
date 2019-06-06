#pragma once
#include "IndividualState.h"
#include "Attraction.h"
#include "SFML/Graphics.hpp"
#include "Value.h"

class Individual {
public:
	Individual(std::unique_ptr<IndividualState>, sf::Vector2f);
	void changeState(std::unique_ptr<IndividualState>);
	void updatePosition();
	void action();
	IndividualState* getState() const { return state.get(); };
	void setCoord(const sf::Vector2f& new_coord) { state->setCoord(new_coord); };
	sf::Vector2f& getCoord() const { return state->getCoord(); };
	void changeColor(const sf::Color& color);
	float distanceToPoint(const sf::Vector2f &point) const { return state->distanceToPoint(point); };
	float distanceToIndividual(const Individual &individual) const;
	float distanceToIndividual(const IndividualState& const individual) const;
	void applyCollision(const sf::Vector2f&);
	sf::Vector2f directionToward(const sf::Vector2f &point) const 
		{ return state->directionToward(point); };

	void updateMyGroup(std::vector<std::unique_ptr<Individual>>&, int);
	void findMyGroup(std::vector<std::unique_ptr<Individual>>&, int);
	int findSubPosition(const Individual&);
	int myStrength() const { return state->myStrength(); };
	std::vector<std::unique_ptr<Individual>>& getSubordinates();

	bool operator <(const Individual&);

private:
	int ATTRACTION_DIVIDER = 1;
	std::unique_ptr<IndividualState> state;
	std::vector<std::unique_ptr<Attraction>> attractions;
	
	void updatePositionAttraction();
};



void moveIndividuals(std::vector<std::unique_ptr<Individual>>&, std::vector<std::unique_ptr<Individual>>&, int, int);