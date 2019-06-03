#pragma once
#include "SFML/Graphics.hpp"

class ViewManager {
private:
	sf::View view;
public:
	ViewManager() = default;
	ViewManager(sf::RenderWindow& window);
	void set_View(sf::RenderWindow& window);
};
