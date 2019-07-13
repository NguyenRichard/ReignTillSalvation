#include "LineDanger.h"
/*
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
	rotation = 180.0f / PI * atan(direction.y / direction.x);
	if (direction.y < 0)
		rotation += 180.0f;
	shape.setRotation(rotation);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape.setFillColor(color);
	shape.setOutlineThickness(2);
	color.a = 150.0f;
	shape.setOutlineColor(color);
}*/
/*
LineDanger::LineDanger(std::unique_ptr<sftools::Chronometer>& time, float set_countdownAppearance,
		float set_duration, sf::Vector2f coord) :
	LineDanger(time, set_countdownAppearance, set_duration, coord,
		DEFAULT_DIRECTION_DANGER, DEFAULT_WIDTH_DANGER, 0, 8.0f) {}*/

LineDanger::LineDanger(std::unique_ptr<sftools::Chronometer> &time, float wait,
		sf::SoundBuffer* buffer) :
	Danger(time, wait), texture(texture), buffer(buffer)
{
	//float length = (float)2 * sqrt(pow(WINDOW_HEIGHT, 2) + pow(WINDOW_WIDTH, 2));
	width = (float)MIN_WIDTH_DANGER + randomint(MAX_WIDTH_DANGER - MIN_WIDTH_DANGER);
	/*shape = sf::RectangleShape(sf::Vector2f(length, width));

	coord.x = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_WIDTH - 2 * DEFAULT_RADIUS_DANGER);
	coord.y = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_HEIGHT - 2 * DEFAULT_RADIUS_DANGER);
	shape.setOrigin(sf::Vector2f(length / 2, width / 2));
	shape.setPosition(coord);*/

	coord = sf::Vector2f(
		(float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_WIDTH - 2 * DEFAULT_RADIUS_DANGER),
		(float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_HEIGHT - 2 * DEFAULT_RADIUS_DANGER)
	);
	direction.x = (float)(1 + randomint(9)) / 10;
	direction.y = (float)(1 + randomint(9)) / 10;
	direction.y *= (randomint(1) == 0) ? 1 : -1;
	direction.x = direction.x / magnitude(direction);
	direction.y = direction.y / magnitude(direction);
	rotation = 180.0f / PI * atan(direction.y / direction.x);
	if (direction.y < 0)
		rotation += 180.0f;
	/*shape.setRotation(rotation);

	sf::Color color = sf::Color::Red;
	color.a = 0;
	shape.setFillColor(color);
	shape.setOutlineThickness(2);
	color.a = 150.0f;
	shape.setOutlineColor(color);

	anim_count = 0;
	float ratio_length = MULTIPLY_RATIO_LASER_LENTGH * sqrt(pow(WINDOW_WIDTH,2)+pow(WINDOW_HEIGHT,2)) / BASE_LASER_SPRITE_LENTGH;
	float ratio_width = MULTIPLY_RATIO_LASER_WIDTH * width / BASE_LASER_SPRITE_WIDTH;
	sprite.setOrigin(sf::Vector2f(BASE_LASER_SPRITE_LENTGH / 2, BASE_LASER_SPRITE_WIDTH / 2));
	
	if (direction.y / direction.x < 0) {
		if (coord.y - coord.x*(direction.y / direction.x) > 0
			&& coord.y - coord.x*(direction.y / direction.x) <= WINDOW_HEIGHT) {
			sprite.setPosition(sf::Vector2f(0, coord.y - coord.x*(direction.y / direction.x)));
		}
		else {
			sprite.setPosition(sf::Vector2f((WINDOW_HEIGHT - coord.y + coord.x*(direction.y / direction.x)) / (direction.y / direction.x), WINDOW_HEIGHT));
		}	
		sprite.setRotation(180.0f+rotation);
	}
	else {
		if ((coord.x*(direction.y / direction.x) - coord.y) / (direction.y / direction.x) > 0 
			&& (coord.x*(direction.y / direction.x) - coord.y) / (direction.y / direction.x) <= WINDOW_WIDTH) 
		{
			sprite.setPosition(sf::Vector2f((coord.x*(direction.y / direction.x) - coord.y) / (direction.y / direction.x), 0));
		}
		else {
			sprite.setPosition(sf::Vector2f(0, coord.y - coord.x*(direction.y / direction.x)));
		}
		sprite.setRotation(rotation);
	}
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, BASE_LASER_SPRITE_LENTGH, BASE_LASER_SPRITE_WIDTH));
	sprite.setScale(ratio_length, ratio_width);
	*/
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


/*void LineDanger::render(sf::RenderWindow& window) {
	sf::CircleShape circle;
	circle.setPosition(shape.getOrigin());
	circle.setFillColor(sf::Color::Yellow);
	circle.setRadius(20);
	window.draw(circle);
	if (!countdownFinished) {
		window.draw(shape);
	}
	else {
		if (!firstRenderBeenDone)
		{
			firstRenderBeenDone = true;
			playSound();
		}

		window.draw(sprite);
		anim_count++;
		if (anim_count*BASE_LASER_SPRITE_WIDTH >= texture->getSize().y) {
			anim_count = 0;
		}
		sprite.setTextureRect(sf::IntRect(0, anim_count*BASE_LASER_SPRITE_WIDTH, BASE_LASER_SPRITE_LENTGH, BASE_LASER_SPRITE_WIDTH));
	}
}*/

void LineDanger::playSound()
{
	sound.setBuffer(*buffer);
	sound.setVolume(30);
	sound.setLoop(false);
	sound.play();
}

void LineDanger::updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>>& drawables)

{
	if (!countdownFinished) {
		sf::RectangleShape* old_shape = static_cast<sf::RectangleShape*>(drawables[0].first.get());
		sf::Color color = old_shape->getFillColor();
		color.a = opacity;
		old_shape->setFillColor(color);
	}

	else
	{
		// if the sprite has not yet been moved
		if (drawables[0].first != nullptr)
		{
			sf::RectangleShape* old_shape = static_cast<sf::RectangleShape*>(drawables[0].first.get());
			std::unique_ptr<sf::Sprite> new_sprite = std::make_unique<sf::Sprite>();

			float length = (float)2 * sqrt(pow(WINDOW_HEIGHT, 2) + pow(WINDOW_WIDTH, 2));
			width = (float)MIN_WIDTH_DANGER + randomint(MAX_WIDTH_DANGER - MIN_WIDTH_DANGER);
			shape = sf::RectangleShape(sf::Vector2f(length, width));

			coord.x = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_WIDTH - 2 * DEFAULT_RADIUS_DANGER);
			coord.y = (float)DEFAULT_RADIUS_DANGER + randomint(WINDOW_HEIGHT - 2 * DEFAULT_RADIUS_DANGER);
			shape.setOrigin(sf::Vector2f(length / 2, width / 2));
			shape.setPosition(coord);


			direction.x = (float)(1 + randomint(9)) / 10;
			direction.y = (float)(1 + randomint(9)) / 10;
			direction.y *= (randomint(1) == 0) ? 1 : -1;
			direction.x = direction.x / magnitude(direction);
			direction.y = direction.y / magnitude(direction);
			rotation = 180.0f / PI * atan(direction.y / direction.x);
			if (direction.y < 0)
				rotation += 180.0f;
			shape.setRotation(rotation);


			anim_count = 0;
			float ratio_length = MULTIPLY_RATIO_LASER_LENTGH * sqrt(pow(WINDOW_WIDTH,2)+pow(WINDOW_HEIGHT,2)) / BASE_LASER_SPRITE_LENTGH;
			float ratio_width = MULTIPLY_RATIO_LASER_WIDTH * width / BASE_LASER_SPRITE_WIDTH;
			sprite.setOrigin(sf::Vector2f(BASE_LASER_SPRITE_LENTGH / 2, BASE_LASER_SPRITE_WIDTH / 2));
	
			if (direction.y / direction.x < 0) {
				if (coord.y - coord.x*(direction.y / direction.x) > 0
					&& coord.y - coord.x*(direction.y / direction.x) <= WINDOW_HEIGHT) {
					sprite.setPosition(sf::Vector2f(0, coord.y - coord.x*(direction.y / direction.x)));
				}
				else {
					sprite.setPosition(sf::Vector2f((WINDOW_HEIGHT - coord.y + coord.x*(direction.y / direction.x)) / (direction.y / direction.x), WINDOW_HEIGHT));
				}	
				sprite.setRotation(180.0f+rotation);
			}
			else {
				if ((coord.x*(direction.y / direction.x) - coord.y) / (direction.y / direction.x) > 0 
					&& (coord.x*(direction.y / direction.x) - coord.y) / (direction.y / direction.x) <= WINDOW_WIDTH) 
				{
					sprite.setPosition(sf::Vector2f((coord.x*(direction.y / direction.x) - coord.y) / (direction.y / direction.x), 0));
				}
				else {
					sprite.setPosition(sf::Vector2f(0, coord.y - coord.x*(direction.y / direction.x)));
				}
				sprite.setRotation(rotation);
			}

			new_sprite->setTexture(*drawables[1].second.first[0]);
			new_sprite->setTextureRect(sf::IntRect(0, 0, BASE_LASER_SPRITE_LENTGH, BASE_LASER_SPRITE_WIDTH));
			new_sprite->setScale(ratio_length, ratio_width);

			drawables[1].first = std::move(new_sprite);
			drawables[0].first.release();

			drawables[1].second.second = 0;	
		}
	}
}