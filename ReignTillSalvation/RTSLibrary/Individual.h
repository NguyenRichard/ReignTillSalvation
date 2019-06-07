#pragma once
#include "IndividualState.h"
#include "Attraction.h"
#include "SFML/Graphics.hpp"
#include "Value.h"

class Individual {
public:
	Individual(std::unique_ptr<IndividualState>, sf::Vector2f);
	Individual(std::unique_ptr<IndividualState>, sf::Vector2f, Element*, Element*);
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
	void applyCollision(const sf::Vector2f&,float);
	void applyCollisionElements();
	sf::Vector2f directionToward(const sf::Vector2f &point) const 
		{ return state->directionToward(point); };

	void updateMyGroup(std::vector<std::unique_ptr<Individual>>&, int);
	void findMyGroup(std::vector<std::unique_ptr<Individual>>&, int);
	void findMyGroupNew(std::vector<std::unique_ptr<Individual>>&, int);
	int findSubPosition(const Individual&);
	int myStrength() const { return state->myStrength(); };

	void setLiked(Element* el_liked);
	void setDisliked(Element* el_disliked);
	void addElement(Element* element);
	void deleteElement(Element* element);

	bool operator <(const Individual&);

private:
	int ATTRACTION_DIVIDER = 1;
	std::unique_ptr<IndividualState> state;
	std::vector<std::unique_ptr<Attraction>> attractions;
	std::vector<Element*> elements;
	Element* liked;
	Element* disliked;

	void updatePositionAttraction();
};

void moveIndividuals(std::vector<std::unique_ptr<Individual>>&, std::vector<std::unique_ptr<Individual>>&, int, int);