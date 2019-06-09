#pragma once

#include "SFML/Graphics.hpp"

class TextureManager {
public:
	TextureManager();
	std::map<std::string,std::pair<sf::Texture, sf::Texture>> individuals;
	std::map <std::string, sf::Texture> elements;
	sf::Texture map;

private:
	void loadIndividualsSprite();
	void loadElementSprite();
};