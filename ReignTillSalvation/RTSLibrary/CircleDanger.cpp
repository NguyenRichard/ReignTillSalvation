#include "CircleDanger.h"

CircleDanger::CircleDanger(std::unique_ptr<sftools::Chronometer>& time,
		float setCountdownAppearance, float setDuration, sf::Vector2f coord,
		float radius, float time_offset, float time_before_next) :
	Danger(time, setCountdownAppearance, setDuration, time_offset, time_before_next)
{
	shape = sf::CircleShape(radius);

	shape.setOrigin(sf::Vector2f(radius, radius));
	shape.setPosition(coord);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape.setFillColor(color);
	shape.setOutlineThickness(2);
	color.a = 150.0f;
	shape.setOutlineColor(color);

}

CircleDanger::CircleDanger(std::unique_ptr<sftools::Chronometer>& time,
		float setCountdownAppearance, float setDuration, sf::Vector2f coord) :
	CircleDanger(time, setCountdownAppearance, setDuration, coord,
		DEFAULT_RADIUS_DANGER, 0, 8.0f) {}

CircleDanger::CircleDanger(std::unique_ptr<sftools::Chronometer> &time, sf::Texture* texture) :
	Danger(time), texture(texture)
{
	float radius = (float)MIN_RADIUS_DANGER + randomint(MAX_RADIUS_DANGER - MIN_RADIUS_DANGER);
	shape = sf::CircleShape(radius);
	sf::Vector2f coord;
	coord.x = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_WIDTH - 2 * DEFAULT_RADIUS_DANGER);
	coord.y = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_HEIGHT - 2 * DEFAULT_RADIUS_DANGER);
	shape.setOrigin(sf::Vector2f(radius, radius));
	shape.setPosition(coord);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape.setFillColor(color);
	shape.setOutlineThickness(2);
	color.a = 150.0f;
	shape.setOutlineColor(color);

	float ratio = MULTIPLY_RATIO_EXPLOSION*radius/BASE_EXPLOSION_SPRITE_SIZE;
	anim_count = 0;
	sprite.setOrigin(sf::Vector2f(ratio*BASE_EXPLOSION_SPRITE_SIZE, ratio*BASE_EXPLOSION_SPRITE_SIZE));
	sprite.setPosition(coord);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, BASE_EXPLOSION_SPRITE_SIZE, BASE_EXPLOSION_SPRITE_SIZE));
	sprite.setScale(ratio, ratio);
}

void CircleDanger::updateOpacity(float opacity)
{
	sf::Color color = shape.getFillColor();
	color.a = opacity;
	shape.setFillColor(color);
}

void CircleDanger::affectZone(std::vector<std::unique_ptr<Individual>> &leaders)
{
	sf::Vector2f center = shape.getPosition();
	Strong leader_of_death = Strong();
	int nb_weak_dead = 0;
	for (int i = leaders.size() - 1; i >= 0; i--)
	{
		std::unique_ptr<Individual> &leader = leaders[i];
		if (distanceBetween(center, leader->getCoord()) < shape.getRadius()) {
			moveIndividuals(leaders, leader_of_death.getSubordinates(),
				i, leader_of_death.getSubordinates().size());
		}
		else
		{
			Strong* strong = dynamic_cast<Strong*>(leader->getState());
			for (int i = strong->getSubordinates().size() - 1; i >= 0; i--)
			{
				std::unique_ptr<Individual> &weak = strong->getSubordinates()[i];
				if (distanceBetween(center, weak->getCoord()) < shape.getRadius()) {
					moveIndividuals(strong->getSubordinates(),
						leader_of_death.getSubordinates(), i, 0);
					nb_weak_dead++;
				}
			}
		}
	}

	for (int i = leader_of_death.getSubordinates().size() - 1; i >= nb_weak_dead ;i--)
	{
		Strong* strong = dynamic_cast<Strong*>(leader_of_death.getSubordinates()[i]->getState());
		for (int i = strong->getSubordinates().size() - 1; i >= 0; i--)
		{
			std::unique_ptr<Individual> &weak = strong->getSubordinates()[i];
			if (distanceBetween(center, weak->getCoord()) > shape.getRadius()) {
				weak->findMyGroupNew(leaders, i);
			}
		}
	}
}

void CircleDanger::render(sf::RenderWindow& window) {
	if (!countdownFinished) {
		window.draw(shape);
	}
	else {
		window.draw(sprite);
		anim_count++;
		if (anim_count*BASE_EXPLOSION_SPRITE_SIZE >= texture->getSize().x) {
			anim_count = 0;
		}
		sprite.setTextureRect(sf::IntRect(anim_count*BASE_EXPLOSION_SPRITE_SIZE, 0, BASE_EXPLOSION_SPRITE_SIZE, BASE_EXPLOSION_SPRITE_SIZE));
	}
}