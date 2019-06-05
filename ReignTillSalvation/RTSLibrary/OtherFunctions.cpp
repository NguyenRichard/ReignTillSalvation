#include "OtherFunctions.h"

int randomint(int const &n) {
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(0, n);
	return distribution(engine);
}