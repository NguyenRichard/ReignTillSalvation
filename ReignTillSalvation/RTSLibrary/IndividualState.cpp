#include "IndividualState.h"


IndividualState::IndividualState() : anim(sf::Vector2i(0, Right)) {};

IndividualState::IndividualState(std::pair<sf::Texture, sf::Texture>* textures) : 
	textures(textures),
	anim(sf::Vector2i(0,Right))
{}

IndividualState::IndividualState(const IndividualState & state) : 
	coord(state.coord), 
	textures(state.textures),
	anim(state.anim) {}

sf::Vector2f IndividualState::directionToward(const sf::Vector2f &point) const {
	sf::Vector2f direction = sf::Vector2f(point.x - coord.x, point.y - coord.y);
	float length = std::hypot(direction.x, direction.y);
	if (length != 0)
		return direction / length;
	return direction;
}


float IndividualState::distanceToPoint(const sf::Vector2f &point) const {
	return std::hypot((point.x - coord.x),(point.y - coord.y));
}


float IndividualState::distanceToIndividual(const IndividualState& individual) const {
	return std::hypot((individual.coord.x - coord.x), (individual.coord.y - coord.y));
}

bool IndividualState:: operator <(const IndividualState& individual) {
	return myStrength() < individual.myStrength();
}


void IndividualState::applyCollision(const sf::Vector2f& compare_coord, float min) {

	float dist = distanceToPoint(compare_coord);
	if (dist < min) {
		sf::Vector2f direction = directionToward(compare_coord);
		float direction_x = coord.x - (min - dist)*direction.x;
		float direction_y = coord.y - (min - dist)*direction.y;
		coord = sf::Vector2f(direction_x, direction_y);

		sf::Vector2f new_coord = coord;
		if (compare_coord.x < 0)
			new_coord.x = 0;
		if (compare_coord.y < 0)
			new_coord.y = 0;

		float outside_mvt_x = compare_coord.x - WINDOW_WIDTH;
		float outside_mvt_y = compare_coord.y - WINDOW_HEIGHT;

		if (outside_mvt_x > 0)
			new_coord.x -= outside_mvt_x;
		if (outside_mvt_y > 0)
			new_coord.y -= outside_mvt_y;

		coord = new_coord;
	}
}

void IndividualState::applyCollisionElements(std::vector<std::unique_ptr<Element>>& elements) {
	for (const auto & element : elements) {
		for (auto coord : element->getCoords()) {
			applyCollision(coord, DIST_TO_ELEMENTS);
		}
	}

}


void IndividualState::updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>> drawables) {

	sf::Sprite* sprite = static_cast<sf::Sprite*>(drawables[0].first.get());
	sprite->setPosition(coord.x, coord.y);
	sf::Vector2f direction(coord.x - old_coord.x, coord.y - old_coord.x);
	float rotation = calculateAngle(direction);
	if (direction.y < 0) {
		rotation = 360.0f - rotation;
	}
	sf::IntRect rect = sprite->getTextureRect();
	setSpriteDirection(rotation, rect);
	sprite->setTextureRect(rect);
}


void IndividualState::setSpriteDirection(float rotation, sf::IntRect& rect) {
	if ((rotation >= 0 && rotation < 22.5)) {
		rect.top = Right * rect.height;
	}
	else if (rotation >= 22.5 && rotation < 67.5) {
		rect.top = DownRight * rect.height;
		if (rotation > 45.0f) {
			rotation = rotation - 45.0f;
		}
		else {
			rotation = 360.0f - (45.0f - rotation);
		}
	}
	else if (rotation >= 67.5 && rotation < 112.5) {
		rect.top = Down * rect.height;
		if (rotation > 90.0f) {
			rotation = rotation - 90.0f;
		}
		else {
			rotation = 360.0f - (90.0f - rotation);
		}
	}
	else if (rotation >= 112.5 && rotation < 157.5) {
		rect.top = DownLeft * rect.height;
		if (rotation > 135.0f) {
			rotation = rotation - 135.0f;
		}
		else {
			rotation = 360.0f - (135.0f - rotation);
		}
	}
	else if (rotation >= 157.5 && rotation < 202.5) {
		rect.top = Left * rect.height;
		if (rotation > 185.0f) {
			rotation = rotation - 185.0f;
		}
		else {
			rotation = 360.0f - (185.0f - rotation);
		}
	}
	else if (rotation >= 202.5 && rotation < 247.5) {
		rect.top = TopLeft * rect.height;
		if (rotation > 225.0f) {
			rotation = rotation - 225.0f;
		}
		else {
			rotation = 360.0f - (225.0f - rotation);
		}
	}
	else if (rotation >= 247.5 && rotation < 292.5) {
		rect.top = Top * rect.height;
		if (rotation > 270.0f) {
			rotation = rotation - 270.0f;
		}
		else {
			rotation = 360.0f - (270.0f - rotation);
		}
	}
	else if (rotation >= 292.5 && rotation <= 337.5) {
		rect.top = TopRight * rect.height;
		if (rotation > 315.0f) {
			rotation = rotation - 315.0f;
		}
		else {
			rotation = 360.0f - (315.0f - rotation);
		}
	}
	else if (rotation >= 337.5 && rotation <= 360) {
		rect.top = Right * rect.height;
		rotation = 360 - rotation;
	}

	//	sprite.setRotation(rotation);
}


