#include "Strong.h"
#include "OtherFunctions.h"

Strong::Strong() {
	sprite.setFillColor(sf::Color(randomint(255), randomint(255), randomint(255)));
	sprite.setRadius(CIRCLE_S_RADIUS);
}

Strong::Strong(const IndividualState & state) : 
	IndividualState(state),
	subordinates() {

	sprite.setFillColor(sf::Color(randomint(255), randomint(255), randomint(255)));
	sprite.setRadius(CIRCLE_S_RADIUS);
}

std::unique_ptr<IndividualState> Strong::changeState(Individual* new_leader) {
	std::unique_ptr<Weak> weak = std::make_unique<Weak>(*this);
	weak->changeColor(new_leader->getState()->getSprite()->getFillColor());
	weak->setLeader(new_leader);
	return move(weak);
}

void Strong::action() {
	std::cout << "I am strong.\n";
}

void Strong::addSubordinate(std::unique_ptr<Individual>& subordinate) {
	subordinate.get()->changeColor(sprite.getFillColor());
	subordinates.push_back(move(subordinate));
}

std::vector<std::unique_ptr<Individual>>& Strong::getSubordinates() { return subordinates; }

void Strong::updatePositionChaos() {
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

	for (int i = 0; i < subordinates.size();i++) {
		subordinates[i]->updatePosition();
		subordinates[i]->applyCollision(coord);
		for (int j = 0; j < i; j++) {
			subordinates[i]->applyCollision(subordinates[j]->getCoord());
		}
		for (int j = i+1; j < subordinates.size(); j++) {
			subordinates[i]->applyCollision(subordinates[j]->getCoord());
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

void Strong::insertSubordinate(const int &index, std::unique_ptr<Individual> &new_sub) {
	if (subordinates.size() == index) {
		subordinates.push_back(std::move(new_sub));
		return;
	}
	subordinates.resize(1+subordinates.size());

	for (int i = subordinates.size() - 2; i >= index; i--) {
		subordinates[i + 1] = std::move(subordinates[i]);
	}
	subordinates[index] = std::move(new_sub);
	subordinates[index]->changeColor(sprite.getFillColor());
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
	me->changeColor(new_leader->getState()->getSprite()->getFillColor());
	moveIndividuals(leaders, strong->getSubordinates(), my_position, new_position);
	for (int i = subordinates.size() - 1; i >= 0; i--) {
		subordinates[i]->findMyGroupNew(leaders,i);
	}
	me->changeState(changeState(new_leader));

}


