#pragma once

#include "SFML/Graphics.hpp"

class TextureManager {
public:
	TextureManager();
	std::map<std::string,std::pair<sf::Texture, sf::Texture>> individuals;

};