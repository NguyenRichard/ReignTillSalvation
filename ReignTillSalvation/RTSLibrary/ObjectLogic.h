#pragma once

class ObjectLogic{
public:
	virtual void updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>>&) = 0;
};