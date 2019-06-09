#include "Map.h"


Map::Map() {
	background.setTexture(textureManager.map);
}

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
				std::make_unique<Strong>(&textureManager.individuals.find(liked->getName())->second), coord, liked, disliked
				));
	}
	else {
		leaders.push_back(std::make_unique<Individual>(std::make_unique<Strong>(&textureManager.individuals.find("darkelement")), coord));
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
		name, range, color, attractionMessage, repulsionMessage,cancelMessage, &textureManager.elements.find(name)
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

void Map::update(std::unique_ptr<sftools::Chronometer>& time) {
	updatePositions();
	updateGroup();
	updateLaws();
	updateDangers(time);
	updateAnim(time);
}

int Map::individualsNumber() {
	int sum = 0;
	for (const auto & leader : leaders) {
		sum += leader->myStrength()+1;
	}
	return sum;
}

void Map::updateDangers(std::unique_ptr<sftools::Chronometer>& time) {
	if (dangers.empty() || dangers.back()->isNextNow(time))
		addRandomDanger(time);

	for (int i = dangers.size() - 1; i >= 0; i--) {
		std::unique_ptr<Danger> &danger = dangers[i];
		if (danger->hasBegun(time))
			if (danger->update(time)) {
				if (danger->isFinished(time))
					deleteDanger(i);
				else
					danger->affectZone(leaders);
			}
	}
}

void Map::deleteDanger(const int &i) {
	dangers.erase(dangers.begin() + i);
}

void Map::addDangerInMap(std::unique_ptr<sftools::Chronometer> &time,
		std::string shape, sf::Vector2f coord) {
	if (shape == "circle")
		dangers.push_back(std::make_unique<CircleDanger>(time,
			DEFAULT_COUNTDOWN_DANGER, DEFAULT_DURATION_DANGER, coord));

	if (shape == "line")
		dangers.push_back(std::make_unique<LineDanger>(time,
			DEFAULT_COUNTDOWN_DANGER, DEFAULT_DURATION_DANGER, coord));
}

void Map::addRandomDanger(std::unique_ptr<sftools::Chronometer> &time)
{
	if (randomint(1) == 0)
	{
		dangers.push_back(std::make_unique<CircleDanger>(time));
	}
	else
	{
		dangers.push_back(std::make_unique<LineDanger>(time));
	}
}

void Map::updateAnim(std::unique_ptr<sftools::Chronometer>& time)
{
	if (time->getElapsedTime().asMilliseconds() - last_anim_update.asMilliseconds() > MS_PER_ANIM) {
		for (auto &leader : leaders)
			leader->getState()->incrementAnim();
		last_anim_update = time->getElapsedTime();
	}
}