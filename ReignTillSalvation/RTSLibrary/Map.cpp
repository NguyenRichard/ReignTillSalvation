#include "Map.h"


Map::Map() {
	background.setTexture(textureManager.map);
	if (!font.loadFromFile(FONT_PATH)) {
		std::cout << "Impossible to load font for map";
		return;
	}
	individualsCount.setFont(font);
	individualsCount.setCharacterSize(INDIVIDUALS_COUNT_CHARACTER_SIZE);
	individualsCount.setFillColor(INDIVIDUALS_COUNT_FILLCOLOR);
	individualsCount.setString(std::to_string(MAX_INDIVIDUALS) + "/" + std::to_string(MAX_INDIVIDUALS));
}

Individual* Map::createIndividual(sf::Vector2f coord) {
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
		return leaders.back.get();
	}
	else {
		leaders.push_back(std::make_unique<Individual>(std::make_unique<Strong>(&textureManager.individuals.find("darkelement")->second), coord));
		return leaders.back.get();
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
		name, range, color, attractionMessage, repulsionMessage,cancelMessage, &textureManager.elements.find(name)->second
	));
}

Law* Map::createLaw(Element* element, LawType type) {
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
	return laws.back.get();
}

void Map::updatePositions() {
	for (std::unique_ptr<Individual> &leader : leaders)
	{
		leader->updatePosition(elements);
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
}

int Map::totalCountIndividuals() {
	int sum = 0;
	for (const auto & leader : leaders) {
		sum += leader->myStrength()+1;
	}
	return sum;
}

void Map::updateDangers(std::unique_ptr<sftools::Chronometer>& time) {
	if (dangers.empty() || dangers.back()->isNextNow(time)) {
		int nbIndividuals = totalCountIndividuals();
		if (randomint(1) == 0)
			renderables.push_back(std::make_unique<Renderable>(
				addRandomCircleDanger(time, COEFF_TIME_BEFORE_NEXT * (log10(nbIndividuals) + 1.0f)), textureManager));
		else
			renderables.push_back(std::make_unique<Renderable>(
				addRandomLineDanger(time, COEFF_TIME_BEFORE_NEXT * (log10(nbIndividuals) + 1.0f)), textureManager));
	}

	for (int i = dangers.size() - 1; i >= 0; i--) {
		std::unique_ptr<Danger> &danger = dangers[i];
		if (danger->hasBegun(time))
			danger->update(time);
			if (danger->getCountdownStatus()) {
				if (danger->isFinished(time))
					deleteDanger(i);
				else
					danger->affectZone(leaders);
			}
	}
}

void Map::deleteDanger(const int &i) {
	dangers[i]->resetBuffer();
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

CircleDanger* Map::addRandomCircleDanger(std::unique_ptr<sftools::Chronometer> &time, float wait)
{
	std::unique_ptr<CircleDanger> danger = std::make_unique<CircleDanger>(time, wait, &textureManager.dangers.find("explosion")->second,
			&soundManager.sounds.find("explosion")->second);
	CircleDanger* circleDanger = danger.get();
	dangers.push_back(std::move(danger));
	return circleDanger;
}

LineDanger* Map::addRandomLineDanger(std::unique_ptr<sftools::Chronometer> &time, float wait)
{
	std::unique_ptr<LineDanger> danger = std::make_unique<LineDanger>(time, wait, &textureManager.dangers.find("laser")->second,
		&soundManager.sounds.find("laser")->second);
	LineDanger* lineDanger = danger.get();
	dangers.push_back(std::move(danger));
	return lineDanger;
}


void Map::render(sf::RenderWindow& window) {
	window.draw(background);
	individualsCount.setString(std::to_string(totalCountIndividuals()) + "/" + std::to_string(MAX_INDIVIDUALS));

	window.draw(individualsCount);
}
