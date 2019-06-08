#pragma once

#include <SFML/Graphics.hpp>
#include "Chronometer.hpp"

#include "Value.h"
#include "OtherFunctions.h"
#include "Individual.h"
#include "Strong.h"

#define MAX_COUNTDOWN_OPACITY			80.0f
#define DANGER_OPACITY					150.0f

class Danger
{
public:
	// countdownAppearance and duration are times in seconds
	Danger(std::unique_ptr<sftools::Chronometer>&, float set_countdownAppearance,
		float set_duration, float time_offset, float time_before_next);
	Danger(std::unique_ptr<sftools::Chronometer>&);

	virtual sf::Shape &getShape() = 0;
	virtual void affectZone(std::vector<std::unique_ptr<Individual>>&) = 0;
	
	// returns true if countdown is finished
	bool update(std::unique_ptr<sftools::Chronometer>&);
	bool isFinished(std::unique_ptr<sftools::Chronometer>&);
	bool hasBegun(std::unique_ptr<sftools::Chronometer>&);
	bool isNextNow(std::unique_ptr<sftools::Chronometer>&);

private:
	sf::Time timeOfNext;
	sf::Time apparitionTime;
	sf::Time countdownAppearance;
	sf::Time duration;

	virtual void updateOpacity(float opacity) = 0;
};