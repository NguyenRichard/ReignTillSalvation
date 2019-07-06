#include "Renderable.h"

Renderable::Renderable(CircleDanger* danger, const TextureManager &textureManager) : object(danger)
{
	float radius = (float)MIN_RADIUS_DANGER + randomint(MAX_RADIUS_DANGER - MIN_RADIUS_DANGER);
	shape = std::make_unique<sf::CircleShape>(radius);
	sf::Vector2f coord;
	coord.x = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_WIDTH - 2 * DEFAULT_RADIUS_DANGER);
	coord.y = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_HEIGHT - 2 * DEFAULT_RADIUS_DANGER);
	shape->setOrigin(sf::Vector2f(radius, radius));
	shape->setPosition(coord);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape->setFillColor(color);
	shape->setOutlineThickness(2);
	color.a = 150.0f;
	shape->setOutlineColor(color);

	drawables.push_back(std::move(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>(std::move(shape), NULL)));

	std::vector<sfvector<sf:Texture * >> textures;
	textures.push_back(&textureManager.dangers.find("explosion")->second);
	drawables.push_back(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>(
		nullptr, std::pair<textures, 0>));
}

Renderable::Renderable(LineDanger* danger, const TextureManager &textureManager) : object(danger)
{
	float length = (float)2 * sqrt(pow(WINDOW_HEIGHT, 2) + pow(WINDOW_WIDTH, 2));
	width = (float)MIN_WIDTH_DANGER + randomint(MAX_WIDTH_DANGER - MIN_WIDTH_DANGER);
	std::unique_ptr<sf:RectangleShape> shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(length, width));

	coord.x = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_WIDTH - 2 * DEFAULT_RADIUS_DANGER);
	coord.y = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_HEIGHT - 2 * DEFAULT_RADIUS_DANGER);
	shape->setOrigin(sf::Vector2f(length / 2, width / 2));
	shape->setPosition(coord);


	direction.x = (float)(1 + randomint(9)) / 10;
	direction.y = (float)(1 + randomint(9)) / 10;
	direction.y *= (randomint(1) == 0) ? 1 : -1;
	direction.x = direction.x / magnitude(direction);
	direction.y = direction.y / magnitude(direction);
	rotation = 180.0f / PI * atan(direction.y / direction.x);
	if (direction.y < 0)
		rotation += 180.0f;
	shape->setRotation(rotation);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape->setFillColor(color);
	shape->setOutlineThickness(2);
	color.a = 150.0f;
	shape->setOutlineColor(color);

	drawables.push_back(std::move(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>(std::move(shape), NULL)));

	std::vector<sfvector<sf:Texture * >> textures;
	textures.push_back(&textureManager.dangers.find("laser")->second);
	drawables.push_back(std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>(
		nullptr, std::pair<textures, 0>));
}

void Renderable::render(sf::RenderWindow& window) {
	for (const auto& drawable : drawables) {
		window.draw(*drawable.first);
	}
}

void Renderable::updateAnimation() {
	if (animcount == -1) {
		return;
	}


}