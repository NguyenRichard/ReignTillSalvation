#pragma once
#include "SFML/Graphics.hpp"
#include "ObjectLogic.h"
#include "IndividualState.h"
#include "TextureManager.h"
#include "SFML/Graphics.hpp"


enum AnimationType { topDown, leftRight, None };

class Renderable {
private:
	std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>,int>>> drawables;
	ObjectLogic* object;
	int animcount;
	AnimationType type;

public:
	Renderable(CircleDanger*, TextureManager&);
	Renderable(LineDanger*, TextureManager&);
	Renderable(Individual*, TextureManager&);
	void render(sf::RenderWindow& window); //
	void updateAnimation(); // Drawable must be a sprite to animate.
};