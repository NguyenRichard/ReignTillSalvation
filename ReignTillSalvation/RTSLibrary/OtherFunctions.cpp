#include "OtherFunctions.h"

int randomint(int const &n) {
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(0, n);
	return distribution(engine);
}

sf::Color stringToColor(const std::string &color) {
	if (color == "Black")
		return sf::Color::Black;
	if (color == "White")
		return sf::Color::White;
	if (color == "Red")
		return sf::Color::Red;
	if (color == "Green")
		return sf::Color::Green;
	if (color == "Blue")
		return sf::Color::Blue;
	if (color == "Yellow")
		return sf::Color::Yellow;
	if (color == "Magenta")
		return sf::Color::Magenta;
	if (color == "Cyan")
		return sf::Color::Cyan;

	return sf::Color::Transparent;
}