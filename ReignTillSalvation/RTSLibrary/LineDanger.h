#pragma once

#include "Danger.h"
#include <math.h>

class LineDanger : public Danger
{
public:
	LineDanger(std::unique_ptr<sftools::Chronometer>&, float, float, sf::Vector2f coord,
		sf::Vector2f direction, float width, float time_offset, float time_before_next);
	LineDanger(std::unique_ptr<sftools::Chronometer>&, float, float, sf::Vector2f coord);
	LineDanger(std::unique_ptr< sftools::Chronometer>&, float, sf::Texture*, sf::SoundBuffer* buffer);
	void affectZone(std::vector<std::unique_ptr<Individual>>&);
	sf::RectangleShape &getShape() { return shape; };
	void render(sf::RenderWindow&) override;
	void resetBuffer() { sound.resetBuffer(); }
private:
	sf::RectangleShape shape;

	void updateOpacity(float opacity);
	bool isInTheZone(std::unique_ptr<Individual> &individual);
	sf::Sprite sprite;
	sf::Texture* texture;
	int anim_count;
	sf::SoundBuffer* buffer;
	sf::Sound sound;

	void playSound();
};