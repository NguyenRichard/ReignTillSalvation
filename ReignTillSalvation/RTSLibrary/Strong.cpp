#include "Strong.h"
#include "Weak.h"
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

std::unique_ptr<IndividualState> Strong::changeState() {
	return std::make_unique<Weak>(*this);
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
	srand(time(0));
	float degree = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 9)) + 1;
	// between 1 and 10

	degree = log10(degree); // between 0 and 1
	degree *= MAX_TURN;

	sf::Vector2f direction = -directionToward(old_coord);
	float theta = degree / 180 * PI;
	float cs = cos(theta);
	float sn = sin(theta);

	float new_x = coord.x * cs - coord.y * sn;
	float new_y = coord.x * sn + coord.y * cs;

	old_coord = coord;

	coord.x = new_x;
	coord.y = new_y;
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
	subordinates[index].get()->changeColor(sprite.getFillColor());
}

/*Searching if the individual is in this group with a linear search, and
-return its position if he is.
-return -1 if the individual is not in the group. */
int Strong::findSubPosition(const Individual& individual) {

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
	for (int position = 0; position < subordinates.size(); position++) {
		if (subordinates[position]->distanceToIndividual(individual) < GROUP_SUB_RANGE) {
			if (subordinates[position]->distanceToIndividual(*this) < individual.distanceToIndividual(*this)) {
				return position+1;
			}
			else {
				return position;
			}
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