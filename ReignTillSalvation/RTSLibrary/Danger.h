#pragma once

#include <SFML/Graphics.hpp>

#include "Value.h"
#include "OtherFunctions.h"
#include "Individual.h"
#include "Strong.h"

class Danger
{
public:
	// countdownAppearance and duration are times in seconds
	Danger(float set_countdownAppearance, float set_duration);

	virtual sf::Shape &getShape() = 0;
	virtual void affectZone(std::vector<std::unique_ptr<Individual>>&) = 0;
	
	// returns true if countdown is finished
	bool update();

private:
	sf::Time timeSinceApparition;
	sf::Time countdownAppearance;
	sf::Time duration;

	virtual void updateOpacity(float opacity) = 0;
};