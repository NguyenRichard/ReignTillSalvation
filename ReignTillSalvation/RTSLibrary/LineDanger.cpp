#include "LineDanger.h"

LineDanger::LineDanger(std::unique_ptr<sftools::Chronometer>& time,
		float set_countdownAppearance, float set_duration, sf::Vector2f coord,
		sf::Vector2f direction, float width, float time_offset, float time_before_next) :
	Danger(time, set_countdownAppearance, set_duration, time_offset, time_before_next)
{
	float length = (float)2 * sqrt(pow(WINDOW_HEIGHT, 2) + pow(WINDOW_WIDTH, 2));
	shape = sf::RectangleShape(sf::Vector2f(length, width));
	
	shape.setOrigin(sf::Vector2f(length / 2, width / 2));
	shape.setPosition(coord);

	direction.x = direction.x / magnitude(direction);
	direction.y = direction.y / magnitude(direction);
	float rotation = 180.0f / PI * atan(direction.y / direction.x);
	if (direction.y < 0)
		rotation += 180.0f;
	shape.setRotation(rotation);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape.setFillColor(color);
	shape.setOutlineThickness(2);
	color.a = 150.0f;
	shape.setOutlineColor(color);
}

LineDanger::LineDanger(std::unique_ptr<sftools::Chronometer>& time, float set_countdownAppearance,
		float set_duration, sf::Vector2f coord) :
	LineDanger(time, set_countdownAppearance, set_duration, coord,
		DEFAULT_DIRECTION_DANGER, DEFAULT_WIDTH_DANGER, 0, 8.0f) {}

LineDanger::LineDanger(std::unique_ptr<sftools::Chronometer> &time,sf::Texture* texture) :
	Danger(time),texture(texture)
{
	float length = (float)2 * sqrt(pow(WINDOW_HEIGHT, 2) + pow(WINDOW_WIDTH, 2));
	float width = (float)MIN_WIDTH_DANGER + randomint(MAX_WIDTH_DANGER - MIN_WIDTH_DANGER);
	shape = sf::RectangleShape(sf::Vector2f(length, width));

	sf::Vector2f coord;
	coord.x = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_WIDTH - 2 * DEFAULT_RADIUS_DANGER);
	coord.y = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_HEIGHT - 2 * DEFAULT_RADIUS_DANGER);
	shape.setOrigin(sf::Vector2f(length / 2, width / 2));
	shape.setPosition(coord);

	sf::Vector2f direction;
	direction.x = (float)randomint(10) / 10;
	direction.y = (float)randomint(10) / 10;
	direction.x = direction.x / magnitude(direction);
	direction.y = direction.y / magnitude(direction);
	float rotation = 180.0f / PI * atan(direction.y / direction.x);
	if (direction.y < 0)
		rotation += 180.0f;
	shape.setRotation(rotation);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape.setFillColor(color);
	shape.setOutlineThickness(2);
	color.a = 150.0f;
	shape.setOutlineColor(color);


	float ratio_length = MULTIPLY_RATIO_LASER_LENTGH * length / BASE_LASER_SPRITE_LENTGH;
	float ratio_width = MULTIPLY_RATIO_LASER_WIDTH * width / BASE_LASER_SPRITE_WIDTH;
	anim_count = 0;
	sprite.setOrigin(sf::Vector2f(length/2,width/2));
	//sprite.setPosition(coord);
	//sprite.setRotation(rotation);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, BASE_LASER_SPRITE_LENTGH, BASE_LASER_SPRITE_WIDTH));
	sprite.setScale(ratio_length, ratio_width);
}

void LineDanger::updateOpacity(float opacity)
{
	sf::Color color = shape.getFillColor();
	color.a = opacity;
	shape.setFillColor(color);
}

void LineDanger::affectZone(std::vector<std::unique_ptr<Individual>> &leaders)
{
	sf::Vector2f center = shape.getPosition();
	Strong leader_of_death = Strong();
	int nb_weak_dead = 0;
	for (int i = leaders.size() - 1; i >= 0; i--)
	{
		std::unique_ptr<Individual> &leader = leaders[i];
		if (isInTheZone(leader)) {
			moveIndividuals(leaders, leader_of_death.getSubordinates(),
				i, leader_of_death.getSubordinates().size());
		}
		else
		{
			Strong* strong = dynamic_cast<Strong*>(leader->getState());
			for (int i = strong->getSubordinates().size() - 1; i >= 0; i--)
			{
				std::unique_ptr<Individual> &weak = strong->getSubordinates()[i];
				if (isInTheZone(weak)) {
					moveIndividuals(strong->getSubordinates(), leader_of_death.getSubordinates(), i, 0);
					nb_weak_dead++;
				}
			}
		}
	}

	for (int i = leader_of_death.getSubordinates().size() - 1; i >= nb_weak_dead; i--)
	{
		Strong* strong = dynamic_cast<Strong*>(leader_of_death.getSubordinates()[i]->getState());
		for (int i = strong->getSubordinates().size() - 1; i >= 0; i--)
		{
			std::unique_ptr<Individual> &weak = strong->getSubordinates()[i];
			if (!isInTheZone(weak)) {
				weak->findMyGroupNew(leaders, i);
			}
		}
	}
}

bool LineDanger::isInTheZone(std::unique_ptr<Individual> &individual)
{
	sf::Vector2f coord = individual->getCoord();
	sf::Vector2f origin = shape.getPosition();

	float rotationLine = shape.getRotation();
	rotationLine = rotationLine * PI / 180.0f;
	sf::Vector2f directionLine = sf::Vector2f(cos(rotationLine), sin(rotationLine));
	
	sf::Vector2f vectorBetween = coord - origin;
	sf::Vector2f directionBetween = sf::Vector2f();
	directionBetween.x = vectorBetween.x / magnitude(vectorBetween);
	directionBetween.y = vectorBetween.y / magnitude(vectorBetween);

	float rotationBetween = acos(directionBetween.x);
	if (directionBetween.y < 0)
		rotationBetween = -rotationBetween;

	// angle between the line and the vector from the origin to the individual
	float rotationRelative = rotationLine - rotationBetween;

	float distancePointToLine = abs(magnitude(vectorBetween) * sin(rotationRelative));
	bool ret = distancePointToLine < shape.getSize().y / 2;
	return ret;
}


void LineDanger::render(sf::RenderWindow& window) {
	if (!countdownFinished) {
		window.draw(shape);
	}
	else {
		window.draw(sprite);
		anim_count++;
		if (anim_count*BASE_LASER_SPRITE_WIDTH >= texture->getSize().y) {
			anim_count = 0;
		}
		sprite.setTextureRect(sf::IntRect(0, anim_count*BASE_LASER_SPRITE_WIDTH, BASE_LASER_SPRITE_LENTGH, BASE_LASER_SPRITE_WIDTH));
	}
}