#pragma once

#include "Danger.h"

class CircleDanger : public Danger
{
public:
	CircleDanger(std::unique_ptr<sftools::Chronometer>&, float, float, sf::Vector2f coord,
		float radius, float time_offset, float time_before_next);
	CircleDanger(std::unique_ptr<sftools::Chronometer>&, float, float, sf::Vector2f coord);
	CircleDanger(std::unique_ptr<sftools::Chronometer>&, float, sf::Texture*, sf::SoundBuffer* buffer);
	void affectZone(std::vector<std::unique_ptr<Individual>>&);
	sf::CircleShape &getShape() { return shape; };
	void render(sf::RenderWindow&) override;
	void resetBuffer() { sound.resetBuffer(); }
private:
	sf::CircleShape shape;
	sf::Sprite sprite;
	sf::Texture* texture;
	int anim_count;
	sf::SoundBuffer* buffer;
	sf::Sound sound;

	void updateOpacity(float opacity);
	void playSound();
};