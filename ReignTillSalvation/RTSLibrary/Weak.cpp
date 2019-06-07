#include "Weak.h"

Weak::Weak()
{
	sprite.setRadius(CIRCLE_W_RADIUS);
};

Weak::Weak(const IndividualState & state) : IndividualState(state) {
	sprite.setRadius(CIRCLE_W_RADIUS);
}

std::unique_ptr<IndividualState> Weak::changeState() {
	std::unique_ptr<Strong> strong = std::make_unique<Strong>(*this);
	strong->changeColor(sf::Color(randomint(255), randomint(255), randomint(255)));
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
	me->changeColor(new_leader->getState()->getSprite()->getFillColor());
	moveIndividuals(subordinates, strong->getSubordinates(), my_position, new_position);

}


