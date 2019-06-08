#include "OtherFunctions.h"
#include "Value.h"

int randomint(int const &n) {
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(0, n);
	return distribution(engine);
}

sf::Color stringToColor(const std::string &color) {
	if (color.compare("Black") == 0)
		return sf::Color::Black;
	if (color.compare("White") == 0)
		return sf::Color::White;
	if (color.compare("Red") == 0)
		return sf::Color::Red;
	if (color.compare("Green") == 0)
		return sf::Color::Green;
	if (color.compare("Blue") == 0)
		return sf::Color::Blue;
	if (color.compare("Yellow") == 0)
		return sf::Color::Yellow;
	if (color.compare("Magenta") == 0)
		return sf::Color::Magenta;
	if (color.compare("Cyan") == 0)
		return sf::Color::Cyan;
}

float distanceBetween(sf::Vector2f p1, sf::Vector2f p2)
{
	return (float)sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

float magnitude(sf::Vector2f &vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

float calculateAngle(sf::Vector2f &vector) {
	float cos_teta = vector.x/magnitude(vector);
	return acos(cos_teta)*180/PI;
}