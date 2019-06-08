#include "Danger.h"


Danger::Danger(std::unique_ptr<sftools::Chronometer> &time, float set_countdownAppearance, float set_duration)
{
	apparitionTime = time->getElapsedTime();
	countdownAppearance = sf::seconds(set_countdownAppearance);
	duration = sf::seconds(set_duration);
}

bool Danger::update(std::unique_ptr<sftools::Chronometer> &time)
{
	float opacity = (time->getElapsedTime().asSeconds() - apparitionTime.asSeconds()) / 
		countdownAppearance.asSeconds() * MAX_COUNTDOWN_OPACITY;
	if (opacity > MAX_COUNTDOWN_OPACITY) {
		updateOpacity(DANGER_OPACITY);
		return true;
	}

	updateOpacity(opacity);
	return false;
}

bool Danger::isFinished(std::unique_ptr<sftools::Chronometer> &time)
{
	return time->getElapsedTime().asSeconds() - apparitionTime.asSeconds() >
		countdownAppearance.asSeconds() + duration.asSeconds();
}