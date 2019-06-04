#include "Map.h"
#include "Strong.h"
#include "Weak.h"

void Map::createIndividual(sf::Vector2f coord) {
	leaders.push_back(std::make_unique<Individual>(std::make_unique<Strong>(),coord));
}

void Map::createElement(std::string name, int range) {
	elements.push_back(std::make_unique<Element>(name, range));
}

void Map::addElementInMap(std::string name, sf::Vector2f coord) {
	for (const auto & element : elements) {
		if (name.compare(element.get()->getName()) == 0) {
			element.get()->addCoord(coord);
			return;
		}
	}
	createElement(name,DEFAULT_RANGE);
	elements.back()->addCoord(coord);
}

void Map::updatePositions() {
	//for (std::unique_ptr<Individual> &leader : leaders)
		//leader.updatePosition();
}

void Map::updateGroup() {
	Strong* strong;
	std::vector<std::unique_ptr<Individual>>* subordinates;
	int my_position = 0;
	for (auto & leader : leaders) {
		strong = dynamic_cast<Strong*>(leader->getState());
		if (strong == NULL) {
			printf("ERROR: Cannot find subordinates for a Weak Individual.");
			return;
		}
		subordinates = &(strong->getSubordinates());

		for (int i = subordinates->size() - 1; i >= 0;i--) {
			findGroup((*subordinates)[i],i);
		}
	}

	printf("%d\n", leaders.size() - 1);
	for (int i = leaders.size() - 1; i >= 0; i--) {
		findStrongerLeader(leaders[i], i);
	}

}

/*Searching if the individual is in this group using dichotomy, and 
	-return its position if he is.
	-return -1 if the individual is not in the group.
	Approximately effective for 25 or more subordinates*/
int Map::findSubPositionDicho(const Individual& individual, Strong& strong) {
	std::vector<std::unique_ptr<Individual>>& subordinates = strong.getSubordinates();
	//For ascending list, comparing distance to leader.
	float distanceToLead = individual.distanceToIndividual(strong);
	if (distanceToLead < GROUP_LEAD_RANGE) {
		for (int position = 0; position < subordinates.size() ; position++) {
			if (distanceToLead < subordinates[position].get()->distanceToIndividual(strong)) {
				return position;
			}
		}
	}
	int index_left = 0;
	int index_right = subordinates.size() - 1;
	if (subordinates[index_right].get()->distanceToIndividual(strong) + GROUP_SUB_RANGE < individual.distanceToIndividual(strong)) {
		return -1;
	}

	int index_mid = (index_left + index_right) / 2;
	while ((index_right - index_left) > 0) {
		//Looking for the position the individual might be in the vector.
		if (subordinates[index_mid].get()->distanceToIndividual(strong) + GROUP_SUB_RANGE < individual.distanceToIndividual(strong)) {
			index_left = index_mid;
			index_mid = (index_left + index_right) / 2;
		}
		else {
			index_right = index_mid;
			index_mid = (index_left + index_right) / 2;
		}
	}

	//Checking if he is in the list around GROUP_SUB_RANGE from this position.
	//Finding lower limit.
	int index_left_lower = 0;
	int index_right_lower = index_right;
	while ((subordinates[index_right_lower].get()->distanceToIndividual(strong) - subordinates[index_left_lower].get()->distanceToIndividual(strong)) > GROUP_SUB_RANGE) {
		index_left_lower = (index_right_lower + index_left_lower) / 2;
	}
	
	//Finding the upper limit.
	int index_left_upper = index_left;
	int index_right_upper = subordinates.size()-1;
	while ((subordinates[index_right_lower].get()->distanceToIndividual(strong) - subordinates[index_left_lower].get()->distanceToIndividual(strong)) > GROUP_SUB_RANGE) {
		index_right_lower = (index_right_lower + index_left_lower) / 2;
	}
	//Checking if the individual is in the boundaries found.
	for (int position = index_left_lower; position == index_right_lower; position++) {
		if (subordinates[position].get()->distanceToIndividual(individual) < GROUP_SUB_RANGE) {
			return position;
		}
	}
	return -1;

}

/*Searching if the individual is in this group with a linear search, and
-return its position if he is.
-return -1 if the individual is not in the group. */
int Map::findSubPosition(const Individual& individual, Strong& strong) {
	std::vector<std::unique_ptr<Individual>>& subordinates = strong.getSubordinates();
	//For ascending list, comparing distance to leader.
	float distanceToLead = individual.distanceToIndividual(strong);
	if (distanceToLead < GROUP_LEAD_RANGE) {
		for (int position = 0; position < subordinates.size(); position++) {
			if (distanceToLead < subordinates[position].get()->distanceToIndividual(strong)) {
				return position;
			}
		}
	}
	for (int i = 0; i < subordinates.size(); i++) {
		if (subordinates[i].get()->distanceToIndividual(individual) < GROUP_SUB_RANGE) {
			return i;
		}
	}
	return -1;
}

/*Searching if the individual is in this group with a linear search, and
-return its position if he is.
-return -1 if the individual is not in the group. */
bool Map::stillInGroup(int position, Strong& strong) {
	std::vector<std::unique_ptr<Individual>>& subordinates = strong.getSubordinates();
	//For ascending list, comparing distance to leader.
	float distanceToLead = subordinates[position]->distanceToIndividual(strong);
	if (distanceToLead < GROUP_LEAD_RANGE) {
		return true;
	}
	for (int i = position+1; i < subordinates.size(); i++) {
		if (subordinates[i].get()->distanceToIndividual(*subordinates[position]) < GROUP_SUB_RANGE) {
			return true;
		}
	}
	for (int i = 0; i < position; i++) {
		if (subordinates[i].get()->distanceToIndividual(*subordinates[position]) < GROUP_SUB_RANGE) {
			return true;
		}
	}
	return false;
}

void Map::findGroup(std::unique_ptr<Individual>& individual,int my_position) {
	Individual* strongestnew = NULL;
	int temp = -1;

	int index_new_leader = -1;
	int position_in_subordinate = -1;
	Weak* weak = dynamic_cast<Weak*>(individual->getState());
	if (weak == NULL) {
		printf("ERROR: this individual is not weak.");
		return;
	}

	const Individual* leader = weak->getLeader();
	Strong* actual_lead = dynamic_cast<Strong*>(leader->getState());
	int size_strongest = actual_lead->getSubordinates().size();

	Strong* strong_lead;
	for (int i = 0; i < leaders.size(); i++) {
		strong_lead = dynamic_cast<Strong*>(leaders[i]->getState());
		if (size_strongest < strong_lead->getSubordinates().size())
		{
			temp = findSubPosition(*individual, *strong_lead);
			if (temp != -1) {
				index_new_leader = i;
				position_in_subordinate = temp;
			}
		}
	}

	if (index_new_leader != -1) {
		//insert in position_in_subordinate
		strong_lead = dynamic_cast<Strong*>(leaders[index_new_leader]->getState());
		strong_lead->addSubordinate(individual);
		weak->setLeader(leaders[index_new_leader].get());
		actual_lead->eraseSubordinate(my_position);
	}
	else {
		if (!stillInGroup(my_position,*actual_lead)) {
			makeLeader(individual);
			actual_lead->eraseSubordinate(my_position);
		}
	}

}

void Map::findStrongerLeader(std::unique_ptr<Individual>& individual, int position) {
	if (leaders.size() == 1) {
		return;
	}
	int index = position;
	Strong* strong = dynamic_cast<Strong*>(individual->getState());
	int size_strongest = strong->getSubordinates().size();
	if (strong == NULL) {
		printf("ERROR: this individual is not strong.");
		return;
	}

	Strong* strong_lead;
	for (int i = position+1; i < leaders.size(); i++) {
		strong_lead = dynamic_cast<Strong*>(leaders[i]->getState());
		if ((size_strongest <= strong_lead->getSubordinates().size())
			&& (leaders[i].get()->distanceToIndividual(*individual) < GROUP_LEAD_RANGE))
		{
			index = i;
			size_strongest = strong_lead->getSubordinates().size();
		}
	}
	for (int i = 0; i != position; i++) {
		strong_lead = dynamic_cast<Strong*>(leaders[i]->getState());
		if ((size_strongest <= strong_lead->getSubordinates().size())
			&& (leaders[i].get()->distanceToIndividual(*individual) < GROUP_LEAD_RANGE))
		{
			index = i;
			size_strongest = strong_lead->getSubordinates().size();
		}
	}

	if (index != position) {
		makeSubordinate(individual, leaders[index]);
		eraseLeader(position);
	}
}

void Map::makeLeader(std::unique_ptr<Individual>& individual) {
	if (dynamic_cast<Weak*>(individual.get()->getState()) == NULL) {
		printf("ERROR: the individual is already a leader.");
		return;
	}
	individual->changeState();
	leaders.push_back(std::move(individual));
}

void Map::makeSubordinate(std::unique_ptr<Individual>& individual, std::unique_ptr<Individual>& leader) {
	Strong* strong = dynamic_cast<Strong*>(individual.get()->getState());
	if (strong == NULL) {
		printf("ERROR: the individual is already a subordinate.");
		return;
	}
	std::vector<std::unique_ptr<Individual>>& individual_subordinates = strong->getSubordinates();

	Strong* new_leader = dynamic_cast<Strong*>(leader.get()->getState());
	if (new_leader == NULL) {
		printf("ERROR: the new_leader cannot be weak.");
		return;
	}
	Weak* weak;
	for (auto& subordinate : individual_subordinates) {
		weak = dynamic_cast<Weak*>(subordinate.get()->getState());
		weak->setLeader(leader.get());
		new_leader->addSubordinate(subordinate);
	}
	individual->changeState();
	individual->changeColor(new_leader->getSprite()->getFillColor());
	weak = dynamic_cast<Weak*>(individual.get()->getState());
	if (weak == NULL) {
		printf("ERROR: the individual is not weak.");
		return;
	}
	weak->setLeader(leader.get());
	new_leader->addSubordinate(individual);
}

void Map::eraseLeader(int index) {
	leaders.erase(leaders.begin() + index);
}