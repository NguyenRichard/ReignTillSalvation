#include "Renderable.h"
#include "Individual.h"
#include "Value.h"


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

	std::unique_ptr<sf::Sprite> sprite;
	sprite->setTexture(*textures[0]);
	sprite->setTextureRect(sf::IntRect(0, 0, STRONG_SPRITE_SIZE, STRONG_SPRITE_SIZE));
	sprite->setOrigin(sf::Vector2f(STRONG_SPRITE_SIZE / 2, STRONG_SPRITE_SIZE / 2));
	sprite->setScale(5, 5);

	drawables.push_back(std::move
	(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>
		(std::move(sprite),std::pair<std::vector<sf::Texture*>, int>(textures,0)
			)));
}

void Renderable::render(sf::RenderWindow& window) {
	for (const auto& drawable : drawables) {
		if (drawable.first != nullptr) {
			window.draw(*drawable.first);
		}
	}
}

void Renderable::updateAnimation() {

	switch (type) {
		case topDown:
			sf::Sprite* sprite;
			sf::IntRect* rect;
			for (const auto& drawable : drawables) {
				sprite = static_cast<sf::Sprite*>(drawable.first.get());
				*rect = sprite->getTextureRect();
				sprite->setTextureRect(sf::IntRect(rect->left,
												animcount*rect->height,
												rect->width,
												rect->height));
			}
			break;
		case leftRight:
			sf::Sprite* sprite;
			sf::IntRect* rect;
			for (const auto& drawable : drawables) {
				sprite = static_cast<sf::Sprite*>(drawable.first.get());
				*rect = sprite->getTextureRect();
				sprite->setTextureRect(sf::IntRect(animcount*rect->width,
												rect->top,
												rect->width,
												rect->height));
			}
			break;
		default: //None included
			break;
	}

}