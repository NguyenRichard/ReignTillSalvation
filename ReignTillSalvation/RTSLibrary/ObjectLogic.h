#pragma once

class ObjectLogic{
public:
	virtual void updateDrawabbles(std::vector <std::pair<sf::Drawable, std::vector<sf::Texture*>>>) = 0;
};