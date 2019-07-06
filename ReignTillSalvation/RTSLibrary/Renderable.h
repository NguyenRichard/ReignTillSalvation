#pragma once
#include "SFML/Graphics.hpp"
#include "ObjectLogic.h"


class Renderable {
private:
	std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>,int>>> drawables;
	ObjectLogic* object;
	int animcount; // if animcount = -1, no animation. (WARNING: Drawable must be a sprite if animcount != -1)
public:
	void render(sf::RenderWindow& window);
	void updateAnimation();
};