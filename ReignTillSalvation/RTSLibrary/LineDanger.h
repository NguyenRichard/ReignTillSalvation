#pragma once

#include "Danger.h"
#include <math.h>

class LineDanger : public Danger
{
public:
	//LineDanger(std::unique_ptr<sftools::Chronometer>&, float, float, sf::Vector2f coord,
	//	sf::Vector2f direction, float width, float time_offset, float time_before_next);
	//LineDanger(std::unique_ptr<sftools::Chronometer>&, float, float, sf::Vector2f coord);
	LineDanger(std::unique_ptr< sftools::Chronometer>&, float, sf::Texture*, sf::SoundBuffer* buffer);
	void affectZone(std::vector<std::unique_ptr<Individual>>&);
	sf::RectangleShape &getShape() { return shape; };
	void render(sf::RenderWindow&) override;
	void resetBuffer() { sound.resetBuffer(); }
	sf::Vector2f getCoord() { return coord; }
	sf::Vector2f getDirection() { return direction; }

	void updateDrawabbles(std::vector <std::pair<std::unique_ptr<sf::Drawable>, std::pair<std::vector<sf::Texture*>, int>>>&);
private:
	sf::RectangleShape shape;

	void updateOpacity(float opacity);
	bool isInTheZone(std::unique_ptr<Individual> &individual);
	sf::Sprite sprite;
	sf::Texture* texture;
	int anim_count;
	sf::SoundBuffer* buffer;
	sf::Sound sound;

	float width;
	float rotation;
	sf::Vector2f direction;
	sf::Vector2f coord;

	void playSound();
};