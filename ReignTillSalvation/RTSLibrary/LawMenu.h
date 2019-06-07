#pragma once
#include "Menu.h"
#include "Element.h"
#include "Individual.h"
#include "Law.h"


class LawMenu : public Menu{
public:
	LawMenu(Element*, std::vector<std::unique_ptr<Individual>>*, std::vector<std::unique_ptr<Law>>*,int width, int height);
	void render(sf::RenderWindow& window) override;
	void handleMouseEventClick(sf::RenderWindow& window) override;
private:
	Element* element;
	sf::RectangleShape background;
	std::vector<std::unique_ptr<Individual>>* leaders;
	std::vector<std::unique_ptr<Law>>* laws;
};