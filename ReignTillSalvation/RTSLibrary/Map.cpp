#include "Map.h"

void Map::createIndividual(sf::Vector2f coord) {
	int nb_elements = elements.size();
	if (nb_elements > 0) {
		int rdm1 = randomint(nb_elements - 1);
		Element* liked = elements[rdm1].get();
		int rdm2 = randomint(nb_elements - 1);
		if (nb_elements > 1)
			while (rdm2 == rdm1)
				rdm2 = randomint(nb_elements - 1);
		Element* disliked = elements[rdm2].get();
		leaders.push_back(
			std::make_unique<Individual>(
				std::make_unique<Strong>(), coord, liked, disliked
				));
	}
	else {
		leaders.push_back(std::make_unique<Individual>(std::make_unique<Strong>(), coord));
	}
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
	std::string attractionMessage, std::string repulsionMessage,std::string cancelMessage) {
	elements.push_back(std::make_unique<Element>(
		name, range, color, attractionMessage, repulsionMessage,cancelMessage
	));
}

void Map::createLaw(Element* element, LawType type) {
	for (int i = laws.size()-1; i >= 0; i--) {
		if (laws[i]->getElement() == element) {
			laws.erase(laws.begin() + i);
		}
	}
	Strong* strong;
	laws.push_back(std::make_unique<Law>(element, type));
	for (auto & leader : leaders) {
		strong = dynamic_cast<Strong*>(leader->getState());
		leader->addElement(element);
		for (auto & subordinate : strong->getSubordinates()) {
			subordinate->addElement(element);
		}
	}
}

void Map::updatePositions() {
	for (std::unique_ptr<Individual> &leader : leaders)
	{
		leader->updatePosition();
		leader->applyCollisionElements();
	}
}

void Map::updateGroup() {
	int leaders_size = leaders.size();
	for (int i = leaders_size-1; i >= 0; i--) {
		leaders[i]->updateMyGroup(leaders,i);
	}
}

void Map::updateLaws() {
	Strong* strong;
	for (int i = laws.size() - 1; i >= 0; i--) {
		if (laws[i]->done()) {
			for (auto & leader : leaders) {
				strong = dynamic_cast<Strong*>(leader->getState());
				leader->deleteElement(laws[i]->getElement());
				for (auto & subordinate : strong->getSubordinates()) {
					subordinate->deleteElement(laws[i]->getElement());
				}
			}
			laws.erase(laws.begin() + i);
		}
		else {
			laws[i]->updateElement();
		}
	}
}

void Map::update() {
	updatePositions();
	updateGroup();
	updateLaws();
	updateDangers();
}

int Map::individualsNumber() {
	int sum = 0;
	for (const auto & leader : leaders) {
		sum += leader->myStrength()+1;
	}
	return sum;
}

void Map::updateDangers() {
	for (auto &danger : dangers) {
		if (danger->update())
			danger->affectZone(leaders);
	}
}