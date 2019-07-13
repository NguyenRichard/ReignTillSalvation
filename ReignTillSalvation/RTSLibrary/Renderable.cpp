#include "Renderable.h"
#include "Individual.h"
#include "Value.h"
#include "CircleDanger.h"
#include "LineDanger.h"


Renderable::Renderable(Individual* individual, TextureManager& textureManager) :
	object(individual->getState())
{
	animcount = 0;
	type = leftRight;

	std::pair<sf::Texture, sf::Texture>* textures_from_manger = 
		&textureManager.individuals.find(individual->getLiked()->getName())->second;

	std::vector<sf::Texture*> textures(2);
	textures[0] = &textures_from_manger->first;
	textures[1] = &textures_from_manger->second;

	std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();
	sprite->setTexture(*textures[0]);
	sprite->setTextureRect(sf::IntRect(0, 0, STRONG_SPRITE_SIZE, STRONG_SPRITE_SIZE));
	sprite->setOrigin(sf::Vector2f(STRONG_SPRITE_SIZE / 2, STRONG_SPRITE_SIZE / 2));
	sprite->setScale(5, 5);

	drawables.push_back(std::move
	(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>
		(std::move(sprite),std::pair<std::vector<sf::Texture*>, int>(textures,0)
			)));
}

Renderable::Renderable(CircleDanger* danger, TextureManager &textureManager) : 
	object(danger)
{
	float radius = (float)MIN_RADIUS_DANGER + randomint(MAX_RADIUS_DANGER - MIN_RADIUS_DANGER);
	std::unique_ptr<sf::CircleShape> shape = std::make_unique<sf::CircleShape>(radius);

	sf::Vector2f coord = danger->getCoord();
	shape->setOrigin(sf::Vector2f(radius, radius));
	shape->setPosition(coord);
	type = leftRight;

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape->setFillColor(color);
	shape->setOutlineThickness(2);
	color.a = 150.0f;
	shape->setOutlineColor(color);

	drawables.push_back(std::move
	(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>
		(std::move(shape), std::pair<std::vector<sf::Texture*>, int>(std::vector<sf::Texture*>(), -1)))); // -1 because there are no texture.

	std::vector<sf::Texture *> textures;
	textures.push_back(&textureManager.dangers.find("explosion")->second);
	drawables.push_back(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>(
		nullptr, std::pair<std::vector<sf::Texture*>, int>(textures, 0)));
}

Renderable::Renderable(LineDanger* danger, TextureManager &textureManager) 
	: object(danger)
{
	float length = (float)2 * sqrt(pow(WINDOW_HEIGHT, 2) + pow(WINDOW_WIDTH, 2));
	float width = (float)MIN_WIDTH_DANGER + randomint(MAX_WIDTH_DANGER - MIN_WIDTH_DANGER);
	std::unique_ptr<sf::RectangleShape> shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(length, width));

	sf::Vector2f coord = danger->getCoord();
	shape->setOrigin(sf::Vector2f(length / 2, width / 2));
	shape->setPosition(coord);
	type = topDown;

	sf::Vector2f direction = danger->getDirection();
	float rotation = 180.0f / PI * atan(direction.y / direction.x);
	if (direction.y < 0)
		rotation += 180.0f;
	shape->setRotation(rotation);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape->setFillColor(color);
	shape->setOutlineThickness(2);
	color.a = 150.0f;
	shape->setOutlineColor(color);

	drawables.push_back(std::move
	(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>
		(std::move(shape), std::pair<std::vector<sf::Texture*>, int>(std::vector<sf::Texture*>(), -1)))); // -1 because there are no texture.

	std::vector<sf::Texture *> textures;
	textures.push_back(&textureManager.dangers.find("laser")->second);
	drawables.push_back(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>(
		nullptr, std::pair<std::vector<sf::Texture*>, int>(textures, 0)));
}

Renderable::Renderable(Element* element, TextureManager &textures)
{
	sf::Color color = sf::Color(randomint(255), randomint(255), randomint(255));
	float range = element->getRangeUnmutable();

	type = leftRight;

	for (auto coord : element->getCoords()) {
		std::unique_ptr<sf::CircleShape> rangeShape = std::make_unique<sf::CircleShape>(range);
		rangeShape->setFillColor(FILL_COLOR);
		rangeShape->setOutlineThickness(2);
		rangeShape->setOutlineColor(color);
		rangeShape->setOrigin(range, range);
		rangeShape->setPosition(coord);

		drawables.push_back(std::move(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>(
			std::move(rangeShape), std::pair<std::vector<sf::Texture*>, int>(std::vector<sf::Texture*>(), -1)
		)));
	}
	
	std::vector<sf::Texture*> texturesVect;
	texturesVect.push_back(&textures.elements.find(element->getName())->second);
	for (auto coord : element->getCoords()) {
		std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();
		sprite->setTexture(textures.elements.find(element->getName())->second);
		sprite->setScale(ELEMENT_SPRITE_RATIO, ELEMENT_SPRITE_RATIO);
		sprite->setOrigin(ELEMENT_SPRITE_SIZE / 2, ELEMENT_SPRITE_SIZE / 2);
		sprite->setPosition(coord);

		drawables.push_back(std::move(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>(
			std::move(sprite), std::pair<std::vector<sf::Texture*>, int>(texturesVect, 1)
		)));
	}
}

Renderable::Renderable(Law* law, TextureManager &textureManager) {
	std::vector<sf::Vector2f> element_coords = law->getElement()->getCoords();

	std::unique_ptr<sf::RectangleShape> bar;
	std::unique_ptr<sf::RectangleShape> fillBar;

	for (const auto & coord : element_coords) {
		bar = std::make_unique<sf::RectangleShape>();
		fillBar = std::make_unique<sf::RectangleShape>();
		bar->setPosition(coord.x - ELEMENT_SPRITE_SIZE / 2 + BAR_RELATIVE_COORD_X,
			coord.y - ELEMENT_SPRITE_SIZE / 2 + BAR_RELATIVE_COORD_Y);
		fillBar->setPosition(coord.x - ELEMENT_SPRITE_SIZE / 2 + FILLBAR_RELATIVE_COORD_X,
			coord.y - ELEMENT_SPRITE_SIZE / 2 + FILLBAR_RELATIVE_COORD_Y);
		bar->setFillColor(sf::Color::White);
		drawables.push_back(std::move
		(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>
			(std::move(bar), std::pair<std::vector<sf::Texture*>, int>(std::vector<sf::Texture*>(), -1)))); // -1 because there are no texture.
		drawables.push_back(std::move
		(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>
			(std::move(fillBar), std::pair<std::vector<sf::Texture*>, int>(std::vector<sf::Texture*>(), -1)))); // -1 because there are no texture.
	}

}

void Renderable::render(sf::RenderWindow& window) {
	object->updateDrawables(drawables);
	for (const auto& drawable : drawables) {
		if (drawable.first != nullptr){
			window.draw(*drawable.first);
		}
	}
}

void Renderable::updateAnimation() {

	sf::Sprite* sprite = nullptr;
	sf::IntRect rect;
	switch (type) {
		case topDown:
			for (const auto& drawable : drawables) {
				sprite = dynamic_cast<sf::Sprite*>(drawable.first.get());
				if (sprite) {
					rect = sprite->getTextureRect();
					sprite->setTextureRect(sf::IntRect(rect.left,
						animcount*rect.height,
						rect.width,
						rect.height));
				}
			}
			break;
		case leftRight:
			for (const auto& drawable : drawables) {
				sprite = dynamic_cast<sf::Sprite*>(drawable.first.get());
				if (sprite) {
					rect = sprite->getTextureRect();
					sprite->setTextureRect(sf::IntRect(animcount*rect.width,
						rect.top,
						rect.width,
						rect.height));
				}
			}
			break;
		default: //None included
			break;
	}

}