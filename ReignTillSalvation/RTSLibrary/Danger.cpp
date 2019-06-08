#include "Danger.h"

Danger::Danger(float set_countdownAppearance, float set_duration)
{
	countdownAppearance = sf::seconds(set_countdownAppearance);
	duration = sf::seconds(set_duration);
}

bool Danger::update()
{
	float opacity = timeSinceApparition.asSeconds() / 
		countdownAppearance.asSeconds() * MAX_COUNTDOWN_OPACITY;
	if (opacity > MAX_COUNTDOWN_OPACITY) {
		updateOpacity(DANGER_OPACITY);
		return true;
	}

	updateOpacity(opacity);
	return false;
}