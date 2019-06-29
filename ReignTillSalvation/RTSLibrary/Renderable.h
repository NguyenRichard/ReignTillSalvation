#pragma once
#include "SFML/Graphics.hpp"
#include "ObjectLogic.h"


class Renderable {
private:
	std::vector <std::pair<sf::Drawable, std::vector<sf::Texture>>> drawables;
	ObjectLogic* object;
};