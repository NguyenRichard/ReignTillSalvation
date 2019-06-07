#include "Danger.h"

Danger::Danger(float set_countdownAppearance, float set_duration)
{
	countdownAppearance = sf::seconds(set_countdownAppearance);
	duration = sf::seconds(set_duration);
}

bool Danger::update()
{
	float opacity = timeSinceApparition.asSeconds() / countdownAppearance.asSeconds() * 255.0f;
	if (opacity > 255.0f)
		return true;
	
	updateOpacity(opacity);
	return false;
}