#include "Danger.h"


Danger::Danger(std::unique_ptr<sftools::Chronometer> &time, float set_countdownAppearance,
	float set_duration, float time_offset, float time_before_next)
{
	timeOfNext = time->getElapsedTime() + sf::seconds(time_before_next);
	apparitionTime = time->getElapsedTime() + sf::seconds(time_offset);
	countdownAppearance = sf::seconds(set_countdownAppearance);
	duration = sf::seconds(set_duration);
	countdownFinished = false;
	firstRenderBeenDone = false;
}

Danger::Danger(std::unique_ptr<sftools::Chronometer> &time, float wait) :
	Danger(
		time,
		DEFAULT_COUNTDOWN_DANGER,
		DEFAULT_DURATION_DANGER,
		MIN_TIME_BEFORE_APPARITION
			+ (float)randomint(MAX_TIME_BEFORE_APPARITION - MIN_TIME_BEFORE_APPARITION),
		wait)  {}

void Danger::update(std::unique_ptr<sftools::Chronometer> &time)
{
	opacity = (time->getElapsedTime().asSeconds() - apparitionTime.asSeconds()) / 
		countdownAppearance.asSeconds() * MAX_COUNTDOWN_OPACITY;
	if (opacity > MAX_COUNTDOWN_OPACITY) {
		opacity = DANGER_OPACITY;
		countdownFinished = true;
	}
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
