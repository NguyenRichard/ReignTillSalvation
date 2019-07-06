#include "Law.h"
#include "Value.h"

Law::Law(Element* element, LawType type) : element(element), type(type) {
	bar.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
	fillBar.setSize(sf::Vector2f(FILLBAR_WIDTH, FILLBAR_HEIGHT));
	bar.setFillColor(sf::Color::White);

}

void Law::updateElement() {

	switch (type) {
	case Attraction:
		if (element->getPower() < MAX_POWER) {
			element->changePower(MAX_POWER / LAW_PROPORTION);
		}
		break;
	case Repulsion:
		if (element->getPower() > -MAX_POWER) {
			element->changePower(-MAX_POWER / LAW_PROPORTION);
		}
		break;
	case Cancel:
		if (element->getPower() > 2*MAX_POWER/LAW_PROPORTION) {
			element->changePower(-MAX_POWER / LAW_PROPORTION);
		}
		else if (element->getPower() < -2 * MAX_POWER / LAW_PROPORTION) {
			element->changePower(MAX_POWER / LAW_PROPORTION);
		}
		break;
	}


}

bool Law::done() {
	return (element->getPower() < 2 * MAX_POWER / LAW_PROPORTION) 
		&& (element->getPower() > -2 * MAX_POWER / LAW_PROPORTION) 
		&& type == Cancel;
}

void Law::render(sf::RenderWindow& window) {
	std::vector<sf::Vector2f> element_coords = element->getCoords();

	for (const auto & coord : element_coords) {
		bar.setPosition(coord.x - ELEMENT_SPRITE_SIZE / 2 + BAR_RELATIVE_COORD_X,
			coord.y - ELEMENT_SPRITE_SIZE / 2 + BAR_RELATIVE_COORD_Y);
		fillBar.setPosition(coord.x - ELEMENT_SPRITE_SIZE / 2 + FILLBAR_RELATIVE_COORD_X,
			coord.y - ELEMENT_SPRITE_SIZE / 2 + FILLBAR_RELATIVE_COORD_Y);
		window.draw(bar);
		window.draw(fillBar);

	}
}

void Law::updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>> drawables) {
	//Each coordinate of the element have two drawables, a bar and a fill bar. We only need to update the fillbar.
	sf::RectangleShape* fillbar;
	for (int i = 0; i < drawables.size()-1; i+=2) {
		fillbar = static_cast<sf::RectangleShape*>(drawables[i].first.get());
		if (element->getPower() > 0) {
			fillBar.setFillColor(ATTRACTION_COLOR);
		}
		else {
			fillBar.setFillColor(REPULSION_COLOR);
		}
		fillBar.setSize(sf::Vector2f((abs(element->getPower()))*FILLBAR_WIDTH / MAX_POWER, FILLBAR_HEIGHT));
	}

}