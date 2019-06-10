#include "SoundManager.h"

SoundManager::SoundManager()
{
	loadSoundEffects();
}

void SoundManager::loadSoundEffects()
{
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile("../ReignTillSalvation/res/sound_effects/explosion.wav"))
		printf("cannot load explosion.wav music");
	sounds.insert({ "explosion", buffer });

	if (!buffer.loadFromFile("../ReignTillSalvation/res/sound_effects/laser.wav"))
		printf("cannot load laser.wav music");
	sounds.insert({ "laser", buffer });
}