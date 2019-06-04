#include "Map.h"
#include "Strong.h"

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
	for (auto & leader : leaders) {
		strong = static_cast<Strong*>(leader->getState());
		subordinates = &strong->getSubordinate();
	}

}

/*Searching if the individual is in this group, and 
	-return its position if he is.
	-return -1 if the individual is not in the group.*/
int Map::findSubPosition(const Individual& individual, Strong& strong) {
	std::vector<std::unique_ptr<Individual>>& subordinates = strong.getSubordinate();
	//For ascending list, comparing distance to leader.
	if (individual.distanceToIndividual(strong) < GROUP_LEAD_RANGE) {
		return 0;
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
	for (int i = index_left_lower; i == index_right_lower; i++) {
		if (subordinates[i].get()->distanceToIndividual(individual) < GROUP_SUB_RANGE) {
			return i;
		}
	}
	return -1;

}

Individual* Map::findLeader(const Individual& individual) {
	Individual* strongestnew = NULL;
	Strong* strong;
	int position;
	for (auto & leader : leaders) {
		strong = static_cast<Strong*>(leader->getState());
		position = findSubPosition(individual, *strong);
		if (position != -1) {
			//Sort leaders or not?
		}
	}

	return strongestnew;
}
