#include "Weak.h"

Weak::Weak(const IndividualState & state) : 
	IndividualState(state) 
{
	sprite.setTexture(textures->first);
	sprite.setTextureRect(sf::IntRect(anim.x*WEAK_SPRITE_SIZE, anim.y*WEAK_SPRITE_SIZE, WEAK_SPRITE_SIZE, WEAK_SPRITE_SIZE));
	sprite.setOrigin(sf::Vector2f(WEAK_SPRITE_SIZE / 2, WEAK_SPRITE_SIZE / 2));
	sprite.setScale(3, 3);
}

std::unique_ptr<IndividualState> Weak::changeState() {
	std::unique_ptr<Strong> strong = std::make_unique<Strong>(*this);
	strong->getSprite()->setTexture(textures->second);
	return move(strong);
}

void Weak::action() {
	std::cout << "I am weak\n";
}

void Weak::updatePositionChaos() {
	sf::Vector2f direction = directionToward(leader->getCoord());
	old_coord = coord;

	coord += sf::Vector2f(DISTANCE_RUN_SUBORDINATE * direction.x,
		DISTANCE_RUN_SUBORDINATE * direction.y);

	if (coord.x < 0)
		coord.x = 0;
	if (coord.y < 0)
		coord.y = 0;

	float outside_mvt_x = coord.x - WINDOW_WIDTH;
	float outside_mvt_y = coord.y - WINDOW_HEIGHT;

	if (outside_mvt_x > 0)
		coord.x -= outside_mvt_x;
	if (outside_mvt_y > 0)
		coord.y -= outside_mvt_y;
}

void Weak::setLeader(Individual* individual) {
	leader = individual;
}

void Weak::updateMyGroup(Individual* me,std::vector<std::unique_ptr<Individual>>& leaders,int my_position) {

	findGroup(me, leaders, my_position);
}

void Weak::findGroup(Individual* me,std::vector<std::unique_ptr<Individual>>& leaders, int my_position) {

	Individual* new_leader = NULL;
	int temp = -1;

	int index_new_leader = -1;
	int position_in_subordinate = -1;
	int strongest_strength = leader->myStrength();
	for (int i = 0; i < leaders.size(); i++) {
		if (strongest_strength < leaders[i]->myStrength())
		{
			temp = leaders[i]->getState()->findSubPosition(*this);
			if (temp != -1) {
				index_new_leader = i;
				position_in_subordinate = temp;
				strongest_strength = leaders[i]->myStrength();
			}
		}
	}
	Strong* strong = static_cast<Strong*>(leader->getState());
	if (index_new_leader != -1) {
		makeSubordinate(me,strong->getSubordinates(), leaders[index_new_leader], my_position);
	}
	else {
		if (!strong->stillInGroup(my_position)) {
			moveIndividuals(strong->getSubordinates(), leaders, my_position, leaders.size());
			me->changeState(changeState());
		}
	}
}

void Weak::findGroupNew(Individual* me, std::vector<std::unique_ptr<Individual>>& leaders, int my_position) {
	Individual* new_leader = NULL;
	int temp = -1;

	int index_new_leader = -1;
	int position_in_subordinate = -1;
	int strongest_strength = 1;
	for (int i = 0; i < leaders.size(); i++) {
		if (strongest_strength < leaders[i]->myStrength())
		{
			temp = leaders[i]->getState()->findSubPosition(*this);
			if (temp != -1) {
				index_new_leader = i;
				position_in_subordinate = temp;
				strongest_strength = leaders[i]->myStrength();
			}
		}
	}
	Strong* strong = static_cast<Strong*>(leader->getState());
	if (index_new_leader != -1) {
		makeSubordinate(me, strong->getSubordinates(), leaders[index_new_leader], my_position);
	}
	else {
		moveIndividuals(strong->getSubordinates(), leaders, my_position, leaders.size());
		me->changeState(changeState());

	}

}

void Weak::makeSubordinate(Individual* me,std::vector<std::unique_ptr<Individual>>& subordinates, std::unique_ptr<Individual>& new_leader,int my_position) {
	//Only works if the weak can be part of the group otherwise new_position will be equal to -1.
	//Careful MoveIndividuals erase the content of the subordinates vector. So if you loop on subordinates, the index might change.

	Strong* strong = static_cast<Strong*>(new_leader->getState());
	int new_position = new_leader->getState()->findSubPosition(*this);
	setLeader(new_leader.get());
	moveIndividuals(subordinates, strong->getSubordinates(), my_position, new_position);

}

void Weak::render_and_update(sf::RenderWindow& window) {
	sprite.setPosition(coord.x, coord.y);
	
	sf::Vector2f direction(coord.x - old_coord.x, coord.y - old_coord.y);
	float rotation = calculateAngle(direction);
	if (direction.y < 0) {
		rotation = 360.0f-rotation;
	}
	setSpriteDirection(rotation);

	//incrementAnim();

	sprite.setTextureRect(sf::IntRect(anim.x*WEAK_SPRITE_SIZE, anim.y*WEAK_SPRITE_SIZE,WEAK_SPRITE_SIZE,WEAK_SPRITE_SIZE));

	window.draw(sprite);
}

void Weak::render(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Weak::incrementAnim(){
	anim.x++;
	if (anim.x*WEAK_SPRITE_SIZE >= textures->first.getSize().x) {
		anim.x = 0;
	}
}

void Weak::setSpriteDirection(float rotation) {
	if ((rotation >= 0 && rotation < 22.5)) {
		anim.y = Right;
	}
	else if (rotation >= 22.5 && rotation < 67.5) {
		anim.y = DownRight;
		if (rotation > 45.0f) {
			rotation = rotation - 45.0f;
		}
		else {
			rotation = 360.0f - (45.0f - rotation);
		}
	}
	else if (rotation >= 67.5 && rotation < 112.5) {
		anim.y = Down;
		if (rotation > 90.0f) {
			rotation = rotation - 90.0f;
		}
		else {
			rotation = 360.0f - (90.0f - rotation);
		}
	}
	else if (rotation >= 112.5 && rotation < 157.5) {
		anim.y = DownLeft;
		if (rotation > 135.0f) {
			rotation = rotation - 135.0f;
		}
		else {
			rotation = 360.0f - (135.0f - rotation);
		}
	}
	else if (rotation >= 157.5 && rotation < 202.5) {
		anim.y = Left;
		if (rotation > 185.0f) {
			rotation = rotation - 185.0f;
		}
		else {
			rotation = 360.0f - (185.0f - rotation);
		}
	}
	else if (rotation >= 202.5 && rotation < 247.5) {
		anim.y = TopLeft;
		if (rotation > 225.0f) {
			rotation = rotation - 225.0f;
		}
		else {
			rotation = 360.0f - (225.0f - rotation);
		}
	}
	else if (rotation >= 247.5 && rotation < 292.5) {
		anim.y = Top;
		if (rotation > 270.0f) {
			rotation = rotation - 270.0f;
		}
		else {
			rotation = 360.0f - (270.0f - rotation);
		}
	}
	else if (rotation >= 292.5 && rotation <= 337.5) {
		anim.y = TopRight;
		if (rotation > 315.0f) {
			rotation = rotation - 315.0f;
		}
		else {
			rotation = 360.0f - (315.0f - rotation);
		}
	}
	else if (rotation >= 337.5 && rotation <= 360) {
		anim.y = Right;
		rotation = 360 - rotation;
	}

	sprite.setRotation(rotation);
}