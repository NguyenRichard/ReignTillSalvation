#include "Danger.h"


Danger::Danger(std::unique_ptr<sftools::Chronometer> &time, float set_countdownAppearance,
	float set_duration, float time_offset, float time_before_next)
{
	timeOfNext = time->getElapsedTime() + sf::seconds(time_before_next);
	apparitionTime = time->getElapsedTime() + sf::seconds(time_offset);
	countdownAppearance = sf::seconds(set_countdownAppearance);
	duration = sf::seconds(set_duration);
}

Danger::Danger(std::unique_ptr<sftools::Chronometer> &time) :
	Danger(time, DEFAULT_COUNTDOWN_DANGER, DEFAULT_DURATION_DANGER,
		MIN_TIME_BEFORE_APPARITION
			+ (float)randomint(MAX_TIME_BEFORE_APPARITION - MIN_TIME_BEFORE_APPARITION),
		MIN_TIME_BEFORE_NEXT
			+ (float)randomint(MAX_TIME_BEFORE_NEXT - MIN_TIME_BEFORE_NEXT)) {}

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

bool Danger::hasBegun(std::unique_ptr<sftools::Chronometer> &time)
{
	return time->getElapsedTime().asSeconds() > apparitionTime.asSeconds();
}

bool Danger::isNextNow(std::unique_ptr<sftools::Chronometer>& time)
{
	return time->getElapsedTime().asSeconds() > timeOfNext.asSeconds();
}