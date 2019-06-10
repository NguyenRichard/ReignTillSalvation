#pragma once

#include "SFML/Audio.hpp"
#include <map>

class SoundManager {
public:
	SoundManager();
	std::map<std::string, sf::SoundBuffer> sounds;

private:
	void loadSoundEffects();
};