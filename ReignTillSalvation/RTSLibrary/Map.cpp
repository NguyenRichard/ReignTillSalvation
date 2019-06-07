#include "Map.h"

void Map::createIndividual(sf::Vector2f coord) {
	leaders.push_back(std::make_unique<Individual>(std::make_unique<Strong>(),coord));
}

void Map::createElement(std::string name, float range) {
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

void Map::createElement(std::string name, float range, sf::Color color,
	std::string attractionMessage, std::string repulsionMessage) {
	elements.push_back(std::make_unique<Element>(
		name, range, color, attractionMessage, repulsionMessage
	));
}

void Map::updatePositions() {
	for (std::unique_ptr<Individual> &leader : leaders)
		leader->updatePosition();
}

void Map::updateGroup() {
	int leaders_size = leaders.size();
	for (int i = leaders_size-1; i >= 0; i--) {
		leaders[i]->updateMyGroup(leaders,i);
	}
}

/*
void Map::updateGroup() {
	Strong* strong;
	std::vector<std::unique_ptr<Individual>>* subordinates;
	int my_position = 0;
	int leaders_size = leaders.size();
	for (int i = 0; i < leaders_size; i++) {
		strong = dynamic_cast<Strong*>(leaders[i]->getState());
		if (strong == NULL) {
			printf("ERROR: Cannot find subordinates for a Weak Individual.");
			return;
		}
		subordinates = &(strong->getSubordinates());

		for (int i = subordinates->size() - 1; i >= 0;i--) {
			findGroup((*subordinates)[i],i);
		}
	}

	for (int i = leaders.size() - 1; i >= 0; i--) {
		findStrongerLeader(leaders[i], i);
	}

}*/

/*

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
			temp = strong_lead->findSubPosition(*individual);
			if (temp != -1) {
				index_new_leader = i;
				position_in_subordinate = temp;
			}
		}
	}

	if (index_new_leader != -1) {
		strong_lead = dynamic_cast<Strong*>(leaders[index_new_leader]->getState());
		strong_lead->insertSubordinate(position_in_subordinate,individual);
		weak->setLeader(leaders[index_new_leader].get());
		actual_lead->eraseSubordinate(my_position);
	}
	else {
		if (!actual_lead->stillInGroup(my_position)) {
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
			&& (leaders[i]->distanceToIndividual(*individual) < GROUP_LEAD_RANGE))
		{
			index = i;
			size_strongest = strong_lead->getSubordinates().size();
		}
	}
	for (int i = 0; i != position; i++) {
		strong_lead = dynamic_cast<Strong*>(leaders[i]->getState());
		if ((size_strongest <= strong_lead->getSubordinates().size())
			&& (leaders[i]->distanceToIndividual(*individual) < GROUP_LEAD_RANGE))
		{
			index = i;
			size_strongest = strong_lead->getSubordinates().size();
		}
	}

	if (index != position) {
		makeSubordinate(individual, position, leaders[index]);
	}
}

void Map::makeLeader(std::unique_ptr<Individual>& individual) {
	if (dynamic_cast<Weak*>(individual->getState()) == NULL) {
		printf("ERROR: the individual is already a leader.");
		return;
	}
	individual->changeState();
	leaders.push_back(std::move(individual));
}

void Map::makeSubordinate(std::unique_ptr<Individual>& individual, int position,
		std::unique_ptr<Individual>& leader	) 
{
	Strong* strong_individual = dynamic_cast<Strong*>(individual->getState());
	if (strong_individual == NULL) {
		printf("ERROR: the individual is already a subordinate.");
		return;
	}
	Strong* new_leader = dynamic_cast<Strong*>(leader->getState());
	if (new_leader == NULL) {
		printf("ERROR: the new_leader cannot be weak.");
		return;
	}

	std::vector<std::unique_ptr<Individual>>& individual_subordinates = strong_individual->getSubordinates();

	Weak* weak;
	int new_position = -1;
	int my_position = 0;
	for (auto& subordinate : individual_subordinates) {
		findGroup(subordinate,my_position);
		my_position++;
	}
	individual->changeState();
	individual->changeColor(new_leader->getSprite()->getFillColor());
	new_position = new_leader->findSubPosition(*individual);
	weak = dynamic_cast<Weak*>(individual->getState());
	weak->setLeader(leader.get());
	new_leader->insertSubordinate(new_position,individual);
	eraseLeader(position);
}

void Map::eraseLeader(int index) {
	leaders.erase(leaders.begin() + index);
}

*/