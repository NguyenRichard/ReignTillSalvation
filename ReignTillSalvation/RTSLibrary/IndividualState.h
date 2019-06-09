#ifndef INDIVIDUALSTATE_H
#define INDIVIDUALSTATE_H
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Value.h"

enum Dir {Down, DownLeft, Left, TopLeft, Top, TopRight, Right, DownRight};

class Individual;

class IndividualState {
public:
	IndividualState() = default;
	IndividualState(std::pair<sf::Texture, sf::Texture>*);
	IndividualState(const IndividualState & state);
	virtual void action() = 0;
	virtual ~IndividualState() = default;
	sf::Sprite* getSprite() { return &sprite; };
	void setTextures(std::pair<sf::Texture, sf::Texture>* textures) { this->textures = textures; };
	virtual void updatePositionChaos() = 0;
	virtual void render(sf::RenderWindow&) = 0;
	virtual void render_and_update(sf::RenderWindow&) = 0;

	void setCoord(const sf::Vector2f& new_coord) { coord = new_coord; };
	sf::Vector2f& getCoord() { return coord; };
	sf::Vector2f& getOldCoord() { return old_coord; };
	float distanceToPoint(const sf::Vector2f&) const;
	float distanceToIndividual(const IndividualState& individual) const;
	sf::Vector2f directionToward(const sf::Vector2f&) const;
	void setOldCoord(const sf::Vector2f &coord) { old_coord = coord; };
	void rotateSprite(float degree);

	virtual void updateMyGroup(Individual*,std::vector<std::unique_ptr<Individual>>&, int) = 0;
	virtual void findGroup(Individual*,std::vector<std::unique_ptr<Individual>>&, int) = 0;
	virtual void findGroupNew(Individual*, std::vector<std::unique_ptr<Individual>>&, int) {};
	virtual int findSubPosition(const IndividualState&) = 0;
	virtual int myStrength() const = 0;

	bool operator <(const IndividualState&);

	virtual void incrementAnim() = 0;

protected:
	sf::Sprite sprite;
	std::pair<sf::Texture, sf::Texture>* textures;
	sf::Vector2f coord;
	sf::Vector2f old_coord;
	sf::Vector2i anim;
};

#endif