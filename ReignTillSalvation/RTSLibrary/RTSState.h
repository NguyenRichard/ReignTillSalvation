#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

class RTSState{
public:
	RTSState(int width, int height) : width(width), height(height), state(false) {};
	virtual ~RTSState() = default;
	virtual std::unique_ptr<RTSState> changeState() = 0;
	virtual void processInput(sf::RenderWindow& window) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void init() = 0;
	int getHeight() const { return height; };
	int getWidth() const { return width; };
	bool haveToChangeState() const { return state; };
protected:
	int height;
	int width;
	bool state; //true when state need to be changed.

};