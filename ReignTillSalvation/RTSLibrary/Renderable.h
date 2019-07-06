#pragma once
#include "SFML/Graphics.hpp"
#include "ObjectLogic.h"
#include "IndividualState.h"
#include "TextureManager.h"


enum AnimationType { topDown, leftRight, None };

class Renderable {
private:
	std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>,int>>> drawables;
	ObjectLogic* object;
	int animcount;
	AnimationType type;

public:
<<<<<<< HEAD
	Renderable(CircleDanger*, const TextureManager&);
	Renderable(LineDanger*, const TextureManager&);
	void render(sf::RenderWindow& window);
	void updateAnimation();
=======
	Renderable(Individual*, TextureManager&);
	void render(sf::RenderWindow& window); //
	void updateAnimation(); // Drawable must be a sprite to animate.
>>>>>>> f431030f8fe71b2750b55eb9757bd20018754541
};