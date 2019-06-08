#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

class RTS;

class RTSState{
public:
	RTSState(int width, int height) : width(width), height(height) {};
	RTSState(const RTSState& state) : width(state.getWidth()), height(state.getHeight()) {};
	virtual ~RTSState() = default;
	virtual void processInput(RTS* rts,sf::RenderWindow& window) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void update() {};
	virtual void init() = 0;
	int getHeight() const { return height; };
	int getWidth() const { return width; };
	virtual void changeState(RTS* rts) = 0;

protected:
	int height;
	int width;

};