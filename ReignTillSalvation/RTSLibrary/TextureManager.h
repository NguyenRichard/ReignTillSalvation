#pragma once

#include "SFML/Graphics.hpp"

class TextureManager {
public:
	TextureManager() = default;
	std::vector<std::pair<sf::Texture, sf::Texture>> individuals;

};