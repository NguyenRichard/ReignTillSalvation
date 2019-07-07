#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Chronometer.hpp"
#include "SoundManager.h"

#include "Value.h"
#include "OtherFunctions.h"
#include "Individual.h"
#include "Strong.h"
#include "ObjectLogic.h"

#define MAX_COUNTDOWN_OPACITY			80.0f
#define DANGER_OPACITY					150.0f

class Danger : public ObjectLogic
{
public:
	// countdownAppearance and duration are times in seconds
	Danger(std::unique_ptr<sftools::Chronometer>&, float set_countdownAppearance,
		float set_duration, float time_offset, float time_before_next);
	Danger(std::unique_ptr<sftools::Chronometer>&, float wait);

	virtual sf::Shape &getShape() = 0;
	virtual void affectZone(std::vector<std::unique_ptr<Individual>>&) = 0;
	virtual void render(sf::RenderWindow&) = 0;
	
	// returns true if countdown is finished
	void update(std::unique_ptr<sftools::Chronometer>&);
	bool isFinished(std::unique_ptr<sftools::Chronometer>&);
	bool hasBegun(std::unique_ptr<sftools::Chronometer>&);
	bool isNextNow(std::unique_ptr<sftools::Chronometer>&);
	bool getCountdownStatus() { return countdownFinished; }

	virtual void resetBuffer() = 0;

private:
	sf::Time timeOfNext;
	sf::Time apparitionTime;
	sf::Time countdownAppearance;
	sf::Time duration;

	virtual void updateOpacity(float opacity) = 0;
	void updateDrawables(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>>&) override = 0;

protected:
	bool firstRenderBeenDone;
	bool countdownFinished;
	float opacity;
};