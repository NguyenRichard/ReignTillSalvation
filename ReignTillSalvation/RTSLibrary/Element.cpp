#include "Attraction.h"
#include "Element.h"

Element::Element(std::string name) :
	name(name), coords(), range(DEFAULT_RANGE), power(0.0f) {
	rangeShape = sf::CircleShape(range);
	rangeShape.setFillColor(FILL_COLOR);
	rangeShape.setOutlineThickness(2);
	sf::Color color = sf::Color(randomint(255), randomint(255), randomint(255));
	rangeShape.setOutlineColor(color);
}

Element::Element(std::string name, float new_range) :
	Element(name) {
	range = new_range;
}

Element::Element(std::string name, float range, sf::Color color, std::string attractionMessage,
		std::string repulsionMessage, std::string cancelMessage, sf::Texture* texture) :
		name(name), coords(), range(range), power(0),
		attractionMessage(attractionMessage),
		repulsionMessage(repulsionMessage),
		cancelMessage(cancelMessage),
		texture(texture)
{
	rangeShape = sf::CircleShape(range);
	sf::Color fill = color;
	fill.a = 30.0f;
	rangeShape.setFillColor(fill);
	sprite.setTexture(*texture);
	sprite.setScale(ELEMENT_SPRITE_RATIO, ELEMENT_SPRITE_RATIO);


}

void Element::addCoord(sf::Vector2f coord) {
	coords.push_back(coord);
}

std::vector<sf::Vector2f> Element::getCoords() const {
	return coords;
}

/*void Element::render(sf::RenderWindow& window) {
	sprite.setOrigin(ELEMENT_SPRITE_SIZE / 2, ELEMENT_SPRITE_SIZE / 2);
	changeSprite();
	for (const auto & element_coord : coords) {
		rangeShape.setPosition(element_coord.x - range, element_coord.y - range);
		rangeShape.setRadius(range);
		sprite.setPosition(element_coord.x, element_coord.y);
		window.draw(sprite);
		window.draw(rangeShape);
	}
}*/


bool Element:: operator ==(const Element &element) {
	return name == element.getName();
}


/*void Element::changeSprite() {
	if (power > 2*MAX_POWER / LAW_PROPORTION) {
		sprite.setTextureRect(sf::IntRect(1 * ELEMENT_SPRITE_SIZE, 0, ELEMENT_SPRITE_SIZE, ELEMENT_SPRITE_SIZE));
	}
	else if (power < -2*MAX_POWER / LAW_PROPORTION) {
		sprite.setTextureRect(sf::IntRect(2 * ELEMENT_SPRITE_SIZE, 0, ELEMENT_SPRITE_SIZE, ELEMENT_SPRITE_SIZE));
	}
	else {
		sprite.setTextureRect(sf::IntRect(0 * ELEMENT_SPRITE_SIZE, 0, ELEMENT_SPRITE_SIZE, ELEMENT_SPRITE_SIZE));
	}
}*/

void Element::updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>> &drawables)
{
	for (auto &drawable : drawables)
	{
		if (drawable.second.first.size() > 0) {
			sf::Sprite* sprite = static_cast<sf::Sprite*>(drawable.first.get());
			if (power > 2*MAX_POWER / LAW_PROPORTION) {
				sprite->setTextureRect(
					sf::IntRect(1 * ELEMENT_SPRITE_SIZE, 0, ELEMENT_SPRITE_SIZE, ELEMENT_SPRITE_SIZE));
			}
			else if (power < -2*MAX_POWER / LAW_PROPORTION) {
				sprite->setTextureRect(
					sf::IntRect(2 * ELEMENT_SPRITE_SIZE, 0, ELEMENT_SPRITE_SIZE, ELEMENT_SPRITE_SIZE));
			}
			else {
				sprite->setTextureRect(
					sf::IntRect(0 * ELEMENT_SPRITE_SIZE, 0, ELEMENT_SPRITE_SIZE, ELEMENT_SPRITE_SIZE));
			}
		}
	}
}