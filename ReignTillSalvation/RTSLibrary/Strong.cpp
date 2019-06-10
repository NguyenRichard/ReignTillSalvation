#include "Strong.h"
#include "OtherFunctions.h"


Strong::Strong(std::pair<sf::Texture, sf::Texture>* textures) : IndividualState(textures) 
{
	sprite.setPosition(coord.x, coord.y);
	sprite.setTexture(textures->second);
	sprite.setTextureRect(sf::IntRect(anim.x*STRONG_SPRITE_SIZE, anim.y*STRONG_SPRITE_SIZE, STRONG_SPRITE_SIZE, STRONG_SPRITE_SIZE));
	sprite.setOrigin(sf::Vector2f(STRONG_SPRITE_SIZE / 2, STRONG_SPRITE_SIZE / 2));
	sprite.setScale(5, 5);
}

Strong::Strong(const IndividualState & state) : 
	IndividualState(state)
{
	sprite.setPosition(coord.x, coord.y);
	sprite.setTexture(textures->second);
	sprite.setTextureRect(sf::IntRect(anim.x*STRONG_SPRITE_SIZE, anim.y*STRONG_SPRITE_SIZE, STRONG_SPRITE_SIZE, STRONG_SPRITE_SIZE));
	sprite.setOrigin(sf::Vector2f(STRONG_SPRITE_SIZE / 2, STRONG_SPRITE_SIZE / 2));
	sprite.setScale(5, 5);
}

std::unique_ptr<IndividualState> Strong::changeState(Individual* new_leader) {
	std::unique_ptr<Weak> weak = std::make_unique<Weak>(*this);
	weak->getSprite()->setTexture(textures->first);
	weak->setLeader(new_leader);
	return move(weak);
}

void Strong::action() {
	std::cout << "I am strong.\n";
}

std::vector<std::unique_ptr<Individual>>& Strong::getSubordinates() { return subordinates; }

void Strong::updatePositionChaos(std::vector<std::unique_ptr<Element>>& elements) {
	float degree = 0.01 + (1 - 0.01) * randomint(RAND_MAX) / (float) RAND_MAX;
	// between 1 and 10

	degree = -log10(degree); // between 0 and 1
	if (randomint(1) == 0)
		degree = -degree;
	degree *= MAX_TURN;
	float theta = degree / 1800.0f * PI;
	float cs = cos(theta);
	float sn = sin(theta);

	sf::Vector2f direction = -directionToward(old_coord);
	float direction_x = direction.x * cs - direction.y * sn;
	float direction_y = direction.x * sn + direction.y * cs;

	old_coord = coord;

	coord.x += direction_x * DISTANCE_RUN_LEADER;
	coord.y += direction_y * DISTANCE_RUN_LEADER;

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

	applyCollisionElements(elements);

	for (int i = 0; i < subordinates.size();i++) {
		subordinates[i]->updatePosition(elements);
		subordinates[i]->getState()->applyCollision(coord,DIST_BETWEEN_LEADER);
		for (int j = 0; j < i; j++) {
			subordinates[i]->getState()->applyCollision(subordinates[j]->getCoord(),DIST_BETWEEN_SUBORDINATE);
		}
		for (int j = i+1; j < subordinates.size(); j++) {
			subordinates[i]->getState()->applyCollision(subordinates[j]->getCoord(), DIST_BETWEEN_SUBORDINATE);
		}
	}

	std::sort(subordinates.begin(), subordinates.end(), [](const std::unique_ptr<Individual>& a, const std::unique_ptr<Individual>& b)->bool {
		Weak* a_weak = dynamic_cast<Weak*>(a->getState());
		Weak* b_weak = dynamic_cast<Weak*>(b->getState());
		return a->distanceToIndividual(*a_weak->getLeader()) < b->distanceToIndividual(*b_weak->getLeader());
	});
}

void Strong::eraseSubordinate(int index) {
	subordinates.erase(subordinates.begin() + index);
}


/*Searching if the individual is in this group with a linear search, and
-return its position if he is.
-return -1 if the individual is not in the group. */
int Strong::findSubPosition(const IndividualState& individual) {

	//For ascending list, comparing distance to leader.
	float distanceToLead = individual.distanceToIndividual(*this);
	if (distanceToLead < GROUP_LEAD_RANGE) {
		//In this case, the new subordinate is in the list. We just need to find its position.
		for (int position = 0; position < subordinates.size(); position++) {
			if (distanceToLead < subordinates[position]->distanceToIndividual(*this)) {
				return position;
			}
		}
		//If we arrive here, it means that all the other subordinates are farther from the leader.
		return subordinates.size();
	}
	int position = subordinates.size();
	for (int i = subordinates.size()-1; i > 0; i--) {
		if (subordinates[i]->distanceToIndividual(*this) > individual.distanceToIndividual(*this)) {
			position = i;
		}
		if (subordinates[i]->distanceToIndividual(individual) < GROUP_SUB_RANGE 
			&& stillInGroup(i)) {
			return position;
		}
	}
	return -1;
}


/*Searching if the individual is in this group with a linear search, and
-return its position if he is.
-return -1 if the individual is not in the group. */
bool Strong::stillInGroup(int position) {
	std::vector<Individual*> members;
	//For ascending list, comparing distance to leader.
	float distanceToLead = subordinates[position]->distanceToIndividual(*this);
	if (distanceToLead < GROUP_LEAD_RANGE) {
		return true;
	}
	for (int i = 0; i < position; i++) {
		if (subordinates[i]->distanceToIndividual(*this) < GROUP_LEAD_RANGE) {
			members.push_back(subordinates[i].get());
		}
		else {
			for (const auto& member : members) {
				if (member->distanceToIndividual(*subordinates[i]) < GROUP_SUB_RANGE) {
					members.push_back(subordinates[i].get());
					break;
				}
			}
		}
	}
	for (auto& member : members) {
		if (member->distanceToIndividual(*subordinates[position]) < GROUP_SUB_RANGE) {
			return true;
		}
	}

	return false;
}

void Strong::updateMyGroup(Individual* me,std::vector<std::unique_ptr<Individual>>& leaders, int my_position) {

	for (int sub_position = subordinates.size() - 1; sub_position >= 0; sub_position--) {
		subordinates[sub_position]->updateMyGroup(leaders, sub_position);
	}
	findGroup(me,leaders, my_position);
}

void Strong::findGroup(Individual* me,std::vector<std::unique_ptr<Individual>>& leaders, int my_position) {
	if (leaders.size() == 1) {
		return;
	}

	int index_strongest = my_position;
	int strongest_strength = myStrength();
	for (int i = my_position + 1; i < leaders.size(); i++) {
		if ((strongest_strength <= leaders[i]->myStrength())
			&& (leaders[i]->distanceToIndividual(*this) < GROUP_LEAD_RANGE))
		{
			index_strongest = i;
			strongest_strength = leaders[i]->myStrength();
		}
	}
	for (int i = 0; i != my_position; i++) {
		if ((strongest_strength <= leaders[i]->myStrength())
			&& (leaders[i]->distanceToIndividual(*this) < GROUP_LEAD_RANGE))
		{
			index_strongest = i;
			strongest_strength = leaders[i]->myStrength();
		}
	}

	if (index_strongest != my_position) {
		makeSubordinate(me,leaders, leaders[index_strongest].get(), my_position);
	}

}

void Strong::makeSubordinate(Individual* me,std::vector<std::unique_ptr<Individual>>& leaders, Individual* new_leader, int my_position) {

	Strong* strong = static_cast<Strong*>(new_leader->getState());
	int new_position = new_leader->getState()->findSubPosition(*this);
	moveIndividuals(leaders, strong->getSubordinates(), my_position, new_position);
	for (int i = subordinates.size() - 1; i >= 0; i--) {
		subordinates[i]->findMyGroupNew(leaders,i);
	}
	me->changeState(changeState(new_leader));
}

void Strong::render_and_update(sf::RenderWindow& window) {

	sprite.setPosition(coord.x, coord.y);
	sf::Vector2f direction(coord.x - old_coord.x, coord.y - old_coord.y);
	float rotation = calculateAngle(direction);
	if (direction.y < 0) {
		rotation = 360.0f - rotation;
	}
	setSpriteDirection(rotation);

	//incrementAnim();
	sprite.setTextureRect(sf::IntRect(anim.x*STRONG_SPRITE_SIZE, anim.y*STRONG_SPRITE_SIZE,STRONG_SPRITE_SIZE,STRONG_SPRITE_SIZE));


	window.draw(sprite);
	for (const auto & subordinate : subordinates) {
		subordinate->render_and_update(window);
	}
}

void Strong::render(sf::RenderWindow& window) {
	window.draw(sprite);
	for (const auto & subordinate : subordinates) {
		subordinate->render(window);
	}
}

void Strong::incrementAnim() {
	anim.x++;
	if (anim.x*STRONG_SPRITE_SIZE >= textures->second.getSize().x) {
		anim.x = 0;
	}
	for (const auto & subordinate : subordinates) {
		subordinate->getState()->incrementAnim();
	}
}

void Strong::setSpriteDirection(float rotation) {
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
	else if(rotation >= 337.5 && rotation <= 360){
		anim.y = Right;
		rotation = 360-rotation;
	}

	sprite.setRotation(rotation);
}